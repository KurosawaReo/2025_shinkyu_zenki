/*
   - Player.h -
   �v���C���[�Ǘ�.
*/
#pragma once
#include "EffectManager.h"

class GameData; //�O���錾.

//�_�b�V���G�t�F�N�g.
struct ReflectEffect
{
	DBL_XY pos;           // �G�t�F�N�g�ʒu
	float  scale;         // �X�P�[��
	float  alpha;         // �����x
	int    timer;         // �\������
	bool   active;        // �L���t���O
};

//�c���f�[�^.
struct AfterEffect
{
	DBL_XY pos;
	bool   isActive;
};

//�v���C���[���[�h.
enum PlayerMode
{
	Player_Normal,
	Player_Reflect,     //���˃��[�h.
	Player_SuperReflect //���˃��[�h������.
};

//�v���C���[.[�p���s��]
class Player final
{
//�����̊֌W.
public:
	//���̎擾�p.
	static Player& GetInst() {
		static Player inst; //���g�̃C���X�^���X.
		return inst;
	}
	//�g�p�֎~.
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
private:
	//constructor(�V�K�쐬���ł��Ȃ�����)
	Player(){}

//���f�[�^.
private:
	PlayerMode  mode{};     //���[�h.
	
	Circle      hit{};      //�v���C���[�̓����蔻��~.
	bool        active{};   //�L����.
	bool        isDebug{};  //�f�o�b�O�p.

	float       afterCntr{};	 		     //�c���p���ԃJ�E���^�[.
	AfterEffect after[PLAYER_AFT_IMG_NUM]{}; //�c���ʒu�̗���.

	DrawImg     imgPlayer[2]{}; //�v���C���[�摜.
	double      imgRot{};       //�v���C���[�̉摜�p�x.

	bool        isMoveAble{};   //�ړ��\���ǂ���.

	GameData*      p_data{};      //�Q�[���f�[�^.
	EffectManager* p_effectMng{}; //�G�t�F�N�g�Ǘ�.
	InputMng*      p_input{};     //���͋@�\.

	//�G�t�F�N�g�p(���g�p)
	ReflectEffect reflectEffects[PLAYER_MAX_EFFECT]{}; // �G�t�F�N�g�z��
	int reflectEffectIndex{};                          // ���Ɏg�p����G�t�F�N�g�̃C���f�b�N�X

public:
	//set.
	void       SetPos       (DBL_XY     _pos)    { hit.pos    = _pos;    }
	void       SetActive    (bool       _active) { active     = _active; }
	void       SetMode      (PlayerMode _mode)   { mode       = _mode;   } //���[�h�ݒ�.
	void       SetIsMoveAble(bool       _flag)   { isMoveAble = _flag;   }
	//get. 
	DBL_XY     GetPos()     const { return hit.pos; }
	bool       GetActive()  const { return active; }
	PlayerMode GetMode()    const { return mode; }
	Circle     GetHit()     const { return hit; }
	//�v��.
	double     GetMoveDist() const { 
		return Calc::CalcDist(hit.pos, after[1].pos); //�ړ���������.
	}

	//���̑�.
	void Init  ();
	void Reset (DBL_XY _pos, bool _active);
	void Update();
	void Draw  ();

	void PlayerMove();       //�v���C���[�ړ�.
	void PlayerDeath();      //�v���C���[���S.
	void PlayerRevival();    //�v���C���[����.

	void UpdateAfterImage(); //�c���X�V.
	void DrawAfterImage();   //�c���`��.

	//�G�t�F�N�g�p(���g�p)
	void CreateReflectEffect(DBL_XY pos);
	void UpdateReflectEffects();
	void DrawReflectEffects();
};