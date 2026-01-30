/*
   - KR_App.cpp - (DxLib)
   ver.2026/01/29
*/
#include "KR_App.h"

//[include] cppでのみ使うもの.
#include <algorithm>
#include "KR_ManagerBase.h"

//KrLib名前空間.
namespace KR 
{
	App App::inst; //実体生成.

	//DxLibの初期化処理.
	ResultInt App::InitDx(int windowWid, int windowHei, bool isWindowMode, int fps, bool isVSync) {

		ChangeWindowMode(isWindowMode);				//TRUEでwindow, FALSEで全画面にする.
		SetWindowSize   (windowWid, windowHei);		//ウィンドウサイズの設定.
		SetGraphMode    (windowWid, windowHei, 32); //解像度の設定.
		SetWaitVSyncFlag((isVSync) ? TRUE : FALSE);	//FALSEでVSyncを無効化(FPS制限なし)
		SetDrawScreen   (DX_SCREEN_BACK);			//裏画面へ描画(ダブルバッファ)
		SetOutApplicationLogValidFlag(FALSE);		//FALSEでLog.txtにログを書き込まない.

		//DxLibの初期化.
		if (DxLib_Init() == -1) {
			return {-1, _T("App::InitDx"), _T("初期化エラー")};
		}

		//fps計測用タイマー.
		inst.tmFps = TimerMicro(TimerMode::CountDown, 1000000/fps);
		inst.tmFps.Start();
		//値の保存.
		inst.windowSize = { windowWid, windowHei };
		inst.fps = fps;
		//変数初期化.
		inst.isQuit = false;

		//order値で並び替える.
		std::sort(
			ManagerInsts::GetInst().GetAll().begin(), ManagerInsts::GetInst().GetAll().end(), //管理クラス配列.
			[](const auto& a, const auto& b) {
				return a->GetOrder() < b->GetOrder(); //order値を比較.
			}
		);

		//Initを実行.
		for (const auto& i : ManagerInsts::GetInst().GetAll()) {
			Debug::Log(_T("order:"), i->GetOrder());
			i->Init();
		}
		//Resetを実行.
		Reset();

		return {0, _T("App::InitDx"), _T("正常終了")};
	}

	//DxLibのループ処理.
	void App::LoopDx() {

		//メインループ.
		//ESCが押されるか、終了サインがあれば終了.
		while (ProcessMessage() == 0 && !inst.isQuit) {
			//一定時間ごとに処理.
			if (inst.tmFps.IntervalTime()) {
				//画面クリア.
				ClearDrawScreen();
				//Update, Drawを実行.
				for (const auto& i : ManagerInsts::GetInst().GetAll()) {
					if (i->CanUpdate()) { i->Update(); }
					if (i->CanDraw())   { i->Draw();   } 
				}
				//表画面へ描画.
				ScreenFlip();
			}
		}

		inst.EndDx(); //終了処理.
	}

	//DxLibの終了処理.
	void App::EndDx() {
		DxLib_End();               //DxLibの終了処理.
		DeleteFile(_T("Log.txt")); //Log.txtが生成されるので消去する.
	}

	//全管理クラスのリセット.
	void App::Reset() {
		//Resetを実行.
		for (const auto& i : ManagerInsts::GetInst().GetAll()) {
			i->Reset();
		}
	}
	//ゲームを終了する.
	void App::Quit() {
		inst.isQuit = true;
	}
}