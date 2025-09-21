/*
   - Item.cpp -
   Item管理.
*/
#include "Player.h"
#include "GameManager.h"
#include "LaserManager.h"
#include "EffectManager.h"

#include "Item.h"

using namespace Calc; //計算機能を使用.

//初期化.
void ItemManager::Init()
{
	p_gamedata  = GameData::GetPtr();
	p_player    = Player::GetPtr();
	p_laserMng  = LaserManager::GetPtr();
	p_effectMng = EffectManager::GetPtr();

	//画像.
	imgItem.LoadFile(_T("Resources/Images/item.png"));	
}
//リセット.
void ItemManager::Reset()
{
	//全て消滅.
	for (int i = 0; i < _countof(items); i++) {
		ItemErase(i);
	}
	//最初はアイテム1つ.
	itemMaxCnt = 1;
}
//更新.
void ItemManager::Update()
{
	for (int i = 0; i < ITEM_COUNT; i++) {

		//出現済みアイテム.
		if (items[i].active) {

			//カウンター.
			items[i].counter += p_gamedata->speedRate;
			//落下.
			items[i].pos.y += ITEM_SPEED * p_gamedata->speedRate;
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
				items[i].spawnCounter += (p_gamedata->isReflectMode) ? 0 : 1;
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
			//強化演出.
			if (items[i].type == Item_Super) {

				Circle cir = { items[i].pos, 30, COLOR_PLY_REFLECT };

				SetDrawBlendModeST(MODE_ADD, 128 + 127*CalcNumWaveLoop(items[i].counter/20)); //点滅.
				DrawCircleST(&cir, false, true);
				ResetDrawBlendMode();
			}
			//アイテム本体.
			{
				//Box box1 = { data[i].pos, {ITEM_SIZE,   ITEM_SIZE  }, COLOR_ITEM }; //{pos}, {size}, color.
				//Box box2 = { data[i].pos, {ITEM_SIZE-2, ITEM_SIZE-2}, COLOR_ITEM }; //{pos}, {size}, color.
				//DrawBoxST(&box1, ANC_MID, false);
				//DrawBoxST(&box2, ANC_MID, false);

				imgItem.DrawExtend(items[i].pos, {0.045, 0.045}, ANC_MID, true, true);

				//チュートリアル用.
				if (p_gamedata->stage == STAGE_TUTORIAL) {
					DrawStr str(_T("アイテム"), items[i].pos.Add(0, -35).ToIntXY(), COLOR_ITEM);
					str.Draw();
				}
			}
		}
	}
}

//アイテム召喚.
void ItemManager::ItemSpawn(int idx) {

	//座標の設定.
	items[idx].pos.x = (double)RandNum(ITEM_SIZE, WINDOW_WID-ITEM_SIZE); // X座標をランダムに設定
	items[idx].pos.y = -ITEM_SIZE;					        		    // 画面上部の少し上から開始
	//タイプを決める.
	if (p_gamedata->level < 5) {
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
	GameManager::GetPtr()->ItemUsed();
	//サウンド.
	SoundMng* sound = SoundMng::GetPtr();
	sound->Play(_T("ItemUse"), false, 76); //ポワーン.
}

// プレイヤーとの当たり判定
void ItemManager::CheckHitPlayer(int idx)
{
	//アイテムが無効orプレイヤーがいないなら処理しない.
	if (!items[idx].active || !p_player->GetActive()) {
		return;
	}

	//プレイヤーの判定を取得.
	Circle plyHit = p_player->GetHit();
	//当たり判定を四角形とする.
	Box itemBox = { items[idx].pos, {ITEM_SIZE, ITEM_SIZE}, {} };
	
	//当たった場合.
	if (HitBoxCir(&itemBox, &plyHit)) {

		//エフェクト召喚.
		EffectData effect{};
		effect.type = Effect_Score100;
		effect.pos = items[idx].pos;
		p_effectMng->SpawnEffect(&effect);
		//スコア加算.
		p_gamedata->score += SCORE_TAKE_ITEM;

		//プレイヤーのモード設定.
		switch (items[idx].type)
		{
			case Item_Normal:
				p_player->SetMode(Player_Reflect);
				break;
			case Item_Super:
				p_player->SetMode(Player_SuperReflect);
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