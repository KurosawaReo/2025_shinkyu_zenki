/*
   - myObjectST.cpp - (original)
   ver.2025/08/02

   DxLib: オリジナルオブジェクト機能の追加.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx等に入ってなければここで導入.
  #include "myDrawST.h"
#endif
#include "myObjectST.h"

//画像読み込み.
int Object::LoadGraphST(MY_STRING fileName) {
	return img.LoadGraphST(fileName);
}
int Object::LoadDivGraphST(MY_STRING fileName, INT_XY size, INT_XY cnt) {
	return img.LoadDivGraphST(fileName, size, cnt);
}

//オブジェクト(ObjectCir型)の描画.
int ObjectCir::Draw(int imgNo, BOOL isDrawHit) {

	//座標.
	INT_XY pos = {
		_int(cir.pos.x + offset.x),
		_int(cir.pos.y + offset.y)
	};
	//画像描画.
	int err = img.DrawGraphST(imgNo, pos, TRUE);
	if (err < 0) {
		return -1; //-1: DrawGraphSTでエラー.
	}
	//当たり判定表示.
	if (isDrawHit) {
		int err = DrawCircleST(&cir, FALSE, TRUE);
		if (err < 0) {
			return -2; //-2: DrawCircleSTでエラー.
		}
	}
	return 0; //正常終了.
}
//オブジェクト(ObjectBox型)の描画.
int ObjectBox::Draw(int imgNo, BOOL isDrawHit) {

	//座標.
	INT_XY pos = {
		_int(box.pos.x + offset.x),
		_int(box.pos.y + offset.y)
	};
	//画像描画.
	int err = img.DrawGraphST(imgNo, pos, TRUE);
	if (err < 0) {
		return -1; //-1: DrawGraphSTでエラー.
	}
	//当たり判定表示.
	if (isDrawHit) {
		int err = DrawBoxST(&box, TRUE, FALSE, TRUE);
		if (err < 0) {
			return -2; //-2: DrawBoxSTでエラー.
		}
	}
	return 0; //正常終了.
}
//オブジェクト(ObjectGrid型)の描画.
int ObjectGrid::Draw(int imgNo, INT_XY gridPos, INT_XY gridSize) {

	//座標.
	INT_XY pos{};
	pos = {
		gridPos.x + pos.x * gridSize.x,
		gridPos.y + pos.y * gridSize.y
	};
	//画像描画.
	int err = img.DrawGraphST(imgNo, pos, FALSE);
	return err; //-1: DrawGraphSTでエラー.
}