#include "Player.h"

int PlayerX = 320, PlayerY = 400, PlayerGraph = -1; // 中央下に初期値を設定
int i = 0; // iにも初期値を設定

//初期化.
void InitPlayer() {

	PlayerGraph = LoadGraph(_T("image/Player.png"));
	if (PlayerGraph == -1){
		return; //エラー.
	}

	//初期位置の設定
	PlayerX = 320; // 画面中央のX座標
	PlayerY = 400; // 画面下部のY座標
}

//更新.
void UpdatePlayer() {

}

//描画.
void DrawPlayer() {
	DrawExtendGraph(270, 430, 270 + 50, 430 + 50, PlayerGraph, TRUE);
}