/*
   - myInputST.h - (original)

   DxLib�Ŏg���p�̃I���W�i�����͊֐�.
   2025/05/14
*/
#pragma once

#if !defined DEF_INT_XY
#define DEF_INT_XY
//int�^�̋Ïkxy.
struct INT_XY
{
	int x;
	int y;
};
#endif

#if !defined DEF_DBL_XY
#define DEF_DBL_XY
//double�^�̋Ïkxy.
struct DBL_XY
{
	double x;
	double y;
};
#endif

BOOL IsPushMouse  (int num);
BOOL IsPushKey    (int num);
int  IsPushKeyTime(int num);

void InputMove4Dir(DBL_XY* pos, int speed);
void MoveLimPos   (DBL_XY* pos, INT_XY size, int lLim, int uLim, int rLim, int dLim);

void UpdateKeys();