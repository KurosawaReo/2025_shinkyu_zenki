/*
   - Player.cpp -
   �v���C���[�Ǘ�.
*/
#include "GameManager.h"
#include "LaserManager.h"
#include "Obst_NormalLaserMain.h"
#include "Stage_Tutorial.h"

#include "Player.h"

using namespace Calc; //�v�Z�@�\���g�p.

//������(���̂ݍs��)
void Player::Init()
{
	p_data      = &GameData::GetInst();
	p_effectMng = &EffectManager::GetInst();
	p_input     = &InputMng::GetInst();

	isDebug = false;

	//�摜�ǂݍ���.
	imgPlayer[0].     LoadFile(_T("Resources/Images/player_normal.png"));
	imgPlayer[1].     LoadFile(_T("Resources/Images/player_reflect.png"));
	imgPlayerLight[0].LoadFile(_T("Resources/Images/light_color_2.png"));
	imgPlayerLight[1].LoadFile(_T("Resources/Images/light_color_3.png"));
}
//���Z�b�g(����ł��s��)
void Player::Reset(DBL_XY _pos, bool _active)
{
	hit        = { _pos, PLAYER_SIZE, {} };
	active     = _active;
	mode       = Player_Normal;
	afterCntr  = 1;
	isMoveAble = true;

	// �_�b�V���֘A�̏�����.
	isDashing    = false;
	dashTimer    = 0;
	dashCooldown = 0;

	//�c���z��̃��Z�b�g.
	for (int i = 0; i < _countof(after); i++) {
		after[i].pos      = _pos;
		after[i].isActive = false;
	}
	//���˃G�t�F�N�g���Z�b�g.
	dashEffectIndex = 0;
	for (int i = 0; i < PLAYER_DASH_EFFECT_MAX; i++) {
		dashEffects[i].active = false;
		dashEffects[i].timer = 0;
		dashEffects[i].alpha = 0.0f;
		dashEffects[i].scale = 1.0f;
		dashEffects[i].pos = _pos;
	}
}
//�X�V.
void Player::Update()
{
#if defined _DEBUG //Release�ł͓���Ȃ�.
	//���G���[�h.
	if (p_input->IsPushKeyTime(KeyID::M) == 1) {
		isDebug = !isDebug;
	}
#endif

	//�L���Ȃ�.
	if (active) {
		imgRot += 1.5 * p_data->speedRate; //�摜��].

		UpdateAfterImage();
		UpdateDash();
		PlayerMove();
		
		//���˃��[�h��.
		if (p_data->isReflectMode) {
			//�G�̃��[�U�[���߂��ɂ����.
			if (LaserManager::GetInst().IsExistEnemyLaser(hit.pos, SLOW_MODE_DIS_LEN)) {
				p_data->slowBufCntr = SLOW_MODE_BUF_F;
			}
		}
	}
}
//�`��.
void Player::Draw()
{
#if defined _DEBUG //Release�ł͓���Ȃ�.
	//�f�o�b�O�\��.
	if (isDebug) {
		DrawStr str(_T("[Debug] ���G���[�h"), {WINDOW_WID/2, WINDOW_HEI/2+300}, COLOR_PLY_DEBUG);
		str.Draw(Anchor::Mid, p_data->font1);
	}
	// �G�t�F�N�g�̃f�o�b�O���\��
	for (int i = 0; i < PLAYER_DASH_EFFECT_MAX; i++) {
		if (dashEffects[i].active) {
			TCHAR debugStr[128];
			_stprintf_s(debugStr, _T("Effect[%d]: timer=%d, alpha=%.1f, scale=%.1f"),
				i, dashEffects[i].timer, dashEffects[i].alpha, dashEffects[i].scale);
			DrawString(0, 450 + i * 20, debugStr, 0xFFFFFF);
		}
	}
	// �_�b�V���̃f�o�b�O�\��
	if (isDashing || dashCooldown > 0) {
		TCHAR dashStr[128];
		_stprintf_s(dashStr, _T("Dash: timer=%f, cooldown=%f"), dashTimer, dashCooldown);
		DrawString(0, 430, dashStr, isDashing ? 0x00FF00 : 0xFFFF00);
	}
#endif

	//�L���Ȃ�.
	if (active) {
		DrawAfterImage();

		const float size = 0.17;

		//�v���C���[�`��.
		if (mode == Player_Reflect ||
			mode == Player_SuperReflect
		){
			//�_�b�V�����o.
			if (isDashing) {
				imgPlayerLight[0].DrawExtend(hit.pos, {0.05, 0.05}, Anchor::Mid, true, true);
			}
			//���˃��[�h�̉摜.
			imgPlayer[1].DrawRota(hit.pos, size, imgRot, {0, 0}, Anchor::Mid, true, true);
		}
		else {
			//�_�b�V�����o.
			if (isDashing) {
				imgPlayerLight[1].DrawExtend(hit.pos, {0.05, 0.05}, Anchor::Mid, true, true);
			}
			//�ʏ탂�[�h�̉摜.
			imgPlayer[0].DrawRota(hit.pos, size, imgRot, {0, 0}, Anchor::Mid, true, true);
		}

		//�`���[�g���A���p.
		if (p_data->stage == STAGE_TUTORIAL) {
			DrawStr str(_T("�v���C���["), hit.pos.Add(0, -35).ToIntXY(), 0xFFFFFF );
			str.Draw();
		}
	}
}

//�_�b�V������.
void Player::UpdateDash()
{
	//�_�b�V���N�[���_�E������.
	if (dashCooldown > 0){
		dashCooldown -= 1 * p_data->speedRate;
	}

	//�_�b�V�����Ȃ�.
	if (isDashing)
	{
		dashTimer -= 1 * p_data->speedRate;
		//�_�b�V�����Ԑ؂�.
		if (dashTimer <= 0)
		{
			isDashing = false; //�_�b�V���I��.
		}
	}
	//�_�b�V�����ĂȂ��Ȃ�.
	else
	{
		if (dashCooldown <= 0)
		{
			bool dashkey = p_input->IsPushActionTime(_T("PlayerDash")) == 1;
			//�_�b�V���J�n.
			if (dashkey)
			{
				dashTimer    = PLAYER_DASH_DURATION;
				dashCooldown = PLAYER_DASH_COOLDOWN;
				isDashing    = true;

				//�`���[�g���A���Ȃ�.
				if (p_data->stage == STAGE_TUTORIAL) {
					TutorialStage::GetInst().SetPlayerDash(true);
				}
			}
		}
	}
}

//�ړ�����(�΂ߑΉ�)
void Player::PlayerMove()
{
	float speed = PLAYER_MOVE_SPEED * p_data->speedRate;

	//�ړ��\�Ȃ�.
	if (isMoveAble) {
		//�_�b�V�����͉���.
		if (isDashing)
		{
			//�c�莞�Ԃɉ����Ēi�X����.
			speed *= 1.0 + PLAYER_DASH_SPEED * Calc::CalcNumEaseOut(dashTimer/PLAYER_DASH_DURATION);
		}
		//�ړ�.
		p_input->MoveKey4Dir(&hit.pos, speed);
		p_input->MovePadStick(&hit.pos, speed);
		//�ړ����E.
		FixPosInArea(&hit.pos, { PLAYER_SIZE * 2, PLAYER_SIZE * 2 }, 0, 0, WINDOW_WID - 1, WINDOW_HEI - 1);
	}
}

//���S����.
void Player::PlayerDeath() {

	//�f�o�b�O���[�h���͖��G.
	if (isDebug) { return; }

	//�܂��������Ă�Ȃ�.
	if (active) {

		//�T�E���h.
		InstSoundMng.Play(_T("PlayerDeath"), false, 80);
		//�G�t�F�N�g.
		EffectData data{};
		data.type = Effect_PlayerDeath;
		data.pos  = hit.pos;
		p_effectMng->SpawnEffect(&data);
		//GamaManager�̊֐����s(include��������Ύg����)
		GameManager::GetInst().GameOver(); //�Q�[���I��.
	
		isDashing    = false;
		dashTimer    = 0;
        dashCooldown = 0;
		active       = false;
	}
}

//�v���C���[����.
void Player::PlayerRevival()
{
	hit.pos = {WINDOW_WID/2, WINDOW_HEI/2};
	active  = true;

	//�c���z��̃��Z�b�g.
	for (int i = 0; i < _countof(after); i++) {
		after[i].pos = hit.pos;
		after[i].isActive = false;
	}
}

//�c���X�V.
void Player::UpdateAfterImage()
{
	afterCntr -= p_data->speedRate;

	//�c�����c���^�C�~���O�ɂȂ�����(��{�͖��t���[��)
	if (afterCntr <= 0) {
		afterCntr = 1;

		//�c���f�[�^�����ɂ��炷.
		for (int i = PLAYER_AFT_IMG_NUM - 1; i > 0; i--)
		{
			after[i] = after[i-1];
		}
		after[0].pos      = hit.pos; //�v���C���[���W��1�t���[���ڂɋL�^.
		after[0].isActive = false;   //��U�����ɂ���.

		//�_�b�V����.
		if (isDashing) {
			//�G�t�F�N�g.
			EffectData data;
			data.type = Effect_PlayerDash;
			data.pos  = hit.pos;
			data.ang  = Calc::CalcFacingAng(after[0].pos, after[1].pos); //�ړ������̋t����.
			p_effectMng->SpawnEffect(&data);
		}
		else {
			//�ʒu���ς������(�ړ�������)
			if (after[0].pos.x != after[1].pos.x || after[0].pos.y != after[1].pos.y) {
				after[0].isActive = true; //�L����.
			}
		}
	}
}

//�c���`��.
void Player::DrawAfterImage()
{
	//�c������.
	for (int i = 0; i < PLAYER_AFT_IMG_NUM; i++)
	{
		if (!after[i].isActive) { continue; }

		if (hit.pos.x != after[i].pos.x || hit.pos.y != after[i].pos.y) {
			//�����x�̌v�Z.
			float alpha = (float)i/PLAYER_AFT_IMG_NUM;
			//�����x���f.
			SetDrawBlendModeKR(BlendModeID::Add, 255*(1-alpha));

			Circle cir = { after[i].pos, PLAYER_SIZE, {} };
			//���˃J���[.
			if (mode == Player_Reflect ||
				mode == Player_SuperReflect
			){
				cir.color = COLOR_PLY_AFT_REF;
			}
			//�ʏ�J���[.
			else
			{
				cir.color = COLOR_PLY_AFT_NOR;
			}

			DrawCircleKR(&cir, false, true);
		}
	}

	//�`�惂�[�h���Z�b�g.
	ResetDrawBlendMode();
}

/*
//�_�b�V���G�t�F�N�g����.
void Player::CreateDashEffect(DBL_XY pos)
{
	DashEffect* effect = &dashEffects[dashEffectIndex];

	effect->pos = pos;
	effect->scale = 1.0f;
	effect->alpha = 255.0f;
	effect->timer = 30;  // 30�t���[���\��
	effect->active = true;

	// ���̃C���f�b�N�X�Ɉړ��i�z�j
	dashEffectIndex = (dashEffectIndex + 1) % PLAYER_DASH_EFFECT_MAX;
}

//�_�b�V���G�t�F�N�g�X�V.
void Player::UpdateDashEffects()
{
	for (int i = 0; i < PLAYER_DASH_EFFECT_MAX; i++) {
		if (dashEffects[i].active) {
			dashEffects[i].timer--;
			dashEffects[i].scale += 0.1f; // �g�呬�x�������x��
			dashEffects[i].alpha -= 6.0f; // �t�F�[�h�A�E�g���x�������x��

			//�^�C�}�[��0 or �����x��0�ȉ��ɂȂ�����.
			if (dashEffects[i].timer <= 0 || dashEffects[i].alpha <= 0) {
				dashEffects[i].active = false; //��A�N�e�B�u��.
			}
		}
	}
}

//�_�b�V���G�t�F�N�g�`��.
void Player::DrawDashEffects()
{
	for (int i = 0; i < PLAYER_DASH_EFFECT_MAX; i++) {
		if (dashEffects[i].active) {

			DashEffect* effect = &dashEffects[i];

			// �_�Ō��ʂ̌v�Z�i2�t���[�����Ƃɓ_�Łj
			bool isFlashOn = ((effect->timer / 2) % 2) == 0;
			if (!isFlashOn) continue;  // �_�ł�OFF�t���[���Ȃ�`�悵�Ȃ�

			// �G�t�F�N�g�̃T�C�Y�v�Z
			int baseSize = (int)(PLAYER_SIZE * effect->scale);
			int alpha = (int)max(0, min(255, effect->alpha));

			// �A���t�@��0�ȉ��Ȃ�`�悵�Ȃ�
			if (alpha <= 0) continue;

			// �_�łɂ��P�x�ω��i���߂̓_�Łj
			float flashIntensity = (effect->timer % 4 < 2) ? 1.5f : 0.8f;
			alpha = (int)(alpha * flashIntensity);
			alpha = Calc::ClampNum(alpha, 0, 255); //0�`255�͈̔͂Ɏ��߂�.

			// �A���t�@�u�����h���[�h�ݒ�i�G�t�F�N�g���Ƃɐݒ�j
			SetDrawBlendModeKR(BlendModeID::Alpha, alpha);

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
						DrawBoxKR(&thickBox, Anchor::Mid, false, true);
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
			DrawBoxKR(&centerBox, Anchor::Mid, false, true);

			// �`�惂�[�h���Z�b�g
			ResetDrawBlendMode();
		}
	}
}
*/