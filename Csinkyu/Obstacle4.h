/*
   - Obstacle3.h -
   ��Q���Ǘ�.
*/
#pragma once
#include "Player.h"
#define MAX_L 100 //�~�T�C������ԍő勗��.
#define PI 3.14159//�~����.
#define LINE_MAXNUM 3000//�`�悷����̍ő吔.

typedef struct TUGLASER
{
	int x, y;   //���݂̉摜.
	int sx, sy; //���݂̑��x.

	int LogNum;  //�L�^�����O�Ղ̐�.
	int Counter; //�ǔ������߂Ă���ʉ߂�������.

	int ValidFlag;//���̃f�[�^���g�p�����t���O.


}LASER,*LPLASER;

typedef struct TUGLINE
{
	int x1, y1, x2, y2;  //�`�����C���̍��W.
	int Counter;         //�`�����C���̐F����p�l.

    int ValidFlag;       //���̃f�[�^���g�p�����t���O.

}LINE,*LPLINE;


class Obstacle4
{
private:
	int Hx, Hy;  //�C��̈ʒu.
	int Hm;      //�C��̈ړ�����.
	int Hsc;     //�C��̃V���b�g�Ԋu�J�E���^.

	LASER Ld[MAX_L];        //�z�[�~���O���[�U�[�̃f�[�^.
	LINE Line[LINE_MAXNUM]; //���C���`��p�f�[�^.
	IMG img;
	Player* player;

public:
	void Init(Player*);
	void Update();
	void Draw();
	void enemy4Move();
};