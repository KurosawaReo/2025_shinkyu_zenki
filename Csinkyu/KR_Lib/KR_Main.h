/*
   - KR_Main.h - (DxLib)
   ver: 2025/09/10

   プログラム開始地点の処理を行います。
*/
#pragma once

//KR_Libに使う用.
namespace KR_Lib
{
	class TimerMicro; //前方宣言.

	//DxLibの基本処理クラス.
	class DxLibMain
	{
	private: 
		TimerMicro tmFps{};  //fps計測用タイマー.
		
		INT_XY windowSize{}; //画面サイズ.    (記録用)
		int    fps{};        //フレームレート.(記録用)

		bool   isEnd{};      //ゲームを終了するか.

	public:
		//実体の取得.
		static DxLibMain* GetPtr() {
			static DxLibMain inst; //自身のインスタンス.
			return &inst;
		}
		//get.
		INT_XY GetWindowSize() const { return windowSize; }
		int    GetFps()        const { return fps; }

		int  InitDx(int windowWid, int windowHei, bool isWindowMode, int fps, bool isVSync = TRUE);
		void LoopDx();

		void Init();
		void Update();
		void Draw();

		void GameEnd(); //ゲームを終了する.
	};
}