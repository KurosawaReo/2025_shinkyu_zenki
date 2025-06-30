/*
   - Meteo.h -
   降ってくる隕石.
*/
#pragma once

/*
//隕石を構成する線.
struct MeteoLine : public Line
{
	BOOL active; //有効かどうか.
};
*/

//隕石(単体)
class Meteo
{
private:
	DBL_XY pos{};				   //中心座標.
	float  ang{};				   //角度.
	DBL_XY vel{};                  //速度.
	int    shapeCnt;		       //隕石を何角形にするか.
	Line   line[METEO_LINE_MAX]{}; //隕石を構成する多角形の線.
	BOOL   active{};               //有効かどうか.

	GameData* p_data;                 //ゲームデータ.

public:
	//set.
	void SetActive(BOOL _active) { 
		active = _active; 
	}
	//get.
	DBL_XY GetPos()    { return pos; }
	BOOL   GetActive() { return active; }

	//その他.
	void Init(GameData*);
	void Reset();
	void Update();
	void Draw();

	void Spawn();           //隕石出現. 
	void UpdateMeteoLine(); //隕石を構成する線の更新.
};