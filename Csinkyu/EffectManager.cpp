/*
   - EffectManager.cpp -
   エフェクトを管理するクラス.
*/
#include "GameManager.h"
#include "EffectManager.h"

using namespace Calc; //計算機能を使用.

void EffectManager::Init(GameData* _data) {
	p_data = _data;

	imgScore[0].LoadFile(_T("Resources/Images/score100.png"));
	imgScore[1].LoadFile(_T("Resources/Images/score500.png"));
}

void EffectManager::Reset() {
	//全てのエフェクトをリセット.
	for (int i = 0; i < EFFECT_MAX; i++) {
		effect[i].active = false;
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
					//座標.
					DBL_XY pos = {effect[i].pos.x, effect[i].pos.y - CalcNumEaseOut(effect[i].counter/SCORE_ANIM_TIME)*30};
					//アニメーション値.
					int pow = _int_r(255 * CalcNumEaseOut(1 - effect[i].counter/SCORE_ANIM_TIME));

					//描画.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					imgScore[0].DrawExtend(pos, {0.2, 0.2});
					ResetDrawBlendMode();
				}
				break;

				case Effect_Score500:
				{
  				    //座標.
					DBL_XY pos = { effect[i].pos.x, effect[i].pos.y - CalcNumEaseOut(effect[i].counter / SCORE_ANIM_TIME) * 30 };
					//アニメーション値.
					int pow = _int_r(255 * CalcNumEaseOut(1 - effect[i].counter/SCORE_ANIM_TIME));

					//描画.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					imgScore[1].DrawExtend(pos, {0.2, 0.2});
					ResetDrawBlendMode();
				}
				break;

				case Effect_PlayerDeath:
				{
					Box box = { effect[i].pos, { PLAYER_SIZE+effect[i].counter, PLAYER_SIZE+effect[i].counter }, 0xFFFFFF };
					//アニメーション値.
					int pow = _int_r(255 * CalcNumEaseOut(1 - effect[i].counter/PLAYER_DEATH_ANIM_TIME));

					//描画.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					DrawBoxST(&box, ANC_MID, false, true);
					ResetDrawBlendMode();
				}
				break;

				case Effect_ReflectLaser:
				{
					Box box = { effect[i].pos, { 10+effect[i].counter*4, 10+effect[i].counter*4 }, COLOR_PLY_REFLECT };
					//アニメーション値.
					int pow = _int_r(255 * CalcNumEaseOut(1 - effect[i].counter/LASER_REF_ANIM_TIME));

					//描画.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					DrawBoxST(&box, ANC_MID, false, true);
					ResetDrawBlendMode();
				}
				break;

				case Effect_BreakMeteo:
				{
					//飛ばす線のデータ.
					Line line{};
					line.stPos = CalcArcPos(effect[i].pos, effect[i].ang,     effect[i].len);
					line.edPos = CalcArcPos(effect[i].pos, effect[i].ang+180, effect[i].len);
			        line.color = COLOR_METEO(effect[i].pos);
					//アニメーション値.
					int pow = _int_r(255 * CalcNumEaseOut(1 - effect[i].counter/METEO_BREAK_ANIM_TIME));

					//描画.
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
					//アニメーション値.
					int pow = _int_r(255 * CalcNumWaveLoop(1 - effect[i].counter/LEVEL_UP_ANIM_TIME));

					//描画.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					str.Draw(ANC_MID, p_data->font2);
					DrawCircleST(&cir, false, true);
					DrawCircleST(&cirLevel[0], true,  true); //●
					DrawCircleST(&cirLevel[1], false, true); //○
					DrawCircleST(&cirLevel[2], false, true); //○
					DrawCircleST(&cirLevel[3], false, true); //○
					DrawCircleST(&cirLevel[4], false, true); //○
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
					//アニメーション値.
					int pow = _int(255 * CalcNumWaveLoop(1 - effect[i].counter/LEVEL_UP_ANIM_TIME));

					//描画.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					str.Draw(ANC_MID, p_data->font2);
					DrawCircleST(&cir, false, true);
					DrawCircleST(&cirLevel[0], true,  true); //●
					DrawCircleST(&cirLevel[1], true,  true); //●
					DrawCircleST(&cirLevel[2], false, true); //○
					DrawCircleST(&cirLevel[3], false, true); //○
					DrawCircleST(&cirLevel[4], false, true); //○
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
					//アニメーション値.
					int pow = _int_r(255 * CalcNumWaveLoop(1 - effect[i].counter/LEVEL_UP_ANIM_TIME));

					//描画.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					str.Draw(ANC_MID, p_data->font2);
					DrawCircleST(&cir, false, true);
					DrawCircleST(&cirLevel[0], true,  true); //●
					DrawCircleST(&cirLevel[1], true,  true); //●
					DrawCircleST(&cirLevel[2], true,  true); //●
					DrawCircleST(&cirLevel[3], false, true); //○
					DrawCircleST(&cirLevel[4], false, true); //○
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
					//アニメーション値.
					int pow = _int_r(255 * CalcNumWaveLoop(1 - effect[i].counter/LEVEL_UP_ANIM_TIME));

					//描画.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					str.Draw(ANC_MID, p_data->font2);
					DrawCircleST(&cir, false, true);
					DrawCircleST(&cirLevel[0], true,  true); //●
					DrawCircleST(&cirLevel[1], true,  true); //●
					DrawCircleST(&cirLevel[2], true,  true); //●
					DrawCircleST(&cirLevel[3], true,  true); //●
					DrawCircleST(&cirLevel[4], false, true); //○
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
					//アニメーション値.
					int pow = _int_r(255 * CalcNumWaveLoop(1 - effect[i].counter/LEVEL_UP_ANIM_TIME));

					//描画.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					str.Draw(ANC_MID, p_data->font2);
					DrawCircleST(&cir, false, true);
					DrawCircleST(&cirLevel[0], true, true); //●
					DrawCircleST(&cirLevel[1], true, true); //●
					DrawCircleST(&cirLevel[2], true, true); //●
					DrawCircleST(&cirLevel[3], true, true); //●
					DrawCircleST(&cirLevel[4], true, true); //●
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
			effect[i].active  = true;      //有効にする.

			break; //召喚完了.
		}
	}
}
//エフェクト消去.
void EffectManager::DeleteEffect(int idx) {

	effect[idx].active = false;
}