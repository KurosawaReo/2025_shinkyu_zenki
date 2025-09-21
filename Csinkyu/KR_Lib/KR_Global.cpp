/*
   - KR_Global.h - (DxLib)
   ver: 2025/09/21

   KR_Lib全体で使う汎用機能を追加します。
*/
#include "KR_Global.h"

//KR_Libに使う用.
namespace KR_Lib
{
	//constructor.
	MY_COLOR::MY_COLOR(UINT _colorCode) {
		*this = _colorCode;
	}

	//代入用.
	inline void MY_COLOR::operator=(const RGBA& rgba) {
		color = rgba; //そのまま.
	}
	inline void MY_COLOR::operator=(UINT colorCode) {
		//カラーコードをRGBに分解.
		color.r =  colorCode / 0x010000;
		color.g = (colorCode / 0x000100) % 0x100;
		color.b =  colorCode % 0x100;
		color.a = 255;
	}
}