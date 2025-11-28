/*
   - KR_Sound.h - (DxLib)
   ver: 2025/11/29

   サウンド機能を追加。
*/
#pragma once
//KR_Globalが入ってなければここで導入.
#if !defined DEF_KR_DXLIB_GLOBAL
  #include "KR_Global.h"
#endif
#include "KR_Timer.h"

//実体取得用.
#define InstSoundMng KR::SoundMng::GetInst()

//KrLib名前空間.
namespace KR
{
	//サウンドデータ.
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

	//サウンド管理クラス[継承不可]
	class SoundMng final
	{
	//▼実体関係.
	private:
		static SoundMng inst; //実体を入れる用.
	public:
		//実体を取得.
		static SoundMng& GetInst() {
			return inst;
		}
		//使用禁止.
		SoundMng(const SoundMng&) = delete;
		SoundMng& operator=(const SoundMng&) = delete;
	private: 
		//constructor(新規作成をできなくする)
		SoundMng(){}

	//▼データ.
	private: 
		map<MY_STRING, SoundData> sound;

	public:
		//destructor.
		~SoundMng();

		int  LoadFile(MY_STRING fileName, MY_STRING saveName);
		int  Play    (MY_STRING saveName, bool isLoop, int volume = 100);
		int  Stop    (MY_STRING saveName);
		void StopAll ();
		void Update  ();

		void ChangeVolume(MY_STRING saveName, int volume, float sec = 0);	       //音量を変更.
		void FadeInPlay  (MY_STRING saveName, bool isLoop, int volume, float sec); //フェードイン再生.
		void FadeOutPlay (MY_STRING saveName, float sec);						   //フェードアウトする.
	};
}