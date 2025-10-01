/*
   - KR_Draw.cpp - (DxLib)
   ver: 2025/10/02

   描画機能を追加します。
   (オブジェクト指向ver → KR_Object)
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.hに入ってなければここで導入.
  #include "KR_Calc.h"
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

   [サイズの-1について]
   画像やテキストの描画で、調整でサイズを-1している。
   -1が必要かどうかは悩ましいが、これがないと画像をタイルのように並べた時にずれが起きる。
*/

//KR_Libに使う用.
namespace KR_Lib
{
	constexpr int NONE_HANDLE = -1; //ハンドルなし.

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
			DeleteGraph(data.handle); //画像解放.
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
	int DrawImg::DrawRect(DBL_XY pos, int left, int up, int right, int down, Anchor anc, bool isTrans, bool isFloat) {

		_return(-3, data.handle == NONE_HANDLE) //-3: handle未設定.

		//アンカーを含めた描画座標.
		DBL_XY drawPos = {
			pos.x - data.size.x * ANCHOR_POS[anc].x,
			pos.y - data.size.y * ANCHOR_POS[anc].y
		};
		//画像の矩形.
		INT_XY stPxl = {0, 0};
		INT_XY size  = data.size;

		//クリッピング(画像の切り取り処理)
		if (drawPos.x < left) {
			stPxl.x += _int(left - drawPos.x);
			size.x  -= _int(left - drawPos.x);
			drawPos.x = left;
		}
		if (drawPos.y < up) {
			stPxl.y += _int(up - drawPos.y);
			size.y  -= _int(up - drawPos.y);
			drawPos.y = up;
		}
		if (drawPos.x + size.x > right) {
			size.x -= _int((drawPos.x + size.x) - right);
		}
		if (drawPos.y + size.y > down) {
			size.y -= _int((drawPos.y + size.y) - down);
		}

		//描画する範囲があるなら描画.
		if (size.x > 0 && size.y > 0) {
			if (isFloat) {
				int err = DrawRectGraphF(_flt(drawPos.x), _flt(drawPos.y), stPxl.x, stPxl.y, size.x, size.y, data.handle, isTrans);
				_return(-1, err < 0) //-1: DrawRectGraphFエラー.
			}
			else {
				int err = DrawRectGraph(_int(drawPos.x), _int(drawPos.y), stPxl.x, stPxl.y, size.x, size.y, data.handle, isTrans);
				_return(-2, err < 0) //-2: DrawRectGraphエラー.
			}
		}

		return 0; //正常終了.
	}
	int DrawDivImg::DrawRect(int imgNo, DBL_XY pos, int left, int up, int right, int down, Anchor anc, bool isTrans, bool isFloat) {

		_return(-3, data[imgNo].handle == NONE_HANDLE) //-3: handle未設定.

		//ソース矩形.
		INT_XY stPxl = {0, 0};           //画像の始点ピクセル.
		INT_XY size  = data[imgNo].size; //始点からのサイズ.

		//左にはみ出てるなら.
		if (pos.x < left) {
			stPxl.x -= _int_r(pos.x); //ソースを右にずらす.
			size .x += _int_r(pos.x); //描画幅を減らす(pos.xは負の値なので加算)
		}
		//上にはみ出てるなら.
		if (pos.y < up) {
			stPxl.y -= _int_r(pos.y);
			size .y += _int_r(pos.y);
		}
		//右にはみ出てるなら.
		if (pos.x + data[imgNo].size.x * ANCHOR_POS[anc].x > right) {
			size.x = _int_r((right - pos.x) * ANCHOR_POS[anc].x); //幅を削る.
		}
		//下にはみ出てるなら.
		if (pos.y + data[imgNo].size.y * ANCHOR_POS[anc].y > down) {
			size.y = _int_r((down - pos.y) * ANCHOR_POS[anc].y); //幅を削る.
		}
		//描画する範囲があるなら.
		if (size.x > 0 && size.y > 0) {
			//float型かどうか.
			if (isFloat) {
				//基準点に座標をずらす.
				float x = _flt(pos.x - (data[imgNo].size.x) * ANCHOR_POS[anc].x);
				float y = _flt(pos.y - (data[imgNo].size.y) * ANCHOR_POS[anc].y);
				//描画.
				int err = DrawRectGraphF(
					x, y, stPxl.x, stPxl.y, size.x, size.y, data[imgNo].handle, isTrans
				);
				_return(-1, err < 0) //-1: DrawRectGraphFエラー.
			}
			else {
				//基準点に座標をずらす.
				int x = _int(pos.x - (data[imgNo].size.x-1) * ANCHOR_POS[anc].x);
				int y = _int(pos.y - (data[imgNo].size.y-1) * ANCHOR_POS[anc].y);
				//描画.
				int err = DrawRectGraph(
					_int_r(pos.x), _int_r(pos.y), stPxl.x, stPxl.y, size.x, size.y, data[imgNo].handle, isTrans
				);
				_return(-2, err < 0) //-2: DrawRectGraphエラー.
			}
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
			int x1 = _int_r(pos.x - ((data[imgNo].size.x * sizeRate.x)-1) * ANCHOR_POS[anc].x);
			int y1 = _int_r(pos.y - ((data[imgNo].size.y * sizeRate.y)-1) * ANCHOR_POS[anc].y);
			//終点を求める.
			int x2 = _int_r(x1 + ((data[imgNo].size.x * sizeRate.x)-1));
			int y2 = _int_r(y1 + ((data[imgNo].size.y * sizeRate.y)-1));

			int err = DrawExtendGraph(x1, y1, x2+1, y2+1, data[imgNo].handle, isTrans);
			_return(-2, err < 0) //-2: DrawExtendGraphエラー.
		}
		return 0; //正常終了.
	}

	//DrawRotaGraphの改造版.
	//DrawRotaGraphはデフォルトで中央基準のため、アンカーを-0.5する.
	int DrawImg::DrawRota(DBL_XY pos, double extend, double ang, INT_XY pivot, Anchor anc, bool isTrans, bool isFloat) {

		_return(-3, data.handle == NONE_HANDLE) //-3: handle未設定.

		//float型かどうか.
		if (isFloat) {
			//基準点に座標をずらす.
			float x = _flt(pos.x - (data.size.x-1) * (ANCHOR_POS[anc].x-0.5));
			float y = _flt(pos.y - (data.size.y-1) * (ANCHOR_POS[anc].y-0.5));
			//pivot(デフォルトは画像の中心)
			float px = _flt(data.size.x/2 + pivot.x);
			float py = _flt(data.size.y/2 + pivot.y);

			int err = DrawRotaGraph2F(x, y, px, py, extend, _rad(ang), data.handle, isTrans);
			_return(-1, err < 0) //-1: DrawRotaGraphFエラー.
		}
		else {
			//基準点に座標をずらす.
			int x = _int(pos.x - (data.size.x-1) * (ANCHOR_POS[anc].x-0.5));
			int y = _int(pos.y - (data.size.y-1) * (ANCHOR_POS[anc].y-0.5));
			//pivot(デフォルトは画像の中心)
			int px = data.size.x/2 + pivot.x;
			int py = data.size.y/2 + pivot.y;
	
			int err = DrawRotaGraph2(x, y, px, py, extend, _rad(ang), data.handle, isTrans);
			_return(-2, err < 0) //-2: DrawRotaGraphエラー.
		}
		return 0; //正常終了.
	}
	int DrawDivImg::DrawRota(int imgNo, DBL_XY pos, double extend, double ang, INT_XY pivot, Anchor anc, bool isTrans, bool isFloat) {

		_return(-3, data[imgNo].handle == NONE_HANDLE) //-3: handle未設定.

		//float型かどうか.
		if (isFloat) {
			//基準点に座標をずらす.
			float x = _flt(pos.x - (data[imgNo].size.x-1) * (ANCHOR_POS[anc].x-0.5));
			float y = _flt(pos.y - (data[imgNo].size.y-1) * (ANCHOR_POS[anc].y-0.5));
			//pivot(デフォルトは画像の中心)
			float px = _flt(data[imgNo].size.x/2 + pivot.x);
			float py = _flt(data[imgNo].size.y/2 + pivot.y);

			int err = DrawRotaGraph2F(x, y, px, py, extend, _rad(ang), data[imgNo].handle, isTrans);
			_return(-1, err < 0) //-1: DrawRotaGraphFエラー.
		}
		else {
			//基準点に座標をずらす.
			int x = _int(pos.x - (data[imgNo].size.x-1) * (ANCHOR_POS[anc].x-0.5));
			int y = _int(pos.y - (data[imgNo].size.y-1) * (ANCHOR_POS[anc].y-0.5));
			//pivot(デフォルトは画像の中心)
			int px = data[imgNo].size.x/2 + pivot.x;
			int py = data[imgNo].size.y/2 + pivot.y;
	
			int err = DrawRotaGraph2(x, y, px, py, extend, _rad(ang), data[imgNo].handle, isTrans);
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
		float x = _flt(pos.x - (GetTextSize(font).x-1) * ANCHOR_POS[anc].x);
		float y = _flt(pos.y - (GetTextSize(font).y-1) * ANCHOR_POS[anc].y);

		//デフォルトフォント.
		if (font < 0) {
			int err = DrawString(_int(x), _int(y), text.c_str(), color.GetColorCode());
			_return(-1, err < 0) //-1: DrawStringエラー.
		}
		//フォント設定あり.
		else {
			int err = DrawStringToHandle(_int(x), _int(y), text.c_str(), color.GetColorCode(), font);
			_return(-2, err < 0) //-2: DrawStringToHandleエラー.
		}
		return 0; //正常終了.
	}
	//DrawRotaStringの改造版.
	int DrawStr::DrawRota(INT_XY extend, INT_XY pivot, double ang, bool isVertical, int font) {

		//デフォルトフォント.
		if (font < 0) {
			int err = DrawRotaString(
				pos.x, pos.y, extend.x, extend.y, pivot.x, pivot.y,
				_rad(ang), color.GetColorCode(), 0, isVertical, text.c_str()
			);
			_return(-1, err < 0) //-1: DrawRotaStringエラー.
		}
		//フォント設定あり.
		else {
			int err = DrawRotaStringToHandle(
				pos.x, pos.y, extend.x, extend.y, pivot.x, pivot.y,
				_rad(ang), color.GetColorCode(), font, 0, isVertical, text.c_str()
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
				color.GetColorCode(), 0, isVertical, text.c_str()
			);
			_return(-1, err < 0) //-1: DrawModiStringエラー.
		}
		//フォント設定あり.
		else {
			int err = DrawModiStringToHandle(
				luPos.x, luPos.y, ruPos.x, ruPos.y,
				rdPos.x, rdPos.y, ldPos.x, ldPos.y,
				color.GetColorCode(), font, 0, isVertical, text.c_str()
			);
			_return(-2, err < 0) //-2: DrawModiStringToHandleエラー.
		}
		return 0; //正常終了.
	}

	//テキストのサイズ取得.
	INT_XY DrawStr::GetTextSize(int font) {
	
		INT_XY size{};

		TCHAR name[256]{}; //無視.
		int   line{};      //無視.
		int   thick{};     //無視.

		//デフォルトフォント.
		if (font < 0) {
			GetDrawStringSize(&size.x, &size.y, &line, text.c_str(), 255);
		}
		//フォント設定あり.
		else {
			GetDrawStringSizeToHandle(&size.x, &size.y, &line, text.c_str(), 255, font);
			GetFontStateToHandle(name, &size.y, &thick, font); //size.yはフォントから取得.
		}

		return size;
	}

// ▼*---=[ Font ]=---*▼ //

	//constructor, destructor.
	Font::Font() {
		handle = NONE_HANDLE;
	}
	Font::~Font() {
		//ハンドルがあれば.
		if (handle != NONE_HANDLE) {
			DeleteFontToHandle(handle); //解放.
		}
	}
	//フォント作成.
	void Font::CreateFontH(MY_STRING fontName, int size, int thick, FontTypeID fontId) {
		handle = CreateFontToHandle(fontName.c_str(), size, thick, _int(fontId));
	}

// ▼*---=[ GradLine ]=---*▼ //
	
	//頂点追加.
	void GradLine::AddPoint(DBL_XY pos, MY_COLOR color) {

		VERTEX2D point;
		point.pos = VGet(_flt(pos.x), _flt(pos.y), 0); //VECTOR型にして登録.
		point.dif = color.GetColorU8();                //COLOR_U8で登録.
		point.rhw = 1.0f;                              //2Dでは不要?
		point.u = point.v = 0.0f;                      //テクスチャUVは使わない.

		points.push_back(point); //頂点追加.
	}
	//描画.
	void GradLine::Draw(bool isClose) {

		//頂点の数.
		int count = _int((isClose) ? points.size()+1 : points.size());
		//頂点配列.
		vector<VERTEX2D> tmp(count);

		//頂点データをコピー.
		for (int i = 0; i < points.size(); i++) {
			tmp[i] = points[i];
		}
		if (isClose) {
			tmp[points.size()] = tmp[0]; //終点に始点を入れる.
		}

		//描画.
		SetDrawBlendModeKR(BlendModeID::Alpha, 255); //透過を反映させるためにアルファモードにする.
		DrawPrimitive2D(tmp.data(), count, DX_PRIMTYPE_LINESTRIP, DX_NONE_GRAPH, FALSE); //TODO: DX_PRIMTYPE_LINESTRIP以外の機能.
		ResetDrawBlendMode();
	}

// ▼*---=[ function ]=---*▼ //

	//DrawCircleの改造版.
	int DrawCircleKR(const Circle* data, bool isFill, bool isAnti, float thick) {

		//アンチエイリアスあり.
		if (isAnti) {
			//posnum(角形数)は60に設定する.
			int err = DrawCircleAA(_flt(data->pos.x), _flt(data->pos.y), data->r, 60, data->color.GetColorCode(), isFill, thick);
			_return(-1, err < 0) //-1: DrawCircleAAエラー.
		}
		//アンチエイリアスなし.
		else{
			int err = DrawCircle(_int_r(data->pos.x), _int_r(data->pos.y), _int_r(data->r), data->color.GetColorCode(), isFill, _int_r(thick));
			_return(-2, err < 0) //-2: DrawCircleエラー.
		}
		return 0; //正常終了.
	}
	//DrawBoxの改造版.
	int DrawBoxKR(const Box* data, Anchor anc, bool isFill, bool isAnti) {

		_return(-3, data->size.x <= 0.0 || data->size.y <= 0.0) //-3: サイズが0.0以下.

		//始点を求める.
		float x1 = _flt(data->pos.x - (data->size.x-1) * ANCHOR_POS[anc].x);
		float y1 = _flt(data->pos.y - (data->size.y-1) * ANCHOR_POS[anc].y);
		//終点を求める.
		float x2 = _flt(x1 + data->size.x-1);
		float y2 = _flt(y1 + data->size.y-1);

		//アンチエイリアスあり.
		if (isAnti) {
			int err = DrawBoxAA(x1, y1, x2+1, y2+1, data->color.GetColorCode(), isFill);
			_return(-1, err < 0) //-1: DrawBoxAAエラー.
		}
		//アンチエイリアスなし.
		else {
			int err = DrawBox(_int(x1), _int(y1), _int(x2+1), _int(y2+1), data->color.GetColorCode(), isFill);
			_return(-2, err < 0) //-2: DrawBoxエラー.
		}
		return 0; //正常終了.
	}
	//DrawTriangleの改造版.
	int DrawTriangleKR(const Triangle* data, bool isFill, bool isAnti) {

		//アンチエイリアスあり.
		if (isAnti) {
			int err = DrawTriangleAA(
				_flt(data->pos[0].x), _flt(data->pos[0].y),
				_flt(data->pos[1].x), _flt(data->pos[1].y),
				_flt(data->pos[2].x), _flt(data->pos[2].y), data->color.GetColorCode(), isFill
			);
			_return(-1, err < 0) //-1: DrawTriangleAAエラー.
		}
		//アンチエイリアスなし.
		else {
			int err = DrawTriangle(
				_int_r(data->pos[0].x), _int_r(data->pos[0].y),
				_int_r(data->pos[1].x), _int_r(data->pos[1].y),
				_int_r(data->pos[2].x), _int_r(data->pos[2].y), data->color.GetColorCode(), isFill
			);
			_return(-2, err < 0) //-2: DrawTriangleエラー.
		}
		return 0; //正常終了.
	}
	//DrawLineの改造版.
	int DrawLineKR(const Line* data, bool isAnti, float thick) {

		//アンチエイリアスあり.
		if (isAnti) {
			int err = DrawLineAA(
				_flt(data->stPos.x), _flt(data->stPos.y),
				_flt(data->edPos.x), _flt(data->edPos.y), data->color.GetColorCode(), thick
			);
			_return(-1, err < 0) //-1: DrawLineAAエラー.
		}
		//アンチエイリアスなし.
		else {
			int err = DrawLine(
				_int_r(data->stPos.x), _int_r(data->stPos.y), 
				_int_r(data->edPos.x), _int_r(data->edPos.y), data->color.GetColorCode(), _int(thick)
			);
			_return(-2, err < 0) //-2: DrawLineエラー.
		}
		return 0; //正常終了.
	}
	//画面全体にグリッド線を描画.
	int DrawWindowGrid(int wid, int hei, int size, MY_COLOR clrWid, MY_COLOR clrHei) {

		//縦線の描画.
		for (int x = 0; x < wid; x += size) {

			Line line = { {_dbl(x), 0}, {_dbl(x), _dbl(hei)}, clrHei };
			int err = DrawLineKR(&line);
			_return(-1, err < 0) //-1: 縦線でエラー.
		}
		//横線の描画.
		for (int y = 0; y < hei; y += size) {

			Line line = { {0, _dbl(y)}, {_dbl(wid), _dbl(y)}, clrWid };
			int err = DrawLineKR(&line);
			_return(-2, err < 0) //-2: 横線でエラー.
		}
		return 0; //正常終了.
	}

	//描画モード変更.
	int SetDrawBlendModeKR(BlendModeID id, int power) {
		return SetDrawBlendMode(_int(id), power);
	}
	int SetDrawBlendModeKR(BlendModeID id, double power) {
		return SetDrawBlendMode(_int(id), _int_r(power));
	}
	//描画モードリセット.
	int ResetDrawBlendMode() {
		return SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}