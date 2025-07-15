
/*
   - Player.cpp -
   �v���C���[�Ǘ�.
*/
#include "GameManager.h"
#include "Obstacle4main.h"

#include "Player.h"

//������(���̂ݍs��)
void Player::Init(GameData* _data)
{
	p_data = _data;
}
//���Z�b�g(����ł��s��)
void Player::Reset(DBL_XY _pos, BOOL _active) 
{
	hit       = {_pos, PLAYER_HIT_R, {} };
	active    = _active;
	isReflect = false;
}
//�X�V.
void Player::Update()
{
	InputST* input = InputST::GetPtr();

	//�f�o�b�O���[�h�؂�ւ�.
	if (input->IsPushKeyTime(KEY_M) == 1) {
		isDebug = !isDebug;
	}

	//�L���Ȃ�.
	if (active) {
		UpdateAfterImage();
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
		DrawAfterImage();
		//�l�p�`.
		Box box1 = { hit.pos, { PLAYER_SIZE,   PLAYER_SIZE   }, 0xFFFFFF };
		Box box2 = { hit.pos, { PLAYER_SIZE-2, PLAYER_SIZE-2 }, 0xFFFFFF };

		//���˃��[�h���̐F.
		if (IsReflectionMode())
		{
			box1.clr = box2.clr = COLOR_PLY_REFLECT;
		}
		//�f�o�b�O���[�h��.
		if (isDebug) {
			box1.clr = box2.clr = COLOR_PLY_DEBUG;
		}

		DrawBoxST(&box1, TRUE, FALSE);
		DrawBoxST(&box2, TRUE, FALSE);
	}
}

//�c���X�V.
void Player::UpdateAfterImage()
{
	afterCntr -= (p_data->isSlow) ? SLOW_MODE_SPEED : 1;

	//�c�����c���^�C�~���O�ɂȂ�����(��{�͖��t���[��)
	if (afterCntr <= 0) {
		afterCntr = 1;

		//�c���f�[�^�����ɂ��炷.
		for (int i = PLAYER_AFT_IMG_NUM-1; i > 0; i--)
		{
			afterPos[i] = afterPos[i - 1];
		}
		afterPos[0] = hit.pos; //�v���C���[���W��1�t���[���ڂɋL�^.
	}
}

//�c���`��.
void Player::DrawAfterImage()
{
	//�`�惂�[�h�ύX.
	SetDrawBlendModeST(MODE_ADD, 255);

	//�c������.
	for (int i = PLAYER_AFT_IMG_NUM - 1; i >= 0; i -= 1)
	{
		int  alpha  = 105 - 105*i/PLAYER_AFT_IMG_NUM;
		int  alpha2 =  50 -  50*i/PLAYER_AFT_IMG_NUM;
		UINT color  = GetColor(alpha, alpha, alpha);

		if (IsReflectionMode())
		{
			color = GetColor(alpha2*255/50, alpha2/2, alpha2*255/50);
		}
		else
		{
			color = GetColor(alpha, alpha, alpha);
		}

		Box box3 = { afterPos[i], {PLAYER_SIZE, PLAYER_SIZE}, color };
		DrawBoxST(&box3, TRUE, FALSE);
	}

	//�`�惂�[�h���Z�b�g.
	ResetDrawBlendMode();
}

//�ړ�����(�΂ߑΉ�)
void Player::PlayerMove()
{
	InputST* input = InputST::GetPtr();

	//�ړ�����.
	if (p_data->isSlow) {
		input->InputKey4Dir(&hit.pos, PLAYER_MOVE_SPEED * SLOW_MODE_SPEED);
		input->InputPad4Dir(&hit.pos, PLAYER_MOVE_SPEED * SLOW_MODE_SPEED); //�R���g���[���ړ�(��)
	}
	else {
		input->InputKey4Dir(&hit.pos, PLAYER_MOVE_SPEED);
		input->InputPad4Dir(&hit.pos, PLAYER_MOVE_SPEED); //�R���g���[���ړ�(��)
	}
	//�ړ����E.
	FixPosInArea(&hit.pos, { PLAYER_SIZE, PLAYER_SIZE }, 0, 0, WINDOW_WID, WINDOW_HEI);
}

//���˃��[�h���ǂ���.
BOOL Player::IsReflectionMode() const
{
	return isReflect;
}
//���˃��[�h�ݒ�.
void Player::SetReflectionMode(BOOL tf)
{
	isReflect = tf;
}

//���S����.
void Player::PlayerDeath() {

	//�f�o�b�O���[�h���͖��G.
	if (isDebug) { return; }

	active = FALSE;
	//GamaManager�̊֐����s(include��������Ύg����)
	GameManager::GetPtr()->GameEnd(); //�Q�[���I��.
}