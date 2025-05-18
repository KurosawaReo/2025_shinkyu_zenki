/*
   - Obstacle.h -
   障害物管理.
*/
#pragma once

class Obstacle
{
private:
	Line  line{};
	float ang;  //角度.
	float len;  //長さ.

	Player* player{};

public:
	//コンストラクタ.
	Obstacle(DBL_XY _stPos, float _ang, float _len, UINT _clr) {
		line.stPos = _stPos;
		ang        = _ang;
		len        = _len;
		line.clr   = _clr;
	}

	void Init(Player*);
	void Update();
	void Draw();
};