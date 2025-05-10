/*
   - myDrawST.cpp - (original)
   
   DxLibで使う用のオリジナル描画関数.
*/
#if false
  #include "stdafx.h" //stdafxがあるならこっちを使う.
#else
  #define _USE_MATH_DEFINES //math定数を使うのに必要.
  #include <math.h>
  #include "DxLib.h"
#endif

#include "myDrawST.h"

//線の描画関数.
INT_XY DrawLineAng(INT_XY stPos, float ang, float len, int clr, int thick) {

	//角度をradに変換し、座標の計算.
	int y = _int(sin(ang * M_PI/180) * len);
	int x = _int(cos(ang * M_PI/180) * len);
	//終点座標.
	INT_XY edPos = { stPos.x+x, stPos.y+y };
	//始点から終点へ描画.
	DrawLine(stPos.x, stPos.y, edPos.x, edPos.y, clr, thick);

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
int DrawGraphST(const IMG_DRAW* data) {

	if (data->img.handle == 0) {
		return -2; //-2: handle未設定.
	}

	int x = data->pos.x;
	int y = data->pos.y;

	//中央座標モード.
	if (data->isCenter) {
		x -= data->img.size.x / 2; //(size/2)ずらす.
		y -= data->img.size.y / 2;
	}

	int err = DrawGraph(x, y, data->img.handle, data->isTrans);
	return err; //-1: DrawGraphエラー.
}

//DrawRectGraphの改造版.
//Rect = 矩形(正方形や長方形のこと)
int DrawRectGraphST(const IMG_DRAW_RECT* data) {

	if (data->img.handle == 0) {
		return -2; //-2: handle未設定.
	}
	int err = DrawRectGraph(
		data->pos.x,      data->pos.y,
		data->stPxl.x,    data->stPxl.y,
		data->size.x,     data->size.y,
		data->img.handle, data->isTrans
	);
	return err; //-1: DrawRectGraphエラー.
}

//DrawStringの改造版.
int DrawStringST(const STR_DRAW* data, int font) {
	
	int ret = 0;

	//デフォルトフォント.
	if (font < 0) {
		ret = DrawString(data->pos.x, data->pos.y, data->text, data->color);
	}
	//フォント設定あり.
	else {
		ret = DrawStringToHandle(data->pos.x, data->pos.y, data->text, data->color, font);
	}

	return ret;
}
//DrawRotaStringの改造版.
int DrawRotaStringST(const STR_DRAW_ROTA* data, int font) {

	int ret = 0;
	double rad = data->ang * M_PI/180; //角度をラジアンに変換.

	//デフォルトフォント.
	if (font < 0) {
		ret = DrawRotaString(
			data->pos.x,    data->pos.y,
			data->extend.x, data->extend.y,
			data->pivot.x,  data->pivot.y,
			rad, data->color, 0, data->isVertical, data->text
		);
	}
	//フォント設定あり.
	else {
		ret = DrawRotaStringToHandle(
			data->pos.x,    data->pos.y,
			data->extend.x, data->extend.y,
			data->pivot.x,  data->pivot.y,
			rad, data->color, font, 0, data->isVertical, data->text
		);
	}

	return ret;
}
//DrawModiStringの改造版.
int DrawModiStringST(const STR_DRAW_MODI* data, int font) {

	int ret = 0;

	//デフォルトフォント.
	if (font < 0) {
		ret = DrawModiString(
			data->luPos.x, data->luPos.y, data->ruPos.x, data->ruPos.y,
			data->rdPos.x, data->rdPos.y, data->ldPos.x, data->ldPos.y,
			data->color, 0, data->isVertical, data->text
		);
	}
	//フォント設定あり.
	else {
		ret = DrawModiStringToHandle(
			data->luPos.x, data->luPos.y, data->ruPos.x, data->ruPos.y,
			data->rdPos.x, data->rdPos.y, data->ldPos.x, data->ldPos.y,
			data->color, font, 0, data->isVertical,	data->text
		);
	}

	return ret;
}