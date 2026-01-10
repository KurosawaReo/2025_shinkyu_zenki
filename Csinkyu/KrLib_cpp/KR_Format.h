/*
   - KR_Format.h - (C++)
   ver.2025/12/30

   文字列のフォーマット機能を追加。
*/
#pragma once
//KR_Globalが入ってなければここで導入.
#if !defined DEF_KR_CPP_GLOBAL
  #include "KR_Global.h"
#endif

//KrLib名前空間.
namespace KR
{
	//フォーマット(文字列に変数を挿入する)
	MY_STRING StrFormat(MY_STRING text, ...);
}