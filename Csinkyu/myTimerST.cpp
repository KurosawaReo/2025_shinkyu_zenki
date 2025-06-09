/*
   - myTimerST.cpp - (original)
   ver.2025/06/09

   DxLib�Ŏg���p�̃I���W�i�����Ԋ֐�.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx���Ȃ���΂����Œ�`.
#endif

#include "myTimerST.h"

//���Ԏ擾.
float Timer::GetTime() {

	//�I���̎���.
	clock_t ed = (isMove) ? clock() : edTime;
	//���ԍ�.
	float ret = 0;

	switch (mode)
	{
		case CountUp:   
			ret = initTime + (float)(ed - stTime)/1000; //�^�C�}�[����.
			break;
		case CountDown: 
			ret = initTime - (float)(ed - stTime)/1000; //�^�C�}�[����.
			ret = max(ret, 0); //������0�b.
			break;

		default: assert(FALSE); break;
	}

	return ret; //���Ԃ�Ԃ�.
}