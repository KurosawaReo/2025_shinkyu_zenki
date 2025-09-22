/*
   - KR_Object.cpp - (DxLib)
   ver: 2025/09/21

   オブジェクトを追加します, 継承して使うことも可です。
   Draw, Calc, Inputの一部機能をオブジェクト指向で使えます。
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.hに入ってなければここで導入.
  #include "KR_Calc.h"
  #include "KR_Draw.h"
  #include "KR_Input.h"
#endif
#include "KR_Object.h"

//KR_Libに使う用.
namespace KR_Lib
{
	InputMng* p_input = InputMng::GetPtr();

// ▼*---=[ Object ]=---*▼ //

	//移動限界を越えないよう位置修正.
	void ObjectShape::FixPosInArea(int left, int up, int right, int down) {
		Calc::FixPosInArea(GetPosPtr(), GetSize().ToIntXY(), left, up, right, down);
	}
	//エリアを越えているかどうか.
	bool ObjectShape::IsOutInArea(int left, int up, int right, int down, bool isCompOut) {
		return Calc::IsOutInArea(GetPos(), GetSize().ToIntXY(), left, up, right, down, isCompOut);
	}
	//距離を求める.
	double ObjectShape::CalcDist(DBL_XY pos) {
		return Calc::CalcDist(GetPos(), pos);
	}
	//角度と長さから円周上の座標を求める.
	DBL_XY ObjectShape::CalcArcPos(double ang, double len) {
		return Calc::CalcArcPos(GetPos(), ang, len);
	}
	//対象座標を見た時の方向を求める.
	double ObjectShape::CalcFacingAng(DBL_XY targetPos) {
		return Calc::CalcFacingAng(GetPos(), targetPos);
	}

	//移動操作.
	void ObjectShape::MoveKey4Dir(float speed) {
		p_input->MoveKey4Dir(GetPosPtr(), speed);
	}
	void ObjectShape::MovePad4Dir(float speed) {
		p_input->MovePad4Dir(GetPosPtr(), speed);
	}
	void ObjectShape::MovePadStick(float speed) {
		p_input->MovePadStick(GetPosPtr(), speed);
	}
	void ObjectShape::MoveMousePos(bool isValidX, bool isValidY) {
		SetPos(p_input->GetMousePos(isValidX, isValidY));
	}
	
	//画像を描画.
	int ObjectShape::DrawGraph() {

		_return(-1, !isActive); //-1: 非アクティブ.

		//画像データがない.
		if (img == nullptr) {
			DrawShape(); //代わりに図形を描画.
			return -2;   //-2: 画像なし.
		}
		//座標にoffsetを足す.
		DBL_XY pos = GetPos() + offset;
		//描画.
		int err = img->Draw(pos);
		_return(-3, err < 0); //-3: 画像描画エラー.

		return 0; //正常終了.
	}
	int ObjectShape::DrawRectGraph(int left, int up, int right, int down) {

		_return(-1, !isActive); //-1: 非アクティブ.

		//画像データがない.
		if (img == nullptr) {
			DrawShape(); //代わりに図形を描画.
			return -2;   //-2: 画像なし.
		}
		//座標にoffsetを足す.
		DBL_XY pos = GetPos() + offset;
		//描画.
		int err = img->DrawRect(pos, left, up, right, down);
		_return(-3, err < 0); //-3: 画像描画エラー.

		return 0; //正常終了.
	}
	int ObjectShape::DrawExtendGraph(DBL_XY sizeRate) {

		_return(-1, !isActive); //-1: 非アクティブ.

		//画像データがない.
		if (img == nullptr) {
			DrawShape(); //代わりに図形を描画.
			return -2;   //-2: 画像なし.
		}
		//座標にoffsetを足す.
		DBL_XY pos = GetPos() + offset;
		//描画.
		int err = img->DrawExtend(pos, sizeRate);
		_return(-3, err < 0); //-3: 画像描画エラー.

		return 0; //正常終了.
	}
	int ObjectShape::DrawRotaGraph(double ang, double sizeRate, INT_XY pivot) {

		_return(-1, !isActive); //-1: 非アクティブ.

		//画像データがない.
		if (img == nullptr) {
			DrawShape(); //代わりに図形を描画.
			return -2;   //-2: 画像なし.
		}
		//座標にoffsetを足す.
		DBL_XY pos = GetPos() + offset;

		//描画.
		int err = img->DrawRota(pos, sizeRate, ang, pivot);
		_return(-3, err < 0); //-3: 画像描画エラー.

		return 0; //正常終了.
	}

// ▼*---=[ ObjectCir ]=---*▼ //

	//円との判定.
	bool ObjectCir::HitCheckCir(const Circle* cir) {
		return Calc::HitCirCir(cir, &this->cir);
	}
	//四角形との判定.
	bool ObjectCir::HitCheckBox(const Box* box) {
		return Calc::HitBoxCir(box, &this->cir);
	}
	//線との当たり判定.
	bool ObjectCir::HitCheckLine(const Line* line) {
		return Calc::HitLineCir(line, &this->cir);
	}
	//図形: 円を描画.
	int ObjectCir::DrawShape(bool isFill, bool isAnti) {

		_return(0, !isActive); //非アクティブなら描画しない.

		//座標にoffsetを足す.
		Circle tmpCir = cir;
		tmpCir.pos += offset;
		//描画.
		int err = DrawCircleKR(&tmpCir, isFill, isAnti);
		return err; //-1: 円描画エラー.
	}

// ▼*---=[ ObjectBox ]=---*▼ //

	//円との判定.
	bool ObjectBox::HitCheckCir(const Circle* cir) {
		return Calc::HitBoxCir(&this->box, cir);
	}
	//四角形との判定.
	bool ObjectBox::HitCheckBox(const Box* box) {
		return Calc::HitBoxBox(&this->box, box);
	}
	//図形: 四角形を描画.
	int ObjectBox::DrawShape(bool isFill, bool isAnti) {

		_return(0, !isActive); //非アクティブなら描画しない.

		//座標にoffsetを足す.
		Box tmpBox = box;
		tmpBox.pos += offset;
		//描画.
		int err = DrawBoxKR(&tmpBox, ANC_MID, isFill, isAnti);
		return err; //-1: 円描画エラー.
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