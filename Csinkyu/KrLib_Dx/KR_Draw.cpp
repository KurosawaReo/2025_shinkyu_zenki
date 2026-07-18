/*
   - KR_Draw.cpp - (DxLib)
*/
#include "KR_Draw.h"

//[include] ".cpp"ファイルでのみ使うもの.
#include "KR_App.h"

/*
   [終点の注意]
   DrawBox, DrawLine, DrawExtendGraphなどの終点を設定するものは
   始点から終点-1まで描画される仕様(その方が直感的だと作者は判断したそう)

   例: DrawBox(1, 1, 5, 5, color, false)とした場合

   　１２３４５
   １■■■■
   ２■　　■
   ３■　　■
   ４■■■■
   ５

   [サイズの-1について]
   画像やテキストの描画で、調整でサイズを-1している。
   これがないとタイルのように並べた時にずれが起きるため、多分必要。
*/

//KrLib名前空間.
namespace KR
{
	constexpr int NONE_HANDLE = -1; //ハンドルなし.

	//アンカー座標.
	static const DBL_XY ANCHOR_POS[9] = {
		{0.0, 0.0}, {0.5, 0.0}, {1.0, 0.0},
		{0.0, 0.5}, {0.5, 0.5}, {1.0, 0.5},
		{0.0, 1.0}, {0.5, 1.0}, {1.0, 1.0}
	};

// ▼*--=<[ DrawStr ]>=--*▼ //

	//DrawStringの改造版.
	void DrawStr::Draw(Anchor anc, int font, bool isCameraDisp) {
	
		//描画座標.
		DBL_XY newPos = (isCameraDisp) ? App::ToWorldPos(pos.ToDbl()) : pos.ToDbl();

		//基準点に座標をずらす.
		int x = _int_r(newPos.x - (GetTextSize(font).x-1) * ANCHOR_POS[_int(anc)].x);
		int y = _int_r(newPos.y - (GetTextSize(font).y-1) * ANCHOR_POS[_int(anc)].y);

		//デフォルトフォント.
		if (font < 0) {
			int err = DrawString(x, y, text.c_str(), color.GetColorCode());
			if (err < 0) {
				throw ErrorMsg(_T("DrawStr::Draw"), _T("DrawStringエラー"));
				return;
			}
		}
		//フォント設定あり.
		else {
			int err = DrawStringToHandle(x, y, text.c_str(), color.GetColorCode(), font);
			if (err < 0) {
				throw ErrorMsg(_T("DrawStr::Draw"), _T("DrawStringToHandleエラー"));
				return;
			}
		}
	}
	//DrawRotaStringの改造版.
	void DrawStr::DrawRota(INT_XY extend, INT_XY pivot, double ang, bool isVertical, int font, bool isCameraDisp) {

		DBL_XY newPos = pos.ToDbl(); //描画座標.
		double newAng = ang;         //描画角度.

		//カメラ基準に変換.
		if (isCameraDisp) {
			//TODO: 画像のDrawRotaみたいに回転対応させる.
		}

		//デフォルトフォント.
		if (font < 0) {
			int err = DrawRotaString(
				_int_r(newPos.x), _int_r(newPos.y), extend.x, extend.y, pivot.x, pivot.y,
				_rad(newAng), color.GetColorCode(), 0, isVertical, text.c_str()
			);
			if (err < 0) {
				throw ErrorMsg(_T("DrawStr::DrawRota"), _T("DrawRotaStringエラー"));
				return;
			}
		}
		//フォント設定あり.
		else {
			int err = DrawRotaStringToHandle(
				_int_r(newPos.x), _int_r(newPos.y), extend.x, extend.y, pivot.x, pivot.y,
				_rad(newAng), color.GetColorCode(), font, 0, isVertical, text.c_str()
			);
			if (err < 0) {
				throw ErrorMsg(_T("DrawStr::DrawRota"), _T("DrawRotaStringToHandleエラー"));
				return;
			}
		}
	}
	//DrawModiStringの改造版.
	void DrawStr::DrawModi(INT_XY luPos, INT_XY ruPos, INT_XY rdPos, INT_XY ldPos, bool isVertical, int font, bool isCameraDisp) {

		//描画座標.
		DBL_XY newPos[4] = { luPos.ToDbl(), ruPos.ToDbl(), rdPos.ToDbl(), ldPos.ToDbl() };
		//カメラ基準に変換.
		if (isCameraDisp) {
			for (auto& i : newPos) { i = App::ToWorldPos(i); }
		}

		//デフォルトフォント.
		if (font < 0) {
			int err = DrawModiString(
				_int_r(newPos[0].x), _int_r(newPos[0].y), _int_r(newPos[1].x), _int_r(newPos[1].y),
				_int_r(newPos[2].x), _int_r(newPos[2].y), _int_r(newPos[3].x), _int_r(newPos[3].y),
				color.GetColorCode(), 0, isVertical, text.c_str()
			);
			if (err < 0) {
				throw ErrorMsg(_T("DrawStr::DrawModi"), _T("DrawModiStringエラー"));
				return;
			}
		}
		//フォント設定あり.
		else {
			int err = DrawModiStringToHandle(
				_int_r(newPos[0].x), _int_r(newPos[0].y), _int_r(newPos[1].x), _int_r(newPos[1].y),
				_int_r(newPos[2].x), _int_r(newPos[2].y), _int_r(newPos[3].x), _int_r(newPos[3].y),
				color.GetColorCode(), font, 0, isVertical, text.c_str()
			);
			if (err < 0) {
				throw ErrorMsg(_T("DrawStr::DrawModi"), _T("DrawModiStringToHandleエラー"));
				return;
			}
		}
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

// ▼*--=<[ Font ]>=--*▼ //

	//コンストラクタ, デストラクタ.
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

// ▼*--=<[ GradLine ]>=--*▼ //
	
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
	void GradLine::Draw(bool isClose, bool isCameraDisp) {

		//頂点の数.
		int count = _int((isClose) ? points.size()+1 : points.size());
		//頂点配列.
		vector<VERTEX2D> tmp(count);

		//頂点データをコピー.
		for (int i = 0; i < points.size(); i++) {
			tmp[i] = points[i]; //頂点を登録.
			//カメラ基準に変換.
			if (isCameraDisp) {
				tmp[i].pos.x -= _flt(App::GetWindowRect().GetLU().x);
				tmp[i].pos.y -= _flt(App::GetWindowRect().GetLU().y);
			}
		}
		if (isClose) {
			tmp[points.size()] = tmp[0]; //終点に始点を入れる.
		}

		//描画.
		DrawMode::Exe(
			DrawModeID::None, DrawBlendModeID::Alpha, 255,
			[&]() {
				//TODO: ↓DX_PRIMTYPE_LINESTRIP以外の機能.
				DrawPrimitive2D(tmp.data(), count, DX_PRIMTYPE_LINESTRIP, DX_NONE_GRAPH, FALSE);
			}
		);
	}

// ▼*--=<[ DrawMode ]>=--*▼ //

	DrawMode DrawMode::inst;
}