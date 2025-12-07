/*
   - KR_Draw.cpp - (DxLib)
   ver: 2025/12/07
*/
#include "KR_Draw.h"

//[include] cppでのみ使うもの.
#include "KR_App.h"
#include "KR_Calc.h"
#include "KR_Camera.h"

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
   -1が必要かどうかは悩ましいが、これがないと画像をタイルのように並べた時にずれが起きる(検証結果)
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

// ▼*--=<[ DrawImgST ]>=--*▼ //

	//constructor.
	DrawImg::DrawImg() {
		img.handle = NONE_HANDLE;
	}
	//destructor.
	DrawImg::~DrawImg() {
		Release();
	}

	//読み込み.
	ResultInt DrawImg::LoadFile(MY_STRING fileName) {

		//読み込み済のものは解放.
		Release();
		//画像読み込み.
		img.handle = LoadGraph   (fileName.c_str());
		int err    = GetGraphSize(img.handle, &img.size.x, &img.size.y);
	
		//結果を返す.
		if (img.handle < 0) {
			return {-1, _T("DrawImg::LoadFile"), _T("LoadGraphエラー")};
		}
		if (err < 0) {
			return {-2, _T("DrawImg::LoadFile"), _T("GetGraphSizeエラー")};
		}
		return {0, _T("DrawImg::LoadFile"), _T("正常終了")};
	}
	//解放.
	void DrawImg::Release() {
		//データが登録されていれば.
		if (img.handle != NONE_HANDLE) {
			DeleteGraph(img.handle); //解放.
			img.handle = NONE_HANDLE;
		}
	}

	//TODO: LoadDivGraphにはそのうち対応したい. <<<<<<<<<<<<<<<<<<<<<<<<<
#if false
	//LoadDivGraphの改造版.
	ResultInt DrawDivImg::LoadFile(MY_STRING fileName, INT_XY size, INT_XY cnt) {

		//過去に読み込んだ画像は解放.
		for (auto& i : data) {
			DeleteGraph(i.handle); //画像解放.
			i.handle = NONE_HANDLE;
		}

		int* pHandle = new int[cnt.x*cnt.y]; //LoadDivGraphからハンドル取り出す用.

		//画像分割読み込み.
		int err = LoadDivGraph(fileName.c_str(), cnt.x*cnt.y, cnt.x, cnt.y, size.x, size.y, pHandle);
		if (err < 0) {
			return {-1, _T("DrawDivImg::LoadFile"), _T("LoadDivGraphエラー")};
		}
		//Image型配列のサイズを分割数に合わせる.
		img.resize(cnt.x*cnt.y);
		//分割数だけループ.
		for (int i = 0; i < cnt.y; i++) {
			for (int j = 0; j < cnt.x; j++) {
				data[j+i*cnt.x].handle = pHandle[j+i*cnt.x]; //ハンドル保存.
				data[j+i*cnt.x].size   = size;               //サイズ保存.
			}
		}

		//配列破棄.
		delete[] pHandle; pHandle = nullptr;

		return {0, _T("DrawDivImg::LoadFile"), _T("正常終了")};
	}
#endif

	/*
	   DrawGraphの改造版.
	*/
	ResultInt DrawImg::Draw(DBL_XY pos, Anchor anc, bool isTrans, bool isFloat, bool isCameraDis) const {

		if (img.handle == NONE_HANDLE) {
			return {-3, _T("DrawImg::Draw"), _T("ハンドル未設定")};
		}

		//描画座標.
		DBL_XY newPos = pos;
		//カメラ基準に変換.
		if (isCameraDis) { newPos -= Camera::GetCameraPos(); }

		//float型かどうか.
		if (isFloat) {
			//基準点に座標をずらす.
			float x = _flt(newPos.x - (img.size.x) * ANCHOR_POS[_int(anc)].x);
			float y = _flt(newPos.y - (img.size.y) * ANCHOR_POS[_int(anc)].y);
			//float型描画.
			int err = DrawGraphF(x, y, img.handle, isTrans);
			if (err < 0) {
				return {-1, _T("DrawImg::Draw"), _T("DrawGraphFエラー")};
			}
		}
		else {
			//基準点に座標をずらす.
			int x = _int(newPos.x - (img.size.x-1) * ANCHOR_POS[_int(anc)].x);
			int y = _int(newPos.y - (img.size.y-1) * ANCHOR_POS[_int(anc)].y);
			//int型描画.
			int err = DrawGraph(x, y, img.handle, isTrans);
			if (err < 0) {
				return {-2, _T("DrawImg::Draw"), _T("DrawGraphエラー")};
			}
		}
		return {0, _T("DrawImg::Draw"), _T("正常終了")};
	}

	/*
	   DrawRectGraphの改造版.
	   Rect = 矩形(正方形や長方形のこと)
	*/
	ResultInt DrawImg::DrawRect(DBL_XY pos, DBL_RECT rect, Anchor anc, bool isTrans, bool isFloat, bool isCameraDis) const {

		if (img.handle == NONE_HANDLE) {
			return {-3, _T("DrawImg::DrawRect"), _T("ハンドル未設定")};
		}

		//描画座標.
		DBL_XY newPos = pos;
		//カメラ基準に変換.
		if (isCameraDis) { newPos -= Camera::GetCameraPos(); }
		//アンカーを含めた描画座標.
		newPos -= img.size.ToDbl() * ANCHOR_POS[_int(anc)];
		//画像の矩形.
		INT_XY stPxl  = {0, 0};
		INT_XY size   = img.size;

		//クリッピング(画像の切り取り処理)
		if (newPos.x < rect.left) {
			stPxl.x += _int(rect.left - newPos.x);
			size.x  -= _int(rect.left - newPos.x);
			newPos.x = rect.left;
		}
		if (newPos.y < rect.up) {
			stPxl.y += _int(rect.up - newPos.y);
			size.y  -= _int(rect.up - newPos.y);
			newPos.y = rect.up;
		}
		if (newPos.x + size.x > rect.right) {
			size.x -= _int((newPos.x + size.x) - rect.right);
		}
		if (newPos.y + size.y > rect.down) {
			size.y -= _int((newPos.y + size.y) - rect.down);
		}

		//描画する範囲があるなら描画.
		if (size.x > 0 && size.y > 0) {
			if (isFloat) {
				//float型描画.
				int err = DrawRectGraphF(_flt(newPos.x), _flt(newPos.y), stPxl.x, stPxl.y, size.x, size.y, img.handle, isTrans);
				if (err < 0) {
					return {-1, _T("DrawImg::DrawRect"), _T("DrawRectGraphFエラー")};
				}
			}
			else {
				//int型描画.
				int err = DrawRectGraph(_int(newPos.x), _int(newPos.y), stPxl.x, stPxl.y, size.x, size.y, img.handle, isTrans);
				if (err < 0) {
					return {-2, _T("DrawImg::DrawRect"), _T("DrawRectGraphエラー")};
				}
			}
		}

		return {0, _T("DrawImg::DrawRect"), _T("正常終了")};
	}
	
	/*
	   DrawExtendGraphの改造版.
	*/
	ResultInt DrawImg::DrawExtend(DBL_XY pos, DBL_XY sizeRate, Anchor anc, bool isTrans, bool isFloat, bool isCameraDis) const {

		if (img.handle == NONE_HANDLE) {
			return {-3, _T("DrawImg::DrawExtend"), _T("ハンドル未設定")};
		}

		//描画座標.
		DBL_XY newPos = pos;
		//カメラ基準に変換.
		if (isCameraDis) { newPos -= Camera::GetCameraPos(); }

		//float型かどうか.
		if (isFloat) {
			//始点を求める.
			float x1 = _flt(newPos.x - (img.size.x * sizeRate.x) * ANCHOR_POS[_int(anc)].x);
			float y1 = _flt(newPos.y - (img.size.y * sizeRate.y) * ANCHOR_POS[_int(anc)].y);
			//終点を求める.
			float x2 = _flt(x1 + img.size.x * sizeRate.x);
			float y2 = _flt(y1 + img.size.y * sizeRate.y);
			//float型描画.
			int err = DrawExtendGraphF(x1, y1, x2+1, y2+1, img.handle, isTrans);
			if (err < 0) {
				return {-1, _T("DrawImg::DrawExtend"), _T("DrawExtendGraphFエラー")};
			}
		}
		else {
			//始点を求める.
			int x1 = _int(newPos.x - ((img.size.x * sizeRate.x)-1) * ANCHOR_POS[_int(anc)].x);
			int y1 = _int(newPos.y - ((img.size.y * sizeRate.y)-1) * ANCHOR_POS[_int(anc)].y);
			//終点を求める.
			int x2 = _int(x1 + ((img.size.x * sizeRate.x)-1));
			int y2 = _int(y1 + ((img.size.y * sizeRate.y)-1));
			//int型描画.
			int err = DrawExtendGraph(x1, y1, x2+1, y2+1, img.handle, isTrans);
			if (err < 0) {
				return {-2, _T("DrawImg::DrawExtend"), _T("DrawExtendGraphエラー")};
			}
		}
		return {0, _T("DrawImg::DrawExtend"), _T("正常終了")};
	}

	/*
	   DrawRotaGraphの改造版.

	   DrawRotaGraphFast2F()について
	   2   : 回転基準位置も指定する.
	   F   : float型描画.
	   Fast: アルゴリズムが高速になったver.
	*/
	ResultInt DrawImg::DrawRota(DBL_XY pos, double extend, double ang, INT_XY pivot, bool isTrans, bool isFloat, bool isCameraDis) const {

		if (img.handle == NONE_HANDLE) {
			return {-3, _T("DrawImg::DrawRota"), _T("ハンドル未設定")};
		}

		DBL_XY newPos = pos; //描画座標.
		double newAng = ang; //描画角度.

		//カメラ基準に変換.
		if (isCameraDis) { 

			//[world基準]
			//カメラ→画像 の距離.
			const double wrdDist = Calc::CalcDist     (Camera::GetPos(), pos);
			//カメラ→画像 の角度.
			const double wrdAng  = Calc::CalcFacingAng(Camera::GetPos(), pos);

			//[camera基準]
			//カメラ→画像 の角度.
			const double cmrAng = wrdAng - Camera::GetAng();             //カメラの角度を0とする.
			//カメラ→画像 の位置.
			const DBL_XY cmrPos = Calc::CalcVectorDeg(cmrAng) * wrdDist; //方向 * 距離.
			
			//描画座標が確定.
			//カメラ基準にするため、画面の半分ずらす.
			newPos = cmrPos + App::GetWindowRect().GetMiddle().ToDbl();
			//描画角度が確定.
			newAng -= Camera::GetAng();
		}

		//float型かどうか.
		if (isFloat) {
			//回転軸(デフォルトは画像の中心とする)
			float cx = _flt(img.size.x/2 + pivot.x);
			float cy = _flt(img.size.y/2 + pivot.y);
			//float型描画.
			int err = DrawRotaGraphFast2F(newPos.x, newPos.y, cx, cy, extend, _rad(newAng), img.handle, isTrans);
			if (err < 0) {
				return {-1, _T("DrawImg::DrawRota"), _T("DrawRotaGraph2Fエラー") };
			}
		}
		else {
			//回転軸(デフォルトは画像の中心とする)
			int cx = img.size.x/2 + pivot.x;
			int cy = img.size.y/2 + pivot.y;
			//int型描画.
			int err = DrawRotaGraphFast2(_int_r(newPos.x), _int_r(newPos.y), cx, cy, extend, _rad(newAng), img.handle, isTrans);
			if (err < 0) {
				return {-2, _T("DrawImg::DrawRota"), _T("DrawRotaGraph2エラー")};
			}
		}
		return {0, _T("DrawImg::DrawRota"), _T("正常終了")};
	}
	
	/*
	   DrawModiGraphの改造版.
	*/
	ResultInt DrawImg::DrawModi(DBL_XY luPos, DBL_XY ruPos, DBL_XY rdPos, DBL_XY ldPos, bool isTrans, bool isFloat, bool isCameraDis) const {
	
		if (img.handle == NONE_HANDLE) {
			return {-3, _T("DrawImg::DrawModi"), _T("ハンドル未設定")};
		}

		//描画座標.
		DBL_XY newPos[4] = { luPos, ruPos, rdPos, ldPos };
		//カメラ基準に変換.
		if (isCameraDis) {
			for (auto& i : newPos) { i -= Camera::GetCameraPos(); }
		}

		//float型かどうか.
		if (isFloat) {
			//float型描画.
			int err = DrawModiGraphF(
				_flt(newPos[0].x), _flt(newPos[0].y), _flt(newPos[1].x), _flt(newPos[1].y),
				_flt(newPos[2].x), _flt(newPos[2].y), _flt(newPos[3].x), _flt(newPos[3].y), img.handle, isTrans
			);
			if (err < 0) {
				return {-1, _T("DrawImg::DrawModi"), _T("DrawModiGraphFエラー")};
			}
		}
		else {
			//int型描画.
			int err = DrawModiGraph(
				_int_r(newPos[0].x), _int_r(newPos[0].y), _int_r(newPos[1].x), _int_r(newPos[1].y),
				_int_r(newPos[2].x), _int_r(newPos[2].y), _int_r(newPos[3].x), _int_r(newPos[3].y), img.handle, isTrans
			);
			if (err < 0) {
				return {-2, _T("DrawImg::DrawModi"), _T("DrawModiGraphエラー")};
			}
		}
		return {0, _T("DrawImg::DrawModi"), _T("正常終了")};
	}

// ▼*--=<[ DrawImgMng ]>=--*▼ //

	DrawImgMng DrawImgMng::inst; //実体生成.

	//destructor.
	DrawImgMng::~DrawImgMng() {
		//画像データを全て取り出す.
		for (auto& i : images) {
			i.second.Release(); //各画像の解放.
		}
		images.clear(); //データを空にする.
	}

	//画像取得.
	DrawImg* DrawImgMng::Get(string saveName) {
		//存在すれば.
		if (inst.images.count(saveName) > 0) {
			return &inst.images[saveName]; //返す.
		}
		return nullptr;
	}
	//画像取得(チェックあり)
	bool DrawImgMng::TryGet(string saveName, DrawImg* ptr) {
		//存在すれば.
		if (inst.images.count(saveName) > 0) {
			ptr = &inst.images[saveName]; //返す.
			return true;             //取得成功.
		}
		return false; //取得失敗.
	}

	//画像読み込み.
	ResultInt DrawImgMng::LoadFile(MY_STRING fileName, string saveName) {

		//既に存在すれば.
		if (inst.images.count(saveName) > 0) {
			return { -1, _T("DrawImgMng::LoadFile"), _T("使用済みの保存名") };
		}
		//ファイル読み込み.
		ResultInt err = inst.images[saveName].LoadFile(fileName);
		if (err.GetCode() < 0) {
			return { -2, _T("DrawImgMng::LoadFile"), _T("LoadFileエラー") };
		}
		return { 0, _T("DrawImgMng::LoadFile"), _T("正常終了") };
	}

// ▼*--=<[ DrawStr ]>=--*▼ //

	//DrawStringの改造版.
	ResultInt DrawStr::Draw(Anchor anc, int font, bool isCameraDis) {
	
		//描画座標.
		DBL_XY newPos = pos.ToDbl();
		//カメラ基準に変換.
		if (isCameraDis) { newPos -= Camera::GetCameraPos(); }
		//基準点に座標をずらす.
		int x = _int_r(newPos.x - (GetTextSize(font).x-1) * ANCHOR_POS[_int(anc)].x);
		int y = _int_r(newPos.y - (GetTextSize(font).y-1) * ANCHOR_POS[_int(anc)].y);

		//デフォルトフォント.
		if (font < 0) {
			int err = DrawString(x, y, text.c_str(), color.GetColorCode());
			if (err < 0) {
				return {-1, _T("DrawStr::Draw"), _T("DrawStringエラー")};
			}
		}
		//フォント設定あり.
		else {
			int err = DrawStringToHandle(x, y, text.c_str(), color.GetColorCode(), font);
			if (err < 0) {
				return {-2, _T("DrawStr::Draw"), _T("DrawStringToHandleエラー")};
			}
		}
		return {0, _T("DrawStr::Draw"), _T("正常終了")};
	}
	//DrawRotaStringの改造版.
	ResultInt DrawStr::DrawRota(INT_XY extend, INT_XY pivot, double ang, bool isVertical, int font, bool isCameraDis) {

		DBL_XY newPos = pos.ToDbl(); //描画座標.
		double newAng = ang;         //描画角度.

		//カメラ基準に変換.
		if (isCameraDis) {
			//TODO: 画像のDrawRotaみたいに回転対応させる.
		}

		//デフォルトフォント.
		if (font < 0) {
			int err = DrawRotaString(
				_int_r(newPos.x), _int_r(newPos.y), extend.x, extend.y, pivot.x, pivot.y,
				_rad(newAng), color.GetColorCode(), 0, isVertical, text.c_str()
			);
			if (err < 0) {
				return {-1, _T("DrawStr::DrawRota"), _T("DrawRotaStringエラー")};
			}
		}
		//フォント設定あり.
		else {
			int err = DrawRotaStringToHandle(
				_int_r(newPos.x), _int_r(newPos.y), extend.x, extend.y, pivot.x, pivot.y,
				_rad(newAng), color.GetColorCode(), font, 0, isVertical, text.c_str()
			);
			if (err < 0) {
				return {-2, _T("DrawStr::DrawRota"), _T("DrawRotaStringToHandleエラー")};
			}
		}
		return {0, _T("DrawStr::DrawRota"), _T("正常終了")};
	}
	//DrawModiStringの改造版.
	ResultInt DrawStr::DrawModi(INT_XY luPos, INT_XY ruPos, INT_XY rdPos, INT_XY ldPos, bool isVertical, int font, bool isCameraDis) {

		//描画座標.
		DBL_XY newPos[4] = { luPos.ToDbl(), ruPos.ToDbl(), rdPos.ToDbl(), ldPos.ToDbl() };
		//カメラ基準に変換.
		if (isCameraDis) {
			for (auto& i : newPos) { i -= Camera::GetCameraPos(); }
		}

		//デフォルトフォント.
		if (font < 0) {
			int err = DrawModiString(
				_int_r(newPos[0].x), _int_r(newPos[0].y), _int_r(newPos[1].x), _int_r(newPos[1].y),
				_int_r(newPos[2].x), _int_r(newPos[2].y), _int_r(newPos[3].x), _int_r(newPos[3].y),
				color.GetColorCode(), 0, isVertical, text.c_str()
			);
			if (err < 0) {
				return {-1, _T("DrawStr::DrawModi"), _T("DrawModiStringエラー")};
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
				return {-2, _T("DrawStr::DrawModi"), _T("DrawModiStringToHandleエラー")};
			}
		}
		return {0, _T("DrawStr::DrawModi"), _T("正常終了")};
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
	void GradLine::Draw(bool isClose, bool isCameraDis) {

		//頂点の数.
		int count = _int((isClose) ? points.size()+1 : points.size());
		//頂点配列.
		vector<VERTEX2D> tmp(count);

		//頂点データをコピー.
		for (int i = 0; i < points.size(); i++) {
			tmp[i] = points[i]; //頂点を登録.
			//カメラ基準に変換.
			if (isCameraDis) {
				tmp[i].pos.x += _flt(Camera::GetCameraPos().x);
				tmp[i].pos.y += _flt(Camera::GetCameraPos().y);
			}
		}
		if (isClose) {
			tmp[points.size()] = tmp[0]; //終点に始点を入れる.
		}

		//描画.
		SetDrawBlendModeKR(BlendModeID::Alpha, 255); //透過を反映させるためにアルファモードにする.
		DrawPrimitive2D(tmp.data(), count, DX_PRIMTYPE_LINESTRIP, DX_NONE_GRAPH, FALSE); //TODO: DX_PRIMTYPE_LINESTRIP以外の機能.
		ResetDrawBlendMode();
	}

// ▼*--=<[ function ]>=--*▼ //

	/*
	   DrawCircleの改造版.
	*/
	ResultInt DrawCircleKR(const Circle& cir, bool isFill, bool isAnti, float thick, bool isCameraDis) {

		//描画座標.
		DBL_XY newPos = cir.pos;
		//カメラ基準に変換.
		if (isCameraDis) { newPos -= Camera::GetCameraPos(); }

		//アンチエイリアスあり.
		if (isAnti) {
			//posnum(角形数)は60に設定する.
			int err = DrawCircleAA(_flt(newPos.x), _flt(newPos.y), cir.r, 60, cir.color.GetColorCode(), isFill, thick);
			if (err < 0) {
				return {-1, _T("DrawCircleKR"), _T("DrawCircleAAエラー")};
			}
		}
		//アンチエイリアスなし.
		else{
			int err = DrawCircle(_int_r(newPos.x), _int_r(newPos.y), _int_r(cir.r), cir.color.GetColorCode(), isFill, _int_r(thick));
			if (err < 0) {
				return {-2, _T("DrawCircleKR"), _T("DrawCircleエラー")};
			}
		}
		return {0, _T("DrawCircleKR"), _T("正常終了")};
	}
	
	/*
	   DrawBoxの改造版.
	*/
	ResultInt DrawBoxKR(const Box& box, Anchor anc, bool isFill, bool isAnti, bool isCameraDis) {

		if (box.size.x <= 0.0 || box.size.y <= 0.0) {
			return {-3, _T("DrawCircleKR"), _T("サイズが0.0以下") };
		}

		//描画座標.
		DBL_XY newPos = box.pos;
		//カメラ基準に変換.
		if (isCameraDis) { newPos -= Camera::GetCameraPos(); }

		//始点を求める.
		float x1 = _flt(newPos.x - (box.size.x-1) * ANCHOR_POS[_int(anc)].x);
		float y1 = _flt(newPos.y - (box.size.y-1) * ANCHOR_POS[_int(anc)].y);
		//終点を求める.
		float x2 = _flt(x1 + box.size.x-1);
		float y2 = _flt(y1 + box.size.y-1);

		//アンチエイリアスあり.
		if (isAnti) {
			int err = DrawBoxAA(x1, y1, x2+1, y2+1, box.color.GetColorCode(), isFill);
			if (err < 0) {
				return {-1, _T("DrawBoxKR"), _T("DrawBoxAAエラー")};
			}
		}
		//アンチエイリアスなし.
		else {
			int err = DrawBox(_int(x1), _int(y1), _int(x2+1), _int(y2+1), box.color.GetColorCode(), isFill);
			if (err < 0) {
				return {-2, _T("DrawBoxKR"), _T("DrawBoxエラー")};
			}
		}
		return {0, _T("DrawBoxKR"), _T("正常終了")};
	}
	
	/*
	   DrawTriangleの改造版.
	*/
	ResultInt DrawTriangleKR(const Triangle& tri, bool isFill, bool isAnti, bool isCameraDis) {

		//描画座標.
		DBL_XY newPos[3] = { tri.pos[0], tri.pos[1], tri.pos[2] };
		//カメラ基準に変換.
		if (isCameraDis) {
			for (auto& i : newPos) { i -= Camera::GetCameraPos(); }
		}

		//アンチエイリアスあり.
		if (isAnti) {
			int err = DrawTriangleAA(
				_flt(newPos[0].x), _flt(newPos[0].y),
				_flt(newPos[1].x), _flt(newPos[1].y),
				_flt(newPos[2].x), _flt(newPos[2].y), tri.color.GetColorCode(), isFill
			);
			if (err < 0) {
				return {-1, _T("DrawTriangleKR"), _T("DrawTriangleAAエラー")};
			}
		}
		//アンチエイリアスなし.
		else {
			int err = DrawTriangle(
				_int_r(newPos[0].x), _int_r(newPos[0].y),
				_int_r(newPos[1].x), _int_r(newPos[1].y),
				_int_r(newPos[2].x), _int_r(newPos[2].y), tri.color.GetColorCode(), isFill
			);
			if (err < 0) {
				return {-2, _T("DrawTriangleKR"), _T("DrawTriangleエラー")};
			}
		}
		return {0, _T("DrawTriangleKR"), _T("正常終了")};
	}
	
	/*
	   DrawLineの改造版.
	*/
	ResultInt DrawLineKR(const Line& line, bool isAnti, float thick, bool isCameraDis) {

		//描画座標.
		DBL_XY newPos[2] = { line.stPos, line.edPos };
		//カメラ基準に変換.
		if (isCameraDis) {
			for (auto& i : newPos) { i -= Camera::GetCameraPos(); }
		}

		//アンチエイリアスあり.
		if (isAnti) {
			int err = DrawLineAA(
				_flt(newPos[0].x), _flt(newPos[0].y),
				_flt(newPos[1].x), _flt(newPos[1].y), line.color.GetColorCode(), thick
			);
			if (err < 0) {
				return {-1, _T("DrawLineKR"), _T("DrawLineAAエラー")};
			}
		}
		//アンチエイリアスなし.
		else {
			int err = DrawLine(
				_int_r(newPos[0].x), _int_r(newPos[0].y),
				_int_r(newPos[1].x), _int_r(newPos[1].y), line.color.GetColorCode(), _int(thick)
			);
			if (err < 0) {
				return {-2, _T("DrawLineKR"), _T("DrawLineエラー")};
			}
		}
		return {0, _T("DrawLineKR"), _T("正常終了")};
	}
	
	/*
	   扇形を描画(オリジナル図形)
	*/
	ResultInt DrawPieKR(const Pie& pie, bool isAnti, float thick, bool isCameraDis) {

		DrawArcKR(pie, isCameraDis, isAnti, thick); //そのまま弧も描く.

		//描画座標.
		DBL_XY newPos = pie.pos;
		//カメラ基準に変換.
		if (isCameraDis) { newPos -= Camera::GetCameraPos(); }

		Line line;     //描画用の線.
		ResultInt err; //エラー判定用.

		//ベクトルを求める.
		DBL_XY vec1 = Calc::CalcVectorDeg(pie.stAng);             //扇の始まりの角度.
		DBL_XY vec2 = Calc::CalcVectorDeg(pie.stAng+pie.arcAng); //扇の終わりの角度.
		//座標を求める.
		DBL_XY pos1 = newPos + vec1 * pie.r;
		DBL_XY pos2 = newPos + vec2 * pie.r;
		//線1を描画.
		line = { pos1, newPos, pie.color };
		err = DrawLineKR(line, isAnti, thick);
		if (err.GetCode() < 0) {
			return {-1, _T("DrawPieKR"), _T("DrawLineKR 1つ目エラー")};
		}
		//線2を描画.
		line = { pos2, newPos, pie.color };
		err = DrawLineKR(line, isAnti, thick);
		if (err.GetCode() < 0) {
			return {-2, _T("DrawPieKR"), _T("DrawLineKR 2つ目エラー")};
		}
		return {0, _T("DrawPieKR"), _T("正常終了")};
	}
	
	/*
	   円弧を描画(オリジナル図形)
	*/
	ResultInt DrawArcKR(const Pie& pie, bool isAnti, float thick, bool isCameraDis) {

		//描画座標.
		DBL_XY newPos = pie.pos;
		//カメラ基準に変換.
		if (isCameraDis) { newPos -= Camera::GetCameraPos(); }

		const double addAng = 1.0;                    //一度で描く線の長さ.
		const double edAng  = pie.stAng + pie.arcAng; //弧の終わりの角度.

		for (double i = pie.stAng; i <= edAng-addAng; i += addAng) {
			//角度の設定.
			double ang1 = i - 1;
			ang1 = max(ang1, pie.stAng); //下限.
			double ang2 = i + addAng + 1;
			ang2 = min(ang2, edAng);      //上限.
			//座標の設定.
			DBL_XY pos1 = Calc::CalcArcPos(newPos, ang1, pie.r); //繋ぎ目が綺麗になるよう角度を-1する.
			DBL_XY pos2 = Calc::CalcArcPos(newPos, ang2, pie.r); //繋ぎ目が綺麗になるよう角度を+1する.
			Line line = { pos1, pos2, pie.color };
			//線を描画.
			ResultInt err = DrawLineKR(line, isAnti, thick);
			if (err.GetCode() < 0) {
				return {-1, _T("DrawArcKR"), _T("DrawLineKRエラー")};
			}
		}
		return {0, _T("DrawArcKR"), _T("正常終了")};
	}
	
	/*
	   画面全体にグリッド線を描画.
	*/
	ResultInt DrawWindowGrid(int wid, int hei, int size, MY_COLOR clrWid, MY_COLOR clrHei) {

		//縦線の描画.
		for (int x = 0; x < wid; x += size) {

			Line line = { {_dbl(x), 0}, {_dbl(x), _dbl(hei)}, clrHei };
			ResultInt err = DrawLineKR(line);
			if (err.GetCode() < 0) {
				return {-1, _T("DrawWindowGrid"), _T("縦線でエラー")};
			}
		}
		//横線の描画.
		for (int y = 0; y < hei; y += size) {

			Line line = { {0, _dbl(y)}, {_dbl(wid), _dbl(y)}, clrWid };
			ResultInt err = DrawLineKR(line);
			if (err.GetCode() < 0) {
				return {-2, _T("DrawWindowGrid"), _T("横線でエラー")};
			}
		}
		return {0, _T("DrawWindowGrid"), _T("正常終了")};
	}

	/*
	   キューブ(3D)[試作品]
	*/
	ResultInt DrawBox3DKR(const Box3D& box, bool isFill, bool isCameraDis) {

		//描画座標.
		DBL_XYZ newPos[2] = { box.stPos, box.edPos };
		//カメラ基準に変換.
		if (isCameraDis) { 
			for (auto& i : newPos) { i -= Camera::GetPos3D(); }
		}

		//座標.
		VECTOR vec1 = { newPos[0].x, newPos[0].y, newPos[0].z };
		VECTOR vec2 = { newPos[1].x, newPos[1].y, newPos[1].z };
		//描画.
		int err = DrawCube3D(vec1, vec2, box.difColor.GetColorCode(), box.spcColor.GetColorCode(), isFill);
		if (err < 0) {
			return {-1, _T("DrawBox3DKR"), _T("描画エラー")};
		}
		return {0, _T("DrawBox3DKR"), _T("正常終了")};
	}

	//描画モード変更.
	ResultInt SetDrawBlendModeKR(BlendModeID id, int power) {
		//設定.
		if (SetDrawBlendMode(_int(id), power) < 0) {
			return {-1, _T("SetDrawBlendModeKR"), _T("エラー") };
		}
		return {0, _T("SetDrawBlendModeKR"), _T("正常終了")};
	}
	ResultInt SetDrawBlendModeKR(BlendModeID id, double power) {
		return SetDrawBlendModeKR(id, _int_r(power));
	}
	//描画モードリセット.
	ResultInt ResetDrawBlendMode() {
		return SetDrawBlendModeKR(BlendModeID::None, 255);
	}
}