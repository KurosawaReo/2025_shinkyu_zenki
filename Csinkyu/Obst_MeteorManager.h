/*
   - Obst_MeteorManager.h -

   障害物: 隕石出現管理.
*/
#pragma once
#include "Obst_Meteor.h"

//隕石管理.
class MeteorManager
{
public: //実体.
	static MeteorManager* GetPtr() {
		static MeteorManager inst; //自身のインスタンス.
		return &inst;
	}

private:
	Meteor meteor[METEOR_CNT_MAX]{}; //隕石データ.
	float timer{};			      //隕石生成用.

	GameData*      p_data{};      //ゲームデータ.
	Player*        p_player{};	  //プレイヤーデータ.
	EffectManager* p_effectMng{};

public:
	void Init();
	void Reset();
	void Update();
	void Draw();

	void SpawnMeteor(); //隕石生成.

	bool IsHitMeteors(Circle cir, bool isDestroy); //隕石のどれか1つでも当たっているか.
	bool GetMeteorPosNearest(DBL_XY _startPos, DBL_XY* _nearPos); //最寄りの隕石座標を探す.
};