/*
   - KR_App.h - (DxLib)
   ver: 2025/12/05

   プログラム全体(開始,終了など)の処理を行う。
*/
#pragma once
//KR_Globalが入ってなければここで導入.
#if !defined DEF_KR_DX_GLOBAL
  #include "KR_Global.h"
#endif
#include "KR_Timer.h"

//KrLib名前空間.
namespace KR
{
	//プログラム全体処理[staticクラス]
	class App final
	{
	//▼実体関係.
	private:
		static App inst; //実体を入れる用.
	public:
		//使用禁止.
		App(const App&) = delete;
		App& operator=(const App&) = delete;
	private: 
		//constructor(新規作成できなくする)
		App(){}
		//destructor.
		~App();

	//▼変数.
	private:
		TimerMicro* tmFps{}; //fps計測用タイマー.
		
		INT_XY windowSize{}; //画面サイズ.    (記録用)
		int    fps{};        //フレームレート.(記録用)

		bool   isQuit{};     //ゲームを終了するか.

	//▼関数.
	private:
		static void      EndDx();

	public:
		//get.
		static INT_RECT  GetWindowRect() { return {0, 0, inst.windowSize.x, inst.windowSize.y}; }
		static int		 GetWindowX()    { return inst.windowSize.x; }
		static int		 GetWindowY()    { return inst.windowSize.y; }
		static int		 GetFps()        { return inst.fps; }

		static ResultInt InitDx(int windowWid, int windowHei, bool isWindowMode, int fps, bool isVSync = TRUE);
		static void		 LoopDx();

		static void	     Init  ();
		static void	     Update();
		static void	     Draw  ();

		static void      Quit  (); //ゲームを終了する.
	};
}