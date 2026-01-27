/*
   - Obst_StraightLaser.h -

   障害物: 直線レーザー.
*/
#include "Obst_StraightLaser.h"

//依存関係.
#include "Player.h"
#include "LaserManager.h"
#include "Obst_MeteorManager.h"
#include "GameData.h"
#include "GameManager.h"
//参照.
static GameData&      gameData  = GameData::GetInst();
static Player&        player    = Player::GetInst();
static LaserManager&  laserMng  = LaserManager::GetInst();
static MeteorManager& meteorMng = MeteorManager::GetInst();

/// <summary>
/// 初期化.
/// </summary>
void StraightLaser::Init()
{
	currentDirection = 0;
	nextDirection = 0;
	
	Reset();
}
/// <summary>
/// リセット.
/// </summary>
void StraightLaser::Reset()
{
	laserSpawnTimer = LASER_STR_PREDICTION_TIME+80; //予測線が出るタイミングから開始.
	nextLaserIndex = 0;
	predictionTimer = 0;
	showPrediction = false;
	nextCenterPos = 0;  //次のレーザー発射位置リセット
}
/// <summary>
/// 更新.
/// </summary>
void StraightLaser::Update()
{
	plyPos = player.GetPos();//プレイヤーの現在位置を取得.

	//レーザー発射タイマー更新.
	laserSpawnTimer -= gameData.speedRate;

	// 予測線表示タイマー更新（レーザー発射の60フレーム前から表示）
	if (laserSpawnTimer <= LASER_STR_PREDICTION_TIME)
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
		predictionTimer = LASER_STR_PREDICTION_TIME - laserSpawnTimer; // 予測線表示からの経過時間
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
		laserSpawnTimer = LASER_STR_PREDICTION_TIME + LASER_STR_SPAWN_SPAN * gameData.spawnRate;

		showPrediction = false;
		predictionTimer = 0;
		currentDirection = nextDirection; // 予測した方向で発射
	}
}
/// <summary>
/// 描画.
/// </summary>
void StraightLaser::Draw()
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
void StraightLaser::DrawPredictionLine()
{
	//予測線の透明度.
	const double alpha = Calc::AnimEaseIn((float)predictionTimer/LASER_STR_PREDICTION_TIME); //0.0～1.0の範囲.
	//予測線の位置.
	const double centerPos = nextCenterPos;

	{
		DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * (1 - alpha));
	
		Line preLine = { {0, 0}, {0, 0}, {} };
		//位置の設定.
		switch (nextDirection)
		{
		case 0: //→.
			preLine.stPos = { -50,             centerPos };
			preLine.edPos = { WINDOW_WID + 50, centerPos };
			break;
		case 1: //←.
			preLine.stPos = { WINDOW_WID + 50, centerPos };
			preLine.edPos = { -50,             centerPos };
			break;
		case 2: //↓.
			preLine.stPos = { centerPos, -50             };
			preLine.edPos = { centerPos, WINDOW_HEI + 50 };
			break;
		case 3: //↑.
			preLine.stPos = { centerPos, WINDOW_HEI + 50 };
			preLine.edPos = { centerPos, -50             };
			break;
		}
		//描画.
		preLine.color = COLOR_PRE_EFFECT;
		DrawLineKR(preLine, true);
	}
}

/// <summary>
/// 直線レーザー発射.
/// </summary>
void StraightLaser::SpawnStraightLaser()
{
	//予測線と同じ所を通る.
	const int    direction = nextDirection;
	const double centerPos = nextCenterPos;
	//レーザー間の間隔.
	const double spacing = 20;

	DBL_XY startPos{};
	DBL_XY vel{};

	switch (direction)
	{
	case 0: //→.
		startPos.x = -50;
		vel = { +1.0, 0.0 };
		break;
	case 1: //←.
		startPos.x = WINDOW_WID + 50;
		vel = { -1.0, 0.0 };
		break;
	case 2: //↓.
		startPos.y = -50;
		vel = { 0.0, +1.0 };
		break;
	case 3: //↑.
		startPos.y = WINDOW_HEI + 50;
		vel = { 0.0, -1.0 };
		break;
	}

	//3つのレーザーを同時に発射.
	for (int i = 0; i < 3; i++)
	{
		DBL_XY tmpPos{};
		
		//水平発射.
		if (direction == 0 || direction == 1) {
			tmpPos.x = startPos.x;
			tmpPos.y = centerPos + (i-1) * spacing; // -spacing, 0, +spacing
		}
		//垂直発射.
		else {
			tmpPos.x = centerPos + (i-1) * spacing; // -spacing, 0, +spacing
			tmpPos.y = startPos.y;
		}
		//直線レーザーを発射.
		laserMng.SpawnLaser(tmpPos, vel, Laser_Straight);
	}

	nextLaserIndex = 0;
	currentDirection = nextDirection; //発射後に現在の方向を更新.
}