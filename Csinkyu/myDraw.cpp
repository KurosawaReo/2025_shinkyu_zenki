/*
   - myDraw.cpp - (original)
   
   DxLibで使う用のオリジナル描画関数.
   ※STはstructの略.
*/
#if false
  #include "stdafx.h" //stdafxがあるならこっちを使う.
#else
  #define _USE_MATH_DEFINES //math定数を使うのに必要.
  #include <math.h>
  #include "DxLib.h"
#endif

#include "myDraw.h"

//int型変換マクロ.
#define _int(n) (int)(round(n))

//線の描画関数.
INT_XY DrawLineAng(INT_XY stPos, float ang, float len, int clr, int _thickness) {

	//角度をradに変換し、座標の計算.
	int y = _int(sin(ang * M_PI/180) * len);
	int x = _int(cos(ang * M_PI/180) * len);
	//終点座標.
	INT_XY edPos = { stPos.x+x, stPos.y+y };
	//始点から終点へ描画.
	DrawLine(stPos.x, stPos.y, edPos.x, edPos.y, clr, _thickness);

	return edPos; //終点座標を返す.
}

//LoadGraphの改造版.
int LoadGraphST(IMG* img, const TCHAR* fileName) {

	//画像読み込み.
	img->handle = LoadGraph(fileName);
	int ret = GetGraphSize(img->handle, &img->size.x, &img->size.y);
	
	if (img->handle == -1) {
		return -1; //-1: LoadGraphエラー.
	}
	if (ret == -1) {
		return -2; //-2: GetGraphSizeエラー.
	}
	return 0; //0: 正常終了.
}

//DrawGraphの改造版.
int DrawGraphST(const IMG_DRAW* img, BOOL isDrawCenter) {

	if (img->handle == 0) {
		return -2; //-2: handle未設定.
	}

	int x = img->pos.x;
	int y = img->pos.y;

	//中央座標モード.
	if (isDrawCenter) {
		x -= img->size.x / 2; //(size/2)ずらす.
		y -= img->size.y / 2;
	}

	int err = DrawGraph(x, y, img->handle, img->isTrans);
	return err; //-1: DrawGraphエラー.
}

//DrawRectGraphの改造版.
//Rect = 矩形(正方形や長方形のこと)
int DrawRectGraphST(const IMG_DRAW_RECT* img) {

	if (img->handle == 0) {
		return -2; //-2: handle未設定.
	}
	int err = DrawRectGraph(
		img->pos.x,   img->pos.y,
		img->stPxl.x, img->stPxl.y,
		img->size.x,  img->size.y,
		img->handle,  img->isTrans
	);
	return err; //-1: DrawRectGraphエラー.
}