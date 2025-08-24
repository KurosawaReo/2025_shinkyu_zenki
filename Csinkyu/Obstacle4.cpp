/*
   - Obstacle4.cpp -

   ���[�U�[�̌p����N���X.
   �C��(�s��)�����E�ňႤ�����ɂ��邽�߁Aoverride���g�p.
*/
#include "Player.h"    // �v���C���[�N���X�̃w�b�_�[�t�@�C��
#include "Obstacle4.h" // ���g�̃w�b�_�[�t�@�C��

//obstacle4main��Move�֐���obstacle4�p�ɏ㏑��.
void Obstacle4_1::Move()
{
	// �ړ����x
	float moveSpeed = Hm * (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);

	// ��`�o�H�̈ړ�(�E���)
	switch (moveDir)
	{
	case MOVE_LEFT:
		Hx -= moveSpeed;
		if (Hx < 0 + OBSTACLE4_OUTER_MARGIN) {
			Hx = 0 + OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_UP;
		}
		break;
	case MOVE_RIGHT:
		Hx += moveSpeed;
		if (Hx > WINDOW_WID - OBSTACLE4_OUTER_MARGIN) {
			Hx = WINDOW_WID - OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_DOWN;
		}
		break;
	case MOVE_DOWN:
		Hy += moveSpeed;
		if (Hy > WINDOW_HEI - OBSTACLE4_OUTER_MARGIN) {
			Hy = WINDOW_HEI - OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_LEFT;
		}
		break;
	case MOVE_UP:
		Hy -= moveSpeed;
		if (Hy < 0 + OBSTACLE4_OUTER_MARGIN) {
			Hy = 0 + OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_RIGHT;
		}
		break;
	}
}

//obstacle4main��Move�֐���obstacle5�p�ɏ㏑��.
void Obstacle4_2::Move()
{
	// �ړ����x
	float moveSpeed = Hm * (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);

	// ��`�o�H�̈ړ�(�����)
	switch (moveDir)
	{
	case MOVE_LEFT:
		Hx -= moveSpeed;
		if (Hx < 0 + OBSTACLE4_OUTER_MARGIN) {
			Hx = 0 + OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_DOWN;
		}
		break;
	case MOVE_RIGHT:
		Hx += moveSpeed;
		if (Hx > WINDOW_WID - OBSTACLE4_OUTER_MARGIN) {
			Hx = WINDOW_WID - OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_UP;
		}
		break;
	case MOVE_DOWN:
		Hy += moveSpeed;
		if (Hy > WINDOW_HEI - OBSTACLE4_OUTER_MARGIN) {
			Hy = WINDOW_HEI - OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_RIGHT;
		}
		break;
	case MOVE_UP:
		Hy -= moveSpeed;
		if (Hy < 0 + OBSTACLE4_OUTER_MARGIN) {
			Hy = 0 + OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_LEFT;
		}
		break;
	}
}

//obstacle4main��Move�֐���obstacle5�p�ɏ㏑��.
void Obstacle4_3::Move()
{
	// �ړ����x
	float moveSpeed = Hm * ((p_data->isSlow) ? (float)SLOW_MODE_SPEED : 1);

	// ��`�o�H�̈ړ�(�����)
	switch (moveDir)
	{
	case MOVE_LEFT:
		Hx -= moveSpeed;
		if (Hx < 0 + OBSTACLE4_OUTER_MARGIN) {
			Hx = 0 + OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_DOWN;
		}
		break;
	case MOVE_RIGHT:
		Hx += moveSpeed;
		if (Hx > WINDOW_WID - OBSTACLE4_OUTER_MARGIN) {
			Hx = WINDOW_WID - OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_UP;
		}
		break;
	case MOVE_DOWN:
		Hy += moveSpeed;
		if (Hy > WINDOW_HEI - OBSTACLE4_OUTER_MARGIN) {
			Hy = WINDOW_HEI - OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_RIGHT;
		}
		break;
	case MOVE_UP:
		Hy -= moveSpeed;
		if (Hy < 0 + OBSTACLE4_OUTER_MARGIN) {
			Hy = 0 + OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_LEFT;
		}
		break;
	}
}

//obstacle4main��Move�֐���obstacle4�p�ɏ㏑��.
void Obstacle4_4::Move()
{
	// �ړ����x
	float moveSpeed = Hm * ((p_data->isSlow) ? (float)SLOW_MODE_SPEED : 1);

	// ��`�o�H�̈ړ�(�E���)
	switch (moveDir)
	{
	case MOVE_LEFT:
		Hx -= moveSpeed;
		if (Hx < 0 + OBSTACLE4_OUTER_MARGIN) {
			Hx = 0 + OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_UP;
		}
		break;
	case MOVE_RIGHT:
		Hx += moveSpeed;
		if (Hx > WINDOW_WID - OBSTACLE4_OUTER_MARGIN) {
			Hx = WINDOW_WID - OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_DOWN;
		}
		break;
	case MOVE_DOWN:
		Hy += moveSpeed;
		if (Hy > WINDOW_HEI - OBSTACLE4_OUTER_MARGIN) {
			Hy = WINDOW_HEI - OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_LEFT;
		}
		break;
	case MOVE_UP:
		Hy -= moveSpeed;
		if (Hy < 0 + OBSTACLE4_OUTER_MARGIN) {
			Hy = 0 + OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_RIGHT;
		}
		break;
	}
}
