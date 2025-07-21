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

			//カウンター加算.
			effect[i].counter++;
//			effect[i].counter += ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);

			//タイプ別.
			switch (effect[i].type) 
			{
				case Effect_Score100:
				{
					//時間経過で消滅.
					if (effect[i].counter >= SCORE_ANIM_TIME) {
						DeleteEffect(i);
					}
				}
				break;

				case Effect_Score500:
				{
					//時間経過で消滅.
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

	//有効なエフェクトのみ描画.
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (effect[i].active) {

			//タイプ別.
			switch (effect[i].type)
			{
				case Effect_Score100:
				{
					//テキスト設定.
					STR_DRAW str = { _T("+100"), {}, COLOR_SCORE };
					str.pos = { _int(effect[i].pos.x), _int(effect[i].pos.y - CalcNumEaseOut(effect[i].counter/SCORE_ANIM_TIME)*30)};
					//アニメーション値.
					int pow = 255 * CalcNumEaseOut(1 - effect[i].counter/SCORE_ANIM_TIME);

					//描画.
					SetDrawBlendModeST(MODE_ALPHA, pow);
					DrawStringST(&str, TRUE, p_data->font1);
					ResetDrawBlendMode();
				}
				break;

				case Effect_Score500:
				{
					//テキスト設定.
					STR_DRAW str = { _T("+500"), {}, COLOR_SCORE };
					str.pos = { _int(effect[i].pos.x), _int(effect[i].pos.y - CalcNumEaseOut(effect[i].counter/SCORE_ANIM_TIME)*30)};
					//アニメーション値.
					int pow = 255 * CalcNumEaseOut(1 - effect[i].counter/SCORE_ANIM_TIME);

					//描画.
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

//エフェクト出現.
void EffectManager::SpawnEffect(EffectType type, DBL_XY pos) {

	//未使用のエフェクトを探す.
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (!effect[i].active) {

			effect[i].type    = type;
			effect[i].pos     = pos; 
			effect[i].counter = 0;    //0から開始. 
			effect[i].active  = TRUE; //有効にする.
			break;                    //召喚完了.
		}
	}
}
//エフェクト消去.
void EffectManager::DeleteEffect(int idx) {

	effect[idx].active = FALSE;
}