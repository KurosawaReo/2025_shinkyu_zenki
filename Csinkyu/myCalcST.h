/*
   - myCalcST.h - (original)

   DxLibで使う用のオリジナル計算関数.
   2025/05/14
*/
#pragma once

#if !defined DEF_INT_XY
#define DEF_INT_XY
//int型の凝縮xy.
struct INT_XY
{
	int x;
	int y;
};
#endif

#if !defined DEF_DBL_XY
#define DEF_DBL_XY
//double型の凝縮xy.
struct DBL_XY
{
	double x;
	double y;
};
#endif

#if !defined DEF_SHAPES
#define DEF_SHAPES
//円データ.
struct Circle
{
	DBL_XY pos;  //座標.
	int    r;    //半径.
	UINT   clr;  //色.
};
//四角形データ.
struct Box
{
	DBL_XY pos;  //座標.
	INT_XY size; //サイズ.
	UINT   clr;  //色.
};
//線データ.
struct Line
{
	DBL_XY stPos; //始点座標.
	DBL_XY edPos; //終点座標.
	UINT   clr;   //色.
};
#endif

BOOL   IsHitCircle(DBL_XY pos1, int r1, DBL_XY pos2, int r2);
BOOL   IsHitBox   (DBL_XY pos1, INT_XY size1, DBL_XY pos2, INT_XY size2, BOOL isCenter);
BOOL   IsHitLine  (const Line* line, const Circle* circle);

double CalcDis    (DBL_XY pos1, DBL_XY pos2);
DBL_XY CalcMidPos (DBL_XY pos1, DBL_XY pos2);
DBL_XY CalcLineAng(DBL_XY stPos, float ang, float len);