/*
   - Meteo.cpp -
   降ってくる隕石.
*/
#include "Meteo.h"

void Meteo::Init(GameData* _data) {
	p_data = _data;
}

void Meteo::Reset() {

	pos    = {0, 0};
	vel    = {0, 0};
	active = FALSE;
}

void Meteo::Update() {

	//隕石本体が有効なら.
	if (active) {
		//移動.
		pos.x += vel.x * METEO_SPEED * (double)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		pos.y += vel.y * METEO_SPEED * (double)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		//画面外で消去.
		if (IsOutInArea(pos, { METEO_LINE_DIS_MAX*2, METEO_LINE_DIS_MAX*2 }, 0, 0, WINDOW_WID, WINDOW_HEI, TRUE)){
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
		for (int i = 0; i < shape.lineCnt; i++) {
			
			int g = _int(255 * fabs(sin(pos.x/200))); //色の変化.
			shape.line[i].clr = GetColor(0, g, 255);
			DrawLineST(&shape.line[i]);
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

	//隕石の設定.
	{
		//何角形にするか.
		shape.lineCnt = RndNum(3, METEO_LINE_CNT_MAX);
		//頂点の位置を抽選.
		for (int i = 0; i < shape.lineCnt; i++) {
			shape.lineDis[i] = RndNum(METEO_LINE_DIS_MIN, METEO_LINE_DIS_MAX);
		}
	}

	active = TRUE; //隕石を有効にする.
}

//隕石を構成する線の更新.
void Meteo::UpdateMeteoLine() {

	float rot = 360/shape.lineCnt; //図形の1つの角の角度.

	//回転しながら始点と終点を設定していく.
	for (int i = 0; i < shape.lineCnt; i++) {
		
		//要素数が0未満なら最大値へ移動する.
		int i2 = ((i-1) < 0) ? shape.lineCnt-1 : (i-1);

		shape.line[i].stPos = CalcLineAng(pos, ang +  i  *rot, shape.lineDis[i]);  //現在の角度から計算.
		shape.line[i].edPos = CalcLineAng(pos, ang + (i2)*rot, shape.lineDis[i2]); //1つ前の角度から計算.
	}
}