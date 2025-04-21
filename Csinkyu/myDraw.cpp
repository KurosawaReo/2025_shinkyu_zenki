/*
   - myDraw.cpp - (original)
   
   DxLibで使う用のオリジナル描画関数.
   ※STはstructの略.
*/
#include "stdafx.h" //stdafxがあるならこっちを使う
#include "myDraw.h"

//int型変換マクロ.
#define _int(n) (int)(round(n))

//線の描画関数.
INT_XY DrawLineAng(INT_XY stPos, float ang, float len, int clr) {

	//角度をradに変換し、座標の計算.
	int y = _int(sin(ang * M_PI/180) * len);
	int x = _int(cos(ang * M_PI/180) * len);
	//終点座標.
	INT_XY edPos = { stPos.x+x, stPos.y+y };
	//始点から終点へ描画.
	DrawLine(stPos.x, stPos.y, edPos.x, edPos.y, clr);

	return edPos; //終点座標を返す.
}

//DrawGraphの改造版.
int DrawGraphST(const IMG_DRAW* img, BOOL isDrawCenter) {

	int x = img->pos.x;
	int y = img->pos.y;

	//中央座標モード.
	if (isDrawCenter) {
		x -= img->size.x / 2; //(size/2)ずらす.
		y -= img->size.y / 2;
	}

	if (img->handle == 0) {
		return -2; //-2:handle未設定.
	}
	int err = DrawGraph(x, y, img->handle, img->isTrans);
	return err; //-1:DrawGraphエラー.
}
//DrawRectGraphの改造版.
int DrawRectGraphST(const IMG_DRAW_RECT* img) {

	//Rect = 矩形(正方形や長方形のこと)

	if (img->handle == 0) {
		return -2; //-2:handle未設定.
	}
	int err = DrawRectGraph(
		img->pos.x,   img->pos.y,
		img->stPxl.x, img->stPxl.y,
		img->size.x,  img->size.y,
		img->handle,  img->isTrans
	);
	return err; //-1:DrawRectGraphエラー.
}