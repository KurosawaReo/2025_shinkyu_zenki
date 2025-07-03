/*
   - Meteo.h -
   降ってくる隕石.
*/
#pragma once
#include "Player.h"

//隕石の形データ.
struct MeteoShape
{
	int   lineCnt{};					 //隕石を何角形にするか.
	float lineDis[METEO_LINE_CNT_MAX]{}; //隕石の中心からの頂点の距離.
	Line  line   [METEO_LINE_CNT_MAX]{}; //隕石を構成する線. 
};

//隕石(単体)
class Meteo
{
private:
	DBL_XY     pos{};	 //中心座標.
	float      ang{};	 //角度.
	DBL_XY     vel{};    //速度.
	BOOL       active{}; //有効かどうか.

	MeteoShape shape{};  //隕石の形データ.

	GameData*  p_data;   //ゲームデータ.
	Player*    p_player; //プレイヤーデータ.

public:
	//set.
	void SetActive(BOOL _active) { 
		active = _active; 
	}
	//get.
	DBL_XY GetPos()    { return pos; }
	BOOL   GetActive() { return active; }

	//その他.
	void Init(GameData*, Player*);
	void Reset();
	void Update();
	void Draw();

	void Spawn();				//隕石出現. 
	void Destroy();				//隕石破壊.
	BOOL IsHitMeteo(Circle*);	//隕石の当たり判定.

	void UpdateMeteoLine();		//隕石を構成する線の更新.
};