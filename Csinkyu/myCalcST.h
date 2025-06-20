/*
   - myCalcST.h - (original)
   ver.2025/06/18

   DxLib�Ŏg���p�̃I���W�i���v�Z�֐�.
*/
#pragma once

//�����蔻��.
BOOL   IsHitCircle	(const Circle* cir1, const Circle* cir2);
BOOL   IsHitBox		(const Box*    box1, const Box*    box2,  BOOL isCenter);
BOOL   IsHitLine	(const Line*   line, const Circle* cir);

int    RndNum		(int st, int ed, BOOL isDxRnd = FALSE);

//�v�Z.
double CalcDis		(INT_XY pos1, INT_XY pos2);
double CalcDis		(DBL_XY pos1, DBL_XY pos2);
DBL_XY CalcMidPos	(DBL_XY pos1, DBL_XY pos2);
DBL_XY CalcLineAng	(DBL_XY stPos, float ang, float len);
DBL_XY CalcAngToPos	(double ang);