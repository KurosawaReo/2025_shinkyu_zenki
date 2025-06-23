/*
   - MeteoManager.h -
   隕石の出現を管理する.
*/
#pragma once
#include "Meteo.h"

#define METEO_MAX (256) //隕石の最大出現数.

//隕石管理.
class MeteoManager
{
private:
	Meteo meteo[METEO_MAX]{};          //隕石データ.
	Timer timer = Timer(CountDown, 2); //生成用タイマー.

public:
	void Init(GameData*);
	void Reset();
	void Update();
	void Draw();

	void   GenerateMeteo();                 //隕石生成.
	DBL_XY GetMeteoPosNearest(DBL_XY _pos); //最寄りの隕石座標を探す.
};