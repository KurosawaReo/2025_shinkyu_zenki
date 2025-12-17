/*
   - KR_Draw.h - (DxLib)
   ver: 2025/12/17

   描画機能を追加。
   (オブジェクト指向ver → KR_Object)
*/
#pragma once
//KR_Globalが入ってなければここで導入.
#if !defined DEF_KR_DX_GLOBAL
  #include "KR_Global.h"
#endif

//KrLib名前空間.
namespace KR
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
	enum class Anchor
	{
		LU,	U,   RU, //例: Anchor::LU = Left Up.
		L,  Mid, R,
		LD,	D,   RD,
	};

	//画像クラス.
	class DrawImg
	{
		friend class DrawImgMng; //アクセス許可.

	//▼ ===== 変数 ===== ▼.
	private:
		Image img{}; //画像データ.

	//▼ ===== 関数 ===== ▼.
	private:
		ResultInt LoadFile(MY_STRING fileName); //読み込み.
		void      Release ();                   //解放.

	public:
		//constructor, destructor.
		//std::mapを使う関係でpublicに入れておく.
		DrawImg();
		~DrawImg();
		//get.
		INT_XY    GetSize() const { return img.size; }

		//描画.
		ResultInt Draw      (DBL_XY pos,                                                   Anchor anc = Anchor::Mid, bool isTrans = true, bool isFloat = false, bool isCameraDis = true) const;
		ResultInt DrawRect  (DBL_XY pos, DBL_RECT rect,                                    Anchor anc = Anchor::Mid, bool isTrans = true, bool isFloat = false, bool isCameraDis = true) const;
		ResultInt DrawExtend(DBL_XY pos, DBL_XY sizeRate,                                  Anchor anc = Anchor::Mid, bool isTrans = true, bool isFloat = false, bool isCameraDis = true) const;
		ResultInt DrawRota  (DBL_XY pos, double extend, double ang, INT_XY pivot = {0, 0},                           bool isTrans = true, bool isFloat = false, bool isCameraDis = true) const;
		ResultInt DrawModi  (DBL_XY luPos, DBL_XY ruPos, DBL_XY rdPos, DBL_XY ldPos,                                 bool isTrans = true, bool isFloat = false, bool isCameraDis = true) const;

		//使用禁止(「=」で実体が複製されて、意図せずデストラクタが実行されるのを防ぐため)
		DrawImg& operator=(const DrawImg&) = delete;
	};

	//画像管理クラス[staticクラス]
	class DrawImgMng final
	{
	//▼ ===== 実体 ===== ▼.
	private:
		static DrawImgMng inst; //実体を入れる用.

	//▼ ===== 変数 ===== ▼.
	private:
		umap<string, DrawImg> images; //画像データ.

	//▼ ===== 関数 ===== ▼.
	private:
		//constructor(新規作成できなくする)
		DrawImgMng(){}
		//destructor.
		~DrawImgMng();

	public:
		//get.
		static DrawImg*  Get     (string saveName);
		static bool      TryGet  (string saveName, DrawImg* ptr);
		
		static ResultInt LoadFile(MY_STRING fileName, string saveName); //読み込み.

		//使用禁止.
		DrawImgMng(const DrawImgMng&) = delete;
		DrawImgMng& operator=(const DrawImgMng&) = delete;
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
		ResultInt Draw	  (                                                                         Anchor anc = Anchor::Mid, int font = -1, bool isCameraDis = true);
		ResultInt DrawRota(INT_XY extend, INT_XY pivot, double ang, bool isVertical,                                          int font = -1, bool isCameraDis = true);
		ResultInt DrawModi(INT_XY luPos, INT_XY ruPos, INT_XY rdPos, INT_XY ldPos, bool isVertical,                           int font = -1, bool isCameraDis = true);
		//その他.
		INT_XY    GetTextSize(int font = -1);
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
		int  GetFont() const { return handle; }
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
		void Draw(bool isClose = false, bool isCameraDis = true);
	};

	//図形(2D)
	ResultInt DrawCircleKR		(const Circle&   cir,                            bool isFill = true, bool isAnti = false, float thick = 1.0f, bool isCameraDis = true);
	ResultInt DrawBoxKR			(const Box&      box,  Anchor anc = Anchor::Mid, bool isFill = true, bool isAnti = false,                     bool isCameraDis = true);
	ResultInt DrawTriangleKR	(const Triangle& tri,                            bool isFill = true, bool isAnti = false,                     bool isCameraDis = true);
	ResultInt DrawLineKR		(const Line&     line,                                               bool isAnti = false, float thick = 1.0f, bool isCameraDis = true);
	ResultInt DrawPieKR			(const Pie&      pie,                                                bool isAnti = false, float thick = 1.0f, bool isCameraDis = true);
	ResultInt DrawArcKR			(const Pie&      pie,                                                bool isAnti = false, float thick = 1.0f, bool isCameraDis = true);
	ResultInt DrawWindowGrid	(int wid, int hei, int size, MY_COLOR clrWid = {160, 160, 255}, MY_COLOR clrHei = {255, 160, 160});

	//図形(3D)[試作品]
	ResultInt DrawBox3DKR		(const Box3D& box, bool isFill = true, bool isCameraDis = true);

	//描画モード.
	ResultInt SetDrawBlendModeKR(BlendModeID id, int    power = 255);
	ResultInt SetDrawBlendModeKR(BlendModeID id, double power = 255);
	ResultInt ResetDrawBlendMode();
}