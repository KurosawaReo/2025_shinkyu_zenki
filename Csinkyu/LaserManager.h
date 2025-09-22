/*
   - LaserManager.h -
   元々Obstacle4mainとしてまとめられてたレーザー.
*/
#pragma once

//前方宣言.
class GameData;
class Player;
class MeteorManager;
class EffectManager;

//レーザータイプ.
enum LaserType
{
	Laser_Normal,       //通常レーザー.
	Laser_Straight,     //直線レーザー.
	Laser_Reflect,      //反射レーザー.
	Laser_SuperReflect, //反射レーザー強化版.
	Laser_Falling,      //落下レーザー(花火用)
};

//レーザー本体データ.
struct LaserData
{
	LaserType type;      //レーザータイプ.

	double    x,  y;     //現在の座標.
	double    bx, by;    //前回描画した時にいた座標.
	double    vx, vy;    //進行方向ベクトル.

	DBL_XY    goalPos;   //目標地点の座標.
	bool      isGoGoal;  //目標地点に向かって進むか.

	int       LogNum;    //記録した軌跡の数.
	float     Counter;   //追尾を初めてから通過した時間.

	int       ValidFlag; //このデータが使用中かフラグ.
};

//レーザーが描く軌道ラインデータ.
struct LaserLineData
{
	LaserType type;         //レーザータイプ.

	double x1, y1, x2, y2;  //描くラインの座標.
	float  Counter;         //描くラインの色決定用値.

	int    ValidFlag;       //このデータが使用中かフラグ
};

//レーザー管理用.
class LaserManager final
{
public: //実体.
	static LaserManager* GetPtr() {
		static LaserManager inst; //自身のインスタンス.
		return &inst;
	}

private:
	LaserData     laser[LASER_CNT_MAX]{};      //ホーミングレーザーのデータ.
	LaserLineData line [LASER_LINE_CNT_MAX]{}; //ライン描画用データ.

	DBL_XY plyPos{}; //プレイヤー座標保管用.

	GameData*      p_data{};
	Player*        p_player{};
	MeteorManager* p_meteorMng{};
	EffectManager* p_effectMng{};

public:
	void Init();
	void Reset();
	void Update();
	void Draw();

	void UpdateLaser();                                             //各レーザーの更新.
	void UpdateLaserLine();                                         //各レーザー描画線の更新.
	
	bool SpawnLaser       (DBL_XY pos, DBL_XY vel, LaserType type); //召喚.
	void DeleteLaser      (int idx);                                //消去.
	void ReflectLaser     (int idx);               	                //反射.

	bool IsExistEnemyLaser(DBL_XY pos, float len);                  //敵のレーザーが1つでも存在するかどうか.

	void LaserRefTracking (int idx);                                //レーザー(reflected)の隕石追尾.
	void LaserReflectRange(Circle* cir);						    //レーザーの一括反射.
};