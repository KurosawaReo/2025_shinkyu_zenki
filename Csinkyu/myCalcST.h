/*
   - myCalcST.h - (original)
   ver.2025/06/23

   DxLib: オリジナル計算機能の追加.
*/
#pragma once

//当たり判定.
BOOL   IsHitCircle	(const Circle* cir1, const Circle* cir2);
BOOL   IsHitBox		(const Box*    box1, const Box*    box2,  BOOL isCenter);
BOOL   IsHitLine	(const Line*   line, const Circle* cir);

int    RndNum		(int st, int ed, BOOL isDxRnd = FALSE);

//移動限界.
void   FixPosInArea (DBL_XY* pos, INT_XY size, int left, int up, int right, int down);
BOOL   IsOutInArea  (DBL_XY  pos, INT_XY size, int left, int up, int right, int down);

//計算.
double CalcDis		(INT_XY pos1, INT_XY pos2);
double CalcDis		(DBL_XY pos1, DBL_XY pos2);
DBL_XY CalcMidPos	(DBL_XY pos1, DBL_XY pos2);
DBL_XY CalcLineAng	(DBL_XY stPos, float ang, float len);
DBL_XY CalcAngToPos	(double ang);