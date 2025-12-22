/*
   - Obst_MeteorManager.cpp -

   障害物: 隕石出現管理.
*/
#include "Obst_MeteorManager.h"

//依存関係.
#include "GameData.h"
#include "GameManager.h"
#include "EffectManager.h"
//参照.
GameData&      p_data      = GameData::GetInst();
Player&        p_player    = Player::GetInst();
EffectManager& p_effectMng = EffectManager::GetInst();

void MeteorManager::Init() {

}

void MeteorManager::Reset() {

	isSpawnAble = false;             //許可が出されるまで召喚不可.
	timer       = METEOR_SPAWN_SPAN; //初期時間.

	//隕石を全て消去.
	meteor.clear();
}

void MeteorManager::Update() {

	//召喚可能なら.
	if (isSpawnAble) {
		//タイマーが残っていれば.
		if (timer > 0) {
			timer -= p_data.speedRate;
		}
		//タイマーが0になったら.
		else {
			SpawnMeteor(); //隕石生成.
			timer = METEOR_SPAWN_SPAN * p_data.spawnRate; //タイマー再開(徐々に短くなる)
		}
	}

	//全隕石ループ.
	for (auto i = meteor.begin(); i != meteor.end(); ) {
		i->Update(); //更新.
		//次の要素へ.
		if (i->GetIsErase()) {
			i = meteor.erase(i);
		}
		else{
			i++;
		}
	}
	//プレイヤーとの当たり判定.
	if (IsHitMeteors(p_player.GetHit(), false)) {
		p_player.PlayerDeath(); //死亡.
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

#if defined DEBUG_OBJ_ACTIVE
	//デバッグ表示.
	DrawFormatString(0, 140, 0xFF00FF, _T("隕石　　　　　 : %d"), meteor.size());
#endif

	//全隕石ループ.
	for (auto& i : meteor) {
		i.Draw(); //描画.
	}
}

//隕石生成.
void MeteorManager::SpawnMeteor(){
	
	Meteor tmp;
	tmp.Init();  //初期化.
	tmp.Spawn(); //スポーン処理.
	meteor.push_back(tmp);
}

//隕石のどれか1つでも当たっているか.
bool MeteorManager::IsHitMeteors(Circle cir, bool isDestroy) {

	bool hit;

	//全隕石ループ.
	for (auto& i : meteor) {
		hit = i.IsHitMeteor(cir); //1こずつ判定.
		//当たれば.
		if (hit) {
			if (isDestroy) {
				//壊れてない隕石であれば.
				if (i.GetState() == Meteor_Normal) {
					i.Destroy();						 //隕石を破壊.
					p_data.score += SCORE_BREAK_METEOR; //スコア加算.
				}
			}
			return true; //1つでも当たっている.
		}
	}
	return false; //どれも当たっていない.
}

//最寄りの隕石座標を探す.
bool MeteorManager::GetMeteorPosNearest(DBL_XY _startPos, DBL_XY* _nearPos) {

	bool   isExistMeteo = false; //1つでも隕石があるか.
	double shortest     = -1;    //暫定の最短距離.

	//全隕石ループ.
	for (const auto& i : meteor) {
		//破壊されてないなら.
		if (i.GetState() == Meteor_Normal) {

			DBL_XY tmpPos = i.GetPos();                    //1つずつ座標取得.
			double tmpDis = Calc::Dist(tmpPos, _startPos); //距離を計算.

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