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
}FLASHEFFECT5;

class Obstacle5
{
private:
	Line  line{};
	float ang{};   //�p�x.
	float len{};   //����.
	float speed{}; //����.

	GameData* data{};
	Player* player{};
	FLASHEFFECT5 flashEffect[OBSTACLE5_FLASH_MAX]{}; // �N���X�̃����o�ϐ��Ƃ��Ēǉ�

public:
	void Init(GameData*, Player*);  // �|�C���^�̃|�C���^����C��
	void Reset(double x, double y, float speed, int direction);
	void Update();
	void Draw();
	void Hitjudgment();
	void UpdateFlashGeneration();
	void DrawObstFlash();
	void StartFlashEffect(double x, double y);  // ���̍s��ǉ�
};