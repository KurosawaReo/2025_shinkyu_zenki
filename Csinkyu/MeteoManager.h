/*
   - MeteoManager.h -
   隕石の出現を管理する.
*/
#pragma once
#include "Meteo.h"

//隕石管理.
class MeteoManager
{
private:
	Meteo meteo[METEO_CNT_MAX]{}; //隕石データ.
	float timer;			      //隕石生成用.

	GameData* p_data;             //ゲームデータ.

public:
	void Init(GameData*);
	void Reset();
	void Update();
	void Draw();

	void   GenerateMeteo();                 //隕石生成.
	DBL_XY GetMeteoPosNearest(DBL_XY _pos); //最寄りの隕石座標を探す.
};