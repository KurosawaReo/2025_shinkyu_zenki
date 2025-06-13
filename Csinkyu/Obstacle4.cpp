/*
   - Obstacle4.cpp -
   ��Q���Ǘ��N���X (���c����)
   �v���C���[��ǔ����郌�[�U�[�𔭎˂����Q��������
*/
#include "Player.h"    // �v���C���[�N���X�̃w�b�_�[�t�@�C��
#include "Obstacle4.h" // ���g�̃w�b�_�[�t�@�C��

//obstacle4main��Init�֐���obstacle4�p�ɏ㏑��.
void Obstacle4_1::Init(GameData* _data, Player* _player)
{
	data   = _data;
	player = _player;  // �v���C���[�I�u�W�F�N�g���Q�ƂƂ��ĕۑ�
}
//obstacle4main��Reset�֐���obstacle4�p�ɏ㏑��.
void Obstacle4_1::Reset(float _Hx, float _Hy, float _Hm)
{
	Hx      = _Hx;                  // �C���X���W�����l�i��ʒ����j
	Hy      = _Hy;                  // �C���Y���W�����l�i��ʏ㕔�j
	Hm      = _Hm;                  // �C��̈ړ����x
	Hsc     = OBSTACLE4_SHOT_RESET; // �C��̔��˃J�E���^�����l
	HscTm   = OBSTACLE4_SHOT_START; // �C��̔��˃^�C�~���O�����l
	moveDir = MOVE_RIGHT;           // �����������E�ɐݒ�.
	// ���[�U�[�f�[�^�̏�����
	for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
		laser[i].ValidFlag = 0;    // ���ׂẴ��[�U�[�𖳌���Ԃ�

	// ���[�U�[�̋O�Ճf�[�^�̏�����
	for (int i = 0; i < OBSTACLE4_LINE_MAX; i++)
		line[i].ValidFlag = 0;  // ���ׂĂ̋O�Ղ𖳌���Ԃ�
 
}
//obstacle4main��Move�֐���obstacle4�p�ɏ㏑��.
void Obstacle4_1::Move()
{
	// �ړ����x
	float moveSpeed = Hm * ((data->isSlow) ? (float)SLOW_MODE_SPEED : 1);

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

//obstacle4main��Init�֐���obstacle5�p�ɏ㏑��.
void Obstacle4_2::Init(GameData* _data, Player* _player)
{
	data   = _data;
	player = _player;  // �v���C���[�I�u�W�F�N�g���Q�ƂƂ��ĕۑ�
}
//obstacle4main��Reset�֐���obstacle5�p�ɏ㏑��.
void Obstacle4_2::Reset(float _Hx, float _Hy, float _Hm)
{
	Hx      = _Hx;                  // �C���X���W�����l�i��ʒ����j
	Hy      = _Hy;                  // �C���Y���W�����l�i��ʏ㕔�j
	Hm      = _Hm;                  // �C��̈ړ����x
	Hsc     = OBSTACLE4_SHOT_RESET; // �C��̔��˃J�E���^�����l
	HscTm   = OBSTACLE4_SHOT_START; // �C��̔��˃^�C�~���O�����l
	moveDir = MOVE_LEFT;            // �������������ɐݒ�.
	// ���[�U�[�f�[�^�̏�����
	for (int i = 0; i < OBSTACLE4_LASER_LIM; i++)
		laser[i].ValidFlag = 0;    // ���ׂẴ��[�U�[�𖳌���Ԃ�

	// ���[�U�[�̋O�Ճf�[�^�̏�����
	for (int i = 0; i < OBSTACLE4_LINE_MAX; i++)
		line[i].ValidFlag = 0;  // ���ׂĂ̋O�Ղ𖳌���Ԃ�
}
//obstacle4main��Move�֐���obstacle5�p�ɏ㏑��.
void Obstacle4_2::Move()
{
	// �ړ����x
	float moveSpeed = Hm * ((data->isSlow) ? (float)SLOW_MODE_SPEED : 1);

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
