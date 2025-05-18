/*
   - Player.cpp -
   �v���C���[�Ǘ�.
*/
#include "Player.h"

//������.
void Player::Init()
{

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
		// �l�p�`��`��i�v���C���[�̈ʒu�Ɂj
		int x  = _int(hit.pos.x - PLAYER_SIZE/2);
		int y  = _int(hit.pos.y - PLAYER_SIZE/2);
		int dx = _int(hit.pos.x + PLAYER_SIZE/2);
		int dy = _int(hit.pos.y + PLAYER_SIZE/2);

		unsigned int Cr;
		Cr = GetColor(255, 255, 255); // ���F

		DrawBox(x, y, dx, dy, Cr, TRUE);
	}
}

//�ړ�����(�΂ߑΉ�)
void Player::PlayerMove()
{
	//�ړ�����.
	InputKey4Dir(&hit.pos, PLAYER_MOVE_SPEED);
	//�ړ����E.
	LimMovePos(&hit.pos, { PLAYER_SIZE, PLAYER_SIZE }, 0, 0, WINDOW_WID, WINDOW_HEI);
}