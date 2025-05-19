/*
   - GameManager.h -
   �Q�[���S�̊Ǘ�.
*/
#pragma once

class GameManager 
{
private:
	clock_t stTime;
	clock_t nowTime;

	Scene scene; //�V�[���̋L�^�p.

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