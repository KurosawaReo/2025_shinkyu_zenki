/*
   - myDrawST.cpp - (original)

   DxLibで使う用のオリジナル描画関数.
*/
#pragma once

#if !defined DEF_INT_XY
#define DEF_INT_XY
//xとyの凝縮体.
struct INT_XY
{
	int x;
	int y;
};
#endif

//画像データ格納用.
struct IMG
{
	int    handle;	 //ハンドル.
	INT_XY size;	 //画像のサイズ.
};
//画像描画に使う用.
struct IMG_DRAW
{
	IMG    img;      //画像データ.
	
	INT_XY pos;      //画面のどこに描画するか.

	BOOL   isCenter; //中央基準にするか.
	BOOL   isTrans;  //透過の可否.
};
struct IMG_DRAW_RECT
{
	IMG    img;      //画像データ.

	INT_XY pos;      //画面のどこに描画するか.(左上座標基準)
	INT_XY stPxl;    //始点pixel.
	INT_XY size;     //切り取るサイズ.

	BOOL   isTrans;  //透過の可否.
};
//文字描画に使う用.
struct STR_DRAW
{
	TCHAR  text[256]{};        //テキスト.
	INT_XY pos   = {0, 0};     //画面のどこに描画するか.
	UINT   color = 0xFFFFFF;   //文字の色.
};
struct STR_DRAW_ROTA
{
	TCHAR  text[256]{};        //テキスト.
	INT_XY pos    = {0, 0};    //画面のどこに描画するか.
	INT_XY extend = {1, 1};    //伸縮倍率.
	INT_XY pivot  = {0, 0};    //回転基準点.
	double ang    = 0;         //回転度.
	UINT   color  = 0xFFFFFF;  //文字の色.

	BOOL   isVertical = FALSE; //縦書きにするか.
};
struct STR_DRAW_MODI
{
	TCHAR  text[256]{};        //テキスト.
	INT_XY luPos = {  0,  0};  //テキストの左上座標.
	INT_XY ruPos = {100,  0};  //テキストの右上座標.
	INT_XY rdPos = {100, 30};  //テキストの右下座標.
	INT_XY ldPos = {  0, 30};  //テキストの左下座標.
	UINT   color = 0xFFFFFF;   //文字の色.

	BOOL   isVertical = FALSE; //縦書きにするか.
};

INT_XY DrawLineAng     (INT_XY pos, float ang, float len, int clr, int thick = 1);

int    LoadGraphST     (IMG* img, const TCHAR* fileName);
int    DrawGraphST     (const IMG_DRAW*      data);
int    DrawRectGraphST (const IMG_DRAW_RECT* data);

int    DrawStringST    (const STR_DRAW*      data, int font = -1);
int    DrawRotaStringST(const STR_DRAW_ROTA* data, int font = -1);
int    DrawModiStringST(const STR_DRAW_MODI* data, int font = -1);