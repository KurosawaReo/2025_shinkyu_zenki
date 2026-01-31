/*
   - KR_App.h - (DxLib)
   ver.2026/01/31

   プログラムの根底(開始,終了など)の処理。
*/
#pragma once
//[include] KR_Global.
#if !defined DEF_KR_DX_GLOBAL
  #include "KR_Global.h"
#endif
//[include] hで使うもの.
#include "KR_Timer.h"

//KrLib名前空間.
namespace KR
{
	//プログラム全体処理.
	class App final
	{
	//▼ ===== 実体 ===== ▼.
	private:
		static App inst; //実体を入れる用.

	//▼ ===== 変数 ===== ▼.
	private:
		TimerMicro tmFps{};		 //fps計測用タイマー.
		bool       isQuit{};     //ゲーム終了フラグ.

		INT_XY     windowSize{}; //画面サイズ.    (記録用)
		int        fps{};        //フレームレート.(記録用)

	//▼ ===== 関数 ===== ▼.
	private:
		//コンストラクタ.
		App() {}

		void EndDx();

	public:
		//get.
		static INT_RECT  GetWindowRect() { return {0, 0, inst.windowSize.x, inst.windowSize.y}; }
		static int		 GetWindowX()    { return inst.windowSize.x; }
		static int		 GetWindowY()    { return inst.windowSize.y; }
		static int		 GetFps()        { return inst.fps; }

		static ResultInt InitDx(int windowWid, int windowHei, bool isWindowMode, int fps, bool isVSync = TRUE);
		static void		 LoopDx();

		static void		 Reset(); //全管理クラスのリセット.
		static void      Quit();  //ゲームを終了する.

		//使用禁止.
		App(const App&) = delete;
		App& operator=(const App&) = delete;
	};
}