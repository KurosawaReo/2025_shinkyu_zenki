/*
   - myDrawST.h - (original)
   ver.2025/08/20

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
	MODE_ALPHA = DX_BLENDMODE_ALPHA,   //αブレンド.  (重なると透過する)
	MODE_ADD   = DX_BLENDMODE_ADD,     //加算ブレンド.(重なると明度が明るくなる)
	MODE_SUB   = DX_BLENDMODE_SUB,     //減算ブレンド.(重なると明度が暗くなる)
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
	MY_STRING text;  //テキスト.
	INT_XY    pos;   //画面のどこに描画するか.
	UINT      color; //文字の色.
};
//アンカー(描画の基準点)
enum Anchor
{
	ANC_LU,	ANC_U,   ANC_RU, //例:ANC_LU = Left Up.
	ANC_L,  ANC_MID, ANC_R,
	ANC_DL,	ANC_D,   ANC_DR,
};

//画像描画クラス.
class DrawImgST
{
private:
	Image data; //画像データ.

public:
	//デストラクタ.
	~DrawImgST() {
		DeleteGraph(data.handle); //画像解放.
	}
	//set, get.
	void   SetImage(Image* _data) { data = *_data; }
	Image* GetImage()             { return &data; }
	//読み込み.
	int LoadGraphST      (MY_STRING fileName);
	//描画.
	int DrawGraphST      (DBL_XY pos,                                              Anchor anc = ANC_MID, bool isTrans = true, bool isFloat = false);
	int DrawRectGraphST  (DBL_XY pos,   INT_XY stPos,  INT_XY size,                                      bool isTrans = true, bool isFloat = false);
	int DrawExtendGraphST(DBL_XY pos,   DBL_XY sizeRate,                           Anchor anc = ANC_MID, bool isTrans = true, bool isFloat = false);
	int DrawRotaGraphST  (DBL_XY pos,   double extend, double ang,                 Anchor anc = ANC_MID, bool isTrans = true, bool isFloat = false);
	int DrawModiGraphST  (DBL_XY luPos, DBL_XY ruPos,  DBL_XY rdPos, DBL_XY ldPos,                       bool isTrans = true, bool isFloat = false);

	//使用禁止(意図しないDeleteGraphを防ぐため)
	DrawImgST& operator=(const DrawImgST&) = delete;
};

//画像描画クラス(分割読み込み)
class DrawDivImgST
{
private:
	vector<Image> data; //画像データ.

public:
	//デストラクタ.
	~DrawDivImgST() {
		for (auto& i : data) {
			DeleteGraph(i.handle); //画像解放.
		}
	}
	//set, get.
	void SetImage(Image* _data, int imgNo) {
		//サイズをオーバーしてないなら.
		if (imgNo >= 0 && imgNo < data.size()) {
			data[imgNo] = *_data;
		}
	}
	Image* GetImage(int imgNo) {
		//サイズをオーバーしてないなら.
		if (imgNo >= 0 && imgNo < data.size()) {
			return &data[imgNo];
		}
		return nullptr; //nullを返す.
	}
	//読み込み.
	int LoadDivGraphST   (MY_STRING fileName, INT_XY size, INT_XY cnt);
	//描画.
	int DrawGraphST      (int imgNo, DBL_XY pos,                                              Anchor anc = ANC_MID, bool isTrans = true, bool isFloat = false);
	int DrawRectGraphST  (int imgNo, DBL_XY pos,   INT_XY stPos , INT_XY size,                                      bool isTrans = true, bool isFloat = false);
	int DrawExtendGraphST(int imgNo, DBL_XY pos,   DBL_XY sizeRate,                           Anchor anc = ANC_MID, bool isTrans = true, bool isFloat = false);
	int DrawRotaGraphST  (int imgNo, DBL_XY pos,   double extend, double ang,                 Anchor anc = ANC_MID, bool isTrans = true, bool isFloat = false);
	int DrawModiGraphST  (int imgNo, DBL_XY luPos, DBL_XY ruPos,  DBL_XY rdPos, DBL_XY ldPos,                       bool isTrans = true, bool isFloat = false);

	//使用禁止(意図しないDeleteGraphを防ぐため)
	DrawDivImgST& operator=(const DrawDivImgST&) = delete;
};

//テキスト描画クラス.
class DrawStrST
{
private:
	String data; //文字列データ.

public:
	//初期化用.
	DrawStrST(MY_STRING _text, INT_XY _pos, UINT _color) :
		data{_text, _pos, _color}
	{}
	//set.
	void SetText(MY_STRING _text) {
		data.text = _text;
	}
	void SetPos(int _x, int _y) {
		data.pos = {_x, _y};
	}
	void SetColor(UINT _color) {
		data.color = _color;
	}
	//get.
	INT_XY GetPos() {
		return data.pos;
	}
	//描画.
	int    DrawStringST	   (Anchor anc = ANC_MID, int font = -1);
	int    DrawRotaStringST(INT_XY extend, INT_XY pivot, double ang, bool isVertical, int font = -1);
	int    DrawModiStringST(INT_XY luPos, INT_XY ruPos, INT_XY rdPos, INT_XY ldPos, bool isVertical, int font = -1);
	INT_XY GetTextSize 	   (MY_STRING str, int font = -1);
};

//図形.
int    DrawCircleST		 (const Circle*   data,                       bool isFill = true, bool isAnti = false, float thick = 1);
int    DrawBoxST		 (const Box*      data, Anchor anc = ANC_MID, bool isFill = true, bool isAnti = false);
int    DrawTriangleST	 (const Triangle* data,                       bool isFill = true, bool isAnti = false);
int    DrawLineST		 (const Line*     data,                                           bool isAnti = false, float thick = 1.0f);
int    DrawWindowGrid	 (int wid, int hei, int size, UINT clrWid = 0xA0A0FF, UINT clrHei = 0xFFA0A0);

//フォント.
int    CreateFontH       (int size, int thick, FontTypeID fontId = FONT_NONE);

//描画モード.
int    SetDrawBlendModeST(BlendModeID id, int    power = 255);
int    SetDrawBlendModeST(BlendModeID id, double power = 255);
int    ResetDrawBlendMode();