/*
   - myObjectST.cpp - (original)
   ver.2025/08/03

   DxLib: オリジナルオブジェクト機能の追加.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx等に入ってなければここで導入.
  #include "myDrawST.h"
#endif
#include "myObjectST.h"

//オブジェクト(ObjectCir型)の描画.
int ObjectCir::Draw(bool isDrawHit) {

	if (!isActive) {
		return 0; //非アクティブなら描画しない.
	}

	//座標.
	INT_XY pos = {
		_int(cir.pos.x + offset.x),
		_int(cir.pos.y + offset.y)
	};
	//画像描画.
	int err = img.DrawGraphST(pos);
	if (err < 0) {
		return -1; //-1: DrawGraphSTでエラー.
	}
	//当たり判定表示.
	if (isDrawHit) {
		int err = DrawCircleST(&cir, false, true);
		if (err < 0) {
			return -2; //-2: DrawCircleSTでエラー.
		}
	}
	return 0; //正常終了.
}
//オブジェクト(ObjectBox型)の描画.
int ObjectBox::Draw(bool isDrawHit) {

	if (!isActive) {
		return 0; //非アクティブなら描画しない.
	}

	//座標.
	INT_XY pos = {
		_int(box.pos.x + offset.x),
		_int(box.pos.y + offset.y)
	};
	//画像描画.
	int err = img.DrawGraphST(pos);
	if (err < 0) {
		return -1; //-1: DrawGraphSTでエラー.
	}
	//当たり判定表示.
	if (isDrawHit) {
		int err = DrawBoxST(&box, ANC_MID, false, true);
		if (err < 0) {
			return -2; //-2: DrawBoxSTでエラー.
		}
	}
	return 0; //正常終了.
}
//オブジェクト(ObjectGrid型)の描画.
int ObjectGrid::Draw(INT_XY gridPos, INT_XY gridSize) {

	if (!isActive) {
		return 0; //非アクティブなら描画しない.
	}

	//座標.
	INT_XY newPos = {
		gridPos.x + pos.x * gridSize.x,
		gridPos.y + pos.y * gridSize.y
	};
	//画像描画.
	int err = img.DrawGraphST(newPos, ANC_LU);
	return err; //-1: DrawGraphSTでエラー.
}