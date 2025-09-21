/*
   - Obst_StraightLaser.h -

   障害物: 直線レーザー.
*/
#pragma once
//#include "MeteoManager.h"

//直線レーザー.
class StraightLaser
{
private:
	DBL_XY plyPos{};   // プレイヤー座標保管用.

	GameData*      p_data{};
	Player*        p_player{};
	LaserManager*  p_laserMng{};
	MeteorManager* p_meteorMng{};

	float  laserSpawnTimer{};  // レーザー発射タイマー.
	float  predictionTimer{};  // 予測線タイマー.
	bool   showPrediction{};   // 予測線表示フラグ
	int    nextLaserIndex{};   // 次の発射するレーザーのインデックス.
	int    currentDirection{}; // 現在の発射方向
	int    nextDirection{};    // 次の発射方向
	double nextCenterPos{};    // 次のレーザー発射位置（予測線用）

public:
	void Init();
	void Reset();
	void Update();
	void Draw();

	void SpawnStraightLaser();   // 直線レーザー発射.
	void DrawPredictionLine();
};