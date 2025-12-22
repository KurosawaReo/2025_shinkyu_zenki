/*
   - BG_Base.h -
*/
#pragma once

//背景ベース.
class BG_Base
{
//▼変数.
protected:
	float counter{}; //時間経過計測用.

//▼関数.
public:
	//get.
	float GetCounter() const { return counter; }

	virtual void Init()   = 0;
	virtual void Update() = 0;
	virtual void Draw()   = 0;

	//ポーズ用.
	virtual void StopAnim()    = 0;
	virtual void RestartAnim() = 0;
};