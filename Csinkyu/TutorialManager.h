/*
   - TutorialManager.h -
   �`���[�g���A���V�[��.
*/
#pragma once

class TutorialManager 
{
private:
	int stepNo; //���݂̃X�e�b�v�ԍ�.

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