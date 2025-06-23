/*
   - MeteoManager.cpp -
   隕石の出現を管理する.
*/
#include "MeteoManager.h"

void MeteoManager::Init(GameData* _data) {
	//全隕石ループ.
	for (int i = 0; i < METEO_MAX; i++) {
		meteo[i].Init(_data);
	}
}

void MeteoManager::Reset() {

	timer.Start();
	
	//全隕石ループ.
	for (int i = 0; i < METEO_MAX; i++) {
		meteo[i].Reset();
	}
}

void MeteoManager::Update() {

	//タイマーが0になったら.
	if (timer.GetPassTime() <= 0) {
		GenerateMeteo(); //隕石生成.
	}

	//全隕石ループ.
	for (int i = 0; i < METEO_MAX; i++) {
		meteo[i].Update(); //更新.
	}
}

void MeteoManager::Draw() {
	//全隕石ループ.
	for (int i = 0; i < METEO_MAX; i++) {
		meteo[i].Draw(); //描画.
	}
}

//隕石生成.
void MeteoManager::GenerateMeteo(){

	//空いてる所を探す.
	for (int i = 0; i < METEO_MAX; i++) {
		if (!meteo[i].GetActive()) {

			meteo[i].SetActive(TRUE); //有効にする.
			meteo[i].Spawn();         //出現.
			timer.Start();            //タイマー再開.

			break; //出現完了.
		}
	}
}

//最寄りの隕石座標を探す.
DBL_XY MeteoManager::GetMeteoPosNearest(DBL_XY _pivotPos) {
	
	DBL_XY nearPos;  //最寄り座標.
	double shortest; //暫定の最短距離.

	//全隕石ループ.
	for (int i = 0; i < METEO_MAX; i++) {
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