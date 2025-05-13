/*
   - myCalcST.cpp - (original)

   DxLibで使う用のオリジナル計算関数.
   2025/05/14
*/
#if false
  #include "stdafx.h" //stdafxがあるならこっちを使う.
#else
  #define _USE_MATH_DEFINES //math定数を使うのに必要.
  #include <math.h>
  #include "DxLib.h"
#endif

#include "myCalcST.h"

//int型変換マクロ.
#define _int(n) (int)(round(n))

//当たり判定(円と円)
BOOL IsHitCircle(DBL_XY pos1, int r1, DBL_XY pos2, int r2) {

    double disX = pos1.x - pos2.x;
    double disY = pos1.y - pos2.y;

    if (sqrt(disX * disX + disY * disY) <= r1 + r2) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}
//当たり判定(四角と四角)
BOOL IsHitBox(DBL_XY pos1, INT_XY size1, DBL_XY pos2, INT_XY size2, BOOL isCenter) {

    BOOL hit = FALSE;

    //中央基準座標での判定.
    if (isCenter) {
        if (fabs(pos1.x - pos2.x) <= (size1.x + size2.x)/2 &&
            fabs(pos1.y - pos2.y) <= (size1.y + size2.y)/2)
        {
            hit = TRUE;
        }
    }
    //左上基準座標での判定.
    else {
        if (pos1.x + size1.x >= pos2.x && pos2.x + size2.x >= pos1.x &&
            pos1.y + size1.y >= pos2.y && pos2.y + size2.y >= pos1.y)
        {
            hit = TRUE;
        }
    }
    return hit;
}
//当たり判定(線と円)
BOOL IsHitLine(const Line* line, const Circle* circle) {

	//線の始点と終点から傾きを求める.
	double katamuki;
	{
		double x = line->edPos.x - line->stPos.x;
		double y = line->edPos.y - line->stPos.y;
		if (x != 0) {
			katamuki = y / x;
		}
		else {
			katamuki = 100; //0割対策.
		}
	}
	//線を方程式にした時の切片.
	double seppen = line->stPos.y - line->stPos.x * katamuki;

	//線～円の距離.
	double dis1;
	{
		//直線: ax + by + c = 0
		//bを1として「y = 」の形にする→ y = -ax - c
		double a = -katamuki;
		double b = 1;
		double c = -seppen;
		//公式: d = |ax + by + c|/√(a^2 + b^2)
		dis1 = fabs(a*circle->pos.x + b*circle->pos.y + c) / sqrt(a*a + b*b);
	}
	//線の中点～円の中心の距離.
	double dis2;
	{
		double x = circle->pos.x - CalcMidPos(line->stPos, line->edPos).x;
		double y = circle->pos.y - CalcMidPos(line->stPos, line->edPos).y;
		//距離: d = √(x^2 + y^2) (三平方の定理)
		dis2 = sqrt(x*x + y*y);
	}

	//hit条件.
	if (dis1 <= circle->r &&                                    //条件1:線に触れている.
		dis2 <= CalcDis(line->stPos, line->edPos)/2 + circle->r //条件2:線を直径とする円に触れている.
	){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

//距離計算.
double CalcDis(DBL_XY pos1, DBL_XY pos2) {

	double x = pos1.x - pos2.x; //xの差.
    double y = pos1.y - pos2.y; //yの差.

	return sqrt(x*x + y*y); //斜辺の長さを返す.
}
//中点座標計算.
DBL_XY CalcMidPos(DBL_XY pos1, DBL_XY pos2) {

	double x = (pos1.x + pos2.x)/2; //xの平均.
    double y = (pos1.y + pos2.y)/2; //yの平均.

	return { x, y };
}
//線の終点計算.
DBL_XY CalcLineAng(DBL_XY stPos, float ang, float len) {

    //角度をradに変換し、座標の計算.
    double y = sin(ang * M_PI/180) * len;
    double x = cos(ang * M_PI/180) * len;

    return { stPos.x+x, stPos.y+y }; //終点座標を返す.
}