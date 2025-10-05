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
		//1�t���[���ڂ̏��o�^.
		after[0].pos      = hit.pos;                                         //�v���C���[���W.
		after[0].ang      = Calc::CalcFacingAng(after[0].pos, after[1].pos); //�ړ�����.
		after[0].isDash   = isDashing;                                       //�_�b�V�����Ȃ�_�b�V���G�t�F�N�g��.
		after[0].isActive = false;                                           //��U�����ɂ���.
		//�ʒu���ς������(�ړ�������)
		if (after[0].pos.x != after[1].pos.x || after[0].pos.y != after[1].pos.y) {
			after[0].isActive = true; //�L����.
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
			//�A�j���[�V�����l.
			float anim = (float)i/PLAYER_AFT_IMG_NUM;
			//�����x���f.
			SetDrawBlendModeKR(BlendModeID::Add, 255*(1-anim));

			MY_COLOR color;

			//�_�b�V���G�t�F�N�g.
			if (after[i].isDash) {
				//�O�p�`�f�[�^.
				DBL_XY   pos1 = after[i].pos + Calc::CalcVectorDeg(after[i].ang)    * (30 * (1-anim));
				DBL_XY   pos2 = after[i].pos + Calc::CalcVectorDeg(after[i].ang+90) * (20 * (1-anim));
				DBL_XY   pos3 = after[i].pos + Calc::CalcVectorDeg(after[i].ang-90) * (20 * (1-anim));
				GradLine line;
				//���˃J���[.
				if (mode == Player_Reflect ||
					mode == Player_SuperReflect
				){
					line.AddPoint(pos2, {255,   0, 255, _int_r(255*(1-anim))});
					line.AddPoint(pos1, {100,   0, 100, _int_r(255*(1-anim))});
					line.AddPoint(pos3, {255,   0, 255, _int_r(255*(1-anim))});
				}
				//�ʏ�J���[.
				else
				{
					line.AddPoint(pos2, {255, 255, 255, _int_r(255*(1-anim))});
					line.AddPoint(pos1, {100, 100, 100, _int_r(255*(1-anim))});
					line.AddPoint(pos3, {255, 255, 255, _int_r(255*(1-anim))});
				}
				line.Draw();
			}
			//�ʏ�G�t�F�N�g.
			else {
				//���˃J���[.
				if (mode == Player_Reflect ||
					mode == Player_SuperReflect
				){
					color = COLOR_PLY_AFT_REF;
				}
				//�ʏ�J���[.
				else
				{
					color = COLOR_PLY_AFT_NOR;
				}
				//�~�`��.
				Circle cir = { after[i].pos, PLAYER_SIZE, color };
				DrawCircleKR(&cir, false, true);
			}
		}
	}

	//�`�惂�[�h���Z�b�g.
	KR_Lib::ResetDrawBlendMode();
}