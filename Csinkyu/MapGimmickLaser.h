/* 
   - MapGimmickLaserManager.h -
   マップギミック用の直線レーザー管理.
*/
#pragma once
//#include "MeteoManager.h"

//マップギミックレーザー管理用.
class MapGimmickLaser
{
private:
//	STRAIGHT_LASER_DATA laser[3]{};
//	STRAIGHT_LINE_DATA line[OBSTACLE6_LINE_MAX]{}; //レーザーはLaserManagerに統一しとく.

	DBL_XY plyPos{};   // プレイヤー座標保管用.

	GameData*     p_data{};
	Player*       p_player{};
	LaserManager* p_laserMng{};
	MeteoManager* p_meteoMng{};

	float  laserSpawnTimer{};  // レーザー発射タイマー.
	float  predictionTimer{};  // 予測線タイマー.
	bool   showPrediction{};   // 予測線表示フラグ
	int    nextLaserIndex{};   // 次の発射するレーザーのインデックス.
	int    currentDirection{}; // 現在の発射方向
	int    nextDirection{};    // 次の発射方向
	double nextCenterPos{};    // 次のレーザー発射位置（予測線用）

public:
	void Init(GameData*, Player*, LaserManager*, MeteoManager*);
	void Reset();
	void Update();
	void Draw();

	void SpawnStraightLaser();   // 直線レーザー発射.
	void DrawPredictionLine();
};

//↑のクラスの実体を2つ出せばいいため不要.
#if false
#include "Player.h"
#include "MapGimmickLaserManager.h"
class MapGimmickLaser : public MapGimmickLaserManager
{
public:


private:

};
#endif