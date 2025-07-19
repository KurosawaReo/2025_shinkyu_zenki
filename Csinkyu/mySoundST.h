/*
   - mySoundST.h - (original)
   ver.2025/07/19

   DxLib: オリジナルサウンド機能の追加.
*/
#pragma once

//サウンドクラス.
class SoundData
{
private:
	int        handle{};                       //サウンドハンドル.

	int        nowVol{};                       //現在の音量.
	int        aftVol{};                       //変化後の音量.
	LONGLONG   aftUS{};                        //変化時間(マイクロ秒)
	TimerMicro timer = TimerMicro(CountUp, 0); //タイマー計測用.
	BOOL       isFadeOut{};                    //フェードアウトかどうか.

public:
	//コンストラクタ.
	SoundData() : handle(-1), nowVol(-1), aftVol(-1) {};
	//set.
	void SetHandle(int _handle) {
		handle = _handle;
	}
	void SetIsFadeOut(BOOL _isFadeOut) {
		isFadeOut = _isFadeOut;
	}

	void Release(); //解放.
	void Update();  //更新.

	void Play(BOOL isLoop, int volume);       //再生.
	void Stop();                              //停止.
	void ChangeVolume(int volume, float sec); //音量変更設定.

	int  GetVolumeRange(int volume);          //ボリューム値を有効範囲に変換.
};

//サウンド管理クラス.
class SoundST
{
private: //実体.
	static SoundST self; //自身の実体.

private: //データ.
	map<TCHAR*, SoundData> sound;

public:
	//実体の取得.
	static SoundST* GetPtr() {
		return &self;
	}
	//デストラクタ.
	~SoundST();

	int  LoadFile(const TCHAR fileName[], const TCHAR saveName[]);
	void Play    (const TCHAR saveName[], BOOL isLoop, int volume = 100);
	void Stop    (const TCHAR saveName[]);
	void Update  ();

	void ChangeVolume(const TCHAR saveName[], int volume, float sec = 0);	       //音量を変更.
	void FadeInPlay  (const TCHAR saveName[], int volume, float sec, BOOL isLoop); //フェードイン再生.
	void FadeOutPlay (const TCHAR saveName[], float sec);						   //フェードアウトする.
};