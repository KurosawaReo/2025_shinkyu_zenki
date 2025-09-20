/*
   - Obst_NormalLaser.cpp -

   ��Q��: ���[�U�[���ˑ�(�p����)
   �̂ɂ���ĈႤ���������邽�߁Aoverride���g�p.
*/
#include "GameManager.h"
#include "Obst_NormalLaser.h"

//obstacle4main��Move�֐���obstacle4�p�ɏ㏑��.
void NormalLaser_1::Move()
{
	// �ړ����x
	float moveSpeed = Hm * p_data->speedRate;

	// ��`�o�H�̈ړ�(�E���)
	switch (moveDir)
	{
	case MOVE_LEFT:
		Hx -= moveSpeed;
		if (Hx < 0 + LASER_NOR_OUTER_MARGIN) {
			Hx = 0 + LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_UP;
		}
		break;
	case MOVE_RIGHT:
		Hx += moveSpeed;
		if (Hx > WINDOW_WID - LASER_NOR_OUTER_MARGIN) {
			Hx = WINDOW_WID - LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_DOWN;
		}
		break;
	case MOVE_DOWN:
		Hy += moveSpeed;
		if (Hy > WINDOW_HEI - LASER_NOR_OUTER_MARGIN) {
			Hy = WINDOW_HEI - LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_LEFT;
		}
		break;
	case MOVE_UP:
		Hy -= moveSpeed;
		if (Hy < 0 + LASER_NOR_OUTER_MARGIN) {
			Hy = 0 + LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_RIGHT;
		}
		break;
	}
}

//obstacle4main��Move�֐���obstacle5�p�ɏ㏑��.
void NormalLaser_2::Move()
{
	// �ړ����x
	float moveSpeed = Hm * p_data->speedRate;

	// ��`�o�H�̈ړ�(�����)
	switch (moveDir)
	{
	case MOVE_LEFT:
		Hx -= moveSpeed;
		if (Hx < 0 + LASER_NOR_OUTER_MARGIN) {
			Hx = 0 + LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_DOWN;
		}
		break;
	case MOVE_RIGHT:
		Hx += moveSpeed;
		if (Hx > WINDOW_WID - LASER_NOR_OUTER_MARGIN) {
			Hx = WINDOW_WID - LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_UP;
		}
		break;
	case MOVE_DOWN:
		Hy += moveSpeed;
		if (Hy > WINDOW_HEI - LASER_NOR_OUTER_MARGIN) {
			Hy = WINDOW_HEI - LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_RIGHT;
		}
		break;
	case MOVE_UP:
		Hy -= moveSpeed;
		if (Hy < 0 + LASER_NOR_OUTER_MARGIN) {
			Hy = 0 + LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_LEFT;
		}
		break;
	}
}

//obstacle4main��Move�֐���obstacle5�p�ɏ㏑��.
void NormalLaser_3::Move()
{
	// �ړ����x
	float moveSpeed = Hm * p_data->speedRate;

	// ��`�o�H�̈ړ�(�����)
	switch (moveDir)
	{
	case MOVE_LEFT:
		Hx -= moveSpeed;
		if (Hx < 0 + LASER_NOR_OUTER_MARGIN) {
			Hx = 0 + LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_DOWN;
		}
		break;
	case MOVE_RIGHT:
		Hx += moveSpeed;
		if (Hx > WINDOW_WID - LASER_NOR_OUTER_MARGIN) {
			Hx = WINDOW_WID - LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_UP;
		}
		break;
	case MOVE_DOWN:
		Hy += moveSpeed;
		if (Hy > WINDOW_HEI - LASER_NOR_OUTER_MARGIN) {
			Hy = WINDOW_HEI - LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_RIGHT;
		}
		break;
	case MOVE_UP:
		Hy -= moveSpeed;
		if (Hy < 0 + LASER_NOR_OUTER_MARGIN) {
			Hy = 0 + LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_LEFT;
		}
		break;
	}
}

//obstacle4main��Move�֐���obstacle4�p�ɏ㏑��.
void NormalLaser_4::Move()
{
	// �ړ����x
	float moveSpeed = Hm * p_data->speedRate;

	// ��`�o�H�̈ړ�(�E���)
	switch (moveDir)
	{
	case MOVE_LEFT:
		Hx -= moveSpeed;
		if (Hx < 0 + LASER_NOR_OUTER_MARGIN) {
			Hx = 0 + LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_UP;
		}
		break;
	case MOVE_RIGHT:
		Hx += moveSpeed;
		if (Hx > WINDOW_WID - LASER_NOR_OUTER_MARGIN) {
			Hx = WINDOW_WID - LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_DOWN;
		}
		break;
	case MOVE_DOWN:
		Hy += moveSpeed;
		if (Hy > WINDOW_HEI - LASER_NOR_OUTER_MARGIN) {
			Hy = WINDOW_HEI - LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_LEFT;
		}
		break;
	case MOVE_UP:
		Hy -= moveSpeed;
		if (Hy < 0 + LASER_NOR_OUTER_MARGIN) {
			Hy = 0 + LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_RIGHT;
		}
		break;
	}
}
