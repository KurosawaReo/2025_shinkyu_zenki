/*
   - MeteoManager.h -
   覐΂̏o�����Ǘ�����.
*/
#pragma once
#include "Meteo.h"

#define METEO_MAX (256) //覐΂̍ő�o����.

//覐ΊǗ�.
class MeteoManager
{
private:
	Meteo meteo[METEO_MAX]{};          //覐΃f�[�^.
	Timer timer = Timer(CountDown, 2); //�����p�^�C�}�[.

public:
	void Init(GameData*);
	void Reset();
	void Update();
	void Draw();

	void   GenerateMeteo();                 //覐ΐ���.
	DBL_XY GetMeteoPosNearest(DBL_XY _pos); //�Ŋ���覐΍��W��T��.
};