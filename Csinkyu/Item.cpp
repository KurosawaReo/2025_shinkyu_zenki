/*
   - Item.cpp -
   Item管理.
*/
#include "Item.h"

//依存関係.
#include "Player.h"
#include "LaserManager.h"
#include "EffectManager.h"
#include "GameData.h"
#include "GameManager.h"
//参照.
static GameData*      gameData;
static GameManager*   gameMng;
static Player*        player;
static LaserManager*  laserMng;
static EffectManager* effectMng;
//参照(KRライブラリ)
static SoundMng*      soundMng;

using namespace Calc; //計算機能を使用.

// ▼*---=[ ItemManager ]=---*▼ //

//初期化.
void ItemManager::Init() 
{
	gameData  = ManagerInsts::Get<GameData>();
	gameMng   = ManagerInsts::Get<GameManager>();
	player    = ManagerInsts::Get<Player>();
	laserMng  = ManagerInsts::Get<LaserManager>();
	effectMng = ManagerInsts::Get<EffectManager>();
	soundMng  = ManagerInsts::Get<SoundMng>();
}
//リセット.
void ItemManager::Reset()
{
	//自動実行設定.
	SetAutoExeMode(MngAutoExe::Stop);

	itemMaxCnt = 0; //最大出現数は0にする.

	//全て消滅.
	for (int i = 0; i < _countof(items); i++) {
		ItemErase(i);
	}
}
//更新.
void ItemManager::Update()
{
	for (int i = 0; i < ITEM_COUNT; i++) {

		//出現済みアイテム.
		if (items[i].active) {

			//カウンター.
			items[i].counter += gameData->speedRate;
			//落下.
			items[i].pos.y += ITEM_SPEED * gameData->speedRate;
			//当たり判定.
			CheckHitPlayer(i);

			//画面下部を超えたら消滅.
			//チュートリアルテキスト用に余分をつける.
			if (items[i].pos.y > WINDOW_HEI + ITEM_SIZE + 50) {
				ItemErase(i);
			}
		}
		//未出現アイテム.
		else {
			//召喚可能なら.
			if (i+1 <= itemMaxCnt) {
				//反射モード中は加算しない.
				items[i].spawnCounter += (gameData->isReflectMode) ? 0 : 1;
				//一定時間で再生成.
				if (items[i].spawnCounter > ITEM_RESPAWN_TIME)
				{
					items[i].spawnCounter = 0; //リセット.
					ItemSpawn(i);
				}
			}
		}
	}

	//発動待ちなら(もし何か発動条件をつけるならここに)
	if (isItemUseWait) {
		isItemUseWait = false;
		ItemUse(); //アイテム発動.
	}
}
//描画.
void ItemManager::Draw()
{
	for (int i = 0; i < _countof(items); i++) {

		//有効なアイテムを描画.
		if (items[i].active) {

			const int pow = _int(155 + 100 * AnimWave(WaveType::CosLoop, items[i].counter / 30)); //透明度.

			//点滅描画.
			DrawMode::Exe(
				DrawModeID::None, DrawBlendModeID::Alpha, pow,
				[&]() {
					//強化演出.
					if (items[i].type == Item_Super) {
						//アイテム発光.
						DrawImgMng::Get(_T("item_light"))->DrawExtend(items[i].pos, { 0.05, 0.05 });
					}
					//アイテム本体.
					{
						DBL_XY size = {
							ITEM_SIZE / DrawImgMng::Get(_T("item"))->GetSize().ToDbl().x,
							ITEM_SIZE / DrawImgMng::Get(_T("item"))->GetSize().ToDbl().y
						};
						DrawImgMng::Get(_T("item"))->DrawExtend(items[i].pos, size, Anchor::Mid, true, true);
					}
				}
			);

			//チュートリアル用.
			if (gameData->stage == Stage_Tutorial) {
				DrawStr str(_T("アイテム"), items[i].pos.ToInt() + INT_XY(0, -35), COLOR_ITEM);
				str.Draw();
			}
		}
	}
}

//アイテム召喚.
void ItemManager::ItemSpawn(int idx) {

	//座標の設定.
	items[idx].pos.x = (double)RandNum(ITEM_SIZE, WINDOW_WID-ITEM_SIZE); // X座標をランダムに設定
	items[idx].pos.y = -ITEM_SIZE;					        	    	 // 画面上部の少し上から開始
	//タイプを決める.
	if (gameData->level < 5) {
		items[idx].type = Item_Normal;
	}
	else {
		items[idx].type = Item_Super; //Lv5からは強化版へ.
	}
	// アイテムの状態設定
	items[idx].active = true; //アクティブフラグ
	items[idx].counter = 0;
}
//アイテム消滅.
void ItemManager::ItemErase(int idx) {
	items[idx].active = false;
	items[idx].counter = 0;
	items[idx].spawnCounter = 0;
}
//アイテム発動.
void ItemManager::ItemUse()
{
	//アイテムを使用.
	gameMng->ItemUsed();
	//サウンド.
	if (auto i = soundMng->Get(_T("ItemUse"))) {
		i->Play(false, 76); //ポワーン.
	}
}

// プレイヤーとの当たり判定
void ItemManager::CheckHitPlayer(int idx)
{
	//アイテムが無効orプレイヤーがいないなら処理しない.
	if (!items[idx].active || !player->GetActive()) {
		return;
	}

	//プレイヤーの判定を取得.
	Circle plyHit = player->GetHit();
	//当たり判定を四角形とする.
	Box itemBox = { items[idx].pos, {ITEM_SIZE, ITEM_SIZE}, {}, {} };
	
	//当たった場合.
	if (HitBoxCir(itemBox, plyHit)) {

		//エフェクト召喚.
		EffectData effect{};
		effect.type = Effect_Score100;
		effect.pos = items[idx].pos;
		effectMng->SpawnEffect(&effect);
		//スコア加算.
		gameData->score += SCORE_TAKE_ITEM;

		//プレイヤーのモード設定.
		switch (items[idx].type)
		{
			case Item_Normal:
				player->SetMode(Player_Reflect);
				break;
			case Item_Super:
				player->SetMode(Player_SuperReflect);
				break;

			default: assert(FALSE); break;
		}

		//座標を画面上に移動.
		items[idx].pos = { -100, -100 };
		//全てのアイテム.
		for (int i = 0; i < ITEM_COUNT; i++) {
			items[i].active  = false; //削除(非アクティブに)
			items[i].counter = 0;     //カウンターリセット.
		}

		isItemUseWait = true; //発動待ち.
	}
}