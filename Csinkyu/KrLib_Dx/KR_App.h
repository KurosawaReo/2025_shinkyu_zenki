/*
   - KR_App.h - (DxLib)
   ver: 2025/11/29

   プログラム全体(開始,終了など)の処理を行う。
*/
#pragma once
//KR_Globalが入ってなければここで導入.
#if !defined DEF_KR_DXLIB_GLOBAL
  #include "KR_Global.h"
#endif
#include "KR_Timer.h"

//実体取得用.
#define InstApp KR::App::GetInst()

//KrLib名前空間.
namespace KR
{
	//プログラム全体処理[継承不可]
	class App final
	{
	//▼実体関係.
	private:
		static App inst; //実体を入れる用.
	public:
		//実体を取得.
		static App& GetInst() {
			return inst;
		}
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
		void      EndDx();

	public:
		//get.
		INT_RECT  GetWindowRect() const { return {0, 0, windowSize.x, windowSize.y}; }
		int		  GetWindowX()    const { return windowSize.x; }
		int		  GetWindowY()    const { return windowSize.y; }
		int		  GetFps()        const { return fps; }

		ResultInt InitDx(int windowWid, int windowHei, bool isWindowMode, int fps, bool isVSync = TRUE);
		void	  LoopDx();

		void	  Init  ();
		void	  Update();
		void	  Draw  ();

		void	  Quit  (); //ゲームを終了する.
	};
}