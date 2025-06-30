/*
   - Player.h -
   �v���C���[�Ǘ�.
*/
#pragma once


class Player
{
private:
	Circle hit{};       //�v���C���[�̓����蔻��~.
	int    graph{};     //�摜�f�[�^.
	BOOL   active{};    //�L����.
	DBL_XY afterImagePos[AFTIMAGENUM];//�c���ʒu�̗���.
	
	float  reflectionCooldown{}; //���˂̃N�[���_�E������.

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
	void Init  (GameData*);
	void Reset (DBL_XY _pos, BOOL _active);
	void Update();
	void Draw  ();

	void PlayerMove();          //�v���C���[�ړ�.
	void PlayerDeath();         //�v���C���[���S.
	void PlayerFaterimage();        //�v���C���[�c��.
	BOOL IsReflectionMode();    //���˃��[�h���ǂ�����Ԃ�.
	void UseReflection();         //���˂��g�p.
	float GetReflectionCooldown();//�N�[���_�E�����Ԃ�����.
};