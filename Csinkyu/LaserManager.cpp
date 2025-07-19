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
	for (int i = 0; i < LASER_CNT_MAX; i++) {
		DeleteLaser(i); //全て消去しておく.
	}
	//レーザーの軌跡データの初期化.
	for (int i = 0; i < LASER_LINE_CNT_MAX; i++) {
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
	for (int i = 0; i < LASER_LINE_CNT_MAX; i++)
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
			case Laser_Straight:  tmpLine.clr = GetColor(50, clr, 255); break;
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
	for (int i = 0; i < LASER_CNT_MAX; i++)
	{
		if (laser[i].ValidFlag == 0) continue;  // 無効なレーザーはスキップ

		//移動前の座標を保存.
		DBL_XY befPos = { laser[i].x, laser[i].y };
		//弾が当たったかどうか.
		bool isHit = false;

		//レーザータイプ別.
		switch (laser[i].type)
		{
			case Laser_Normal:
			{
				// プレイヤーとレーザーの当たり判定
				if ((laser[i].x > plyPos.x - pSizeHalf && laser[i].x < plyPos.x + pSizeHalf) &&
					(laser[i].y > plyPos.y - pSizeHalf && laser[i].y < plyPos.y + pSizeHalf))
				{
					//反射あり.
					if (p_player->IsReflectionMode())
					{
						ReflectLaser(i); //レーザーを反射.		
					}
					//反射なし.
					else
					{
						DeleteLaser(i);
						p_player->PlayerDeath(); //プレイヤー死亡.
					}
					isHit = true; //当たったことを記録.
				}

				//速度(時間経過で速くなる)
				double speed = laser[i].Counter * LASER_NOR_SPEED * (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
				//レーザーの移動.
				laser[i].x += laser[i].vx * speed;
				laser[i].y += laser[i].vy * speed;
				
				//レーザーの追尾処理.
				LaserNorTracking(i);
			}
			break;

			case Laser_Straight:
			{
				// プレイヤーとレーザーの当たり判定
				if ((laser[i].x > plyPos.x - pSizeHalf && laser[i].x < plyPos.x + pSizeHalf) &&
					(laser[i].y > plyPos.y - pSizeHalf && laser[i].y < plyPos.y + pSizeHalf))
				{
					//反射あり.
					if (p_player->IsReflectionMode())
					{
						ReflectLaser(i); //レーザーを反射.		
					}
					//反射なし.
					else
					{
						DeleteLaser(i);
						p_player->PlayerDeath(); //プレイヤー死亡.
					}
					isHit = true; //当たったことを記録.
				}

				//速度(直線レーザーなので一定速度)
				double speed = 50.0 * ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
				//レーザーの移動.
				laser[i].x += laser[i].vx * speed;
				laser[i].y += laser[i].vy * speed;
			}
			break;

			case Laser_Reflected:
			{
				//一定時間で目標地点を決める.
				if (laser[i].Counter >= LASER_REF_TRACK_ST_TM) {

					assert(p_meteoMng != nullptr); //ポインタが空でないことを確認.

					DBL_XY laserPos = { laser[i].x, laser[i].y }; //レーザーの現在位置.
					DBL_XY meteoPos{-1, -1};

					//最も近い隕石の位置を取得する.
					bool hasMeteo = p_meteoMng->GetMeteoPosNearest(laserPos, &meteoPos);
					//隕石があった場合.
					if (hasMeteo) {
						laser[i].goalPos = meteoPos; //登録.
						laser[i].isGoGoal = true;
					}
				}

				Circle hit = { {laser[i].x, laser[i].y}, 10, {} }; //当たり判定円(仮)

				//隕石と当たっているなら.
				if (p_meteoMng->IsHitMeteos(&hit, TRUE)) {
					DeleteLaser(i);
					isHit = true;
					break;
				}
				//レーザーの追尾処理.
				LaserRefTracking(i);

				//速度(時間経過で速くなる)
				double speed = laser[i].Counter * LASER_REF_SPEED * (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
				//レーザーの移動.
				laser[i].x += laser[i].vx * speed;
				laser[i].y += laser[i].vy * speed;
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

		// レーザーの軌跡を生成
		for (int j = 0; j < LASER_LINE_CNT_MAX; j++)
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

		//画面外判定.
		int _x = (laser[i].x < -100) || (laser[i].x > WINDOW_WID + 100);
		int _y = (laser[i].y < -100) || (laser[i].y > WINDOW_HEI + 100);
		//画面外に出たレーザーを無効化.
		if (_x || _y)
		{
			DeleteLaser(i);
		}
	}
}
//各レーザー描画線の更新.
void LaserManager::UpdateLaserLine() {

	for (int i = 0; i < LASER_LINE_CNT_MAX; i++) {

		// 経過時間カウンタ増加
		line[i].Counter += (p_data->isSlow) ? SLOW_MODE_SPEED : 1;
		// 64フレーム経過したら軌跡を無効化
		if (line[i].Counter >= 64) line[i].ValidFlag = 0;
	}
}

//レーザー召喚.
BOOL LaserManager::SpawnLaser(DBL_XY pos, DBL_XY vel, LaserType type) {

	// 未使用のレーザースロットを探してレーザーを発射
	for (int i = 0; i < LASER_CNT_MAX; i++)
	{
		if (laser[i].ValidFlag == 0)  // 未使用のレーザースロットを見つけた
		{
			// レーザーデータの初期化
			laser[i].x = pos.x;	    // 初期座標x
			laser[i].y = pos.y;     // 初期座標y
			laser[i].vx = vel.x;    // 初期方向x
			laser[i].vy = vel.y;    // 初期方向y
			laser[i].Counter = 0;	// 経過時間カウンタ初期化
			laser[i].LogNum = 0;	// 軌跡カウンタ初期化
			laser[i].ValidFlag = 1;	// レーザーを有効化
			laser[i].type = type;   // タイプの登録

			return TRUE; //召喚成功.
		}
	}
	return FALSE; //召喚失敗.
}
//レーザー消去.
void LaserManager::DeleteLaser(int idx) {

	laser[idx].type = Laser_Normal; //ノーマルモードに戻す.
	laser[idx].goalPos = {0, 0};    //目標地点リセット.
	laser[idx].isGoGoal = false;    //目標地点なし.
	laser[idx].ValidFlag = 0;       //無効にする.
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

	//反射時の元の角度.
	double ang = _dig(atan2(laser[idx].vy, laser[idx].vx));
	//角度を逆方向へ(少しだけランダムでずれる)
	ang += 180 + (float)RndNum(-200, 200)/10;
	//角度反映.
	laser[idx].vx = cos(_rad(ang));
	laser[idx].vy = sin(_rad(ang));

	// レーザーをプレイヤーから少し離れた位置に移動（重複当たり判定を防ぐ）
	double pushDistance = PLAYER_SIZE / 2.0 + 5; // プレイヤーサイズの半分 + 余裕
	laser[idx].x = plyPos.x + -dx * pushDistance;
	laser[idx].y = plyPos.y + -dy * pushDistance;

	laser[idx].type    = Laser_Reflected; //反射モードへ.
	laser[idx].Counter = 0;               //カウンターをリセット.
}

//レーザー(normal)の隕石追尾.
void LaserManager::LaserNorTracking(int idx) 
{
	//一定時間のみ追尾.
	if (laser[idx].Counter < 200)  // 200フレーム（約3.3秒）以内のみ追尾
	{
		// 現在のプレイヤー方向への角度を計算
		double targetAngle = atan2(plyPos.y - laser[idx].y, plyPos.x - laser[idx].x);
		// レーザーの現在の移動方向
		double currentAngle = atan2(laser[idx].vy, laser[idx].vx);
		// 角度の差分を計算
		double angleDiff = targetAngle - currentAngle;

		// 角度差分を-PI～PIの範囲に正規化
		while (angleDiff > +M_PI) angleDiff -= 2 * M_PI;
		while (angleDiff < -M_PI) angleDiff += 2 * M_PI;

		// 最大旋回角度を制限（1フレームにn度まで）
		const double maxTurn = _rad(LASER_NOR_ROT_MAX) * (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		if (angleDiff > +maxTurn) angleDiff = +maxTurn;
		if (angleDiff < -maxTurn) angleDiff = -maxTurn;

		// 新しい角度を計算.
		double newAngle = currentAngle + angleDiff;
		laser[idx].vx += cos(newAngle);
		laser[idx].vy += sin(newAngle);
	}
}
//レーザー(reflected)の隕石追尾.
void LaserManager::LaserRefTracking(int idx)
{
	//目標地点に向かうなら.
	if (laser[idx].isGoGoal) {
		//一定時間のみ追尾.
		if (laser[idx].Counter > LASER_REF_TRACK_ST_TM &&
		    laser[idx].Counter < LASER_REF_TRACK_ED_TM) 
		{
			//目標地点までの座標差と方角.
			double targetAngle = atan2(laser[idx].goalPos.y - laser[idx].y, laser[idx].goalPos.x - laser[idx].x);
			//レーザーの現在の移動方向の角度.
			double currentAngle = atan2(laser[idx].vy, laser[idx].vx);
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

			// 反射レーザーの旋回角度（通常レーザーより少し速く）.
			double maxTurn = _rad(LASER_REF_ROT_MAX) * (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
			if (angleDiff > +maxTurn) angleDiff = +maxTurn;
			if (angleDiff < -maxTurn) angleDiff = -maxTurn;

			//新しい角度を計算して速度を更新
			double newAngle = currentAngle + angleDiff;

			// 方向を計算して設定.
			laser[idx].vx = cos(newAngle);
			laser[idx].vy = sin(newAngle);
		}
	}
}