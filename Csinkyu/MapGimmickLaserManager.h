/* - MapGimmickLaserManager.h -
   �}�b�v�M�~�b�N�p�̒������[�U�[�Ǘ�.
*/
#pragma once
#include "MeteoManager.h"
#include "Global.h"

// �������[�U�[�{��.
 typedef struct tagStraightLASER_DATA
{

	double    x, y;     //���݂̍��W.
	double    vx, vy;    //�i�s�����x�N�g��.

	DBL_XY    goalPos;   //�Ŋ��覐΍��W���L�^����p.
	BOOL      isGoGoal;  //�ڕW�n�_�Ɍ������Đi�ނ�.

	int       LogNum;    //�L�^�����O�Ղ̐�.
	float     Counter;   //�ǔ������߂Ă���ʉ߂�������.

	int       ValidFlag; //���̃f�[�^���g�p�����t���O.

}STRAIGHT_LASER_DATA, * LPSTRAIGHT_LASER_DATA;

 // ���[�U�[���`���O�����C��.
 typedef struct tagStraightLINE_DATA
 {
	 double x1, y1, x2, y2;  // �`�����C���̍��W.
	 float Counter;          // �`�����C���̐F����p�l.
	 int ValidFlag;          // ���̃f�[�^���g�p�����t���O.
 }STRAIGHT_LINE_DATA, * LPSTRAIGHT_LINE_DATA;

 //�}�b�v�M�~�b�N���[�U�[�Ǘ��p.
 class MapGimmickLaserManager
 {
 private:
	 STRAIGHT_LASER_DATA laser[3]{};
	 STRAIGHT_LINE_DATA line[OBSTACLE6_LINE_MAX]{};

	 DBL_XY plyPos{};   // �v���C���[���W�ۊǗp.

	 GameData*     p_data{};
	 Player*       p_player{};
	 MeteoManager* p_meteoMng{};

	 float laserSpawnTimer{};//���[�U�[���˃^�C�}�[.
	 int   nextLaserIndex{}; //���̔��˂��郌�[�U�[�̃C���f�b�N�X.

 public:

	 void Init(GameData*, Player*, MeteoManager*);
	 void Reset();
	 void Update();
	 void Draw();

	 void UpdateLaser();          // �e���[�U�[�̍X�V.
	 void UpdateLaserLine();      // �e���[�U�[�`����̍X�V.
	 void SpawnStraightLaser();   // �������[�U�[����.
	 void DeleteLaser(int idx);   // ����.
 };