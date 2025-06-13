/*
   - Player.cpp -
   �v���C���[�Ǘ�.
*/
#include "GameManager.h"
#include "Player.h"
#include "Obstacle4main.h"

//������(���̂ݍs��)
void Player::Init(GameData* _data)
{
	p_data = _data;
}
//���Z�b�g(����ł��s��)
void Player::Reset(DBL_XY _pos, BOOL _active) 
{
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

	// ���˃��[�h�̏�Ԃ��R���\�[���ɏo�́i�f�o�b�O�p�j
	if (CheckHitKey(KEY_INPUT_V)) {
		printf("V�L�[������, �N�[���_�E��: %.1f\n", reflectionCooldown);
	}


	if (reflectionCooldown > 0)
	{
		reflectionCooldown -= (p_data->isSlow) ? (float)SLOW_MODE_SPEED : 1;
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

	// ���˃��[�h�\��.
	if (IsReflectionMode())
	{
		DrawString(0, 430, _T("���˃��[�h ON"), 0x00FF00);
	}

	// �N�[���_�E���\��.
	if (reflectionCooldown > 0) {
		DrawString(0, 470, _T("���˃N�[���_�E����..."), 0xFF0000);
	}


	//�L���Ȃ�.
	if (active) {
		//�l�p�`.
		Box box1 = { hit.pos, { PLAYER_SIZE,   PLAYER_SIZE   }, 0xFFFFFF };
		Box box2 = { hit.pos, { PLAYER_SIZE-2, PLAYER_SIZE-2 }, 0xA0A0A0 };

		//���˃��[�h���͐F�ɕύX.
		if (IsReflectionMode())
		{
			box1.clr = box2.clr = GetColor(255, 155, 255);//�F.
		}

		//�f�o�b�O���[�h��.
		if (isDebug) {
			box1.clr = box2.clr = GetColor(255, 150, 150); //�ԐF.
		}

		DrawBoxST(&box1, TRUE, FALSE);
		DrawBoxST(&box2, TRUE, FALSE);
	}
}

//�ړ�����(�΂ߑΉ�)
void Player::PlayerMove()
{
	//�ړ�����.
	if (p_data->isSlow) {
		InputKey4Dir(&hit.pos, PLAYER_MOVE_SPEED * SLOW_MODE_SPEED);
		InputPad4Dir(&hit.pos, PLAYER_MOVE_SPEED * SLOW_MODE_SPEED); //�R���g���[���ړ�(��)
	}
	else {
		InputKey4Dir(&hit.pos, PLAYER_MOVE_SPEED);
		InputPad4Dir(&hit.pos, PLAYER_MOVE_SPEED); //�R���g���[���ړ�(��)
	}
	//�ړ����E.
	FixPosInArea(&hit.pos, { PLAYER_SIZE, PLAYER_SIZE }, 0, 0, WINDOW_WID, WINDOW_HEI);
}

BOOL Player::IsReflectionMode()
{
	int vKeyPressed = CheckHitKey(KEY_INPUT_V);
	int cooldownOK = (reflectionCooldown <= 0);

	// �f�o�b�O�o��.
	DrawFormatString(0, 300, 0xFF0000, _T("���˃��[�h�m�F: V�L�[=%d"), vKeyPressed);
	DrawFormatString(0, 320, 0xFF0000, _T("�N�[���_�E��=%.1f"), reflectionCooldown);
	DrawFormatString(0, 340, 0xFF0000, _T("����=%d"), (vKeyPressed & cooldownOK));

	return vKeyPressed && cooldownOK;
}

void Player::UseReflection()
{
	reflectionCooldown = 60;
}
float Player::GetReflectionCooldown()
{
	return reflectionCooldown;
}


//���S����.
void Player::PlayerDeath() {

	//�f�o�b�O���[�h���͖��G.
	if (isDebug) { return; }

	active = FALSE;
	//GamaManager�̊֐����s(include��������Ύg����)
	GameManager::GetPtr()->GameEnd(); //�Q�[���I��.
}
