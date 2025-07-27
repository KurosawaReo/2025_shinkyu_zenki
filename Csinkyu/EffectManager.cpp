/*
   - EffectManager.cpp -
   エフェクトを管理するクラス.
*/
#include "GameManager.h"
#include "EffectManager.h"

void EffectManager::Init(GameData* _data) {
	p_data = _data;
}

void EffectManager::Reset() {
	//全てのエフェクトをリセット.
	for (int i = 0; i < EFFECT_MAX; i++) {
		effect[i].active = FALSE;
	}
}

void EffectManager::Update() {
	
	//有効なエフェクトのみ更新.
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (effect[i].active) {

			//タイプ別.
			switch (effect[i].type) 
			{
				case Effect_Score100:
				{
					effect[i].counter++;

					//時間経過で消滅.
					if (effect[i].counter >= SCORE_ANIM_TIME) {
						DeleteEffect(i);
					}
				}
				break;

				case Effect_Score500:
				{
					effect[i].counter++;

					//時間経過で消滅.
					if (effect[i].counter >= SCORE_ANIM_TIME) {
						DeleteEffect(i);
					}
				}
				break;

				case Effect_PlayerDeath:
				{
					effect[i].counter++;

					//時間経過で消滅.
					if (effect[i].counter >= PLAYER_DEATH_ANIM_TIME) {
						DeleteEffect(i);
					}
				}
				break;

				case Effect_ReflectLaser:
				{
					effect[i].counter++;

					//時間経過で消滅.
					if (effect[i].counter >= LASER_REF_ANIM_TIME) {
						DeleteEffect(i);
					}
				}
				break;

				case Effect_BreakMeteo:
				{
					//カウンター加算.
					effect[i].counter += ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
					//回転.
					effect[i].ang += 3 * ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
					//減速.
					float newSpeed = effect[i].speed/(1+(effect[i].counter/10));
					//移動.
					effect[i].pos.x += effect[i].vec.x * newSpeed * ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
					effect[i].pos.y += effect[i].vec.y * newSpeed * ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);

					//時間経過で消滅.
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

					//時間経過で消滅.
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

	//有効なエフェクトのみ描画.
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (effect[i].active) {

			//タイプ別.
			switch (effect[i].type)
			{
				case Effect_Score100:
				{
					//テキスト設定.
					DrawStrST str = { _T("+100"), {}, COLOR_SCORE };
					str.SetPos(_int(effect[i].pos.x), _int(effect[i].pos.y - CalcNumEaseOut(effect[i].counter/SCORE_ANIM_TIME)*30));
					//アニメーション値.
					int pow = _int(255 * CalcNumEaseOut(1 - effect[i].counter/SCORE_ANIM_TIME));

					//描画.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					str.DrawStringST(TRUE, p_data->font1);
					ResetDrawBlendMode();
				}
				break;

				case Effect_Score500:
				{
					//テキスト設定.
					DrawStrST str = { _T("+500"), {}, COLOR_SCORE };
					str.SetPos(_int(effect[i].pos.x), _int(effect[i].pos.y - CalcNumEaseOut(effect[i].counter/SCORE_ANIM_TIME)*30));
					//アニメーション値.
					int pow = _int(255 * CalcNumEaseOut(1 - effect[i].counter/SCORE_ANIM_TIME));

					//描画.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					str.DrawStringST(TRUE, p_data->font1);
					ResetDrawBlendMode();
				}
				break;

				case Effect_PlayerDeath:
				{
					Box box = { effect[i].pos, { PLAYER_SIZE+effect[i].counter, PLAYER_SIZE+effect[i].counter }, 0xFFFFFF };
					//アニメーション値.
					int pow = _int(255 * CalcNumEaseOut(1 - effect[i].counter/PLAYER_DEATH_ANIM_TIME));

					//描画.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					DrawBoxST(&box, TRUE, FALSE, TRUE);
					ResetDrawBlendMode();
				}
				break;

				case Effect_ReflectLaser:
				{
					Box box = { effect[i].pos, { 10+effect[i].counter*4, 10+effect[i].counter*4 }, COLOR_PLY_REFLECT };
					//アニメーション値.
					int pow = _int(255 * CalcNumEaseOut(1 - effect[i].counter/LASER_REF_ANIM_TIME));

					//描画.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					DrawBoxST(&box, TRUE, FALSE, TRUE);
					ResetDrawBlendMode();
				}
				break;

				case Effect_BreakMeteo:
				{
					//飛ばす線のデータ.
					Line line{};
					line.stPos = CalcArcPos(effect[i].pos, effect[i].ang,     effect[i].len);
					line.edPos = CalcArcPos(effect[i].pos, effect[i].ang+180, effect[i].len);
			        line.clr   = COLOR_METEO(effect[i].pos);
					//アニメーション値.
					int pow = _int(255 * CalcNumEaseOut(1 - effect[i].counter/METEO_BREAK_ANIM_TIME));

					//描画.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					DrawLineST(&line, TRUE);
					ResetDrawBlendMode();
				}
				break;

				case Effect_Level1:
				{
					DrawStrST str = { _T("Level 1"), {_int(effect[i].pos.x), _int(effect[i].pos.y-20)}, 0xFFFFFF};
					Circle cir = { effect[i].pos, effect[i].counter*5, 0xFFFFFF };
					Circle cirLevel[5] = {
						{{effect[i].pos.x-60, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x-30, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x,    effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x+30, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x+60, effect[i].pos.y+20}, 10, 0xFFFFFF}
					};
					//アニメーション値.
					int pow = _int(255 * CalcNumWaveLoop(1 - effect[i].counter/LEVEL_UP_ANIM_TIME));

					//描画.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					str.DrawStringST(TRUE, p_data->font2);
					DrawCircleST(&cir, FALSE, TRUE);
					DrawCircleST(&cirLevel[0], TRUE,  TRUE); //●
					DrawCircleST(&cirLevel[1], FALSE, TRUE); //○
					DrawCircleST(&cirLevel[2], FALSE, TRUE); //○
					DrawCircleST(&cirLevel[3], FALSE, TRUE); //○
					DrawCircleST(&cirLevel[4], FALSE, TRUE); //○
					ResetDrawBlendMode();
				}
				break;

				case Effect_Level2:
				{
					DrawStrST str = { _T("Level 2"), {_int(effect[i].pos.x), _int(effect[i].pos.y-20)}, 0xFFFFFF };
					Circle cir = { effect[i].pos, effect[i].counter*5, 0xFFFFFF };
					Circle cirLevel[5] = {
						{{effect[i].pos.x-60, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x-30, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x,    effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x+30, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x+60, effect[i].pos.y+20}, 10, 0xFFFFFF}
					};
					//アニメーション値.
					int pow = _int(255 * CalcNumWaveLoop(1 - effect[i].counter/LEVEL_UP_ANIM_TIME));

					//描画.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					str.DrawStringST(TRUE, p_data->font2);
					DrawCircleST(&cir, FALSE, TRUE);
					DrawCircleST(&cirLevel[0], TRUE,  TRUE); //●
					DrawCircleST(&cirLevel[1], TRUE,  TRUE); //●
					DrawCircleST(&cirLevel[2], FALSE, TRUE); //○
					DrawCircleST(&cirLevel[3], FALSE, TRUE); //○
					DrawCircleST(&cirLevel[4], FALSE, TRUE); //○
					ResetDrawBlendMode();
				}
				break;

				case Effect_Level3:
				{
					DrawStrST str = { _T("Level 3"), {_int(effect[i].pos.x), _int(effect[i].pos.y-20)}, 0xFFFFFF };
					Circle cir = { effect[i].pos, effect[i].counter*5, 0xFFFFFF };
					Circle cirLevel[5] = {
						{{effect[i].pos.x-60, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x-30, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x,    effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x+30, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x+60, effect[i].pos.y+20}, 10, 0xFFFFFF}
					};
					//アニメーション値.
					int pow = _int(255 * CalcNumWaveLoop(1 - effect[i].counter/LEVEL_UP_ANIM_TIME));

					//描画.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					str.DrawStringST(TRUE, p_data->font2);
					DrawCircleST(&cir, FALSE, TRUE);
					DrawCircleST(&cirLevel[0], TRUE,  TRUE); //●
					DrawCircleST(&cirLevel[1], TRUE,  TRUE); //●
					DrawCircleST(&cirLevel[2], TRUE,  TRUE); //●
					DrawCircleST(&cirLevel[3], FALSE, TRUE); //○
					DrawCircleST(&cirLevel[4], FALSE, TRUE); //○
					ResetDrawBlendMode();
				}
				break;

				case Effect_Level4:
				{
					DrawStrST str = { _T("Level 4"), {_int(effect[i].pos.x), _int(effect[i].pos.y-20)}, 0xFFFFFF };
					Circle cir = { effect[i].pos, effect[i].counter*5, 0xFFFFFF };
					Circle cirLevel[5] = {
						{{effect[i].pos.x-60, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x-30, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x,    effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x+30, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x+60, effect[i].pos.y+20}, 10, 0xFFFFFF}
					};
					//アニメーション値.
					int pow = _int(255 * CalcNumWaveLoop(1 - effect[i].counter/LEVEL_UP_ANIM_TIME));

					//描画.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					str.DrawStringST(TRUE, p_data->font2);
					DrawCircleST(&cir, FALSE, TRUE);
					DrawCircleST(&cirLevel[0], TRUE,  TRUE); //●
					DrawCircleST(&cirLevel[1], TRUE,  TRUE); //●
					DrawCircleST(&cirLevel[2], TRUE,  TRUE); //●
					DrawCircleST(&cirLevel[3], TRUE,  TRUE); //●
					DrawCircleST(&cirLevel[4], FALSE, TRUE); //○
					ResetDrawBlendMode();
				}
				break;

				case Effect_Level5:
				{
					DrawStrST str = { _T("Level 5"), {_int(effect[i].pos.x), _int(effect[i].pos.y-20)}, 0xFFFFFF };
					Circle cir = { effect[i].pos, effect[i].counter*5, 0xFFFFFF };
					Circle cirLevel[5] = {
						{{effect[i].pos.x-60, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x-30, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x,    effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x+30, effect[i].pos.y+20}, 10, 0xFFFFFF},
						{{effect[i].pos.x+60, effect[i].pos.y+20}, 10, 0xFFFFFF}
					};
					//アニメーション値.
					int pow = _int(255 * CalcNumWaveLoop(1 - effect[i].counter/LEVEL_UP_ANIM_TIME));

					//描画.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					str.DrawStringST(TRUE, p_data->font2);
					DrawCircleST(&cir, FALSE, TRUE);
					DrawCircleST(&cirLevel[0], TRUE, TRUE); //●
					DrawCircleST(&cirLevel[1], TRUE, TRUE); //●
					DrawCircleST(&cirLevel[2], TRUE, TRUE); //●
					DrawCircleST(&cirLevel[3], TRUE, TRUE); //●
					DrawCircleST(&cirLevel[4], TRUE, TRUE); //●
					ResetDrawBlendMode();
				}
				break;

				default: assert(FALSE); break;
			}
		}
	}
}

//エフェクト出現.
void EffectManager::SpawnEffect(EffectData* data) {

	//未使用のエフェクトを探す.
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (!effect[i].active) {

			effect[i].type    = data->type;
			effect[i].pos     = data->pos;
			effect[i].vec     = data->vec;
			effect[i].speed   = data->speed;
			effect[i].ang     = data->ang;
			effect[i].len     = data->len;
			effect[i].counter = 0;         //0から開始. 
			effect[i].active  = TRUE;      //有効にする.

			break; //召喚完了.
		}
	}
}
//エフェクト消去.
void EffectManager::DeleteEffect(int idx) {

	effect[idx].active = FALSE;
}