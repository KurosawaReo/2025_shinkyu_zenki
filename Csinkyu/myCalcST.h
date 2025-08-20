/*
   - myCalcST.h - (original)
   ver.2025/08/20

   DxLib: �I���W�i���v�Z�@�\�̒ǉ�.
*/
#pragma once

//�p�x�ϊ��p.
#define _rad(x) (x)*(M_PI/180)
#define _deg(x) (x)*(180/M_PI)

//�����蔻��.
bool		HitCheckCircle	(const Circle* cir1, const Circle* cir2);
bool		HitCheckBox		(const Box*    box1, const Box*    box2);
bool		HitCheckLine	(const Line*   line, const Circle* cir);

//�ړ����E.
void		FixPosInArea	(DBL_XY* pos, INT_XY size, int left, int up, int right, int down);
bool		IsOutInArea		(DBL_XY  pos, INT_XY size, int left, int up, int right, int down, bool isCompOut);

//�v�Z.
double		CalcDist		(INT_XY pos1,  INT_XY pos2);
double		CalcDist		(DBL_XY pos1,  DBL_XY pos2);
DBL_XY		CalcMidPos		(DBL_XY pos1,  DBL_XY pos2);
DBL_XY		CalcArcPos		(DBL_XY stPos, double ang, double len);
double		CalcFacingAng	(DBL_XY stPos, DBL_XY targetPos);
DBL_XY		CalcDegToPos	(double deg);
DBL_XY		CalcRadToPos	(double rad);

//�l�̋Ȑ��ϓ�(�A�j���[�V�����p)
double		CalcNumEaseIn	(double time);
double		CalcNumEaseOut	(double time);
double		CalcNumEaseInOut(double time);
double		CalcNumWaveLoop	(double time);

//�l�̑���.
int         RandNum			(int st, int ed,            bool isDxRand = false);
vector<int> RandNums		(int st, int ed, int count, bool isDxRand = false);
double      GetDecimal		(double num);