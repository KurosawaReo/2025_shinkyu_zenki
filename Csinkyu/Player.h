/*
   - Player.h -
   �v���C���[�Ǘ�.
*/
#pragma once
#include "EffectManager.h"

//�_�b�V���G�t�F�N�g.
struct ReflectEffect
{
	DBL_XY pos;           // �G�t�F�N�g�ʒu
	float  scale;         // �X�P�[��
	float  alpha;         // �����x
	int    timer;         // �\������
	BOOL   active;        // �L���t���O
};

class Player
{
private:
	Circle hit{};       //�v���C���[�̓����蔻��~.
	BOOL   isReflect{}; //���˃��[�h���ǂ���.
	BOOL   active{};    //�L����.

	float  afterCntr{};					   //�c���p���ԃJ�E���^�[.
	DBL_XY afterPos[PLAYER_AFT_IMG_NUM]{}; //�c���ʒu�̗���.

	GameData*      p_data{};      //�Q�[���f�[�^.
	EffectManager* p_effectMng{}; //�G�t�F�N�g�Ǘ�.

	BOOL   isDebug{};   //�f�o�b�O�p.

public:

	//set.
	void    SetActive(BOOL _active) { active = _active; }
	//get. 
	DBL_XY  GetPos()   { return hit.pos; }
	BOOL    GetActive(){ return active; }
	Circle* GetHit()   { return &hit; }
	static const int MAX_REFLECT_EFFECTS = 5;  // �ő�G�t�F�N�g��
	ReflectEffect reflectEffects[MAX_REFLECT_EFFECTS]{};  // �G�t�F�N�g�z��
	int reflectEffectIndex{};  // ���Ɏg�p����G�t�F�N�g�̃C���f�b�N�X

	//���̑�.
	void  Init  (GameData*, EffectManager*);
	void  Reset (DBL_XY _pos, BOOL _active);
	void  Update();
	void  Draw  ();

	void  PlayerMove();          //�v���C���[�ړ�.
	void  PlayerDeath();         //�v���C���[���S.

	void  UpdateAfterImage();	 //�c���X�V.
	void  DrawAfterImage();      //�c���`��.

	BOOL  IsReflectionMode() const; //���˃��[�h���ǂ�����Ԃ�.
	void  SetReflectionMode(BOOL);	//���˃��[�h�ݒ�.

	void CreateReflectEffect(DBL_XY pos);
	void UpdateReflectEffects();
	void DrawReflectEffects();
};