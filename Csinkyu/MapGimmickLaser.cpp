/*
   - MapGimmickLaserManager.cpp -
   マップギミック用の直線レーザー管理.
*/
#include "Player.h"
#include "MeteoManager.h"
#include "LaserManager.h"

#include "MapGimmickLaser.h"

/// <summary>
/// リセットするぜ.
/// </summary>
void MapGimmickLaser::Init(GameData* _data, Player* _player, LaserManager* _laserMng, MeteoManager* _meteoMng)
{
	//実態取得するぜ.
	p_data     = _data;
	p_player   = _player;
	p_laserMng = _laserMng;
	p_meteoMng = _meteoMng;
	p_calc     = Calc::GetPtr();

	currentDirection = 0;
	nextDirection = 0;
	// 重複削除: currentDirection = 0;
	// 重複削除: nextDirection = 0;
	
	Reset();
}
/// <summary>
/// リセットするよ～ん
/// </summary>
void MapGimmickLaser::Reset()
{
	laserSpawnTimer = MGL_LASER_PREDICTION_TIME+80; //予測線が出るタイミングから開始.
	nextLaserIndex = 0;
	predictionTimer = 0;
	showPrediction = false;
	nextCenterPos = 0;  //次のレーザー発射位置リセット
}
/// <summary>
/// 更新するぜ.
/// </summary>
void MapGimmickLaser::Update()
{
	plyPos = p_player->GetPos();//プレイヤーの現在位置を取得.

	//レーザー発射タイマー更新.
	laserSpawnTimer -= (p_data->isSlow) ? SLOW_MODE_SPEED : 1;

	// 予測線表示タイマー更新（レーザー発射の60フレーム前から表示）
	if (laserSpawnTimer <= MGL_LASER_PREDICTION_TIME)
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
		predictionTimer = MGL_LASER_PREDICTION_TIME - laserSpawnTimer; // 予測線表示からの経過時間
	}
	else
	{
		showPrediction = false;
		predictionTimer = 0;
	}

	//タイミングになったら3つの直線レーザーを同時発射.
	if (laserSpawnTimer <= 0)
	{
		SpawnStraightLaser();

		//タイマー再開(徐々に短くなる)
		//予測線の出る時間より短くならないよう設定.
		laserSpawnTimer = MGL_LASER_PREDICTION_TIME + MGL_LASER_SPAWN_SPAN * p_data->spawnRate;

		showPrediction = false;
		predictionTimer = 0;
		currentDirection = nextDirection; // 予測した方向で発射
	}
}
/// <summary>
/// 描画処理だぜ～
/// </summary>
void MapGimmickLaser::Draw()
{
	// 予測線の描画（レーザーより先に描画）
	if (showPrediction)
	{
		DrawPredictionLine();
	}
}

/// <summary>
/// 予測線描画処理
/// </summary>
void MapGimmickLaser::DrawPredictionLine()
{
	// 次のレーザー発射方向と位置を使用
	double startX, startY, endX, endY;
	double centerPos = nextCenterPos;  // 修正: 予測された位置を使用

	//30フレーム周期だとそもそも点滅してない.
#if false
	// 点滅効果（30フレーム周期で点滅）
	int blinkCycle = 30;
	int alpha = 128; // 基本透明度
	if ((predictionTimer / blinkCycle) % 2 == 0)
	{
		alpha = 64; // 薄くする
	}
#endif

	// 予測線の透明度.
	double alpha = p_calc->CalcNumEaseIn((float)predictionTimer/MGL_LASER_PREDICTION_TIME); //0.0～1.0の範囲.
	SetDrawBlendModeST(MODE_ALPHA, 255*(1-alpha));

	// 中央の予測線のみを描画
	// 発射方向に応じて予測線を描画
	switch (nextDirection)
	{
	case 0: // 左から右へ
		startX = -50;
		endX = WINDOW_WID + 50;
		{
			Line predictionLine = { {startX, centerPos}, {endX, centerPos}, {} };
			predictionLine.color = COLOR_PRE_LINE;
			DrawLineST(&predictionLine, true);
		}
		break;
	case 1: // 右から左へ
		startX = WINDOW_WID + 50;
		endX = -50;
		{
			Line predictionLine = { {startX, centerPos}, {endX, centerPos}, {} };
			predictionLine.color = COLOR_PRE_LINE;
			DrawLineST(&predictionLine, true);
		}
		break;
	case 2: // 上から下へ
		startY = -50;
		endY = WINDOW_HEI + 50;
		{
			Line predictionLine = { {centerPos, startY}, {centerPos, endY}, {} };
			predictionLine.color = COLOR_PRE_LINE;
			DrawLineST(&predictionLine, true);
		}
		break;
	case 3: // 下から上へ
		startY = WINDOW_HEI + 50;
		endY = -50;
		{
			Line predictionLine = { {centerPos, startY}, {centerPos, endY}, {} };
			predictionLine.color = COLOR_PRE_LINE;
			DrawLineST(&predictionLine, true);
		}
		break;
	}

	// 描画モードを戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

/// <summary>
/// //直線レーザー発射(コードおもれー) - ランダム発射版
/// </summary>
void MapGimmickLaser::SpawnStraightLaser()
{
	// 予測された方向で発射
	int direction = nextDirection;  // 修正: currentDirectionではなくnextDirectionを使用

	double centerPos = nextCenterPos;  // 修正: 予測された位置を使用
	double spacing = 20;  // レーザー間の間隔

	DBL_XY startPos{};
	DBL_XY vel{};

	switch (direction)
	{
	case 0: // 左から右へ発射
		startPos.x = -50;
		vel = { +1.0, 0.0 };
		break;
	case 1: // 右から左へ発射
		startPos.x = WINDOW_WID + 50;
		vel = { -1.0, 0.0 };
		break;
	case 2: // 上から下へ発射
		startPos.y = -50;
		vel = { 0.0, +1.0 };
		break;
	case 3: // 下から上へ発射
		startPos.y = WINDOW_HEI + 50;
		vel = { 0.0, -1.0 };
		break;
	}

	// 3つのレーザーを同時に発射
	for (int i = 0; i < 3; i++)
	{
		DBL_XY tmpPos{};
		// レーザーデータの初期化
		if (direction == 0 || direction == 1) // 水平発射
		{
			tmpPos.x = startPos.x;
			tmpPos.y = centerPos + (i-1) * spacing; // -spacing, 0, +spacing
		}
		else // 垂直発射
		{
			tmpPos.x = centerPos + (i-1) * spacing; // -spacing, 0, +spacing
			tmpPos.y = startPos.y;
		}

		//直線レーザーを発射.
		p_laserMng->SpawnLaser(tmpPos, vel, Laser_Straight);
	}

	nextLaserIndex = 0;
	currentDirection = nextDirection; // 発射後に現在の方向を更新
}