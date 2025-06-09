/*
   - myTimerST.h - (original)
   ver.2025/06/02

   DxLib�Ŏg���p�̃I���W�i�����Ԋ֐�.
*/
#pragma once

//�^�C�}�[���[�h.
enum TimerMode
{
	CountUp,
	CountDown,
};
//�^�C�}�[�@�\.
class Timer
{
private:
	float     initTime{}; //��������.
	clock_t   stTime{};   //�v���J�n����.
	clock_t   edTime{};   //�v���I������.

	BOOL      isMove{};   //�v������.
	TimerMode mode{};     //�v�����[�h.

public:
	//�R���X�g���N�^.
	Timer(float _init, TimerMode _mode) : 
		initTime(_init), mode(_mode) //�������q.
	{}

	void StartTimer() {
		stTime = clock(); //�^�C�}�[�J�n.
		edTime = 0;
		isMove = TRUE;    //�v����.
	}
	void StopTimer() {
		if (isMove) {
			edTime = clock(); //�^�C�}�[�I��.
			isMove = FALSE;   //��~.
		}
	}

	float GetTime(); //���Ԏ擾.
};