/*---------------------------------------------------------------------/
   - stdafx.h -

   �v���R���p�C���ς݃w�b�_�[�Ƃ��Ďg�������.
   �r���h���Ԃ�Z�k���邱�Ƃ��ړI.
   �S�Ă�cpp�t�@�C���ŁA�ŏ��ɂ��̃w�b�_��include����K�v������.

   �蓮�œ����̂��ʓ|�Ȃ�A������������@�Ƃ���
   �v���W�F�N�g > �v���p�e�B > [C/C++] > [�ڍאݒ�] ��
   �K���g�p�����include�t�@�C����ݒ�ł��鏊������.
/----------------------------------------------------------------------/
   [�g����]
   �����Ɏ��O�ɓǂݍ��݂����w�b�_������.
   ����̂��̂ł������A���g�����܂�ύX����Ȃ����̂���������.
   (�p�ɂɕς�����̂�����ƁA�t�Ƀr���h���x���Ȃ�)

   <cstdio>�Ȃǂ̕W�����C�u�����͂����ɓ����
   ����cpp�t�@�C������A����stdafx.h��ʂ��ă��C�u�����𓱓����闬��.

   �Q�l
   https://www.isus.jp/products/c-compilers/stdafxh/
/---------------------------------------------------------------------*/
#pragma once

//�G���[���p.
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#include <cstdio>
#include <cstring>

#include "KR_Lib/KR_Global.h"
#include "KR_Lib/KR_Calc.h"
#include "KR_Lib/KR_Draw.h"
#include "KR_Lib/KR_File.h"
#include "KR_Lib/KR_Input.h"
#include "KR_Lib/KR_Object.h"
#include "KR_Lib/KR_Sound.h"
#include "KR_Lib/KR_Timer.h"

#include "Global.h"