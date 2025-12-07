/*
   - KR_Object.cpp - (DxLib)
   ver: 2025/12/07
*/
#include "KR_Object.h"

//[include] cppでのみ使うもの.
#include "KR_Calc.h"
#include "KR_Input.h"

//KrLib名前空間.
namespace KR
{
// ▼*--=<[ ObjectShape ]>=--*▼ //

	//移動限界を越えないよう位置修正.
	void ObjectShape::FixPosInArea(DBL_RECT rect) {
		Calc::FixPosInArea(GetPosPtr(), GetSize().ToInt(), rect);
	}
	//エリアを越えているかどうか.
	bool ObjectShape::IsOutInArea(DBL_RECT rect, bool isCompOut) {
		return Calc::IsOutInArea(GetPos(), GetSize().ToInt(), rect, isCompOut);
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
		InputMng::MoveKey4Dir(GetPosPtr(), speed);
	}
	void ObjectShape::MovePad4Dir(float speed) {
		InputMng::MovePad4Dir(GetPosPtr(), speed);
	}
	void ObjectShape::MovePadStick(float speed) {
		InputMng::MovePadStick(GetPosPtr(), speed);
	}
	void ObjectShape::MoveMousePos(bool isMoveX, bool isMoveY) {
		//有効ならマウス座標を反映.
		double x = (isMoveX) ? InputMng::GetMousePos().x : GetPos().x;
		double y = (isMoveY) ? InputMng::GetMousePos().y : GetPos().y;
		SetPos({x, y});
	}
	
	//DrawGraph描画.
	ResultInt ObjectShape::DrawGraph(Anchor anc, bool isFloat, bool isCameraDis) const {

		if (!isActive) {
			return {-1, _T("ObjectShape::DrawGraph"), _T("非アクティブ")};
		}

		//画像データがない.
		if (img == nullptr) {
			DrawShape(); //代わりに図形を描画.
			return {-2, _T("ObjectShape::DrawGraph"), _T("画像なし") };
		}
		//座標にoffsetを足す.
		DBL_XY pos = GetPos() + offset;
		//描画.
		ResultInt err = img->Draw(pos, anc, true, isFloat, isCameraDis);
		if (err.GetCode() < 0) {
			return {-3, _T("ObjectShape::DrawGraph"), _T("描画エラー")};
		}

		return {0, _T("ObjectShape::DrawGraph"), _T("正常終了")};
	}
	//DrawRectGraph描画.
	ResultInt ObjectShape::DrawRectGraph(DBL_RECT rect, Anchor anc, bool isFloat, bool isCameraDis) const {

		if (!isActive) {
			return {-1, _T("ObjectShape::DrawRectGraph"), _T("非アクティブ")};
		}

		//画像データがない.
		if (img == nullptr) {
			DrawShape(); //代わりに図形を描画.
			return {-2, _T("ObjectShape::DrawRectGraph"), _T("画像なし")};
		}
		//座標にoffsetを足す.
		DBL_XY pos = GetPos() + offset;
		//描画.
		ResultInt err = img->DrawRect(pos, rect, anc, true, isFloat, isCameraDis);
		if (err.GetCode() < 0) {
			return {-3, _T("ObjectShape::DrawRectGraph"), _T("描画エラー")};
		}

		return {0, _T("ObjectShape::DrawRectGraph"), _T("正常終了")};
	}
	//DrawExtendGraph描画.
	ResultInt ObjectShape::DrawExtendGraph(DBL_XY sizeRate, Anchor anc, bool isFloat, bool isCameraDis) const {

		if (!isActive) {
			return {-1, _T("ObjectShape::DrawExtendGraph"), _T("非アクティブ")};
		}

		//画像データがない.
		if (img == nullptr) {
			DrawShape(); //代わりに図形を描画.
			return {-2, _T("ObjectShape::DrawExtendGraph"), _T("画像なし")};
		}
		//座標にoffsetを足す.
		DBL_XY pos = GetPos() + offset;
		//描画.
		ResultInt err = img->DrawExtend(pos, sizeRate, anc, true, isFloat, isCameraDis);
		if (err.GetCode() < 0) {
			return {-3, _T("ObjectShape::DrawExtendGraph"), _T("描画エラー")};
		}

		return {0, _T("ObjectShape::DrawExtendGraph"), _T("正常終了")};
	}
	//DrawRotaGraph描画.
	ResultInt ObjectShape::DrawRotaGraph(double ang, double sizeRate, INT_XY pivot, bool isFloat, bool isCameraDis) const {

		if (!isActive) {
			return {-1, _T("ObjectShape::DrawRotaGraph"), _T("非アクティブ")};
		}

		//画像データがない.
		if (img == nullptr) {
			DrawShape(); //代わりに図形を描画.
			return {-2, _T("ObjectShape::DrawRotaGraph"), _T("画像なし")};
		}
		//座標にoffsetを足す.
		DBL_XY pos = GetPos() + offset;

		//描画.
		ResultInt err = img->DrawRota(pos, sizeRate, ang, pivot, true, isFloat, isCameraDis);
		if (err.GetCode() < 0) {
			return {-3, _T("ObjectShape::DrawRotaGraph"), _T("描画エラー")};
		}

		return {0, _T("ObjectShape::DrawRotaGraph"), _T("正常終了")};
	}

// ▼*--=<[ ObjectCir ]>=--*▼ //

	//円との判定.
	bool ObjectCir::HitCheckCir(const Circle& cir) const {
		return Calc::HitCirCir(cir, this->cir);
	}
	//四角形との判定.
	bool ObjectCir::HitCheckBox(const Box& box) const {
		return Calc::HitBoxCir(box, this->cir);
	}
	//線との当たり判定.
	bool ObjectCir::HitCheckLine(const Line& line) const {
		return Calc::HitLineCir(line, this->cir);
	}
	//図形: 円を描画.
	ResultInt ObjectCir::DrawShape(bool isFill, bool isAnti, bool isCameraDis) const {

		if (!isActive) {
			return {-1, _T("ObjectCir::DrawShape"), _T("非アクティブ")};
		}

		//座標にoffsetを足す.
		Circle tmpCir = cir;
		tmpCir.pos += offset;
		//描画.
		ResultInt err = DrawCircleKR(tmpCir, isFill, isAnti, 1.0, isCameraDis);
		if (err.GetCode() < 0) {
			return {-2, _T("ObjectCir::DrawShape"), _T("DrawCircleKRエラー")};
		}
		return {0, _T("ObjectCir::DrawShape"), _T("正常終了") };
	}

// ▼*--=<[ ObjectBox ]>=--*▼ //

	//円との判定.
	bool ObjectBox::HitCheckCir(const Circle& cir) const {
		return Calc::HitBoxCir(this->box, cir);
	}
	//四角形との判定.
	bool ObjectBox::HitCheckBox(const Box& box) const {
		return Calc::HitBoxBox(this->box, box);
	}
	//図形: 四角形を描画.
	ResultInt ObjectBox::DrawShape(bool isFill, bool isAnti, bool isCameraDis) const {

		if (!isActive) {
			return {-1, _T("ObjectBox::DrawShape"), _T("非アクティブ")};
		}

		//座標にoffsetを足す.
		Box tmpBox = box;
		tmpBox.pos += offset;
		//描画.
		ResultInt err = DrawBoxKR(tmpBox, Anchor::Mid, isFill, isAnti, isCameraDis);
		if (err.GetCode() < 0) {
			return {-2, _T("ObjectBox::DrawShape"), _T("DrawBoxKRエラー")};
		}
		return {0, _T("ObjectBox::DrawShape"), _T("正常終了")};
	}

// ▼*--=<[ ObjectGrid ]>=--*▼ //

	//オブジェクト(ObjectGrid型)の描画.
	ResultInt ObjectGrid::Draw(const DrawImg& img, INT_XY gridPos, INT_XY gridSize) {

		if (!isActive) {
			return {-1, _T("ObjectGrid::Draw"), _T("非アクティブ") };
		}

		//座標.
		INT_XY newPos = {
			gridPos.x + pos.x * gridSize.x,
			gridPos.y + pos.y * gridSize.y
		};
		//画像描画.
		ResultInt err = img.Draw(newPos.ToDbl(), Anchor::LU);
		if (err.GetCode() < 0) {
			return {-2, _T("ObjectGrid::Draw"), _T("画像描画エラー")};
		}
		return {0, _T("ObjectGrid::Draw"), _T("正常終了")};
	}
}