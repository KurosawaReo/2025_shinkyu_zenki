/*
   - myDrawST.cpp - (original)
   ver.2025/07/27
   
   DxLib: オリジナル描画機能の追加.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx等に入ってなければここで導入.
#endif
#include "myDrawST.h"

/*
   [sizeについて]
   端から端までの長さをsizeとする.
   この時、始点座標+(size-1)と計算することに注意.
   中央基準の場合、(size-1)/2ずらせばok.

   １２３４
   ■■■■
   ■　　■
   ■　　■
   ■■■■
*/

//DrawCircleの改造版.
int DrawCircleST(const Circle* data, BOOL isFill, BOOL isAnti, float thick) {

	//アンチエイリアスあり.
	if (isAnti) {
		//posnum(角形数)は60に設定する.
		int err = DrawCircleAA((float)data->pos.x, (float)data->pos.y, data->r, 60, data->clr, isFill, thick);
		if (err < 0) {
			return -1; //-1: DrawCircleAAでエラー.
		}
	}
	//アンチエイリアスなし.
	else{
		int err = DrawCircle(_int(data->pos.x), _int(data->pos.y), _int(data->r), data->clr, isFill, (int)thick);
		if (err < 0) {
			return -2; //-2: DrawCircleでエラー.
		}
	}
	return 0; //正常終了.
}
//DrawBoxの改造版.
int DrawBoxST(const Box* data, BOOL isCenter, BOOL isFill, BOOL isAnti) {

	if (data->size.x <= 0 || data->size.y <= 0) {
		return -3; //-3: サイズが0以下.
	}

	double x1, x2, y1, y2;

	//中央基準かどうか.
	if (isCenter) {
		x1 = data->pos.x - (data->size.x-1)/2;
		y1 = data->pos.y - (data->size.y-1)/2;
		x2 = data->pos.x + (data->size.x-1)/2;
		y2 = data->pos.y + (data->size.y-1)/2;
	}
	else {
		x1 = data->pos.x;
		y1 = data->pos.y;
		x2 = data->pos.x + (data->size.x-1);
		y2 = data->pos.y + (data->size.y-1);
	}

	//アンチエイリアスあり.
	if (isAnti) {
		int err = DrawBoxAA((float)x1, (float)y1, (float)x2, (float)y2, data->clr, isFill);
		if (err < 0) {
			return -1; //-1: DrawBoxAAでエラー.
		}
	}
	//アンチエイリアスなし.
	else {
		int err = DrawBox(_int(x1), _int(y1), _int(x2), _int(y2), data->clr, isFill);
		if (err < 0) {
			return -2; //-2: DrawBoxでエラー.
		}
	}
	return 0; //正常終了.
}
//DrawTriangleの改造版.
int DrawTriangleST(const Triangle* data, BOOL isFill, BOOL isAnti) {

	//アンチエイリアスあり.
	if (isAnti) {
		int err = DrawTriangleAA(
			data->pos[0].x, data->pos[0].y,
			data->pos[1].x, data->pos[1].y,
			data->pos[2].x, data->pos[2].y, data->clr, isFill
		);
		if (err < 0) {
			return -1; //-1: DrawTriangleAAでエラー.
		}
	}
	//アンチエイリアスなし.
	else {
		int err = DrawTriangle(
			data->pos[0].x, data->pos[0].y,
			data->pos[1].x, data->pos[1].y,
			data->pos[2].x, data->pos[2].y, data->clr, isFill
		);
		if (err < 0) {
			return -2; //-2: DrawTriangleでエラー.
		}
	}
	return 0; //正常終了.
}
//DrawLineの改造版.
int DrawLineST(const Line* data, BOOL isAnti, float thick) {

	//アンチエイリアスあり.
	if (isAnti) {
		int err = DrawLineAA(
			(float)data->stPos.x, (float)data->stPos.y,
			(float)data->edPos.x, (float)data->edPos.y, data->clr, thick
		);
		if (err < 0) {
			return -1; //-1: DrawLineAAでエラー.
		}
	}
	//アンチエイリアスなし.
	else {
		int err = DrawLine(
			_int(data->stPos.x), _int(data->stPos.y), 
			_int(data->edPos.x), _int(data->edPos.y), data->clr, (int)thick
		);
		if (err < 0) {
			return -2; //-2: DrawLineでエラー.
		}
	}
	return 0; //正常終了.
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
	return 0; //正常終了.
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

	int* pHandle = new int[cnt.x*cnt.y]; //LoadDivGraphからハンドル取り出す用.
	vector<Image> tmpImg;                //仮保存用.

	//画像分割読み込み.
	int err = LoadDivGraph(fileName.c_str(), cnt.x*cnt.y, cnt.x, cnt.y, size.x, size.y, pHandle);
	if (err < 0) {
		return -1; //-1: LoadDivGraphエラー.
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

	return 0; //正常終了.
}

//DrawGraphの改造版.
int DrawGraphST(const DrawImg* data, BOOL isCenter, BOOL isTrans) {

	float x = (float)data->pos.x;
	float y = (float)data->pos.y;

	//中央座標モード.
	if (isCenter) {
		x -= (float)(data->img.size.x-1)/2;
		y -= (float)(data->img.size.y-1)/2;
	}

	if (data->img.handle == 0) {
		return -2; //-2: handle未設定.
	}
	int err = DrawGraph(_int(x), _int(y), data->img.handle, isTrans);
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

	float x1, y1, x2, y2;

	//中央基準かどうか.
	if (isCenter) {
		x1 = (float)(data->pos.x - (float)(data->img.size.x-1)/2 * data->sizeRate.x);
		y1 = (float)(data->pos.y - (float)(data->img.size.y-1)/2 * data->sizeRate.y);
		x2 = (float)(data->pos.x + (float)(data->img.size.x-1)/2 * data->sizeRate.x);
		y2 = (float)(data->pos.y + (float)(data->img.size.y-1)/2 * data->sizeRate.y);
	}
	else {
		x1 = (float)data->pos.x;
		y1 = (float)data->pos.y;
		x2 = (float)(data->pos.x + (data->img.size.x-1) * data->sizeRate.x);
		y2 = (float)(data->pos.y + (data->img.size.y-1) * data->sizeRate.y);
	}

	int err = DrawExtendGraph(_int(x1), _int(y1), _int(x2), _int(y2), data->img.handle, isTrans);
	return err; //-1: DrawExtendGraphエラー.
}
//DrawRotaGraphの改造版.
int DrawRotaGraphST(const DrawImgRota* data, BOOL isCenter, BOOL isTrans) {

	float x = (float)data->pos.x;
	float y = (float)data->pos.y;

	//中央座標モード.
	if (isCenter) {
		x -= (float)(data->img.size.x-1)/2;
		y -= (float)(data->img.size.y-1)/2;
	}

	if (data->img.handle == 0) {
		return -2; //-2: handle未設定.
	}
	int err = DrawRotaGraph(_int(x), _int(y), data->extend, data->ang, data->img.handle, isTrans);
	return err; //-1: DrawRotaGraphエラー.
}

//DrawStringの改造版.
int DrawStringST(const DrawStr* data, BOOL isCenter, int font) {
	
	float x = (float)data->pos.x;
	float y = (float)data->pos.y;

	//デフォルトフォント.
	if (font < 0) {
		//中央座標モード.
		if (isCenter) {
			x -= (float)(GetTextSize(data->text).x-1)/2;
			y -= (float)(GetTextSize(data->text).y-1)/2;
		}
		int err = DrawString(_int(x), _int(y), data->text, data->color);
		if (err < 0) {
			return -1; //-1: DrawStringでエラー.
		}
	}
	//フォント設定あり.
	else {
		//中央座標モード.
		if (isCenter) {
			x -= (float)(GetTextSize(data->text, font).x-1)/2;
			y -= (float)(GetTextSize(data->text, font).y-1)/2;
			printfDx(L"size:%d\n", GetTextSize(data->text, font).y);
			printfDx(L"x:%f y:%f\n", x, y);
		}
		int err = DrawStringToHandle(_int(x), _int(y), data->text, data->color, font);
		if (err < 0) {
			return -2; //-2: DrawStringToHandleでエラー.
		}
	}
	return 0; //正常終了.
}
//DrawRotaStringの改造版.
int DrawRotaStringST(const DrawStrRota* data, BOOL isVertical, int font) {

	double rad = _rad(data->ang); //角度をラジアンに変換.

	//デフォルトフォント.
	if (font < 0) {
		int err = DrawRotaString(
			data->pos.x,    data->pos.y,
			data->extend.x, data->extend.y,
			data->pivot.x,  data->pivot.y,
			rad, data->color, 0, isVertical, data->text
		);
		if (err < 0) {
			return -1; //-1: DrawRotaStringでエラー.
		}
	}
	//フォント設定あり.
	else {
		int err = DrawRotaStringToHandle(
			data->pos.x,    data->pos.y,
			data->extend.x, data->extend.y,
			data->pivot.x,  data->pivot.y,
			rad, data->color, font, 0, isVertical, data->text
		);
		if (err < 0) {
			return -2; //-2: DrawRotaStringToHandleでエラー.
		}
	}
	return 0; //正常終了.
}
//DrawModiStringの改造版.
int DrawModiStringST(const DrawStrModi* data, BOOL isVertical, int font) {

	//デフォルトフォント.
	if (font < 0) {
		int err = DrawModiString(
			data->luPos.x, data->luPos.y, data->ruPos.x, data->ruPos.y,
			data->rdPos.x, data->rdPos.y, data->ldPos.x, data->ldPos.y,
			data->color, 0, isVertical, data->text
		);
		if (err < 0) {
			return -1; //-1: DrawModiStringでエラー.
		}
	}
	//フォント設定あり.
	else {
		int err = DrawModiStringToHandle(
			data->luPos.x, data->luPos.y, data->ruPos.x, data->ruPos.y,
			data->rdPos.x, data->rdPos.y, data->ldPos.x, data->ldPos.y,
			data->color, font, 0, isVertical, data->text
		);
		if (err < 0) {
			return -2; //-2: DrawModiStringToHandleでエラー.
		}
	}
	return 0; //正常終了.
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
	size.y -= 2; //2pixelのずれがあるため調整.

	return size;
}

//フォント作成.
int CreateFontH(int size, int thick, FontTypeID fontId) {
	return CreateFontToHandle(NULL, size, thick, fontId);
}

//オブジェクト(ObjectCir型)の描画.
int DrawObjectCir(const ObjectCir* data, BOOL isDrawHit) {

	//画像設定.
	DrawImg draw = { data->img, {} };
	draw.pos.x = _int(data->cir.pos.x + data->offset.x);
	draw.pos.y = _int(data->cir.pos.y + data->offset.y);
	//画像描画.
	int err = DrawGraphST(&draw, TRUE);
	if (err < 0) {
		return -1; //-1: DrawGraphSTでエラー.
	}
	//当たり判定表示.
	if (isDrawHit) {
		int err = DrawCircleST(&data->cir, FALSE, TRUE);
		if (err < 0) {
			return -2; //-2: DrawCircleSTでエラー.
		}
	}
	return 0; //正常終了.
}
//オブジェクト(ObjectBox型)の描画.
int DrawObjectBox(const ObjectBox* data, BOOL isDrawHit) {

	//画像設定.
	DrawImg draw = { data->img, {} };
	draw.pos.x = _int(data->box.pos.x + data->offset.x);
	draw.pos.y = _int(data->box.pos.y + data->offset.y);
	//画像描画.
	int err = DrawGraphST(&draw, TRUE);
	if (err < 0) {
		return -1; //-1: DrawGraphSTでエラー.
	}
	//当たり判定表示.
	if (isDrawHit) {
		int err = DrawBoxST(&data->box, TRUE, FALSE, TRUE);
		if (err < 0) {
			return -2; //-2: DrawBoxSTでエラー.
		}
	}
	return 0; //正常終了.
}
//オブジェクト(ObjectGrid型)の描画.
int DrawObjectGrid(const ObjectGrid* data, INT_XY gridPos, INT_XY gridSize) {

	//画像設定.
	DrawImg draw = { data->img, {} };
	draw.pos.x = gridPos.x + data->pos.x * gridSize.x;
	draw.pos.y = gridPos.y + data->pos.y * gridSize.y;
	//画像描画.
	int err = DrawGraphST(&draw, FALSE);
	return err; //-1: DrawGraphSTでエラー.
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