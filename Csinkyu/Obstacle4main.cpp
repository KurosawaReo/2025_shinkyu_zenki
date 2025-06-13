/*
   - Obstacle4.cpp -
   障害物管理クラス (小田島作)
   プレイヤーを追尾するレーザーを発射する障害物を実装
*/
#include "Player.h"    // プレイヤークラスのヘッダーファイル
#include "Obstacle4.h" // 自身のヘッダーファイル

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
	for (int i = 0; i < OBSTACLE4_LASER_LINE_MAX; i++)
	{
		if (line[i].ValidFlag == 0) continue;  // 無効な軌跡はスキップ

		//緑色の値, 時間経過で徐々に薄くする.
		int g = _int(255 - line[i].Counter * 4);
		g = max(g, 0); //最低値を0にする.

		// 軌跡の線を描画（時間経過で色が変化）
		Line tmpLine = { {line[i].x1, line[i].y1}, {line[i].x2, line[i].y2}, GetColor(0, g, 0) };
		DrawLineST(&tmpLine);

		// 経過時間カウンタ増加
		line[i].Counter += (data->isSlow) ? (float)SLOW_MODE_SPEED : 1;
		// 64フレーム経過したら軌跡を無効化
		if (line[i].Counter >= 64) line[i].ValidFlag = 0;
	}

	// 通常の描画モードに戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);


	// レーザー本体の描画処理を追加.
	for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
	{
		//無効なレーザーはスキップ.
		if (ld[i].ValidFlag == 0)continue;

		// 反射レーザーは赤色、通常レーザーは緑色で描画
		int color = ld[i].isReflected ? GetColor(255, 100, 100) : GetColor(100, 255, 100);

	}
}

/**
 * @brief 敵（障害物）の移動処理
 * レーザーの移動とプレイヤーへの追尾、砲台の移動とレーザー発射を管理
 */
void Obstacle4main::enemy4Move()
{
	DBL_XY pPos = player->GetPos(); // プレイヤーの現在位置を取得
	double pSizeHalf = PLAYER_SIZE / 2.0;  // プレイヤーの当たり判定サイズの半分

	// 各レーザーの処理
	for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
	{
		if (ld[i].ValidFlag == 0) continue;  // 無効なレーザーはスキップ

		DBL_XY befPos;  // 前回位置を保存する変数

		// プレイヤーとレーザーの当たり判定
		if ((ld[i].x > pPos.x - pSizeHalf && ld[i].x < pPos.x + pSizeHalf) &&
			(ld[i].y > pPos.y - pSizeHalf && ld[i].y < pPos.y + pSizeHalf))
		{
		
			if (player->IsReflectionMode())
			{
				CreateReflectedLasers(
                  ld[i].x,
			      ld[i].y,
				  ld[i].sx,
				  ld[i].sy
				);
				//プレイヤーのクールダウンを設定.
				player->UseReflection();

				//元のレーザを無効化.
				ld[i].ValidFlag = 0;
				continue;
		    }
	
			DrawString(0, 400, _T("反射処理が失敗したか、条件を満たしませんでした"), 0xFFFFFF);
			ld[i].ValidFlag = 0;  // 当たったらレーザーを無効化
			player->PlayerDeath();
			continue;
		}

		// レーザーの追尾処理（発射後一定時間のみ、かつ反射レーザー以外）
		if (ld[i].Counter < 200 && !ld[i].isReflected)  // 200フレーム（約3.3秒）以内のみ追尾、反射レーザーは追尾しない
		{
			// 現在のプレイヤー方向への角度を計算
			double targetAngle = atan2(pPos.y - ld[i].y, pPos.x - ld[i].x);
			// レーザーの現在の移動方向の角度
			double currentAngle = atan2(ld[i].sy, ld[i].sx);
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
			ld[i].sx += (int)(cos(newAngle) * 30);  // X方向速度を更新
			ld[i].sy += (int)(sin(newAngle) * 30);  // Y方向速度を更新
		}

		// レーザーの経過時間カウンタを増加
		ld[i].Counter += (data->isSlow) ? (float)SLOW_MODE_SPEED : 1;

		// 移動前の座標を保存
		befPos = { ld[i].x, ld[i].y };

		// ミサイルの速度
		double speed = OBSTACLE4_LASER_SPEED;
		if (data->isSlow) { speed /= SLOW_MODE_SPEED; }

		// レーザーの位置を更新（速度に基づいて移動）
		ld[i].x = (ld[i].x * speed + ld[i].sx) / speed;
		ld[i].y = (ld[i].y * speed + ld[i].sy) / speed;

		// レーザーの軌跡を生成
		for (int j = 0; j < OBSTACLE4_LASER_LINE_MAX; j++)
		{
			if (line[j].ValidFlag == 0)  // 未使用の軌跡スロットを探す
			{
				// 軌跡データの設定
				line[j].x1 = befPos.x;     // 開始点X座標
				line[j].y1 = befPos.y;     // 開始点Y座標
				line[j].x2 = ld[i].x;      // 終了点X座標
				line[j].y2 = ld[i].y;      // 終了点Y座標
				line[j].Counter = 0;       // 経過時間カウンタ初期化
				line[j].ValidFlag = 1;     // 軌跡を有効化
				break;
			}
		}

		// 画面外に出たレーザーを無効化
		if (ld[i].x < -100 || ld[i].x > WINDOW_WID + 100 ||
			ld[i].y < -100 || ld[i].y > WINDOW_HEI + 100)
		{
			ld[i].ValidFlag = 0;
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
				if (ld[i].ValidFlag == 0)  // 未使用のレーザースロットを見つけた
				{
					// 発射位置（砲台の少し下から）
					double startX = Hx;
					double startY = Hy;

					// プレイヤー方向への初期角度計算
					double angle = atan2(pPos.y - startY, pPos.x - startX);

					// レーザーデータの初期化
					ld[i].x = startX;			// 初期X座標
					ld[i].y = startY;			// 初期Y座標
					ld[i].sx = cos(angle) * 30; // X方向初期速度
					ld[i].sy = sin(angle) * 30; // Y方向初期速度
					ld[i].Counter = 0;			// 経過時間カウンタ初期化
					ld[i].LogNum = 0;			// 軌跡カウンタ初期化
					ld[i].ValidFlag = 1;		// レーザーを有効化
					ld[i].isReflected = FALSE;	// 通常レーザーは反射フラグをFALSEに設定
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

//BOOL Obstacle4main::HandleLaserHit(int laserIndex)
//{
//	DrawString(0, 440, _T("HandleLaserHit関数が呼ばれました。: %d\n", laserIndex), 0xFFFFFF);
//	//反射モードかチェック.
//	if (!player->IsReflectionMode())
//	{
//		DrawString(0, 430, _T("プレイヤーが反射モードではありません\n"), 0xFFFFFF);
//		return FALSE;//反射しない.
//	}
//
//	DrawString(0, 450, _T("反射処理を開始します。レーザー位置:(%.2f, %.2f) 速度:(%.2f, %.2f)\n",
//		ld[laserIndex].x, ld[laserIndex].y, ld[laserIndex].sx, ld[laserIndex].sy), 0xFFFFFF);
//
//	CreateReflectedLasers(
//		ld[laserIndex].x,
//		ld[laserIndex].y,
//		ld[laserIndex].sx,
//		ld[laserIndex].sy
//	);
//
//	//プレイヤーのクールダウンを設定.
//	player->UseReflection();
//
//
//	//元のレーザーを無効化.
//	ld[laserIndex].ValidFlag = 0;
//
//	return TRUE;//反射処理完了.
//}

void Obstacle4main::CreateReflectedLasers(double reflectX, double reflectY, int originalSx, int originalSy)
{
	//8方向に拡散するレーザーを生成.
	const int numReflectedLasers = 8;
	const double angleStep = 2 * M_PI / numReflectedLasers;

	//元のレーザーの速度を基に反射レーザーの基本速度を計算
	double baseSpeed = sqrt(originalSx * originalSx + originalSy * originalSy) * 0.8;

	int createdCount = 0;
	for (int dir = 0; dir < numReflectedLasers && createdCount < numReflectedLasers; dir++)
	{
		if (baseSpeed < 20)
		{
			baseSpeed = 30;
		}


		// 未使用のレーザースロットを探す
		bool foundSlot = false;
		for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
		{
			if (ld[i].ValidFlag == 0)
			{
				DrawCircle(ld[i].x, ld[i].y, 5, 0xFFFF00);
				printfDx(_T("反射レーザー生成: 方向%d\n"), dir);
				double angle = dir * angleStep;

				ld[i].x = player->GetPos().x;
				ld[i].y = player->GetPos().y;
				ld[i].sx = cos(angle) * baseSpeed;
				ld[i].sy = sin(angle) * baseSpeed;
				ld[i].Counter = 300;  // クールタイムを無効化（追尾しないように大きな値を設定）
				ld[i].LogNum = 0;
				ld[i].ValidFlag = 1;
				ld[i].isReflected = TRUE;

				createdCount++;
				foundSlot = true;
				break;  // 1つのレーザーを作成したら次の方向へ
			}
		}
		if (!foundSlot) {
			printfDx(_T("レーザースロットが見つかりません\n"));
		}
	}

	printfDx(_T("反射レーザー生成完了: %d個作成\n"), createdCount);
}
