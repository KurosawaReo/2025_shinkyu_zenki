/*
   - EffectManager.cpp -
   �G�t�F�N�g���Ǘ�����N���X.
*/
#include "GameManager.h"
#include "EffectManager.h"

using namespace Calc; //�v�Z�@�\���g�p.

void EffectManager::Init() {
	p_data = GameData::GetPtr();

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
					if (effect[i].counter >= METEOR_BREAK_ANIM_TIME) {
						DeleteEffect(i);
					}
				}
				break;

				case Effect_Endless_Level1:
				case Effect_Endless_Level2:
				case Effect_Endless_Level3:
				case Effect_Endless_Level4:
				case Effect_Endless_Level5:
				case Effect_Tutorial_Step1:
				case Effect_Tutorial_Step2:
				case Effect_Tutorial_Step3:
				case Effect_Tutorial_Step4:
				{
					effect[i].counter++;

					//���Ԍo�߂ŏ���.
					if (effect[i].counter >= MIDDLE_ANIM_TIME) {
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
				case Effect_Score500:
				{
					//���W.
					DBL_XY pos = {effect[i].pos.x, effect[i].pos.y - CalcNumEaseOut(effect[i].counter/SCORE_ANIM_TIME)*30};
					//�A�j���[�V�����l.
					int pow = _int_r(255 * CalcNumEaseOut(1 - effect[i].counter/SCORE_ANIM_TIME));

					//�`��.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					//�摜�؂�ւ�.
					if (Effect_Score100) {
						imgScore[0].DrawExtend(pos, {0.2, 0.2});
					}
					else {
						imgScore[1].DrawExtend(pos, {0.2, 0.2});
					}
				}
				break;

				case Effect_PlayerDeath:
				{
					Circle cir= { effect[i].pos, PLAYER_SIZE+effect[i].counter/2, 0xFFFFFF };
					//�A�j���[�V�����l.
					int pow = _int_r(255 * CalcNumEaseOut(1 - effect[i].counter/PLAYER_DEATH_ANIM_TIME));

					//�`��.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					DrawCircleST(&cir, false, true);
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
					int pow = _int_r(255 * CalcNumEaseOut(1 - effect[i].counter/METEOR_BREAK_ANIM_TIME));

					//�`��.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					DrawLineST(&line, true);
				}
				break;

				case Effect_Endless_Level1:
				case Effect_Endless_Level2:
				case Effect_Endless_Level3:
				case Effect_Endless_Level4:
				case Effect_Endless_Level5:
				case Effect_Tutorial_Step1:
				case Effect_Tutorial_Step2:
				case Effect_Tutorial_Step3:
				case Effect_Tutorial_Step4:
				{
					//���ʐݒ�.
					DrawStr str = { _T("Unknown"), {_int_r(effect[i].pos.x), _int_r(effect[i].pos.y-20)}, 0xFFFFFF};
					Circle mainCir = { effect[i].pos, effect[i].counter*5, 0xFFFFFF };
					Circle lampCir[5] = {
						{{-1, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{-1, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{-1, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{-1, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{-1, effect[i].pos.y+20}, 10, 0xFFFFFF}
					};
					//�A�j���[�V�����l.
					int pow = _int_r(255 * CalcNumWaveLoop(1 - effect[i].counter/MIDDLE_ANIM_TIME));
					//�������v���g����.
					int lampUseCnt  = 0;
					int lampFillCnt = 0;

					//�`��.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					DrawCircleST(&mainCir, false, true);

					switch (effect[i].type) 
					{
						case Effect_Endless_Level1:
							str.text = _T("Level 1");
							lampUseCnt  = 5;
							lampFillCnt = 1;
							break;
						case Effect_Endless_Level2:
							str.text = _T("Level 2");
							lampUseCnt  = 5;
							lampFillCnt = 2;
							break;
						case Effect_Endless_Level3:
							str.text = _T("Level 3");
							lampUseCnt  = 5;
							lampFillCnt = 3;
							break;
						case Effect_Endless_Level4:
							str.text = _T("Level 4");
							lampUseCnt  = 5;
							lampFillCnt = 4;
							break;
						case Effect_Endless_Level5:
							str.text = _T("Level 5");
							lampUseCnt  = 5;
							lampFillCnt = 5;
							break;

						case Effect_Tutorial_Step1:
							str.text = _T("Step 1");
							lampUseCnt  = 4;
							lampFillCnt = 1;
							break;
						case Effect_Tutorial_Step2:
							str.text = _T("Step 2");
							lampUseCnt  = 4;
							lampFillCnt = 2;
							break;
						case Effect_Tutorial_Step3:
							str.text = _T("Step 3");
							lampUseCnt  = 4;
							lampFillCnt = 3;
							break;
						case Effect_Tutorial_Step4:
							str.text = _T("Step 4");
							lampUseCnt  = 4;
							lampFillCnt = 4;
							break;
					}
					//�e�L�X�g.
					str.Draw(ANC_MID, p_data->font2);
					//�����v(�K�v�Ȑ������`��)
					for (int j = 0; j < lampUseCnt; j++) {
						
						const int interval = 30; //�Ԋu.
						//�ϓ��ɂȂ�悤�ɔz�u����.
						lampCir[j].pos.x = effect[i].pos.x + interval * (j - _flt(lampUseCnt-1)/2);
						//�~�`��.
						DrawCircleST(&lampCir[j], (lampFillCnt >= j+1), true); 
					}
				}
				break;

				default: assert(FALSE); break;
			}

			ResetDrawBlendMode(); //�`�惂�[�h���Z�b�g.
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