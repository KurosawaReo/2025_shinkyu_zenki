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

	//有効なら.
	if (active) {
		//移動.
		pos.x += vel.x * METEO_SPEED * (double)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		pos.y += vel.y * METEO_SPEED * (double)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		//printfDx(_T("② x:%f, y:%f\n"), vel.x, vel.y);
		//printfDx(_T("③ x:%f, y:%f\n"), pos.x, pos.y);
		//画面外で消去.
		if (IsOutInArea(pos, {}, 0, 0, WINDOW_WID, WINDOW_HEI)){
			active = FALSE; //無効にする.
			//printfDx(_T("無効になった\n"));
		}
	}
}

void Meteo::Draw() {
	
	//有効なら.
	if (active) {
		DrawCircle(pos.x, pos.y, 20, 0xFFFFFF); //kari
	}
}

//隕石出現.
void Meteo::Spawn() {

	int rnd1 = RndNum(0, 99);
	int rnd2 = RndNum(0, 99);

	INT_XY goalPos; //目標座標.

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
		double ang = atan2(goalPos.y - pos.y, goalPos.x - pos.x);
		//xとyのvectorに分解.
		vel = CalcAngToPos(ang);

		printfDx(_T("ang:%f\n"), ang*180/M_PI);
		printfDx(_T("x:%f, y:%f\n"), vel.x, vel.y);
	}
}