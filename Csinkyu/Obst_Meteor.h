/*
   - Obst_Meteor.h -
   
   ��Q��: 覐�.
*/
#pragma once
#include "Player.h"

class GameData; //�O���錾.

//覐΂̏��.
enum MeteorState
{
	Meteor_Normal,
	Meteor_Destroy, //�j�󃂁[�h.
};

//覐΂̌`�f�[�^.
struct MeteorShape
{
	int   lineCnt{};					 //覐΂����p�`�ɂ��邩.
	float lineDis[METEOR_LINE_CNT_MAX]{}; //覐΂̒��S����̒��_�̋���.
	Line  line   [METEOR_LINE_CNT_MAX]{}; //覐΂��\�������. 
};

//覐�(�P��)
class Meteor
{
private:
	MeteorState state{};      //覐΂̏��.
	MeteorShape shape{};      //覐΂̌`�f�[�^.

	DBL_XY     pos{};	      //���S���W.
	float      ang{};	      //�p�x.
	DBL_XY     vel{};         //���x.
	bool       active{};      //�L�����ǂ���.

	float      destroyCntr{}; //�j��ʂ̓x��.

	GameData*  p_data;        //�Q�[���f�[�^.

public:
	//set.
	void SetActive(bool _active) { 
		active = _active; 
	}
	//get.
	DBL_XY      GetPos()    { return pos; }
	bool        GetActive() { return active; }
	MeteorState GetState()  { return state; }

	//���̑�.
	void Init();
	void Reset();
	void Update();
	void Draw();

	void Spawn();				//覐Ώo��. 
	void Destroy();				//覐Δj��.
	bool IsHitMeteor(Circle*);	//覐΂̓����蔻��.

	void UpdateMeteoLine();		//覐΂��\��������̍X�V.
};