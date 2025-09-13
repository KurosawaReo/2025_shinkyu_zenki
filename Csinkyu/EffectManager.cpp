/*
   - EffectManager.cpp -
   �G�t�F�N�g���Ǘ�����N���X.
*/
#include "GameManager.h"
#include "EffectManager.h"

using namespace Calc; //�v�Z�@�\���g�p.

void EffectManager::Init(GameData* _data) {
	p_data = _data;

	imgScore[0].LoadFile(_T("Resources/Images/score100.png"));
	imgScore[1].LoadFile(_T("Resources/Images/score500.png"));
}

void EffectManager::Reset() {
	//�S�ẴG�t�F�N�g�����Z�b�g.
	for (int i = 0; i < EFFECT_MAX; i++) {
		effect[i].active = false;
	}
}

void EffectManager::Update() {
	
	//�L���ȃG�t�F�N�g�̂ݍX�V.
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (effect[i].active) {

			//�^�C�v��.
			switch (effect[i].type) 
			{
				case Effect_Score100:
				{
					effect[i].counter++;

					//���Ԍo�߂ŏ���.
					if (effect[i].counter >= SCORE_ANIM_TIME) {
						DeleteEffect(i);
					}
				}
				break;

				case Effect_Score500:
				{
					effect[i].counter++;

					//���Ԍo�߂ŏ���.
					if (effect[i].counter >= SCORE_ANIM_TIME) {
						DeleteEffect(i);
					}
				}
				break;

				case Effect_PlayerDeath:
				{
					effect[i].counter++;

					//���Ԍo�߂ŏ���.
					if (effect[i].counter >= PLAYER_DEATH_ANIM_TIME) {
						DeleteEffect(i);
					}
				}
				break;

				case Effect_ReflectLaser:
				{
					effect[i].counter++;

					//���Ԍo�߂ŏ���.
					if (effect[i].counter >= LASER_REF_ANIM_TIME) {
						DeleteEffect(i);
					}
				}
				break;

				case Effect_BreakMeteo:
				{
					//�J�E���^�[���Z.
					effect[i].counter += ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
					//��].
					effect[i].ang += 3 * ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
					//����.
					float newSpeed = effect[i].speed/(1+(effect[i].counter/10));
					//�ړ�.
					effect[i].pos.x += effect[i].vec.x * newSpeed * ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
					effect[i].pos.y += effect[i].vec.y * newSpeed * ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);

					//���Ԍo�߂ŏ���.
					if (effect[i].counter >= METEO_BREAK_ANIM_TIME) {
						DeleteEffect(i);
					}
				}
				break;

				case Effect_Level1:
				case Effect_Level2:
				case Effect_Level3:
				case Effect_Level4:
				case Effect_Level5:
				{
					effect[i].counter++;

					//���Ԍo�߂ŏ���.
					if (effect[i].counter >= LEVEL_UP_ANIM_TIME) {
						DeleteEffect(i);
					}
				}
				break;

				default: assert(FALSE); break;
			}
		}
	}
}

void EffectManager::Draw() {

	//�L���ȃG�t�F�N�g�̂ݕ`��.
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (effect[i].active) {

			//�^�C�v��.
			switch (effect[i].type)
			{
				case Effect_Score100:
				{
					//���W.
					DBL_XY pos = {effect[i].pos.x, effect[i].pos.y - CalcNumEaseOut(effect[i].counter/SCORE_ANIM_TIME)*30};
					//�A�j���[�V�����l.
					int pow = _int_r(255 * CalcNumEaseOut(1 - effect[i].counter/SCORE_ANIM_TIME));

					//�`��.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					imgScore[0].DrawExtend(pos, {0.2, 0.2});
					ResetDrawBlendMode();
				}
				break;

				case Effect_Score500:
				{
  				    //���W.
					DBL_XY pos = { effect[i].pos.x, effect[i].pos.y - CalcNumEaseOut(effect[i].counter / SCORE_ANIM_TIME) * 30 };
					//�A�j���[�V�����l.
					int pow = _int_r(255 * CalcNumEaseOut(1 - effect[i].counter/SCORE_ANIM_TIME));

					//�`��.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					imgScore[1].DrawExtend(pos, {0.2, 0.2});
					ResetDrawBlendMode();
				}
				break;

				case Effect_PlayerDeath:
				{
					Box box = { effect[i].pos, { PLAYER_SIZE+effect[i].counter, PLAYER_SIZE+effect[i].counter }, 0xFFFFFF };
					//�A�j���[�V�����l.
					int pow = _int_r(255 * CalcNumEaseOut(1 - effect[i].counter/PLAYER_DEATH_ANIM_TIME));

					//�`��.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					DrawBoxST(&box, ANC_MID, false, true);
					ResetDrawBlendMode();
				}
				break;

				case Effect_ReflectLaser:
				{
					Box box = { effect[i].pos, { 10+effect[i].counter*4, 10+effect[i].counter*4 }, COLOR_PLY_REFLECT };
					//�A�j���[�V�����l.
					int pow = _int_r(255 * CalcNumEaseOut(1 - effect[i].counter/LASER_REF_ANIM_TIME));

					//�`��.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					DrawBoxST(&box, ANC_MID, false, true);
					ResetDrawBlendMode();
				}
				break;

				case Effect_BreakMeteo:
				{
					//��΂����̃f�[�^.
					Line line{};
					line.stPos = CalcArcPos(effect[i].pos, effect[i].ang,     effect[i].len);
					line.edPos = CalcArcPos(effect[i].pos, effect[i].ang+180, effect[i].len);
			        line.color = COLOR_METEO(effect[i].pos);
					//�A�j���[�V�����l.
					int pow = _int_r(255 * CalcNumEaseOut(1 - effect[i].counter/METEO_BREAK_ANIM_TIME));

					//�`��.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					DrawLineST(&line, true);
					ResetDrawBlendMode();
				}
				break;

				case Effect_Level1:
				{
					DrawStr str = { _T("Level 1"), {_int_r(effect[i].pos.x), _int_r(effect[i].pos.y-20)}, 0xFFFFFF};
					Circle cir = { effect[i].pos, effect[i].counter*5, 0xFFFFFF };
					Circle cirLevel[5] = {
						{{effect[i].pos.x-60, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x-30, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x,    effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x+30, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x+60, effect[i].pos.y+20}, 10, 0xFFFFFF}
					};
					//�A�j���[�V�����l.
					int pow = _int_r(255 * CalcNumWaveLoop(1 - effect[i].counter/LEVEL_UP_ANIM_TIME));

					//�`��.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					str.Draw(ANC_MID, p_data->font2);
					DrawCircleST(&cir, false, true);
					DrawCircleST(&cirLevel[0], true,  true); //��
					DrawCircleST(&cirLevel[1], false, true); //��
					DrawCircleST(&cirLevel[2], false, true); //��
					DrawCircleST(&cirLevel[3], false, true); //��
					DrawCircleST(&cirLevel[4], false, true); //��
					ResetDrawBlendMode();
				}
				break;

				case Effect_Level2:
				{
					DrawStr str = { _T("Level 2"), {_int_r(effect[i].pos.x), _int_r(effect[i].pos.y-20)}, 0xFFFFFF };
					Circle cir = { effect[i].pos, effect[i].counter*5, 0xFFFFFF };
					Circle cirLevel[5] = {
						{{effect[i].pos.x-60, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x-30, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x,    effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x+30, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x+60, effect[i].pos.y+20}, 10, 0xFFFFFF}
					};
					//�A�j���[�V�����l.
					int pow = _int(255 * CalcNumWaveLoop(1 - effect[i].counter/LEVEL_UP_ANIM_TIME));

					//�`��.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					str.Draw(ANC_MID, p_data->font2);
					DrawCircleST(&cir, false, true);
					DrawCircleST(&cirLevel[0], true,  true); //��
					DrawCircleST(&cirLevel[1], true,  true); //��
					DrawCircleST(&cirLevel[2], false, true); //��
					DrawCircleST(&cirLevel[3], false, true); //��
					DrawCircleST(&cirLevel[4], false, true); //��
					ResetDrawBlendMode();
				}
				break;

				case Effect_Level3:
				{
					DrawStr str = { _T("Level 3"), {_int_r(effect[i].pos.x), _int_r(effect[i].pos.y-20)}, 0xFFFFFF };
					Circle cir = { effect[i].pos, effect[i].counter*5, 0xFFFFFF };
					Circle cirLevel[5] = {
						{{effect[i].pos.x-60, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x-30, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x,    effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x+30, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x+60, effect[i].pos.y+20}, 10, 0xFFFFFF}
					};
					//�A�j���[�V�����l.
					int pow = _int_r(255 * CalcNumWaveLoop(1 - effect[i].counter/LEVEL_UP_ANIM_TIME));

					//�`��.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					str.Draw(ANC_MID, p_data->font2);
					DrawCircleST(&cir, false, true);
					DrawCircleST(&cirLevel[0], true,  true); //��
					DrawCircleST(&cirLevel[1], true,  true); //��
					DrawCircleST(&cirLevel[2], true,  true); //��
					DrawCircleST(&cirLevel[3], false, true); //��
					DrawCircleST(&cirLevel[4], false, true); //��
					ResetDrawBlendMode();
				}
				break;

				case Effect_Level4:
				{
					DrawStr str = { _T("Level 4"), {_int_r(effect[i].pos.x), _int_r(effect[i].pos.y-20)}, 0xFFFFFF };
					Circle cir = { effect[i].pos, effect[i].counter*5, 0xFFFFFF };
					Circle cirLevel[5] = {
						{{effect[i].pos.x-60, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x-30, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x,    effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x+30, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x+60, effect[i].pos.y+20}, 10, 0xFFFFFF}
					};
					//�A�j���[�V�����l.
					int pow = _int_r(255 * CalcNumWaveLoop(1 - effect[i].counter/LEVEL_UP_ANIM_TIME));

					//�`��.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					str.Draw(ANC_MID, p_data->font2);
					DrawCircleST(&cir, false, true);
					DrawCircleST(&cirLevel[0], true,  true); //��
					DrawCircleST(&cirLevel[1], true,  true); //��
					DrawCircleST(&cirLevel[2], true,  true); //��
					DrawCircleST(&cirLevel[3], true,  true); //��
					DrawCircleST(&cirLevel[4], false, true); //��
					ResetDrawBlendMode();
				}
				break;

				case Effect_Level5:
				{
					DrawStr str = { _T("Level 5"), {_int_r(effect[i].pos.x), _int_r(effect[i].pos.y-20)}, 0xFFFFFF };
					Circle cir = { effect[i].pos, effect[i].counter*5, 0xFFFFFF };
					Circle cirLevel[5] = {
						{{effect[i].pos.x-60, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x-30, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x,    effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x+30, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x+60, effect[i].pos.y+20}, 10, 0xFFFFFF}
					};
					//�A�j���[�V�����l.
					int pow = _int_r(255 * CalcNumWaveLoop(1 - effect[i].counter/LEVEL_UP_ANIM_TIME));

					//�`��.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					str.Draw(ANC_MID, p_data->font2);
					DrawCircleST(&cir, false, true);
					DrawCircleST(&cirLevel[0], true, true); //��
					DrawCircleST(&cirLevel[1], true, true); //��
					DrawCircleST(&cirLevel[2], true, true); //��
					DrawCircleST(&cirLevel[3], true, true); //��
					DrawCircleST(&cirLevel[4], true, true); //��
					ResetDrawBlendMode();
				}
				break;

				default: assert(FALSE); break;
			}
		}
	}
}

//�G�t�F�N�g�o��.
void EffectManager::SpawnEffect(EffectData* data) {

	//���g�p�̃G�t�F�N�g��T��.
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (!effect[i].active) {

			effect[i].type    = data->type;
			effect[i].pos     = data->pos;
			effect[i].vec     = data->vec;
			effect[i].speed   = data->speed;
			effect[i].ang     = data->ang;
			effect[i].len     = data->len;
			effect[i].counter = 0;         //0����J�n. 
			effect[i].active  = true;      //�L���ɂ���.

			break; //��������.
		}
	}
}
//�G�t�F�N�g����.
void EffectManager::DeleteEffect(int idx) {

	effect[idx].active = false;
}