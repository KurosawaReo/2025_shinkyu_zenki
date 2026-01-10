/*
   - Stage_Endless.cpp -

   ステージ: 耐久モード.
*/
#include "Stage_Endless.h"

//依存関係.
#include "LaserManager.h"
#include "Obst_NormalLaser.h"
#include "Obst_StraightLaser.h"
#include "Obst_MeteorManager.h"
#include "Obst_Ripples.h"
#include "Obst_Fireworks.h"
#include "Item.h"
#include "EffectManager.h"
#include "GameData.h"
#include "GameManager.h"
//参照.
static GameData&         gameData         = GameData::GetInst();
static GameManager&      gameMng      = GameManager::GetInst();
static LaserManager&     laserMng     = LaserManager::GetInst();
static MeteorManager&    meteorMng    = MeteorManager::GetInst();
static Ripples&          ripples      = Ripples::GetInst();
static ItemManager&      itemMng      = ItemManager::GetInst();
static FireworksManager& p_fireworksMng = FireworksManager::GetInst();
static EffectManager&    effectMng    = EffectManager::GetInst();

//初期化.
void EndlessStage::Init() {

}
//リセット.
void EndlessStage::Reset() {

}
//更新.
void EndlessStage::Update() {

	//最初のみ.
	if (gameData.counter == 0) {
		//サウンド.
		if (auto i = SoundMng::Get("LevelUp")) {
			i->Play(false, 100);
		}
		//エフェクト.
		EffectData data{};
		data.type = Effect_Endless_Level1;
		data.pos = { WINDOW_WID/2, WINDOW_HEI/2 };
		effectMng.SpawnEffect(&data);

		//召喚可能にする.
		meteorMng.SetIsSpawnAble(true);
		itemMng.  SetIsSpawnAble(true);
	}
	else {
#if defined _DEBUG //Releaseでは入れない.
		//タイマー加速(Debug)
		if (InputMng::IsPushKey(KeyID::L) == 1) {
			gameData.counter += 30;
		}
#endif
	}

	//カウンター増加.
	gameData.counter += gameData.speedRate;
	//出現間隔.
	gameData.spawnRate = 1.0f/(1+(gameData.counter/8000)); //100%から少しずつ減少.
	//レベル管理.
	switch (gameData.level)
	{
		case 1:
			if (gameData.counter >= 1500) { //1500 = 出現間隔約??%地点.
				gameData.level = 2; //Lv2へ.

				//サウンド.
				if (auto i = SoundMng::Get("LevelUp")) {
					i->Play(false, 100);
				}
				//エフェクト.
				EffectData data{};
				data.type = Effect_Endless_Level2;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);
			}
			break;
		case 2:
			if (gameData.counter >= 3500) { //3500 = 出現間隔約??%地点.
				gameData.level = 3; //Lv3へ.

				//サウンド.
				if (auto i = SoundMng::Get("LevelUp")) {
					i->Play(false, 100);
				}
				//エフェクト.
				EffectData data{};
				data.type = Effect_Endless_Level3;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);
			}
			break;
		case 3:
			if (gameData.counter >= 6000) { //6000 = 出現間隔約??%地点.
				gameData.level = 4; //Lv4へ.

				itemMng.AddItemCnt(); //アイテムを増やす.

				//サウンド.
				if (auto i = SoundMng::Get("LevelUp")) {
					i->Play(false, 100);
				}
				//エフェクト.
				EffectData data{};
				data.type = Effect_Endless_Level4;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);
			}
			break;
		case 4:
			if (gameData.counter >= 9000) { //9000 = 出現間隔約??%地点.
				gameData.level = 5; //Lv5へ.

				gameMng.ResetNorLaser();

				//サウンド.
				if (auto i = SoundMng::Get("LevelUp")) {
					i->Play(false, 100);
				}
				//エフェクト.
				EffectData data{};
				data.type = Effect_Endless_Level5;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);
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
	laserMng.Update();
	gameMng.laserNor1->Update();
	gameMng.laserNor2->Update();
	meteorMng.Update();
	itemMng.Update();
	//Lv2以上.
	if (gameData.level >= 2) {
		gameMng.laserStr[0]->Update();
		gameMng.laserStr[1]->Update();
	}
	//Lv3以上.
	if (gameData.level >= 3) {
		ripples.Update();
	}
	//Lv4以上.
	if (gameData.level >= 4) {
		p_fireworksMng.Update();
	}
	//Lv5以上.
	if (gameData.level >= 5) {
		gameMng.laserNor3->Update();
		gameMng.laserNor4->Update();
	}
}
//オブジェクトの描画.
void EndlessStage::DrawObjects() {

	//Lv1以上.
	laserMng.Draw();
	gameMng.laserNor1->Draw();
	gameMng.laserNor1->Draw();
	meteorMng.Draw();
	itemMng.Draw();
	//Lv2以上.
	if (gameData.level >= 2) {
		gameMng.laserStr[0]->Draw();
		gameMng.laserStr[1]->Draw();
	}
	//Lv3以上.
	if (gameData.level >= 3) {
		ripples.Draw();
	}
	//Lv4以上.
	if (gameData.level >= 4) {
		p_fireworksMng.Draw();
	}
	//Lv5以上.
	if (gameData.level >= 5) {
		gameMng.laserNor3->Draw();
		gameMng.laserNor4->Draw();
	}
}