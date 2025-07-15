/*
   - myCalcST.cpp - (original)
   ver.2025/07/15

   DxLib: オリジナル計算機能の追加.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx等に入ってなければここで導入.
#endif

#include "myCalcST.h"

//当たり判定(円と円)
BOOL IsHitCircle(const Circle* cir1, const Circle* cir2) {

	//距離差.
	double x = cir1->pos.x - cir2->pos.x;
	double y = cir1->pos.y - cir2->pos.y;
    //距離が半径の合計より短ければ当たっている.
	//(√を削減するために2乗して計算)
    if (x*x + y*y <= pow(cir1->r+cir2->r, 2)) {
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

//移動可能範囲内に補正する.
void FixPosInArea(DBL_XY* pos, INT_XY size, int left, int up, int right, int down) {

	if (pos->x < left  + size.x/2) { pos->x = left  + size.x/2; }
	if (pos->y < up    + size.y/2) { pos->y = up    + size.y/2; }
	if (pos->x > right - size.x/2) { pos->x = right - size.x/2; }
	if (pos->y > down  - size.y/2) { pos->y = down  - size.y/2; }
}
//範囲外かどうか.
BOOL IsOutInArea(DBL_XY pos, INT_XY size, int left, int up, int right, int down, BOOL isCompOut) {

	//完全に出たら範囲外とする.
	if (isCompOut) {
		if (pos.x < left  - size.x/2) { return TRUE; }
		if (pos.y < up    - size.y/2) { return TRUE; }
		if (pos.x > right + size.x/2) { return TRUE; }
		if (pos.y > down  + size.y/2) { return TRUE; }
	}
	//触れた瞬間に範囲外とする.
	else {
		if (pos.x < left  + size.x/2) { return TRUE; }
		if (pos.y < up    + size.y/2) { return TRUE; }
		if (pos.x > right - size.x/2) { return TRUE; }
		if (pos.y > down  - size.y/2) { return TRUE; }
	}

	return FALSE; //範囲内.
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
//2つの座標の中点を計算.
DBL_XY CalcMidPos(DBL_XY pos1, DBL_XY pos2) {

	double x = (pos1.x + pos2.x)/2; //xの平均.
    double y = (pos1.y + pos2.y)/2; //yの平均.

	return { x, y };
}
//始点から角度と長さを入れた座標を計算.
DBL_XY CalcArcPos(DBL_XY stPos, double ang, double len) {

    //角度をradに変換し、座標の計算.
    double y = sin(_rad(ang)) * len;
    double x = cos(_rad(ang)) * len;

    return { stPos.x+x, stPos.y+y }; //終点座標を返す.
}
//始点から目標を見た時の角度を計算.
double CalcFacingAng(DBL_XY stPos, DBL_XY targetPos) {
	//座標差.
    double disX = targetPos.x - stPos.x;
	double disY = targetPos.y - stPos.y;
	//radをdigにして返す.
	return _dig(atan2(disY, disX));
}
//角度から座標を求める.
DBL_XY CalcDigToPos(double dig) {
	//座標vector(値が-1～+1になる)を返す.
	return { cos(_rad(dig)), sin(_rad(dig)) };
}
//角度から座標を求める.
DBL_XY CalcRadToPos(double rad) {
	//座標vector(値が-1～+1になる)を返す.
	return { cos(rad), sin(rad) };
}

//ease-out:だんだん減速.
float CalcNumEaseOut(float time) {
	time = min(time, 1.0f); //上限は1.0
	time = max(time, 0.0f); //下限は0.0
	return 1 - (1-time) * (1-time);
}

//値の抽選.
int RndNum(int st, int ed, BOOL isDxRnd) {

	int rnd = 0;

	//edがst以上の時のみ抽選.
	_if_check(st <= ed) {

		//DxLib用の乱数を使うかどうか.
		if (isDxRnd) {
			rnd = GetRand(ed - st); //st～endの差で抽選.
		}
		else {
			rnd = rand() % ((ed - st) + 1); //st～endの差で抽選.
		}
	}
	return st + rnd;
}
//値から小数だけ取り出す.
double GetDecimal(double num) {

	double n = 0; //整数部.
	double f = 0; //小数部.
	f = modf(num, &n); //小数だけ取り出す.

	return f;
}