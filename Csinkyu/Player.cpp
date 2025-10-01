/*
   - Player.cpp -
   �v���C���[�Ǘ�.
*/
#include "GameManager.h"
#include "LaserManager.h"
#include "Obst_NormalLaserMain.h"

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
	imgPlayer[0].LoadFile(_T("Resources/Images/player_normal.png"));
	imgPlayer[1].LoadFile(_T("Resources/Images/player_reflect.png"));
}
//���Z�b�g(����ł��s��)
void Player::Reset(DBL_XY _pos, bool _active)
{
	hit        = { _pos, PLAYER_SIZE, {} };
	active     = _active;
	mode       = Player_Normal;
	afterCntr  = 1;
	isMoveAble = true;

	//�c���z��̃��Z�b�g.
	for (int i = 0; i < _countof(after); i++) {
		after[i].pos      = _pos;
		after[i].isActive = false;
	}
	//���˃G�t�F�N�g���Z�b�g.
	reflectEffectIndex = 0;
	for (int i = 0; i < PLAYER_MAX_EFFECT; i++) {
		reflectEffects[i].active = false;
		reflectEffects[i].timer = 0;
		reflectEffects[i].alpha = 0.0f;
		reflectEffects[i].scale = 1.0f;
		reflectEffects[i].pos = _pos;
	}
}
//�X�V.
void Player::Update()
{
#if defined _DEBUG //Release�ł͓���Ȃ�.
	//�f�o�b�O���[�h�؂�ւ�.
	if (p_input->IsPushKeyTime(KeyID::M) == 1) {
		isDebug = !isDebug;
	}
	//�e�X�g�p�FE�L�[�Ŕ��˃G�t�F�N�g�𐶐�
	if (p_input->IsPushKeyTime(KeyID::E) == 1) {
		CreateReflectEffect(hit.pos);
	}
#endif

	//�L���Ȃ�.
	if (active) {
		imgRot += 1.5 * p_data->speedRate; //�摜��].

		UpdateAfterImage();
		UpdateReflectEffects();
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
	for (int i = 0; i < PLAYER_MAX_EFFECT; i++) {
		if (reflectEffects[i].active) {
			TCHAR debugStr[128];
			_stprintf_s(debugStr, _T("Effect[%d]: timer=%d, alpha=%.1f, scale=%.1f"),
				i, reflectEffects[i].timer, reflectEffects[i].alpha, reflectEffects[i].scale);
			DrawString(0, 450 + i * 20, debugStr, 0xFFFFFF);
		}
	}
#endif

	//�L���Ȃ�.
	if (active) {
		DrawAfterImage();
		DrawReflectEffects();  // �G�t�F�N�g���ɕ`��

		const float size = 0.17;

		//�摜�`��.
		if (mode == Player_Reflect ||
			mode == Player_SuperReflect
		){
			//���˃��[�h�̉摜.
			imgPlayer[1].DrawRota(hit.pos, size, imgRot, {0, 0}, Anchor::Mid, true, true);
		}
		else {
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

//�ړ�����(�΂ߑΉ�)
void Player::PlayerMove()
{
	//�ړ��\�Ȃ�.
	if (isMoveAble) {
		//�ړ�����.
		p_input->MoveKey4Dir (&hit.pos, PLAYER_MOVE_SPEED * p_data->speedRate);
		p_input->MovePadStick(&hit.pos, PLAYER_MOVE_SPEED * p_data->speedRate);
		//�ړ����E.
		FixPosInArea(&hit.pos, { PLAYER_SIZE*2, PLAYER_SIZE*2 }, 0, 0, WINDOW_WID-1, WINDOW_HEI-1);
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
	
		active = false;
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
		//�ʒu���ς������(�ړ�������)
		if (hit.pos.x != after[1].pos.x || hit.pos.y != after[1].pos.y) {
			after[0].pos      = hit.pos; //�v���C���[���W��1�t���[���ڂɋL�^.
			after[0].isActive = true;    //�L����.
		}
		else {
			after[0].isActive = false;   //������.
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

// ���˃G�t�F�N�g����
void Player::CreateReflectEffect(DBL_XY pos)
{
	ReflectEffect* effect = &reflectEffects[reflectEffectIndex];

	effect->pos = pos;
	effect->scale = 1.0f;
	effect->alpha = 255.0f;
	effect->timer = 30;  // 30�t���[���\��
	effect->active = true;

	// ���̃C���f�b�N�X�Ɉړ��i�z�j
	reflectEffectIndex = (reflectEffectIndex + 1) % PLAYER_MAX_EFFECT;
}

// ���˃G�t�F�N�g�X�V
void Player::UpdateReflectEffects()
{
	for (int i = 0; i < PLAYER_MAX_EFFECT; i++) {
		if (reflectEffects[i].active) {
			reflectEffects[i].timer--;
			reflectEffects[i].scale += 0.1f;      // �g�呬�x�������x��
			reflectEffects[i].alpha -= 6.0f;     // �t�F�[�h�A�E�g���x�������x��

			// �^�C�}�[��0�ɂȂ����������x��0�ȉ��ɂȂ������A�N�e�B�u
			if (reflectEffects[i].timer <= 0 || reflectEffects[i].alpha <= 0) {
				reflectEffects[i].active = false;
			}
		}
	}
}

// ���˃G�t�F�N�g�`��
void Player::DrawReflectEffects()
{
	for (int i = 0; i < PLAYER_MAX_EFFECT; i++) {
		if (reflectEffects[i].active) {
			ReflectEffect* effect = &reflectEffects[i];

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
			alpha = min(255, max(0, alpha));

			// �s���N�F�̐ݒ�i��薾�邭�A�_�łŕω��j
			UINT color = GetColor(
				min(255, (int)(alpha * flashIntensity)),
				alpha * 80 / 255,
				min(255, alpha * 150 / 255)
			);

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