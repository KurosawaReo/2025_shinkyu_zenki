/*
   - Obstacle4main_kr.cpp -

   レーザーの継承元クラス (黒澤修正)
   プレイヤーを追尾するレーザーを発射する障害物を実装

   << 2025/06/13 >>
   反射レーザーが動かないバグの修正ver.
   参考用に残しておく
*/
#include "Player.h"    // プレイヤークラスのヘッダーファイル
#include "Obstacle4.h" // 自身のヘッダーファイル

//これが定義されてなければ、こちらがON.
#if !defined ODAZIMA_LASER

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

		// 緑色の値, 時間経過で徐々に薄くする.
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

	/*
	//レーザーの色を変えるためには↑を改造する必要あり.
	//ここは一旦保留.
	for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
	{
		//無効なレーザーはスキップ.
		if (laser[i].ValidFlag == 0)continue;

		// 反射レーザーは赤色、通常レーザーは緑色で描画
		int color = laser[i].isReflected ? GetColor(255, 100, 100) : GetColor(100, 255, 100);
	}
	*/

	//[debug] レーザーの先端に円を描く.
	for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
	{
		//反射レーザーは赤色、通常レーザーは緑色.
		int color = laser[i].isReflected ? GetColor(255, 100, 100) : GetColor(100, 255, 100);
		DrawCircle(laser[i].x, laser[i].y, 5, color);
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
		if (laser[i].ValidFlag == 0) continue;  // 無効なレーザーはスキップ

		DBL_XY befPos;  // 前回位置を保存する変数

		//通常レーザーなら.
		if (!laser[i].isReflected) {

			// プレイヤーとレーザーの当たり判定
			if ((laser[i].x > pPos.x - pSizeHalf && laser[i].x < pPos.x + pSizeHalf) &&
				(laser[i].y > pPos.y - pSizeHalf && laser[i].y < pPos.y + pSizeHalf))
			{
				//プレイヤーが反射モードなら.
				if (player->IsReflectionMode())
				{
					//反射レーザー生成.
					CreateReflectedLasers(
					  laser[i].x,
					  laser[i].y,
					  laser[i].sx,
					  laser[i].sy
					);
					//プレイヤーのクールダウンを設定.
					player->UseReflection();

					//元のレーザを無効化.
					laser[i].ValidFlag = 0;
				}
				else {

					DrawString(0, 400, _T("反射モードではありません"), 0xFFFFFF);

					laser[i].ValidFlag = 0;  //当たったらレーザーを無効化.
					player->PlayerDeath();   //プレイヤー死亡.
				}
			}
		}
		//反射レーザーなら.
		else {
			//隕石とレーザーの当たり判定.
		}

		// レーザーの追尾処理（発射後一定時間のみ、かつ反射レーザー以外）
		if (laser[i].Counter < 200 && !laser[i].isReflected)  // 200フレーム（約3.3秒）以内のみ追尾、反射レーザーは追尾しない
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
		befPos = { laser[i].x, laser[i].y };

		// ミサイルの速度
		double speed = OBSTACLE4_LASER_SPEED;
		if (data->isSlow) { speed /= SLOW_MODE_SPEED; }

		// レーザーの位置を更新（速度に基づいて移動）
		laser[i].x = (laser[i].x * speed + laser[i].sx) / speed;
		laser[i].y = (laser[i].y * speed + laser[i].sy) / speed;

		DrawCircle(laser[i].x, laser[i].y, 8, 0xFF00FF); //debug.

		// レーザーの軌跡(ライン)を生成
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
		}
	}

	// 砲台の移動とレーザー発射処理
	{
		Move(); //移動処理.
           
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
					laser[i].sx = cos(angle) * 30;	// X方向初期速度
					laser[i].sy = sin(angle) * 30;	// Y方向初期速度
					laser[i].Counter = 0;			// 経過時間カウンタ初期化
					laser[i].LogNum = 0;			// 軌跡カウンタ初期化
					laser[i].ValidFlag = 1;			// レーザーを有効化
					laser[i].isReflected = FALSE;	// 通常レーザーは反射フラグをFALSEに設定
					break;
				}
			}
			HscTm -= OBSTACLE4_SHOT_SPAN; //発射タイミングを変更.
		}
		//0秒を下回ったらもう一周.
		if (Hsc <= 0) {
			Hsc   = OBSTACLE4_SHOT_RESET;  // 発射カウンタをリセット（次の発射までの待機時間）
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
//		laser[laserIndex].x, laser[laserIndex].y, laser[laserIndex].sx, laser[laserIndex].sy), 0xFFFFFF);
//
//	CreateReflectedLasers(
//		laser[laserIndex].x,
//		laser[laserIndex].y,
//		laser[laserIndex].sx,
//		laser[laserIndex].sy
//	);
//
//	//プレイヤーのクールダウンを設定.
//	player->UseReflection();
//
//
//	//元のレーザーを無効化.
//	laser[laserIndex].ValidFlag = 0;
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
	if (baseSpeed < 20)
	{
		baseSpeed = 30;
	}

	int createdCount = 0;
	//8方向ループ.
	for (int dir = 0; dir < numReflectedLasers && createdCount < numReflectedLasers; dir++)
	{
		// 未使用のレーザースロットを探す
		bool foundSlot = false;
		for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
		{
			if (laser[i].ValidFlag == 0)
			{
				//printfDx(_T("反射レーザー生成: 方向%d\n"), dir);
				double angle = dir * angleStep;

				laser[i].x = player->GetPos().x;
				laser[i].y = player->GetPos().y;
				laser[i].sx = cos(angle) * baseSpeed;
				laser[i].sy = sin(angle) * baseSpeed;
				laser[i].Counter = 300;  // クールタイムを無効化（追尾しないように大きな値を設定）
				laser[i].LogNum = 0;
				laser[i].ValidFlag = 1;
				laser[i].isReflected = TRUE;

				createdCount++;
				foundSlot = true;
				break;  // 1つのレーザーを作成したら次の方向へ
			}
		}
		if (!foundSlot) {
			printfDx(_T("レーザースロットが見つかりません\n"));
		}
	}

	//printfDx(_T("反射レーザー生成完了: %d個作成\n"), createdCount);
}

#endif