/*
   - Obstacle4.cpp -
   障害物管理.(小田島作)
*/
#include "DxLib.h"
#include <math.h>
#include "Player.h"
#include "Obstacle4.h"

// 外部定義があれば追加
#define PLAYER_SIZE 32
#define WINDOW_WID 640
#define WINDOW_HEI 480

void Obstacle4::Init(Player* _player)
{
	// プレイヤーの実体アドレスをもらう
	player = _player;

	// 砲台の座標セット
	Hx = 320;
	Hy = 30;

	// 砲台の移動方向セット
	Hm = 3;

	// 砲台の移動間隔カウンタセット
	Hsc = 30;

	// レーザーデータの初期化
	for (int i = 0; i < MAX_L; i++)
		Ld[i].ValidFlag = 0;

	// ラインデータの初期化
	for (int i = 0; i < LINE_MAXNUM; i++)
		Line[i].ValidFlag = 0;
}

void Obstacle4::Update()
{
	// プレイヤーが有効なときのみ更新
	if (player->GetActive()) {
		// レーザーの移動処理と砲台の動きを更新
		enemy4Move();
	}
}

void Obstacle4::Draw()
{
	// 描画ブレンドモードを加算半透明にセット
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// ラインの描画
	for (int i = 0; i < LINE_MAXNUM; i++)
	{
		// ラインデータが有効でない場合は次に移る
		if (Line[i].ValidFlag == 0) continue;

		// ラインの描画
		DrawLine(Line[i].x1, Line[i].y1,
			Line[i].x2, Line[i].y2,
			GetColor(0, 255 - Line[i].Counter * 4, 0));

		// カウンタを加算する
		Line[i].Counter++;

		// もし規定値に達していたらラインデータを無効にする
		if (Line[i].Counter == 64) Line[i].ValidFlag = 0;
	}

	// 描画ブレンドモードを通常描画モードにセット
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// 砲台の描画
	DrawBox(Hx - 8, Hy - 8, Hx + 8, Hy + 8, GetColor(255, 255, 0), TRUE);
}

// 敵の移動
void Obstacle4::enemy4Move()
{
	// レーザーの移動処理
	for (int i = 0; i < MAX_L; i++)
	{
		int xb, yb;

		// レーザーデータが無効だったらスキップ
		if (Ld[i].ValidFlag == 0) continue;

		// プレイヤーの座標を取得
		DBL_XY playerPos = player->GetPos();
		double Px = playerPos.x;
		double Py = playerPos.y;

		// プレイヤー判定用サイズ
		double halfSize = PLAYER_SIZE / 2.0;

		// 照準に当たっていたらレーザーデータを無効にする
		if ((Ld[i].x > Px - halfSize && Ld[i].x < Px + halfSize) &&
			(Ld[i].y > Py - halfSize && Ld[i].y < Py + halfSize))
		{
			Ld[i].ValidFlag = 0;
			// ここでプレイヤーへのダメージ処理を追加できます
			// プレイヤークラスにダメージメソッドがない場合はコメントアウト
			// player->SetActive(FALSE); // プレイヤーを無効化する例

			continue;
		}

		// 追尾カウンタが規定値に来ていなければ追尾処理
		double Angle = atan2(Ld[i].sy, Ld[i].sx); // 角度を計算
		if (Ld[i].Counter < 200)
		{
			double ax, ay, bx, by;

			// bx,by 自分の進んでいる方向 ax,ay 本来進むべき方向  
			bx = cos(Angle);
			by = sin(Angle);
			ax = Px - Ld[i].x;
			ay = Py - Ld[i].y;

			// 外積を利用し向きを照準側に向ける
			Angle += (ax * by - ay * bx < 0.0) ? +PI / 180 * 15 : -PI / 180 * 15;
		}

		// 追尾カウンタ加算
		Ld[i].Counter++;

		// 速度を変更する
		Ld[i].sx += (int)(cos(Angle) * 30);
		Ld[i].sy += (int)(sin(Angle) * 30);

		// 移動前のアドレスを保存
		xb = Ld[i].x;
		yb = Ld[i].y;

		// 移動する
		Ld[i].x = (Ld[i].x * 100 + Ld[i].sx) / 100;
		Ld[i].y = (Ld[i].y * 100 + Ld[i].sy) / 100;

		// 現在の状態をラインデータに変換
		{
			int j;

			// 使われていないラインデータを探す
			for (j = 0; j < LINE_MAXNUM; j++)
			{
				if (Line[j].ValidFlag == 0) break;
			}

			// もし空のデータがあった場合のみラインデータ追加
			if (j != LINE_MAXNUM)
			{
				// ライン情報をセットする

				// 座標のセット
				Line[j].x1 = xb; Line[j].y1 = yb;
				Line[j].x2 = Ld[i].x; Line[j].y2 = Ld[i].y;

				// 色決定カウンタを初期化
				Line[j].Counter = 0;

				// データを使用中にセット
				Line[j].ValidFlag = 1;
			}
		}

		// 画面外に出ていたらレーザーデータを無効にする
		if (Ld[i].x < -100 || Ld[i].x > WINDOW_WID + 100 ||
			Ld[i].y < -100 || Ld[i].y > WINDOW_HEI + 100) Ld[i].ValidFlag = 0;
	}

	// 砲台の移動処理
	{
		Hx += Hm;

		// 画面端まで来ていたら反転
		if (Hx > WINDOW_WID - 16 || Hx < 0) Hm *= -1;

		// ショットカウンタを減らす
		Hsc--;

		// カウンタが０になっていたらレーザー発射
		if (Hsc == 0)
		{
			int i;
			// 使われていないレーザーデータを探す
			for (i = 0; i < MAX_L; i++)
			{
				if (Ld[i].ValidFlag == 0) break;
			}

			// もし使われていないレーザーデータがあったらショットを出す
			if (i != MAX_L)
			{
				// レーザーの位置を設定
				Ld[i].x = Hx + 16;
				Ld[i].y = Hy + 16;

				// レーザーの速度を設定
				Ld[i].sx = 0;
				Ld[i].sy = 0;

				// カウンタをセット
				Ld[i].LogNum = 0;
				Ld[i].Counter = 0;

				// レーザーデータを使用中にセット
				Ld[i].ValidFlag = 1;
			}

			// 発射間隔カウンタ値をセット
			Hsc = 30;
		}
	}
}