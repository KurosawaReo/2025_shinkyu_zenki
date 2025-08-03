/*
   - myTimerST.cpp - (original)
   ver.2025/08/03

   DxLib: �I���W�i���^�C�}�[�@�\�̒ǉ�.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx���ɓ����ĂȂ���΂����œ���.
#endif
#include "myTimerST.h"

//�^�C�}�[��~.
void Timer::Stop() {

	//�v�����Ȃ�.
	if (isMove) {

		float elapsed = (float)(clock() - tmStart)/1000; //���ԍ�.

		//�o�ߎ��Ԃ��X�V.
		if (mode == COUNT_UP) {
			tmSavePass += elapsed;           //�^�C�}�[����.
		}
		else {
			tmSavePass -= elapsed;           //�^�C�}�[����.
			tmSavePass = max(tmSavePass, 0); //������0�b.
		}
		isMove = false; //��~.
	}
}
//�o�ߎ��Ԏ擾.
float Timer::GetPassTime() {

	//�v�����Ȃ�.
	if (isMove) { 
		float elapsed = (float)(clock() - tmStart)/1000; //���ԍ�.
		float pass = 0; //�o�ߎ���.

		if (mode == COUNT_UP) {
			pass = tmSavePass + elapsed; //�^�C�}�[����.
		}
		else {
			pass = tmSavePass - elapsed; //�^�C�}�[����.
			pass = max(pass, 0);         //������0�b.
		}
		return pass; //���Ōv�Z�������ԍ���Ԃ�.
	}
	else {
		return tmSavePass; //�ۑ����Ԃ�Ԃ�.
	}	
}

void TimerMicro::Stop() {

	if (isMove) {
		
		LARGE_INTEGER tmEnd;
		QueryPerformanceCounter(&tmEnd); //�I�������̎擾.

		//���ԍ�(freq�ŃJ�E���g���}�C�N���b�ɕϊ�����)
		LONGLONG elapsed = (tmEnd.QuadPart - tmStart.QuadPart) * 1000000/freq.QuadPart;

		//�o�ߎ��Ԃ��X�V.
		if (mode == COUNT_UP) {
			tmSavePass += elapsed;           //�^�C�}�[����.
		}
		else {
			tmSavePass -= elapsed;           //�^�C�}�[����.
			tmSavePass = max(tmSavePass, 0); //������0�b.
		}
		isMove = false; //��~.
	}
}
//�o�ߎ��Ԏ擾(�}�C�N���b)
LONGLONG TimerMicro::GetPassTime() {

	//�v�����Ȃ�.
	if (isMove) { 

		LARGE_INTEGER tmEnd;
		QueryPerformanceCounter(&tmEnd); //�I�������̎擾.

		//���ԍ�(freq�ŃJ�E���g���}�C�N���b�ɕϊ�����)
		LONGLONG elapsed = (tmEnd.QuadPart - tmStart.QuadPart) * 1000000/freq.QuadPart;
		//�o�ߎ���.
		LONGLONG pass;

		if (mode == COUNT_UP) {
			pass = tmSavePass + elapsed; //�^�C�}�[����.
		}
		else{
			pass = tmSavePass - elapsed; //�^�C�}�[����.
			pass = max(pass, 0);         //������0�J�E���g.
		}
		return pass; //���Ōv�Z�������ԍ���Ԃ�.
	}
	else {
		return tmSavePass; //�ۑ����Ԃ�Ԃ�.
	}
}
//��莞�Ԃ��Ƃ�true��Ԃ�(CountDown��p)
bool TimerMicro::IntervalTime() {

	//CountDown����Ȃ��ꍇ��false��Ԃ�������.
	if (mode != COUNT_DOWN) {
		return false;
	}

	//�^�C�}�[��0�ɂȂ�܂�.
	if (GetPassTime() > 0) {
		return false; //false��Ԃ�.
	}
	Start();     //���ԃ��Z�b�g.
	return true; //true��Ԃ�.
}