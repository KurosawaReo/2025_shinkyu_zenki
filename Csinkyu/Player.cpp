
#include "DxLib.h"
//WinMain関数
int PlayerX = 320, PlayerY = 400, PlayerGraph = -1; // 中央下に初期値を設定
int i = 0; // iにも初期値を設定
void Player();
int main()
{
	ChangeWindowMode(TRUE);
	//画面モード設定.
	SetGraphMode(640, 480, 16);

	//DXライブラリを初期化.
	if (DxLib_Init() == -1)return -1;
	//グラフィックの画面先を裏画面にセット.
	SetDrawScreen(DX_SCREEN_BACK);
	PlayerGraph = LoadGraph(_T("Player.png"));
	if (PlayerGraph == -1)
	{
		return -1;
	}
	//初期位置の設定
	PlayerX = 320; // 画面中央のX座標
	PlayerY = 400; // 画面下部のY座標
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//画面クリア.
		ClearDrawScreen();
		//プレイヤーの描画.
		Player();
		//裏画面の内容を表画面に反映.
		ScreenFlip();
	}
	//DXライブラリの終了処理
	DxLib_End();
	return 0;
}
void Player()
{
   DrawExtendGraph(270, 430, 270 + 50, 430 + 50, PlayerGraph, TRUE);

   // 裏画面の内容を表画面にコピーする
   ScreenFlip();
}
