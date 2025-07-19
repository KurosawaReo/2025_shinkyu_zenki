/*
   - mySoundST.h - (original)
   ver.2025/07/19

   DxLib: オリジナルサウンド機能の追加.
*/
#pragma once

//サウンドクラス.
class SoundData
{
	friend class SoundST; //管理クラスのみアクセス許可.

private:
	int handle;

public:
	SoundData() : handle(-1){};

	void Release();         //解放.
	void Play(BOOL isLoop); //再生.
	void Stop();            //停止.
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
	void Play    (const TCHAR saveName[], BOOL isLoop);
	void Stop    (const TCHAR saveName[]);
};