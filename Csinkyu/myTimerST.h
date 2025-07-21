/*
   - myTimerST.h - (original)
   ver.2025/07/19

   DxLib: �I���W�i���^�C�}�[�@�\�̒ǉ�.
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
	TimerMode mode{};    //�v�����[�h.
	BOOL      isMove{};  //�v������.

	float     tmInit{};  //init : ��������.
	clock_t   tmStart{}; //start: �J�n����.
	clock_t   tmEnd{};   //end  : �I������.

public:
	//�R���X�g���N�^.
	Timer(TimerMode _mode, float _init) :
		mode(_mode), tmInit(_init) //�������q.
	{}

	void Start() {
		tmStart = clock(); //�J�n�����̎擾.
		isMove = TRUE;     //�v����.
	}
	void Stop() {
		if (isMove) {
			tmEnd = clock(); //�I�������̎擾.
			isMove = FALSE;  //��~.
		}
	}
	void Reset() {
		tmStart = 0;
		tmEnd = 0;
		isMove = FALSE;
	}
	BOOL GetIsMove() {
		return isMove;
	}

	float GetPassTime(); //���Ԏ擾.
};
//�^�C�}�[�@�\(�}�C�N���b)
class TimerMicro
{
private:
	TimerMode     mode{};    //�v�����[�h.
	BOOL          isMove{};  //�v������.

	LONGLONG      tmInit{};  //init     : ��������(�}�C�N���b)
	LARGE_INTEGER tmStart{}; //start    : �J�n����(�J�E���g)
	LARGE_INTEGER tmEnd{};   //end      : �I������(�J�E���g)
	LARGE_INTEGER freq{};    //frequency: 1�b�ŉ��J�E���g�i�ނ�.

public:
	//�R���X�g���N�^.
	TimerMicro(TimerMode _mode, LONGLONG _init) :
		mode(_mode), tmInit(_init) //�������q.
	{
		Init();
	}

	void Init() {
		QueryPerformanceFrequency(&freq); //�p�x�̎擾.
	}
	void Start() {
		QueryPerformanceCounter(&tmStart); //�J�n�����̎擾.
		isMove = TRUE; //�v����.
	}
	void Stop() {
		if (isMove) {
			QueryPerformanceCounter(&tmEnd); //�I�������̎擾.
			isMove = FALSE; //��~.
		}
	}
	void Reset() {
		tmStart.QuadPart = 0;
		tmEnd.QuadPart = 0;
		isMove = FALSE;
	}
	BOOL GetIsMove() {
		return isMove;
	}

	LONGLONG GetPassTime (); //���Ԏ擾.
	BOOL     IntervalTime(); //��莞�Ԃ��Ƃ�TRUE��Ԃ�.
};