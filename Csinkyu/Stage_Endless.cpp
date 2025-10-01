/*
   - Stage_Endless.cpp -

   ステージ: 耐久モード.
*/
#include "LaserManager.h"
#include "Obst_NormalLaser.h"
#include "Obst_StraightLaser.h"
#include "Obst_MeteorManager.h"
#include "Obst_Ripples.h"
#include "Obst_Fireworks.h"
#include "Item.h"
#include "EffectManager.h"
#include "GameManager.h"

#include "Stage_Endless.h"

//初期化.
void EndlessStage::Init() {
	//実体取得.
	p_data         = &GameData::GetInst();
	p_gameMng      = &GameManager::GetInst();
	p_laserMng     = &LaserManager::GetInst();
	p_meteorMng    = &MeteorManager::GetInst();
	p_ripples      = &Ripples::GetInst();
	p_itemMng      = &ItemManager::GetInst();
	p_fireworksMng = &FireworksManager::GetInst();
	p_effectMng    = &EffectManager::GetInst();
	p_input        = &InputMng::GetInst();
	p_sound        = &SoundMng::GetInst();
}
//リセット.
void EndlessStage::Reset() {

}
//更新.
void EndlessStage::Update() {

#if defined _DEBUG //Releaseでは入れない.
	//タイマー加速(Debug)
	if (p_input->IsPushKey(KeyID::L) == 1) {
		p_data->counter += 30;
	}
#endif

	//最初のみ.
	if (p_data->counter == 0) {
		//サウンド.
		p_sound->Play(_T("LevelUp"), false, 100);
		//エフェクト.
		EffectData data{};
		data.type = Effect_Endless_Level1;
		data.pos = { WINDOW_WID/2, WINDOW_HEI/2 };
		p_effectMng->SpawnEffect(&data);

		//召喚可能にする.
		p_meteorMng->SetIsSpawnAble(true);
		p_itemMng->  SetIsSpawnAble(true);
	}

	//カウンター増加.
	p_data->counter += p_data->speedRate;
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

				p_itemMng->AddItemCnt(); //アイテムを増やす.

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

				p_gameMng->ResetNorLaser();

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

	UpdateObjects();
}
//描画.
void EndlessStage::Draw() {
	DrawObjects();
}

//オブジェクトの更新.
void EndlessStage::UpdateObjects() {

	//Lv1以上.
	p_laserMng->Update();
	p_gameMng->laserNor1->Update();
	p_gameMng->laserNor2->Update();
	p_meteorMng->Update();
	p_itemMng->Update();
	//Lv2以上.
	if (p_data->level >= 2) {
		p_gameMng->laserStr[0]->Update();
		p_gameMng->laserStr[1]->Update();
	}
	//Lv3以上.
	if (p_data->level >= 3) {
		p_ripples->Update();
	}
	//Lv4以上.
	if (p_data->level >= 4) {
		p_fireworksMng->Update();
	}
	//Lv5以上.
	if (p_data->level >= 5) {
		p_gameMng->laserNor3->Update();
		p_gameMng->laserNor4->Update();
	}
}
//オブジェクトの描画.
void EndlessStage::DrawObjects() {

	//Lv1以上.
	p_laserMng->Draw();
	p_gameMng->laserNor1->Draw();
	p_gameMng->laserNor2->Draw();
	p_meteorMng->Draw();
	p_itemMng->Draw();
	//Lv2以上.
	if (p_data->level >= 2) {
		p_gameMng->laserStr[0]->Draw();
		p_gameMng->laserStr[1]->Draw();
	}
	//Lv3以上.
	if (p_data->level >= 3) {
		p_ripples->Draw();
	}
	//Lv4以上.
	if (p_data->level >= 4) {
		p_fireworksMng->Draw();
	}
	//Lv5以上.
	if (p_data->level >= 5) {
		p_gameMng->laserNor3->Draw();
		p_gameMng->laserNor4->Draw();
	}
}