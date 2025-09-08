#pragma once
#include "Global.h"
#include "LaserManager.h"

class Player;
// �ԉ΂̏��
enum FireworksState {
	FIREWORKS_STATE_WARNING,    // �\�����
	FIREWORKS_STATE_EXPLODING,  // ������
	FIREWORKS_STATE_FALLING     // ������
};

// �ԉ΃f�[�^�\��
struct FireworksData {
	int ValidFlag;              // �L���t���O
	float x, y;                 // ���W
	float targetX, targetY;     // �ڕW���W�i�����ʒu�j
	float vx, vy;              // ���x
	float Counter;             // �J�E���^
	float Duration;            // ��������
	FireworksState state;      // ���݂̏��
	int sparkCount;            // �ΉԐ�

	int fallDelay;   // �����܂ł̒x��
	bool hasFallen;  // �����ς݂�
};

class FireworksObstacle {
private:
	GameData* p_data;
	Player* p_player;
	LaserManager* p_laserMng;
	FireworksData fireworks[FIREWORKS_MAX];
	float spawnTimer;

	// �v���C�x�[�g�֐�
	void GenerateRandomPosition(float& x, float& y);
	bool CheckDistance(float x, float y);
	void StartFireworks(float x, float y);
	void UpdateFireworksGeneration();
	void UpdateIndividualFireworks();
	void ExplodeFireworks(int index);
	void CreateFireworksSparks(float x, float y);

	// �`��֐�
	void DrawWarningEffect(int index);

public:
	void Init(GameData* data, Player* player, LaserManager* laserMng);
	void Reset();
	void Update();
	void Draw();
};