/*
   - LaserManager.h -
   ���XObstacle4main�Ƃ��Ă܂Ƃ߂��Ă����[�U�[.
*/
#pragma once
#include "MeteoManager.h"
#include "EffectManager.h"

//���[�U�[�^�C�v.
enum LaserType
{
	Laser_Normal,       //�ʏ탌�[�U�[.
	Laser_Straight,     //�������[�U�[.
	Laser_Reflect,      //���˃��[�U�[.
	Laser_SuperReflect, //���˃��[�U�[������.
};

//���[�U�[�{�̃f�[�^.
typedef struct tagLASER_DATA
{
	LaserType type;      //���[�U�[�^�C�v.

	double    x,  y;     //���݂̍��W.
	double    bx, by;    //�O��`�悵�����ɂ������W.
	double    vx, vy;    //�i�s�����x�N�g��.

	DBL_XY    goalPos;   //�ڕW�n�_�̍��W.
	BOOL      isGoGoal;  //�ڕW�n�_�Ɍ������Đi�ނ�.

	int       LogNum;    //�L�^�����O�Ղ̐�.
	float     Counter;   //�ǔ������߂Ă���ʉ߂�������.

	int       ValidFlag; //���̃f�[�^���g�p�����t���O.

}LASER_DATA, *LPLASER_DATA;

//���[�U�[���`���O�����C���f�[�^.
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
	LASER_DATA laser[LASER_CNT_MAX]{};      //�z�[�~���O���[�U�[�̃f�[�^.
	LINE_DATA  line [LASER_LINE_CNT_MAX]{}; //���C���`��p�f�[�^.

	DBL_XY plyPos{}; //�v���C���[���W�ۊǗp.

	GameData*      p_data{};
	Player*        p_player{};
	MeteoManager*  p_meteoMng{};
	EffectManager* p_effectMng{};

public:
	void Init(GameData*, Player*, MeteoManager*, EffectManager*);
	void Reset();
	void Update();
	void Draw();

	void UpdateLaser();                                            //�e���[�U�[�̍X�V.
	void UpdateLaserLine();                                        //�e���[�U�[�`����̍X�V.
	
	BOOL SpawnLaser      (DBL_XY pos, DBL_XY vel, LaserType type); //����.
	void DeleteLaser     (int idx);                                //����.
	void ReflectLaser    (int idx);               	               //����.

//  void LaserNorTracking(int idx);                                //���[�U�[(normal)   ��覐Βǔ�.
	void LaserRefTracking(int idx);                                //���[�U�[(reflected)��覐Βǔ�.
	void LaserReflectRange(Circle* cir);						   //���[�U�[�̈ꊇ����.
};