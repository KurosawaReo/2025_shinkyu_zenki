/*
   - Obst_MeteorManager.cpp -

   障害物: 隕石出現管理.
*/
#include "GameManager.h"
#include "EffectManager.h"
#include "Obst_MeteorManager.h"

using namespace Calc; //計算機能を使用.

void MeteorManager::Init() {

	p_data      = &GameData::GetInst();
	p_player    = &Player::GetInst();
	p_effectMng = &EffectManager::GetInst();

	//全隕石ループ.
	for (int i = 0; i < METEOR_CNT_MAX; i++) {
		meteor[i].Init();
	}
}

void MeteorManager::Reset() {

	isSpawnAble = false; //許可が出されるまで召喚不可.

	timer = METEOR_SPAWN_SPAN; //初期時間.

	//全隕石ループ.
	for (int i = 0; i < METEOR_CNT_MAX; i++) {
		meteor[i].Reset();
	}
}

void MeteorManager::Update() {

	//召喚可能なら.
	if (isSpawnAble) {
		//タイマーが残っていれば.
		if (timer > 0) {
			timer -= p_data->speedRate;
		}
		//タイマーが0になったら.
		else {
			SpawnMeteor(); //隕石生成.
			timer = METEOR_SPAWN_SPAN * p_data->spawnRate; //タイマー再開(徐々に短くなる)
		}
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

#if defined	DEBUG_METEOR_SPAWN
	//隕石の目標地点範囲.
	SetDrawBlendModeKR(BlendModeID::Alpha, 100);
	Box box = {{WINDOW_WID/2, WINDOW_HEI/2}, {METEOR_GOAL_RAND_RANGE*2, METEOR_GOAL_RAND_RANGE*2}, 0xFFA0A0};
	DrawBoxKR(&box, Anchor::Mid);
	ResetDrawBlendMode();
#endif

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
			break;             //出現完了.
		}
	}
}

//隕石のどれか1つでも当たっているか.
bool MeteorManager::IsHitMeteors(Circle cir, bool isDestroy) {

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
					p_data->score += SCORE_BREAK_METEOR; //スコア加算.
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

			DBL_XY tmpPos = meteor[i].GetPos();          //1つずつ座標取得.
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