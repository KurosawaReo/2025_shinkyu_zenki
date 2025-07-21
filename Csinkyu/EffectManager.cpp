/*
   - EffectManager.cpp -
   �G�t�F�N�g���Ǘ�����N���X.
*/
#include "GameManager.h"
#include "EffectManager.h"

void EffectManager::Init(GameData* _data) {
	p_data = _data;
}

void EffectManager::Reset() {
	//�S�ẴG�t�F�N�g�����Z�b�g.
	for (int i = 0; i < EFFECT_MAX; i++) {
		effect[i].active = FALSE;
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
					//�ړ�.
					effect[i].pos.x += effect[i].vec.x * effect[i].speed * ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
					effect[i].pos.y += effect[i].vec.y * effect[i].speed * ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);

					//���Ԍo�߂ŏ���.
					if (effect[i].counter >= METEO_BREAK_ANIM_TIME) {
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
					//�e�L�X�g�ݒ�.
					STR_DRAW str = { _T("+100"), {}, COLOR_SCORE };
					str.pos = { _int(effect[i].pos.x), _int(effect[i].pos.y - CalcNumEaseOut(effect[i].counter/SCORE_ANIM_TIME)*30)};
					//�A�j���[�V�����l.
					int pow = 255 * CalcNumEaseOut(1 - effect[i].counter/SCORE_ANIM_TIME);

					//�`��.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					DrawStringST(&str, TRUE, p_data->font1);
					ResetDrawBlendMode();
				}
				break;

				case Effect_Score500:
				{
					//�e�L�X�g�ݒ�.
					STR_DRAW str = { _T("+500"), {}, COLOR_SCORE };
					str.pos = { _int(effect[i].pos.x), _int(effect[i].pos.y - CalcNumEaseOut(effect[i].counter/SCORE_ANIM_TIME)*30)};
					//�A�j���[�V�����l.
					int pow = 255 * CalcNumEaseOut(1 - effect[i].counter/SCORE_ANIM_TIME);

					//�`��.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					DrawStringST(&str, TRUE, p_data->font1);
					ResetDrawBlendMode();
				}
				break;

				case Effect_PlayerDeath:
				{
					Box box = { effect[i].pos, { PLAYER_SIZE+effect[i].counter, PLAYER_SIZE+effect[i].counter }, 0xFFFFFF };
					//�A�j���[�V�����l.
					int pow = 255 * CalcNumEaseOut(1 - effect[i].counter/PLAYER_DEATH_ANIM_TIME);

					//�`��.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					DrawBoxST(&box, TRUE, FALSE);
					ResetDrawBlendMode();
				}
				break;

				case Effect_ReflectLaser:
				{
					Box box = { effect[i].pos, { 10+effect[i].counter*2, 10+effect[i].counter*2 }, COLOR_PLY_REFLECT };
					//�A�j���[�V�����l.
					int pow = 255 * CalcNumEaseOut(1 - effect[i].counter/LASER_REF_ANIM_TIME);

					//�`��.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					DrawBoxST(&box, TRUE, FALSE);
					ResetDrawBlendMode();
				}
				break;

				case Effect_BreakMeteo:
				{
					//��΂����̃f�[�^.
					Line line{};
					line.stPos = CalcArcPos(effect[i].pos, effect[i].ang,     effect[i].len);
					line.edPos = CalcArcPos(effect[i].pos, effect[i].ang+180, effect[i].len);
			        line.clr   = COLOR_METEO(effect[i].pos);
					//�A�j���[�V�����l.
					int pow = 255 * CalcNumEaseOut(1 - effect[i].counter/METEO_BREAK_ANIM_TIME);

					//�`��.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					DrawLineST(&line);
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
			effect[i].active  = TRUE;      //�L���ɂ���.

			break; //��������.
		}
	}
}
//�G�t�F�N�g����.
void EffectManager::DeleteEffect(int idx) {

	effect[idx].active = FALSE;
}