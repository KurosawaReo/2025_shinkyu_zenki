/*
   - KR_Global.h - (C++)
   ver.2025/11/29

   KrLib全体で使う汎用機能を追加。
*/
#pragma once

//このヘッダが定義されているか判別する用.
#define DEF_KR_CPP_GLOBAL

//C++用.
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <cmath>    //math.hをラップしたもの.
//C言語用.
#include <tchar.h>

//名前空間なしで使えるように.
using std::list;
using std::vector;
using std::map;
using std::string;
using std::wstring;

//型変換マクロ.
#define _int(n)   static_cast<int>   (n)        //int型変換マクロ.
#define _int_r(n) static_cast<int>   (round(n)) //int型変換マクロ(四捨五入)
#define _flt(n)   static_cast<float> (n)        //float型変換マクロ.
#define _dbl(n)   static_cast<double>(n)        //double型変換マクロ.
#define _byte(n)  static_cast<BYTE>  (n)        //BYTE型変換マクロ.
//便利マクロ.
#define _if_check(n)        assert(n); if(n)             //if文の前に同条件のassertを挟む.
#define _return(num, condi) if (condi) { return num; }   //条件に合うならreturnする.(cond = 条件)
#define _get_name(value)    #value                       //名前を取得(変数名など)
//template用マクロ.
#define _type_num_only(T)	typename = typename std::enable_if_t<std::is_arithmetic<T>::value> //算術型(int/float/double/char)のみOKとし, そうでない場合は関数を無効にする.

//KrLib名前空間.
namespace KR
{
	//文字コードで切り替え.
#if defined UNICODE
	using MY_STRING = wstring;        //wchar_t型.
	#define _to_mystr std::to_wstring //to_wstring用.
#else
	using MY_STRING = string;         //char型.
	#define _to_mystr std::to_string  //to_string用.
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
		XY<int>    ToInt() const {
			return {_int_r(x), _int_r(y)};
		}
		//double型に変換.
		XY<double> ToDbl() const {
			return {_dbl(x), _dbl(y)};
		}
		//加算した結果を返す.
		XY<T> Add(T _x, T _y) const {
			return { x + _x, y + _y};
		}
		XY<T> Add(XY<T> other) const {
			return *this + other;
		}

		//演算子[+,-,*,/,%] [XY<T>・XY<T>]
		XY<T> operator+(const XY<T>& other) const {  //+の右側が引数に入り、返り値が左側に入る.
			return { x + other.x, y + other.y };     //xとyを加算して返す.
		}
		XY<T> operator-(const XY<T>& other) const {
			return { x - other.x, y - other.y };
		}
		XY<T> operator*(const XY<T>& other) const {
			return { x * other.x, y * other.y };
		}
		XY<T> operator/(const XY<T>& other) const {
			return { x / other.x, y / other.y };
		}
		XY<T> operator%(const XY<T>& other) const {
			return { x % other.x, y % other.y };
		}
		//演算子[+=,-=,*=,/=,%=] [XY<T>・XY<T>]
		XY<T>& operator+=(const XY<T>& other) {
			*this = *this + other;
			return *this; //自身の実体.
		}
		XY<T>& operator-=(const XY<T>& other) {
			*this = *this - other;
			return *this;
		}
		XY<T>& operator*=(const XY<T>& other) {
			*this = *this * other;
			return *this;
		}
		XY<T>& operator/=(const XY<T>& other) {
			*this = *this / other;
			return *this;
		}
		XY<T>& operator%=(const XY<T>& other) {
			*this = *this % other;
			return *this;
		}

		//演算子[+,-,*,/,%] [XY<T>・数値]
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
		template<typename T2, _type_num_only(T2)>
		XY<T> operator%(T2 num) const {
			return { x % static_cast<T>(num), y % static_cast<T>(num) };
		}
		//演算子[+=,-=,*=,/=,%=] [XY<T>・数値]
		//右側が数値でなければ無効にする.
		template<typename T2, _type_num_only(T2)>
		XY<T>& operator+=(T2 num) {
			*this = *this + num;
			return *this; //自身の実体.
		}
		template<typename T2, _type_num_only(T2)>
		XY<T>& operator-=(T2 num) {
			*this = *this - num;
			return *this;
		}
		template<typename T2, _type_num_only(T2)>
		XY<T>& operator*=(T2 num) {
			*this = *this * num;
			return *this;
		}
		template<typename T2, _type_num_only(T2)>
		XY<T>& operator/=(T2 num) {
			*this = *this / num;
			return *this;
		}
		template<typename T2, _type_num_only(T2)>
		XY<T>& operator%=(T2 num) {
			*this = *this % num;
			return *this;
		}
	};
	using INT_XY = XY<int>;    //int型.
	using DBL_XY = XY<double>; //double型.

	//上下左右.
	template<typename T, _type_num_only(T)>
	struct RECT
	{
		T left;
		T up;
		T right;
		T down;

		//int型に変換.
		RECT<int>    ToInt() const {
			return { _int_r(left), _int_r(up), _int_r(right), _int_r(down) };
		}
		//double型に変換.
		RECT<double> ToDbl() const {
			return { _dbl(left), _dbl(up), _dbl(right), _dbl(down) };
		}
	};
	using INT_RECT = RECT<int>;    //int型.
	using DBL_RECT = RECT<double>; //double型.

	//処理の結果(返り値用)
	class ResultInt final
	{
	private:
		int       codeNum;  //コード値.
		MY_STRING funcName; //関数名.
		MY_STRING msg;      //メッセージ.

	public:
		//constructor.
		ResultInt() {
			ResultInt(0, _T("None"), _T("No Msg"));
		}
		ResultInt(int _codeNum, MY_STRING _funcName, MY_STRING _msg) :
			codeNum(_codeNum), funcName(_funcName), msg(_msg)
		{};
		//コード値取得.
		int GetCode() const { return codeNum; }
		//結果取得.
		MY_STRING GetResult() const {
			return _T("[") + funcName + _T("] code:") + _to_mystr(codeNum) + _T(", msg:") + msg;
		}
	};

	//値が範囲内かどうか.
	template<typename T, _type_num_only(T)>
	bool IsInRange(T num, T min, T max) {
		return (min <= num && num <= max);
	}
}