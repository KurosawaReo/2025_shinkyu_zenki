/*
   - Obstacle2.cpp -
   障害物管理クラス（追尾ミサイル）の実装ファイル
   プレイヤーを追跡するミサイルの生成・動作・衝突判定を管理する
*/
#include "Player.h"    // プレイヤークラスのヘッダーをインクルード
#include "Obstacle2.h" // 障害物クラスのヘッダーをインクルード

// 初期化関数
void Obstacle2::Init(Player* _player)
{
	// 敵の画像を読み込む.
	LoadGraphST(&img, _T("image/enemy.png"));
	// img.handle;  読み込んだ画像.
	// img.size.x;  画像の幅
	// img.size.y;/ 画像の高さ

	player = _player; // プレイヤーのポインタを保存

	// すべてのミサイルの状態を初期化.
	for (int i = 0; i < MAX_M; i++)
	{
		Mv[i] = 0; // ミサイルの有効フラグをリセット.
	}

	// ミサイル発射カウントをリセット.
	hsc = 30;
}

// 更新関数
void Obstacle2::Update()
{
	enemyMove(); // 敵の移動処理を実行
}

// 描画関数
void Obstacle2::Draw()
{
	// 有効なミサイルをすべて描画.
	for (int i = 0; i < MAX_M; i++)
	{
		// ミサイルが無効（Mv[i]=0）なら、このミサイルの描画をしない.
		if (Mv[i] == 0) continue;

		double size = 0.1; // 描画サイズ仮の値
		// ミサイルを回転させて描画する位置、サイズ、角度、画像ハンドル、透過フラグ
		DrawRotaGraph(Mx[i], My[i], size, Ma[i], img.handle, TRUE);
	}
}

// 敵（ミサイル）の移動・発射・衝突判定を処理する関数.
void Obstacle2::enemyMove()
{

	// extern Player player;

	// ミサイル発射カウンタを少なくする.
	hsc--;

	// カウンタが0になったらミサイルを発射.
	if (hsc == 0)
	{
		// 使われていないミサイルデータ（Mv[i]=0）を探す.
		for (int i = 0; i < MAX_M; i++)
		{
			// 使われていないミサイルデータを見つけたら初期化
			if (Mv[i] == 0) {
				// ミサイル発射位置を設定（画面中央上部の砲台から.
				Mx[i] = 320 + 16; // 砲台のX座標.
				My[i] = 30 + 16;  // 砲台のY座標.

				// プレイヤーの中心座標を計算.
				double px = player->GetPos().x + PLAYER_SIZE / 2.0; // プレイヤーの中心X座標.
				double py = player->GetPos().y + PLAYER_SIZE / 2.0; // プレイヤーの中心Y座標.

				// プレイヤーに向かう角度を計算（atan2関数で方向を求める）
				Ma[i] = atan2(py - My[i], px - Mx[i]);

				// 以前は固定角度だったものをプレイヤー追尾に変更
				// Ma[i] = M_PI / 2;

				// 追尾カウンタを初期化
				Mc[i] = 0;

				// ミサイルを有効化
				Mv[i] = 1;

				// 一発だけ発射するためループを抜ける
				break;
			}
		}

		// 次のミサイル発射までのカウンタをリセット
		hsc = 30;
	}

	// すべてのミサイルの移動処理
	for (int i = 0; i < MAX_M; i++)
	{
		// ミサイルが無効ならスキップ
		if (Mv[i] == 0) continue;

		// プレイヤーとミサイルの衝突判定
		bool isCollison = false;

		// 衝突判定の条件チェック（矩形同士の交差判定）
		int x = Mx[i] < player->GetPos().x + PLAYER_SIZE;    // ミサイルの左端がプレイヤーの右端より左にあるか
		int x2 = Mx[i] + 16 > player->GetPos().x;           // ミサイルの右端がプレイヤーの左端より右にあるか
		int y = My[i] < player->GetPos().y + PLAYER_SIZE;    // ミサイルの上端がプレイヤーの下端より上にあるか
		int y2 = My[i] + 16 > player->GetPos().y;           // ミサイルの下端がプレイヤーの上端より下にあるか

		// すべての条件が真なら衝突している
		if (x && x2 && y && y2)
		{
			isCollison = true;
		}

		// 衝突していたらミサイルを無効化して次のミサイルへ
		if (isCollison)
		{
			Mv[i] = 0;
			continue;
		}

		// 追尾処理（発射後100フレームまで追尾する）
		if (Mc[i] < 100)
		{
			// プレイヤーの中心座標を計算
			double px = player->GetPos().x + PLAYER_SIZE / 2.0;
			double py = player->GetPos().y + PLAYER_SIZE / 2.0;

			// プレイヤーへの目標角度を計算
			//関数の説明atan2は、2つの点の間の角度を求めるための便利な関数
			//ミサイルからプレイヤーへのy座標からx座標を計算するプレイヤーがどこにいるかわかる
			double targetAngle = atan2(py - My[i], px - Mx[i]);

			// 現在の角度と目標角度の差を計算
			double angleDiff = targetAngle - Ma[i];

			// 角度差を-πからπの範囲に正規化（角度の巻き込み防止）
			while (angleDiff > M_PI) angleDiff -= 2 * M_PI;
			while (angleDiff < -M_PI) angleDiff += 2 * M_PI;

			// 一度に回転できる最大角度を制限して滑らかな追尾を実現
			double turnSpeed = (M_PI / 180.0) * 5.0; // 1フレームあたり最大5度回転

			// 角度を更新（差がほぼ0なら調整しない、差が正なら右回り、負なら左回りに調整）
			if (fabs(angleDiff) < 0.001)
			{
				// 角度差がほぼ0の場合は調整しない
				// 何もしない
			}
			else if (angleDiff > 0)
			{
				// 右回りに調整（ただし最大turnSpeed度まで）
				Ma[i] += fmin(turnSpeed, angleDiff);
			}
			else
			{
				// 左回りに調整（ただし最大turnSpeed度まで）
				Ma[i] += fmax(-turnSpeed, angleDiff);
			}
		}

		// 追尾カウンタを増加
		Mc[i]++;

		// 現在の角度に基づいてミサイルを移動させる
		double speed = 4.0; // ミサイルの速度
		Mx[i] += (int)(cos(Ma[i]) * speed); // X方向の移動
		My[i] += (int)(sin(Ma[i]) * speed); // Y方向の移動

		// 画面外に出たらミサイルを無効化
		if (Mx[i] < -100 || Mx[i] > 740 || My[i] < -100 || My[i] > 500)
		{
			Mv[i] = 0;
		}
	}
}