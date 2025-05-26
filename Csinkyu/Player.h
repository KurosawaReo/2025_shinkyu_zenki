/*
   - Player.h -
   �v���C���[�Ǘ�.
*/
#pragma once

//extern POINT Get(int x, int y);//X�n�_��Y�n�_����POINT�^���ꎞ�I�Ɏ擾.
//extern BOOL  CollPointToPoint(POINT a, POINT b);//�_�Ɠ_�����������Ă��邩.
//extern RECT  GetRect(int left, int top, int right, int bottom);
//extern int   PlayerX, PlayerY, PlayerGraph;

class Player
{
private:
	int    graph{};     //�摜�f�[�^.
	BOOL   active{};    //�L����.
	Circle hit{};       //�v���C���[�̓����蔻��~.
	BOOL   isDebug{};   //�f�o�b�O�p.
	
	GameData* p_data{}; //�Q�[���f�[�^.

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

	void PlayerMove();  //�v���C���[�ړ�.
	void PlayerDeath(); //�v���C���[���S.
};