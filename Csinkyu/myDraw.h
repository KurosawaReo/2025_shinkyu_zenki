/*
   - myDraw.cpp - (original)

   DxLibで使う用のオリジナル描画関数.
   ※STはstructの略.
*/
#pragma once

//画像データ格納用.
struct IMG
{
	int    handle;	//ハンドル.
	INT_XY size;	//画像のサイズ.
};
//画像描画に使う用.
struct IMG_DRAW
{
	INT_XY pos;     //画面のどこに描画するか.(左上座標基準)

	INT_XY size;    //画像のサイズ.

	int    handle;  //画像データ.
	BOOL   isTrans; //透過の可否.
};
struct IMG_DRAW_RECT
{
	INT_XY pos;     //画面のどこに描画するか.(左上座標基準)

	INT_XY stPxl;   //始点pixel.
	INT_XY size;    //切り取るサイズ.

	int    handle;  //画像データ.
	BOOL   isTrans; //透過の可否.
};

INT_XY DrawLineAng    (INT_XY pos, float ang, float len, int clr, int _thickness = 1);

int    LoadGraphST    (IMG* img, const TCHAR* fileName);
int    DrawGraphST    (const IMG_DRAW* img, BOOL isDrawCenter = FALSE);
int    DrawRectGraphST(const IMG_DRAW_RECT* img);