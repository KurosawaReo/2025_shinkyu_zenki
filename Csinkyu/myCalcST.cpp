/*
   - myCalcST.cpp - (original)
   ver.2025/08/20

   DxLib: オリジナル計算機能の追加.
*/
#if !defined DEF_MYLIB_GLOBAL
  #include "Global.h" //stdafx等に入ってなければここで導入.
#endif
#include "myCalcST.h"

//当たり判定(円と円)
bool HitCheckCircle(const Circle* cir1, const Circle* cir2) {

	//距離差.
	double x = cir1->pos.x - cir2->pos.x;
	double y = cir1->pos.y - cir2->pos.y;
    //距離が半径の合計より短ければ当たっている.
	//(√を削減するために2乗して計算)
    if (x*x + y*y <= pow(cir1->r+cir2->r, 2)) {
        return true;
    }
    else {
        return false;
    }
}
//当たり判定(四角と四角)
bool HitCheckBox(const Box* box1, const Box* box2) {

    //中央基準座標での判定.
	if (fabs(box1->pos.x - box2->pos.x) <= (box1->size.x + box2->size.x)/2 &&
		fabs(box1->pos.y - box2->pos.y) <= (box1->size.y + box2->size.y)/2
	){
		return true;
	}
	else {
	    return false;
	}
}
//当たり判定(線と円)
bool HitCheckLine(const Line* line, const Circle* cir) {

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
	if (dis1 <= cir->r &&                                     //条件1:線に触れている.
		dis2 <= CalcDist(line->stPos, line->edPos)/2 + cir->r //条件2:線を直径とする円に触れている.
	){
		return true;
	}
	else {
		return false;
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
bool IsOutInArea(DBL_XY pos, INT_XY size, int left, int up, int right, int down, bool isCompOut) {

	//完全に出たら範囲外とする.
	if (isCompOut) {
		if (pos.x < left  - size.x/2) { return true; }
		if (pos.y < up    - size.y/2) { return true; }
		if (pos.x > right + size.x/2) { return true; }
		if (pos.y > down  + size.y/2) { return true; }
	}
	//触れた瞬間に範囲外とする.
	else {
		if (pos.x < left  + size.x/2) { return true; }
		if (pos.y < up    + size.y/2) { return true; }
		if (pos.x > right - size.x/2) { return true; }
		if (pos.y > down  - size.y/2) { return true; }
	}

	return false; //範囲内.
}

//距離計算.
double CalcDist(INT_XY pos1, INT_XY pos2) {

	double x = pos1.x - pos2.x; //xの差.
    double y = pos1.y - pos2.y; //yの差.

	return sqrt(x*x + y*y); //斜辺の長さを返す.
}
double CalcDist(DBL_XY pos1, DBL_XY pos2) {

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
	return _deg(atan2(disY, disX));
}
//角度から座標を求める.
DBL_XY CalcDegToPos(double deg) {
	//座標vector(値が-1～+1になる)を返す.
	return { cos(_rad(deg)), sin(_rad(deg)) };
}
//角度から座標を求める.
DBL_XY CalcRadToPos(double rad) {
	//座標vector(値が-1～+1になる)を返す.
	return { cos(rad), sin(rad) };
}

//ease-int: 徐々に加速.
double CalcNumEaseIn(double time) {
	time = min(time, 1.0); //上限は1.0
	time = max(time, 0.0); //下限は0.0
	return time * time;
}
//ease-out: 徐々に減速.
double CalcNumEaseOut(double time) {
	time = min(time, 1.0); //上限は1.0
	time = max(time, 0.0); //下限は0.0
	return 1 - (1-time) * (1-time);
}
//ease-in-out: 徐々に加速して減速.
double CalcNumEaseInOut(double time) {
	time = min(time, 1.0); //上限は1.0
	time = max(time, 0.0); //下限は0.0
	return 0.5 * (1.0 - cos(M_PI*time)); //cosの返り値は1.0 → -1.0
}
//wave loop: cos波のループ(0.0～1.0)
double CalcNumWaveLoop(double time) {
	return 0.5 - cos(M_PI*time)/2;
}

//値の抽選.
int RandNum(int st, int ed, bool isDxRnd) {

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
//値の抽選(重複なし複数)
vector<int> RandNums(int st, int ed, int count, bool isDxRnd) {

	int unUsedCnt = (ed-st)+1;      //未使用数字はいくつあるか.
	vector<bool> isUsed((ed-st)+1); //各数字が使用済かどうか.
	vector<int>  ret   (count);     //抽選結果を入れる用.
	
	//抽選する回数分ループ.
	for (int i = 0; i < count; i++) {

		//未使用数字から何番目を選ぶか抽選.
		int cnt = RandNum(1, unUsedCnt, isDxRnd);
		
		//st～edの中で数字を選ぶ.
		for (int j = 0; j <= ed-st; j++) {
			//未使用数字なら.
			if (!isUsed[j]) {
				cnt--; //カウント-1
				if (cnt == 0) {
					ret[i] = st+j;    //この数字を抽選結果に保存.
					isUsed[j] = true; //この数字は使用済.
					unUsedCnt--;      //未使用枠-1.
					break;
				}
			}
		}
	}

	//抽選結果を返す.
	return ret;
}
//値から小数だけ取り出す.
double GetDecimal(double num) {
	return fmod(num, 1.0); //1.0で割った余り.
}