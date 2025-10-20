/*
   - KR_App.cpp - (DxLib)
   ver: 2025/10/09

   プログラム全体(開始,終了など)の処理を行います。
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.hに入ってなければここで導入.
  #include "KR_Timer.h"
#endif
#include "KR_App.h"

//KR_Libに使う用.
namespace KR_Lib
{
	//DxLibの初期化処理.
	int App::InitDx(int windowWid, int windowHei, bool isWindowMode, int fps, bool isVSync) {

		ChangeWindowMode(isWindowMode);				//TRUEでwindow, FALSEで全画面にする.
		SetWindowSize   (windowWid, windowHei);		//ウィンドウサイズの設定.
		SetGraphMode    (windowWid, windowHei, 32); //解像度の設定.
		SetWaitVSyncFlag((isVSync) ? TRUE : FALSE);	//FALSEでVSyncを無効化(FPS制限なし)
		SetDrawScreen   (DX_SCREEN_BACK);			//裏画面へ描画(ダブルバッファ)
		SetOutApplicationLogValidFlag(FALSE);		//FALSEでLog.txtにログを書き込まない.

		//DxLibの初期化.
		if (DxLib_Init() == -1) {
			return -1; //-1: 初期化エラー.
		}

		//fps計測用タイマー.
		tmFps = TimerMicro(TimerMode::CountDown, 1000000/fps);
		tmFps.Start();
		//変数の設定.
		windowSize = { windowWid, windowHei };
		this->fps = fps;
		isQuit = false;

		Init(); //初期化処理(main.cppへ)

		return 0; //正常終了.
	}
	//DxLibのループ処理.
	void App::LoopDx() {

		//メインループ.
		//ESCが押されるか、終了サインがあれば終了.
		while (ProcessMessage() == 0 && !isQuit) {
			//一定時間ごとに処理.
			if (tmFps.IntervalTime()) {
				ClearDrawScreen(); //画面クリア.
				Update();          //更新処理(main.cppへ)
				Draw();			   //描画処理(main.cppへ)
				ScreenFlip();      //表画面へ描画.
			}
		}

		DxLib_End();               //DxLibの終了処理.
		DeleteFile(_T("Log.txt")); //Log.txtが生成されるので消去する.
	}
	//ゲームを終了する.
	void App::Quit() {
		isQuit = true;
	}
}