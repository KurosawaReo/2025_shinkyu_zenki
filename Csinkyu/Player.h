/*
   - Player.h -
   �v���C���[�Ǘ�.
*/
#pragma once

//�v���C���[���͂��V�[���h.
struct PlayerShield
{
	
};

class Player
{
private:
	Circle hit{};       //�v���C���[�̓����蔻��~.
	BOOL   active{};    //�L����.

	float  afterCntr;					 //�c���p���ԃJ�E���^�[.
	DBL_XY afterPos[PLAYER_AFT_IMG_NUM]; //�c���ʒu�̗���.
	float  reflectionCooldown{};         //���˂̃N�[���_�E������.

	GameData* p_data{}; //�Q�[���f�[�^.

	BOOL   isDebug{};   //�f�o�b�O�p.

public:

	//set.
	void    SetActive(BOOL _active) { active = _active; }
	//get. 
	DBL_XY  GetPos()   { return hit.pos; }
	BOOL    GetActive(){ return active; }
	Circle* GetHit()   { return &hit; }

	//���̑�.
	void  Init  (GameData*);
	void  Reset (DBL_XY _pos, BOOL _active);
	void  Update();
	void  Draw  ();

	void  PlayerMove();          //�v���C���[�ړ�.
	void  PlayerDeath();         //�v���C���[���S.

	void  UpdateAfterImage();	 //�c���X�V.
	void  DrawAfterImage();      //�c���`��.

	BOOL  IsReflectionMode() const;			//���˃��[�h���ǂ�����Ԃ�.
	float GetReflectionCooldown() const;	//�N�[���_�E�����Ԃ�����.
	void  UseReflection();					//���˂��g�p.
};