/*
�ˑR�o�������Q��
*/
#pragma once

typedef struct tagFLASHEFFECT5
{
	double x, y;    // �G�t�F�N�g�ʒu.
	float Counter;  // �o�ߎ���.
	float Duration; // �G�t�F�N�g�̎�������.
	int BaseSize;   // ��{�T�C�Y
	int ValidFlag;  // �L���t���O
	bool AlreadyHit;
}FLASHEFFECT5;

class Obstacle5
{
private:
	FLASHEFFECT5 flashEffect[OBSTACLE5_FLASH_MAX]{}; // �N���X�̃����o�ϐ��Ƃ��Ēǉ�

	float flashTimer{}; //�o���^�C�}�[.

	GameData* p_data{};
	Player*   p_player{};

public:
	void Init(GameData*, Player*);  // �|�C���^�̃|�C���^����C��
	void Reset();
	void Update();
	void Draw();
	void Hitjudgment();
	void UpdateFlashGeneration();
	void DrawObstFlash();
	void StartFlashEffect(double x, double y); // ���̍s��ǉ�

	void GenerateRandomPosition(double& x, double& y);
	bool CheckDistance(double x, double y);
	void SpawnObstaclegroup();
	int  GetEffectState(int index);
	void DrawWarningEffect(int index);
	void DrawActiveEffect(int index);
};