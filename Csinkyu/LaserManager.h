/*
   - LaserManager.h -
   ���XObstacle4main�Ƃ��Ă܂Ƃ߂��Ă����[�U�[.
*/
#pragma once

#include "MeteoManager.h"

//���[�U�[�^�C�v.
enum LaserType
{
	Laser_Normal,    //�ʏ탌�[�U�[.
	Laser_Reflected, //���˃��[�U�[.
};

//���[�U�[�{��.
typedef struct tagLASER_DATA
{
	LaserType type;      //���[�U�[�^�C�v.

	double    x, y;      //���݂̍��W.
	double    sx, sy;    //���݂̑��x.

	int       LogNum;    //�L�^�����O�Ղ̐�.
	float     Counter;   //�ǔ������߂Ă���ʉ߂�������.

	int       ValidFlag; //���̃f�[�^���g�p�����t���O.

}LASER_DATA, *LPLASER_DATA;

//���[�U�[���`���O�����C��.
typedef struct tagLINE_DATA
{
	LaserType type;         //���[�U�[�^�C�v.

	double x1, y1, x2, y2;  //�`�����C���̍��W.
	float  Counter;         //�`�����C���̐F����p�l.

	int    ValidFlag;       //���̃f�[�^���g�p�����t���O

}LINE_DATA, *LPLINE_DATA;

//���[�U�[�Ǘ��p.
class LaserManager
{
private:
	LASER_DATA laser[OBSTACLE4_LASER_LIM]{}; //�z�[�~���O���[�U�[�̃f�[�^.
	LINE_DATA  line [OBSTACLE4_LINE_MAX]{};  //���C���`��p�f�[�^.

	GameData*     p_data{};
	Player*       p_player{};
	MeteoManager* p_meteoMng{};

public:
	void Init(GameData*, Player*, MeteoManager*);
	void Reset();
	void Update();
	void Draw();

	BOOL SpawnLaser  (float x, float y);	//����.
	void DeleteLaser (int idx);             //����.
	void ReflectLaser(int idx);				//����.
	void ReflectedLaserTracking(int idx);   //���˃��[�U�[��覐Βǔ�.
};