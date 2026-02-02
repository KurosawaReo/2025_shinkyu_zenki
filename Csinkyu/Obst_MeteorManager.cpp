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
static GameData&      gameData  = GameData::GetInst();
static Player&        player    = Player::GetInst();
static EffectManager& effectMng = EffectManager::GetInst();

// ▼*---=[ MeteorManager ]=---*▼ //

MeteorManager MeteorManager::inst;

//範囲内の隕石を取得(1つ)
Meteor* MeteorManager::GetHitMeteor(Circle cir, bool isDestroy) {

	//全隕石ループ.
	for (auto& i : meteor) {
		if (i.IsHitMeteor(cir)) {
			return &i; //この隕石を返す.
		}
	}
	return nullptr; //隕石はない.
}
//最寄りの隕石を取得.
Meteor* MeteorManager::GetNearestMeteor(DBL_XY pos) {

	Meteor* ret = nullptr; //最寄りの隕石.
	double shortest = -1;  //暫定の最短距離.

	//全隕石ループ.
	for (auto& i : meteor) {
		//破壊されてないなら.
		if (i.GetState() == Meteor_Normal) {

			DBL_XY tmpPos = i.GetPos();              //1つずつ座標取得.
			double tmpDis = Calc::Dist(tmpPos, pos); //距離を計算.

			//初回限定.
			if (shortest == -1) {
				shortest = tmpDis; //暫定1位.
				ret = &i;
			}
			//より近い場所が見つかれば更新.
			else if (tmpDis < shortest) {
				shortest = tmpDis;
				ret = &i;
			}
		}
	}

	return ret;
}

void MeteorManager::Init() {

}

void MeteorManager::Reset() {

	//自動実行設定.
	SetAutoExeMode(MngAutoExe::Stop);

	timer = METEOR_SPAWN_SPAN; //初期時間.
	meteor.clear();            //隕石を全て消去.
}

void MeteorManager::Update() {

	//タイマーが残っていれば.
	if (timer > 0) {
		timer -= gameData.speedRate;
	}
	//タイマーが0になったら.
	else {
		SpawnMeteor(); //隕石生成.
		timer = METEOR_SPAWN_SPAN * gameData.spawnRate; //タイマー再開(徐々に短くなる)
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
	if (GetHitMeteor(player.GetHit(), false)) {
		player.PlayerDeath(); //死亡.
	}
}

void MeteorManager::Draw() {

#if defined	DEBUG_METEOR_SPAWN
	//隕石の目標地点範囲.
	{
		DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 100);

		Box box = {{WINDOW_WID/2, WINDOW_HEI/2}, {METEOR_GOAL_RAND_RANGE*2, METEOR_GOAL_RAND_RANGE*2}, 0xFFA0A0};
		DrawBoxKR(&box, Anchor::Mid);
	}
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
//隕石破壊演出.
void MeteorManager::BreakMeteor(DBL_XY pos, double ang, bool isScore, double scale) {
	
	//エフェクトデータ.
	EffectData data{};
	data.type = Effect_BreakMeteor;
	data.pos  = pos;
	//いくつか出す.
	for (int i = 0; i < METEOR_BREAK_ANIM_CNT; i++) {

		double newDig = ang + _flt(Calc::RandNum(-300, 300)) / 10;	//少し角度をずらす.
		data.vec   = Calc::VectorDeg(newDig);						//ずらした角度を反映.
		data.speed = _flt(Calc::RandNum(50, 300) / 10 * scale);		//速度抽選.
		data.len   = _flt(Calc::RandNum(10, 100) / 10 * scale);		//長さ抽選.
		data.ang   = _flt(Calc::RandNum(0, 3599) / 10);				//角度抽選.
		effectMng.SpawnEffect(&data);								//エフェクト出現.
	}
	//スコアエフェクト.
	if (isScore) {
		data.type = Effect_Score500;
		effectMng.SpawnEffect(&data); //エフェクト出現.
	}
	//サウンド.
	if (auto i = SoundMng::Get("Break")) {
		i->Play(false, 74); //再生.
	}
}