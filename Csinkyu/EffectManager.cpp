/*
   - EffectManager.cpp -
   エフェクトを管理するクラス.
*/
#include "EffectManager.h"

//依存関係.
#include "GameData.h"
//参照
static GameData* gameData;

using namespace Calc; //計算機能を使用.

// ▼*---=[ EffectManager ]=---*▼ //

void EffectManager::Init() {
	gameData = ManagerInsts::Get<GameData>();
}

void EffectManager::Reset() {
	//エフェクトを全て消去.
	effect.clear();
}

void EffectManager::Update() {
	
	//ポーズ中の更新はしない.
	if (gameData->isPause) { return; }

	//全てのエフェクト.
	for (auto i = effect.begin(); i != effect.end(); ) {

		bool isErase = false; //消去するかどうか.

		//タイプ別.
		switch (i->type) 
		{
			case Effect_Score100:
			case Effect_Score500:
			{
				i->counter++;

				//時間経過で消滅.
				if (i->counter >= SCORE_ANIM_TIME) {
					isErase = true;
				}
			}
			break;

			case Effect_PlayerDeath:
			{
				i->counter++;

				//時間経過で消滅.
				if (i->counter >= PLAYER_DEATH_ANIM_TIME) {
					isErase = true;
				}
			}
			break;

			case Effect_Reflect:
			case Effect_ReflectSpark:
			{
				i->counter++;

				//時間経過で消滅.
				if (i->counter >= LASER_REF_ANIM_TIME) {
					isErase = true;
				}
			}
			break;

			case Effect_MeteorCrash:
			{
				//カウンター加算.
				i->counter += gameData->speedRate;
				//時間経過で消滅.
				if (i->counter >= METEOR_BREAK_ANIM_TIME) {
					isErase = true;
				}
			}
			break;

			case Effect_MeteorFragment:
			{
				//カウンター加算.
				i->counter += gameData->speedRate;
				//回転.
				i->ang += 3 * gameData->speedRate;
				//減速.
				float newSpeed = i->speed/(1+(i->counter/10));
				//移動.
				i->pos.x += i->vec.x * newSpeed * gameData->speedRate;
				i->pos.y += i->vec.y * newSpeed * gameData->speedRate;

				//時間経過で消滅.
				if (i->counter >= METEOR_BREAK_ANIM_TIME) {
					isErase = true;
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
				i->counter++;

				//時間経過で消滅.
				if (i->counter >= MIDDLE_ANIM_TIME) {
					isErase = true;
				}
			}
			break;

			default: assert(FALSE); break;
		}

		//次の要素に進む.
		if (isErase) {
			i = effect.erase(i); //消去して次へ.
		}
		else {
			i++;
		}
	}
}

void EffectManager::Draw() {

#if defined DEBUG_OBJ_ACTIVE
	//デバッグ表示.
	DrawFormatString(0, 80, 0xFF00FF, _T("エフェクト　　 : %d"), effect.size());
#endif

	//全てのエフェクト.
	for (const auto& i : effect) {

		//タイプ別.　
		switch (i.type)
		{
			case Effect_Score100:
			case Effect_Score500:
			{
				//座標.
				DBL_XY pos = {i.pos.x, i.pos.y - AnimEase(EaseType::OutQuad, i.counter/SCORE_ANIM_TIME)*30};
				//描画.
				const int pow = _int_r(255 * AnimEase(EaseType::OutQuad, 1 - i.counter/SCORE_ANIM_TIME)); //透明度.
				DrawMode::Exe(
					DrawModeID::None, DrawBlendModeID::Alpha, pow,
					[&]() {
						//画像切り替え.
						if (i.type == Effect_Score100) {
							GraphMng::Get(_T("score100"))->DrawExtend(pos, { 0.2, 0.2 });
						}
						else {
							GraphMng::Get(_T("score500"))->DrawExtend(pos, { 0.2, 0.2 });
						}
					}
				);
			}
			break;

			case Effect_PlayerDeath:
			{
				Circle cir = { i.pos, PLAYER_SIZE+i.counter/2, 0xFFFFFF, 1.0f };
				
				//描画.
				const int pow = _int_r(255 * AnimEase(EaseType::OutQuad, 1 - i.counter/PLAYER_DEATH_ANIM_TIME)); //透明度.
				DrawMode::Exe(
					DrawModeID::None, DrawBlendModeID::Alpha, pow,
					[&]() {
						DrawCircleKR(cir, Anchor::Mid, false, true);
					}
				);
			}
			break;

			case Effect_Reflect:
			{
				Circle cir = { i.pos, _flt(5+i.counter*2), COLOR_PLY_REFLECT, 1.0f };
				//描画.
				const int pow = _int_r(255 * AnimEase(EaseType::OutQuad, 1 - i.counter/LASER_REF_ANIM_TIME)); //透明度.
				DrawMode::Exe(
					DrawModeID::None, DrawBlendModeID::Alpha, pow,
					[&]() {
						DrawCircleKR(cir, Anchor::Mid, false, true);
					}
				);
			}
			break;

			case Effect_ReflectSpark:
			{
				Circle cir = { i.pos, _flt(5 + i.counter * 2), COLOR_PLY_REFLECT, 1.0f };
				//描画.
				const int pow = _int_r(255 * AnimEase(EaseType::OutQuad, 1 - i.counter / LASER_REF_ANIM_TIME)); //透明度.
				DrawMode::Exe(
					DrawModeID::None, DrawBlendModeID::Alpha, pow,
					[&]() {
						DrawCircleKR(cir, Anchor::Mid, false, true);
					}
				);
			}
			break;

			case Effect_MeteorCrash:
			{
				Circle cir = { i.pos, i.counter, COLOR_METEOR(i.pos), 1.0f };
				//描画.
				const int pow = _int_r(255 * AnimEase(EaseType::OutQuad, 1 - i.counter/METEOR_BREAK_ANIM_TIME)); //透明度.
				DrawMode::Exe(
					DrawModeID::None, DrawBlendModeID::Alpha, pow,
					[&]() {
						DrawCircleKR(cir, Anchor::Mid, false, true);
					}
				);
			}
			break;

			case Effect_MeteorFragment:
			{
				//飛ばす線のデータ.
				Line line{};
				line.stPos = ArcPos(i.pos, i.ang,     i.len);
				line.edPos = ArcPos(i.pos, i.ang+180, i.len);
			    line.color = COLOR_METEOR(i.pos);
				line.thick = 1;
				//描画.
				const int pow = _int_r(255 * AnimEase(EaseType::OutQuad, 1 - i.counter/METEOR_BREAK_ANIM_TIME)); //透明度.
				DrawMode::Exe(
					DrawModeID::None, DrawBlendModeID::Alpha, pow,
					[&]() {
						DrawLineKR(line, true);
					}
				);
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
				//共通設定.
				DrawStr str = { _T("Unknown"), {_int_r(i.pos.x), _int_r(i.pos.y-20)}, 0xFFFFFF};
				Circle mainCir = { i.pos, i.counter*5, 0xFFFFFF, 1.0f };
				Circle lampCir[5] = {
					{{-1, i.pos.y+20}, 10, 0xFFFFFF, 1.0f},
					{{-1, i.pos.y+20}, 10, 0xFFFFFF, 1.0f},
					{{-1, i.pos.y+20}, 10, 0xFFFFFF, 1.0f},
					{{-1, i.pos.y+20}, 10, 0xFFFFFF, 1.0f},
					{{-1, i.pos.y+20}, 10, 0xFFFFFF, 1.0f}
				};
				//アニメーション値.
				int pow = _int_r(255 * AnimWave(WaveType::CosLoop, 1 - i.counter/MIDDLE_ANIM_TIME));
				//何個ランプを使うか.
				int lampUseCnt  = 0;
				int lampFillCnt = 0;

				switch (i.type)
				{
					case Effect_Endless_Level1:
						str.text = _T("Level 1");
						lampUseCnt = 5;
						lampFillCnt = 1;
						break;
					case Effect_Endless_Level2:
						str.text = _T("Level 2");
						lampUseCnt = 5;
						lampFillCnt = 2;
						break;
					case Effect_Endless_Level3:
						str.text = _T("Level 3");
						lampUseCnt = 5;
						lampFillCnt = 3;
						break;
					case Effect_Endless_Level4:
						str.text = _T("Level 4");
						lampUseCnt = 5;
						lampFillCnt = 4;
						break;
					case Effect_Endless_Level5:
						str.text = _T("Level 5");
						lampUseCnt = 5;
						lampFillCnt = 5;
						break;

					case Effect_Tutorial_Step1:
						str.text = _T("Step 1");
						lampUseCnt = 4;
						lampFillCnt = 1;
						break;
					case Effect_Tutorial_Step2:
						str.text = _T("Step 2");
						lampUseCnt = 4;
						lampFillCnt = 2;
						break;
					case Effect_Tutorial_Step3:
						str.text = _T("Step 3");
						lampUseCnt = 4;
						lampFillCnt = 3;
						break;
					case Effect_Tutorial_Step4:
						str.text = _T("Step 4");
						lampUseCnt = 4;
						lampFillCnt = 4;
						break;
				}

				//描画.
				DrawMode::Exe(
					DrawModeID::None, DrawBlendModeID::Alpha, pow,
					[&]() {

						//円.
						DrawCircleKR(mainCir, Anchor::Mid, false, true);
						//テキスト.					
						str.Draw(Anchor::Mid, gameData->fonts["en-size3"].GetFont());

						//ランプ(必要な数だけ)
						for (int j = 0; j < lampUseCnt; j++) {
							//均等になるように配置する.
							const int interval = 30; //間隔.
							lampCir[j].pos.x = i.pos.x + interval * (j - _flt(lampUseCnt - 1) / 2);
							DrawCircleKR(lampCir[j], Anchor::Mid, (lampFillCnt >= j + 1), true);
						}
					}
				);
			}
			break;

			default: assert(FALSE); break;
		}
	}
}

//エフェクト出現.
void EffectManager::SpawnEffect(const EffectData* data) {

	Effect tmp; //エフェクト作成.

	tmp.type  = data->type;
	tmp.pos   = data->pos;
	tmp.vec   = data->vec;
	tmp.speed = data->speed;
	tmp.ang   = data->ang;
	tmp.len   = data->len;
	tmp.counter = 0;       //0から開始.

	effect.push_back(tmp); //listに追加.
}