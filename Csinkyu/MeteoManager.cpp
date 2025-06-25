/*
   - MeteoManager.cpp -
   隕石の出現を管理する.
*/
#include "MeteoManager.h"

void MeteoManager::Init(GameData* _data) {

	p_data = _data;

	//全隕石ループ.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		meteo[i].Init(_data);
	}
}

void MeteoManager::Reset() {

	timer = 0;

	//全隕石ループ.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		meteo[i].Reset();
	}
}

void MeteoManager::Update() {

	//タイマーが残っていれば.
	if (timer > 0) {
		timer -= (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
	}
	//タイマーが0になったら.
	else {
		GenerateMeteo(); //隕石生成.
	}

	//全隕石ループ.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		meteo[i].Update(); //更新.
	}
}

void MeteoManager::Draw() {
	//全隕石ループ.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		meteo[i].Draw(); //描画.
	}
}

//隕石生成.
void MeteoManager::GenerateMeteo(){

	//空いてる所を探す.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		if (!meteo[i].GetActive()) {
			meteo[i].Spawn();         //出現.
			timer = METEO_SPAWN_SPAN; //タイマー再開.

			break; //出現完了.
		}
	}
}

//最寄りの隕石座標を探す.
DBL_XY MeteoManager::GetMeteoPosNearest(DBL_XY _pivotPos) {
	
	DBL_XY nearPos;  //最寄り座標.
	double shortest; //暫定の最短距離.

	//全隕石ループ.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		//有効なら.
		if (meteo[i].GetActive()) {

			DBL_XY tmpPos = meteo[i].GetPos();          //1つずつ座標取得.
			double tmpDis = CalcDis(tmpPos, _pivotPos); //距離を計算.

			//初回限定.
			if (i == 0) {
				shortest = tmpDis; //暫定1位.
				nearPos  = tmpPos;
			}
			//より近い場所が見つかれば更新.
			else if (tmpDis < shortest){
				shortest = tmpDis;
				nearPos  = tmpPos;
			}
		}
	}

	return nearPos; //最寄り座標を返す.
}