/*
   - Meteo.cpp -
   降ってくる隕石.
*/
#include "Meteo.h"

void Meteo::Init(GameData* _data) {
	p_data = _data;
}

void Meteo::Reset() {

	state       = Meteo_Normal;
	pos         = {0, 0};
	vel         = {0, 0};
	active      = FALSE;
	destroyCntr = 0;
}

void Meteo::Update() {

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
			case Meteo_Normal:
				//画面外で消去.
				if (IsOutInArea(pos, { METEO_LINE_DIS_MAX*2, METEO_LINE_DIS_MAX*2 }, 0, 0, WINDOW_WID, WINDOW_HEI, TRUE)){
					active = FALSE; //無効にする.
				}
				break;

			case Meteo_Destroy:
				//破壊量の度合.
				destroyCntr += (p_data->isSlow) ? SLOW_MODE_SPEED : 1;
				//時間が終了したら.
				if (destroyCntr >= METEO_DEST_TIME) {
					state  = Meteo_Normal; //元に戻す.
					active = FALSE;        //消滅.
				}
				break;

			default: assert(FALSE); break;
		}
		//隕石構成線の更新.
		UpdateMeteoLine();
	}
}

void Meteo::Draw() {
	
	//隕石本体が有効なら.
	if (active) {
		//破壊モード限定.
		if (state == Meteo_Destroy) {
			int pow = _int(min(255 * (float)(METEO_DEST_TIME-destroyCntr)/METEO_DEST_TIME, 255)); //少しずつ減少(255→0)
			SetDrawBlendModeST(MODE_ADD, pow);
		}

		//有効な線を全て描画.
		for (int i = 0; i < shape.lineCnt; i++) {
			
			int clr = _int(255 * fabs(sin(pos.x/200))); //色の変化.
			shape.line[i].clr = GetColor(0, clr, 255);
			DrawLineST(&shape.line[i]);
		}

		ResetDrawBlendMode(); //描画モードリセット.
	}
}

//隕石出現.
void Meteo::Spawn() {

	int rnd1 = RndNum(0, 99);
	int rnd2 = RndNum(0, 99);

	INT_XY goalPos{}; //目標座標.

	//50%:上下端から出現.
	if (rnd1 < 50) {
		pos.x = RndNum(0, WINDOW_WID);                                                  //xの設定.
		pos.y = (rnd2 < 50) ? 0 - METEO_LINE_DIS_MAX : WINDOW_HEI + METEO_LINE_DIS_MAX; //yの設定.
	}
	//50%:左右端から出現.
	else {
		pos.x = (rnd2 < 50) ? 0 - METEO_LINE_DIS_MAX : WINDOW_WID + METEO_LINE_DIS_MAX; //xの設定.
		pos.y = RndNum(0, WINDOW_HEI);                                                  //yの設定.
	}

	//目標地点の抽選.
	{
		goalPos.x = RndNum(WINDOW_WID/2 - METEO_GOAL_RAND_RANGE, WINDOW_WID/2 + METEO_GOAL_RAND_RANGE);
		goalPos.y = RndNum(WINDOW_HEI/2 - METEO_GOAL_RAND_RANGE, WINDOW_HEI/2 + METEO_GOAL_RAND_RANGE);
		//目標地点までの角度を求める.
		double rad = atan2(goalPos.y - pos.y, goalPos.x - pos.x);
		//xとyのvectorに分解.
		vel = CalcRadToPos(rad);
	}

	//隕石の設定.
	{
		//何角形にするか.
		shape.lineCnt = RndNum(METEO_LINE_CNT_MIN, METEO_LINE_CNT_MAX);
		//頂点の位置を抽選.
		for (int i = 0; i < shape.lineCnt; i++) {
			shape.lineDis[i] = (float)RndNum(METEO_LINE_DIS_MIN*10, METEO_LINE_DIS_MAX*10)/10; //小数第1位まで抽選する.
		}
	}

	active = TRUE; //隕石を有効にする.
}

//隕石破壊.
void Meteo::Destroy() {
	//破壊してないなら.
	if (state == Meteo_Normal) {
		state = Meteo_Destroy; //破壊モードに.
		destroyCntr = 0;       //0から開始.
	}
}

//隕石の当たり判定.
BOOL Meteo::IsHitMeteo(Circle* pos) {

	//有効な隕石なら.
	if (active && state == Meteo_Normal) {
		//全ての線で判定.
		for (int i = 0; i < shape.lineCnt; i++) {
			//線とプレイヤーが当たったら.
			if (IsHitLine(&shape.line[i], pos)) {
				return TRUE; //当たった.
			}
		}
	}

	return FALSE; //当たっていない.
}

//隕石を構成する線の更新.
void Meteo::UpdateMeteoLine() {

	//何度ずつずれるか.
	float rot = (float)360/shape.lineCnt; //360度÷描く線の数.

	//回転しながら始点と終点を設定していく.
	for (int i = 0; i < shape.lineCnt; i++) {

		//要素数が0未満なら最大値へ移動する.
		int bef = ((i-1) < 0) ? shape.lineCnt-1 : (i-1);

		shape.line[i].stPos = CalcArcPos(pos, ang+  i*rot, shape.lineDis[i]);   //始点: 現在の角度から計算.
		shape.line[i].edPos = CalcArcPos(pos, ang+bef*rot, shape.lineDis[bef]); //終点: 1つ前の角度から計算.

		//破壊時の回転アニメーション.
		if (state == Meteo_Destroy) {

			//①隕石を構成する線の情報.
			DBL_XY lineMidPos = CalcMidPos(shape.line[i].stPos, shape.line[i].edPos); //中点の位置.
			double lineLen    = CalcDis(shape.line[i].stPos, lineMidPos);             //長さの半分.
			double lineAng    = CalcFacingAng(lineMidPos, shape.line[i].stPos);       //角度.
			//②隕石の中央からどんどん離していく.
			double pivotDis   = CalcDis(pos, lineMidPos);                             //隕石の中央からの距離.
			double pivotAng   = CalcFacingAng(pos, lineMidPos);                       //隕石の中央から見た角度.
			DBL_XY newPos     = CalcArcPos(pos, pivotAng, pivotDis+destroyCntr);      //距離を増やす.
			//③新たな線の始点と終点.
			shape.line[i].stPos = CalcArcPos(newPos, lineAng    +destroyCntr, lineLen);
			shape.line[i].edPos = CalcArcPos(newPos, lineAng+180+destroyCntr, lineLen);
		}
	}
}