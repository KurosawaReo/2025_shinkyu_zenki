/*
   - Player.h -
   �v���C���[�Ǘ�.
*/
#pragma once

extern POINT Get(int x, int y);//X�n�_��Y�n�_����POINT�^���ꎞ�I�Ɏ擾.
extern BOOL CollPointToPoint(POINT a, POINT b);//�_�Ɠ_�����������Ă��邩.
extern RECT GetRect(int left, int top, int right, int bottom);
extern int PlayerX, PlayerY, PlayerGraph;
class Player
{
public:
	void Init();
	void Update();
	void Draw();

	// �ǉ��F�v���C���[�̈ʒu���擾���郁�\�b�h
	int GetX() { return PlayerX; }
	int GetY() { return PlayerY; }
};