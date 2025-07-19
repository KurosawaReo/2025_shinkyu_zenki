/*
   - mySoundST.cpp - (original)
   ver.2025/07/19

   DxLib: オリジナルサウンド機能の追加.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx等に入ってなければここで導入.
#endif
#include "mySoundST.h"

SoundST SoundST::self; //実体の宣言.

//サウンド解放.
void SoundData::Release() {
	//データが登録されていれば.
	if (handle >= 0) {
		DeleteSoundMem(handle); //解放.
	}
}
//サウンド再生.
void SoundData::Play(BOOL isLoop) {
	//データが登録されていれば.
	if (handle >= 0) {
		Stop();
		PlaySoundMem(handle, (isLoop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK));
	}
}
//サウンド停止.
void SoundData::Stop() {
	//データが登録されていれば.
	if (handle >= 0) {
		StopSoundMem(handle);
	}
}

//デストラクタ.
SoundST::~SoundST() {

	//サウンドデータを全て取り出す.
	for (auto& i : sound) {
		i.second.Release(); //解放を行う.
	}
	sound.clear(); //データを空にする.
}
//サウンド読み込み.
int SoundST::LoadFile(const TCHAR fileName[], const TCHAR saveName[]) {
	
	//読み込み.
	int load = LoadSoundMem(fileName);
	if (load < 0) {
		return -1; //-1: 読み込み失敗.
	}
	//ハンドルを保存.
	sound[(TCHAR*)saveName].handle = load;

	return 0; //正常終了.
}
//サウンド再生.
void SoundST::Play(const TCHAR saveName[], BOOL isLoop) {
	//存在すれば.
	if (sound.count((TCHAR*)saveName) > 0) {
		sound[(TCHAR*)saveName].Play(isLoop); //再生.
	}
}
//サウンド停止.
void SoundST::Stop(const TCHAR saveName[]) {
	//存在すれば.
	if (sound.count((TCHAR*)saveName) > 0) {
		sound[(TCHAR*)saveName].Stop(); //停止.
	}
}