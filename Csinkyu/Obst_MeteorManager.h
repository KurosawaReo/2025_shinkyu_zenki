/*
   - Obst_MeteorManager.h -

   ��Q��: 覐Ώo���Ǘ�.
*/
#pragma once
#include "Obst_Meteor.h"

//覐ΊǗ�[�p���s��]
class MeteorManager final
{
//�����̊֌W.
public:
	//���̎擾�p.
	static MeteorManager& GetInst() {
		static MeteorManager inst; //���g�̃C���X�^���X.
		return inst;
	}
	//�g�p�֎~.
	MeteorManager(const MeteorManager&) = delete;
	MeteorManager& operator=(const MeteorManager&) = delete;
private:
	//constructor(�V�K�쐬���ł��Ȃ�����)
	MeteorManager(){}

//���f�[�^.
private:
	Meteor meteor[METEOR_CNT_MAX]{}; //覐΃f�[�^.

	float timer{};       //覐ΐ����p.
	bool  isSpawnAble{}; //�����\���ǂ���.

	GameData*      p_data{};      //�Q�[���f�[�^.
	Player*        p_player{};	  //�v���C���[.
	EffectManager* p_effectMng{}; //�G�t�F�N�g�Ǘ�.

public:
	//set.
	void SetIsSpawnAble(bool _flag) { isSpawnAble = _flag; }

	void Init();
	void Reset();
	void Update();
	void Draw();

	void SpawnMeteor(); //覐ΐ���.

	bool IsHitMeteors(Circle cir, bool isDestroy); //覐΂̂ǂꂩ1�ł��������Ă��邩.
	bool GetMeteorPosNearest(DBL_XY _startPos, DBL_XY* _nearPos); //�Ŋ���覐΍��W��T��.
};