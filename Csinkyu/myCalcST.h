/*
   - myCalcST.h - (original)
   ver.2025/05/15

   DxLibで使う用のオリジナル計算関数.
*/
#pragma once

BOOL   IsHitCircle(DBL_XY pos1, int r1, DBL_XY pos2, int r2);
BOOL   IsHitBox   (DBL_XY pos1, INT_XY size1, DBL_XY pos2, INT_XY size2, BOOL isCenter);
BOOL   IsHitLine  (const Line* line, const Circle* circle);

double CalcDis    (DBL_XY pos1, DBL_XY pos2);
DBL_XY CalcMidPos (DBL_XY pos1, DBL_XY pos2);
DBL_XY CalcLineAng(DBL_XY stPos, float ang, float len);