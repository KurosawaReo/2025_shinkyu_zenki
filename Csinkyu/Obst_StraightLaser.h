/*
   - Obst_StraightLaser.h -

   ��Q��: �������[�U�[.
*/
#pragma once
//#include "MeteoManager.h"

//�������[�U�[.
class StraightLaser
{
private:
	DBL_XY plyPos{};   // �v���C���[���W�ۊǗp.

	GameData*      p_data{};
	Player*        p_player{};
	LaserManager*  p_laserMng{};
	MeteorManager* p_meteorMng{};

	float  laserSpawnTimer{};  // ���[�U�[���˃^�C�}�[.
	float  predictionTimer{};  // �\�����^�C�}�[.
	bool   showPrediction{};   // �\�����\���t���O
	int    nextLaserIndex{};   // ���̔��˂��郌�[�U�[�̃C���f�b�N�X.
	int    currentDirection{}; // ���݂̔��˕���
	int    nextDirection{};    // ���̔��˕���
	double nextCenterPos{};    // ���̃��[�U�[���ˈʒu�i�\�����p�j

public:
	void Init();
	void Reset();
	void Update();
	void Draw();

	void SpawnStraightLaser();   // �������[�U�[����.
	void DrawPredictionLine();
};