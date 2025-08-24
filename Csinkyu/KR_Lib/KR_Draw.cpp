/*
   - KR_Draw.cpp - (DxLib)
   ver: 2025/08/24

   描画機能を追加します.
   (オブジェクト指向ver → KR_Object)
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.hに入ってなければここで導入.
  using namespace KR_Lib;
#endif
#include "KR_Draw.h"

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

//KR_Libに使う用.
namespace KR_Lib
{
	constexpr int NONE_HANDLE = 0; //ハンドルなし.

	//アンカー座標.
	static const DBL_XY ANCHOR_POS[9] = {
		{0.0, 0.0}, {0.5, 0.0}, {1.0, 0.0},
		{0.0, 0.5}, {0.5, 0.5}, {1.0, 0.5},
		{0.0, 1.0}, {0.5, 1.0}, {1.0, 1.0}
	};

// ▼*---=[ DrawImgST / DrawDivImgST ]=---*▼ //

	//constructor, destructor.
	DrawImg::DrawImg() {
		data.handle = NONE_HANDLE;
	}
	DrawImg::~DrawImg() {
		DeleteGraph(data.handle); //画像解放.
	}

	//constructor, destructor.
	DrawDivImg::DrawDivImg() {
		for (auto& i : data) {
			i.handle = NONE_HANDLE;
		}
	}
	DrawDivImg::~DrawDivImg() {
		for (auto& i : data) {
			DeleteGraph(i.handle); //画像解放.
		}
	}

	//LoadGraphの改造版.
	int DrawImg::LoadFile(MY_STRING fileName) {

		//過去に読み込んだ画像は解放.
		if (data.handle != NONE_HANDLE) {
			DeleteGraph(data.handle);
			data.handle = NONE_HANDLE;
		}
		//画像読み込み.
		data.handle = LoadGraph(fileName.c_str());
		int err = GetGraphSize(data.handle, &data.size.x, &data.size.y);
	
		_return(-1, data.handle < 0) //-1: LoadGraphエラー.
		_return(-2, err < 0)         //-2: GetGraphSizeエラー.
		return 0;                    // 0: 正常終了.
	}
	//LoadDivGraphの改造版.
	int DrawDivImg::LoadFile(MY_STRING fileName, INT_XY size, INT_XY cnt) {

		//過去に読み込んだ画像は解放.
		for (auto& i : data) {
			DeleteGraph(i.handle); //画像解放.
			i.handle = NONE_HANDLE;
		}

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
	int DrawImg::Draw(DBL_XY pos, Anchor anc, bool isTrans, bool isFloat) {

		_return(-3, data.handle == NONE_HANDLE) //-3: handle未設定.

		//float型かどうか.
		if (isFloat) {
			//基準点に座標をずらす.
			float x = _flt(pos.x - (data.size.x) * ANCHOR_POS[anc].x);
			float y = _flt(pos.y - (data.size.y) * ANCHOR_POS[anc].y);
			//描画.
			int err = DrawGraphF(x, y, data.handle, isTrans);
			_return(-1, err < 0) //-1: DrawGraphFエラー.
		}
		else {
			//基準点に座標をずらす.
			int x = _int(pos.x - (data.size.x-1) * ANCHOR_POS[anc].x);
			int y = _int(pos.y - (data.size.y-1) * ANCHOR_POS[anc].y);
			//描画.
			int err = DrawGraph(x, y, data.handle, isTrans);
			_return(-2, err < 0) //-2: DrawGraphエラー.
		}
		return 0; //正常終了.
	}
	int DrawDivImg::Draw(int imgNo, DBL_XY pos, Anchor anc, bool isTrans, bool isFloat) {

		_return(-3, data[imgNo].handle == NONE_HANDLE) //-3: handle未設定.

		//float型かどうか.
		if (isFloat) {
			//基準点に座標をずらす.
			float x = _flt(pos.x - (data[imgNo].size.x) * ANCHOR_POS[anc].x);
			float y = _flt(pos.y - (data[imgNo].size.y) * ANCHOR_POS[anc].y);
			//描画.
			int err = DrawGraphF(x, y, data[imgNo].handle, isTrans);
			_return(-1, err < 0) //-1: DrawGraphFエラー.
		}
		else {
			//基準点に座標をずらす.
			int x = _int(pos.x - (data[imgNo].size.x-1) * ANCHOR_POS[anc].x);
			int y = _int(pos.y - (data[imgNo].size.y-1) * ANCHOR_POS[anc].y);
			//描画.
			int err = DrawGraph(x, y, data[imgNo].handle, isTrans);
			_return(-2, err < 0) //-2: DrawGraphエラー.
		}
		return 0; //正常終了.
	}

	//DrawRectGraphの改造版.
	//Rect = 矩形(正方形や長方形のこと)
	int DrawImg::DrawRect(DBL_XY pos, INT_XY stPixel, INT_XY size, bool isTrans, bool isFloat) {

		_return(-3, data.handle == NONE_HANDLE) //-3: handle未設定.

		//float型かどうか.
		if (isFloat) {
			int err = DrawRectGraphF(
				_flt(pos.x), _flt(pos.y), stPixel.x, stPixel.y, size.x, size.y, data.handle, isTrans
			);
			_return(-1, err < 0) //-1: DrawRectGraphFエラー.
		}
		else {
			int err = DrawRectGraph(
				_int_r(pos.x), _int_r(pos.y), stPixel.x, stPixel.y, size.x, size.y, data.handle, isTrans
			);
			_return(-2, err < 0) //-2: DrawRectGraphエラー.
		}
		return 0; //正常終了.
	}
	int DrawDivImg::DrawRect(int imgNo, DBL_XY pos, INT_XY stPixel, INT_XY size, bool isTrans, bool isFloat) {

		_return(-3, data[imgNo].handle == NONE_HANDLE) //-3: handle未設定.

		//float型かどうか.
		if (isFloat) {
			int err = DrawRectGraphF(
				_flt(pos.x), _flt(pos.y), stPixel.x, stPixel.y, size.x, size.y, data[imgNo].handle, isTrans
			);
			_return(-1, err < 0) //-1: DrawRectGraphFエラー.
		}
		else {
			int err = DrawRectGraph(
				_int_r(pos.x), _int_r(pos.y), stPixel.x, stPixel.y, size.x, size.y, data[imgNo].handle, isTrans
			);
			_return(-2, err < 0) //-2: DrawRectGraphエラー.
		}
		return 0; //正常終了.
	}

	//DrawExtendGraphの改造版.
	int DrawImg::DrawExtend(DBL_XY pos, DBL_XY sizeRate, Anchor anc, bool isTrans, bool isFloat) {

		_return(-3, data.handle == NONE_HANDLE) //-3: handle未設定.

		//float型かどうか.
		if (isFloat) {
			//始点を求める.
			float x1 = _flt(pos.x - (data.size.x * sizeRate.x) * ANCHOR_POS[anc].x);
			float y1 = _flt(pos.y - (data.size.y * sizeRate.y) * ANCHOR_POS[anc].y);
			//終点を求める.
			float x2 = _flt(x1 + data.size.x * sizeRate.x);
			float y2 = _flt(y1 + data.size.y * sizeRate.y);

			int err = DrawExtendGraphF(x1, y1, x2+1, y2+1, data.handle, isTrans);
			_return(-1, err < 0) //-1: DrawExtendGraphFエラー.
		}
		else {
			//始点を求める.
			int x1 = _int(pos.x - ((data.size.x * sizeRate.x)-1) * ANCHOR_POS[anc].x);
			int y1 = _int(pos.y - ((data.size.y * sizeRate.y)-1) * ANCHOR_POS[anc].y);
			//終点を求める.
			int x2 = _int(x1 + ((data.size.x * sizeRate.x)-1));
			int y2 = _int(y1 + ((data.size.y * sizeRate.y)-1));

			int err = DrawExtendGraph(x1, y1, x2+1, y2+1, data.handle, isTrans);
			_return(-2, err < 0) //-2: DrawExtendGraphエラー.
		}
		return 0; //正常終了.
	}
	int DrawDivImg::DrawExtend(int imgNo, DBL_XY pos, DBL_XY sizeRate, Anchor anc, bool isTrans, bool isFloat) {

		_return(-3, data[imgNo].handle == NONE_HANDLE) //-3: handle未設定.

		//float型かどうか.
		if (isFloat) {
			//始点を求める.
			float x1 = _flt(pos.x - (data[imgNo].size.x * sizeRate.x) * ANCHOR_POS[anc].x);
			float y1 = _flt(pos.y - (data[imgNo].size.y * sizeRate.y) * ANCHOR_POS[anc].y);
			//終点を求める.
			float x2 = _flt(x1 + data[imgNo].size.x * sizeRate.x);
			float y2 = _flt(y1 + data[imgNo].size.y * sizeRate.y);

			int err = DrawExtendGraphF(x1, y1, x2+1, y2+1, data[imgNo].handle, isTrans);
			_return(-1, err < 0) //-1: DrawExtendGraphFエラー.
		}
		else {
			//始点を求める.
			int x1 = _int(pos.x - ((data[imgNo].size.x * sizeRate.x)-1) * ANCHOR_POS[anc].x);
			int y1 = _int(pos.y - ((data[imgNo].size.y * sizeRate.y)-1) * ANCHOR_POS[anc].y);
			//終点を求める.
			int x2 = _int(x1 + ((data[imgNo].size.x * sizeRate.x)-1));
			int y2 = _int(y1 + ((data[imgNo].size.y * sizeRate.y)-1));

			int err = DrawExtendGraph(x1, y1, x2+1, y2+1, data[imgNo].handle, isTrans);
			_return(-2, err < 0) //-2: DrawExtendGraphエラー.
		}
		return 0; //正常終了.
	}

	//DrawRotaGraphの改造版.
	int DrawImg::DrawRota(DBL_XY pos, double extend, double ang, Anchor anc, bool isTrans, bool isFloat) {

		_return(-3, data.handle == NONE_HANDLE) //-3: handle未設定.

		//float型かどうか.
		if (isFloat) {
			//基準点に座標をずらす.
			float x = _flt(pos.x - (data.size.x-1) * ANCHOR_POS[anc].x);
			float y = _flt(pos.y - (data.size.y-1) * ANCHOR_POS[anc].y);
	
			int err = DrawRotaGraphF(x, y, extend, ang, data.handle, isTrans);
			_return(-1, err < 0) //-1: DrawRotaGraphFエラー.
		}
		else {
			//基準点に座標をずらす.
			int x = _int(pos.x - (data.size.x-1) * ANCHOR_POS[anc].x);
			int y = _int(pos.y - (data.size.y-1) * ANCHOR_POS[anc].y);
	
			int err = DrawRotaGraph(x, y, extend, ang, data.handle, isTrans);
			_return(-2, err < 0) //-2: DrawRotaGraphエラー.
		}
		return 0; //正常終了.
	}
	int DrawDivImg::DrawRota(int imgNo, DBL_XY pos, double extend, double ang, Anchor anc, bool isTrans, bool isFloat) {

		_return(-3, data[imgNo].handle == NONE_HANDLE) //-3: handle未設定.

		//float型かどうか.
		if (isFloat) {
			//基準点に座標をずらす.
			float x = _flt(pos.x - (data[imgNo].size.x-1) * ANCHOR_POS[anc].x);
			float y = _flt(pos.y - (data[imgNo].size.y-1) * ANCHOR_POS[anc].y);
	
			int err = DrawRotaGraphF(x, y, extend, ang, data[imgNo].handle, isTrans);
			_return(-1, err < 0) //-1: DrawRotaGraphFエラー.
		}
		else {
			//基準点に座標をずらす.
			int x = _int(pos.x - (data[imgNo].size.x-1) * ANCHOR_POS[anc].x);
			int y = _int(pos.y - (data[imgNo].size.y-1) * ANCHOR_POS[anc].y);
	
			int err = DrawRotaGraph(x, y, extend, ang, data[imgNo].handle, isTrans);
			_return(-2, err < 0) //-2: DrawRotaGraphエラー.
		}
		return 0; //正常終了.
	}

	//DrawModiGraphの改造版.
	int DrawImg::DrawModi(DBL_XY luPos, DBL_XY ruPos, DBL_XY rdPos, DBL_XY ldPos, bool isTrans, bool isFloat) {
	
		_return(-3, data.handle == NONE_HANDLE) //-3: handle未設定.

		//float型かどうか.
		if (isFloat) {
			int err = DrawModiGraphF(
				_flt(luPos.x), _flt(luPos.y), _flt(ruPos.x), _flt(ruPos.y), 
				_flt(rdPos.x), _flt(rdPos.y), _flt(ldPos.x), _flt(ldPos.y), data.handle, isTrans
			);
			_return(-1, err < 0) //-1: DrawModiGraphFエラー.
		}
		else {
			int err = DrawModiGraph(
				_int_r(luPos.x), _int_r(luPos.y), _int_r(ruPos.x), _int_r(ruPos.y),
				_int_r(rdPos.x), _int_r(rdPos.y), _int_r(ldPos.x), _int_r(ldPos.y), data.handle, isTrans
			);
			_return(-2, err < 0) //-2: DrawModiGraphエラー.
		}
		return 0; //正常終了.
	}
	int DrawDivImg::DrawModi(int imgNo, DBL_XY luPos, DBL_XY ruPos, DBL_XY rdPos, DBL_XY ldPos, bool isTrans, bool isFloat) {

		_return(-3, data[imgNo].handle == NONE_HANDLE) //-3: handle未設定.

		//float型かどうか.
		if (isFloat) {
			int err = DrawModiGraphF(
				_flt(luPos.x), _flt(luPos.y), _flt(ruPos.x), _flt(ruPos.y),
				_flt(rdPos.x), _flt(rdPos.y), _flt(ldPos.x), _flt(ldPos.y), data[imgNo] .handle, isTrans
			);
			_return(-1, err < 0) //-1: DrawModiGraphFエラー.
		}
		else {
			int err = DrawModiGraph(
				_int_r(luPos.x), _int_r(luPos.y), _int_r(ruPos.x), _int_r(ruPos.y),
				_int_r(rdPos.x), _int_r(rdPos.y), _int_r(ldPos.x), _int_r(ldPos.y), data[imgNo].handle, isTrans
			);
			_return(-2, err < 0) //-2: DrawModiGraphエラー.
		}
		return 0; //正常終了.
	}

// ▼*---=[ DrawStr ]=---*▼ //

	//DrawStringの改造版.
	int DrawStr::Draw(Anchor anc, int font) {
	
		//基準点に座標をずらす.
		float x = _flt(data.pos.x - (GetTextSize(data.text, font).x-1) * ANCHOR_POS[anc].x);
		float y = _flt(data.pos.y - (GetTextSize(data.text, font).y-1) * ANCHOR_POS[anc].y);

		//デフォルトフォント.
		if (font < 0) {
			int err = DrawString(_int(x), _int(y), data.text.c_str(), data.color);
			_return(-1, err < 0) //-1: DrawStringエラー.
		}
		//フォント設定あり.
		else {
			int err = DrawStringToHandle(_int(x), _int(y), data.text.c_str(), data.color, font);
			_return(-2, err < 0) //-2: DrawStringToHandleエラー.
		}
		return 0; //正常終了.
	}
	//DrawRotaStringの改造版.
	int DrawStr::DrawRota(INT_XY extend, INT_XY pivot, double ang, bool isVertical, int font) {

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
	int DrawStr::DrawModi(INT_XY luPos, INT_XY ruPos, INT_XY rdPos, INT_XY ldPos, bool isVertical, int font) {

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
	INT_XY DrawStr::GetTextSize(MY_STRING str, int font) {
	
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
			int err = DrawCircleAA(_flt(data->pos.x), _flt(data->pos.y), data->r, 60, data->color, isFill, thick);
			_return(-1, err < 0) //-1: DrawCircleAAエラー.
		}
		//アンチエイリアスなし.
		else{
			int err = DrawCircle(_int_r(data->pos.x), _int_r(data->pos.y), _int_r(data->r), data->color, isFill, _int_r(thick));
			_return(-2, err < 0) //-2: DrawCircleエラー.
		}
		return 0; //正常終了.
	}
	//DrawBoxの改造版.
	int DrawBoxST(const Box* data, Anchor anc, bool isFill, bool isAnti) {

		_return(-3, data->size.x <= 0.0 || data->size.y <= 0.0) //-3: サイズが0.0以下.

		//始点を求める.
		float x1 = _flt(data->pos.x - (data->size.x-1) * ANCHOR_POS[anc].x);
		float y1 = _flt(data->pos.y - (data->size.y-1) * ANCHOR_POS[anc].y);
		//終点を求める.
		float x2 = _flt(x1 + data->size.x-1);
		float y2 = _flt(y1 + data->size.y-1);

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
				_flt(data->pos[0].x), _flt(data->pos[0].y),
				_flt(data->pos[1].x), _flt(data->pos[1].y),
				_flt(data->pos[2].x), _flt(data->pos[2].y), data->color, isFill
			);
			_return(-1, err < 0) //-1: DrawTriangleAAエラー.
		}
		//アンチエイリアスなし.
		else {
			int err = DrawTriangle(
				_int_r(data->pos[0].x), _int_r(data->pos[0].y),
				_int_r(data->pos[1].x), _int_r(data->pos[1].y),
				_int_r(data->pos[2].x), _int_r(data->pos[2].y), data->color, isFill
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
				_flt(data->stPos.x), _flt(data->stPos.y),
				_flt(data->edPos.x), _flt(data->edPos.y), data->color, thick
			);
			_return(-1, err < 0) //-1: DrawLineAAエラー.
		}
		//アンチエイリアスなし.
		else {
			int err = DrawLine(
				_int_r(data->stPos.x), _int_r(data->stPos.y), 
				_int_r(data->edPos.x), _int_r(data->edPos.y), data->color, (int)thick
			);
			_return(-2, err < 0) //-2: DrawLineエラー.
		}
		return 0; //正常終了.
	}
	//画面全体にグリッド線を描画.
	int DrawWindowGrid(int wid, int hei, int size, UINT clrWid, UINT clrHei) {

		//縦線の描画.
		for (int x = 0; x < wid; x += size) {

			Line line = { {_dbl(x), 0}, {_dbl(x), _dbl(hei)}, clrHei};
			int err = DrawLineST(&line);
			_return(-1, err < 0) //-1: 縦線でエラー.
		}
		//横線の描画.
		for (int y = 0; y < hei; y += size) {

			Line line = { {0, _dbl(y)}, {_dbl(wid), _dbl(y)}, clrWid };
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
		return SetDrawBlendMode(id, _int_r(power));
	}
	//描画モードリセット.
	int ResetDrawBlendMode() {
		return SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}