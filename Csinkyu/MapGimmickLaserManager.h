/* - MapGimmickLaserManager.h -
   マップギミック用の直線レーザー管理.
*/
#pragma once
#include "MeteoManager.h"
#include "Global.h"

// 直線レーザー本体.
 typedef struct tagStraightLASER_DATA
{

	double    x, y;     //現在の座標.
	double    vx, vy;    //進行方向ベクトル.

	DBL_XY    goalPos;   //最寄り隕石座標を記録する用.
	BOOL      isGoGoal;  //目標地点に向かって進むか.

	int       LogNum;    //記録した軌跡の数.
	float     Counter;   //追尾を初めてから通過した時間.

	int       ValidFlag; //このデータが使用中かフラグ.

}STRAIGHT_LASER_DATA, * LPSTRAIGHT_LASER_DATA;

 // レーザーが描く軌道ライン.
 typedef struct tagStraightLINE_DATA
 {
	 double x1, y1, x2, y2;  // 描くラインの座標.
	 float Counter;          // 描くラインの色決定用値.
	 int ValidFlag;          // このデータが使用中かフラグ.
 }STRAIGHT_LINE_DATA, * LPSTRAIGHT_LINE_DATA;

 //マップギミックレーザー管理用.
 class MapGimmickLaserManager
 {
 private:
	 STRAIGHT_LASER_DATA laser[3]{};
	 STRAIGHT_LINE_DATA line[OBSTACLE6_LINE_MAX]{};

	 DBL_XY plyPos{};   // プレイヤー座標保管用.

	 GameData*     p_data{};
	 Player*       p_player{};
	 MeteoManager* p_meteoMng{};

	 float laserSpawnTimer{};//レーザー発射タイマー.
	 int   nextLaserIndex{}; //次の発射するレーザーのインデックス.

 public:

	 void Init(GameData*, Player*, MeteoManager*);
	 void Reset();
	 void Update();
	 void Draw();

	 void UpdateLaser();          // 各レーザーの更新.
	 void UpdateLaserLine();      // 各レーザー描画線の更新.
	 void SpawnStraightLaser();   // 直線レーザー発射.
	 void DeleteLaser(int idx);   // 消去.
 };