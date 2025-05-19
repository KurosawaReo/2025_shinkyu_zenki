/*
   - Obstacle.h -
   ��Q���Ǘ�.
*/
#pragma once

class Obstacle
{
private:
	Line  line{};
	float ang{}; //�p�x.
	float len;   //����.
	float speed; //����.

	GameData* data  {};
	Player*   player{};

public:
	//�R���X�g���N�^.
	Obstacle(float _len, float _speed, UINT _clr) {
		len        = _len;
		speed      = _speed;
		line.clr   = _clr;
	}

	void Init  (GameData*, Player*);
	void Reset (DBL_XY _pos, float _ang);
	void Update();
	void Draw  ();
};