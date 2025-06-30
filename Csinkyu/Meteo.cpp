/*
   - Meteo.cpp -
   降ってくる隕石.
*/
#include "Meteo.h"

void Meteo::Init(GameData* _data) {
	p_data   = _data;
	shapeCnt = 4;
}

void Meteo::Reset() {

	pos    = {0, 0};
	vel    = {0, 0};
	active = FALSE;
}

void Meteo::Update() {

	InputST* input = InputST::GetPtr();

	if (input->IsPushKeyTime(KEY_1) == 1) {
		shapeCnt++;
		if (shapeCnt > METEO_LINE_MAX) {
			shapeCnt = METEO_LINE_MAX;
		}
	}
	if (input->IsPushKeyTime(KEY_2) == 1) {
		shapeCnt--;
		if (shapeCnt < 3) {
			shapeCnt = 3;
		}
	}

	//隕石本体が有効なら.
	if (active) {
		//移動.
		pos.x += vel.x * METEO_SPEED * (double)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		pos.y += vel.y * METEO_SPEED * (double)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		//画面外で消去.
		if (IsOutInArea(pos, {}, 0, 0, WINDOW_WID, WINDOW_HEI)){
			active = FALSE; //無効にする.
		}
		//回転.
		ang += (p_data->isSlow) ? SLOW_MODE_SPEED : 1;

		UpdateMeteoLine();
	}
}

void Meteo::Draw() {
	
	//隕石本体が有効なら.
	if (active) {

		Circle cir = {pos, 8, 0xFFFFFF};
		DrawCircleST(&cir, FALSE);

		//有効な線を全て描画.
		for (int i = 0; i < shapeCnt; i++) {
			
			int g = _int(255 * fabs(sin(pos.x/200))); //色の変化.
			line[i].clr = GetColor(0, g, 255);
			DrawLineST(&line[i]);
		}
	}
}

//隕石出現.
void Meteo::Spawn() {

	int rnd1 = RndNum(0, 99);
	int rnd2 = RndNum(0, 99);

	INT_XY goalPos{}; //目標座標.

	//50%:上下端から出現.
	if (rnd1 < 50) {
		pos.x = RndNum(0, WINDOW_WID);        //xの設定.
		pos.y = (rnd2 < 50) ? 0 : WINDOW_HEI; //yの設定.
	}
	//50%:左右端から出現.
	else {
		pos.x = (rnd2 < 50) ? 0 : WINDOW_WID; //xの設定.
		pos.y = RndNum(0, WINDOW_HEI);        //yの設定.
	}

	//目標地点の抽選.
	{
		goalPos.x = RndNum(WINDOW_WID/2 - METEO_GOAL_RAND_RANGE, WINDOW_WID/2 + METEO_GOAL_RAND_RANGE);
		goalPos.y = RndNum(WINDOW_HEI/2 - METEO_GOAL_RAND_RANGE, WINDOW_HEI/2 + METEO_GOAL_RAND_RANGE);
		//目標地点までの角度を求める.
		double rad = atan2(goalPos.y - pos.y, goalPos.x - pos.x);
		//xとyのvectorに分解.
		vel = CalcRadToPos(rad);
	}

	active = TRUE; //有効にする.
}

//隕石を構成する線の更新.
void Meteo::UpdateMeteoLine() {

	float rot = 360/shapeCnt; //図形の1つの角の角度.
	float len = 120/shapeCnt; //図形の1つの辺の長さ.

	for (int i = 0; i < shapeCnt; i++) {
		
		//基準となる位置と角度.
		float  mainAng = ang+i*rot;
		DBL_XY mainPos = CalcLineAng(pos, mainAng, 30);
		
		line[i].stPos = CalcLineAng(mainPos, mainAng+90, len);
		line[i].edPos = CalcLineAng(mainPos, mainAng-90, len);
	}
}