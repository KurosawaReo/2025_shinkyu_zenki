/*
   - myCalcST.cpp - (original)
   ver.2025/06/02

   DxLibで使う用のオリジナル計算関数.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafxがなければここで定義.
#endif

#include "myCalcST.h"

//当たり判定(円と円)
BOOL IsHitCircle(const Circle* cir1, const Circle* cir2) {

    //距離が半径の合計より短ければ当たっている.
    if (CalcDis(cir1->pos, cir2->pos) <= cir1->r + cir2->r) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}
//当たり判定(四角と四角)
BOOL IsHitBox(const Box* box1, const Box* box2, BOOL isCenter) {

    BOOL hit = FALSE;

    //中央基準座標での判定.
    if (isCenter) {
        if (fabs(box1->pos.x - box2->pos.x) <= (box1->size.x + box2->size.x)/2 &&
            fabs(box1->pos.y - box2->pos.y) <= (box1->size.y + box2->size.y)/2)
        {
            hit = TRUE;
        }
    }
    //左上基準座標での判定.
    else {
        if (box1->pos.x + box1->size.x >= box2->pos.x && box2->pos.x + box2->size.x >= box1->pos.x &&
            box1->pos.y + box1->size.y >= box2->pos.y && box2->pos.y + box2->size.y >= box1->pos.y)
        {
            hit = TRUE;
        }
    }
    return hit;
}
//当たり判定(線と円)
BOOL IsHitLine(const Line* line, const Circle* cir) {

	//線の始点と終点から傾きを求める.
	double katamuki;
	{
		double x = line->edPos.x - line->stPos.x;
		double y = line->edPos.y - line->stPos.y;
		if (x != 0) {
			katamuki = y / x;
		}
		else {
			katamuki = 999; //0割対策.
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
		dis1 = fabs(a*cir->pos.x + b*cir->pos.y + c) / sqrt(a*a + b*b);
	}
	//線の中点～円の中心の距離.
	double dis2;
	{
		double x = cir->pos.x - CalcMidPos(line->stPos, line->edPos).x;
		double y = cir->pos.y - CalcMidPos(line->stPos, line->edPos).y;
		//距離: d = √(x^2 + y^2) (三平方の定理)
		dis2 = sqrt(x*x + y*y);
	}

	//hit条件.
	if (dis1 <= cir->r &&                                    //条件1:線に触れている.
		dis2 <= CalcDis(line->stPos, line->edPos)/2 + cir->r //条件2:線を直径とする円に触れている.
	){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

//距離計算.
double CalcDis(INT_XY pos1, INT_XY pos2) {

	double x = pos1.x - pos2.x; //xの差.
    double y = pos1.y - pos2.y; //yの差.

	return sqrt(x*x + y*y); //斜辺の長さを返す.
}
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