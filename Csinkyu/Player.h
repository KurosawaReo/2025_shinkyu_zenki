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
	DBL_XY pos;   //�ʒu.
	int    graph; //�摜�f�[�^.

public:
	void Init();
	void Update();
	void Draw();
	void PlayerMove(); //�v���C���[�ړ�.

	// �ǉ��F�v���C���[�̈ʒu���擾���郁�\�b�h
	double GetX() { return pos.x; }
	double GetY() { return pos.y; }
};