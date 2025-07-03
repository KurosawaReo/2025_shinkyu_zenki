/*
   - MeteoManager.h -
   覐΂̏o�����Ǘ�����.
*/
#pragma once
#include "Meteo.h"

//覐ΊǗ�.
class MeteoManager
{
private:
	Meteo meteo[METEO_CNT_MAX]{}; //覐΃f�[�^.
	float timer{};			      //覐ΐ����p.

	GameData* p_data{};           //�Q�[���f�[�^.

public:
	void Init(GameData*, Player*);
	void Reset();
	void Update();
	void Draw();

	void GenerateMeteo(); //覐ΐ���.
	BOOL GetMeteoPosNearest(DBL_XY _startPos, DBL_XY* _nearPos); //�Ŋ���覐΍��W��T��.
	BOOL IsHitMeteos(Circle* pos); //覐΂̂ǂꂩ1�ł��������Ă��邩.
};