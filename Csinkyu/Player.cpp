/*
   - Player.cpp -
   �v���C���[�Ǘ�.
*/
#include "Player.h"

//������(���̂ݍs��)
void Player::Init(GameData* _data)
{
	p_data = _data;
}
//���Z�b�g(����ł��s��)
void Player::Reset(DBL_XY _pos, BOOL _active) {
	hit    = {_pos, PLAYER_HIT_R, 0x000000};
	active = _active;
}
//�X�V.
void Player::Update()
{
	//�f�o�b�O���[�h�؂�ւ�.
	if (IsPushKeyTime(KEY_INPUT_M) == 1) {
		isDebug = !isDebug;
	}
	//�L���Ȃ�.
	if (active) {
		PlayerMove();
	}
}
//�`��.
void Player::Draw()
{
	//�f�o�b�O�\��.
	if (isDebug) {
		DrawString(0, 430, _T("[Debug] ���G���[�h"), 0xFFFFFF);
	}
	//�L���Ȃ�.
	if (active) {
		// �l�p�`��`��i�v���C���[�̈ʒu�Ɂj
		int x  = _int(hit.pos.x - PLAYER_SIZE/2);
		int y  = _int(hit.pos.y - PLAYER_SIZE/2);
		int dx = _int(hit.pos.x + PLAYER_SIZE/2);
		int dy = _int(hit.pos.y + PLAYER_SIZE/2);

		unsigned int Cr;
		//�f�o�b�O���[�h��.
		if (isDebug) {
			Cr = GetColor(255, 150, 150); //�ԐF.
		}
		else {
			Cr = GetColor(255, 255, 255); //���F.
		}

		DrawBox(x, y, dx, dy, Cr, TRUE);
	}
}

//�ړ�����(�΂ߑΉ�)
void Player::PlayerMove()
{
	//�ړ�����.
	if (p_data->isSlow) {
		InputKey4Dir(&hit.pos, PLAYER_MOVE_SPEED/3);
	}
	else {
		InputKey4Dir(&hit.pos, PLAYER_MOVE_SPEED);
	}
	//�ړ����E.
	LimMovePos(&hit.pos, { PLAYER_SIZE, PLAYER_SIZE }, 0, 0, WINDOW_WID, WINDOW_HEI);
}

//���S����.
void Player::PlayerDeath() {

	//�f�o�b�O���[�h���͖��G.
	if (isDebug) { return; }

	active = FALSE;
	p_data->scene = SCENE_END; //�Q�[���I����.
}