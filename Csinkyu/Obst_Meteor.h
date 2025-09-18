/*
   - Obst_Meteor.h -
   
   障害物: 隕石.
*/
#pragma once
#include "Player.h"

class GameData; //前方宣言.

//隕石の状態.
enum MeteorState
{
	Meteor_Normal,
	Meteor_Destroy, //破壊モード.
};

//隕石の形データ.
struct MeteorShape
{
	int   lineCnt{};					 //隕石を何角形にするか.
	float lineDis[METEOR_LINE_CNT_MAX]{}; //隕石の中心からの頂点の距離.
	Line  line   [METEOR_LINE_CNT_MAX]{}; //隕石を構成する線. 
};

//隕石(単体)
class Meteor
{
private:
	MeteorState state{};      //隕石の状態.
	MeteorShape shape{};      //隕石の形データ.

	DBL_XY     pos{};	      //中心座標.
	float      ang{};	      //角度.
	DBL_XY     vel{};         //速度.
	bool       active{};      //有効かどうか.

	float      destroyCntr{}; //破壊量の度合.

	GameData*  p_data;        //ゲームデータ.

public:
	//set.
	void SetActive(bool _active) { 
		active = _active; 
	}
	//get.
	DBL_XY      GetPos()    { return pos; }
	bool        GetActive() { return active; }
	MeteorState GetState()  { return state; }

	//その他.
	void Init();
	void Reset();
	void Update();
	void Draw();

	void Spawn();				//隕石出現. 
	void Destroy();				//隕石破壊.
	bool IsHitMeteor(Circle*);	//隕石の当たり判定.

	void UpdateMeteoLine();		//隕石を構成する線の更新.
};