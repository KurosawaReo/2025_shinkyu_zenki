/*
   - myDrawST.cpp - (original)
   ver.2025/08/03
   
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

//アンカー座標.
static const DBL_XY anchorPos[9] = {
	{0.0, 0.0}, {0.5, 0.0}, {1.0, 0.0},
	{0.0, 0.5}, {0.5, 0.5}, {1.0, 0.5},
	{0.0, 1.0}, {0.5, 1.0}, {1.0, 1.0}
};

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
int DrawBoxST(const Box* data, Anchor anc, BOOL isFill, BOOL isAnti) {

	if (data->size.x <= 0 || data->size.y <= 0) {
		return -3; //-3: サイズが0以下.
	}

	//始点を求める.
	float x1 = (float)(data->pos.x - (data->size.x-1) * anchorPos[anc].x);
	float y1 = (float)(data->pos.y - (data->size.y-1) * anchorPos[anc].y);
	//終点を求める.
	float x2 = (float)(data->pos.x + (data->size.x-1) * (1-anchorPos[anc].x));
	float y2 = (float)(data->pos.y + (data->size.y-1) * (1-anchorPos[anc].y));

	//アンチエイリアスあり.
	if (isAnti) {
		int err = DrawBoxAA(x1, y1, x2, y2, data->clr, isFill);
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
			(float)data->pos[0].x, (float)data->pos[0].y,
			(float)data->pos[1].x, (float)data->pos[1].y,
			(float)data->pos[2].x, (float)data->pos[2].y, data->clr, isFill
		);
		if (err < 0) {
			return -1; //-1: DrawTriangleAAでエラー.
		}
	}
	//アンチエイリアスなし.
	else {
		int err = DrawTriangle(
			_int(data->pos[0].x), _int(data->pos[0].y),
			_int(data->pos[1].x), _int(data->pos[1].y),
			_int(data->pos[2].x), _int(data->pos[2].y), data->clr, isFill
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
int DrawImgST::LoadGraphST(MY_STRING fileName) {

	//画像読み込み.
	data.handle = LoadGraph(fileName.c_str());
	int err = GetGraphSize(data.handle, &data.size.x, &data.size.y);
	
	if (data.handle < 0) {
		return -1; //-1: LoadGraphエラー.
	}
	if (err < 0) {
		return -2; //-2: GetGraphSizeエラー.
	}
	return 0; //正常終了.
}
//LoadDivGraphの改造版.
int DrawDivImgST::LoadDivGraphST(MY_STRING fileName, INT_XY size, INT_XY cnt) {

	int* pHandle = new int[cnt.x*cnt.y]; //LoadDivGraphからハンドル取り出す用.

	//画像分割読み込み.
	int err = LoadDivGraph(fileName.c_str(), cnt.x*cnt.y, cnt.x, cnt.y, size.x, size.y, pHandle);
	if (err < 0) {
		return -1; //-1: LoadDivGraphエラー.
	}
	//Image型配列のサイズを分割数に合わせる.
	data.resize(cnt.x*cnt.y);
	//分割数だけループ.
	for (int i = 0; i < cnt.y; i++) {
		for (int j = 0; j < cnt.x; j++) {
			data[j+i*cnt.x].handle = pHandle[j+i*cnt.x]; //ハンドル保存.
			data[j+i*cnt.x].size   = size;               //サイズ保存.
		}
	}

	//配列破棄.
	delete[] pHandle; pHandle = nullptr;

	return 0; //正常終了.
}

//DrawGraphの改造版.
int DrawImgST::DrawGraphST(INT_XY pos, Anchor anc, BOOL isTrans) {

	//基準点に座標をずらす.
	float x = (float)(pos.x - (data.size.x-1) * anchorPos[anc].x);
	float y = (float)(pos.y - (data.size.y-1) * anchorPos[anc].y);

	if (data.handle == 0) {
		return -2; //-2: handle未設定.
	}
	int err = DrawGraph(_int(x), _int(y), data.handle, isTrans);
	return err; //-1: DrawGraphエラー.
}
int DrawDivImgST::DrawGraphST(int imgNo, INT_XY pos, Anchor anc, BOOL isTrans) {

	//基準点に座標をずらす.
	float x = (float)(pos.x - (data[imgNo].size.x-1) * anchorPos[anc].x);
	float y = (float)(pos.y - (data[imgNo].size.y-1) * anchorPos[anc].y);

	if (data[imgNo].handle == 0) {
		return -2; //-2: handle未設定.
	}
	int err = DrawGraph(_int(x), _int(y), data[imgNo].handle, isTrans);
	return err; //-1: DrawGraphエラー.
}
//DrawRectGraphの改造版.
//Rect = 矩形(正方形や長方形のこと)
int DrawImgST::DrawRectGraphST(INT_XY pos, INT_XY stPos, INT_XY size, BOOL isTrans) {

	if (data.handle == 0) {
		return -2; //-2: handle未設定.
	}
	int err = DrawRectGraph(
		pos.x, pos.y, stPos.x, stPos.y, size.x, size.y,
		data.handle, isTrans
	);
	return err; //-1: DrawRectGraphエラー.
}
int DrawDivImgST::DrawRectGraphST(int imgNo, INT_XY pos, INT_XY stPos, INT_XY size, BOOL isTrans) {

	if (data[imgNo].handle == 0) {
		return -2; //-2: handle未設定.
	}
	int err = DrawRectGraph(
		pos.x, pos.y, stPos.x, stPos.y, size.x, size.y,
		data[imgNo].handle, isTrans
	);
	return err; //-1: DrawRectGraphエラー.
}
//DrawExtendGraphの改造版.
int DrawImgST::DrawExtendGraphST(INT_XY pos, DBL_XY sizeRate, Anchor anc, BOOL isTrans) {

	//始点を求める.
	float x1 = (float)(pos.x - (data.size.x-1) * anchorPos[anc].x * sizeRate.x);
	float y1 = (float)(pos.y - (data.size.y-1) * anchorPos[anc].y * sizeRate.y);
	//終点を求める.
	float x2 = (float)(pos.x + (data.size.x-1) * (1-anchorPos[anc].x) * sizeRate.x);
	float y2 = (float)(pos.y + (data.size.y-1) * (1-anchorPos[anc].y) * sizeRate.y);

	int err = DrawExtendGraph(_int(x1), _int(y1), _int(x2), _int(y2), data.handle, isTrans);
	return err; //-1: DrawExtendGraphエラー.
}
int DrawDivImgST::DrawExtendGraphST(int imgNo, INT_XY pos, DBL_XY sizeRate, Anchor anc, BOOL isTrans) {

	//始点を求める.
	float x1 = (float)(pos.x - (data[imgNo].size.x-1) * anchorPos[anc].x * sizeRate.x);
	float y1 = (float)(pos.y - (data[imgNo].size.y-1) * anchorPos[anc].y * sizeRate.y);
	//終点を求める.
	float x2 = (float)(pos.x + (data[imgNo].size.x-1) * (1-anchorPos[anc].x) * sizeRate.x);
	float y2 = (float)(pos.y + (data[imgNo].size.y-1) * (1-anchorPos[anc].y) * sizeRate.y);

	int err = DrawExtendGraph(_int(x1), _int(y1), _int(x2), _int(y2), data[imgNo].handle, isTrans);
	return err; //-1: DrawExtendGraphエラー.
}
//DrawRotaGraphの改造版.
int DrawImgST::DrawRotaGraphST(INT_XY pos, double extend, double ang, Anchor anc, BOOL isTrans) {

	//基準点に座標をずらす.
	float x = (float)(pos.x - (data.size.x-1) * anchorPos[anc].x);
	float y = (float)(pos.y - (data.size.y-1) * anchorPos[anc].y);

	if (data.handle == 0) {
		return -2; //-2: handle未設定.
	}
	int err = DrawRotaGraph(_int(x), _int(y),extend, ang, data.handle, isTrans);
	return err; //-1: DrawRotaGraphエラー.
}
int DrawDivImgST::DrawRotaGraphST(int imgNo, INT_XY pos, double extend, double ang, Anchor anc, BOOL isTrans) {

	//基準点に座標をずらす.
	float x = (float)(pos.x - (data[imgNo].size.x-1) * anchorPos[anc].x);
	float y = (float)(pos.y - (data[imgNo].size.y-1) * anchorPos[anc].y);

	if (data[imgNo].handle == 0) {
		return -2; //-2: handle未設定.
	}
	int err = DrawRotaGraph(_int(x), _int(y),extend, ang, data[imgNo].handle, isTrans);
	return err; //-1: DrawRotaGraphエラー.
}

//DrawStringの改造版.
int DrawStrST::DrawStringST(Anchor anc, int font) {
	
	//基準点に座標をずらす.
	float x = (float)(data.pos.x - (GetTextSize(data.text, font).x-1) * anchorPos[anc].x);
	float y = (float)(data.pos.y - (GetTextSize(data.text, font).y-1) * anchorPos[anc].y);

	//デフォルトフォント.
	if (font < 0) {
		int err = DrawString(_int(x), _int(y), data.text.c_str(), data.clr);
		if (err < 0) {
			return -1; //-1: DrawStringでエラー.
		}
	}
	//フォント設定あり.
	else {
		int err = DrawStringToHandle(_int(x), _int(y), data.text.c_str(), data.clr, font);
		if (err < 0) {
			return -2; //-2: DrawStringToHandleでエラー.
		}
	}
	return 0; //正常終了.
}
//DrawRotaStringの改造版.
int DrawStrST::DrawRotaStringST(INT_XY extend, INT_XY pivot, double ang, BOOL isVertical, int font) {

	double rad = _rad(ang); //角度をラジアンに変換.

	//デフォルトフォント.
	if (font < 0) {
		int err = DrawRotaString(
			data.pos.x, data.pos.y, extend.x, extend.y, pivot.x, pivot.y,
			rad, data.clr, 0, isVertical, data.text.c_str()
		);
		if (err < 0) {
			return -1; //-1: DrawRotaStringでエラー.
		}
	}
	//フォント設定あり.
	else {
		int err = DrawRotaStringToHandle(
			data.pos.x, data.pos.y, extend.x, extend.y, pivot.x, pivot.y,
			rad, data.clr, font, 0, isVertical, data.text.c_str()
		);
		if (err < 0) {
			return -2; //-2: DrawRotaStringToHandleでエラー.
		}
	}
	return 0; //正常終了.
}
//DrawModiStringの改造版.
int DrawStrST::DrawModiStringST(INT_XY luPos, INT_XY ruPos, INT_XY rdPos, INT_XY ldPos, BOOL isVertical, int font) {

	//デフォルトフォント.
	if (font < 0) {
		int err = DrawModiString(
			luPos.x, luPos.y, ruPos.x, ruPos.y,
			rdPos.x, rdPos.y, ldPos.x, ldPos.y,
			data.clr, 0, isVertical, data.text.c_str()
		);
		if (err < 0) {
			return -1; //-1: DrawModiStringでエラー.
		}
	}
	//フォント設定あり.
	else {
		int err = DrawModiStringToHandle(
			luPos.x, luPos.y, ruPos.x, ruPos.y,
			rdPos.x, rdPos.y, ldPos.x, ldPos.y,
			data.clr, font, 0, isVertical, data.text.c_str()
		);
		if (err < 0) {
			return -2; //-2: DrawModiStringToHandleでエラー.
		}
	}
	return 0; //正常終了.
}

//テキストのサイズ取得.
INT_XY DrawStrST::GetTextSize(MY_STRING str, int font) {
	
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