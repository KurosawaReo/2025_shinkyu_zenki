/*
   - Obst_Fireworks.h -

   ��Q��: �ԉ�.
*/
#pragma once

class GameData; //�O���錾.
class Player;   //�O���錾.

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

//�ԉΊǗ�.[�p���s��]
class FireworksManager final 
{
public: //����.
	static FireworksManager* GetPtr() {
		static FireworksManager inst; //���g�̃C���X�^���X.
		return &inst;
	}

private: //�ϐ�.
	FireworksData fireworks[FIREWORKS_MAX];
	float spawnTimer;

	GameData*     p_data;
	Player*       p_player;
	LaserManager* p_laserMng;

private: //�֐�.
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
	void Init();
	void Reset();
	void Update();
	void Draw();
};