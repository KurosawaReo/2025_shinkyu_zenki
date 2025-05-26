/*
   - myCalcST.h - (original)
   ver.2025/05/21

   DxLibで使う用のオリジナル計算関数.
*/
#pragma once

//当たり判定.
BOOL   IsHitCircle(DBL_XY pos1, int r1, DBL_XY pos2, int r2);
BOOL   IsHitBox   (DBL_XY pos1, INT_XY size1, DBL_XY pos2, INT_XY size2, BOOL isCenter);
BOOL   IsHitLine  (const Line* line, const Circle* circle);

//計算.
int    CalcDis    (INT_XY pos1, INT_XY pos2);
double CalcDis    (DBL_XY pos1, DBL_XY pos2);
DBL_XY CalcMidPos (DBL_XY pos1, DBL_XY pos2);
DBL_XY CalcLineAng(DBL_XY stPos, float ang, float len);