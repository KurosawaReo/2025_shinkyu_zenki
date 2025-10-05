/*
   - KR_Draw.h - (DxLib)
   ver: 2025/10/05

   描画機能を追加します。
   (オブジェクト指向ver → KR_Object)
*/
#pragma once

//KR_Libに使う用.
namespace KR_Lib
{
	//フォントタイプID(入力しやすくする用)
	enum class FontTypeID
	{
		Normal   = DX_FONTTYPE_NORMAL,
		Edge     = DX_FONTTYPE_EDGE,
		Anti     = DX_FONTTYPE_ANTIALIASING,      //アンチエイリアス(滑らかになる)
		AntiEdge = DX_FONTTYPE_ANTIALIASING_EDGE, //アンチエイリアス & エッジ

		None     = -1, //指定なし.
	};
	//描画モードID(入力しやすくする用)
	enum class BlendModeID
	{
		None  = DX_BLENDMODE_NOBLEND, //デフォルト.
		Alpha = DX_BLENDMODE_ALPHA,   //αブレンド.  (重なると透過する)
		Add   = DX_BLENDMODE_ADD,     //加算ブレンド.(重なると明度が明るくなる)
		Sub   = DX_BLENDMODE_SUB,     //減算ブレンド.(重なると明度が暗くなる)
		Mul   = DX_BLENDMODE_MUL      //乗算ブレンド.
	};

	//画像データ.
	struct Image
	{
		int    handle; //ハンドル.
		INT_XY size;   //画像のサイズ.
	};
	//アンカー(描画の基準点)
	enum Anchor
	{
		LU,	U,   RU, //例: Anchor::LU = Left Up.
		L,  Mid, R,
		DL,	D,   DR,
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
		//get.
		INT_XY GetSize() const { return data.size; }
		//読み込み.
		int LoadFile  (MY_STRING fileName);
		//描画.
		int Draw      (DBL_XY pos,                                                    Anchor anc = Anchor::Mid, bool isTrans = true, bool isFloat = false);
		int DrawRect  (DBL_XY pos, int left, int up, int right, int down,             Anchor anc = Anchor::Mid, bool isTrans = true, bool isFloat = false);
		int DrawExtend(DBL_XY pos, DBL_XY sizeRate,                                   Anchor anc = Anchor::Mid, bool isTrans = true, bool isFloat = false);
		int DrawRota  (DBL_XY pos, double extend,  double ang, INT_XY pivot = {0, 0}, Anchor anc = Anchor::Mid, bool isTrans = true, bool isFloat = false);
		int DrawModi  (DBL_XY luPos, DBL_XY ruPos, DBL_XY rdPos, DBL_XY ldPos,                                  bool isTrans = true, bool isFloat = false);

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
		//get.
		INT_XY GetSize(int imgNo) const { return data[imgNo].size; }
		//読み込み.
		int LoadFile  (MY_STRING fileName, INT_XY size, INT_XY cnt);
		//描画.
		int Draw      (int imgNo, DBL_XY pos,                                                   Anchor anc = Anchor::Mid, bool isTrans = true, bool isFloat = false);
		int DrawRect  (int imgNo, DBL_XY pos, int left, int up, int right, int down,            Anchor anc = Anchor::Mid, bool isTrans = true, bool isFloat = false);
		int DrawExtend(int imgNo, DBL_XY pos, DBL_XY sizeRate,                                  Anchor anc = Anchor::Mid, bool isTrans = true, bool isFloat = false);
		int DrawRota  (int imgNo, DBL_XY pos, double extend, double ang, INT_XY pivot = {0, 0}, Anchor anc = Anchor::Mid, bool isTrans = true, bool isFloat = false);
		int DrawModi  (int imgNo, DBL_XY luPos, DBL_XY ruPos, DBL_XY rdPos, DBL_XY ldPos,                                 bool isTrans = true, bool isFloat = false);

		//使用禁止(「=」で実体が複製されて、意図せずデストラクタが実行されるのを防ぐため)
		DrawDivImg& operator=(const DrawDivImg&) = delete;
	};

	//テキスト描画クラス.
	class DrawStr
	{
	public:
		MY_STRING text;  //テキスト.
		INT_XY    pos;   //画面のどこに描画するか.
		MY_COLOR  color; //文字の色.

		//constructor.
		DrawStr(MY_STRING _text, INT_XY _pos, MY_COLOR _color) : text(_text), pos(_pos), color(_color) {}

		//描画.
		int    Draw	   (Anchor anc = Anchor::Mid, int font = -1);
		int    DrawRota(INT_XY extend, INT_XY pivot, double ang, bool isVertical, int font = -1);
		int    DrawModi(INT_XY luPos, INT_XY ruPos, INT_XY rdPos, INT_XY ldPos, bool isVertical, int font = -1);
		//その他.
		INT_XY GetTextSize(int font = -1);
	};

	//フォントクラス.
	class Font
	{
	private:
		int handle;

	public:
		//constructor, destructor.
		Font();
		~Font();
		//get.
		int GetFont() const { return handle; }
		//フォント作成.
		void CreateFontH(MY_STRING fontName, int size, int thick, FontTypeID fontId = FontTypeID::None);

		//使用禁止(「=」で実体が複製されて、意図せずデストラクタが実行されるのを防ぐため)
		Font& operator=(const Font&) = delete;
	};

	//グラデーション線.
	class GradLine
	{
	private:
		vector<VERTEX2D> points; //頂点データ.

	public:
		//頂点追加.
		void AddPoint(DBL_XY pos, MY_COLOR color);
		//描画.
		void Draw(bool isClose = false);
	};

	//図形.
	int    DrawCircleKR		 (const Circle*   data,                           bool isFill = true, bool isAnti = false, float thick = 1.0f);
	int    DrawBoxKR		 (const Box*      data, Anchor anc = Anchor::Mid, bool isFill = true, bool isAnti = false);
	int    DrawTriangleKR	 (const Triangle* data,                           bool isFill = true, bool isAnti = false, float thick = 1.0f);
	int    DrawLineKR		 (const Line*     data,                                               bool isAnti = false, float thick = 1.0f);
	int    DrawPieKR		 (const Pie* pie,                                                     bool isAnti = false, float thick = 1.0f);
	int    DrawArcKR		 (const Pie* pie,                                                     bool isAnti = false, float thick = 1.0f);
	int    DrawWindowGrid	 (int wid, int hei, int size, MY_COLOR clrWid = {160, 160, 255}, MY_COLOR clrHei = {255, 160, 160});

	//描画モード.
	int    SetDrawBlendModeKR(BlendModeID id, int    power = 255);
	int    SetDrawBlendModeKR(BlendModeID id, double power = 255);
	int    ResetDrawBlendMode();
}