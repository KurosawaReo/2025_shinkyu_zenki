/*
   - GameManager.h -
   ƒQ[ƒ€‘S‘ÌŠÇ—.
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

	//‚»‚Ì‘¼.
	void Init();
	void Update();
	void Draw();
};