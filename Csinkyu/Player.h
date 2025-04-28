/*
   - Player.h -
   プレイヤー管理.
*/
#pragma once

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