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
	void UpdateGame();
	void UpdateEnd();

	//Draw.
	void DrawTitle();
	void DrawGame();
	void DrawEnd();

	void DrawBG();
	void DrawObjects();
	void DrawSlowMode();

	//���̑�.
	void GameEnd();
	void TakeItem();
};