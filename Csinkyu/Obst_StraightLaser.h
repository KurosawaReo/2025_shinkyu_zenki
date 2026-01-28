/*
   - Obst_StraightLaser.h -

   障害物: 直線レーザー.
*/
#pragma once

//直線レーザー.
class StraightLaser : public ManagerBase
{
private:
	DBL_XY plyPos{};   // プレイヤー座標保管用.

	float  laserSpawnTimer{};  // レーザー発射タイマー.
	float  predictionTimer{};  // 予測線タイマー.
	bool   showPrediction{};   // 予測線表示フラグ
	int    nextLaserIndex{};   // 次の発射するレーザーのインデックス.
	int    currentDirection{}; // 現在の発射方向
	int    nextDirection{};    // 次の発射方向
	double nextCenterPos{};    // 次のレーザー発射位置（予測線用）

public:
	//コンストラクタ.
	StraightLaser() : ManagerBase(ORDER_STR_LASER_MNG) {}

	void Init()   override;
	void Reset()  override;
	void Update() override;
	void Draw()   override;

	void SpawnStraightLaser();   // 直線レーザー発射.
	void DrawPredictionLine();
};