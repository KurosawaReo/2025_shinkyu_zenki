/*
   - myTimerST.h - (original)
   ver.2025/05/26

   DxLib�Ŏg���p�̃I���W�i�����Ԋ֐�.
*/
#pragma once

//�^�C�}�[�@�\.
class Timer
{
private:
	clock_t stTime; //�J�n����.
	clock_t edTime; //�I������.
	BOOL    isMove; //�v������.

public:
	void StartTimer() {
		stTime = clock(); //�^�C�}�[�J�n.
		edTime = 0;
		isMove = TRUE;    //������.
	}
	void StopTimer() {
		edTime = clock(); //�^�C�}�[�I��.
		isMove = FALSE;   //��~����.
	}
	BOOL GetIsMove() {
		return isMove;
	}
	float GetTime() {
		if (!isMove) {
			return (float)(edTime - stTime)/1000; //���ԍ���Ԃ�.
		}
		else {
			return (float)(clock() - stTime)/1000; //���ԍ���Ԃ�.
		}
	}
};