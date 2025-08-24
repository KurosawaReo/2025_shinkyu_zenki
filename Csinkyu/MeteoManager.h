/*
   - MeteoManager.h -
   覐΂̏o�����Ǘ�����.
*/
#pragma once
#include "Meteo.h"
#include "EffectManager.h"

//覐ΊǗ�.
class MeteoManager
{
private:
	Meteo meteo[METEO_CNT_MAX]{}; //覐΃f�[�^.
	float timer{};			      //覐ΐ����p.

	GameData*      p_data{};      //�Q�[���f�[�^.
	Player*        p_player{};	  //�v���C���[�f�[�^.
	EffectManager* p_effectMng{};
	Calc*          p_calc{};

public:
	void Init(GameData*, Player*, EffectManager*);
	void Reset();
	void Update();
	void Draw();

	void SpawnMeteo(); //覐ΐ���.

	bool IsHitMeteos(Circle* cir, bool isDestroy); //覐΂̂ǂꂩ1�ł��������Ă��邩.
	bool GetMeteoPosNearest(DBL_XY _startPos, DBL_XY* _nearPos); //�Ŋ���覐΍��W��T��.
};