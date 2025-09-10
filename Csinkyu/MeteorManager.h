/*
   - MeteorManager.h -
   覐΂̏o�����Ǘ�����.
*/
#pragma once
#include "Meteor.h"
#include "EffectManager.h"

//覐ΊǗ�.
class MeteorManager
{
private:
	Meteor meteor[METEO_CNT_MAX]{}; //覐΃f�[�^.
	float timer{};			      //覐ΐ����p.

	GameData*      p_data{};      //�Q�[���f�[�^.
	Player*        p_player{};	  //�v���C���[�f�[�^.
	EffectManager* p_effectMng{};

public:
	void Init(GameData*, Player*, EffectManager*);
	void Reset();
	void Update();
	void Draw();

	void SpawnMeteor(); //覐ΐ���.

	bool IsHitMeteors(Circle* cir, bool isDestroy); //覐΂̂ǂꂩ1�ł��������Ă��邩.
	bool GetMeteorPosNearest(DBL_XY _startPos, DBL_XY* _nearPos); //�Ŋ���覐΍��W��T��.
};