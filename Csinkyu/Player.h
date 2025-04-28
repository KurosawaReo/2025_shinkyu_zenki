/*
   - Player.h -
   プレイヤー管理.
*/
#pragma once

extern POINT Get(int x, int y);//X地点とY地点からPOINT型を一時的に取得.
extern BOOL CollPointToPoint(POINT a, POINT b);//点と点があったっているか.
extern RECT GetRect(int left, int top, int right, int bottom);


class Player {

private:
	DBL_XY pos;   //位置.
	int    graph; //画像データ.

public:
	void Init();
	void Update();
	void Draw();

	void PlayerMove(); //プレイヤー移動.
};