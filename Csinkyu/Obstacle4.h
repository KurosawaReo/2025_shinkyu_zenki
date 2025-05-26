/*
   - Obstacle3.h -
   ��Q���Ǘ�.
*/
#pragma once
#include "Player.h"

//#define MAX_L 100 //�~�T�C������ԍő勗��.
//#define PI 3.14159//�~����.
//#define LINE_MAXNUM 3000//�`�悷����̍ő吔.

typedef struct TUGLASER
{  
	int   x, y;      //���݂̉摜.
	int   sx, sy;    //���݂̑��x.

	int   LogNum;    //�L�^�����O�Ղ̐�.
	float Counter;   //�ǔ������߂Ă���ʉ߂�������.

	int   ValidFlag; //���̃f�[�^���g�p�����t���O.


}LASER,*LPLASER;

typedef struct TUGLINE
{
	int   x1, y1, x2, y2;  //�`�����C���̍��W.
	float Counter;         //�`�����C���̐F����p�l.

    int   ValidFlag;       //���̃f�[�^���g�p�����t���O.

}LINE,*LPLINE;


class Obstacle4
{
private:
	float Hx, Hy;  //�C��̈ʒu.
	float Hm;      //�C��̈ړ�����.
	float Hsc;     //�C��̃V���b�g�Ԋu�J�E���^.
	float HscTm;   //�C�䂪�V���b�g���鎞��.

	LASER Ld[OBSTACLE4_MAX_L];     //�z�[�~���O���[�U�[�̃f�[�^.
	LINE Line[OBSTACLE4_LINE_MAX]; //���C���`��p�f�[�^.
	IMG img;

	GameData* data{};
	Player*   player{};

public:
	void Init(GameData*, Player*);
	void Reset();
	void Update();
	void Draw();
	void enemy4Move();
};