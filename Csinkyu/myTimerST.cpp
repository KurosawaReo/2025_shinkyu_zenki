/*
   - myTimerST.cpp - (original)
   ver.2025/06/20

   DxLib: �I���W�i���^�C�}�[�@�\�̒ǉ�.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx���ɓ����ĂȂ���΂����œ���.
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

	//���[�h��.
	if (mode == CountUp) {
		ret = tmInit + tmEnd.QuadPart - tmStart.QuadPart; //�^�C�}�[����.
	}
	else{
		ret = tmInit - tmEnd.QuadPart - tmStart.QuadPart; //�^�C�}�[����.
		ret = max(ret, 0); //������0�ʕb.
	}

	ret *= 1000000;
	ret /= freq.QuadPart;

	return ret; //���Ԃ�Ԃ�.
}

//��莞�Ԃ��Ƃ�TRUE��Ԃ�(CountUp��p)
BOOL TimerMicro::IntervalTime(float sec) {

	//��莞�Ԍo�܂�.
	if (GetPassTime() < 1000000/sec) {
		return FALSE; //FALSE��Ԃ�.
	}
	Start();     //���ԃ��Z�b�g.
	return TRUE; //TRUE��Ԃ�.
}