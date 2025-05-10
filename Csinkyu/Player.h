/*
   - Player.h -
   プレイヤー管理.
*/
#pragma once

extern POINT Get(int x, int y);//X地点とY地点からPOINT型を一時的に取得.
extern BOOL CollPointToPoint(POINT a, POINT b);//点と点があったっているか.
extern RECT GetRect(int left, int top, int right, int bottom);
extern int PlayerX, PlayerY, PlayerGraph;
class Player
{
public:
	void Init();
	void Update();
	void Draw();

	// 追加：プレイヤーの位置を取得するメソッド
	int GetX() { return PlayerX; }
	int GetY() { return PlayerY; }
};