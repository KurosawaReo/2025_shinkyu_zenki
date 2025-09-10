/*
   - MeteoManager.cpp -
   隕石の出現を管理する.
*/
#include "MeteoManager.h"

using namespace Calc; //計算機能を使用.

void MeteoManager::Init(GameData* _data, Player* _player, EffectManager* _effectMng) {

	p_data      = _data;
	p_player    = _player;
	p_effectMng = _effectMng;

	//全隕石ループ.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		meteo[i].Init(_data);
	}
}

void MeteoManager::Reset() {

	timer = METEO_SPAWN_SPAN; //初期時間.

	//全隕石ループ.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		meteo[i].Reset();
	}
}

void MeteoManager::Update() {

	//タイマーが残っていれば.
	if (timer > 0) {
		timer -= (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
	}
	//タイマーが0になったら.
	else {
		SpawnMeteo(); //隕石生成.
		timer = METEO_SPAWN_SPAN * p_data->spawnRate; //タイマー再開(徐々に短くなる)
	}

	//全隕石ループ.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		meteo[i].Update(); //更新.
	}
	//プレイヤーとの当たり判定.
	if (IsHitMeteos(p_player->GetHit(), false)) {
		p_player->PlayerDeath(); //死亡.
	}
}

void MeteoManager::Draw() {

	//全隕石ループ.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		meteo[i].Draw(); //描画.
	}
}

//隕石生成.
void MeteoManager::SpawnMeteo(){

	//空いてる所を探す.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		if (!meteo[i].GetActive()) {

			meteo[i].Spawn(); //出現.
			break;            //出現完了.
		}
	}
}

//隕石のどれか1つでも当たっているか.
bool MeteoManager::IsHitMeteos(Circle* cir, bool isDestroy) {

	bool hit;

	//全隕石ループ.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		hit = meteo[i].IsHitMeteo(cir); //1こずつ判定.
		//当たれば.
		if (hit) {
			if (isDestroy) {
				//壊れてない隕石であれば.
				if (meteo[i].GetState() == Meteo_Normal) {

					meteo[i].Destroy();                 //隕石を破壊.
					p_data->score += SCORE_BREAK_METEO; //スコア加算.

					//エフェクト.
					EffectData data{};
					data.type = Effect_Score500;
					data.pos = cir->pos;
					p_effectMng->SpawnEffect(&data);
					//サウンド.
					SoundMng* sound = SoundMng::GetPtr();
					sound->Play(_T("Break"), false, 74);
				}
			}
			return true; //1つでも当たっている.
		}
	}
	return false; //どれも当たっていない.
}

//最寄りの隕石座標を探す.
bool MeteoManager::GetMeteoPosNearest(DBL_XY _startPos, DBL_XY* _nearPos) {

	bool isExistMeteo = false; //1つでも隕石があるか.
	double shortest = -1; //暫定の最短距離.

	//全隕石ループ.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		//有効かつ、破壊されてないなら.
		if (meteo[i].GetActive() && meteo[i].GetState() == Meteo_Normal) {

			DBL_XY tmpPos = meteo[i].GetPos();           //1つずつ座標取得.
			double tmpDis = CalcDist(tmpPos, _startPos); //距離を計算.

			//初回限定.
			if (shortest == -1) {
				shortest  = tmpDis; //暫定1位.
				*_nearPos = tmpPos;
			}
			//より近い場所が見つかれば更新.
			else if (tmpDis < shortest){
				shortest  = tmpDis;
				*_nearPos = tmpPos;
			}

			isExistMeteo = true; //隕石がある.
		}
	}

	return isExistMeteo;
}