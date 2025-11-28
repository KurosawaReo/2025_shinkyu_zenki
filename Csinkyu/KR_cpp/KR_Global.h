/*
   - KR_Global.h - (C++)
   ver.2025/11/22

   KR_Lib全体で使う汎用機能を追加。
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
using namespace std;

//型変換マクロ.
#define _int(n)   static_cast<int>   (n)        //int型変換マクロ.
#define _int_r(n) static_cast<int>   (round(n)) //int型変換マクロ(四捨五入)
#define _flt(n)   static_cast<float> (n)        //float型変換マクロ.
#define _dbl(n)   static_cast<double>(n)        //double型変換マクロ.
//便利マクロ.
#define _if_check(n)        assert(n); if(n)             //if文の前に同条件のassertを挟む.
#define _return(num, condi) if (condi) { return num; }   //条件に合うならreturnする.(cond = 条件)
#define _get_name(value)    #value                       //名前を取得(変数名など)
//template用マクロ.
#define _type_num_only(T)	typename = typename enable_if<is_arithmetic<T>::value>::type //算術型(int/float/double/char)のみOKとし, そうでない場合は関数を無効にする.

//KR_Libに使う用.
namespace KR
{
	//値が範囲内かどうか.
	template<typename T, _type_num_only(T)>
	bool IsInRange(T num, T min, T max) {
		return (min <= num && num <= max);
	}
}