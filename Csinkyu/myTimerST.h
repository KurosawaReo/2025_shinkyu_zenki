/*
   - myTimerST.h - (original)
   ver.2025/08/03

   DxLib: �I���W�i���^�C�}�[�@�\�̒ǉ�.
*/
#pragma once

//�^�C�}�[���[�h.
enum TimerMode
{
	COUNT_UP,
	COUNT_DOWN,
};
//�^�C�}�[�@�\.
class Timer
{
private:
	TimerMode mode{};       //�v�����[�h.
	bool      isMove{};     //�v������.

	float     tmInit{};     //init : ��������.
	clock_t   tmStart{};    //start: �J�n����.

	float     tmSavePass{}; //�����ۑ��p(Stop���Start������ĊJ�ł���悤��)

public:
	//�R���X�g���N�^.
	Timer(TimerMode _mode, float _init) :
		mode(_mode), tmInit(_init), tmSavePass(_init) //�������q.
	{}

	void Start() {
		tmStart = clock(); //�J�n�����̎擾.
		isMove = true;     //�v����.
	}
	void Stop();
	void Reset() {
		tmStart = 0;
		tmSavePass = tmInit; //��������.
		isMove = false;
	}
	bool GetIsMove() {
		return isMove;
	}

	float GetPassTime(); //���Ԏ擾.
};
//�^�C�}�[�@�\(�}�C�N���b)
class TimerMicro
{
private:
	TimerMode     mode{};       //�v�����[�h.
	bool          isMove{};     //�v������.

	LONGLONG      tmInit{};     //init     : ��������(�}�C�N���b)
	LARGE_INTEGER tmStart{};    //start    : �J�n����(�J�E���g)
	LARGE_INTEGER freq{};       //frequency: 1�b�ŉ��J�E���g�i�ނ�.

	LONGLONG      tmSavePass{}; //�����ۑ��p(Stop���Start������ĊJ�ł���悤��)

public:
	//�R���X�g���N�^.
	TimerMicro(TimerMode _mode, LONGLONG _init) :
		mode(_mode), tmInit(_init), tmSavePass(_init) //�������q.
	{
		Init();
	}

	void Init() {
		QueryPerformanceFrequency(&freq); //�p�x�̎擾.
	}
	void Start() {
		QueryPerformanceCounter(&tmStart); //�J�n�����̎擾.
		isMove = true; //�v����.
	}
	void Stop();
	void Reset() {
		tmStart.QuadPart = 0;
		tmSavePass = tmInit; //��������.
		isMove = false;
	}
	bool GetIsMove() {
		return isMove;
	}

	LONGLONG GetPassTime (); //���Ԏ擾.
	bool     IntervalTime(); //��莞�Ԃ��Ƃ�true��Ԃ�.
};