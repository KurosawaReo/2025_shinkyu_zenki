/*
   - KR_Global.h - (DxLib)
   ver: 2025/10/03

   KR_Lib全体で使う汎用機能を追加します。
*/
#pragma once

//このヘッダが定義されているか判別する用.
#define DEF_KR_GLOBAL

//C言語用.
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
//C++用.
#include <vector>
#include <map>
#include <string>
#include <cassert>   //assert.h をラップしたもの.
#include <cmath>     //math.h   をラップしたもの.
#include <cstdlib>   //stdlib.h をラップしたもの.
#include <ctime>     //time.h   をラップしたもの.
using namespace std;
//DxLib.
#include "DxLib.h"

//型変換マクロ.
#define _int(n)   static_cast<int>   (n)        //int型変換マクロ.
#define _int_r(n) static_cast<int>   (round(n)) //int型変換マクロ(四捨五入)
#define _flt(n)   static_cast<float> (n)        //float型変換マクロ.
#define _dbl(n)   static_cast<double>(n)        //double型変換マクロ.
//便利マクロ.
#define _if_check(n)              assert(n); if(n)             //if文の前に同条件のassertを挟む.
#define _return(num, cond)        if (cond) { return num; }    //条件に合うならreturnする.(cond = 条件)
#define _is_in_range(num, n1, n2) ((n1 <= num) && (num <= n2)) //範囲内に数値があるかどうか.
#define _get_name(value)          #value                       //名前を取得(変数名など)
//template用マクロ.
#define _type_num_only(T)		  typename = typename enable_if<is_arithmetic<T>::value>::type //算術型(int/float/double/char)のみOKとし, そうでない場合は関数を無効にする.

//KR_Libに使う用.
namespace KR_Lib
{
	//文字コードで切り替え.
#if defined UNICODE
	using MY_STRING = wstring; //wchar_t型.
#else
	using MY_STRING = string;  //char型.
#endif

	//xとyの凝縮.
	template<typename T> //型を<>で入力して使う.
	struct XY
	{
		T x, y;

		//constructor.
		XY()           : x(0),  y(0)  {}
		XY(T _x, T _y) : x(_x), y(_y) {} //INT_XY n = {1, 0}; この書き方ができる.

		//int型に変換.
		XY<int> ToIntXY() const {
			return {_int_r(x), _int_r(y)};
		}
		//double型に変換.
		XY<double> ToDblXY() const {
			return {_dbl(x), _dbl(y)};
		}
		//加算した結果を返す.
		XY<T> Add(T _x, T _y) const {
			return {x+_x, y+_y};
		}
		XY<T> Add(XY<T> _xy) const {
			return {x+_xy.x, y+_xy.y};
		}

		//演算子[+,-,*,/] [XY<T>・XY<T>]
		XY<T> operator+(const XY<T>& value) const {  //+の右側が引数に入り、返り値が左側に入る.
			return { x + value.x, y + value.y };     //xとyを加算して返す.
		}
		XY<T> operator-(const XY<T>& value) const {
			return { x - value.x, y - value.y };
		}
		XY<T> operator*(const XY<T>& value) const {
			return { x * value.x, y * value.y };
		}
		XY<T> operator/(const XY<T>& value) const {
			return { x / value.x, y / value.y };
		}
		//演算子[+=,-=,*=,/=] [XY<T>・XY<T>]
		XY<T>& operator+=(const XY<T>& xy) {
			x += xy.x;
			y += xy.y;
			return *this; //自身の実体.
		}
		XY<T>& operator-=(const XY<T>& xy) {
			x -= xy.x;
			y -= xy.y;
			return *this;
		}
		XY<T>& operator*=(const XY<T>& xy) {
			x *= xy.x;
			y *= xy.y;
			return *this;
		}
		XY<T>& operator/=(const XY<T>& xy) {
			x /= xy.x;
			y /= xy.y;
			return *this;
		}

		//演算子[+,-,*,/] [XY<T>・数値]
		//右側が数値でなければ無効にする.
		template<typename T2, _type_num_only(T2)>
		XY<T> operator+(T2 num) const {
			return { x + static_cast<T>(num), y + static_cast<T>(num) }; //cast後にxとyを加算して返す.
		}
		template<typename T2, _type_num_only(T2)>
		XY<T> operator-(T2 num) const {
			return { x - static_cast<T>(num), y - static_cast<T>(num) };
		}
		template<typename T2, _type_num_only(T2)>
		XY<T> operator*(T2 num) const {
			return { x * static_cast<T>(num), y * static_cast<T>(num) };
		}
		template<typename T2, _type_num_only(T2)>
		XY<T> operator/(T2 num) const {
			return { x / static_cast<T>(num), y / static_cast<T>(num) };
		}
		//演算子[+=,-=,*=,/=] [XY<T>・数値]
		//右側が数値でなければ無効にする.
		template<typename T2, _type_num_only(T2)>
		XY<T>& operator+=(T2 num) {
			x += num;
			y += num;
			return *this; //自身の実体.
		}
		template<typename T2, _type_num_only(T2)>
		XY<T>& operator-=(T2 num) {
			x -= num;
			y -= num;
			return *this;
		}
		template<typename T2, _type_num_only(T2)>
		XY<T>& operator*=(T2 num) {
			x *= num;
			y *= num;
			return *this;
		}
		template<typename T2, _type_num_only(T2)>
		XY<T>& operator/=(T2 num) {
			x /= num;
			y /= num;
			return *this;
		}
	};
	using INT_XY = XY<int>;    //int型.
	using DBL_XY = XY<double>; //double型.
	
	//RGBAデータ(COLOR_U8とほぼ同じだが、こっちでは順をrgbにする)
	struct RGBA
	{
		BYTE r, g, b, a;
	};
	//色データ.
	class MY_COLOR
	{
	private:
		RGBA color;

	public:
		//constructor.
		MY_COLOR()                               : color{255, 255, 255, 255} {}
		MY_COLOR(int _r, int _g, int _b)         : color{static_cast<BYTE>(_r), static_cast<BYTE>(_g), static_cast<BYTE>(_b), 255} {}
		MY_COLOR(int _r, int _g, int _b, int _a) : color{static_cast<BYTE>(_r), static_cast<BYTE>(_g), static_cast<BYTE>(_b), static_cast<BYTE>(_a)} {}
		MY_COLOR(UINT _colorCode);
		//get.
		COLOR_U8 GetColorU8()   const { return {color.b, color.g, color.r, color.a}; }
		UINT     GetColorCode() const { return DxLib::GetColor(color.r, color.g, color.b); }

		//代入用.
		void operator=(const RGBA& rgba);
		void operator=(UINT colorCode);
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