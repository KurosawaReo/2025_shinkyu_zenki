/*
   - Obstacle.h -
   ��Q���Ǘ�.
*/
#pragma once

class Obstacle
{
private:
	Line  line{};
	float ang;  //�p�x.
	float len;  //����.

	Player* player{};

public:
	//�R���X�g���N�^.
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