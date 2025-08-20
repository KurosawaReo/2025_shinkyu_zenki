/*
   - myObjectST.cpp - (original)
   ver.2025/08/20

   DxLib: オリジナルオブジェクト機能の追加.
*/
#if !defined DEF_MYLIB_GLOBAL
  #include "Global.h" //stdafx等に入ってなければここで導入.
  #include "myDrawST.h"
#endif
#include "myObjectST.h"

//オブジェクト(ObjectCir型)の描画.
int ObjectCir::Draw(bool isDrawHit) {

	_return(0, !isActive); //非アクティブなら描画しない.

	//座標にoffsetを足す.
	Circle tmpCir = {
		cir.pos+offset, cir.r, cir.color
	};
	//画像がないなら円を描画.
	if (img.GetImage()->handle == 0) {
		DrawCircleST(&tmpCir);
	}
	//画像描画.
	else {
		int err = img.DrawGraphST(tmpCir.pos);
		_return(-1, err < 0); //-1: DrawGraphSTでエラー.
	}
	//当たり判定表示.
	if (isDrawHit) {
		int err = DrawCircleST(&cir, false, true);
		_return(-2, err < 0); //-2: DrawCircleSTでエラー.
	}
	return 0; //正常終了.
}
//オブジェクト(ObjectBox型)の描画.
int ObjectBox::Draw(bool isDrawHit) {

	_return(0, !isActive); //非アクティブなら描画しない.

	//座標にoffsetを足す.
	Box tmpBox = {
		box.pos+offset, box.size, box.color
	};
	//画像がないなら四角を描画.
	if (img.GetImage()->handle == 0) {
		DrawBoxST(&tmpBox);
	}
	//画像描画.
	else {
		int err = img.DrawGraphST(tmpBox.pos);
		_return(-1, err < 0); //-1: DrawGraphSTでエラー.
	}
	//当たり判定表示.
	if (isDrawHit) {
		int err = DrawBoxST(&box, ANC_MID, false, true);
		_return(-2, err < 0); //-2: DrawBoxSTでエラー.
	}
	return 0; //正常終了.
}
//オブジェクト(ObjectGrid型)の描画.
int ObjectGrid::Draw(INT_XY gridPos, INT_XY gridSize) {

	_return(0, !isActive); //非アクティブなら描画しない.

	//座標.
	INT_XY newPos = {
		gridPos.x + pos.x * gridSize.x,
		gridPos.y + pos.y * gridSize.y
	};
	//画像描画.
	int err = img.DrawGraphST(_dblXY(newPos), ANC_LU);
	return err; //-1: DrawGraphSTでエラー.
}