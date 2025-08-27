/*
   - KR_Object.cpp - (DxLib)
   ver: 2025/08/25

   オブジェクトを追加します, 継承して使うことも可です.
   Draw, Calc, Inputの一部機能をオブジェクト指向で使えます.
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.hに入ってなければここで導入.
  #include "KR_Calc.h"
  #include "KR_Draw.h"
  #include "KR_Input.h"
  using namespace KR_Lib;
#endif
#include "KR_Object.h"

//KR_Libに使う用.
namespace KR_Lib
{
	Calc*     p_calc  = Calc::GetPtr();
	InputMng* p_input = InputMng::GetPtr();

// ▼*---=[ ObjectCir ]=---*▼ //

	//円との判定.
	bool ObjectCir::HitCheckCir(const Circle* cir) {
		return p_calc->HitCirCir(cir, &this->cir);
	}
	//四角形との判定.
	bool ObjectCir::HitCheckBox(const Box* box) {
		return p_calc->HitBoxCir(box, &this->cir);
	}
	//線との当たり判定.
	bool ObjectCir::HitCheckLine(const Line* line) {
		return p_calc->HitLineCir(line, &this->cir);
	}

	//移動限界を越えないよう位置修正.
	void ObjectCir::FixPosInArea(int left, int up, int right, int down) {
		p_calc->FixPosInArea(&cir.pos, {_int_r(cir.r), _int_r(cir.r)}, left, up, right, down);
	}
	//エリアを越えているかどうか.
	bool ObjectCir::IsOutInArea(int left, int up, int right, int down, bool isCompOut) {
		return p_calc->IsOutInArea(cir.pos, {_int_r(cir.r), _int_r(cir.r)}, left, up, right, down, isCompOut);
	}
	//距離を求める.
	double ObjectCir::CalcDist(DBL_XY pos) {
		return p_calc->CalcDist(cir.pos, pos);
	}
	//角度と長さから円周上の座標を求める.
	DBL_XY ObjectCir::CalcArcPos(double ang, double len) {
		return p_calc->CalcArcPos(cir.pos, ang, len);
	}
	//対象座標を見た時の方向を求める.
	double ObjectCir::CalcFacingAng(DBL_XY targetPos) {
		return p_calc->CalcFacingAng(cir.pos, targetPos);
	}

	//移動操作.
	void ObjectCir::MoveKey4Dir(float speed) {
		p_input->MoveKey4Dir(&cir.pos, speed);
	}
	void ObjectCir::MovePad4Dir(float speed) {
		p_input->MovePad4Dir(&cir.pos, speed);
	}
	void ObjectCir::MovePadStick(float speed) {
		p_input->MovePadStick(&cir.pos, speed);
	}
	void ObjectCir::MoveMousePos(bool isValidX, bool isValidY) {
		p_input->GetMousePos(&cir.pos, isValidX, isValidY);
	}

	//ObjectCir型: 円を描画.
	int ObjectCir::DrawShape(bool isFill, bool isAnti) {

		_return(0, !isActive); //非アクティブなら描画しない.

		//座標にoffsetを足す.
		Circle tmpCir = cir;
		tmpCir.pos += offset;
		//描画.
		int err = DrawCircleST(&tmpCir, isFill, isAnti);
		return err; //-1: 円描画エラー.
	}
	//ObjectCir型: 画像を描画.
	int ObjectCir::DrawGraph(DrawImg* img, DBL_XY sizeRate) {

		_return(0, !isActive); //非アクティブなら描画しない.

		//座標にoffsetを足す.
		Circle tmpCir = cir;
		tmpCir.pos += offset;
		//描画.
		int err = img->DrawExtend(tmpCir.pos, sizeRate);
		if (err < 0) {
			DrawShape(); //代わりに円を描画.
			return -1;   //-1: 画像描画エラー.
		}
		return 0; //正常終了.
	}

// ▼*---=[ ObjectBox ]=---*▼ //

	//円との判定.
	bool ObjectBox::HitCheckCir(const Circle* cir) {
		return p_calc->HitBoxCir(&this->box, cir);
	}
	//四角形との判定.
	bool ObjectBox::HitCheckBox(const Box* box) {
		return p_calc->HitBoxBox(&this->box, box);
	}

	//移動限界を越えないよう位置修正.
	void ObjectBox::FixPosInArea(int left, int up, int right, int down) {
		p_calc->FixPosInArea(&box.pos, box.size.ToIntXY(), left, up, right, down);
	}
	//エリアを越えているかどうか.
	bool ObjectBox::IsOutInArea(int left, int up, int right, int down, bool isCompOut) {
		return p_calc->IsOutInArea(box.pos, box.size.ToIntXY(), left, up, right, down, isCompOut);
	}
	//距離を求める.
	double ObjectBox::CalcDist(DBL_XY pos) {
		return p_calc->CalcDist(box.pos, pos);
	}
	//角度と長さから円周上の座標を求める.
	DBL_XY ObjectBox::CalcArcPos(double ang, double len) {
		return p_calc->CalcArcPos(box.pos, ang, len);
	}
	//対象座標を見た時の方向を求める.
	double ObjectBox::CalcFacingAng(DBL_XY targetPos) {
		return p_calc->CalcFacingAng(box.pos, targetPos);
	}

	//移動操作.
	void ObjectBox::MoveKey4Dir(float speed) {
		p_input->MoveKey4Dir(&box.pos, speed);
	}
	void ObjectBox::MovePad4Dir(float speed) {
		p_input->MovePad4Dir(&box.pos, speed);
	}
	void ObjectBox::MovePadStick(float speed) {
		p_input->MovePadStick(&box.pos, speed);
	}
	void ObjectBox::MoveMousePos(bool isValidX, bool isValidY) {
		p_input->GetMousePos(&box.pos, isValidX, isValidY);
	}

	//ObjectBox型: 四角形を描画.
	int ObjectBox::DrawShape(bool isFill, bool isAnti) {

		_return(0, !isActive); //非アクティブなら描画しない.

		//座標にoffsetを足す.
		Box tmpBox = box;
		tmpBox.pos += offset;
		//描画.
		int err = DrawBoxST(&tmpBox, ANC_MID, isFill, isAnti);
		return err; //-1: 円描画エラー.
	}
	//ObjectBox型: 画像を描画.
	int ObjectBox::DrawGraph(DrawImg* img, DBL_XY sizeRate) {

		_return(0, !isActive); //非アクティブなら描画しない.

		//座標にoffsetを足す.
		Box tmpBox = box;
		tmpBox.pos += offset;
		//描画.
		int err = img->DrawExtend(tmpBox.pos, sizeRate);
		if (err < 0) {
			DrawShape(); //代わりに四角形を描画.
			return -1;   //-1: 画像描画エラー.
		}
		return 0; //正常終了.
	}

// ▼*---=[ ObjectGrid ]=---*▼ //

	//オブジェクト(ObjectGrid型)の描画.
	int ObjectGrid::Draw(DrawImg* img, INT_XY gridPos, INT_XY gridSize) {

		_return(0, !isActive); //非アクティブなら描画しない.

		//座標.
		INT_XY newPos = {
			gridPos.x + pos.x * gridSize.x,
			gridPos.y + pos.y * gridSize.y
		};
		//画像描画.
		int err = img->Draw(newPos.ToDblXY(), ANC_LU);
		return err; //-1: DrawGraphSTでエラー.
	}
}