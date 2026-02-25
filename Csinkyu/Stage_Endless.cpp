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

// ▼*--=<[ StraightLaser ]>=--*▼ //

EndlessStage EndlessStage::inst;

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

		//Lv1の出現設定.
		{
			ManagerInsts::GetInst().Get<LaserManager> ()->SetAutoExeMode(MngAutoExe::Active);

#if !defined INVALID_ITEM
			ManagerInsts::GetInst().Get<ItemManager>  ()->SetAutoExeMode(MngAutoExe::Active);
			ManagerInsts::GetInst().Get<ItemManager>  ()->SetItemMaxCnt(1);    //アイテムは1つ.
#endif
#if !defined INVALID_OBST_METEOR
			ManagerInsts::GetInst().Get<MeteorManager>()->SetAutoExeMode(MngAutoExe::Active);
#endif
#if !defined INVALID_OBST_NOR_LASER
			ManagerInsts::GetInst().Get<NormalLaser>  ()->SetAutoExeMode(MngAutoExe::Active);
			ManagerInsts::GetInst().Get<NormalLaser>  ()->UseLaserPointCnt(2); //レーザーは2つ.
#endif
		}
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
	gameData.counter += gameData.speedRate * GAME_SPEED;
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

				//Lv2の出現設定.
#if !defined INVALID_OBST_STR_LASER
				ManagerInsts::GetInst().Get<StraightLaser>()->SetAutoExeMode(MngAutoExe::Active);
#endif
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

				//Lv3の出現設定.
#if !defined INVALID_OBST_RIPPLES
				ManagerInsts::GetInst().Get<Ripples>()->SetAutoExeMode(MngAutoExe::Active);
#endif
			}
			break;
		case 3:
			if (gameData.counter >= 6000) { //6000 = 出現間隔約??%地点.
				gameData.level = 4; //Lv4へ.

				ManagerInsts::GetInst().Get<ItemManager>()->SetItemMaxCnt(2); //アイテムを2つに.

				//サウンド.
				if (auto i = SoundMng::Get("LevelUp")) {
					i->Play(false, 100);
				}
				//エフェクト.
				EffectData data{};
				data.type = Effect_Endless_Level4;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);

				//Lv4の出現設定.
#if !defined INVALID_OBST_FIREWORKS
				ManagerInsts::GetInst().Get<Fireworks>()->SetAutoExeMode(MngAutoExe::Active);
#endif
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

				//Lv5の出現設定.
#if !defined INVALID_OBST_NOR_LASER
				ManagerInsts::GetInst().Get<NormalLaser>()->UseLaserPointCnt(4); //レーザーは4つ.
#endif
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