/*
   - Ripples.h -

   ��Q��: �g��.
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

//�g��Ǘ�.[�p���s��]
class Ripples final
{
//�����̊֌W.
public:
	//���̎擾�p.
	static Ripples& GetInst() {
		static Ripples inst; //���g�̃C���X�^���X.
		return inst;
	}
	//�g�p�֎~.
	Ripples(const Ripples&) = delete;
	Ripples& operator=(const Ripples&) = delete;
private:
	//constructor(�V�K�쐬���ł��Ȃ�����)
	Ripples(){}

//���f�[�^.
private:
	FLASHEFFECT5 flashEffect[RIPPLES_FLASH_MAX]{}; // �N���X�̃����o�ϐ��Ƃ��Ēǉ�

	float flashTimer{}; //�o���^�C�}�[.

	GameData* p_data{};
	Player*   p_player{};

public:
	void Init();
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