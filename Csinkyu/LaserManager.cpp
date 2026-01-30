/*
   - LaserManager.cpp -
   レーザー管理クラス.
*/
#include "LaserManager.h"

//依存関係.
#include "Player.h"
#include "Obst_MeteorManager.h"
#include "Stage_Tutorial.h"
#include "GameData.h"
//参照.
static GameData&      gameData  = GameData::GetInst();
static Player&        player    = Player::GetInst();
static MeteorManager& meteorMng = MeteorManager::GetInst();
static EffectManager& effectMng = EffectManager::GetInst();

using namespace Calc; //計算機能を使用.

// ▼*---=[ LaserManager ]=---*▼ //

LaserManager LaserManager::inst;

//初期化.
void LaserManager::Init() {

}
//リセット.
void LaserManager::Reset() {

	//レーザーを全て消去.
	laser.clear();
	//レーザー描画線を全て消去.
	line.clear();
}
//更新.
void LaserManager::Update() {

	plyPos = player.GetPos(); //プレイヤーの現在位置を取得.

	UpdateLaser();     //各レーザーの更新.
	UpdateLaserLine(); //各レーザー描画線の更新.
}
//描画.
void LaserManager::Draw() {

#if defined DEBUG_OBJ_ACTIVE
	//デバッグ表示.
	DrawFormatString(0, 100, 0xFF00FF, _T("レーザー　　　 : %d"), laser.size());
	DrawFormatString(0, 120, 0xFF00FF, _T("レーザー描画線 : %d"), line.size());
#endif

	//レーザー描画線.
	for (const LaserLineData& i : line) 
	{
		//時間経過で徐々に薄くする.
		int color = _int_r(255 * (1 - i.counter/LASER_LINE_DEL_TIME));
		color = max(color, 0); //最低値を0にする.

		//軌跡の線設定.
		Line tmpLine = { i.pos1, i.pos2, {} };
		//線の色(時間経過で色が変化)
		switch (i.type)
		{
			case Laser_Normal:       tmpLine.color = GetColor(50, color, 255);      break;
			case Laser_Straight:     tmpLine.color = GetColor(50, color, 255);      break;
			case Laser_Reflect:      tmpLine.color = GetColor(color/2+128, 0, 255); break;
			case Laser_SuperReflect: tmpLine.color = GetColor(color/2+128, 0, 255); break;
			case Laser_Falling:      tmpLine.color = GetColor(50, color, 255);      break;

			default: assert(FALSE); break;
		}
		//加算合成モードで軌跡を描画(発光エフェクト)
		{
			DrawMode _(DrawModeID::None, DrawBlendModeID::Add, color);
			DrawLineKR(tmpLine, true, 2);
		}
	}

	//チュートリアル限定.
	if (gameData.stage == Stage_Tutorial) {
		//レーザー本体.
		for (const LaserData& i : laser)
		{
			UINT color{};

			//色を指定.
			switch (i.type)
			{
				case Laser_Normal:
				case Laser_Straight:
				case Laser_Falling:
					color = GetColor(50, 255, 255); //色の設定.
					break;
				case Laser_Reflect:
				case Laser_SuperReflect:
					color = GetColor(255, 0, 255); //色の設定.
					break;

				default: assert(FALSE); break;
			}

			//有効なレーザーに表示する.
			DrawStr str(_T("レーザー"), i.nowPos.ToInt(), color);
			str.Draw();
		}
	}
}

//各レーザーの更新.
void LaserManager::UpdateLaser() {

	//各レーザーの更新.
	for (auto i = laser.begin(); i != laser.end(); )
	{
		bool isErase = false; //消去するかどうか.

		//レーザータイプ別.
		switch (i->type)
		{
			case Laser_Normal:
			{
				//レーザーの当たり判定.
				if (HitLaser(i)) {
					bool isErase = true;
				}
				
				//速度(時間経過で速くなる)
				const double speed = i->counter * LASER_NOR_SPEED * gameData.speedRate;
				//レーザーの移動.
				i->nowPos += i->vec * speed;
			}
			break;

			case Laser_Straight:
			{
				//レーザーの当たり判定.
				if (HitLaser(i)) {
					bool isErase = true;
				}

				//速度(直線レーザーなので一定速度)
				const double speed = LASER_STR_SPEED * gameData.speedRate;
				//レーザーの移動.
				i->nowPos += i->vec * speed;
			}
			break;

			case Laser_Falling:
			{
				//ある程度薄くなるまで.
				if (i->counter <= LASER_FAL_HIT_ABLE) {
					//レーザーの当たり判定.
					if (HitLaser(i)) {
						bool isErase = true;
					}
				}

				// 重力効果を適用（下向きの加速度）
				const double gravity = 0.08 * gameData.speedRate;
				i->vec.y += gravity;

				// 空気抵抗効果（水平方向の速度を徐々に減少）
				const double airResistance = 0.995;
				i->vec.x *= airResistance;

				// 速度制限（落下速度が速くなりすぎないように）
				const double maxSpeed = 8.0;
				if (i->vec.y > maxSpeed) {
					i->vec.y = maxSpeed;
				}

				// レーザーの移動
				i->nowPos += i->vec * gameData.speedRate;

				//時間を超えたら.
				if (i->counter >= LASER_FAL_DEL_TIME) {
					isErase = true; //消去する.
				}
			}
			break;

			case Laser_Reflect:
			case Laser_SuperReflect:
			{
				//一定時間で目標地点を決める.
				if (i->counter >= LASER_REF_TRACK_ST_TM) {

					//最寄りの隕石を取得する.
					const DBL_XY  laserPos = i->nowPos; //レーザーの現在位置.
					const Meteor* meteor   = meteorMng.GetNearestMeteor(laserPos);
					//隕石があった場合.
					if (meteor) {
						i->goalPos  = meteor->GetPos(); //座標登録.
						i->isGoGoal = true;
					}
				}

				Circle hit = { i->nowPos, 10, {} }; //当たり判定円(仮)

				//隕石と当たっているなら.
				if (auto meteor = meteorMng.GetHitMeteor(hit, true)) {

					//壊れてない隕石であれば.
					if (meteor->GetState() == Meteor_Normal) {
						meteor->Destroy(); //隕石を破壊.
					}

					const double ang = _deg(atan2(i->vec.y, i->vec.x)); //破片の飛ぶ方向.
					meteorMng.BreakMeteor(i->nowPos, ang); //破壊演出.
					gameData.score += SCORE_BREAK_METEOR;  //スコア加算.

					//どっちのタイプかで切り替え.
					if (i->type == Laser_Reflect) {
						isErase = true; //消去する.
					}
					else {
						i->counter = LASER_REF_TRACK_ED_TM; //再反射後は追尾しない.
						ReflectLaser(i); //再反射.
					}
					//チュートリアルなら指示送信.
					if (gameData.stage == Stage_Tutorial) {
						TutorialStage::GetInst().SetBreakMeteor(true);
					}
				}
				else {
					//レーザーの追尾処理.
					LaserRefTracking(i);

					//速度(時間経過で速くなる)
					const double speed = i->counter * LASER_REF_SPEED * gameData.speedRate;
					//レーザーの移動.
					i->nowPos += i->vec * speed;
				}
			}
			break;

			//想定外の値エラー.
			default: assert(false); break;
		}

		//画面外判定.
		const bool isOutX = (i->nowPos.x < -100) || (i->nowPos.x > WINDOW_WID + 100);
		const bool isOutY = (i->nowPos.y < -100) || (i->nowPos.y > WINDOW_HEI + 100);
		//画面外に出たレーザーを無効化.
		if (isOutX || isOutY) {
			isErase = true; //消去する.
		}

		//次の要素に進む.
		if (isErase) {
			i = laser.erase(i); //消去して次へ.
		}
		else {
			GenerateLaserLine(i);           //レーザー描画線の生成.
			i->counter += gameData.speedRate; //経過カウンター.
			i++;
		}
	}
}
//各レーザー描画線の更新.
void LaserManager::UpdateLaserLine() {

	for (auto i = line.begin(); i != line.end(); ) {

		//経過時間カウンタ増加.
		i->counter += gameData.speedRate;
		//一定フレーム経過したら消去.
		if (i->counter >= LASER_LINE_DEL_TIME) {
			i = line.erase(i);
		}
		else {
			i++;
		}
	}
}

//レーザー召喚.
void LaserManager::SpawnLaser(DBL_XY pos, DBL_XY vel, LaserType type) {

	LaserData tmp;			//レーザー作成.

	tmp.nowPos   = pos;		//初期座標.
	tmp.befPos   = pos;		//初期座標.
	tmp.vec      = vel;		//初期方向.
	tmp.counter  = 0;		//経過時間カウンタ初期化
	tmp.logNum   = 0;		//軌跡カウンタ初期化
	tmp.type     = type;	//タイプの登録

	tmp.isGoGoal = false;
	tmp.goalPos  = {0, 0};

	laser.push_back(tmp); //listに追加.

	//サウンド.
	if (type == Laser_Normal) {
		if (auto i = SoundMng::Get("Laser1")) {
			i->Play(false, 58); //通常レーザー.
		}
	}
	if (type == Laser_Straight) {
		if (auto i = SoundMng::Get("Laser2")) {
			i->Play(false, 60); //直線レーザー.
		}
	}
	if (type == Laser_Falling) {
		if (auto i = SoundMng::Get("Laser1")) {
			i->Play(false, 45); //落下レーザー（少し音量小さめ）.
		}
	}
}

//レーザーの当たり判定.
bool LaserManager::HitLaser(list<LaserData>::iterator it) {

	//プレイヤー当たり判定.
	Circle plyHit = player.GetHit();
	//反射モードならサイズを大きくする.
	if (player.GetMode() == Player_Reflect     || 
		player.GetMode() == Player_SuperReflect) 
	{
		plyHit.r += PLAYER_REF_ADD_SIZE;
	}

	//レーザーの当たり判定.
	Line line = { it->nowPos, it->befPos, {} };

	// プレイヤーとレーザーの当たり判定
	if (player.GetActive() && HitLineCir(line, plyHit)) {

		//反射あり.
		if (player.GetMode() == Player_Reflect)
		{
			it->type = Laser_Reflect; //反射モードへ.
			it->counter = 0;          //リセット.
			ReflectLaser(it);         //レーザーを反射.
		}
		//反射あり(強化版)
		else if (player.GetMode() == Player_SuperReflect)
		{
			it->type = Laser_SuperReflect; //反射モードへ.
			it->counter = 0;               //リセット.
			ReflectLaser(it);              //レーザーを反射.		
		}
		//反射なし.
		else
		{
			player.PlayerDeath(); //プレイヤー死亡.
			return true;             //レーザーを消去する.
		}
	}
	return false; //レーザーを消去しない.
}
//レーザー反射.
void LaserManager::ReflectLaser(list<LaserData>::iterator it)
{
	//反射時の元の角度.
	double ang = _deg(atan2(it->vec.y, it->vec.x));
	//角度を逆方向へ(少しだけランダムでずれる)
	ang += 180 + (float)RandNum(-200, 200)/10;
	//角度反映.
	it->vec = { cos(_rad(ang)), sin(_rad(ang)) };

	//エフェクト.
	EffectData data{};
	data.type = Effect_ReflectLaser;
	data.pos  = it->nowPos;
	effectMng.SpawnEffect(&data);
	//サウンド.
	if (auto i = SoundMng::Get("Laser3")) {
		i->Play(false, 58);
	}

	//チュートリアルなら指示送信.
	if (gameData.stage == Stage_Tutorial) {
		TutorialStage::GetInst().SetReflectLaser(true);
	}
}
//レーザー描画線を生成.
void LaserManager::GenerateLaserLine(list<LaserData>::iterator it) {

	//前回描画した位置からの距離.
	const double dis = Dist(it->nowPos, it->befPos);

	//長さが一定以上あれば描画線を出す(DrawLineAAの関係上)
	if (dis >= LASER_LINE_DRAW_LEN) {
		
		LaserLineData tmp; //描画線作成.

		tmp.pos1 = it->befPos;	//描画線の座標1
		tmp.pos2 = it->nowPos;	//描画線の座標2
		tmp.type = it->type;	//レーザーのタイプに合わせる.
		tmp.counter = 0;		//経過時間.

		//落下レーザーの設定.
		if (tmp.type == Laser_Falling) {
			//レーザーの経過時間を反映.
			//落下レーザー消滅時間が、レーザー描画線消滅時間に合わさるよう計算.
			tmp.counter = it->counter * LASER_LINE_DEL_TIME / LASER_FAL_DEL_TIME;
			//アニメーション曲線の調整.
			const double anim = AnimEaseOut(tmp.counter / LASER_LINE_DEL_TIME);
			tmp.counter *= _flt(anim);
		}

		line.push_back(tmp); //listに追加.

		//最後に描画線を出した座標を記録.
		it->befPos = it->nowPos;
	}
}
//レーザー(reflected)の隕石追尾.
void LaserManager::LaserRefTracking(list<LaserData>::iterator it)
{
	//目標地点に向かうなら.
	if (it->isGoGoal) {
		//一定時間のみ追尾.
		if (it->counter > LASER_REF_TRACK_ST_TM &&
			it->counter < LASER_REF_TRACK_ED_TM)
		{
			//目標地点までの座標差と方角.
			const double targetAngle  = atan2(it->goalPos.y - it->nowPos.y, it->goalPos.x - it->nowPos.x);
			//レーザーの現在の移動方向の角度.
			const double currentAngle = atan2(it->vec.y, it->vec.x);
			//角度の差分を計算.
			double angleDiff = targetAngle - currentAngle;

			//角度差分を-PI～PIの範囲に正規化.
			while (angleDiff > M_PI)
			{
				angleDiff -= 2 * M_PI;
			}
			while (angleDiff < -M_PI)
			{
				angleDiff += 2 * M_PI;
			}

			// 反射レーザーの旋回角度（通常レーザーより少し速く）.
			double maxTurn = _rad(LASER_REF_ROT_MAX) * gameData.speedRate;
			if (angleDiff > +maxTurn) angleDiff = +maxTurn;
			if (angleDiff < -maxTurn) angleDiff = -maxTurn;

			//新しい角度を計算して速度を更新
			double newAngle = currentAngle + angleDiff;

			// 方向を計算して設定.
			it->vec = { cos(newAngle), sin(newAngle) };
		}
	}
}

//敵のレーザーが1つでも存在するかどうか.
bool LaserManager::IsExistEnemyLaser(DBL_XY pos, float len) {

	//全てのレーザー.
	for (const auto& i : laser) {
		//敵のレーザーなら.
		if (i.type == Laser_Normal   ||
			i.type == Laser_Straight ||
			i.type == Laser_Falling)
		{
			//消えかかってる落下レーザーは除外.
			if (i.type == Laser_Falling &&
				i.counter > LASER_FAL_HIT_ABLE) 
			{
				continue;
			}
			//距離が範囲内ならtrueを返す.
			if (Dist(pos, i.nowPos) <= len) {
				return true; 
			}
		}
	}
	return false; //1つもない.
}

//レーザーを一括反射(未使用)
void LaserManager::LaserReflectRange(Circle cir) {
	
	//有効なレーザー.
	for (auto i = laser.begin(); i != laser.end(); i++) {
		const Circle cir2 = { i->nowPos, 1, {} };
		//範囲内なら.
		if (HitCirCir(cir, cir2)) {
			ReflectLaser(i); //その場で反射.
		}
	}
}