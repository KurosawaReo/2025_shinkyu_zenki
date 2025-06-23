/*
   - Meteo.h -
   降ってくる隕石.
*/
#pragma once

#define METEO_MAX_LINE (16) //最大16角形.

//隕石(単体)
class Meteo
{
private:
	DBL_XY pos;					 //中心座標.
	DBL_XY vel;                  //速度.
	Line   line[METEO_MAX_LINE]; //隕石を構成する多角形の線.
	BOOL   active;               //有効かどうか.

	GameData* p_data;            //ゲームデータ.

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

	void Spawn(); //隕石出現. 
};