/*
   - Player.h -
   �v���C���[�Ǘ�.
*/
#pragma once

class Player {

private:
	DBL_XY pos;   //�ʒu.
	int    graph; //�摜�f�[�^.

public:
	void Init();
	void Update();
	void Draw();

	void PlayerMove(); //�v���C���[�ړ�.
};