/*
   - myDrawST.cpp - (original)
   ver.2025/08/20
   
   DxLib: オリジナル描画機能の追加.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx等に入ってなければここで導入.
#endif
#include "myDrawST.h"

/*
   [終点の注意]

   DrawBox, DrawLine, DrawExtendGraphなどの終点を設定するものは
   始点から終点-1まで描画される仕様(その方が直感的だと作者は判断したそう)

   例: DrawBox(1, 1, 5, 5, color, FALSE)とした場合

   　１２３４５
   １■■■■
   ２■　　■
   ３■　　■
   ４■■■■
   ５
*/

//アンカー座標.
static const DBL_XY anchorPos[9] = {
	{0.0, 0.0}, {0.5, 0.0}, {1.0, 0.0},
	{0.0, 0.5}, {0.5, 0.5}, {1.0, 0.5},
	{0.0, 1.0}, {0.5, 1.0}, {1.0, 1.0}
};

// ▼*---=[ DrawImgST / DrawDivImgST ]=---*▼ //

//LoadGraphの改造版.
int DrawImgST::LoadGraphST(MY_STRING fileName) {

	//画像読み込み.
	data.handle = LoadGraph(fileName.c_str());
	int err = GetGraphSize(data.handle, &data.size.x, &data.size.y);
	
	_return(-1, data.handle < 0) //-1: LoadGraphエラー.
	_return(-2, err < 0)         //-2: GetGraphSizeエラー.
	return 0;                    // 0: 正常終了.
}
//LoadDivGraphの改造版.
int DrawDivImgST::LoadDivGraphST(MY_STRING fileName, INT_XY size, INT_XY cnt) {

	int* pHandle = new int[cnt.x*cnt.y]; //LoadDivGraphからハンドル取り出す用.

	//画像分割読み込み.
	int err = LoadDivGraph(fileName.c_str(), cnt.x*cnt.y, cnt.x, cnt.y, size.x, size.y, pHandle);
	_return(-1, err < 0) //-1: LoadDivGraphエラー.
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
int DrawImgST::DrawGraphST(DBL_XY pos, Anchor anc, bool isTrans, bool isFloat) {

	_return(-3, data.handle == 0) //-3: handle未設定.

	//float型かどうか.
	if (isFloat) {
		//基準点に座標をずらす.
		float x = (float)(pos.x - (data.size.x) * anchorPos[anc].x);
		float y = (float)(pos.y - (data.size.y) * anchorPos[anc].y);
		//描画.
		int err = DrawGraphF(x, y, data.handle, isTrans);
		_return(-1, err < 0) //-1: DrawGraphFエラー.
	}
	else {
		//基準点に座標をずらす.
		int x = (int)(pos.x - (data.size.x-1) * anchorPos[anc].x);
		int y = (int)(pos.y - (data.size.y-1) * anchorPos[anc].y);
		//描画.
		int err = DrawGraph(x, y, data.handle, isTrans);
		_return(-2, err < 0) //-2: DrawGraphエラー.
	}
	return 0; //正常終了.
}
int DrawDivImgST::DrawGraphST(int imgNo, DBL_XY pos, Anchor anc, bool isTrans, bool isFloat) {

	_return(-3, data[imgNo].handle == 0) //-3: handle未設定.

	//float型かどうか.
	if (isFloat) {
		//基準点に座標をずらす.
		float x = (float)(pos.x - (data[imgNo].size.x) * anchorPos[anc].x);
		float y = (float)(pos.y - (data[imgNo].size.y) * anchorPos[anc].y);
		//描画.
		int err = DrawGraphF(x, y, data[imgNo].handle, isTrans);
		_return(-1, err < 0) //-1: DrawGraphFエラー.
	}
	else {
		//基準点に座標をずらす.
		int x = (int)(pos.x - (data[imgNo].size.x-1) * anchorPos[anc].x);
		int y = (int)(pos.y - (data[imgNo].size.y-1) * anchorPos[anc].y);
		//描画.
		int err = DrawGraph(x, y, data[imgNo].handle, isTrans);
		_return(-2, err < 0) //-2: DrawGraphエラー.
	}
	return 0; //正常終了.
}

//DrawRectGraphの改造版.
//Rect = 矩形(正方形や長方形のこと)
int DrawImgST::DrawRectGraphST(DBL_XY pos, INT_XY stPixel, INT_XY size, bool isTrans, bool isFloat) {

	_return(-3, data.handle == 0) //-3: handle未設定.

	//float型かどうか.
	if (isFloat) {
		int err = DrawRectGraphF(
			(float)pos.x, (float)pos.y,	stPixel.x, stPixel.y, size.x, size.y, data.handle, isTrans
		);
		_return(-1, err < 0) //-1: DrawRectGraphFエラー.
	}
	else {
		int err = DrawRectGraph(
			_int(pos.x), _int(pos.y), stPixel.x, stPixel.y, size.x, size.y, data.handle, isTrans
		);
		_return(-2, err < 0) //-2: DrawRectGraphエラー.
	}
	return 0; //正常終了.
}
int DrawDivImgST::DrawRectGraphST(int imgNo, DBL_XY pos, INT_XY stPixel, INT_XY size, bool isTrans, bool isFloat) {

	_return(-3, data[imgNo].handle == 0) //-3: handle未設定.

	//float型かどうか.
	if (isFloat) {
		int err = DrawRectGraphF(
			(float)pos.x, (float)pos.y,	stPixel.x, stPixel.y, size.x, size.y, data[imgNo].handle, isTrans
		);
		_return(-1, err < 0) //-1: DrawRectGraphFエラー.
	}
	else {
		int err = DrawRectGraph(
			_int(pos.x), _int(pos.y), stPixel.x, stPixel.y, size.x, size.y, data[imgNo].handle, isTrans
		);
		_return(-2, err < 0) //-2: DrawRectGraphエラー.
	}
	return 0; //正常終了.
}

//DrawExtendGraphの改造版.
int DrawImgST::DrawExtendGraphST(DBL_XY pos, DBL_XY sizeRate, Anchor anc, bool isTrans, bool isFloat) {

	_return(-3, data.handle == 0) //-3: handle未設定.

	//float型かどうか.
	if (isFloat) {
		//始点を求める.
		float x1 = (float)(pos.x - (data.size.x * sizeRate.x) * anchorPos[anc].x);
		float y1 = (float)(pos.y - (data.size.y * sizeRate.y) * anchorPos[anc].y);
		//終点を求める.
		float x2 = (float)(x1 + data.size.x * sizeRate.x);
		float y2 = (float)(y1 + data.size.y * sizeRate.y);

		int err = DrawExtendGraphF(x1, y1, x2+1, y2+1, data.handle, isTrans);
		_return(-1, err < 0) //-1: DrawExtendGraphFエラー.
	}
	else {
		//始点を求める.
		int x1 = (int)(pos.x - ((data.size.x * sizeRate.x)-1) * anchorPos[anc].x);
		int y1 = (int)(pos.y - ((data.size.y * sizeRate.y)-1) * anchorPos[anc].y);
		//終点を求める.
		int x2 = (int)(x1 + ((data.size.x * sizeRate.x)-1));
		int y2 = (int)(y1 + ((data.size.y * sizeRate.y)-1));

		int err = DrawExtendGraph(x1, y1, x2+1, y2+1, data.handle, isTrans);
		_return(-2, err < 0) //-2: DrawExtendGraphエラー.
	}
	return 0; //正常終了.
}
int DrawDivImgST::DrawExtendGraphST(int imgNo, DBL_XY pos, DBL_XY sizeRate, Anchor anc, bool isTrans, bool isFloat) {

	_return(-3, data[imgNo].handle == 0) //-3: handle未設定.

	//float型かどうか.
	if (isFloat) {
		//始点を求める.
		float x1 = (float)(pos.x - (data[imgNo].size.x * sizeRate.x) * anchorPos[anc].x);
		float y1 = (float)(pos.y - (data[imgNo].size.y * sizeRate.y) * anchorPos[anc].y);
		//終点を求める.
		float x2 = (float)(x1 + data[imgNo].size.x * sizeRate.x);
		float y2 = (float)(y1 + data[imgNo].size.y * sizeRate.y);

		int err = DrawExtendGraphF(x1, y1, x2+1, y2+1, data[imgNo].handle, isTrans);
		_return(-1, err < 0) //-1: DrawExtendGraphFエラー.
	}
	else {
		//始点を求める.
		int x1 = (int)(pos.x - ((data[imgNo].size.x * sizeRate.x)-1) * anchorPos[anc].x);
		int y1 = (int)(pos.y - ((data[imgNo].size.y * sizeRate.y)-1) * anchorPos[anc].y);
		//終点を求める.
		int x2 = (int)(x1 + ((data[imgNo].size.x * sizeRate.x)-1));
		int y2 = (int)(y1 + ((data[imgNo].size.y * sizeRate.y)-1));

		int err = DrawExtendGraph(x1, y1, x2+1, y2+1, data[imgNo].handle, isTrans);
		_return(-2, err < 0) //-2: DrawExtendGraphエラー.
	}
	return 0; //正常終了.
}

//DrawRotaGraphの改造版.
int DrawImgST::DrawRotaGraphST(DBL_XY pos, double extend, double ang, Anchor anc, bool isTrans, bool isFloat) {

	_return(-3, data.handle == 0) //-3: handle未設定.

	//float型かどうか.
	if (isFloat) {
		//基準点に座標をずらす.
		float x = (float)(pos.x - (data.size.x-1) * anchorPos[anc].x);
		float y = (float)(pos.y - (data.size.y-1) * anchorPos[anc].y);
	
		int err = DrawRotaGraphF(x, y, extend, ang, data.handle, isTrans);
		_return(-1, err < 0) //-1: DrawRotaGraphFエラー.
	}
	else {
		//基準点に座標をずらす.
		int x = (int)(pos.x - (data.size.x-1) * anchorPos[anc].x);
		int y = (int)(pos.y - (data.size.y-1) * anchorPos[anc].y);
	
		int err = DrawRotaGraph(x, y, extend, ang, data.handle, isTrans);
		_return(-2, err < 0) //-2: DrawRotaGraphエラー.
	}
	return 0; //正常終了.
}
int DrawDivImgST::DrawRotaGraphST(int imgNo, DBL_XY pos, double extend, double ang, Anchor anc, bool isTrans, bool isFloat) {

	_return(-3, data[imgNo].handle == 0) //-3: handle未設定.

	//float型かどうか.
	if (isFloat) {
		//基準点に座標をずらす.
		float x = (float)(pos.x - (data[imgNo].size.x-1) * anchorPos[anc].x);
		float y = (float)(pos.y - (data[imgNo].size.y-1) * anchorPos[anc].y);
	
		int err = DrawRotaGraphF(x, y, extend, ang, data[imgNo].handle, isTrans);
		_return(-1, err < 0) //-1: DrawRotaGraphFエラー.
	}
	else {
		//基準点に座標をずらす.
		int x = (int)(pos.x - (data[imgNo].size.x-1) * anchorPos[anc].x);
		int y = (int)(pos.y - (data[imgNo].size.y-1) * anchorPos[anc].y);
	
		int err = DrawRotaGraph(x, y, extend, ang, data[imgNo].handle, isTrans);
		_return(-2, err < 0) //-2: DrawRotaGraphエラー.
	}
	return 0; //正常終了.
}

//DrawModiGraphの改造版.
int DrawImgST::DrawModiGraphST(DBL_XY luPos, DBL_XY ruPos, DBL_XY rdPos, DBL_XY ldPos, bool isTrans, bool isFloat) {
	
	_return(-3, data.handle == 0) //-3: handle未設定.

	//float型かどうか.
	if (isFloat) {
		int err = DrawModiGraphF(
			(float)luPos.x, (float)luPos.y, (float)ruPos.x, (float)ruPos.y, 
			(float)rdPos.x, (float)rdPos.y, (float)ldPos.x, (float)ldPos.y, data.handle, isTrans
		);
		_return(-1, err < 0) //-1: DrawModiGraphFエラー.
	}
	else {
		int err = DrawModiGraph(
			_int(luPos.x), _int(luPos.y), _int(ruPos.x), _int(ruPos.y),
			_int(rdPos.x), _int(rdPos.y), _int(ldPos.x), _int(ldPos.y), data.handle, isTrans
		);
		_return(-2, err < 0) //-2: DrawModiGraphエラー.
	}
	return 0; //正常終了.
}
int DrawDivImgST::DrawModiGraphST(int imgNo, DBL_XY luPos, DBL_XY ruPos, DBL_XY rdPos, DBL_XY ldPos, bool isTrans, bool isFloat) {

	_return(-3, data[imgNo].handle == 0) //-3: handle未設定.

	//float型かどうか.
	if (isFloat) {
		int err = DrawModiGraphF(
			(float)luPos.x, (float)luPos.y, (float)ruPos.x, (float)ruPos.y, 
			(float)rdPos.x, (float)rdPos.y, (float)ldPos.x, (float)ldPos.y, data[imgNo].handle, isTrans
		);
		_return(-1, err < 0) //-1: DrawModiGraphFエラー.
	}
	else {
		int err = DrawModiGraph(
			_int(luPos.x), _int(luPos.y), _int(ruPos.x), _int(ruPos.y),
			_int(rdPos.x), _int(rdPos.y), _int(ldPos.x), _int(ldPos.y), data[imgNo].handle, isTrans
		);
		_return(-2, err < 0) //-2: DrawModiGraphエラー.
	}
	return 0; //正常終了.
}

//DrawStringの改造版.
int DrawStrST::DrawStringST(Anchor anc, int font) {
	
	//基準点に座標をずらす.
	float x = (float)(data.pos.x - (GetTextSize(data.text, font).x-1) * anchorPos[anc].x);
	float y = (float)(data.pos.y - (GetTextSize(data.text, font).y-1) * anchorPos[anc].y);

	//デフォルトフォント.
	if (font < 0) {
		int err = DrawString((int)x, (int)y, data.text.c_str(), data.color);
		_return(-1, err < 0) //-1: DrawStringエラー.
	}
	//フォント設定あり.
	else {
		int err = DrawStringToHandle((int)x, (int)y, data.text.c_str(), data.color, font);
		_return(-2, err < 0) //-2: DrawStringToHandleエラー.
	}
	return 0; //正常終了.
}
//DrawRotaStringの改造版.
int DrawStrST::DrawRotaStringST(INT_XY extend, INT_XY pivot, double ang, bool isVertical, int font) {

	double rad = M_PI/180 * ang; //角度をラジアンに変換.

	//デフォルトフォント.
	if (font < 0) {
		int err = DrawRotaString(
			data.pos.x, data.pos.y, extend.x, extend.y, pivot.x, pivot.y,
			rad, data.color, 0, isVertical, data.text.c_str()
		);
		_return(-1, err < 0) //-1: DrawRotaStringエラー.
	}
	//フォント設定あり.
	else {
		int err = DrawRotaStringToHandle(
			data.pos.x, data.pos.y, extend.x, extend.y, pivot.x, pivot.y,
			rad, data.color, font, 0, isVertical, data.text.c_str()
		);
		_return(-2, err < 0) //-2 DrawRotaStringToHandleエラー.
	}
	return 0; //正常終了.
}
//DrawModiStringの改造版.
int DrawStrST::DrawModiStringST(INT_XY luPos, INT_XY ruPos, INT_XY rdPos, INT_XY ldPos, bool isVertical, int font) {

	//デフォルトフォント.
	if (font < 0) {
		int err = DrawModiString(
			luPos.x, luPos.y, ruPos.x, ruPos.y,
			rdPos.x, rdPos.y, ldPos.x, ldPos.y,
			data.color, 0, isVertical, data.text.c_str()
		);
		_return(-1, err < 0) //-1: DrawModiStringエラー.
	}
	//フォント設定あり.
	else {
		int err = DrawModiStringToHandle(
			luPos.x, luPos.y, ruPos.x, ruPos.y,
			rdPos.x, rdPos.y, ldPos.x, ldPos.y,
			data.color, font, 0, isVertical, data.text.c_str()
		);
		_return(-2, err < 0) //-2: DrawModiStringToHandleエラー.
	}
	return 0; //正常終了.
}

//テキストのサイズ取得.
INT_XY DrawStrST::GetTextSize(MY_STRING str, int font) {
	
	INT_XY size{};

	TCHAR name[256]{}; //無視.
	int   line{};      //無視.
	int   thick{};     //無視.

	//デフォルトフォント.
	if (font < 0) {
		GetDrawStringSize(&size.x, &size.y, &line, str.c_str(), 255);
	}
	//フォント設定あり.
	else {
		GetDrawStringSizeToHandle(&size.x, &size.y, &line, str.c_str(), 255, font);
		GetFontStateToHandle(name, &size.y, &thick, font); //size.yはフォントから取得.
	}

	return size;
}

// ▼*---=[ function ]=---*▼ //

//DrawCircleの改造版.
int DrawCircleST(const Circle* data, bool isFill, bool isAnti, float thick) {

	//アンチエイリアスあり.
	if (isAnti) {
		//posnum(角形数)は60に設定する.
		int err = DrawCircleAA((float)data->pos.x, (float)data->pos.y, data->r, 60, data->color, isFill, thick);
		_return(-1, err < 0) //-1: DrawCircleAAエラー.
	}
	//アンチエイリアスなし.
	else{
		int err = DrawCircle(_int(data->pos.x), _int(data->pos.y), _int(data->r), data->color, isFill, (int)thick);
		_return(-2, err < 0) //-2: DrawCircleエラー.
	}
	return 0; //正常終了.
}
//DrawBoxの改造版.
int DrawBoxST(const Box* data, Anchor anc, bool isFill, bool isAnti) {

	_return(-3, data->size.x <= 0.0 || data->size.y <= 0.0) //-3: サイズが0.0以下.

	//始点を求める.
	float x1 = (float)(data->pos.x - (data->size.x-1) * anchorPos[anc].x);
	float y1 = (float)(data->pos.y - (data->size.y-1) * anchorPos[anc].y);
	//終点を求める.
	float x2 = (float)(x1 + data->size.x-1);
	float y2 = (float)(y1 + data->size.y-1);

	//アンチエイリアスあり.
	if (isAnti) {
		int err = DrawBoxAA(x1, y1, x2+1, y2+1, data->color, isFill);
		_return(-1, err < 0) //-1: DrawBoxAAエラー.
	}
	//アンチエイリアスなし.
	else {
		int err = DrawBox((int)x1, (int)y1, (int)x2+1, (int)y2+1, data->color, isFill);
		_return(-2, err < 0) //-2: DrawBoxエラー.
	}
	return 0; //正常終了.
}
//DrawTriangleの改造版.
int DrawTriangleST(const Triangle* data, bool isFill, bool isAnti) {

	//アンチエイリアスあり.
	if (isAnti) {
		int err = DrawTriangleAA(
			(float)data->pos[0].x, (float)data->pos[0].y,
			(float)data->pos[1].x, (float)data->pos[1].y,
			(float)data->pos[2].x, (float)data->pos[2].y, data->color, isFill
		);
		_return(-1, err < 0) //-1: DrawTriangleAAエラー.
	}
	//アンチエイリアスなし.
	else {
		int err = DrawTriangle(
			_int(data->pos[0].x), _int(data->pos[0].y),
			_int(data->pos[1].x), _int(data->pos[1].y),
			_int(data->pos[2].x), _int(data->pos[2].y), data->color, isFill
		);
		_return(-2, err < 0) //-2: DrawTriangleエラー.
	}
	return 0; //正常終了.
}
//DrawLineの改造版.
int DrawLineST(const Line* data, bool isAnti, float thick) {

	//アンチエイリアスあり.
	if (isAnti) {
		int err = DrawLineAA(
			(float)data->stPos.x, (float)data->stPos.y,
			(float)data->edPos.x, (float)data->edPos.y, data->color, thick
		);
		_return(-1, err < 0) //-1: DrawLineAAエラー.
	}
	//アンチエイリアスなし.
	else {
		int err = DrawLine(
			_int(data->stPos.x), _int(data->stPos.y), 
			_int(data->edPos.x), _int(data->edPos.y), data->color, (int)thick
		);
		_return(-2, err < 0) //-2: DrawLineエラー.
	}
	return 0; //正常終了.
}
//画面全体にグリッド線を描画.
int DrawWindowGrid(int wid, int hei, int size, UINT clrWid, UINT clrHei) {

	//縦線の描画.
	for (int x = 0; x < wid; x += size) {

		Line line = { {(double)x, 0}, {(double)x, (double)hei}, clrHei };
		int err = DrawLineST(&line);
		_return(-1, err < 0) //-1: 縦線でエラー.
	}
	//横線の描画.
	for (int y = 0; y < hei; y += size) {

		Line line = { {0, (double)y}, {(double)wid, (double)y}, clrWid };
		int err = DrawLineST(&line);
		_return(-2, err < 0) //-2: 横線でエラー.
	}
	return 0; //正常終了.
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