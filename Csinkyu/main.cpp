#include "myDraw.h"
#include "GlovalConst.h"

float g_ang = 0;

void Init() {

}

void Update() {
	g_ang+=1;
}

void Draw() {
	INT_XY pos = { 100, 100 };
	DrawLineAng(pos, g_ang, 100, GetColor(0, 255, 0));
}

int WINAPI WinMain(
	_In_     HINSTANCE hinstance, 
	_In_opt_ HINSTANCE hPrevinstance,
	_In_     LPSTR     lpCmdLine, 
	_In_     int       nCmdShow
){
	ChangeWindowMode(IS_WINDOW_MODE);						//TRUEでwindow, FALSEで全画面にする.
	SetGraphMode(WINDOW_WID, WINDOW_HEI, WINDOW_COLOR_BIT);	//windowサイズとカラーbit数の指定.
	SetDrawScreen(DX_SCREEN_BACK);							//裏画面へ描画(ダブルバッファ)

	//DxLibの初期化.
	if (DxLib_Init() == -1) {
		return -1; //エラーで終了.
	}

	//初期化処理.
	Init();
	//ESCが押されるまでループ.
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();		 //画面クリア.
		Update();				 //更新処理.
		Draw();					 //描画処理.
		ScreenFlip();			 //表画面へ描画.
		WaitTimer(WAIT_LOOP_MS); //待機時間(m秒)
	}

	DxLib_End(); //DXライブラリの終了処理
	return 0;    //終了
}