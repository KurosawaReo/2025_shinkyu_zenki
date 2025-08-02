/*
   - Item.cpp -
   Item管理.
*/
#include "GameManager.h"
#include "Player.h"
#include "EffectManager.h"

#include "Item.h"

//初期化.
void ItemManager::Init(GameData* _gamedata, Player* _player, EffectManager* _effectMng)
{
	p_gamedata  = _gamedata;
	p_player    = _player;
	p_effectMng = _effectMng;
}
//リセット.
void ItemManager::Reset()
{
	//全て消滅.
	for (int i = 0; i < _countof(data); i++) {
		ItemErase(i);
	}
	//最初はアイテム1つ.
	itemCnt = 1;
}
//更新.
void ItemManager::Update()
{
	for (int i = 0; i < _countof(data); i++) {

		if (data[i].active) {

			//カウンター.
			data[i].counter += ((p_gamedata->isSlow) ? SLOW_MODE_SPEED : 1);
			//落下.
			data[i].pos.y += ITEM_SPEED * (double)((p_gamedata->isSlow) ? SLOW_MODE_SPEED : 1);
			//当たり判定.
			CheckHitPlayer(i);

			//画面下部を超えたら消滅.
			if (data[i].pos.y > WINDOW_HEI + ITEM_SIZE) {
				ItemErase(i);
			}
		}
		else {
			//召喚可能なら.
			if (itemCnt >= i+1) {
				//スローモード中は加算しない.
				data[i].spawnCounter += (p_gamedata->isSlow) ? 0 : 1;
				//一定時間で再生成.
				if (data[i].spawnCounter > ITEM_RESPAWN_TIME)
				{
					data[i].spawnCounter = 0; //リセット.
					ItemSpawn(i);
				}
			}
		}
	}
}
//描画.
void ItemManager::Draw()
{
	for (int i = 0; i < _countof(data); i++) {

		//有効なアイテムを描画.
		if (data[i].active) {
			//強化演出.
			if (data[i].type == Item_Super) {

				Circle cir = { data[i].pos, 30, COLOR_PLY_REFLECT };

				SetDrawBlendModeST(MODE_ADD, 128 + 127*CalcNumWaveLoop(data[i].counter/20)); //点滅.
				DrawCircleST(&cir, FALSE, TRUE);
				ResetDrawBlendMode();
			}
			//アイテム本体.
			{
				Box box1 = { data[i].pos, {ITEM_SIZE,   ITEM_SIZE  }, COLOR_ITEM }; //{pos}, {size}, color.
				Box box2 = { data[i].pos, {ITEM_SIZE-2, ITEM_SIZE-2}, COLOR_ITEM }; //{pos}, {size}, color.
				DrawBoxST(&box1, ANC_MID, FALSE);
				DrawBoxST(&box2, ANC_MID, FALSE);
			}
		
			// 画像を使用する場合のコード例
			// if (itemGraph != -1) {
			//     DrawGraph((int)itemX, (int)itemY, itemGraph, TRUE);
			// }
		}
	}
}

//アイテム召喚.
void ItemManager::ItemSpawn(int idx) {

	//座標の設定.
	data[idx].pos.x = (double)RandNum(ITEM_SIZE, WINDOW_WID-ITEM_SIZE); // X座標をランダムに設定
	data[idx].pos.y = -ITEM_SIZE;	 								    // 画面上部の少し上から開始
	//タイプを決める.
	if (p_gamedata->level <= 4) {
		data[idx].type = Item_Normal;
	}
	else {
		data[idx].type = Item_Super; //Lv4からは強化版へ.
	}
	// アイテムの状態設定
	data[idx].active = TRUE; //アクティブフラグ
	data[idx].counter = 0;
}
//アイテム消滅.
void ItemManager::ItemErase(int idx) {
	data[idx].active = FALSE;
	data[idx].counter = 0;
	data[idx].spawnCounter = 0;
}

// プレイヤーとの当たり判定
void ItemManager::CheckHitPlayer(int idx)
{
	//アイテムが無効orプレイヤーがいないなら処理しない.
	if (!data[idx].active || !p_player->GetActive()) {
		return;
	}

	//プレイヤーの判定を取得.
	Circle* plyHit = p_player->GetHit();
	//当たり判定を四角形とする.
	Box plyBox  = { plyHit->pos,   {PLAYER_SIZE, PLAYER_SIZE}, {} };
	Box itemBox = { data[idx].pos, {ITEM_SIZE,   ITEM_SIZE},   {} };
	
	//当たった場合.
	if (HitBox(&plyBox, &itemBox)) {
		OnHitPlayer(idx);
	}
}

// プレイヤーと当たったときの処理
void ItemManager::OnHitPlayer(int idx)
{
	//アイテムを取った処理.
	GameManager::GetPtr()->TakeItem();
	//サウンド.
	SoundST* sound = SoundST::GetPtr();
	sound->Play(_T("TakeItem"),   FALSE, 76); //ポワーン.
	//エフェクト召喚.
	EffectData effect{};
	effect.type = Effect_Score100;
	effect.pos = data[idx].pos;
	p_effectMng->SpawnEffect(&effect);

	/*Circle cir = { p_player.GetPos(), 1000, {} };
	p_laserMng.LaserReflectRange(&cir);*/

	//プレイヤーのモード設定.
	switch (data[idx].type)
	{
		case Item_Normal:
			p_player->SetMode(Player_Reflect);
			break;
		case Item_Super:
			p_player->SetMode(Player_SuperReflect);
			break;

		default: assert(FALSE); break;
	}
	//アイテムを削除（非アクティブにする）
	data[idx].active = FALSE;
	data[idx].counter = 0; //カウンターをリセットして再生成タイマー開始.
	//座標を画面外に移動（念のため）
	data[idx].pos = {-100, -100};
}