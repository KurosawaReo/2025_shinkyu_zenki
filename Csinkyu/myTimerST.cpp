/*
   - myTimerST.cpp - (original)
   ver.2025/06/17

   DxLib�Ŏg���p�̃I���W�i�����Ԋ֐�.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx���Ȃ���΂����Œ�`.
#endif

#include "myTimerST.h"

//�o�ߎ��Ԏ擾.
float Timer::GetPassTime() {

	//�I�������̃Z�b�g.
	if (isMove) { tmEnd = clock(); }
	//���ԍ�.
	float ret = 0;

	switch (mode)
	{
		case CountUp:
			ret = tmInit + (float)(tmEnd - tmStart)/1000; //�^�C�}�[����.
			break;
		case CountDown:
			ret = tmInit - (float)(tmEnd - tmStart)/1000; //�^�C�}�[����.
			ret = max(ret, 0); //������0�b.
			break;

		default: assert(FALSE); break;
	}

	return ret; //���Ԃ�Ԃ�.
}

//�o�ߎ��Ԏ擾(�}�C�N���b)
LONGLONG TimerMicro::GetPassTime() {

	//�I�������̃Z�b�g.
	if (isMove) { QueryPerformanceCounter(&tmEnd); }
	//���ԍ�.
	LONGLONG ret = 0;

	switch (mode)
	{
		case CountUp:
			ret = tmInit + tmEnd.QuadPart - tmStart.QuadPart; //�^�C�}�[����.
			break;
		case CountDown:
			ret = tmInit - tmEnd.QuadPart - tmStart.QuadPart; //�^�C�}�[����.
			ret = max(ret, 0); //������0�ʕb.
			break;

		default: assert(FALSE); break;
	}

	ret *= 1000000;
	ret /= freq.QuadPart;

	return ret; //���Ԃ�Ԃ�.
}