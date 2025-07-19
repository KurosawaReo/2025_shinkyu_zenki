/*
   - MapGimmickLaserManager.cpp -
   マップギミック用の直線レーザー管理.
*/
#include "Player.h"
#include "MeteoManager.h"
#include "MapGimmickLaserManager.h"
/// <summary>
/// リセットするぜ.
/// </summary>
/// <param name="_data"></param>
/// <param name="_player"></param>
/// <param name="_meteoMng"></param>
void MapGimmickLaserManager::Init(GameData* _data, Player* _player, MeteoManager* _meteoMng)
{
	//実態取得するぜ.
	p_data = _data;
	p_player = _player;
	p_meteoMng = _meteoMng;

	laserSpawnTimer = 0;
	nextLaserIndex = 0;
	predictionTimer = 0;
	showPrediction = false;
	currentDirection = 0;
	nextDirection = 0;
	// 重複削除: currentDirection = 0;
	// 重複削除: nextDirection = 0;
	nextCenterPos = 0;  // 追加: 次のレーザー発射位置初期化

}
/// <summary>
/// リセットするよ～ん
/// </summary>
void MapGimmickLaserManager::Reset()
{
	//レーザーデータの初期化.
	for (int i = 0; i < 3; i++)
	{
		DeleteLaser(i);//全て削除するぜ.

	}

	//レーザーの軌跡データの初期化.
	for (int i = 0; i < OBSTACLE6_LINE_MAX; i++)
	{
		line[i].ValidFlag = 0;//全ての軌跡を無効化状態に.
	}
	laserSpawnTimer = 0;
	nextLaserIndex = 0;
	predictionTimer = 0;
	showPrediction = false;
	nextCenterPos = 0;  // 追加: 次のレーザー発射位置リセット
}
/// <summary>
/// 更新するぜ.
/// </summary>
void MapGimmickLaserManager::Update()
{
	plyPos = p_player->GetPos();//プレイヤーの現在位置を取得.

	//レーザー発射タイマー更新.
	laserSpawnTimer += (p_data->isSlow) ? SLOW_MODE_SPEED : 1;

	// 予測線表示タイマー更新（レーザー発射の60フレーム前から表示）
	if (laserSpawnTimer >= 180) // 240-60 = 180フレームから予測線表示
	{
		if (!showPrediction)
		{
			// 予測線表示開始時に次の発射方向と位置を決定
			nextDirection = rand() % 4;

			// 次の発射位置もランダムに決定
			if (nextDirection == 0 || nextDirection == 1) // 水平発射
			{
				nextCenterPos = 100 + rand() % (WINDOW_HEI - 200);
			}
			else // 垂直発射
			{
				nextCenterPos = 100 + rand() % (WINDOW_WID - 200);
			}

			showPrediction = true;
		}
		predictionTimer = laserSpawnTimer - 180; // 予測線表示からの経過時間
	}
	else
	{
		showPrediction = false;
		predictionTimer = 0;
	}

	//240フレーム(約4秒)ごとに3つの直線レーザーを同時発射.
	if (laserSpawnTimer >= 240)
	{
		SpawnStraightLaser();
		laserSpawnTimer = 0;
		showPrediction = false;
		predictionTimer = 0;
		currentDirection = nextDirection; // 予測した方向で発射
	}

	UpdateLaser();    //各レーザーの更新.
	UpdateLaserLine();//各レーザー描画線の更新.

}
/// <summary>
/// 描画処理だぜ～
/// </summary>
void MapGimmickLaserManager::Draw()
{
	// 予測線の描画（レーザーより先に描画）
	if (showPrediction)
	{
		DrawPredictionLine();
	}

	//レーザーの軌跡の描画処理.
	for (int i = 0; i < OBSTACLE6_LINE_MAX; i++)
	{
		if (line[i].ValidFlag == 0) continue;  // 無効な軌跡はスキップ

		//時間経過で徐々に薄くする.
		int clr = _int(255 - line[i].Counter * 4);
		clr = max(clr, 0); //最低値を0にする.

		//加算合成モードで軌跡を描画(発光エフェクト)
		SetDrawBlendMode(DX_BLENDMODE_ADD, clr);

		//軌跡の線設定.
		Line tmpLine = { {line[i].x1,line[i].y1} , { line[i].x2,line[i].y2 }, {} };

		//直線のレーザー(青色にしたぜ)
		tmpLine.clr = GetColor(50, clr, 255);
		DrawLineST(&tmpLine);//描画.

	}
	//通常の描画モードに戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

/// <summary>
/// 予測線描画処理
/// </summary>
void MapGimmickLaserManager::DrawPredictionLine()
{
	// 次のレーザー発射方向と位置を使用
	double startX, startY, endX, endY;
	double centerPos = nextCenterPos;  // 修正: 予測された位置を使用

	// 点滅効果（30フレーム周期で点滅）
	int blinkCycle = 30;
	int alpha = 128; // 基本透明度
	if ((predictionTimer / blinkCycle) % 2 == 0)
	{
		alpha = 64; // 薄くする
	}

	// 灰色の予測線を描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	// 中央の予測線のみを描画
	// 発射方向に応じて予測線を描画
	switch (nextDirection)
	{
	case 0: // 左から右へ
		startX = -50;
		endX = WINDOW_WID + 50;
		{
			Line predictionLine = { {startX, centerPos}, {endX, centerPos}, {} };
			predictionLine.clr = GetColor(128, 128, 128); // 灰色
			DrawLineST(&predictionLine);
		}
		break;
	case 1: // 右から左へ
		startX = WINDOW_WID + 50;
		endX = -50;
		{
			Line predictionLine = { {startX, centerPos}, {endX, centerPos}, {} };
			predictionLine.clr = GetColor(128, 128, 128); // 灰色
			DrawLineST(&predictionLine);
		}
		break;
	case 2: // 上から下へ
		startY = -50;
		endY = WINDOW_HEI + 50;
		{
			Line predictionLine = { {centerPos, startY}, {centerPos, endY}, {} };
			predictionLine.clr = GetColor(128, 128, 128); // 灰色
			DrawLineST(&predictionLine);
		}
		break;
	case 3: // 下から上へ
		startY = WINDOW_HEI + 50;
		endY = -50;
		{
			Line predictionLine = { {centerPos, startY}, {centerPos, endY}, {} };
			predictionLine.clr = GetColor(128, 128, 128); // 灰色
			DrawLineST(&predictionLine);
		}
		break;
	}

	// 描画モードを戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

/// <summary>
/// 各レーザーの更新(むずいぜ)
/// </summary>
void MapGimmickLaserManager::UpdateLaser()
{
	const double pSizeHalf = PLAYER_SIZE / 2.0;//プレイヤーの当たり判定サイズの半分.

	//各レーザーの更新.
	for (int i = 0; i < 3; i++)
	{
		if (laser[i].ValidFlag == 0)continue; //無効なレーザーはスキップ.

		//プレイヤーとレーザーの当たり判定
		int x = (laser[i].x > plyPos.x - pSizeHalf && laser[i].x < plyPos.x + pSizeHalf);
		int y = (laser[i].y > plyPos.y - pSizeHalf && laser[i].y < plyPos.y + pSizeHalf);

		//プレイヤーとレーザーの当たり判定
		if (x && y)
		{
			DeleteLaser(i);
			p_player->PlayerDeath(); //プレイヤー死亡.
			continue;
		}

		//レーザーの通過時間カウンタを増加.
		laser[i].Counter += (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);

		//移動前の座標を保存.
		DBL_XY befPos = { laser[i].x,laser[i].y };

		//速度(直線レーザーなので一定速度) - 修正: 括弧で優先順位を明確化
		double speed = 50.0 * ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);

		//レーザーの移動.
		laser[i].x += laser[i].vx * speed;
		laser[i].y += laser[i].vy * speed;

		//レーザーの軌跡を生成.
		for (int j = 0; j < OBSTACLE6_LINE_MAX; j++)
		{
			if (line[j].ValidFlag == 0) //未使用の軌跡スロット.
			{
				//軌跡データの設定.
				line[j].x1 = befPos.x;   //開始点X座標.
				line[j].y1 = befPos.y;   //開始点Y座標.
				line[j].x2 = laser[i].x; //終了点X座標.
				line[j].y2 = laser[i].y; //終了点Y座標.
				line[j].Counter = 0;   //通過時間カウンタ初期化.
				line[j].ValidFlag = 1;   //軌跡を有効化.
				break;
			}
		}

		//画面外判定も修正（同じ演算子優先順位問題）
		int _x = (laser[i].x < -100) || (laser[i].x > WINDOW_WID + 100);
		int _y = (laser[i].y < -100) || (laser[i].y > WINDOW_HEI + 100);

		//画面外に出たレーザーを無効化.
		if (_x || _y)
		{
			DeleteLaser(i);
		}
	}

}
/// <summary>
/// 各レーザー描画線の更新(いやむずて～).
/// </summary>
void MapGimmickLaserManager::UpdateLaserLine()
{
	for (int i = 0; i < OBSTACLE6_LINE_MAX; i++)
	{
		if (line[i].ValidFlag == 0)continue;

		//通過時間カウンタ増加.
		line[i].Counter += (p_data->isSlow) ? SLOW_MODE_SPEED : 1;
		// 64フレーム経過したら軌跡を無効化
		if (line[i].Counter >= 64) line[i].ValidFlag = 0;
	}
}

/// <summary>
/// //直線レーザー発射(コードおもれー) - ランダム発射版
/// </summary>
void MapGimmickLaserManager::SpawnStraightLaser()
{
	// 予測された方向で発射
	int direction = nextDirection;  // 修正: currentDirectionではなくnextDirectionを使用

	double startX, startY, vx, vy;
	double centerPos = nextCenterPos;  // 修正: 予測された位置を使用
	double spacing = 20;  // レーザー間の間隔

	switch (direction)
	{
	case 0: // 左から右へ発射
		startX = -50;
		vx = 1.0;
		vy = 0.0;
		break;
	case 1: // 右から左へ発射
		startX = WINDOW_WID + 50;
		vx = -1.0;
		vy = 0.0;
		break;
	case 2: // 上から下へ発射
		startY = -50;
		vx = 0.0;
		vy = 1.0;
		break;
	case 3: // 下から上へ発射
		startY = WINDOW_HEI + 50;
		vx = 0.0;
		vy = -1.0;
		break;
	}

	// 3つのレーザーを同時に発射
	for (int i = 0; i < 3; i++)
	{
		// 既存のレーザーがあれば削除
		if (laser[i].ValidFlag == 1)
		{
			DeleteLaser(i);
		}

		// レーザーデータの初期化
		if (direction == 0 || direction == 1) // 水平発射
		{
			laser[i].x = startX;
			laser[i].y = centerPos + (i - 1) * spacing; // -spacing, 0, +spacing
		}
		else // 垂直発射
		{
			laser[i].x = centerPos + (i - 1) * spacing; // -spacing, 0, +spacing
			laser[i].y = startY;
		}

		laser[i].vx = vx;            // 初期方向x
		laser[i].vy = vy;            // 初期方向y
		laser[i].Counter = 0;        // 経過時間カウンタ初期化
		laser[i].ValidFlag = 1;      // レーザーを有効化
	}

	nextLaserIndex = 0;
	currentDirection = nextDirection; // 発射後に現在の方向を更新
}
///レーザー消去.
void MapGimmickLaserManager::DeleteLaser(int idx) {
	laser[idx].ValidFlag = 0;       //無効にする.
	laser[idx].Counter = 0;         //カウンターリセット.
}