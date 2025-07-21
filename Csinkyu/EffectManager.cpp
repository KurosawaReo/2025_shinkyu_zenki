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

			//�J�E���^�[���Z.
			effect[i].counter++;
//			effect[i].counter += ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);

			//�^�C�v��.
			switch (effect[i].type) 
			{
				case Effect_Score100:
				{
					//���Ԍo�߂ŏ���.
					if (effect[i].counter >= SCORE_ANIM_TIME) {
						DeleteEffect(i);
					}
				}
				break;

				case Effect_Score500:
				{
					//���Ԍo�߂ŏ���.
					if (effect[i].counter >= SCORE_ANIM_TIME) {
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

				default: assert(FALSE); break;
			}
		}
	}
}

//�G�t�F�N�g�o��.
void EffectManager::SpawnEffect(EffectType type, DBL_XY pos) {

	//���g�p�̃G�t�F�N�g��T��.
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (!effect[i].active) {

			effect[i].type    = type;
			effect[i].pos     = pos; 
			effect[i].counter = 0;    //0����J�n. 
			effect[i].active  = TRUE; //�L���ɂ���.
			break;                    //��������.
		}
	}
}
//�G�t�F�N�g����.
void EffectManager::DeleteEffect(int idx) {

	effect[idx].active = FALSE;
}