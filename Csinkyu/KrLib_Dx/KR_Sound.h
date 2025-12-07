/*
   - KR_Sound.h - (DxLib)
   ver: 2025/12/06

   サウンド機能を追加。
*/
#pragma once
//KR_Globalが入ってなければここで導入.
#if !defined DEF_KR_DX_GLOBAL
  #include "KR_Global.h"
#endif
//[include] 定義で使ってるもの.
#include "KR_Timer.h"

//KrLib名前空間.
namespace KR
{
	//サウンドクラス.
	class Sound
	{
		friend class SoundMng;   //アクセス許可.

	//▼変数.
	private:
		int         handle{};    //サウンドハンドル.
		
		int         nowVol{};    //現在の音量.
		int         aftVol{};    //変化後の音量.
		LONGLONG    aftUS{};     //変化時間(マイクロ秒)
		TimerMicro* timer{};     //タイマー計測用.
		bool        isFadeOut{}; //フェードアウトで音を消すか.

	//▼関数.
	private:
		ResultInt LoadFile(MY_STRING fileName);	//読み込み.
		void      Release();					//解放.
		void	  Update();						//更新.
		int		  GetVolumeRange(int volume);	//ボリューム値を有効範囲に変換.
		 
	public:
		//constructor, destructor.
		//std::mapを使う関係でpublicに入れておく.
		Sound();
		~Sound();

		void	  Play        (bool isLoop, int volume = 100);      //再生.
		void      Stop        ();									//停止.
		void	  ChangeVolume(int volume, float sec = 0);			//音量変更設定.
		void	  FadeInPlay  (bool isLoop, int volume, float sec); //フェードイン再生.
		void	  FadeOutPlay (float sec);						    //フェードアウトする.

		//使用禁止(「=」で実体が複製されて、意図せずデストラクタが実行されるのを防ぐため)
		Sound& operator=(const Sound&) = delete;
	};

	//サウンド管理クラス[staticクラス]
	class SoundMng final
	{
	//▼実体関係.
	private:
		static SoundMng inst; //実体を入れる用.
	public:
		//使用禁止.
		SoundMng(const SoundMng&) = delete;
		SoundMng& operator=(const SoundMng&) = delete;
	private: 
		//constructor(新規作成をできなくする)
		SoundMng(){}
		//destructor.
		~SoundMng();

	//▼変数.
	private: 
		map<string, Sound> sounds;

	//▼関数.
	public:
		//get.
		static Sound*    Get     (string saveName);
		static bool      TryGet  (string saveName, Sound* ptr);

		static ResultInt LoadFile(MY_STRING fileName, string saveName); //読み込み.
		static void      Update  ();									//全サウンド更新.
		static void      StopAll ();									//全サウンド停止.
	};
}