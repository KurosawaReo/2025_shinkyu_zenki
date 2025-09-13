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
	bool   active;        // �L���t���O
};

//�v���C���[���[�h.
enum PlayerMode
{
	Player_Normal,
	Player_Reflect,     //���˃��[�h.
	Player_SuperReflect //���˃��[�h������.
};

class Player
{
private:
	PlayerMode mode{}; //���[�h.
	
	Circle hit{};      //�v���C���[�̓����蔻��~.
	bool   active{};   //�L����.
	bool   isDebug{};  //�f�o�b�O�p.

	float  afterCntr{};					   //�c���p���ԃJ�E���^�[.
	DBL_XY afterPos[PLAYER_AFT_IMG_NUM]{}; //�c���ʒu�̗���.

	DrawImg imgPlayer[2]{}; //�v���C���[�摜.
	double  imgRot{};       //�v���C���[�̉摜�p�x.

	GameData*      p_data{};      //�Q�[���f�[�^.
	EffectManager* p_effectMng{}; //�G�t�F�N�g�Ǘ�.
	InputMng*      p_input{};     //���͋@�\.

public:

	//???
	static const int MAX_REFLECT_EFFECTS = 5;  // �ő�G�t�F�N�g��
	ReflectEffect reflectEffects[MAX_REFLECT_EFFECTS]{};  // �G�t�F�N�g�z��
	int reflectEffectIndex{};  // ���Ɏg�p����G�t�F�N�g�̃C���f�b�N�X

	//set.
	void       SetActive(bool _active)     { active = _active; }
	void       SetMode  (PlayerMode _mode) { mode   = _mode;   } //���[�h�ݒ�.
	//get. 
	DBL_XY     GetPos()   { return hit.pos; }
	bool       GetActive(){ return active; }
	PlayerMode GetMode()  { return mode; }
	Circle*    GetHit()   { return &hit; }


	//���̑�.
	void Init  (GameData*, EffectManager*);
	void Reset (DBL_XY _pos, bool _active);
	void Update();
	void Draw  ();

	void PlayerMove();       //�v���C���[�ړ�.
	void PlayerDeath();      //�v���C���[���S.

	void UpdateAfterImage(); //�c���X�V.
	void DrawAfterImage();   //�c���`��.

	void CreateReflectEffect(DBL_XY pos);
	void UpdateReflectEffects();
	void DrawReflectEffects();
};