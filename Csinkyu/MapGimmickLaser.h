/* 
   - MapGimmickLaserManager.h -
   �}�b�v�M�~�b�N�p�̒������[�U�[�Ǘ�.
*/
#pragma once
//#include "MeteoManager.h"

//�}�b�v�M�~�b�N���[�U�[�Ǘ��p.
class MapGimmickLaser
{
private:
//	STRAIGHT_LASER_DATA laser[3]{};
//	STRAIGHT_LINE_DATA line[OBSTACLE6_LINE_MAX]{}; //���[�U�[��LaserManager�ɓ��ꂵ�Ƃ�.

	DBL_XY plyPos{};   // �v���C���[���W�ۊǗp.

	GameData*     p_data{};
	Player*       p_player{};
	LaserManager* p_laserMng{};
	MeteoManager* p_meteoMng{};

	float  laserSpawnTimer{};  // ���[�U�[���˃^�C�}�[.
	float  predictionTimer{};  // �\�����^�C�}�[.
	bool   showPrediction{};   // �\�����\���t���O
	int    nextLaserIndex{};   // ���̔��˂��郌�[�U�[�̃C���f�b�N�X.
	int    currentDirection{}; // ���݂̔��˕���
	int    nextDirection{};    // ���̔��˕���
	double nextCenterPos{};    // ���̃��[�U�[���ˈʒu�i�\�����p�j

public:
	void Init(GameData*, Player*, LaserManager*, MeteoManager*);
	void Reset();
	void Update();
	void Draw();

	void SpawnStraightLaser();   // �������[�U�[����.
	void DrawPredictionLine();
};

//���̃N���X�̎��̂�2�o���΂������ߕs�v.
#if false
#include "Player.h"
#include "MapGimmickLaserManager.h"
class MapGimmickLaser : public MapGimmickLaserManager
{
public:


private:

};
#endif