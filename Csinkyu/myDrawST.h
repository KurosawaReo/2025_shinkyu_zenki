/*
   - myDrawST.h - (original)
   ver.2025/07/27

   DxLib: オリジナル描画機能の追加.
*/
#pragma once

//フォントタイプID(入力しやすくする用)
enum FontTypeID
{
	FONT_NORMAL = DX_FONTTYPE_NORMAL,
	FONT_EDGE   = DX_FONTTYPE_EDGE,
	FONT_ANTI   = DX_FONTTYPE_ANTIALIASING, //アンチエイリアス(滑らかになる)

	FONT_NONE   = -1, //指定なし.
};
//描画モードID(入力しやすくする用)
enum BlendModeID
{
	MODE_NONE  = DX_BLENDMODE_NOBLEND, //デフォルト.
	MODE_ALPHA = DX_BLENDMODE_ALPHA,   //αブレンド.
	MODE_ADD   = DX_BLENDMODE_ADD,     //加算ブレンド.
	MODE_SUB   = DX_BLENDMODE_SUB,     //減算ブレンド.
	MODE_MUL   = DX_BLENDMODE_MUL      //乗算ブレンド.
};

//画像データ.
struct Image
{
	int    handle; //ハンドル.
	INT_XY size;   //画像のサイズ.
};
//文字列データ.
struct String
{
	my_string text; //テキスト.
	INT_XY    pos;  //画面のどこに描画するか.
	UINT      clr;  //文字の色.
};

//画像描画クラス.
class DrawImgST
{
private:
	vector<Image> img; //画像データ.

public:
	//読み込み.
	int LoadGraphST   (my_string fileName);
	int LoadDivGraphST(my_string fileName, INT_XY size, INT_XY cnt);
	//描画.
	int DrawGraphST      (int imgNo, INT_XY pos, BOOL isCenter, BOOL isTrans = TRUE);
	int DrawRectGraphST  (int imgNo, INT_XY pos, INT_XY stPxl, INT_XY size, BOOL isTrans = TRUE);
	int DrawExtendGraphST(int imgNo, INT_XY pos, DBL_XY sizeRate, BOOL isCenter, BOOL isTrans = TRUE);
	int DrawRotaGraphST  (int imgNo, INT_XY pos, double extend, double ang, BOOL isCenter, BOOL isTrans = TRUE);
};

//テキスト描画クラス.
class DrawStrST
{
private:
	String str; //文字列データ.

public:
	//初期化用.
	DrawStrST(my_string _text, INT_XY _pos, UINT _clr) :
		str{_text, _pos, _clr}
	{}
	//set.
	void SetText(my_string _text) {
		str.text = _text;
	}
	void SetPos(int _x, int _y) {
		str.pos = {_x, _y};
	}
	void SetColor(UINT _color) {
		str.clr = _color;
	}
	//描画.
	int    DrawStringST	   (BOOL isCenter, int font = -1);
	int    DrawRotaStringST(INT_XY extend, INT_XY pivot, double ang, BOOL isVertical, int font = -1);
	int    DrawModiStringST(INT_XY luPos, INT_XY ruPos, INT_XY rdPos, INT_XY ldPos, BOOL isVertical, int font = -1);
	INT_XY GetTextSize 	   (my_string str, int font = -1);
};

//図形.
int    DrawCircleST		 (const Circle*   data, BOOL isFill = TRUE, BOOL isAnti = FALSE, float thick = 1);
int    DrawBoxST		 (const Box*      data, BOOL isCenter, BOOL isFill = TRUE, BOOL isAnti = FALSE);
int    DrawTriangleST	 (const Triangle* data, BOOL isFill = TRUE, BOOL isAnti = FALSE);
int    DrawLineST		 (const Line*     data, BOOL isAnti = FALSE, float thick = 1.0f);
int    DrawWindowGrid	 (int wid, int hei, int size, UINT clrWid = 0xA0A0FF, UINT clrHei = 0xFFA0A0);

//フォント.
int    CreateFontH       (int size, int thick, FontTypeID fontId = FONT_NONE);

//描画モード.
int    SetDrawBlendModeST(BlendModeID id, int    power = 255);
int    SetDrawBlendModeST(BlendModeID id, double power = 255);
int    ResetDrawBlendMode();