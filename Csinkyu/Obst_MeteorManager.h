/*
   - Obst_MeteorManager.h -

   障害物: 隕石出現管理.
*/
#pragma once
#include "Obst_Meteor.h"

//隕石管理[継承不可]
class MeteorManager final
{
//▼実体関係.
public:
	//実体取得用.
	static MeteorManager& GetInst() {
		static MeteorManager inst; //自身のインスタンス.
		return inst;
	}
	//使用禁止.
	MeteorManager(const MeteorManager&) = delete;
	MeteorManager& operator=(const MeteorManager&) = delete;
private:
	//constructor(新規作成をできなくする)
	MeteorManager(){}

//▼データ.
private:
	Meteor meteor[METEOR_CNT_MAX]{}; //隕石データ.

	float timer{};       //隕石生成用.
	bool  isSpawnAble{}; //召喚可能かどうか.

	GameData*      p_data{};      //ゲームデータ.
	Player*        p_player{};	  //プレイヤー.
	EffectManager* p_effectMng{}; //エフェクト管理.

public:
	//set.
	void SetIsSpawnAble(bool _flag) { isSpawnAble = _flag; }

	void Init();
	void Reset();
	void Update();
	void Draw();

	void SpawnMeteor(); //隕石生成.

	bool IsHitMeteors(Circle cir, bool isDestroy); //隕石のどれか1つでも当たっているか.
	bool GetMeteorPosNearest(DBL_XY _startPos, DBL_XY* _nearPos); //最寄りの隕石座標を探す.
};