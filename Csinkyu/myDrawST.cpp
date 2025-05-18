/*
   - myDrawST.cpp - (original)
   ver.2025/05/18
   
   DxLibで使う用のオリジナル描画関数.
*/
#if !defined DEF_GLOBAL_H
#include "Global.h" //stdafxがなければここで定義.
#endif

#include "myDrawST.h"

//DrawCircleの改造版.
int DrawCircleST(const Circle* data, BOOL isFill, int thick) {

	int ret = DrawCircle(_int(data->pos.x), _int(data->pos.y), data->r, data->clr, isFill, thick);
	return ret;
}
//DrawBoxの改造版.
int DrawBoxST(const Box* data, BOOL isCenter, BOOL isFill) {

	double x1, x2, y1, y2;

	//中央基準かどうか.
	if (isCenter) {
		x1 = data->pos.x - data->size.x/2;
		x2 = data->pos.x + data->size.x/2;
		y1 = data->pos.y - data->size.y/2;
		y2 = data->pos.y + data->size.y/2;
	}
	else {
		x1 = data->pos.x;
		x2 = data->pos.x + data->size.x;
		y1 = data->pos.y;
		y2 = data->pos.y + data->size.y;
	}

	int ret = DrawBox(_int(x1), _int(y1), _int(x2), _int(y2), data->clr, isFill);
	return ret;
}
//DrawLineの改造版.
int DrawLineST(const Line* data, int thick) {

	int ret = DrawLine(
		_int(data->stPos.x), _int(data->stPos.y), 
		_int(data->edPos.x), _int(data->edPos.y), data->clr, thick
	);
	return ret;
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

//DrawRotaGraphの改造版.
int DrawRotaGraphST(const IMG_DRAW_ROTA* data) {

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

	int err = DrawRotaGraph(x, y, data->extend, data->ang, data->img.handle, data->isTrans);
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