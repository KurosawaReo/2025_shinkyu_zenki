/*
   - myCalcST.h - (original)
   ver.2025/07/14

   DxLib: �I���W�i���v�Z�@�\�̒ǉ�.
*/
#pragma once

//�p�x�ϊ��p.
#define _rad(x) (x)*(M_PI/180)
#define _dig(x) (x)*(180/M_PI)

//�����蔻��.
BOOL   IsHitCircle	(const Circle* cir1, const Circle* cir2);
BOOL   IsHitBox		(const Box*    box1, const Box*    box2,  BOOL isCenter);
BOOL   IsHitLine	(const Line*   line, const Circle* cir);

int    RndNum		(int st, int ed, BOOL isDxRnd = FALSE);

//�ړ����E.
void   FixPosInArea (DBL_XY* pos, INT_XY size, int left, int up, int right, int down);
BOOL   IsOutInArea  (DBL_XY  pos, INT_XY size, int left, int up, int right, int down, BOOL isCompOut);

//�v�Z.
double CalcDis		(INT_XY pos1, INT_XY pos2);
double CalcDis		(DBL_XY pos1, DBL_XY pos2);
DBL_XY CalcMidPos	(DBL_XY pos1, DBL_XY pos2);
DBL_XY CalcLineAng	(DBL_XY stPos, float ang, float len);
DBL_XY CalcDigToPos	(double dig);
DBL_XY CalcRadToPos	(double rad);