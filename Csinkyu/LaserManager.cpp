/*
   - LaserManager.cpp -
   元々Obstacle4mainとしてまとめられてたレーザー.
*/
#include "Player.h"
#include "MeteoManager.h"

#include "LaserManager.h"

//初期化.
void LaserManager::Init(GameData* _data, Player* _player, MeteoManager* _meteoMng) {
	
	//実体取得.
	p_data     = _data;
	p_player   = _player;
	p_meteoMng = _meteoMng;
}
//リセット.
void LaserManager::Reset() {

	//レーザーデータの初期化.
	for (int i = 0; i < OBSTACLE4_LASER_LIM; i++) {
		laser[i].ValidFlag = 0; //すべてのレーザーを無効状態に.
	}
	//レーザーの軌跡データの初期化.
	for (int i = 0; i < OBSTACLE4_LINE_MAX; i++) {
		line[i].ValidFlag = 0;  //すべての軌跡を無効状態に.
	}
}
//更新.
void LaserManager::Update() {

	plyPos = p_player->GetPos(); //プレイヤーの現在位置を取得.

	UpdateLaser();     //各レーザーの更新.
	UpdateLaserLine(); //各レーザー描画線の更新.
}
//描画.
void LaserManager::Draw() {

#if defined DEBUG_LASER_ACTIVE
	//デバッグ表示.
	for (int i = 0; i < OBSTACLE4_LINE_MAX; i++)
	{
		int x =   0 +  8 * (i%200);
		int y = 100 + 16 * (i/200);
		DrawString(0, 80, _T("レーザー痕跡のactive"), 0xFF00FF);
		DrawFormatString(x, y, 0xFF00FF, _T("%d"), line[i].ValidFlag);
	}
#endif

	// レーザーの軌跡の描画処理.
	for (int i = 0; i < OBSTACLE4_LINE_MAX; i++)
	{
		if (line[i].ValidFlag == 0) continue;  // 無効な軌跡はスキップ

		//時間経過で徐々に薄くする.
		int clr = _int(255 - line[i].Counter * 4);
		clr = max(clr, 0); //最低値を0にする.

		//加算合成モードで軌跡を描画（発光エフェクト）
		SetDrawBlendMode(DX_BLENDMODE_ADD, clr);

		//軌跡の線設定.
		Line tmpLine = { {line[i].x1, line[i].y1}, {line[i].x2, line[i].y2}, {} };
		//線の色(時間経過で色が変化)
		switch (line[i].type)
		{
			case Laser_Normal:    tmpLine.clr = GetColor(50, clr, 255); break;
			case Laser_Reflected: tmpLine.clr = GetColor(clr, 0, clr);  break;

			default: assert(FALSE); break;
		}
		DrawLineST(&tmpLine); //描画.
	}

	//通常の描画モードに戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

//各レーザーの更新.
void LaserManager::UpdateLaser() {

	const double pSizeHalf = PLAYER_SIZE / 2.0;  // プレイヤーの当たり判定サイズの半分

	// 反射モード中かどうかを一度だけ判定
	bool isReflectionMode = p_player->IsReflectionMode();

	//各レーザーの更新.
	for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
	{
		if (laser[i].ValidFlag == 0) continue;  // 無効なレーザーはスキップ

		bool isHit = false; //弾が当たったかどうか.

		//レーザータイプ別.
		switch (laser[i].type)
		{
			case Laser_Normal:
				// プレイヤーとレーザーの当たり判定
				if ((laser[i].x > plyPos.x - pSizeHalf && laser[i].x < plyPos.x + pSizeHalf) &&
					(laser[i].y > plyPos.y - pSizeHalf && laser[i].y < plyPos.y + pSizeHalf))
				{
					//反射あり.
					if (p_player->IsReflectionMode())
					{
						ReflectLaser(i);           //レーザーを反射.
						p_player->UseReflection(); //クールダウン開始.			
					}
					//反射なし.
					else
					{
						DeleteLaser(i);
						p_player->PlayerDeath(); //プレイヤー死亡.
					}
					isHit = true; //当たったことを記録.

					//レーザーの追尾処理.
					LaserNorTracking(i);
				}
				break;

			case Laser_Reflected:
			{
				Circle hit = { {laser[i].x, laser[i].y}, 10, {} }; //当たり判定円(仮)

				//隕石と当たっているなら.
				if (p_meteoMng->IsHitMeteos(&hit, TRUE)) {
					DeleteLaser(i);
					isHit = true;
					break;
				}
				//レーザーの追尾処理.
				LaserRefTracking(i);
			}
			break;

			//想定外の値エラー.
			default: assert(FALSE); break;
		}

		//当たったら処理終了.
		if (isHit) {
			continue;
		}

		// レーザーの経過時間カウンタを増加
		laser[i].Counter += (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);

		// 移動前の座標を保存
		DBL_XY befPos;  // 前回位置を保存する変数
		befPos = { laser[i].x, laser[i].y };

		// ミサイルの速度(時間経過で速くなる)
		double speed = OBSTACLE4_LASER_SPEED / (laser[i].Counter * 0.01);
		if (p_data->isSlow) { speed /= SLOW_MODE_SPEED; }

		// レーザーの位置を更新（速度に基づいて移動）
		laser[i].x = (laser[i].x * speed + laser[i].sx) / speed;
		laser[i].y = (laser[i].y * speed + laser[i].sy) / speed;

		// レーザーの軌跡を生成
		for (int j = 0; j < OBSTACLE4_LINE_MAX; j++)
		{
			if (line[j].ValidFlag == 0)  // 未使用の軌跡スロットを探す
			{
				// 軌跡データの設定
				line[j].x1 = befPos.x;		  // 開始点X座標
				line[j].y1 = befPos.y;		  // 開始点Y座標
				line[j].x2 = laser[i].x;	  // 終了点X座標
				line[j].y2 = laser[i].y;	  // 終了点Y座標
				line[j].Counter = 0;		  // 経過時間カウンタ初期化
				line[j].ValidFlag = 1;		  // 軌跡を有効化
				line[j].type = laser[i].type; //レーザーのタイプに合わせる.
				break;
			}
		}

		// 画面外に出たレーザーを無効化
		if (laser[i].x < -100 || laser[i].x > WINDOW_WID + 100 ||
			laser[i].y < -100 || laser[i].y > WINDOW_HEI + 100)
		{
			DeleteLaser(i);
		}
	}
}
//各レーザー描画線の更新.
void LaserManager::UpdateLaserLine() {

	for (int i = 0; i < OBSTACLE4_LINE_MAX; i++) {

		// 経過時間カウンタ増加
		line[i].Counter += (p_data->isSlow) ? SLOW_MODE_SPEED : 1;
		// 64フレーム経過したら軌跡を無効化
		if (line[i].Counter >= 64) line[i].ValidFlag = 0;
	}
}

//レーザー召喚.
BOOL LaserManager::SpawnLaser(float x, float y) {

	// 未使用のレーザースロットを探してレーザーを発射
	for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
	{
		if (laser[i].ValidFlag == 0)  // 未使用のレーザースロットを見つけた
		{
			// 発射位置（砲台の少し下から）
			double startX = x;
			double startY = y;
			// プレイヤー方向への初期角度計算
			double angle = atan2(plyPos.y - startY, plyPos.x - startX);

			// レーザーデータの初期化
			laser[i].x = startX;			// 初期X座標
			laser[i].y = startY;			// 初期Y座標
			laser[i].sx = cos(angle) * 30;  // X方向初期速度
			laser[i].sy = sin(angle) * 30;  // Y方向初期速度
			laser[i].Counter = 0;			// 経過時間カウンタ初期化
			laser[i].LogNum = 0;			// 軌跡カウンタ初期化
			laser[i].ValidFlag = 1;			// レーザーを有効化

			return TRUE; //召喚成功.
		}
	}
	return FALSE; //召喚失敗.
}
//レーザー消去.
void LaserManager::DeleteLaser(int idx) {

	laser[idx].ValidFlag = 0;       //無効にする.
	laser[idx].type = Laser_Normal; //ノーマルモードに戻す.
}
//レーザー反射.
void LaserManager::ReflectLaser(int idx)
{
	// レーザーからプレイヤーへのベクトルを計算
	double dx = plyPos.x - laser[idx].x;
	double dy = plyPos.y - laser[idx].y;

	// ベクトルの長さを計算
	double length = sqrt(dx * dx + dy * dy);

	// 正規化（長さを1にする）
	if (length > 0)
	{
		dx /= length;
		dy /= length;
	}

	// レーザーの現在速度(x, y)
	double nowSpeedX = laser[idx].sx;
	double nowSpeedY = laser[idx].sy;
	// 速度ベクトルを計算.
	double speedVector = sqrt(pow(nowSpeedX, 2) + pow(nowSpeedY, 2)); //vector = √(x*x + y*y)

	// 反射後の速度を設定（元の速度の大きさを保持）
	// ※プレイヤーから外向きの方向に反射.
	// ※反射方向 = プレイヤーからレーザーへの方向ベクトル.
	laser[idx].sx = -dx * speedVector;
	laser[idx].sy = -dy * speedVector;

	// レーザーをプレイヤーから少し離れた位置に移動（重複当たり判定を防ぐ）
	double pushDistance = PLAYER_SIZE / 2.0 + 5; // プレイヤーサイズの半分 + 余裕
	laser[idx].x = plyPos.x + -dx * pushDistance;
	laser[idx].y = plyPos.y + -dy * pushDistance;

	laser[idx].type    = Laser_Reflected; //反射モードへ.
	laser[idx].Counter = 0;               //カウンターをリセット.

	//目標地点を決める.
	{
		assert(p_meteoMng != nullptr); //ポインタが空でないことを確認.

		DBL_XY laserPos = { laser[idx].x, laser[idx].y }; //レーザーの現在位置.
		DBL_XY nearestMeteoPos{};

		//最も近い隕石の位置を取得する.
		bool hasMeteo = p_meteoMng->GetMeteoPosNearest(laserPos, &nearestMeteoPos);
		//隕石があった場合.
		if (hasMeteo) {
			laser[idx].meteoPos = nearestMeteoPos; //登録.
		}
		//隕石がなかった場合.
		else {
			//ランダムで適当に.
			laser[idx].meteoPos.x = RndNum(WINDOW_WID / 2 - METEO_GOAL_RAND_RANGE, WINDOW_WID / 2 + METEO_GOAL_RAND_RANGE);
			laser[idx].meteoPos.y = RndNum(WINDOW_HEI / 2 - METEO_GOAL_RAND_RANGE, WINDOW_HEI / 2 + METEO_GOAL_RAND_RANGE);
		}
	}
}

//レーザー(normal)の隕石追尾.
void LaserManager::LaserNorTracking(int idx) 
{
	//一定時間のみ追尾.
	if (laser[idx].Counter < 200)  // 200フレーム（約3.3秒）以内のみ追尾
	{
		// 現在のプレイヤー方向への角度を計算
		double targetAngle = atan2(plyPos.y - laser[idx].y, plyPos.x - laser[idx].x);
		// レーザーの現在の移動方向の角度
		double currentAngle = atan2(laser[idx].sy, laser[idx].sx);
		// 角度の差分を計算
		double angleDiff = targetAngle - currentAngle;

		// 角度差分を-PI～PIの範囲に正規化
		while (angleDiff > +M_PI) angleDiff -= 2 * M_PI;
		while (angleDiff < -M_PI) angleDiff += 2 * M_PI;

		// 最大旋回角度を制限（1フレームにn度まで）
		const double maxTurn = M_PI / 180 * OBSTACLE4_LASER_NOR_ROT_MAX;
		if (angleDiff > +maxTurn) angleDiff = +maxTurn;
		if (angleDiff < -maxTurn) angleDiff = -maxTurn;

		// 新しい角度を計算して速度を更新
		double newAngle = currentAngle + angleDiff;
		laser[idx].sx += (int)(cos(newAngle) * 30);  // X方向速度を更新
		laser[idx].sy += (int)(sin(newAngle) * 30);  // Y方向速度を更新
	}
}
//レーザー(reflected)の隕石追尾.
void LaserManager::LaserRefTracking(int idx)
{
	//一定時間のみ追尾.
	if (laser[idx].Counter < OBSTACLE4_LASER_REF_TRACK_TIME)
	{
		//隕石が存在する場合は隕石に向かって追尾だぜ.
		//隕石方向への角度を計算(いやむずいて).
		double dx = laser[idx].meteoPos.x - laser[idx].x;
		double dy = laser[idx].meteoPos.y - laser[idx].y;
		double targetAngle = atan2(
			laser[idx].meteoPos.y - laser[idx].y,
			laser[idx].meteoPos.x - laser[idx].x);

		//レーザーの現在の移動方向の角度.
		double currentAngle = atan2(laser[idx].sy, laser[idx].sx);

		//角度の差分を計算.
		double angleDiff = targetAngle - currentAngle;

		// 角度差分を-PI～PIの範囲に正規化.
		while (angleDiff > M_PI)
		{
			angleDiff -= 2 * M_PI;
		}
		while (angleDiff < -M_PI)
		{
			angleDiff += 2 * M_PI;
		}

		/*
		double distance = sqrt(dx * dx + dy * dy); //隕石までの距離を計算
		if (distance < 50.0)
		{
			//非常に近い場合は大きく曲がる90度まで.
			maxTurn = M_PI / 180 * 90;
		}
		else if (distance < 100.0)
		{
			// 近い場合は中程度に曲がる（45度まで）.
			maxTurn = M_PI / 180 * 45;
		}
		else
		{
			// 遠い場合は通常の旋回（20度まで）
			maxTurn = M_PI / 180 * 20;
		}
		*/

		// 反射レーザーの旋回角度（通常レーザーより少し速く）.
		double maxTurn = _rad(OBSTACLE4_LASER_REF_ROT_MAX);
		if (angleDiff > +maxTurn) angleDiff = +maxTurn;
		if (angleDiff < -maxTurn) angleDiff = -maxTurn;

		//新しい角度を計算して速度を更新
		double newAngle = currentAngle + angleDiff;

		// 現在の速度の大きさを保持.
		double currentSpeed = sqrt(laser[idx].sx * laser[idx].sx +
			laser[idx].sy * laser[idx].sy);

		//固定の速度を使用(回転を防ぐ.
		if (currentSpeed < 5.0)
		{
			currentSpeed = 5.0;
		}

		const double fixedSpeed = 100.0; // 固定速度.

		// 新しい方向に速度を設定
		laser[idx].sx = cos(newAngle) * currentSpeed;
		laser[idx].sy = sin(newAngle) * currentSpeed;
	}
}