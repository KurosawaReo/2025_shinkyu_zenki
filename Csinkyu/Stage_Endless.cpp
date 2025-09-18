/*
   - Stage_Endless.cpp -

   ステージ: 耐久モード.
*/
#include "GameManager.h"
#include "Item.h"
#include "EffectManager.h"
#include "Stage_Endless.h"

//初期化.
void EndlessStage::Init() {
	//実体取得.
	p_data      = GameData::GetPtr();
	p_effectMng = EffectManager::GetPtr();
	p_sound     = SoundMng::GetPtr();
}
//リセット.
void EndlessStage::Reset() {

}
//更新.
void EndlessStage::Update() {

	//最初のみ.
	if (p_data->counter == 0) {
		//サウンド.
		p_sound->Play(_T("LevelUp"), false, 100);
		//エフェクト.
		EffectData data{};
		data.type = Effect_Endless_Level1;
		data.pos = { WINDOW_WID/2, WINDOW_HEI/2 };
		p_effectMng->SpawnEffect(&data);
	}

	//カウンター増加.
	p_data->counter += ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
	//出現間隔.
	p_data->spawnRate = 1.0f/(1+(p_data->counter/8000)); //100%から少しずつ減少.
	//レベル管理.
	switch (p_data->level)
	{
		case 1:
			if (p_data->counter >= 1500) { //1500 = 出現間隔約??%地点.
				p_data->level = 2; //Lv2へ.

				//サウンド.
				p_sound->Play(_T("LevelUp"), false, 100);
				//エフェクト.
				EffectData data{};
				data.type = Effect_Endless_Level2;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				p_effectMng->SpawnEffect(&data);
			}
			break;
		case 2:
			if (p_data->counter >= 3500) { //3500 = 出現間隔約??%地点.
				p_data->level = 3; //Lv3へ.

				//サウンド.
				p_sound->Play(_T("LevelUp"), false, 100);
				//エフェクト.
				EffectData data{};
				data.type = Effect_Endless_Level3;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				p_effectMng->SpawnEffect(&data);
			}
			break;
		case 3:
			if (p_data->counter >= 6000) { //6000 = 出現間隔約??%地点.
				p_data->level = 4; //Lv4へ.

				GameManager::GetPtr()->ResetStrLaser();
				ItemManager::GetPtr()->AddItemCnt(); //アイテムを増やす.

				//サウンド.
				p_sound->Play(_T("LevelUp"), false, 100);
				//エフェクト.
				EffectData data{};
				data.type = Effect_Endless_Level4;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				p_effectMng->SpawnEffect(&data);
			}
			break;
		case 4:
			if (p_data->counter >= 9000) { //9000 = 出現間隔約??%地点.
				p_data->level = 5; //Lv5へ.

				GameManager::GetPtr()->ResetNorLaser();

				//サウンド.
				p_sound->Play(_T("LevelUp"), false, 100);
				//エフェクト.
				EffectData data{};
				data.type = Effect_Endless_Level5;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				p_effectMng->SpawnEffect(&data);
			}
			break;
		case 5:
			//最終レベル.
			break;

		default: assert(FALSE); break;
	}
}
//描画.
void EndlessStage::Draw() {

}