/*
   - main.cpp -
   プログラムの開始地点.
*/
#include "GameManager.h"

//stdafxがあるならいらない.
#if false
  #include "myTimerST.h"
#endif

GameManager GameManager::self; //static変数の宣言.
GameManager* gm;               //実体を入れる用.

TimerMicro tmFps(COUNT_DOWN, 1000000/FPS); //fps計測用タイマー.

void Init() {
	gm = GameManager::GetPtr(); //GameManagerから実体取得.
	gm->Init();
}

void Update() {
	gm->Update();
}

void Draw() {
	gm->Draw();
}

#if false
int main() {
#else
int WINAPI WinMain(
	_In_     HINSTANCE hinstance, 
	_In_opt_ HINSTANCE hPrevinstance,
	_In_     LPSTR     lpCmdLine, 
	_In_     int       nCmdShow
){
#endif

	ChangeWindowMode(IS_WINDOW_MODE);						//TRUEでwindow, FALSEで全画面にする.
	SetWindowSize(WINDOW_WID, WINDOW_HEI);					//ウィンドウサイズの設定.
	SetGraphMode(WINDOW_WID, WINDOW_HEI, WINDOW_COLOR_BIT);	//解像度の設定.
	SetDrawScreen(DX_SCREEN_BACK);							//裏画面へ描画(ダブルバッファ)
	SetOutApplicationLogValidFlag(FALSE);                   //FALSEでLog.txtにログを書き込まない.
	SetWaitVSyncFlag(FALSE);                                //FALSEでVSyncを無効化(FPS制限なし)

	//DxLibの初期化.
	if (DxLib_Init() == -1) {
		return -1; //エラーで終了.
	}

	//初期化処理.
	Init();
	tmFps.Start();
	//メインループ.
	//ESCが押されるか、エラーが発生すれば終了.
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		//一定時間ごとに処理.
		if (tmFps.IntervalTime()) {
			ClearDrawScreen(); //画面クリア.
			Update();          //更新処理.
			Draw();			   //描画処理.
			ScreenFlip();      //表画面へ描画.
		}
	}

	DxLib_End();               //DxLibの終了処理.
	DeleteFileW(L"Log.txt");   //Log.txtが生成されるので消去する.

	return 0;
}