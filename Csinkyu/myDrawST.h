/*
   - myDrawST.h - (original)
   ver.2025/07/26

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

//画像描画に使う用.
struct DrawImg
{
	Image  img;    //画像データ.
	INT_XY pos;    //画面のどこに描画するか.
};
struct DrawImgRect : public DrawImg
{
	INT_XY stPxl;  //始点pixel.
	INT_XY size;   //切り取るサイズ.
};
struct DrawImgExtend : public DrawImg
{
	INT_XY size;   //描画するサイズ.
};
struct DrawImgRota : public DrawImg
{
	double extend; //サイズ倍率.
	double ang;    //角度.
};
//文字描画に使う用.
struct DrawStr
{
	TCHAR  text[256]{};      //テキスト.
	INT_XY pos;              //画面のどこに描画するか.
	UINT   color = 0xFFFFFF; //文字の色.
};
struct DrawStrRota : public DrawStr
{
	INT_XY extend = {1, 1};  //伸縮倍率.
	INT_XY pivot  = {0, 0};  //回転基準点.
	double ang    = 0;       //回転度.
};
struct DrawStrModi : public DrawStr
{
	INT_XY luPos;            //テキストの左上座標.
	INT_XY ruPos;            //テキストの右上座標.
	INT_XY rdPos;            //テキストの右下座標.
	INT_XY ldPos;            //テキストの左下座標.
};

//図形.
int    DrawCircleST		 (const Circle*   data, BOOL isFill = TRUE, BOOL isAnti = FALSE, float thick = 1);
int    DrawBoxST		 (const Box*      data, BOOL isCenter, BOOL isFill = TRUE, BOOL isAnti = FALSE);
int    DrawTriangleST	 (const Triangle* data, BOOL isFill = TRUE, BOOL isAnti = FALSE);
int    DrawLineST		 (const Line*     data, BOOL isAnti = FALSE, float thick = 1.0f);
int    DrawWindowGrid	 (int wid, int hei, int size, UINT clrWid = 0xA0A0FF, UINT clrHei = 0xFFA0A0);

//画像.
int    LoadGraphST		 (Image* img, my_string fileName);
int    LoadDivGraphST	 (vector<Image>* img, my_string fileName, INT_XY size, INT_XY cnt);
int    DrawGraphST		 (const DrawImg*       data, BOOL isCenter, BOOL isTrans = TRUE);
int    DrawRectGraphST	 (const DrawImgRect*   data, BOOL isTrans = TRUE);
int    DrawExtendGraphST (const DrawImgExtend* data, BOOL isCenter, BOOL isTrans = TRUE);
int    DrawRotaGraphST	 (const DrawImgRota*   data, BOOL isCenter, BOOL isTrans = TRUE);

//テキスト.
int    DrawStringST		 (const DrawStr*     data, BOOL isCenter,   int font = -1);
int    DrawRotaStringST	 (const DrawStrRota* data, BOOL isVertical, int font = -1);
int    DrawModiStringST	 (const DrawStrModi* data, BOOL isVertical, int font = -1);
INT_XY GetTextSize		 (my_string str, int font = -1);

//フォント.
int    CreateFontH		 (int size, int thick, FontTypeID fontId = FONT_NONE);

//オブジェクト.
int    DrawObjectCir	 (const ObjectCir*  data, BOOL isDrawHit = FALSE);
int    DrawObjectBox	 (const ObjectBox*  data, BOOL isDrawHit = FALSE);
int    DrawObjectGrid	 (const ObjectGrid* data, INT_XY gridPos, INT_XY gridSize);

//描画モード.
int    SetDrawBlendModeST(BlendModeID id, int    power = 255);
int    SetDrawBlendModeST(BlendModeID id, double power = 255);
int    ResetDrawBlendMode();