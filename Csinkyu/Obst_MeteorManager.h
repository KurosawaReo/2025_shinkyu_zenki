/*
   - Obst_MeteorManager.h -

   障害物: 隕石出現管理.
*/
#pragma once
#include "Obst_Meteor.h"

//隕石管理.
class MeteorManager : public ManagerBase
{
//▼実体関係.
public:
	static MeteorManager& GetInst() {
		static MeteorManager inst; //自身のインスタンス.
		return inst;
	}

//▼変数.
private:
	list<Meteor>   meteor;		  //隕石配列.

	float		   timer{};       //隕石生成用.
	bool		   isSpawnAble{}; //召喚可能かどうか.

//▼関数.
private:
	//コンストラクタ.
	MeteorManager() : ManagerBase(ORDER_METEOR_MNG) {}

public:
	//get.
	Meteor* GetHitMeteor    (Circle cir, bool isDestroy); //範囲内の隕石を取得(1つ)
	Meteor* GetNearestMeteor(DBL_XY pos);				  //最寄りの隕石を取得.
	//set.
	void SetIsSpawnAble(bool _flag) { isSpawnAble = _flag; }

	void Init()   override;
	void Reset()  override;
	void Update() override;
	void Draw()   override;

	void SpawnMeteor();                       //隕石生成.
	void BreakMeteor(DBL_XY pos, DBL_XY vec); //隕石破壊演出.

	//使用禁止.
	MeteorManager(const MeteorManager&) = delete;
	MeteorManager& operator=(const MeteorManager&) = delete;
};