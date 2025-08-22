/*
   - KR_Sound.h - (kurosawa original)
   ver: 2025/08/23

   DxLib用のサウンド機能.
*/
#pragma once

//KR_Libに使う用.
namespace KR_Lib
{
	class TimerMicro; //前方宣言.

	//サウンドクラス.
	class SoundData
	{
	private:
		int         handle{};    //サウンドハンドル.
		
		int         nowVol{};    //現在の音量.
		int         aftVol{};    //変化後の音量.
		LONGLONG    aftUS{};     //変化時間(マイクロ秒)
		TimerMicro* timer{};     //タイマー計測用.
		bool        isFadeOut{}; //フェードアウトで音を消すか.

	public:
		//constructor, destructor.
		SoundData();
		~SoundData();
		//set.
		void SetHandle(int _handle) {
			handle = _handle;
		}
		void SetIsFadeOut(bool _isFadeOut) {
			isFadeOut = _isFadeOut;
		}

		void Release(); //解放.
		void Update();  //更新.

		void Play(bool isLoop, int volume);       //再生.
		void Stop();                              //停止.
		void ChangeVolume(int volume, float sec); //音量変更設定.

		int  GetVolumeRange(int volume);          //ボリューム値を有効範囲に変換.
	};

	//サウンド管理クラス.
	class Sound
	{
	private: //実体.
		static Sound inst; //自身のインスタンス.

	private: //データ.
		map<MY_STRING, SoundData> sound;

	public:
		//実体の取得.
		static Sound* GetPtr() {
			return &inst;
		}
		//destructor.
		~Sound();

		int  LoadFile(MY_STRING fileName, MY_STRING saveName);
		void Play    (MY_STRING saveName, bool isLoop, int volume = 100);
		void Stop    (MY_STRING saveName);
		void Update  ();

		void ChangeVolume(MY_STRING saveName, int volume, float sec = 0);	       //音量を変更.
		void FadeInPlay  (MY_STRING saveName, bool isLoop, int volume, float sec); //フェードイン再生.
		void FadeOutPlay (MY_STRING saveName, float sec);						   //フェードアウトする.
	};
}