/*
   - KR_Draw.h - (kurosawa original)
   ver: 2025/08/23

   DxLib用の描画機能.
*/
#pragma once

//KR_Libに使う用.
namespace KR_Lib
{
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
	class DrawImg
	{
	private:
		Image data{}; //画像データ.

	public:
		//constructor, destructor.
		DrawImg();
		~DrawImg();
		//set, get.
		void   SetImage(Image* _data) { data = *_data; }
		Image* GetImage()             { return &data; }
		//読み込み.
		int LoadFile  (MY_STRING fileName);
		//描画.
		int Draw      (DBL_XY pos,                                              Anchor anc = ANC_MID, bool isTrans = true, bool isFloat = false);
		int DrawRect  (DBL_XY pos,   INT_XY stPos,  INT_XY size,                                      bool isTrans = true, bool isFloat = false);
		int DrawExtend(DBL_XY pos,   DBL_XY sizeRate,                           Anchor anc = ANC_MID, bool isTrans = true, bool isFloat = false);
		int DrawRota  (DBL_XY pos,   double extend, double ang,                 Anchor anc = ANC_MID, bool isTrans = true, bool isFloat = false);
		int DrawModi  (DBL_XY luPos, DBL_XY ruPos,  DBL_XY rdPos, DBL_XY ldPos,                       bool isTrans = true, bool isFloat = false);

		//使用禁止(「=」で実体が複製されて、意図せずデストラクタが実行されるのを防ぐため)
		DrawImg& operator=(const DrawImg&) = delete;
	};

	//画像描画クラス(分割読み込み)
	class DrawDivImg
	{
	private:
		vector<Image> data{}; //画像データ.

	public:
		//constructor, destructor.
		DrawDivImg();
		~DrawDivImg();
		//set, get.
		void   SetImage(Image* _data, int imgNo);
		Image* GetImage(int imgNo);
		//読み込み.
		int LoadFile  (MY_STRING fileName, INT_XY size, INT_XY cnt);
		//描画.
		int Draw      (int imgNo, DBL_XY pos,                                              Anchor anc = ANC_MID, bool isTrans = true, bool isFloat = false);
		int DrawRect  (int imgNo, DBL_XY pos,   INT_XY stPos , INT_XY size,                                      bool isTrans = true, bool isFloat = false);
		int DrawExtend(int imgNo, DBL_XY pos,   DBL_XY sizeRate,                           Anchor anc = ANC_MID, bool isTrans = true, bool isFloat = false);
		int DrawRota  (int imgNo, DBL_XY pos,   double extend, double ang,                 Anchor anc = ANC_MID, bool isTrans = true, bool isFloat = false);
		int DrawModi  (int imgNo, DBL_XY luPos, DBL_XY ruPos,  DBL_XY rdPos, DBL_XY ldPos,                       bool isTrans = true, bool isFloat = false);

		//使用禁止(「=」で実体が複製されて、意図せずデストラクタが実行されるのを防ぐため)
		DrawDivImg& operator=(const DrawDivImg&) = delete;
	};

	//テキスト描画クラス.
	class DrawStr
	{
	private:
		String data{}; //文字列データ.

	public:
		//constructor.
		DrawStr(MY_STRING _text, INT_XY _pos, UINT _color) :
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
		int    Draw	   (Anchor anc = ANC_MID, int font = -1);
		int    DrawRota(INT_XY extend, INT_XY pivot, double ang, bool isVertical, int font = -1);
		int    DrawModi(INT_XY luPos, INT_XY ruPos, INT_XY rdPos, INT_XY ldPos, bool isVertical, int font = -1);
		//その他.
		INT_XY GetTextSize(MY_STRING str, int font = -1);
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
}