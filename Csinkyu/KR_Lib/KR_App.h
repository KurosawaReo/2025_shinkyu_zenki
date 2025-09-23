/*
   - KR_App.h - (DxLib)
   ver: 2025/09/23

   プログラム全体(開始,終了など)の処理を行います。
*/
#pragma once

//KR_Libに使う用.
namespace KR_Lib
{
	class TimerMicro; //前方宣言.

	//プログラム全体処理クラス[継承不可]
	class App final
	{
	//▼実体関係.
	public:
		//実体取得用.
		static App& GetInst() {
			static App inst; //自身のインスタンス.
			return inst;
		}
		//使用禁止.
		App(const App&) = delete;
		App& operator=(const App&) = delete;
	private: 
		//constructor(新規作成をできなくする)
		App(){}

	//▼データ.
	private:
		TimerMicro tmFps{};  //fps計測用タイマー.
		
		INT_XY windowSize{}; //画面サイズ.    (記録用)
		int    fps{};        //フレームレート.(記録用)

		bool   isEnd{};      //ゲームを終了するか.

	public:
		//get.
		INT_XY GetWindowSize() const { return windowSize; }
		int    GetFps()        const { return fps; }

		int  InitDx(int windowWid, int windowHei, bool isWindowMode, int fps, bool isVSync = TRUE);
		void LoopDx();

		void Init();
		void Update();
		void Draw();

		void GameOver(); //ゲームを終了する.
	};
	//実体.
	static App& InstApp = App::GetInst();	
}