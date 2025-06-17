/*
   - Obstacle4main_od.cpp -

   レーザーの継承元クラス (小田島作)
   プレイヤーを追尾するレーザーを発射する障害物を実装
   レーザー反射機能追加
*/
#include "Player.h"    // プレイヤークラスのヘッダーファイル
#include "Obstacle4.h" // 自身のヘッダーファイル

//これが定義されてたら、こちらがON.
#if defined ODAZIMA_LASER

/**
 * @brief 障害物の更新処理
 * プレイヤーが有効な場合のみ障害物の動きを更新
 */
void Obstacle4main::Update()
{
	if (player->GetActive()) {  // プレイヤーがアクティブな場合のみ
		enemy4Move();           // 障害物の移動処理を実行
	}
}

/**
 * @brief 障害物の描画処理
 * レーザーの軌跡と砲台を描画
 */
void Obstacle4main::Draw()
{
	// 加算合成モードで軌跡を描画（発光エフェクト）
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// レーザーの軌跡の描画処理
	for (int i = 0; i < OBSTACLE4_LINE_MAX; i++)
	{
		if (line[i].ValidFlag == 0) continue;  // 無効な軌跡はスキップ

		//緑色の値, 時間経過で徐々に薄くする.
		int g = _int(255 - line[i].Counter * 4);
		g = max(g, 0); //最低値を0にする.

		// 軌跡の線を描画（時間経過で色が変化）
		Line tmpLine = { {line[i].x1, line[i].y1}, {line[i].x2, line[i].y2}, GetColor(50, g, 255) };
		DrawLineST(&tmpLine);

		// 経過時間カウンタ増加
		line[i].Counter += (data->isSlow) ? (float)SLOW_MODE_SPEED : 1;
		// 64フレーム経過したら軌跡を無効化
		if (line[i].Counter >= 64) line[i].ValidFlag = 0;
	}

	// 通常の描画モードに戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// 動く砲台を描画
	//Box box = { {Hx, Hy}, {10, 10}, GetColor(100, 100, 100) }; //{pos}, {size}, color.
	//DrawBoxST(&box, TRUE, FALSE);
}

/**
 * @brief 敵（障害物）の移動処理
 * レーザーの移動とプレイヤーへの追尾、砲台の移動とレーザー発射を管理
 */
void Obstacle4main::enemy4Move()
{
	const DBL_XY pPos = player->GetPos();        // プレイヤーの現在位置を取得
	const double pSizeHalf = PLAYER_SIZE / 2.0;  // プレイヤーの当たり判定サイズの半分

	// 反射モード中かどうかを一度だけ判定
	bool isReflectionMode = player->IsReflectionMode();

	// 各レーザーの処理
	for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
	{
		if (laser[i].ValidFlag == 0) continue;  // 無効なレーザーはスキップ

		bool isHit = false; //弾が当たったかどうか.
	
		//レーザータイプ別.
		switch (laser[i].type) 
		{
			case Laser_Normal:
				// プレイヤーとレーザーの当たり判定
				if ((laser[i].x > pPos.x - pSizeHalf && laser[i].x < pPos.x + pSizeHalf) &&
					(laser[i].y > pPos.y - pSizeHalf && laser[i].y < pPos.y + pSizeHalf))
				{
					//反射あり.
					if (player->IsReflectionMode())
					{
						ReflectLaser(i, pPos);   //レーザーを反射.
						player->UseReflection(); //クールダウン開始.
					}
					//反射なし.
					else
					{
						laser[i].ValidFlag = 0; //レーザーを無効化.
						player->PlayerDeath();  //プレイヤー死亡.
					}
					isHit = true; //当たったことを記録.
				}
				break;

			case Laser_Reflected:
				break;

			//想定外の値エラー.
			default: assert(FALSE); break;
		}

		//当たったら処理終了.
		if (isHit) {
			continue;
		}

		// レーザーの追尾処理（発射後一定時間のみ）
		if (laser[i].Counter < 200)  // 200フレーム（約3.3秒）以内のみ追尾
		{
			// 現在のプレイヤー方向への角度を計算
			double targetAngle = atan2(pPos.y - laser[i].y, pPos.x - laser[i].x);
			// レーザーの現在の移動方向の角度
			double currentAngle = atan2(laser[i].sy, laser[i].sx);
			// 角度の差分を計算
			double angleDiff = targetAngle - currentAngle;

			// 角度差分を-PI～PIの範囲に正規化
			while (angleDiff > M_PI) angleDiff -= 2 * M_PI;
			while (angleDiff < -M_PI) angleDiff += 2 * M_PI;

			// 最大旋回角度を制限（1フレームに15度まで）
			const double maxTurn = M_PI / 180 * 15;
			if (angleDiff > maxTurn) angleDiff = maxTurn;
			if (angleDiff < -maxTurn) angleDiff = -maxTurn;

			// 新しい角度を計算して速度を更新
			double newAngle = currentAngle + angleDiff;
			laser[i].sx += (int)(cos(newAngle) * 30);  // X方向速度を更新
			laser[i].sy += (int)(sin(newAngle) * 30);  // Y方向速度を更新
		}

		// レーザーの経過時間カウンタを増加
		laser[i].Counter += (data->isSlow) ? (float)SLOW_MODE_SPEED : 1;

		// 移動前の座標を保存
		DBL_XY befPos;  // 前回位置を保存する変数
		befPos = { laser[i].x, laser[i].y };

		// ミサイルの速度
		double speed = OBSTACLE4_LASER_SPEED;
		if (data->isSlow) { speed /= SLOW_MODE_SPEED; }

		// レーザーの位置を更新（速度に基づいて移動）
		laser[i].x = (laser[i].x * speed + laser[i].sx) / speed;
		laser[i].y = (laser[i].y * speed + laser[i].sy) / speed;

		// レーザーの軌跡を生成
		for (int j = 0; j < OBSTACLE4_LINE_MAX; j++)
		{
			if (line[j].ValidFlag == 0)  // 未使用の軌跡スロットを探す
			{
				// 軌跡データの設定
				line[j].x1 = befPos.x;     // 開始点X座標
				line[j].y1 = befPos.y;     // 開始点Y座標
				line[j].x2 = laser[i].x;   // 終了点X座標
				line[j].y2 = laser[i].y;   // 終了点Y座標
				line[j].Counter = 0;       // 経過時間カウンタ初期化
				line[j].ValidFlag = 1;     // 軌跡を有効化
				break;
			}
		}

		// 画面外に出たレーザーを無効化
		if (laser[i].x < -100 || laser[i].x > WINDOW_WID + 100 ||
			laser[i].y < -100 || laser[i].y > WINDOW_HEI + 100)
		{
			laser[i].ValidFlag = 0;
			laser[i].type = Laser_Normal; //ノーマルモードに戻す.
		}
	}

	// 砲台の移動とレーザー発射処理
	{
		//移動処理.
		Move();

		// 発射カウンタを減少
		Hsc -= (data->isSlow) ? (float)SLOW_MODE_SPEED : 1;
		// タイミングが来たらレーザー発射
		if (Hsc <= HscTm)
		{
			// 未使用のレーザースロットを探してレーザーを発射
			for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
			{
				if (laser[i].ValidFlag == 0)  // 未使用のレーザースロットを見つけた
				{
					// 発射位置（砲台の少し下から）
					double startX = Hx;
					double startY = Hy;

					// プレイヤー方向への初期角度計算
					double angle = atan2(pPos.y - startY, pPos.x - startX);

					// レーザーデータの初期化
					laser[i].x = startX;			// 初期X座標
					laser[i].y = startY;			// 初期Y座標
					laser[i].sx = cos(angle) * 30;  // X方向初期速度
					laser[i].sy = sin(angle) * 30;  // Y方向初期速度
					laser[i].Counter = 0;			// 経過時間カウンタ初期化
					laser[i].LogNum = 0;			// 軌跡カウンタ初期化
					laser[i].ValidFlag = 1;			// レーザーを有効化
					break;
				}
			}
			HscTm -= OBSTACLE4_SHOT_SPAN; //発射タイミングを変更.
		}
		//0秒を下回ったらもう一周.
		if (Hsc <= 0) {
			Hsc = OBSTACLE4_SHOT_RESET;  // 発射カウンタをリセット（次の発射までの待機時間）
			HscTm = OBSTACLE4_SHOT_START;
		}
	}
}

/**
 * @brief レーザー反射処理
 * プレイヤーの位置を基準にレーザーの進行方向を反転させる
 * @param laserIndex 反射するレーザーのインデックス
 * @param playerPos プレイヤーの位置
 */
void Obstacle4main::ReflectLaser(int laserIndex, DBL_XY playerPos)
{
	// レーザーからプレイヤーへのベクトルを計算
	double dx = playerPos.x - laser[laserIndex].x;
	double dy = playerPos.y - laser[laserIndex].y;

	// ベクトルの長さを計算
	double length = sqrt(dx * dx + dy * dy);

	// 正規化（長さを1にする）
	if (length > 0)
	{
		dx /= length;
		dy /= length;
	}

	// レーザーの現在の速度ベクトル
	double currentSpeedX = laser[laserIndex].sx;
	double currentSpeedY = laser[laserIndex].sy;

	// 現在の速度の大きさを計算
	double speedMagnitude = sqrt(currentSpeedX * currentSpeedX + currentSpeedY * currentSpeedY);

	// プレイヤーから外向きの方向に反射
	// 反射方向 = プレイヤーからレーザーへの方向ベクトル
	double reflectDx = -dx; // プレイヤーから離れる方向
	double reflectDy = -dy;

	// 反射後の速度を設定（元の速度の大きさを保持）
	laser[laserIndex].sx = reflectDx * speedMagnitude;
	laser[laserIndex].sy = reflectDy * speedMagnitude;

	// 反射後は追尾を無効化（カウンタを最大値に設定）
	laser[laserIndex].Counter = 200;

#if 1
	// レーザーをプレイヤーから少し離れた位置に移動（重複当たり判定を防ぐ）
	double pushDistance = PLAYER_SIZE / 2.0 + 5; // プレイヤーサイズの半分 + 余裕
	laser[laserIndex].x = playerPos.x + reflectDx * pushDistance;
	laser[laserIndex].y = playerPos.y + reflectDy * pushDistance;
#endif

	laser[laserIndex].type = Laser_Reflected; //反射モードへ.
}

#endif