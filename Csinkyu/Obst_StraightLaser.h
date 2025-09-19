/*
   - Obst_StraightLaser.h -

   ��Q��: �������[�U�[.
*/
#pragma once
//#include "MeteoManager.h"

//�������[�U�[�Ǘ�.[�p���s��]
class StraightLaser final
{
public: //����.
	static StraightLaser* GetPtr() {
		static StraightLaser inst; //���g�̃C���X�^���X.
		return &inst;
	}

private:
//	STRAIGHT_LASER_DATA laser[3]{};
//	STRAIGHT_LINE_DATA line[OBSTACLE6_LINE_MAX]{}; //���[�U�[��LaserManager�ɓ��ꂵ�Ƃ�.

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