/*
   - Obst_Meteor.cpp -

   障害物: 隕石.
*/
#include "GameManager.h"
#include "Obst_Meteor.h"

//namespace省略.
using namespace Calc; 

void Meteor::Init() {
	p_data = GameData::GetPtr();
}

void Meteor::Reset() {

	state       = Meteor_Normal;
	pos         = {0, 0};
	vel         = {0, 0};
	active      = false;
	destroyCntr = 0;
}

void Meteor::Update() {

	//隕石本体が有効なら.
	if (active) {

		//移動.
		pos.x += vel.x * METEO_SPEED * (double)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		pos.y += vel.y * METEO_SPEED * (double)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		//回転.
		ang += (p_data->isSlow) ? SLOW_MODE_SPEED : 1;

		//状態別処理.
		switch (state) 
		{
			case Meteor_Normal:
				//画面外で消去.
				if (IsOutInArea(pos, { METEO_LINE_DIS_MAX*2, METEO_LINE_DIS_MAX*2 }, 0, 0, WINDOW_WID, WINDOW_HEI, true)){
					active = false; //無効にする.
				}
				break;

			case Meteor_Destroy:
				//破壊量の度合.
				destroyCntr += (p_data->isSlow) ? SLOW_MODE_SPEED : 1;
				//時間が終了したら.
				if (destroyCntr >= METEO_DEST_TIME) {
					state  = Meteor_Normal; //元に戻す.
					active = false;        //消滅.
				}
				break;

			default: assert(false); break;
		}
		//隕石構成線の更新.
		UpdateMeteoLine();
	}
}

void Meteor::Draw() {
	
	//隕石本体が有効なら.
	if (active) {
		//破壊モード限定.
		if (state == Meteor_Destroy) {
			int pow = _int_r(255 * (1-destroyCntr/METEO_DEST_TIME)); //少しずつ減少(255→0)
			SetDrawBlendModeST(MODE_ADD, pow);
		}

		//有効な線を全て描画.
		for (int i = 0; i < shape.lineCnt; i++) {
			
			shape.line[i].color = COLOR_METEO(pos);
			DrawLineST(&shape.line[i], true, 2);
//			DrawLineST(&shape.line[i], false, 1);
		}

		ResetDrawBlendMode(); //描画モードリセット.
	}
}

//隕石出現.
void Meteor::Spawn() {

	int rnd1 = RandNum(0, 99);
	int rnd2 = RandNum(0, 99);

	INT_XY goalPos{}; //目標座標.

	//50%:上下端から出現.
	if (rnd1 < 50) {
		pos.x = RandNum(0, WINDOW_WID);                                                 //xの設定.
		pos.y = (rnd2 < 50) ? 0 - METEO_LINE_DIS_MAX : WINDOW_HEI + METEO_LINE_DIS_MAX; //yの設定.
	}
	//50%:左右端から出現.
	else {
		pos.x = (rnd2 < 50) ? 0 - METEO_LINE_DIS_MAX : WINDOW_WID + METEO_LINE_DIS_MAX; //xの設定.
		pos.y = RandNum(0, WINDOW_HEI);                                                 //yの設定.
	}

	//目標地点の抽選.
	{
		goalPos.x = RandNum(WINDOW_WID/2 - METEO_GOAL_RAND_RANGE, WINDOW_WID/2 + METEO_GOAL_RAND_RANGE);
		goalPos.y = RandNum(WINDOW_HEI/2 - METEO_GOAL_RAND_RANGE, WINDOW_HEI/2 + METEO_GOAL_RAND_RANGE);
		//目標地点までの角度を求める.
		double rad = atan2(goalPos.y - pos.y, goalPos.x - pos.x);
		//xとyのvectorに分解.
		vel = CalcVectorRad(rad);
	}

	//隕石の設定.
	{
		//何角形にするか.
		shape.lineCnt = RandNum(METEO_LINE_CNT_MIN, METEO_LINE_CNT_MAX);
		//頂点の位置を抽選.
		for (int i = 0; i < shape.lineCnt; i++) {
			shape.lineDis[i] = (float)RandNum(METEO_LINE_DIS_MIN*10, METEO_LINE_DIS_MAX*10)/10; //小数第1位まで抽選する.
		}
	}

	active = true; //隕石を有効にする.
}

//隕石破壊.
void Meteor::Destroy() {
	state = Meteor_Destroy; //破壊モードに.
	destroyCntr = 0;       //0から開始.
}

//隕石の当たり判定.
bool Meteor::IsHitMeteor(Circle* cir) {

	//有効な隕石なら.
	if (active && state == Meteor_Normal) {
		//全ての線で判定.
		for (int i = 0; i < shape.lineCnt; i++) {
			//線とプレイヤーが当たったら.
			if (HitLineCir(&shape.line[i], cir)) {
				return true; //当たった.
			}
		}
	}

	return false; //当たっていない.
}

//隕石を構成する線の更新.
void Meteor::UpdateMeteoLine() {

	//何度ずつずれるか.
	float rot = (float)360/shape.lineCnt; //360度÷描く線の数.

	//回転しながら始点と終点を設定していく.
	for (int i = 0; i < shape.lineCnt; i++) {

		//要素数が0未満なら最大値へ移動する.
		int bef = ((i-1) < 0) ? shape.lineCnt-1 : (i-1);

		shape.line[i].stPos = CalcArcPos(pos, ang+  i*rot, shape.lineDis[i]);   //始点: 現在の角度から計算.
		shape.line[i].edPos = CalcArcPos(pos, ang+bef*rot, shape.lineDis[bef]); //終点: 1つ前の角度から計算.

		//破壊時の回転アニメーション.
		if (state == Meteor_Destroy) {

			//①隕石を構成する線の情報.
			DBL_XY lineMidPos = CalcMidPos(shape.line[i].stPos, shape.line[i].edPos); //中点の位置.
			double lineLen    = CalcDist(shape.line[i].stPos, lineMidPos);            //長さの半分.
			double lineAng    = CalcFacingAng(lineMidPos, shape.line[i].stPos);		  //角度.
			//②隕石の中央からどんどん離していく.
			double pivotDis   = CalcDist(pos, lineMidPos);                            //隕石の中央からの距離.
			double pivotAng   = CalcFacingAng(pos, lineMidPos);                       //隕石の中央から見た角度.
			DBL_XY newPos     = CalcArcPos(pos, pivotAng, pivotDis+destroyCntr);      //距離を増やす.
			//③新たな線の始点と終点.
			shape.line[i].stPos = CalcArcPos(newPos, lineAng    +destroyCntr, lineLen);
			shape.line[i].edPos = CalcArcPos(newPos, lineAng+180+destroyCntr, lineLen);
		}
	}
}