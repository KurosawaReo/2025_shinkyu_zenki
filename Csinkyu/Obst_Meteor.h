/*
   - Obst_Meteor.h -
   
   障害物: 隕石.
*/
#pragma once
#include "Player.h"

//隕石の状態.
enum MeteorState
{
	Meteor_Normal,
	Meteor_Destroy, //破壊モード.
};

//隕石の形データ.
struct MeteorShape
{
	vector<float> lineDis; //隕石の中心からの頂点の距離.
	vector<Line>  line;    //隕石を構成する線. 
};

//隕石(単体)
class Meteor
{
private:
	MeteorState state{};       //隕石の状態.
	MeteorShape shape{};       //隕石の形データ.

	DBL_XY      pos{};	       //中心座標.
	float       ang{};	       //角度.
	DBL_XY      vel{};         //速度.
	bool        isErase{};     //消去するかどうか.

	float       destroyCntr{}; //破壊量の度合.

public:
	//get.
	DBL_XY      GetPos()     const { return pos; }
	bool        GetIsErase() const { return isErase; }
	MeteorState GetState()   const { return state; }

	//その他.
	void Init();
	void Reset();
	void Update();
	void Draw();

	void Spawn();					//隕石出現. 
	void Destroy();					//隕石破壊.
	bool IsHitMeteor(Circle) const;	//隕石の当たり判定.

	void UpdateMeteoLine();			//隕石を構成する線の更新.
};