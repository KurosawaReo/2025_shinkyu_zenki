/*
   - Obstacle.h -
   障害物管理.
*/
#pragma once

class Obstacle
{
private:
	INT_XY stPos{}; //start  pos: 始点
	INT_XY mdPos{}; //middle pos: 中点
	INT_XY edPos{}; //end    pos: 終点
	float  ang;     //角度.
	float  len;     //長さ.

	Player* player{};

public:
	//コンストラクタ.
	Obstacle(INT_XY _stPos, float _ang, float _len) {
		stPos = _stPos;
		ang   = _ang;
		len   = _len;
	}

	void Init(Player*);
	void Update();
	void Draw();
};