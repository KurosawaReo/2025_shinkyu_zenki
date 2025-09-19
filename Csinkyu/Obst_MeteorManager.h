/*
   - Obst_MeteorManager.h -

   ��Q��: 覐Ώo���Ǘ�.
*/
#pragma once
#include "Obst_Meteor.h"

//覐ΊǗ�.
class MeteorManager
{
public: //����.
	static MeteorManager* GetPtr() {
		static MeteorManager inst; //���g�̃C���X�^���X.
		return &inst;
	}

private:
	Meteor meteor[METEOR_CNT_MAX]{}; //覐΃f�[�^.
	float timer{};			      //覐ΐ����p.

	GameData*      p_data{};      //�Q�[���f�[�^.
	Player*        p_player{};	  //�v���C���[�f�[�^.
	EffectManager* p_effectMng{};

public:
	void Init();
	void Reset();
	void Update();
	void Draw();

	void SpawnMeteor(); //覐ΐ���.

	bool IsHitMeteors(Circle cir, bool isDestroy); //覐΂̂ǂꂩ1�ł��������Ă��邩.
	bool GetMeteorPosNearest(DBL_XY _startPos, DBL_XY* _nearPos); //�Ŋ���覐΍��W��T��.
};