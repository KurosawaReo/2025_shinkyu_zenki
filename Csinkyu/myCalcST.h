/*
   - myCalcST.h - (original)
   ver.2025/06/11

   DxLibで使う用のオリジナル計算関数.
*/
#pragma once

//当たり判定.
BOOL   IsHitCircle(const Circle* cir1, const Circle* cir2);
BOOL   IsHitBox   (const Box*    box1, const Box*    box2,  BOOL isCenter);
BOOL   IsHitLine  (const Line*   line, const Circle* cir);

//計算.
int    RndNum     (int st, int ed);
double CalcDis    (INT_XY pos1, INT_XY pos2);
double CalcDis    (DBL_XY pos1, DBL_XY pos2);
DBL_XY CalcMidPos (DBL_XY pos1, DBL_XY pos2);
DBL_XY CalcLineAng(DBL_XY stPos, float ang, float len);