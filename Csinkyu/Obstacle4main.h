/*
   - Obstacle4main.h -
   ��Q���Ǘ�.
*/
#pragma once
#include "Player.h"

//���[�U�[�{��.
typedef struct tagLASER_DATA
{
	double x, y;      //���݂̉摜.
	double sx, sy;    //���݂̑��x.

	int    LogNum;    //�L�^�����O�Ղ̐�.
	float  Counter;   //�ǔ������߂Ă���ʉ߂�������.

	int    ValidFlag; //���̃f�[�^���g�p�����t���O.
	BOOL isReflected; //���˗p���[�U�[���ǂ���.

}LASER_DATA, * LPLASER_DATA;

//���[�U�[���`���O�����C��.
typedef struct tagLINE_DATA
{
	double x1, y1, x2, y2;  //�`�����C���̍��W.
	float  Counter;         //�`�����C���̐F����p�l.

	int    ValidFlag;       //���̃f�[�^���g�p�����t���O
}LINE_DATA, * LPLINE_DATA;

//�p�����ƂȂ�N���X(�e)
class Obstacle4main
{
protected:
	float Hx{}, Hy{};  //�C��̈ʒu.
	float Hm{};        //�C��̈ړ�����.
	float Hsc{};       //�C��̃V���b�g�Ԋu�J�E���^.
	float HscTm{};     //�C�䂪�V���b�g���鎞��.
	MoveDir moveDir{};  // ���݂̈ړ�����.

	LASER_DATA laser[OBSTACLE4_LASER_LIM]{}; //�z�[�~���O���[�U�[�̃f�[�^.
	LINE_DATA  line [OBSTACLE4_LINE_MAX]{};  //���C���`��p�f�[�^.
	IMG        img{};

	GameData*  data{};
	Player*    player{};

public:
	//��{����.
	virtual void Init  (GameData*, Player*) = 0;
	virtual void Reset (float _Hx, float _Hy, float _Hm) = 0;
	        void Update();
	        void Draw  ();
	//�ړ��n.
	        void enemy4Move();
	virtual void Move() = 0;

	//���ˏ���.
	BOOL HandleLaserHit(int laserIndex);
	void CreateReflectedLasers(double reflectX, double reflectY, int originalSx, int originalSy);
};
