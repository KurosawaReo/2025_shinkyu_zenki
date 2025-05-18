/*
   - Player.h -
   プレイヤー管理.
*/
#pragma once

//extern POINT Get(int x, int y);//X地点とY地点からPOINT型を一時的に取得.
//extern BOOL  CollPointToPoint(POINT a, POINT b);//点と点があったっているか.
//extern RECT  GetRect(int left, int top, int right, int bottom);
//extern int   PlayerX, PlayerY, PlayerGraph;

class Player
{
private:
	int    graph;  //画像データ.
	BOOL   active; //有効か.

	Circle hit;    //プレイヤーの当たり判定円.

public:
	Player(DBL_XY _pos, BOOL _active) {
		graph  = {};
		active = _active;
		hit    = { _pos, PLAYER_HIT_R, 0x000000 };
	}

	void Init();
	void Update();
	void Draw();
	void PlayerMove(); //プレイヤー移動.

	//set.
	void    SetActive(BOOL _active) { active = _active; }
	//get. 
	DBL_XY  GetPos()   { return hit.pos; }
	BOOL    GetActive(){ return active; }
	Circle* GetHit()   { return &hit; }
};