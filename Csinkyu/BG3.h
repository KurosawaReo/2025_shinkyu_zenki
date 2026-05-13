/*
   - BG3.h -
   
*/
#pragma once
#include <vector>

//3Dグリッド背景クラス.
class BG3
{
	//▼ ===== 定数 ===== ▼.
private:
	// グリッド設定.
	static constexpr int    GRID_COL = 20;     // 横分割数（列）.
	static constexpr int    GRID_ROW = 12;     // 縦分割数（奥行き）.
	static constexpr double VANISH_X = 960.0;   // 消失点X（画面中央 1920/2）.
	static constexpr double VANISH_Y = 380.0;   // 消失点Y（やや上寄り）.
	static constexpr double FLOOR_Y_NEAR = 1080.0;  // 手前の床Y座標.
	static constexpr double FLOOR_Y_FAR = VANISH_Y; // 奥側（消失点と同じ）.
	static constexpr double FLOOR_X_LEFT = -400.0;  // 手前左端X.
	static constexpr double FLOOR_X_RIGHT = 2320.0;  // 手前右端X.
	static constexpr int    STAR_COUNT = 80;     // 星の数.
	static constexpr int    PARTICLE_COUNT = 30;     // 光パーティクル数.

	//▼ ===== 構造体 ===== ▼.
private:
	// 星.
	struct Star {
		double x, y;
		double brightness;
		double twinkleSpeed;
		double twinkleOffset;
	};

	// 光パーティクル（グリッドライン上を流れる）.
	struct Particle {
		double progress;    // 0.0〜1.0（手前→奥）.
		int    col;         // 何列目のラインを流れるか.
		double speed;       // 移動速度.
		double brightness;  // 輝度.
		bool   isVertical;  // 縦ライン or 横ライン.
		int    row;         // 横ラインの場合の行.
	};

	//▼ ===== 変数 ===== ▼.
private:
	double counter{};      // 経過時間.
	double pulse{};        // 明滅・波動用.
	bool   isPaused{};     // ポーズ状態.

	std::vector<Star>     stars{};
	std::vector<Particle> particles{};

	// グリッド頂点キャッシュ（毎フレーム再計算）.
	// floor_pts[row][col] = スクリーン座標.
	// row=0 が消失点（奥）、row=GRID_ROW が手前.
	struct Pt { int x, y; };
	std::vector<std::vector<Pt>> floorPts{};  // 床グリッド点.
	std::vector<std::vector<Pt>> wallPts{};   // 壁グリッド点（上方向）.

	//▼ ===== 関数 ===== ▼.
public:
	void Init();
	void Update();
	void Draw();
	void Pause();
	void PauseEnd();

private:
	// 初期化ヘルパー.
	void InitStars();
	void InitParticles();
	void ResetParticle(Particle& p);

	// 描画ヘルパー.
	void CalcGridPoints();               // グリッド座標を計算.
	void DrawStars();                    // 星空.
	void DrawFloorGrid();                // 床グリッド.
	void DrawWallGrid();                 // 壁グリッド（左右）.
	void DrawParticles();                // 光パーティクル.
	void DrawCenterGlow();               // 消失点の発光.

	// 透視変換：3D座標→スクリーン座標.
	// x3d: -1.0〜+1.0（横）, z3d: 0.0〜1.0（奥行き、0=手前）
	Pt Project(double x3d, double y3d, double z3d) const;

	// 深度に応じた色の明るさ係数（0.0〜1.0）.
	static double DepthFade(double z /* 0=手前, 1=奥 */);

	// 色の明るさを係数でスケール.
	static unsigned int ScaleColor(unsigned int color, double scale);

	// 線形補間.
	static double Lerp(double a, double b, double t) { return a + (b - a) * t; }
};