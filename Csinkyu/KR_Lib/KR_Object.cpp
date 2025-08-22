/*
   - KR_Object.cpp - (kurosawa original)
   ver: 2025/08/23

   DxLib用のオブジェクト機能.
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.hに入ってなければここで導入.
  #include "KR_Draw.h"
  using namespace KR_Lib;
#endif
#include "KR_Object.h"

//KR_Libに使う用.
namespace KR_Lib
{
	//オブジェクト(ObjectCir型)の描画.
	int ObjectCir::Draw(bool isDrawHit) {

		_return(0, !isActive); //非アクティブなら描画しない.

		//座標にoffsetを足す.
		Circle tmpCir = {
			cir.pos+offset, cir.r, cir.color
		};

		//円を描画(画像がない場合)
		if (img.GetImage()->handle == 0) {
			int err = DrawCircleST(&tmpCir);
		}
		//画像描画.
		else {
			int err = img.Draw(tmpCir.pos);
			_return(-1, err < 0); //-1: DrawGraphSTでエラー.
		
			//当たり判定表示.
			if (isDrawHit) {
				int err = DrawCircleST(&cir, false, true);
				_return(-2, err < 0); //-2: DrawCircleSTでエラー.
			}
		}
		return 0; //正常終了.
	}
	//オブジェクト(ObjectBox型)の描画.
	int ObjectBox::Draw(bool isDrawHit) {

		_return(0, !isActive); //非アクティブなら描画しない.

		//座標にoffsetを足す.
		Box tmpBox = {
			box.pos+offset, box.size, box.color
		};
		//画像がないなら四角を描画.
		if (img.GetImage()->handle == 0) {
			DrawBoxST(&tmpBox);
		}
		//画像描画.
		else {
			int err = img.Draw(tmpBox.pos);
			_return(-1, err < 0); //-1: DrawGraphSTでエラー.
		
			//当たり判定表示.
			if (isDrawHit) {
				int err = DrawBoxST(&box, ANC_MID, false, true);
				_return(-2, err < 0); //-2: DrawBoxSTでエラー.
			}
		}
		return 0; //正常終了.
	}
	//オブジェクト(ObjectGrid型)の描画.
	int ObjectGrid::Draw(INT_XY gridPos, INT_XY gridSize) {

		_return(0, !isActive); //非アクティブなら描画しない.

		//座標.
		INT_XY newPos = {
			gridPos.x + pos.x * gridSize.x,
			gridPos.y + pos.y * gridSize.y
		};
		//画像描画.
		int err = img.Draw(_dblXY(newPos), ANC_LU);
		return err; //-1: DrawGraphSTでエラー.
	}
}