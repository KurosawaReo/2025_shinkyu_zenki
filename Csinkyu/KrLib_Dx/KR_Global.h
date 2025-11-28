/*
   - KR_Global.h - (DxLib)
   ver: 2025/11/29

   KrLib全体で使う汎用機能を追加。
*/
#pragma once

//このヘッダが定義されているか判別する用.
#define DEF_KR_DXLIB_GLOBAL

//C言語用.
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
//C++用.
#include <cassert>   //assert.h をラップしたもの.
#include <cstdlib>   //stdlib.h をラップしたもの.
#include <ctime>     //time.h   をラップしたもの.
//C++用のKrLibを導入.
#if !defined DEF_KR_CPP_GLOBAL
  #include "../KrLib_cpp/KR_Global.h"
#endif
//DxLib.
#include "DxLib.h"

//KrLib名前空間.
namespace KR
{
	//RGBAデータ(COLOR_U8とほぼ同じだが、こっちでは順をrgbにする)
	struct RGBA
	{
		BYTE r, g, b, a;
	};
	//色.
	enum class ColorID
	{
		Red,
		Orange,
		Yellow,
		Lime,
		Green,
		Cyan,
		Blue,
		Purple,
		Pink,
		Magenta,
		White,
		Gray,
		Black,
	};
	//色データ.
	class MY_COLOR
	{
	private:
		RGBA color;

	public:
		//constructor.
		MY_COLOR()                               : color{_byte(255), _byte(255), _byte(255), _byte(255)} {}
		MY_COLOR(int _r, int _g, int _b)         : color{_byte(_r),  _byte(_g),  _byte(_b),  _byte(255)} {}
		MY_COLOR(int _r, int _g, int _b, int _a) : color{_byte(_r) , _byte(_g),  _byte(_b),  _byte(_a) } {}
		MY_COLOR(UINT _colorCode);
		MY_COLOR(ColorID id);
		//get.
		COLOR_U8 GetColorU8()   const;
		UINT     GetColorCode() const;

		//代入演算子.
		void operator=(const RGBA& rgba);
		void operator=(UINT colorCode);
		void operator=(ColorID id);
	};

	//円データ.
	struct Circle
	{
		DBL_XY   pos;    //座標.
		float    r;      //半径.
		MY_COLOR color;  //色.
	};
	//四角形データ.
	struct Box
	{
		DBL_XY   pos;    //座標.
		DBL_XY   size;   //サイズ.
		MY_COLOR color;  //色.
	};
	//三角形データ.
	struct Triangle
	{
		DBL_XY   pos[3]; //3点の座標.
		MY_COLOR color;  //色.
	};
	//線データ.
	struct Line
	{
		DBL_XY   stPos; //始点座標.
		DBL_XY   edPos; //終点座標.
		MY_COLOR color; //色.
	};
	//扇形データ.
	struct Pie
	{
		DBL_XY   pos;    //中心座標.
		double   r;      //半径.
		double   stAng;  //開始角度.
		double   arcAng; //弧の角度.
		MY_COLOR color;  //色.
	};
}