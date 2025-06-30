/*
   - Obstacle4main.h -

   ���[�U�[�̌p�����N���X.
*/
#pragma once
#include "Player.h"

#define ODAZIMA_LASER //��`���遨�V����ver / �R�����g�A�E�g���遨��ver�̏C����.

//���[�U�[�^�C�v.
enum LaserType
{
	Laser_Normal,    //�ʏ탌�[�U�[.
	Laser_Reflected, //���˃��[�U�[.
};

//���[�U�[�{��.
typedef struct tagLASER_DATA
{
	double    x, y;      //���݂̉摜.
	double    sx, sy;    //���݂̑��x.

	int       LogNum;    //�L�^�����O�Ղ̐�.
	float     Counter;   //�ǔ������߂Ă���ʉ߂�������.

	int       ValidFlag; //���̃f�[�^���g�p�����t���O.

	LaserType type;      //���[�U�[�^�C�v.

}LASER_DATA, * LPLASER_DATA;

//���[�U�[���`���O�����C��.
typedef struct tagLINE_DATA
{
	double x1, y1, x2, y2;  //�`�����C���̍��W.
	float  Counter;         //�`�����C���̐F����p�l.

	int    ValidFlag;       //���̃f�[�^���g�p�����t���O
}LINE_DATA, * LPLINE_DATA;

typedef struct tagFLASHEFFECT
{
	double x, y;    // �G�t�F�N�g�ʒu.
	float Counter;  // �o�ߎ���.
	float Duration; // �G�t�F�N�g�̎�������.
	int BaseSize;   // ��{�T�C�Y
	int ValidFlag; // �L���t���O
};

//�p�����ƂȂ�N���X(�e)
class Obstacle4main
{
protected:
	float Hx{}, Hy{};  //�C��̈ʒu.
	float Hm{};        //�C��̈ړ�����.
	float Hsc{};       //�C��̃V���b�g�Ԋu�J�E���^.
	float HscTm{};     //�C�䂪�V���b�g���鎞��.
	MoveDir moveDir{}; // ���݂̈ړ�����.

	LASER_DATA laser[OBSTACLE4_LASER_LIM]{}; //�z�[�~���O���[�U�[�̃f�[�^.
	LINE_DATA  line [OBSTACLE4_LINE_MAX]{};  //���C���`��p�f�[�^.
	IMG        img{};
	tagFLASHEFFECT flashEffect[OBSTACLE4_FLASH_MAX]; // �N���X�̃����o�ϐ��Ƃ��Ēǉ�

	GameData*  data{};
	Player*    player{};

public:
	//��{����.
	virtual void Init  (GameData*, Player*) = 0;
	virtual void Reset (float _Hx, float _Hy, float _Hm, MoveDir) = 0;
	        void Update();
	        void Draw  ();
	//�`��n.
			void DrawObstLine();
			void DrawObstFlash();
	//�ړ��n.
	        void enemy4Move();
	virtual void Move() = 0;

	//�o�钼�O�̓_��.
	void CreateFlashEffect(double x, double y);

	//���ˏ���.
	void ReflectLaser(int laserIndex, DBL_XY playerPos);
};
