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

public:
	//get.
	float GetTime();

	//���̑�.
	void Init();
	void Update();
	void Draw();
};