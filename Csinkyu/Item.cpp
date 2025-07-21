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

// アイテムのリセット（再生成用）
void Item::Reset()
{
	// 座標の初期化
	pos.x = (double)RndNum(ITEM_SIZE, WINDOW_WID- ITEM_SIZE); // X座標をランダムに設定
	pos.y = -1000;											  // 画面上部の少し上から開始
	// サイズと色の設定
	size.x = ITEM_SIZE;
	size.y = ITEM_SIZE;

	// アイテムの状態設定
	active = TRUE;						  // アクティブフラグ
	itemCounter = 0;                      // カウンター初期化
	// itemGraph = LoadGraph("item.png"); // 画像を使用する場合
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
			Reset(); // 新しいアイテムとして再生成
		}
	}
	else
	{
		//アイテムが生成されてない時でもチェック.
		if (itemCounter > ITEM_RESPAWN_TIME)//フレーム1秒に生成.
		{
			Reset();
		}
	}

	CheckHitPlayer(); //当たり判定.
}

// プレイヤーとの当たり判定
BOOL Item::CheckHitPlayer()
{
	//アイテムが無効orプレイヤーがいないなら処理しない.
	if (!active || !p_player->GetActive()) {
		return FALSE;
	}

	// プレイヤーの位置と当たり判定円を取得
	Circle* playerHit = p_player->GetHit();

	// アイテムの矩形とプレイヤーの円の当たり判定
	double dx = pos.x - playerHit->pos.x;
	double dy = pos.y - playerHit->pos.y;
	double distance = sqrt(dx * dx + dy * dy);
	// アイテムのサイズを考慮した当たり判定
	double itemRadius = size.x / 2.0; // アイテムの半径として計算

	if (distance < (playerHit->r + itemRadius)) {
		// 当たった場合の処理
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
	//エフェクト召喚.
	EffectData data{};
	data.type = Effect_Score100;
	data.pos = pos;
	p_effectMng->SpawnEffect(&data);

	// アイテムを削除（非アクティブにする）
	active = FALSE;
	itemCounter = 0;//カウンターをリセットして再生成タイマー開始.
	// 座標を画面外に移動（念のため）
	pos = {-100, -100}; 
}

//描画.
void Item::Draw()
{
	if (active) {

		// 描画（既存のコードを活用）
		Box box1 = { pos, {size.x,   size.y  }, COLOR_ITEM }; //{pos}, {size}, color.
		Box box2 = { pos, {size.x-2, size.y-2}, COLOR_ITEM }; //{pos}, {size}, color.

		DrawBoxST(&box1, TRUE, FALSE);
		DrawBoxST(&box2, TRUE, FALSE);

		// 画像を使用する場合のコード例
		// if (itemGraph != -1) {
		//     DrawGraph((int)itemX, (int)itemY, itemGraph, TRUE);
		// }
	}
}

void Item::ItemMove()
{
	//落下.
	pos.y += ITEM_SPEED * (double)((p_gamedata->isSlow) ? SLOW_MODE_SPEED : 1);

#if false //よく分からん機能.
	// 左右にも少しランダムな動きを追加（オプション）
	if ((int)itemCounter % 20 == 0) {  // 一定間隔で左右に移動
		double moveX = ((rand() % 3) - 1) * 0.5;  // -0.5, 0, 0.5のいずれか
		itemX += moveX;

		// 画面外に出ないように制限
		if (itemX < 0)   itemX = 0;
		if (itemX > 620) itemX = 620;
	}
#endif
}