/*
   - Player.h -
   �v���C���[�Ǘ�.
*/
#pragma once
#include "EffectManager.h"

class GameData; //�O���錾.

//�G�t�F�N�g�f�[�^.
struct AfterEffect
{
	DBL_XY pos;
	double ang;
	bool   isDash;   //�_�b�V���G�t�F�N�g�ɂ��邩.
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
	PlayerMode     mode{};     //���[�h.
	
	Circle         hit{};      //�v���C���[�̓����蔻��~.
	bool           active{};   //�L����.
	bool           isDebug{};  //�f�o�b�O�p.

	//�c��.
	float          afterCntr{};	 		        //�c���p���ԃJ�E���^�[.
	AfterEffect    after[PLAYER_AFT_IMG_NUM]{}; //�c���ʒu�̗���.

	//�_�b�V��.
	bool           isDashing;        // �_�b�V�������ǂ���.
	float          dashTimer;        // �_�b�V���̎c�莞��.
	float          dashCooldown;     // �_�b�V���̃N�[���_�E��.

	DrawImg        imgPlayer[2]{};      //�v���C���[�摜.
	DrawImg        imgPlayerLight[2]{}; //�v���C���[�̌���摜.
	double         imgRot{};            //�v���C���[�̉摜�p�x.

	bool           isMoveAble{};     //�ړ��\���ǂ���.

	GameData*      p_data{};      //�Q�[���f�[�^.
	EffectManager* p_effectMng{}; //�G�t�F�N�g�Ǘ�.
	InputMng*      p_input{};     //���͋@�\.

public:
	//set.
	void       SetPos       (DBL_XY     _pos)    { hit.pos    = _pos;    }
	void       SetActive    (bool       _active) { active     = _active; }
	void       SetMode      (PlayerMode _mode)   { mode       = _mode;   } //���[�h�ݒ�.
	void       SetIsMoveAble(bool       _flag)   { isMoveAble = _flag;   }
	//get. 
	DBL_XY     GetPos()      const { return hit.pos; }
	bool       GetActive()   const { return active; }
	PlayerMode GetMode()     const { return mode; }
	Circle     GetHit()      const { return hit; }
	//�v��.
	double     GetMoveDist() const { 
		return Calc::CalcDist(hit.pos, after[1].pos); //�ړ���������.
	}

	//���̑�.
	void Init  ();
	void Reset (DBL_XY _pos, bool _active);
	void Update();
	void Draw  ();

	void UpdateDash();       //�_�b�V���X�V.

	void PlayerMove();       //�v���C���[�ړ�.
	void PlayerDeath();      //�v���C���[���S.
	void PlayerRevival();    //�v���C���[����.

	void UpdateAfterImage(); //�c���X�V.
	void DrawAfterImage();   //�c���`��.
};