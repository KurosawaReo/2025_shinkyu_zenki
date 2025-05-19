/*
   - GameManager.h -
   �Q�[���S�̊Ǘ�.
*/
#pragma once

//�Q�[���}�l�[�W���[.
class GameManager 
{
private:
	clock_t  stTime;
	clock_t  nowTime;

	GameData data{}; //�Q�[���f�[�^.

public:

	//get.
	float GetTime();

	//���̑�.
	void Init();
	void Reset();
	void Update();
	void Draw();

	void UpdateTitle();
	void UpdateGame();
	void UpdateEnd();

	void DrawTitle();
	void DrawGame();
	void DrawEnd();
	void DrawObjests();
};