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
static GameData&      gameData  = GameData::GetInst();
static EffectManager& effectMng = EffectManager::GetInst();

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

		//Lv1から.
		ManagerBase::GetMng<LaserManager>()->SetExeState(MngExeState::Active);
		ManagerBase::GetMng<NormalLaser>()->SetExeState(MngExeState::Active);
		ManagerBase::GetMng<MeteorManager>()->SetExeState(MngExeState::Active);
		ManagerBase::GetMng<ItemManager>()->SetExeState(MngExeState::Active);

		ManagerBase::GetMng<NormalLaser>()->UseLaserPointCnt(2); //レーザーは2つ.
		ManagerBase::GetMng<ItemManager>()->SetItemMaxCnt(1);    //アイテムは1つ.
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
		case 0:
			break;
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

				//Lv2から.
				//TODO: おそらく2個同時に動く, 1つの管理クラスにまとめたい.
				ManagerBase::GetMng<StraightLaser>()->SetExeState(MngExeState::Active);
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

				//Lv3から.
				ManagerBase::GetMng<Ripples>()->SetExeState(MngExeState::Active);
			}
			break;
		case 3:
			if (gameData.counter >= 6000) { //6000 = 出現間隔約??%地点.
				gameData.level = 4; //Lv4へ.

				ManagerBase::GetMng<ItemManager>()->SetItemMaxCnt(2); //アイテムを2つに.

				//サウンド.
				if (auto i = SoundMng::Get("LevelUp")) {
					i->Play(false, 100);
				}
				//エフェクト.
				EffectData data{};
				data.type = Effect_Endless_Level4;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);

				//Lv4から.
				ManagerBase::GetMng<FireworksManager>()->SetExeState(MngExeState::Active);
			}
			break;
		case 4:
			if (gameData.counter >= 9000) { //9000 = 出現間隔約??%地点.
				gameData.level = 5; //Lv5へ.

				//サウンド.
				if (auto i = SoundMng::Get("LevelUp")) {
					i->Play(false, 100);
				}
				//エフェクト.
				EffectData data{};
				data.type = Effect_Endless_Level5;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);

				//Lv5から.
				ManagerBase::GetMng<NormalLaser>()->UseLaserPointCnt(4); //レーザーは4つ.
			}
			break;
		case 5:
			break;

		default: assert(FALSE); break;
	}
}
//描画.
void EndlessStage::Draw() {
}