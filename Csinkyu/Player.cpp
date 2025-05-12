/*
   - Player.cpp -
   �v���C���[�Ǘ�.
*/
#include "Player.h"

//������.
void Player::Init()
{
	pos    = { 100, 100 }; //�����ʒu.
	active = TRUE;
}
//�X�V.
void Player::Update()
{
	//�L���Ȃ�.
	if (active) {
		PlayerMove();
	}
}
//�`��.
void Player::Draw()
{
	//�L���Ȃ�.
	if (active) {
		unsigned int Cr;
		Cr = GetColor(255, 255, 255); // ���F

		// �l�p�`��`��i�v���C���[�̈ʒu�Ɂj
		int x  = _int(pos.x - PLAYER_SIZE/2);
		int y  = _int(pos.y - PLAYER_SIZE/2);
		int dx = _int(pos.x + PLAYER_SIZE/2);
		int dy = _int(pos.y + PLAYER_SIZE/2);
		DrawBox(x, y, dx, dy, Cr, TRUE);
	}
}

//�ړ�����(�΂ߑΉ�)
void Player::PlayerMove()
{	
	INT_XY pow{};  //�ړ���.
	DBL_XY move{}; //���߂��ړ���.

	//�L�[���͂ɉ����Ĉړ��͂�^����.
	if (CheckHitKey(KEY_INPUT_UP))
	{
		pow.y += -1;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		pow.y += +1;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		pow.x += -1;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		pow.x += +1;
	}

	//�ړ��͂������.
	if (pow.x != 0 || pow.y != 0) {

		//�p�x�ɂ���.
		double theta = atan2(pow.y, pow.x);
		//�ړ��ʂ����߂�.
		move = { cos(theta), sin(theta) };
		//�ق�0�̒l�Ȃ�0�ƌ��Ȃ�(�v�Z��덷�����邽��)
		if (fabs(move.x) < 0.0001) { move.x = 0; }
		if (fabs(move.y) < 0.0001) { move.y = 0; }
	}

	//���W�ړ�.
	pos.x += move.x * PLAYER_MOVE_SPEED;
	pos.y += move.y * PLAYER_MOVE_SPEED;
	//�ړ����E.
	if (pos.x < 0 + PLAYER_SIZE/2) pos.x = PLAYER_SIZE/2;
	if (pos.y < 0 + PLAYER_SIZE/2) pos.y = PLAYER_SIZE/2;
	if (pos.x > WINDOW_WID - PLAYER_SIZE/2) pos.x = WINDOW_WID - PLAYER_SIZE/2;
	if (pos.y > WINDOW_HEI - PLAYER_SIZE/2) pos.y = WINDOW_HEI - PLAYER_SIZE/2;
}