/*
   - Item.cpp -
   Item管理.
*/
#include "Item.h"
#include "Player.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>  // sqrt関数のため
#include"Global.h"
//初期化.
GameData gamedata;
void Item::Init()
{
	// ランダムシードを設定（初回のみ）
	static bool seedSet = false;
	if (!seedSet) {
		srand((unsigned int)time(NULL));
		seedSet = true;
	}

	Reset(); // リセット関数を呼び出し
}

// アイテムのリセット（再生成用）
void Item::Reset()
{
	// 座標の初期化
	itemX = (double)(rand() % 600 + 20);  // X座標をランダムに設定（20～620の範囲）
	itemY = -20.0;                        // 画面上部の少し上から開始
	Ix = (float)itemX;
	Iy = (float)itemY;

	// pos構造体の設定
	pos.x = itemX;
	pos.y = itemY;

	// サイズと色の設定
	size.x = 20;
	size.y = 20;
	clr = GetColor(0, 255, 250);

	// アイテムの状態設定
	active = TRUE;
	itemFlag = 1;                         // アクティブフラグ
	itemCounter = 0;                      // カウンター初期化
	itemW = 20;
	itemH = 20;
	// itemGraph = LoadGraph("item.png"); // 画像を使用する場合
}

//更新.
void Item::Update()
{
	if (active && itemFlag) {
		ItemMove();
		itemCounter++;

		// 画面下部を超えたら再生成
		if (itemY > 480) {
			Reset(); // 新しいアイテムとして再生成
		}
	}
	else
	{
		//アイテムが生成されてない時でもチェック.
		itemCounter++;
		if (itemCounter > ITEM_RESPAWN_TIME)//フレーム1秒に生成.
		{
			Reset();
		}
	}
}

// プレイヤーとの当たり判定
BOOL Item::CheckHitPlayer(Player* player)
{
	if (!active || !itemFlag || !player->GetActive()) {
		return FALSE;
	}

	// プレイヤーの位置と当たり判定円を取得
	Circle* playerHit = player->GetHit();

	// アイテムの矩形とプレイヤーの円の当たり判定
	double dx = itemX - playerHit->pos.x;
	double dy = itemY - playerHit->pos.y;
	double distance = sqrt(dx * dx + dy * dy);

	// アイテムのサイズを考慮した当たり判定
	double itemRadius = (itemW + itemH) / 4.0; // アイテムの半径として計算

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
	// ドットログを表示
	printfDx(_T("当たりました！ X:%.1f Y:%.1f\n"), itemX, itemY);

	

	// アイテムを削除（非アクティブにする）
	active = FALSE;
	itemFlag = 0;
	itemCounter = 0;//カウンターをリセットして再生成タイマー開始.


	// 座標を画面外に移動（念のため）
	itemX = -100;
	itemY = -100;
	Ix = (float)itemX;
	Iy = (float)itemY;
	pos.x = itemX;
	pos.y = itemY;
}

//描画.
void Item::Draw()
{
	if (active && itemFlag) {
		// 座標を更新
		pos.x = itemX;
		pos.y = itemY;
		Ix = (float)itemX;
		Iy = (float)itemY;

		// 描画（既存のコードを活用）
		Box box = { {Ix, Iy}, {itemW, itemH}, clr }; //{pos}, {size}, color.
		DrawBoxST(&box, TRUE);

		// 画像を使用する場合のコード例
		// if (itemGraph != -1) {
		//     DrawGraph((int)itemX, (int)itemY, itemGraph, TRUE);
		// }
	}
}

void Item::ItemMove()
{
	if (active && itemFlag) {
		// 基本的な落下動作
		double fallSpeed = 2.0 + (rand() % 3);  // 2.0～4.0の落下速度
		itemY += fallSpeed;

		// 左右にも少しランダムな動きを追加（オプション）
		if (itemCounter % 20 == 0) {  // 一定間隔で左右に移動
			double moveX = ((rand() % 3) - 1) * 0.5;  // -0.5, 0, 0.5のいずれか
			itemX += moveX;

			// 画面外に出ないように制限
			if (itemX < 0)   itemX = 0;
			if (itemX > 620) itemX = 620;
		}

		// 座標の同期
		pos.x = itemX;
		pos.y = itemY;
		Ix = (float)itemX;
		Iy = (float)itemY;
	}
}