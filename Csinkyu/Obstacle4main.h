/*
   - Obstacle4main.h -
   ��Q���Ǘ�.
*/
#pragma once
#include "Player.h"

//#define MAX_L 100 //�~�T�C������ԍő勗��.
//#define PI 3.14159//�~����.
//#define LINE_MAXNUM 3000//�`�悷����̍ő吔.

typedef struct tagLASER_DATA
{
	double x, y;      //���݂̉摜.
	double sx, sy;    //���݂̑��x.

	int    LogNum;    //�L�^�����O�Ղ̐�.
	float  Counter;   //�ǔ������߂Ă���ʉ߂�������.

	int    ValidFlag; //���̃f�[�^���g�p�����t���O.

}LASER_DATA, * LPLASER_DATA;

typedef struct tagLINE_DATA
{
	double x1, y1, x2, y2;  //�`�����C���̍��W.
	float  Counter;         //�`�����C���̐F����p�l.

	int    ValidFlag;       //���̃f�[�^���g�p�����t���O.

}LINE_DATA, * LPLINE_DATA;

class Obstacle4main
{
protected:
	float Hx{}, Hy{};  //�C��̈ʒu.
	float Hm{};        //�C��̈ړ�����.
	float Hsc{};       //�C��̃V���b�g�Ԋu�J�E���^.
	float HscTm{};     //�C�䂪�V���b�g���鎞��.

	LASER_DATA ld[OBSTACLE4_LASER_LIM]{};      //�z�[�~���O���[�U�[�̃f�[�^.
	LINE_DATA  line[OBSTACLE4_LASER_LINE_MAX]{}; //���C���`��p�f�[�^.
	IMG        img{};
	MoveDir moveDir;  // ���݂̈ړ�����.
	GameData* data{};
	Player* player{};
public:
    void Init(GameData*, Player*);
	virtual void Reset(float _Hx, float _Hy, float _Hm) = 0;
	void Update();
	void Draw();
	void enemy4Move();
	virtual void idou() = 0;
};
