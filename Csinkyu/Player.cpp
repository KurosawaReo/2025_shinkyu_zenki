/*
   - Player.cpp -
   �v���C���[�Ǘ�.
*/
#include "GameManager.h"
#include "Obstacle4main.h"

#include "Player.h"

//������(���̂ݍs��)
void Player::Init(GameData* _data, EffectManager* _effectMng)
{
	p_data = _data;
	p_effectMng = _effectMng;

	isDebug = FALSE;  // �f�o�b�O�t���O�̏�������ǉ�
}
//���Z�b�g(����ł��s��)
void Player::Reset(DBL_XY _pos, BOOL _active)
{
	hit = { _pos, PLAYER_HIT_R, {} };
	active = _active;
	isReflect = false;
	afterCntr = 1;  // afterCntr�̏�������ǉ�

	//���W�z��̃��Z�b�g.
	for (int i = 0; i < _countof(afterPos); i++) {
		afterPos[i] = _pos;
	}
	// ���˃G�t�F�N�g��������ǉ�
	reflectEffectIndex = 0;
	for (int i = 0; i < MAX_REFLECT_EFFECTS; i++) {
		reflectEffects[i].active = FALSE;
		reflectEffects[i].timer = 0;
		reflectEffects[i].alpha = 0.0f;
		reflectEffects[i].scale = 1.0f;
		reflectEffects[i].pos = _pos;
	}
}
//�X�V.
void Player::Update()
{
	InputST* input = InputST::GetPtr();

	//�f�o�b�O���[�h�؂�ւ�.
	if (input->IsPushKeyTime(KEY_M) == 1) {
		isDebug = !isDebug;
	}

	//�e�X�g�p�FE�L�[�Ŕ��˃G�t�F�N�g�𐶐�
	if (input->IsPushKeyTime(KEY_E) == 1) {
		CreateReflectEffect(hit.pos);
	}

	//�L���Ȃ�.
	if (active) {
		UpdateAfterImage();
		UpdateReflectEffects();
		PlayerMove();
	}
}
//�`��.
void Player::Draw()
{
	//�f�o�b�O�\��.
	if (isDebug) {
		DrawString(0, 430, _T("[Debug] ���G���[�h"), 0xFFFFFF);

		// �G�t�F�N�g�̃f�o�b�O���\��
		for (int i = 0; i < MAX_REFLECT_EFFECTS; i++) {
			if (reflectEffects[i].active) {
				TCHAR debugStr[128];
				_stprintf_s(debugStr, _T("Effect[%d]: timer=%d, alpha=%.1f, scale=%.1f"),
					i, reflectEffects[i].timer, reflectEffects[i].alpha, reflectEffects[i].scale);
				DrawString(0, 450 + i * 20, debugStr, 0xFFFFFF);
			}
		}
	}

	//�L���Ȃ�.
	if (active) {
		DrawAfterImage();
		DrawReflectEffects();  // �G�t�F�N�g���ɕ`��

		//�l�p�`.
		Box box1 = { hit.pos, { PLAYER_SIZE,   PLAYER_SIZE   }, 0xFFFFFF };
		Box box2 = { hit.pos, { PLAYER_SIZE - 2, PLAYER_SIZE - 2 }, 0xFFFFFF };

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
		for (int i = PLAYER_AFT_IMG_NUM - 1; i > 0; i--)
		{
			afterPos[i] = afterPos[i - 1];
		}
		afterPos[0] = hit.pos; //�v���C���[���W��1�t���[���ڂɋL�^.
	}
}

//�c���`��.
void Player::DrawAfterImage()
{
	//�c������.
	for (int i = 0; i < PLAYER_AFT_IMG_NUM; i++)
	{
		//�����x�̌v�Z.
		float alpha = (float)i/PLAYER_AFT_IMG_NUM;
		//�����x���f.
		SetDrawBlendModeST(MODE_ADD, 255*(1-alpha));

		Box box = { afterPos[i], {PLAYER_SIZE, PLAYER_SIZE}, {} };
		//���˃J���[.
		if (IsReflectionMode())
		{
			box.clr = COLOR_PLY_AFT_REF;
		}
		//�ʏ�J���[.
		else
		{
			box.clr = COLOR_PLY_AFT_NOR;
		}

		DrawBoxST(&box, TRUE, FALSE);
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
		input->InputKey4Dir (&hit.pos, PLAYER_MOVE_SPEED * SLOW_MODE_SPEED);
		input->InputPadStick(&hit.pos, PLAYER_MOVE_SPEED * SLOW_MODE_SPEED);
	}
	else {
		input->InputKey4Dir (&hit.pos, PLAYER_MOVE_SPEED);
		input->InputPadStick(&hit.pos, PLAYER_MOVE_SPEED);
	}
	//�ړ����E.
	FixPosInArea(&hit.pos, { PLAYER_SIZE, PLAYER_SIZE }, 0, 0, WINDOW_WID, WINDOW_HEI);
}

// ���˃G�t�F�N�g����
void Player::CreateReflectEffect(DBL_XY pos)
{
	ReflectEffect* effect = &reflectEffects[reflectEffectIndex];

	effect->pos = pos;
	effect->scale = 1.0f;
	effect->alpha = 255.0f;
	effect->timer = 30;  // 30�t���[���\��
	effect->active = TRUE;

	// ���̃C���f�b�N�X�Ɉړ��i�z�j
	reflectEffectIndex = (reflectEffectIndex + 1) % MAX_REFLECT_EFFECTS;
}

// ���˃G�t�F�N�g�X�V
void Player::UpdateReflectEffects()
{
	for (int i = 0; i < MAX_REFLECT_EFFECTS; i++) {
		if (reflectEffects[i].active) {
			reflectEffects[i].timer--;
			reflectEffects[i].scale += 0.1f;      // �g�呬�x�������x��
			reflectEffects[i].alpha -= 6.0f;     // �t�F�[�h�A�E�g���x�������x��

			// �^�C�}�[��0�ɂȂ����������x��0�ȉ��ɂȂ������A�N�e�B�u
			if (reflectEffects[i].timer <= 0 || reflectEffects[i].alpha <= 0) {
				reflectEffects[i].active = FALSE;
			}
		}
	}
}

// ���˃G�t�F�N�g�`��
void Player::DrawReflectEffects()
{
	for (int i = 0; i < MAX_REFLECT_EFFECTS; i++) {
		if (reflectEffects[i].active) {
			ReflectEffect* effect = &reflectEffects[i];

			// �_�Ō��ʂ̌v�Z�i2�t���[�����Ƃɓ_�Łj
			BOOL isFlashOn = ((effect->timer / 2) % 2) == 0;
			if (!isFlashOn) continue;  // �_�ł�OFF�t���[���Ȃ�`�悵�Ȃ�

			// �G�t�F�N�g�̃T�C�Y�v�Z
			int baseSize = (int)(PLAYER_SIZE * effect->scale);
			int alpha = (int)max(0, min(255, effect->alpha));

			// �A���t�@��0�ȉ��Ȃ�`�悵�Ȃ�
			if (alpha <= 0) continue;

			// �_�łɂ��P�x�ω��i���߂̓_�Łj
			float flashIntensity = (effect->timer % 4 < 2) ? 1.5f : 0.8f;
			alpha = (int)(alpha * flashIntensity);
			alpha = min(255, max(0, alpha));

			// �s���N�F�̐ݒ�i��薾�邭�A�_�łŕω��j
			UINT color = GetColor(
				min(255, (int)(alpha * flashIntensity)),
				alpha * 80 / 255,
				min(255, alpha * 150 / 255)
			);

			// �A���t�@�u�����h���[�h�ݒ�i�G�t�F�N�g���Ƃɐݒ�j
			SetDrawBlendModeST(MODE_ALPHA, alpha);

			// �l�p���g���`��
			for (int wave = 0; wave < 3; wave++) {
				int waveSize = baseSize + wave * 8; // �e�g��̃T�C�Y
				int waveAlpha = alpha - wave * 50;  // �O���قǔ���

				if (waveAlpha > 0) {
					// ��薾�邢�s���N�F�i�_�Ō��ʕt���j
					UINT waveColor = GetColor(
						min(255, (int)(waveAlpha * 2 * flashIntensity)),
						waveAlpha * 80 / 255,
						min(255, (int)(waveAlpha * 150 / 255))
					);

					// �l�p���g���Ŕg���`��i�������j
					Box waveBox = {
						effect->pos,
						{ (double)waveSize, (double)waveSize },
						waveColor
					};

					// �g���𑾂����邽�ߕ�����`��
					for (int thickness = 0; thickness < 2; thickness++) {
						Box thickBox = {
							{ effect->pos.x - thickness, effect->pos.y - thickness },
							{ (double)(waveSize + thickness * 2), (double)(waveSize + thickness * 2) },
							waveColor
						};
						DrawBoxST(&thickBox, TRUE, FALSE);
					}
				}
			}

			// �����̎l�p�����_�i�_�łŐF�Ƒ傫�����ω��j
			int centerSize = (int)(12 * flashIntensity);
			UINT centerColor = GetColor(
				min(255, (int)(255 * flashIntensity)),
				min(255, (int)(150 * flashIntensity)),
				min(255, (int)(255 * flashIntensity))
			);

			Box centerBox = {
				effect->pos,
				{ (double)centerSize, (double)centerSize },
				centerColor
			};
			DrawBoxST(&centerBox, TRUE, FALSE);

			// �`�惂�[�h���Z�b�g
			ResetDrawBlendMode();
		}
	}
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

	//�T�E���h.
	SoundST* sound = SoundST::GetPtr();
	sound->Play(_T("PlayerDeath"), FALSE, 80);
	//�G�t�F�N�g.
	EffectData data{};
	data.type = Effect_PlayerDeath;
	data.pos  = hit.pos;
	p_effectMng->SpawnEffect(&data);
	//GamaManager�̊֐����s(include��������Ύg����)
	GameManager::GetPtr()->GameEnd(); //�Q�[���I��.
	
	active = FALSE;
}