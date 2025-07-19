/*
   - myTimerST.cpp - (original)
   ver.2025/07/19

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
	
	float elapsed = (float)(tmEnd - tmStart)/1000; //���ԍ�.
	float ret;                                     //�o�ߎ���.

	if (mode == CountUp) {
		ret = tmInit + elapsed; //�^�C�}�[����.
	}
	else {
		ret = tmInit - elapsed; //�^�C�}�[����.
		ret = max(ret, 0);      //������0�b.
	}
	return ret;
}

//�o�ߎ��Ԏ擾(�}�C�N���b)
LONGLONG TimerMicro::GetPassTime() {

	//�I�������̃Z�b�g.
	if (isMove) { QueryPerformanceCounter(&tmEnd); }

	//���ԍ�(freq�ŃJ�E���g���}�C�N���b�ɕϊ�����)
	LONGLONG elapsed = (tmEnd.QuadPart - tmStart.QuadPart) * 1000000/freq.QuadPart;
	//�o�ߎ���.
	LONGLONG ret;

	if (mode == CountUp) {
		ret = tmInit + elapsed; //�^�C�}�[����.
	}
	else{
		ret = tmInit - elapsed; //�^�C�}�[����.
		ret = max(ret, 0);      //������0�J�E���g.
	}
	return ret;
}

//��莞�Ԃ��Ƃ�TRUE��Ԃ�(CountDown��p)
BOOL TimerMicro::IntervalTime() {

	//CountDown����Ȃ��ꍇ��FALSE��Ԃ�������.
	if (mode != CountDown) {
		return FALSE;
	}

	//�^�C�}�[��0�ɂȂ�܂�.
	if (GetPassTime() > 0) {
		return FALSE; //FALSE��Ԃ�.
	}
	Start();     //���ԃ��Z�b�g.
	return TRUE; //TRUE��Ԃ�.
}