/*
   - KR_Global.h - (kurosawa original)
   ver: 2025/08/23

   DxLib用のKR_Lib全体に使う汎用機能.
*/
#pragma once

//このヘッダが定義されているか判別する用.
#define DEF_KR_GLOBAL

//C言語用.
#define _USE_MATH_DEFINES
//C++用.
#include <vector>
#include <map>
#include <string>
#include <cassert> //assert.h をラップしたもの.
#include <cmath>   //math.h   をラップしたもの.
#include <cstdlib> //stdlib.h をラップしたもの.
#include <ctime>   //time.h   をラップしたもの.
using namespace std;
//DxLib.
#include "DxLib.h"

//型変換マクロ.
#define _int(n)   static_cast<int>   (n)        //int型変換マクロ.
#define _int_r(n) static_cast<int>   (round(n)) //int型変換マクロ(四捨五入)
#define _flt(n)   static_cast<float> (n)        //float型変換マクロ.
#define _dbl(n)   static_cast<double>(n)        //double型変換マクロ.
#define _intXY(n) {_int_r(n.x), _int_r(n.y)}    //INT_XY型変換マクロ.
#define _dblXY(n) {_dbl  (n.x), _dbl  (n.y)}    //DBL_XY型変換マクロ.
//便利マクロ.
#define _if_check(n)              assert(n); if(n)          //if文の前に同条件のassertを挟む.
#define _return(num, cond)        if (cond) { return num; } //条件に合うならreturnする.
#define _is_in_range(num, n1, n2) (n1 <= num && num <= n2)  //範囲内に数値があるかどうか.

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
		T x{}, y{};

		//constructor.
		XY(){}
		XY(T _x, T _y) : x(_x), y(_y) {}

		//演算子で計算できるように.
		XY<T> operator+(XY<T>& xy) {       //+の右側が引数に入り、返り値が左側に入る.
			return { x + xy.x, y + xy.y }; //xとyを加算して返す.
		}
		XY<T> operator-(XY<T>& xy) {
			return { x - xy.x, y - xy.y };
		}
		XY<T> operator*(XY<T>& xy) {
			return { x * xy.x, y * xy.y };
		}
		XY<T> operator/(XY<T>& xy) {
			return { x / xy.x, y / xy.y };
		}

		XY<T>& operator+=(XY<T>& xy) {
			x += xy.x;
			y += xy.y;
			return *this; //自身の実体.
		}
		XY<T> operator-=(XY<T>& xy) {
			x -= xy.x;
			y -= xy.y;
			return *this;
		}
		XY<T> operator*=(XY<T>& xy) {
			x *= xy.x;
			y *= xy.y;
			return *this;
		}
		XY<T> operator/=(XY<T>& xy) {
			x /= xy.x;
			y /= xy.y;
			return *this;
		}
		XY<T> operator*=(int n) {
			x *= n;
			y *= n;
			return *this;
		}
		XY<T> operator*=(double n) {
			x *= n;
			y *= n;
			return *this;
		}
		XY<T> operator/=(int n) {
			x /= n;
			y /= n;
			return *this;
		}
		XY<T> operator/=(double n) {
			x /= n;
			y /= n;
			return *this;
		}
	};
	using INT_XY = XY<int>;    //int型.
	using DBL_XY = XY<double>; //double型.

	//円データ.
	struct Circle
	{
		DBL_XY pos;   //座標.
		float  r;     //半径.
		UINT   color; //色.
	};
	//四角形データ.
	struct Box
	{
		DBL_XY pos;   //座標.
		DBL_XY size;  //サイズ.
		UINT   color; //色.
	};
	//三角形データ.
	struct Triangle
	{
		DBL_XY pos[3]; //3点の座標.
		UINT   color;  //色.
	};
	//線データ.
	struct Line
	{
		DBL_XY stPos; //始点座標.
		DBL_XY edPos; //終点座標.
		UINT   color; //色.
	};
}