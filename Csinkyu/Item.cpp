/*
   - Item.cpp -
   Item管理.
*/
#include "GameManager.h"
#include "Player.h"
#include "EffectManager.h"

#include "Item.h"

//初期化.
void Item::Init(GameData* _gamedata, Player* _player, EffectManager* _effectMng)
{
	p_gamedata  = _gamedata;
	p_player    = _player;
	p_effectMng = _effectMng;
}
//リセット.
void Item::Reset()
{
	ItemSpawn();
}
//更新.
void Item::Update()
{
	//カウンタ.
	itemCounter += (float)((p_gamedata->isSlow) ? SLOW_MODE_SPEED : 1);

	if (active) {
		ItemMove();

		// 画面下部を超えたら再生成
		if (pos.y > WINDOW_HEI + size.y) {
			ItemSpawn(); // 新しいアイテムとして再生成
		}
	}
	else
	{
		//アイテムが生成されてない時でもチェック.
		if (itemCounter > ITEM_RESPAWN_TIME)//フレーム1秒に生成.
		{
			ItemSpawn();
		}
	}

	CheckHitPlayer(); //当たり判定.
}
//描画.
void Item::Draw()
{
	if (active) {

		//強化演出.
		if (type == Item_Super) {

			Circle cir = { pos, 30, COLOR_PLY_REFLECT };

			SetDrawBlendModeST(MODE_ADD, 128 + 127*CalcNumWaveLoop(itemCounter/20)); //点滅.
			DrawCircleST(&cir, FALSE, TRUE);
			ResetDrawBlendMode();
		}
		//アイテム本体.
		{
			Box box1 = { pos, {size.x,   size.y  }, COLOR_ITEM }; //{pos}, {size}, color.
			Box box2 = { pos, {size.x-2, size.y-2}, COLOR_ITEM }; //{pos}, {size}, color.
			DrawBoxST(&box1, TRUE, FALSE);
			DrawBoxST(&box2, TRUE, FALSE);
		}
		
		// 画像を使用する場合のコード例
		// if (itemGraph != -1) {
		//     DrawGraph((int)itemX, (int)itemY, itemGraph, TRUE);
		// }
	}
}

//アイテム移動.
void Item::ItemMove()
{
	//落下.
	pos.y += ITEM_SPEED * (double)((p_gamedata->isSlow) ? SLOW_MODE_SPEED : 1);
}
//アイテム召喚.
void Item::ItemSpawn() {

	//座標の設定.
	pos.x = (double)RandNum(ITEM_SIZE, WINDOW_WID-ITEM_SIZE); // X座標をランダムに設定
	pos.y = -1000;											  // 画面上部の少し上から開始
	//サイズと色の設定.
	size.x = ITEM_SIZE;
	size.y = ITEM_SIZE;
	//タイプを決める.
	if (p_gamedata->level <= 3) {
		type = Item_Normal;
	}
	else {
		type = Item_Super; //Lv4からは強化版へ.
	}

	// アイテムの状態設定
	active = TRUE;						  // アクティブフラグ
	itemCounter = 0;                      // カウンター初期化
	// itemGraph = LoadGraph("item.png"); // 画像を使用する場合
}

// プレイヤーとの当たり判定
BOOL Item::CheckHitPlayer()
{
	//アイテムが無効orプレイヤーがいないなら処理しない.
	if (!active || !p_player->GetActive()) {
		return FALSE;
	}

	//プレイヤーの判定を取得.
	Circle* plyHit = p_player->GetHit();
	//当たり判定を四角形とする.
	Box plyBox = { plyHit->pos, {PLAYER_SIZE, PLAYER_SIZE}, {} };
	Box itemBox = { pos, size, {} };
	
	//当たった場合.
	if (HitBox(&plyBox, &itemBox, TRUE)) {
		OnHitPlayer();
		return TRUE;
	}

	return FALSE;
}

// プレイヤーと当たったときの処理
void Item::OnHitPlayer()
{
	//アイテムを取った処理.
	GameManager::GetPtr()->TakeItem();
	//サウンド.
	SoundST* sound = SoundST::GetPtr();
	sound->Play(_T("TakeItem"),   FALSE, 76); //ポワーン.
	//エフェクト召喚.
	EffectData data{};
	data.type = Effect_Score100;
	data.pos = pos;
	p_effectMng->SpawnEffect(&data);

	/*Circle cir = { p_player.GetPos(), 1000, {} };
	p_laserMng.LaserReflectRange(&cir);*/

	//プレイヤーのモード設定.
	switch (type) 
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
	active = FALSE;
	itemCounter = 0;//カウンターをリセットして再生成タイマー開始.
	//座標を画面外に移動（念のため）
	pos = {-100, -100}; 
}