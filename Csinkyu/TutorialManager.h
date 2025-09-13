/*
   - TutorialManager.h -
   チュートリアルシーン.
*/
#pragma once

class TutorialManager 
{
private:
	int stepNo; //現在のステップ番号.

public:
	void Init();
	void Reset();
	void Update();
	void Draw();

	void UpdateStep1();
	void UpdateStep2();
	void UpdateStep3();
	void UpdateStep4();

	void DrawStep1();
	void DrawStep2();
	void DrawStep3();
	void DrawStep4();
};