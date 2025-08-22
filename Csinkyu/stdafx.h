/*---------------------------------------------------------------------/
   - stdafx.h -

   プリコンパイル済みヘッダーとして使われるもの.
   ビルド時間を短縮することが目的.
   全てのcppファイルで、最初にこのヘッダをincludeする必要がある.

   手動で入れるのが面倒なら、自動化する方法として
   プロジェクト > プロパティ > [C/C++] > [詳細設定] に
   必ず使用されるincludeファイルを設定できる所がある.
/----------------------------------------------------------------------/
   [使い方]
   ここに事前に読み込みたいヘッダを入れる.
   自作のものでも可だが、中身があまり変更されないものだけを入れる.
   (頻繁に変えるものを入れると、逆にビルドが遅くなる)

   <cstdio>などの標準ライブラリはここに入れて
   他のcppファイルから、このstdafx.hを通してライブラリを導入する流れ.

   参考
   https://www.isus.jp/products/c-compilers/stdafxh/
/---------------------------------------------------------------------*/
#pragma once

//エラー回避用.
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#include <cstdio>
#include <cstring>

#include "KR_Lib/KR_Global.h"
#include "KR_Lib/KR_Calc.h"
#include "KR_Lib/KR_Draw.h"
#include "KR_Lib/KR_File.h"
#include "KR_Lib/KR_Input.h"
#include "KR_Lib/KR_Object.h"
#include "KR_Lib/KR_Sound.h"
#include "KR_Lib/KR_Timer.h"

#include "Global.h"