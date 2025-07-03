/*
   - MeteoManager.cpp -
   隕石の出現を管理する.
*/
#include "MeteoManager.h"

void MeteoManager::Init(GameData* _data, Player* _player) {

	p_data = _data;

	//全隕石ループ.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		meteo[i].Init(_data, _player);
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

#if true
		int x =   0 + 10 * (i%100);
		int y = 100 + 20 * (i/100);
		DrawString(0, 80, _T("隕石のactive"), 0xFF00FF);
		DrawFormatString(x, y, 0xFF00FF, _T("%d"), meteo[i].GetActive());
#endif
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
BOOL MeteoManager::GetMeteoPosNearest(DBL_XY _startPos, DBL_XY* _nearPos) {

	BOOL isExistMeteo = FALSE; //1つでも隕石があるか.

	double shortest = 0; //暫定の最短距離.

	//全隕石ループ.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		//有効なら.
		if (meteo[i].GetActive()) {

			DBL_XY tmpPos = meteo[i].GetPos();          //1つずつ座標取得.
			double tmpDis = CalcDis(tmpPos, _startPos); //距離を計算.

			//初回限定.
			if (i == 0) {
				shortest  = tmpDis; //暫定1位.
				*_nearPos = tmpPos;
			}
			//より近い場所が見つかれば更新.
			else if (tmpDis < shortest){
				shortest  = tmpDis;
				*_nearPos = tmpPos;
			}

			isExistMeteo = TRUE; //隕石がある.
		}
	}

	return isExistMeteo;
}

//隕石のどれか1つでも当たっているか.
BOOL MeteoManager::IsHitMeteos(Circle* pos) {

	BOOL hit;
	
	//全隕石ループ.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		if (meteo[i].GetActive()) {
			
			hit = meteo[i].IsHitMeteo(pos); //1こずつ判定.
			if (hit) {
				meteo[i].Destroy(); //隕石を破壊.
				return TRUE; //1つでも当たっている.
			}
		}
	}
	return FALSE; //どれも当たっていない.
}