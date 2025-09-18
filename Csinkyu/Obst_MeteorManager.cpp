/*
   - Obst_MeteorManager.cpp -

   障害物: 隕石出現管理.
*/
#include "GameManager.h"
#include "EffectManager.h"
#include "Obst_MeteorManager.h"

using namespace Calc; //計算機能を使用.

void MeteorManager::Init() {

	p_data      = GameData::GetPtr();
	p_player    = Player::GetPtr();
	p_effectMng = EffectManager::GetPtr();

	//全隕石ループ.
	for (int i = 0; i < METEOR_CNT_MAX; i++) {
		meteor[i].Init();
	}
}

void MeteorManager::Reset() {

	timer = METEOR_SPAWN_SPAN; //初期時間.

	//全隕石ループ.
	for (int i = 0; i < METEOR_CNT_MAX; i++) {
		meteor[i].Reset();
	}
}

void MeteorManager::Update() {

	//タイマーが残っていれば.
	if (timer > 0) {
		timer -= (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
	}
	//タイマーが0になったら.
	else {
		SpawnMeteor(); //隕石生成.
		timer = METEOR_SPAWN_SPAN * p_data->spawnRate; //タイマー再開(徐々に短くなる)
	}

	//全隕石ループ.
	for (int i = 0; i < METEOR_CNT_MAX; i++) {
		meteor[i].Update(); //更新.
	}
	//プレイヤーとの当たり判定.
	if (IsHitMeteors(p_player->GetHit(), false)) {
		p_player->PlayerDeath(); //死亡.
	}
}

void MeteorManager::Draw() {

	//全隕石ループ.
	for (int i = 0; i < METEOR_CNT_MAX; i++) {
		meteor[i].Draw(); //描画.
	}
}

//隕石生成.
void MeteorManager::SpawnMeteor(){
	
	//空いてる所を探す.
	for (int i = 0; i < METEOR_CNT_MAX; i++) {
		if (!meteor[i].GetActive()) {

			meteor[i].Spawn(); //出現.
			break;            //出現完了.
		}
	}
}

//隕石のどれか1つでも当たっているか.
bool MeteorManager::IsHitMeteors(Circle* cir, bool isDestroy) {

	bool hit;

	//全隕石ループ.
	for (int i = 0; i < METEOR_CNT_MAX; i++) {
		hit = meteor[i].IsHitMeteor(cir); //1こずつ判定.
		//当たれば.
		if (hit) {
			if (isDestroy) {
				//壊れてない隕石であれば.
				if (meteor[i].GetState() == Meteor_Normal) {

					meteor[i].Destroy();                 //隕石を破壊.
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
bool MeteorManager::GetMeteorPosNearest(DBL_XY _startPos, DBL_XY* _nearPos) {

	bool isExistMeteo = false; //1つでも隕石があるか.
	double shortest = -1; //暫定の最短距離.

	//全隕石ループ.
	for (int i = 0; i < METEOR_CNT_MAX; i++) {
		//有効かつ、破壊されてないなら.
		if (meteor[i].GetActive() && meteor[i].GetState() == Meteor_Normal) {

			DBL_XY tmpPos = meteor[i].GetPos();           //1つずつ座標取得.
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