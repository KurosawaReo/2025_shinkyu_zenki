/*
   - myDrawST.cpp - (original)
   ver.2025/07/26
   
   DxLib: オリジナル描画機能の追加.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx等に入ってなければここで導入.
#endif
#include "myDrawST.h"

//DrawCircleの改造版.
int DrawCircleST(const Circle* data, BOOL isFill, BOOL isAnti, float thick) {

	int ret;
	//アンチエイリアスあり.
	if (isAnti) {
		//posnum(角形数)は60に設定する.
		ret = DrawCircleAA((float)data->pos.x, (float)data->pos.y, data->r, 60, data->clr, isFill, thick);
	}
	//アンチエイリアスなし.
	else{
		ret = DrawCircle(_int(data->pos.x), _int(data->pos.y), _int(data->r), data->clr, isFill, (int)thick);
	}
	return ret;
}
//DrawBoxの改造版.
int DrawBoxST(const Box* data, BOOL isCenter, BOOL isFill, BOOL isAnti) {

	int ret;
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

	//アンチエイリアスあり.
	if (isAnti) {
		ret = DrawBoxAA((float)x1, (float)y1, (float)x2, (float)y2, data->clr, isFill);
	}
	//アンチエイリアスなし.
	else {
		ret = DrawBox(_int(x1), _int(y1), _int(x2), _int(y2), data->clr, isFill);
	}
	return ret;
}
//DrawTriangleの改造版.
int DrawTriangleST(const Triangle* data, BOOL isFill, BOOL isAnti) {

	int ret;
	//アンチエイリアスあり.
	if (isAnti) {
		ret = DrawTriangleAA(
			data->pos[0].x, data->pos[0].y,
			data->pos[1].x, data->pos[1].y,
			data->pos[2].x, data->pos[2].y, data->clr, isFill
		);
	}
	//アンチエイリアスなし.
	else {
		ret = DrawTriangle(
			data->pos[0].x, data->pos[0].y,
			data->pos[1].x, data->pos[1].y,
			data->pos[2].x, data->pos[2].y, data->clr, isFill
		);
	}
	return ret;
}
//DrawLineの改造版.
int DrawLineST(const Line* data, BOOL isAnti, float thick) {

	int ret;
	//アンチエイリアスあり.
	if (isAnti) {
		ret = DrawLineAA(
			(float)data->stPos.x, (float)data->stPos.y,
			(float)data->edPos.x, (float)data->edPos.y, data->clr, thick
		);
	}
	//アンチエイリアスなし.
	else {
		ret = DrawLine(
			_int(data->stPos.x), _int(data->stPos.y), 
			_int(data->edPos.x), _int(data->edPos.y), data->clr, (int)thick
		);
	}
	return ret;
}
//画面全体にグリッド線を描画.
int DrawWindowGrid(int wid, int hei, int size, UINT clrWid, UINT clrHei) {

	//縦線の描画.
	for (int x = 0; x < wid; x += size) {

		Line line = { {(double)x, 0}, {(double)x, (double)hei}, clrHei };
		int err = DrawLineST(&line);
		if (err < 0) {
			return -1; //-1: 縦線でエラー.
		}
	}
	//横線の描画.
	for (int y = 0; y < hei; y += size) {

		Line line = { {0, (double)y}, {(double)wid, (double)y}, clrWid };
		int err = DrawLineST(&line);
		if (err < 0) {
			return -2; //-2: 横線でエラー.
		}
	}

	return 0;
}

//LoadGraphの改造版.
int LoadGraphST(Image* img, my_string fileName) {

	//画像読み込み.
	img->handle = LoadGraph(fileName.c_str());
	int err = GetGraphSize(img->handle, &img->size.x, &img->size.y);
	
	if (img->handle < 0) {
		return -1; //-1: LoadGraphエラー.
	}
	if (err < 0) {
		return -2; //-2: GetGraphSizeエラー.
	}
	return 0; //正常終了.
}
//LoadDivGraphの改造版.
int LoadDivGraphST(vector<Image>* img, my_string fileName, INT_XY size, INT_XY cnt) {

	int ret = 0; //エラー値.

	int* pHandle = new int[cnt.x*cnt.y]; //LoadDivGraphからハンドル取り出す用.
	vector<Image> tmpImg;                //仮保存用.

	//画像分割読み込み.
	int err = LoadDivGraph(fileName.c_str(), cnt.x*cnt.y, cnt.x, cnt.y, size.x, size.y, pHandle);
	if (err < 0) {
		ret = -1; //-1: LoadDivGraphエラー.
	}
	//IMG型配列のサイズを分割数に合わせる.
	tmpImg.resize(cnt.x*cnt.y);
	//分割数だけループ.
	for (int i = 0; i < cnt.y; i++) {
		for (int j = 0; j < cnt.x; j++) {
			tmpImg[j+i*cnt.x].handle = pHandle[j+i*cnt.x]; //ハンドル保存.
			tmpImg[j+i*cnt.x].size   = size;               //サイズ保存.
		}
	}

	//引数のIMG型配列にデータを渡す.
	*img = tmpImg;
	//配列破棄.
	delete[] pHandle; pHandle = nullptr;

	return ret;
}

//DrawGraphの改造版.
int DrawGraphST(const DrawImg* data, BOOL isCenter, BOOL isTrans) {

	int x = data->pos.x;
	int y = data->pos.y;

	//中央座標モード.
	if (isCenter) {
		x -= data->img.size.x / 2; //(size/2)ずらす.
		y -= data->img.size.y / 2;
	}

	if (data->img.handle == 0) {
		return -2; //-2: handle未設定.
	}
	int err = DrawGraph(x, y, data->img.handle, isTrans);
	return err; //-1: DrawGraphエラー.
}
//DrawRectGraphの改造版.
//Rect = 矩形(正方形や長方形のこと)
int DrawRectGraphST(const DrawImgRect* data, BOOL isTrans) {

	if (data->img.handle == 0) {
		return -2; //-2: handle未設定.
	}
	int err = DrawRectGraph(
		data->pos.x,      data->pos.y,
		data->stPxl.x,    data->stPxl.y,
		data->size.x,     data->size.y,
		data->img.handle, isTrans
	);
	return err; //-1: DrawRectGraphエラー.
}
//DrawExtendGraphの改造版.
int DrawExtendGraphST(const DrawImgExtend* data, BOOL isCenter, BOOL isTrans) {

	INT_XY pos1, pos2;

	//中央基準かどうか.
	if (isCenter) {
		pos1.x = data->pos.x - data->size.x/2;
		pos1.y = data->pos.y - data->size.y/2;
		pos2.x = data->pos.x + data->size.x/2;
		pos2.y = data->pos.y + data->size.y/2;
	}
	else {
		pos1   = data->pos;
		pos2.x = data->pos.x + data->size.x;
		pos2.y = data->pos.y + data->size.y;
	}

	int err = DrawExtendGraph(pos1.x, pos1.y, pos2.x, pos2.y, data->img.handle, isTrans);
	return err; //-1: DrawExtendGraphエラー.
}
//DrawRotaGraphの改造版.
int DrawRotaGraphST(const DrawImgRota* data, BOOL isCenter, BOOL isTrans) {

	int x = data->pos.x;
	int y = data->pos.y;

	//中央座標モード.
	if (isCenter) {
		x -= data->img.size.x / 2; //(size/2)ずらす.
		y -= data->img.size.y / 2;
	}

	if (data->img.handle == 0) {
		return -2; //-2: handle未設定.
	}
	int err = DrawRotaGraph(x, y, data->extend, data->ang, data->img.handle, isTrans);
	return err; //-1: DrawRotaGraphエラー.
}

//DrawStringの改造版.
int DrawStringST(const DrawStr* data, BOOL isCenter, int font) {
	
	int err = 0;
	int x = data->pos.x;
	int y = data->pos.y;

	//デフォルトフォント.
	if (font < 0) {
		//中央座標モード.
		if (isCenter) {
			x = data->pos.x - GetTextSize(data->text).x/2;
			y = data->pos.y - GetTextSize(data->text).y/2;
		}
		err = DrawString(x, y, data->text, data->color);
	}
	//フォント設定あり.
	else {
		//中央座標モード.
		if (isCenter) {
			x = data->pos.x - GetTextSize(data->text, font).x/2;
			y = data->pos.y - GetTextSize(data->text, font).y/2;
		}
		err = DrawStringToHandle(x, y, data->text, data->color, font);
	}

	return err;
}
//DrawRotaStringの改造版.
int DrawRotaStringST(const DrawStrRota* data, BOOL isVertical, int font) {

	int err = 0;
	double rad = data->ang * M_PI/180; //角度をラジアンに変換.

	//デフォルトフォント.
	if (font < 0) {
		err = DrawRotaString(
			data->pos.x,    data->pos.y,
			data->extend.x, data->extend.y,
			data->pivot.x,  data->pivot.y,
			rad, data->color, 0, isVertical, data->text
		);
	}
	//フォント設定あり.
	else {
		err = DrawRotaStringToHandle(
			data->pos.x,    data->pos.y,
			data->extend.x, data->extend.y,
			data->pivot.x,  data->pivot.y,
			rad, data->color, font, 0, isVertical, data->text
		);
	}

	return err;
}
//DrawModiStringの改造版.
int DrawModiStringST(const DrawStrModi* data, BOOL isVertical, int font) {

	int err = 0;

	//デフォルトフォント.
	if (font < 0) {
		err = DrawModiString(
			data->luPos.x, data->luPos.y, data->ruPos.x, data->ruPos.y,
			data->rdPos.x, data->rdPos.y, data->ldPos.x, data->ldPos.y,
			data->color, 0, isVertical, data->text
		);
	}
	//フォント設定あり.
	else {
		err = DrawModiStringToHandle(
			data->luPos.x, data->luPos.y, data->ruPos.x, data->ruPos.y,
			data->rdPos.x, data->rdPos.y, data->ldPos.x, data->ldPos.y,
			data->color, font, 0, isVertical, data->text
		);
	}

	return err;
}

//テキストのサイズ取得.
INT_XY GetTextSize(my_string str, int font) {
	
	INT_XY size{};
	int    line{}; //無視.

	//デフォルトフォント.
	if (font < 0) {
		GetDrawStringSize(&size.x, &size.y, &line, str.c_str(), 255);
	}
	//フォント設定あり.
	else {
		GetDrawStringSizeToHandle(&size.x, &size.y, &line, str.c_str(), 255, font);
	}

	return size;
}

//フォント作成.
int CreateFontH(int size, int thick, FontTypeID fontId) {
	return CreateFontToHandle(NULL, size, thick, fontId);
}

//オブジェクト(ObjectCir型)の描画.
int DrawObjectCir(const ObjectCir* data, BOOL isDrawHit) {

	int err = 0;

	//画像設定.
	DrawImg draw = { data->img, {} };
	draw.pos.x = _int(data->cir.pos.x + data->offset.x);
	draw.pos.y = _int(data->cir.pos.y + data->offset.y);
	//画像描画.
	err = DrawGraphST(&draw, TRUE);
	if (err < 0) {
		return -1; //-1: DrawGraphSTでエラー.
	}
	//当たり判定表示.
	if (isDrawHit) {
		err = DrawCircleST(&data->cir, FALSE, TRUE);
		if (err < 0) {
			return -2; //-2: DrawCircleSTでエラー.
		}
	}
	return 0; //正常終了.
}
//オブジェクト(ObjectBox型)の描画.
int DrawObjectBox(const ObjectBox* data, BOOL isDrawHit) {

	int err = 0;

	//画像設定.
	DrawImg draw = { data->img, {} };
	draw.pos.x = _int(data->box.pos.x + data->offset.x);
	draw.pos.y = _int(data->box.pos.y + data->offset.y);
	//画像描画.
	err = DrawGraphST(&draw, TRUE);
	if (err < 0) {
		return -1; //-1: DrawGraphSTでエラー.
	}
	//当たり判定表示.
	if (isDrawHit) {
		err = DrawBoxST(&data->box, TRUE, FALSE, TRUE);
		if (err < 0) {
			return -2; //-2: DrawBoxSTでエラー.
		}
	}
	return 0; //正常終了.
}
//オブジェクト(ObjectGrid型)の描画.
int DrawObjectGrid(const ObjectGrid* data, INT_XY gridPos, INT_XY gridSize) {

	int err = 0;

	//画像設定.
	DrawImg draw = { data->img, {} };
	draw.pos.x = gridPos.x + data->pos.x * gridSize.x;
	draw.pos.y = gridPos.y + data->pos.y * gridSize.y;
	//画像描画.
	err = DrawGraphST(&draw, FALSE);
	if (err < 0) {
		return -1; //-1: DrawGraphSTでエラー.
	}
	return 0; //正常終了.
}

//描画モード変更.
int SetDrawBlendModeST(BlendModeID id, int power) {
	return SetDrawBlendMode(id, power);
}
int SetDrawBlendModeST(BlendModeID id, double power) {
	return SetDrawBlendMode(id, _int(power));
}
//描画モードリセット.
int ResetDrawBlendMode() {
	return SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}