/*
   - Obstacle.h -
   ��Q���Ǘ�.
*/
#pragma once

class Obstacle
{
private:
	INT_XY stPos{}; //start  pos: �n�_
	INT_XY mdPos{}; //middle pos: ���_
	INT_XY edPos{}; //end    pos: �I�_
	float  ang;     //�p�x.
	float  len;     //����.

	Player* player{};

public:
	//�R���X�g���N�^.
	Obstacle(INT_XY _stPos, float _ang, float _len) {
		stPos = _stPos;
		ang   = _ang;
		len   = _len;
	}

	void Init(Player*);
	void Update();
	void Draw();
};