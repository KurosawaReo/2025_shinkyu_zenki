/*
   - GameManager.h -
   �Q�[���S�̊Ǘ�.
*/
#pragma once

//�Q�[���}�l�[�W���[.
class GameManager 
{
private: //����.
	static GameManager self; //���g�̎���.

private: //�f�[�^.
	GameData data{}; //�Q�[���f�[�^.

	Timer tmTitle    = Timer(CountUp,   0);              //�^�C�g���p�^�C�}�[.
	Timer tmReady    = Timer(CountUp,   0);              //�J�n�p�^�C�}�[.
	Timer tmGame     = Timer(CountUp,   0);              //�Q�[������.
	Timer tmSlowMode = Timer(CountDown, SLOW_MODE_TIME); //�X���[�p������.

public:
	//���̂̎擾.
	static GameManager* GetPtr() {
		return &self;
	}

	//���C������.
	void Init();
	void Reset();
	void Update();
	void Draw();

	//Update.
	void UpdateTitle();
	void UpdateReady();
	void UpdateGame();
	void UpdateEnd();

	void UpdateObjects();

	//Draw.
	void DrawTitle();
	void DrawReady();
	void DrawGame();
	void DrawEnd();

	void DrawBG();
	void DrawUI();
	void DrawObjects();
	void DrawSlowMode();

	//���̑�.
	void GameEnd();
	void TakeItem();
};