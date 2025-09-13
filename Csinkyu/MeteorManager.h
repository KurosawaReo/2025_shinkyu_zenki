/*
   - MeteorManager.h -
   隕石の出現を管理する.
*/
#pragma once
#include "Meteor.h"
#include "EffectManager.h"

//隕石管理.
class MeteorManager
{
private:
	Meteor meteor[METEO_CNT_MAX]{}; //隕石データ.
	float timer{};			      //隕石生成用.

	GameData*      p_data{};      //ゲームデータ.
	Player*        p_player{};	  //プレイヤーデータ.
	EffectManager* p_effectMng{};

public:
	void Init(GameData*, Player*, EffectManager*);
	void Reset();
	void Update();
	void Draw();

	void SpawnMeteor(); //隕石生成.

	bool IsHitMeteors(Circle* cir, bool isDestroy); //隕石のどれか1つでも当たっているか.
	bool GetMeteorPosNearest(DBL_XY _startPos, DBL_XY* _nearPos); //最寄りの隕石座標を探す.
};