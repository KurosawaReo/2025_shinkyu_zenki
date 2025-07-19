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
//サウンド更新.
void SoundData::Update() {
	
	//音量が変化するなら.
	if (nowVol != aftVol) {
		//変化時間がある.
		if (aftUS > 0) {

			LONGLONG us = timer.GetPassTime(); //経過時間入手.

			//現在のボリュームを求める.
			assert(aftUS != 0);                                            //0割対策.
			int vol = (int)(nowVol - (nowVol - aftVol) * (float)us/aftUS); //now + 変化量 * 変化時間割合.

			//変化し終わったら.
			if (us >= aftUS) {
				vol    = aftVol; //目標音量に固定.
				nowVol = aftVol; //変化後の音量を設定しておく.
				aftUS  = 0;      //もう音量変化しない.
				//フェードアウトなら.
				if (isFadeOut) {
					Stop(); //停止する.
				}
			}

			//データが登録されていれば.
			if (handle >= 0) {
				assert(0 <= vol && vol <= 255);    //範囲内チェック.
				ChangeVolumeSoundMem(vol, handle); //音量反映.
			}
		}
		//変化時間がない.
		else {
			ChangeVolumeSoundMem(aftVol, handle); //音量反映.
			nowVol = aftVol;                      //変化後の音量に設定.
		}
	}
}
//サウンド再生.
void SoundData::Play(BOOL isLoop, int volume) {

	//データが登録されていれば.
	if (handle >= 0) {
		//音量変更.
		int vol255 = GetVolumeRange(volume);  //0～255に変換.
		ChangeVolumeSoundMem(vol255, handle); //音量反映.
		nowVol = aftVol = vol255;             //音量を保存.

		Stop();
		PlaySoundMem(handle, (isLoop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK));
	}
}
//サウンド停止.
void SoundData::Stop() {

	//データが登録されていれば.
	if (handle >= 0) {
		//停止.
		StopSoundMem(handle);
		//リセット.
		nowVol = -1;
		aftVol = -1;
		isFadeOut = FALSE;
	}
}
//音量変更設定.
void SoundData::ChangeVolume(int volume, float sec) {
	
	nowVol = GetVolumeSoundMem2(handle); //現在の音量.
	aftVol = GetVolumeRange(volume);     //変化後の音量.
	aftUS  = 1000000 * sec;              //変化時間.
	//変化時間があるなら.
	if (aftUS > 0) {
		timer.Start(); //タイマー開始.
	}
}
//ボリューム値を有効範囲に変換.
int SoundData::GetVolumeRange(int volume) {

	int vol255 = 255 * volume/100;        //有効範囲(0～255)に変換.
	assert(0 <= vol255 && vol255 <= 255); //範囲内チェック.
	return vol255;
}

//デストラクタ.
SoundST::~SoundST() {

	//サウンドデータを全て取り出す.
	for (auto& i : sound) {
		i.second.Release(); //各サウンドの解放.
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
	sound[(TCHAR*)saveName].SetHandle(load);

	return 0; //正常終了.
}
//サウンド再生.
void SoundST::Play(const TCHAR saveName[], BOOL isLoop, int volume) {
	//存在すれば.
	if (sound.count((TCHAR*)saveName) > 0) {
		sound[(TCHAR*)saveName].Play(isLoop, volume); //再生.
	}
}
//サウンド停止.
void SoundST::Stop(const TCHAR saveName[]) {
	//存在すれば.
	if (sound.count((TCHAR*)saveName) > 0) {
		sound[(TCHAR*)saveName].Stop(); //停止.
	}
}
//サウンド更新.
void SoundST::Update() {

	//サウンドデータを全て取り出す.
	for (auto& i : sound) {
		i.second.Update(); //各サウンドの更新.
	}
}

//音量を変更.
void SoundST::ChangeVolume(const TCHAR saveName[], int volume, float sec) {
	
	sound[(TCHAR*)saveName].ChangeVolume(volume, sec); //変更設定.
}
//フェードイン再生.
void SoundST::FadeInPlay(const TCHAR saveName[], int volume, float sec, BOOL isLoop) {

	sound[(TCHAR*)saveName].Play(isLoop, 0);           //最初は音量0で再生.
	sound[(TCHAR*)saveName].ChangeVolume(volume, sec); //徐々に大きく.
}
//フェードアウトする.
void SoundST::FadeOutPlay(const TCHAR saveName[], float sec) {

	sound[(TCHAR*)saveName].ChangeVolume(0, sec); //徐々に小さく.
	sound[(TCHAR*)saveName].SetIsFadeOut(TRUE);   //フェードアウトモードに.
}