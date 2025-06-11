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

   <stdio.h>などのc標準のライブラリはここに入れて
   他のcppファイルから、このstdafx.hを通してstdio.hなどを導入する流れ.

   参考
   https://www.isus.jp/products/c-compilers/stdafxh/
/---------------------------------------------------------------------*/
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include "DxLib.h"

#include "Global.h"
#include "myDrawST.h"
#include "myInputST.h"
#include "myCalcST.h"
#include "myTimerST.h"