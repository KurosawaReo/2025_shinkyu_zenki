/*
   - KR_Object.cpp - (DxLib)
   ver: 2025/08/24

   オブジェクトを追加します, 継承して使うことも可です.
   Draw, Calcの一部機能をオブジェクト指向で使えます.
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.hに入ってなければここで導入.
  #include "KR_Calc.h"
  #include "KR_Draw.h"
  using namespace KR_Lib;
#endif
#include "KR_Object.h"

//KR_Libに使う用.
namespace KR_Lib
{
// ▼*---=[ ObjectCir ]=---*▼ //

	//円との判定.
	bool ObjectCir::HitCheckCircle(const Circle* cir) {
		Calc::GetPtr()->HitCheckCircle(&this->cir, cir);
	}
	//線との当たり判定.
	bool ObjectCir::HitCheckLine(const Line* line) {
		Calc::GetPtr()->HitCheckLine(line, &this->cir);
	}

	//移動限界を越えないよう位置修正.
	void ObjectCir::FixPosInArea(int left, int up, int right, int down) {
		Calc::GetPtr()->FixPosInArea(&cir.pos, {_int_r(cir.r), _int_r(cir.r)}, left, up, right, down);
	}
	//エリアを越えているかどうか.
	bool ObjectCir::IsOutInArea(int left, int up, int right, int down, bool isCompOut) {
		return Calc::GetPtr()->IsOutInArea(cir.pos, {_int_r(cir.r), _int_r(cir.r)}, left, up, right, down, isCompOut);
	}
	//距離を求める.
	double ObjectCir::CalcDist(DBL_XY pos) {
		return Calc::GetPtr()->CalcDist(cir.pos, pos);
	}
	//角度と長さから円周上の座標を求める.
	DBL_XY ObjectCir::CalcArcPos(double ang, double len) {
		return Calc::GetPtr()->CalcArcPos(cir.pos, ang, len);
	}
	//対象座標を見た時の方向を求める.
	double ObjectCir::CalcFacingAng(DBL_XY targetPos) {
		return Calc::GetPtr()->CalcFacingAng(cir.pos, targetPos);
	}

	//オブジェクト(ObjectCir型)の描画.
	int ObjectCir::Draw(bool isDrawHit) {

		_return(0, !isActive); //非アクティブなら描画しない.

		//座標にoffsetを足す.
		Circle tmpCir = {
			cir.pos+offset, cir.r, cir.color
		};

		//円を描画(画像がない場合)
		if (img.GetHandle() == 0) {
			int err = DrawCircleST(&tmpCir);
			_return(-1, err < 0); //-1: 円描画エラー.
		}
		//画像描画.
		else {
			int err = img.Draw(tmpCir.pos);
			_return(-2, err < 0); //-2: 画像描画エラー.
		
			//当たり判定表示.
			if (isDrawHit) {
				int err = DrawCircleST(&cir, false, true);
				_return(-3, err < 0); //-3: 当たり判定描画エラー.
			}
		}
		return 0; //正常終了.
	}

// ▼*---=[ ObjectBox ]=---*▼ //

	//四角との判定.
	bool ObjectBox::HitCheckBox(const Box* box) {
		Calc::GetPtr()->HitCheckBox(&this->box, box);
	}

	//移動限界を越えないよう位置修正.
	void ObjectBox::FixPosInArea(int left, int up, int right, int down) {
		Calc::GetPtr()->FixPosInArea(&box.pos, box.size.ToIntXY(), left, up, right, down);
	}
	//エリアを越えているかどうか.
	bool ObjectBox::IsOutInArea(int left, int up, int right, int down, bool isCompOut) {
		return Calc::GetPtr()->IsOutInArea(box.pos, box.size.ToIntXY(), left, up, right, down, isCompOut);
	}
	//距離を求める.
	double ObjectBox::CalcDist(DBL_XY pos) {
		return Calc::GetPtr()->CalcDist(box.pos, pos);
	}
	//角度と長さから円周上の座標を求める.
	DBL_XY ObjectBox::CalcArcPos(double ang, double len) {
		return Calc::GetPtr()->CalcArcPos(box.pos, ang, len);
	}
	//対象座標を見た時の方向を求める.
	double ObjectBox::CalcFacingAng(DBL_XY targetPos) {
		return Calc::GetPtr()->CalcFacingAng(box.pos, targetPos);
	}

	//オブジェクト(ObjectBox型)の描画.
	int ObjectBox::Draw(bool isDrawHit) {

		_return(0, !isActive); //非アクティブなら描画しない.

		//座標にoffsetを足す.
		Box tmpBox = {
			box.pos+offset, box.size, box.color
		};

		//画像がないなら四角を描画.
		if (img.GetHandle() == 0) {
			int err = DrawBoxST(&tmpBox);
			_return(-1, err < 0); //-1: 四角描画エラー.
		}
		//画像描画.
		else {
			int err = img.Draw(tmpBox.pos);
			_return(-2, err < 0); //-2: 画像描画エラー.
		
			//当たり判定表示.
			if (isDrawHit) {
				int err = DrawBoxST(&box, ANC_MID, false, true);
				_return(-3, err < 0); //-3: 当たり判定描画エラー.
			}
		}
		return 0; //正常終了.
	}

// ▼*---=[ ObjectGrid ]=---*▼ //

	//オブジェクト(ObjectGrid型)の描画.
	int ObjectGrid::Draw(INT_XY gridPos, INT_XY gridSize) {

		_return(0, !isActive); //非アクティブなら描画しない.

		//座標.
		INT_XY newPos = {
			gridPos.x + pos.x * gridSize.x,
			gridPos.y + pos.y * gridSize.y
		};
		//画像描画.
		int err = img.Draw(newPos.ToDblXY(), ANC_LU);
		return err; //-1: DrawGraphSTでエラー.
	}
}