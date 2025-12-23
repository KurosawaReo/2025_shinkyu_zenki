/*
   - BG2.cpp -
*/
#include "BG2.h"
#include <cmath>

//初期化.
void BG2::Init() {
	angle    = 0.0;
	pulse    = 0.0;
	isPaused = false;
}

//更新.
void BG2::Update() {
	if (isPaused) return;

	angle += 0.002;   // ゆっくり回転
	pulse += 0.05;    // 明滅用
}

//描画.
void BG2::Draw() {

	const DBL_XY center = { WINDOW_WID / 2.0, WINDOW_HEI / 2.0 };

	//====================================
	// 放射状ライン（サイバー感）
	//====================================
	for (int i = 0; i < 16; i++) {
		double a = angle + (M_PI * 2 / 16) * i;

		Line line{};
		line.stPos = center;
		line.edPos = {
			center.x + cos(a) * 400,
			center.y + sin(a) * 400
		};
		line.color = { 80, 120, 255 };

		DrawLineKR(line, true, 1.5f);
	}

	//====================================
	// 回転する円弧（軌道／レーダー）
	//====================================
	for (int i = 0; i < 3; i++) {
		KR::Pie arc{};
		arc.pos    = center;
		arc.r      = 180 + i * 40;
		arc.stAng  = angle * (i + 1);
		arc.arcAng = M_PI / 2;
		arc.color  = { 120, 200, 255 };

		DrawArcKR(arc, true, 2.0f);
	}

	//====================================
	// 中央HUDボックス
	//====================================
	{
		double s = 40 + sin(pulse) * 5;

		Box box{};
		box.pos   = center;
		box.size  = { s, s };
		box.color = { 180, 220, 255 };

		DrawBoxKR(box, Anchor::Mid, false, true);
	}

	//====================================
	// 背景グリッド（薄く）
	//====================================
	DrawWindowGrid(
		WINDOW_WID,
		WINDOW_HEI,
		80,
		{ 40, 40, 80 },
		{ 40, 40, 80 }
	);

	DrawStr str(_T("ChatGPT作成背景"), App::GetWindowRect().GetMid(), 0xffffff);
	str.Draw();
}

//ポーズする.
void BG2::PauseAnim() {
	isPaused = true;
}

//ポーズ解除.
void BG2::RestartAnim() {
	isPaused = false;
}
