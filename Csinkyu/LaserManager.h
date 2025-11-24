/*
   - LaserManager.h -
   レーザー管理クラス.
*/
#pragma once
#include "Laser.h"

//前方宣言.
class GameData;
class Player;
class MeteorManager;
class EffectManager;

//レーザー管理用.
class LaserManager final
{
//▼実体関係.
public:
	//実体取得用.
	static LaserManager& GetInst() {
		static LaserManager inst; //自身のインスタンス.
		return inst;
	}
	//使用禁止.
	LaserManager(const LaserManager&) = delete;
	LaserManager& operator=(const LaserManager&) = delete;
private:
	//constructor(新規作成をできなくする)
	LaserManager(){}

//▼データ.
private:
	//listで適宜サイズを増減する.
	list<LaserData>     laser; //レーザー.
	list<LaserLineData> line;  //レーザー描画線.

	DBL_XY plyPos{}; //プレイヤー座標保管用.

	DrawImg imgLight[2]{};

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
	
	void SpawnLaser       (DBL_XY pos, DBL_XY vel, LaserType type); //召喚.

	bool HitLaser		  (list<LaserData>::iterator);				//当たり判定.
	void ReflectLaser     (list<LaserData>::iterator);              //反射.
	void GenerateLaserLine(list<LaserData>::iterator);              //レーザー描画線を生成.
	void LaserRefTracking (list<LaserData>::iterator);              //レーザー(reflected)の隕石追尾.

	bool IsExistEnemyLaser(DBL_XY pos, float len);                  //敵のレーザーが1つでも存在するかどうか.

	//未使用.
	void LaserReflectRange(Circle* cir);						    //レーザーを一括反射.
};