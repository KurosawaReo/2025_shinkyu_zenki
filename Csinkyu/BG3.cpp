/*
   - BG3.cpp -
   DXライブラリ（2Dゲーム用疑似3D背景）.

   ┌──────────────────────────────────────────┐
   │  描画内容                                │
   │  1. 星空（上半分）                       │
   │  2. 消失点の発光（中央やや上）           │
   │  3. 床グリッド（透視投影・青発光）       │
   │  4. 壁グリッド（左右）                   │
   │  5. 光パーティクル（ライン上を流れる）   │
   └──────────────────────────────────────────┘
*/
#include "BG3.h"
#include "Global.h"
#include "DxLib.h"
#include <cmath>
// Windows の max/min マクロを無効化（<algorithm> より前に定義）.
#ifndef NOMINMAX
#  define NOMINMAX
#endif
#include <algorithm>
#include <random>

// ── 安全なインラインヘルパー（マクロ衝突回避）────────────────────────
namespace bg3util {
	inline double dmax(double a, double b) { return a > b ? a : b; }
	inline double dmin(double a, double b) { return a < b ? a : b; }
	inline int    imax(int    a, int    b) { return a > b ? a : b; }
	inline int    imin(int    a, int    b) { return a < b ? a : b; }
	inline double dclamp(double v, double lo, double hi) {
		return v < lo ? lo : (v > hi ? hi : v);
	}
	inline int    iclamp(int v, int lo, int hi) {
		return v < lo ? lo : (v > hi ? hi : v);
	}
}
using namespace bg3util;

// ── ウィンドウサイズ（Global.h の WINDOW_WID / WINDOW_HEI に合わせる）──
static constexpr int WIN_W = WINDOW_WID;  // 1920
static constexpr int WIN_H = WINDOW_HEI;  // 1080

// ── ランダム生成器 ─────────────────────────────────────────────────────
static std::mt19937 rng{ std::random_device{}() };
static double Rand01() {
	return std::uniform_real_distribution<double>(0.0, 1.0)(rng);
}
static double RandRange(double lo, double hi) {
	return lo + Rand01() * (hi - lo);
}
static int RandInt(int lo, int hi) { // [lo, hi]
	return std::uniform_int_distribution<int>(lo, hi)(rng);
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  透視投影
//  x3d : -1.0(左端) 〜 +1.0(右端)
//  y3d : -1.0(上)   〜 +1.0(下)  ※床面は y3d=0 固定
//  z3d :  0.0(手前) 〜  1.0(奥)
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
BG3::Pt BG3::Project(double x3d, double y3d, double z3d) const {
	// z が消失点に近づくほど収束.
	const double fov = 1.2;           // 視野角係数.
	const double dz = 1.0 - z3d * (1.0 - 0.001); // 0 除算防止.
	const double scale = fov / dz;

	// スクリーン中央を消失点に合わせる.
	const double sx = VANISH_X + x3d * scale * (WIN_W * 0.5);
	const double sy = VANISH_Y + y3d * scale * (WIN_H * 0.5);
	return { static_cast<int>(sx), static_cast<int>(sy) };
}

// 深度フェード：奥ほど暗く（指数的）.
double BG3::DepthFade(double z) {
	double val = 1.0 - z * z * 0.85;
	return (val > 0.0) ? val : 0.0;
}

// 色に輝度スケール適用.
unsigned int BG3::ScaleColor(unsigned int color, double scale) {
	scale = dclamp(scale, 0.0, 1.0);
	int r = static_cast<int>(((color >> 16) & 0xFF) * scale);
	int g = static_cast<int>(((color >> 8) & 0xFF) * scale);
	int b = static_cast<int>((color & 0xFF) * scale);
	return GetColor(r, g, b);
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  初期化
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void BG3::Init() {
	counter = 0.0;
	pulse = 0.0;
	isPaused = false;
	InitStars();
	InitParticles();
	// グリッド点配列サイズ確保.
	floorPts.assign(GRID_ROW + 1, std::vector<Pt>(GRID_COL + 1));
	wallPts.assign(GRID_ROW + 1, std::vector<Pt>(GRID_COL + 1));
}

void BG3::InitStars() {
	stars.resize(STAR_COUNT);
	for (auto& s : stars) {
		s.x = RandRange(0.0, WIN_W);
		s.y = RandRange(0.0, VANISH_Y * 1.1);  // 上半分に集中.
		s.brightness = RandRange(0.4, 1.0);
		s.twinkleSpeed = RandRange(0.02, 0.08);
		s.twinkleOffset = RandRange(0.0, M_PI * 2.0);
	}
}

void BG3::InitParticles() {
	particles.resize(PARTICLE_COUNT);
	for (auto& p : particles) {
		ResetParticle(p);
		p.progress = Rand01(); // 初期位置をバラけさせる.
	}
}

void BG3::ResetParticle(Particle& p) {
	p.isVertical = (Rand01() < 0.6);    // 縦ライン優先.
	if (p.isVertical) {
		p.col = RandInt(0, GRID_COL);
		p.row = 0;
	}
	else {
		p.col = 0;
		p.row = RandInt(0, GRID_ROW);
	}
	p.progress = 0.0;
	p.speed = RandRange(0.003, 0.012);
	p.brightness = RandRange(0.6, 1.0);
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  更新
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void BG3::Update() {
	if (isPaused) return;
	counter += 1.0;
	pulse += 0.04;

	// パーティクル更新.
	for (auto& p : particles) {
		// 縦ラインは奥→手前（progress: 0=奥, 1=手前）に流れる見た目.
		// ここでは 0→1 で「手前方向に移動」とする.
		p.progress += p.speed;
		if (p.progress >= 1.0) {
			ResetParticle(p);
		}
	}
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  グリッド座標計算
//  ・床面：y3d=0, x3d=-1〜+1, z3d=0〜1
//  ・壁面：x3d=±1, y3d=-1〜0, z3d=0〜1
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void BG3::CalcGridPoints() {
	for (int row = 0; row <= GRID_ROW; row++) {
		double z = static_cast<double>(row) / GRID_ROW; // 0=手前, 1=奥.
		// z は「手前→奥」なので row=0 が手前、row=GRID_ROW が奥.
		// 見た目を自然にするため z に指数カーブをかける.
		double ze = std::pow(z, 1.5);

		for (int col = 0; col <= GRID_COL; col++) {
			double x = -1.0 + 2.0 * static_cast<double>(col) / GRID_COL;

			// 床.
			floorPts[row][col] = Project(x, 1.0, ze);  // y3d=+1.0 が床面.

			// 壁（床グリッドの側面。y3d を -1〜+1 で使う）.
			// 左壁：x3d=-1, 右壁：x3d=+1 で別途描画するので
			// ここでは壁の「天井側」点を wallPts に格納.
			wallPts[row][col] = Project(x, -1.2, ze); // 上方向.
		}
	}
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  描画メイン
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void BG3::Draw() {
	// 背景を黒で塗りつぶす.
	DrawBox(0, 0, WIN_W, WIN_H, GetColor(0, 0, 8), TRUE);

	CalcGridPoints();

	DrawStars();
	DrawCenterGlow();
	DrawWallGrid();
	DrawFloorGrid();
	DrawParticles();
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  星空
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void BG3::DrawStars() {
	for (const auto& s : stars) {
		double br = s.brightness
			* (0.6 + 0.4 * std::sin(pulse * s.twinkleSpeed * 20.0 + s.twinkleOffset));
		int v = static_cast<int>(255.0 * br);
		// 明るい星は少し大きく.
		unsigned int col = GetColor(v, v, imin(255, v + 40));
		if (br > 0.8) {
			DrawBox(
				static_cast<int>(s.x) - 1, static_cast<int>(s.y) - 1,
				static_cast<int>(s.x) + 1, static_cast<int>(s.y) + 1,
				col, TRUE
			);
		}
		else {
			DrawPixel(static_cast<int>(s.x), static_cast<int>(s.y), col);
		}
	}
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  消失点の発光（中央グロー）
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void BG3::DrawCenterGlow() {
	const int cx = static_cast<int>(VANISH_X);
	const int cy = static_cast<int>(VANISH_Y);
	const double pulseAmp = 0.15 + 0.05 * std::sin(pulse * 1.3);

	// 複数の半透明円でグローを重ねる（DXライブラリのSetDrawBlendMode使用）.
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// 外側〜内側に向かって輝度を高める.
	struct GlowRing { int r; int alpha; unsigned int color; };
	const GlowRing rings[] = {
		{ 160, 18,  GetColor(0,  40, 120) },
		{ 100, 30,  GetColor(0,  80, 200) },
		{  60, 50,  GetColor(20, 120, 255) },
		{  30, 80,  GetColor(80, 180, 255) },
		{  12, 150, GetColor(160,220, 255) },
		{   5, 220, GetColor(220,240, 255) },
	};
	for (const auto& ring : rings) {
		int a = static_cast<int>(ring.alpha * (1.0 + pulseAmp));
		SetDrawBlendMode(DX_BLENDMODE_ADD, imin(255, a));
		DrawCircle(cx, cy, ring.r, ring.color, TRUE);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  床グリッド描画
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void BG3::DrawFloorGrid() {
	// ───── 床のポリゴン塗り（グラデーション風）─────
	// 行ごとに少し暗い四角形を描く（奥ほど暗い）.
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	for (int row = 0; row < GRID_ROW; row++) {
		// この行の z 値（手前=小、奥=大）.
		double z0 = std::pow(static_cast<double>(row) / GRID_ROW, 1.5);
		double z1 = std::pow(static_cast<double>(row + 1) / GRID_ROW, 1.5);
		double fade = DepthFade((z0 + z1) * 0.5);

		// 床の帯を四角で描く.
		int x0 = floorPts[row][0].x;
		int y0 = floorPts[row][0].y;
		int x1 = floorPts[row][GRID_COL].x;
		int y1 = floorPts[row + 1][0].y;
		int x2 = floorPts[row + 1][GRID_COL].x;

		// 帯の色（深い青系）.
		int blue = static_cast<int>(15.0 * fade);
		int gr = static_cast<int>(8.0 * fade);
		DrawBox(
			imin(x0, x1), imin(y0, y1),
			imax(x1, x2), imax(y0, y1),
			GetColor(0, gr, blue), TRUE
		);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// ───── 加算ブレンドでライン描画 ─────
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// 横ライン（行方向）.
	for (int row = 0; row <= GRID_ROW; row++) {
		double z = std::pow(static_cast<double>(row) / GRID_ROW, 1.5);
		double fade = DepthFade(z);
		// パルスで輝度が揺れる（手前ほど強く）.
		double p = 1.0 + 0.25 * std::sin(pulse * 2.0 - z * 6.0) * (1.0 - z);
		int alpha = static_cast<int>(200.0 * fade * p);
		alpha = iclamp(alpha, 0, 255);

		SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
		for (int col = 0; col < GRID_COL; col++) {
			auto& p0 = floorPts[row][col];
			auto& p1 = floorPts[row][col + 1];
			DrawLine(p0.x, p0.y, p1.x, p1.y, GetColor(0, 120, 255));
		}
	}

	// 縦ライン（列方向）.
	for (int col = 0; col <= GRID_COL; col++) {
		double xNorm = static_cast<double>(col) / GRID_COL; // 0〜1.
		// 中央の列ほど明るい.
		double centerBoost = 1.0 - std::abs(xNorm - 0.5) * 1.2;
		centerBoost = dmax(0.2, centerBoost);

		for (int row = 0; row < GRID_ROW; row++) {
			double z = std::pow(static_cast<double>(row + 0.5) / GRID_ROW, 1.5);
			double fade = DepthFade(z) * centerBoost;
			double p = 1.0 + 0.2 * std::sin(pulse * 1.5 + col * 0.4);
			int alpha = static_cast<int>(180.0 * fade * p);
			alpha = iclamp(alpha, 0, 255);

			SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
			auto& p0 = floorPts[row][col];
			auto& p1 = floorPts[row + 1][col];
			DrawLine(p0.x, p0.y, p1.x, p1.y, GetColor(0, 100, 255));
		}
	}

	// 交点に光点.
	for (int row = 0; row <= GRID_ROW; row += 2) {
		double z = std::pow(static_cast<double>(row) / GRID_ROW, 1.5);
		double fade = DepthFade(z);
		for (int col = 0; col <= GRID_COL; col += 2) {
			double xNorm = static_cast<double>(col) / GRID_COL;
			double cb = 1.0 - std::abs(xNorm - 0.5) * 1.5;
			cb = dmax(0.0, cb);
			double br = fade * cb * (0.8 + 0.2 * std::sin(pulse + row + col));
			int alpha = static_cast<int>(200.0 * br);
			if (alpha < 10) continue;
			SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
			auto& pt = floorPts[row][col];
			DrawCircle(pt.x, pt.y, 2, GetColor(100, 200, 255), TRUE);
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  壁グリッド（左右）
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void BG3::DrawWallGrid() {
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// ─── 左壁（col=0 の縦ライン）───
	// 壁面：床の左端ライン（x3d=-1）から上方向に伸びる.
	for (int row = 0; row < GRID_ROW; row++) {
		double z = std::pow(static_cast<double>(row + 0.5) / GRID_ROW, 1.5);
		double fade = DepthFade(z);
		int alpha = static_cast<int>(140.0 * fade);

		// 床の左端点.
		auto& flr0 = floorPts[row][0];
		auto& flr1 = floorPts[row + 1][0];
		// 壁の上端点.
		auto& wal0 = wallPts[row][0];
		auto& wal1 = wallPts[row + 1][0];

		SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
		// 縦の柱ライン.
		DrawLine(flr0.x, flr0.y, wal0.x, wal0.y, GetColor(0, 80, 200));
		// 奥行きライン（壁の横）.
		DrawLine(wal0.x, wal0.y, wal1.x, wal1.y, GetColor(0, 80, 200));
		DrawLine(flr0.x, flr0.y, flr1.x, flr1.y, GetColor(0, 80, 200));
	}

	// ─── 右壁（col=GRID_COL）───
	for (int row = 0; row < GRID_ROW; row++) {
		double z = std::pow(static_cast<double>(row + 0.5) / GRID_ROW, 1.5);
		double fade = DepthFade(z);
		int alpha = static_cast<int>(140.0 * fade);

		auto& flr0 = floorPts[row][GRID_COL];
		auto& flr1 = floorPts[row + 1][GRID_COL];
		auto& wal0 = wallPts[row][GRID_COL];
		auto& wal1 = wallPts[row + 1][GRID_COL];

		SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
		DrawLine(flr0.x, flr0.y, wal0.x, wal0.y, GetColor(0, 80, 200));
		DrawLine(wal0.x, wal0.y, wal1.x, wal1.y, GetColor(0, 80, 200));
		DrawLine(flr0.x, flr0.y, flr1.x, flr1.y, GetColor(0, 80, 200));
	}

	// ─── 壁の横グリッドライン ───
	// 左壁・右壁に水平ラインを追加.
	static constexpr int WALL_DIV = 6; // 縦分割数.
	for (int wd = 0; wd <= WALL_DIV; wd++) {
		double yRatio = static_cast<double>(wd) / WALL_DIV; // 0=床, 1=天井.

		for (int row = 0; row <= GRID_ROW; row++) {
			double z = std::pow(static_cast<double>(row) / GRID_ROW, 1.5);
			double fade = DepthFade(z) * (1.0 - yRatio * 0.6);
			int alpha = static_cast<int>(100.0 * fade);

			auto& flrL = floorPts[row][0];
			auto& flrR = floorPts[row][GRID_COL];
			auto& walL = wallPts[row][0];
			auto& walR = wallPts[row][GRID_COL];

			// 左壁の横ライン点を補間.
			int lx = static_cast<int>(Lerp(flrL.x, walL.x, yRatio));
			int ly = static_cast<int>(Lerp(flrL.y, walL.y, yRatio));
			int rx = static_cast<int>(Lerp(flrR.x, walR.x, yRatio));
			int ry = static_cast<int>(Lerp(flrR.y, walR.y, yRatio));

			if (alpha > 5) {
				SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
				// 左壁の横ライン（左端近くのみ）.
				if (row < GRID_ROW) {
					auto& flrL2 = floorPts[row + 1][0];
					auto& walL2 = wallPts[row + 1][0];
					int lx2 = static_cast<int>(Lerp(flrL2.x, walL2.x, yRatio));
					int ly2 = static_cast<int>(Lerp(flrL2.y, walL2.y, yRatio));
					DrawLine(lx, ly, lx2, ly2, GetColor(0, 60, 180));

					auto& flrR2 = floorPts[row + 1][GRID_COL];
					auto& walR2 = wallPts[row + 1][GRID_COL];
					int rx2 = static_cast<int>(Lerp(flrR2.x, walR2.x, yRatio));
					int ry2 = static_cast<int>(Lerp(flrR2.y, walR2.y, yRatio));
					DrawLine(rx, ry, rx2, ry2, GetColor(0, 60, 180));
				}
			}
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  光パーティクル（グリッドライン上を流れる）
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void BG3::DrawParticles() {
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	for (const auto& p : particles) {
		if (p.isVertical) {
			// 縦ライン上を奥→手前（z: 1→0）に流れる.
			// progress=0 が奥、1 が手前.
			double zFar = 1.0 - p.progress;
			double zNear = 1.0 - dmax(0.0, p.progress - 0.06);
			double zF = std::pow(dclamp(zFar, 0.0, 1.0), 1.5);
			double zN = std::pow(dclamp(zNear, 0.0, 1.0), 1.5);
			double x3d = -1.0 + 2.0 * static_cast<double>(p.col) / GRID_COL;

			Pt pt0 = Project(x3d, 1.0, zF);
			Pt pt1 = Project(x3d, 1.0, zN);

			double fade = DepthFade(zF) * p.brightness;
			int alpha = static_cast<int>(220.0 * fade);
			alpha = iclamp(alpha, 0, 255);

			SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
			DrawLine(pt0.x, pt0.y, pt1.x, pt1.y, GetColor(60, 180, 255));
			// 先端に輝点.
			if (alpha > 30) {
				SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
				DrawCircle(pt0.x, pt0.y, 3, GetColor(180, 230, 255), TRUE);
			}
		}
		else {
			// 横ライン上を左→右に流れる.
			double z = std::pow(static_cast<double>(p.row) / GRID_ROW, 1.5);
			double fade = DepthFade(z) * p.brightness;
			int alpha = static_cast<int>(180.0 * fade);
			alpha = iclamp(alpha, 0, 255);

			double x0 = -1.0 + 2.0 * dmax(0.0, p.progress - 0.06);
			double x1 = -1.0 + 2.0 * p.progress;
			x0 = dclamp(x0, -1.0, 1.0);
			x1 = dclamp(x1, -1.0, 1.0);

			Pt pt0 = Project(x0, 1.0, z);
			Pt pt1 = Project(x1, 1.0, z);

			SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
			DrawLine(pt0.x, pt0.y, pt1.x, pt1.y, GetColor(80, 200, 255));
			if (alpha > 30) {
				DrawCircle(pt1.x, pt1.y, 2, GetColor(200, 240, 255), TRUE);
			}
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  ポーズ制御
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void BG3::Pause() { isPaused = true; }
void BG3::PauseEnd() { isPaused = false; }