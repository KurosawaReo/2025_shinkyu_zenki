/*
   - LaserManager.cpp -
   元々Obstacle4mainとしてまとめられてたレーザー.
*/
#include "Player.h"
#include "GameManager.h"
#include "Obst_MeteorManager.h"

#include "LaserManager.h"

using namespace Calc; //計算機能を使用.

//初期化.
void LaserManager::Init() {

	//実体取得.
	p_data      = GameData::GetPtr();
	p_player    = Player::GetPtr();
	p_meteorMng = MeteorManager::GetPtr();
	p_effectMng = EffectManager::GetPtr();
}
//リセット.
void LaserManager::Reset() {

	//レーザーデータの初期化.
	for (int i = 0; i < LASER_CNT_MAX; i++) {
		DeleteLaser(i); //全て消去しておく.
	}
	//レーザーの軌跡データの初期化.
	for (int i = 0; i < LASER_LINE_CNT_MAX; i++) {
		line[i].ValidFlag = 0;  //すべての軌跡を無効状態に.
	}
}
//更新.
void LaserManager::Update() {

	plyPos = p_player->GetPos(); //プレイヤーの現在位置を取得.

	UpdateLaser();     //各レーザーの更新.
	UpdateLaserLine(); //各レーザー描画線の更新.
}
//描画.
void LaserManager::Draw() {

#if defined DEBUG_LASER_ACTIVE
	//デバッグ表示.
	for (int i = 0; i < LASER_LINE_CNT_MAX; i++)
	{
		int x = 0 + 8 * (i % 200);
		int y = 100 + 16 * (i / 200);
		DrawString(0, 80, _T("レーザー痕跡のactive"), 0xFF00FF);
		DrawFormatString(x, y, 0xFF00FF, _T("%d"), line[i].ValidFlag);
	}
#endif

	// レーザーの軌跡の描画処理.
	for (int i = 0; i < LASER_LINE_CNT_MAX; i++)
	{
		if (line[i].ValidFlag == 0) continue;  // 無効な軌跡はスキップ

		//時間経過で徐々に薄くする.
		int clr = _int_r(255 - line[i].Counter * 4);
		clr = max(clr, 0); //最低値を0にする.

		//加算合成モードで軌跡を描画（発光エフェクト）
		SetDrawBlendMode(DX_BLENDMODE_ADD, clr);

		//軌跡の線設定.
		Line tmpLine = { {line[i].x2, line[i].y2}, {line[i].x1, line[i].y1}, {} };
		//線の色(時間経過で色が変化)
		switch (line[i].type)
		{
			case Laser_Normal:       tmpLine.color = GetColor(50, clr, 255);        break;
			case Laser_Straight:     tmpLine.color = GetColor(50, clr, 255);        break;
			case Laser_Reflect:      tmpLine.color = GetColor(clr/2+128, 0, 255);   break;
			case Laser_SuperReflect: tmpLine.color = GetColor(clr/2+128, 0, 255);   break;
			case Laser_Falling:      tmpLine.color = GetColor(50, clr, 255);        break;

			default: assert(FALSE); break;
		}

		DrawLineST(&tmpLine, true); //描画.
	}

	//通常の描画モードに戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

//各レーザーの更新.
void LaserManager::UpdateLaser() {

	//	const double pSizeHalf = PLAYER_SIZE / 2.0;  // プレイヤーの当たり判定サイズの半分

		//各レーザーの更新.
	for (int i = 0; i < LASER_CNT_MAX; i++)
	{
		if (laser[i].ValidFlag == 0) continue;  // 無効なレーザーはスキップ

		//プレイヤー当たり判定.
		Circle plyHit = p_player->GetHit();

		//レーザータイプ別.
		switch (laser[i].type)
		{
		case Laser_Normal:
		{
			Line line = { {laser[i].x, laser[i].y}, {laser[i].bx, laser[i].by}, {} }; //レーザーの当たり判定.
			// プレイヤーとレーザーの当たり判定
			if (HitLineCir(&line, &plyHit)) {

				//反射あり.
				if (p_player->GetMode() == Player_Reflect)
				{
					laser[i].type = Laser_Reflect; //反射モードへ.
					laser[i].Counter = 0;          //リセット.
					ReflectLaser(i);               //レーザーを反射.
				}
				//反射あり(強化版)
				else if (p_player->GetMode() == Player_SuperReflect)
				{
					laser[i].type = Laser_SuperReflect; //反射モードへ.
					laser[i].Counter = 0;               //リセット.
					ReflectLaser(i);                    //レーザーを反射.		
				}
				//反射なし.
				else
				{
					DeleteLaser(i);
					p_player->PlayerDeath(); //プレイヤー死亡.
				}
			}
			else {
				//速度(時間経過で速くなる)
				double speed = laser[i].Counter * LASER_NOR_SPEED * (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
				//レーザーの移動.
				laser[i].x += laser[i].vx * speed;
				laser[i].y += laser[i].vy * speed;
			}
		}
		break;

		case Laser_Straight:
		{
			Line line = { {laser[i].x, laser[i].y}, {laser[i].bx, laser[i].by}, {} }; //レーザーの当たり判定.
			// プレイヤーとレーザーの当たり判定
			if (HitLineCir(&line, &plyHit)) {

				//反射あり.
				if (p_player->GetMode() == Player_Reflect)
				{
					laser[i].type = Laser_Reflect; //反射モードへ.
					laser[i].Counter = 0;          //リセット.
					ReflectLaser(i);               //レーザーを反射.
				}
				//反射あり(強化版)
				else if (p_player->GetMode() == Player_SuperReflect)
				{
					laser[i].type = Laser_SuperReflect; //反射モードへ.
					laser[i].Counter = 0;               //リセット.
					ReflectLaser(i);                    //レーザーを反射.		
				}
				//反射なし.
				else
				{
					DeleteLaser(i);
					p_player->PlayerDeath(); //プレイヤー死亡.
				}
			}
			else {
				//速度(直線レーザーなので一定速度)
				double speed = LASER_STR_SPEED * ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
				//レーザーの移動.
				laser[i].x += laser[i].vx * speed;
				laser[i].y += laser[i].vy * speed;
			}

		}
		break;

		case Laser_Falling:
		{
			Line line = { {laser[i].x, laser[i].y}, {laser[i].bx, laser[i].by}, {} }; //レーザーの当たり判定.
			// プレイヤーとレーザーの当たり判定
			if (HitLineCir(&line, &plyHit)) {

				//反射あり.
				if (p_player->GetMode() == Player_Reflect)
				{
					laser[i].type = Laser_Reflect; //反射モードへ.
					laser[i].Counter = 0;          //リセット.
					ReflectLaser(i);               //レーザーを反射.
				}
				//反射あり(強化版)
				else if (p_player->GetMode() == Player_SuperReflect)
				{
					laser[i].type = Laser_SuperReflect; //反射モードへ.
					laser[i].Counter = 0;               //リセット.
					ReflectLaser(i);                    //レーザーを反射.		
				}
				//反射なし.
				else
				{
					DeleteLaser(i);
					p_player->PlayerDeath(); //プレイヤー死亡.
				}
			}
			else {
				// 重力効果を適用（下向きの加速度）
				double gravity = 0.08 * ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
				laser[i].vy += gravity;

				// 空気抵抗効果（水平方向の速度を徐々に減少）
				double airResistance = 0.995;
				laser[i].vx *= airResistance;

				// 速度制限（落下速度が速くなりすぎないように）
				double maxSpeed = 8.0;
				if (laser[i].vy > maxSpeed) {
					laser[i].vy = maxSpeed;
				}

				// レーザーの移動
				laser[i].x += laser[i].vx;
				laser[i].y += laser[i].vy;
			}
		}
		break;

		case Laser_Reflect:
		case Laser_SuperReflect:
		{
			//一定時間で目標地点を決める.
			if (laser[i].Counter >= LASER_REF_TRACK_ST_TM) {

				assert(p_meteorMng != nullptr); //ポインタが空でないことを確認.

				DBL_XY laserPos = { laser[i].x, laser[i].y }; //レーザーの現在位置.
				DBL_XY meteoPos{ -1, -1 };

				//最も近い隕石の位置を取得する.
				bool hasMeteo = p_meteorMng->GetMeteorPosNearest(laserPos, &meteoPos);
				//隕石があった場合.
				if (hasMeteo) {
					laser[i].goalPos = meteoPos; //登録.
					laser[i].isGoGoal = true;
				}
			}

			Circle hit = { {laser[i].x, laser[i].y}, 10, {} }; //当たり判定円(仮)

			//隕石と当たっているなら.
			if (p_meteorMng->IsHitMeteors(hit, true)) {

				double dig = _deg(atan2(laser[i].vy, laser[i].vx)); //現在のレーザー角度.

				//エフェクトをいくつか出す.
				for (int j = 0; j < METEOR_BREAK_ANIM_CNT; j++) {

					double newDig = dig + (float)RandNum(-300, 300)/10; //少し角度をずらす.

					EffectData data{};
					data.type  = Effect_BreakMeteo;
					data.pos   = { laser[i].x, laser[i].y };
					data.vec   = CalcVectorDeg(newDig);      //ずらした角度を反映.
					data.speed = (float)RandNum(20, 100)/10; //速度抽選.
					data.len   = (float)RandNum(10, 150)/10; //長さ抽選.
					data.ang   = (float)RandNum(0, 3599)/10; //角度抽選.
					//エフェクト召喚.
					p_effectMng->SpawnEffect(&data);
				}

				//どっちのタイプかで切り替え.
				if (laser[i].type == Laser_Reflect) {
					DeleteLaser(i);  //消去.
				}
				else {
					laser[i].Counter = LASER_REF_TRACK_ED_TM; //再反射後は追尾しない.
					ReflectLaser(i); //再反射.
				}
			}
			else {
				//レーザーの追尾処理.
				LaserRefTracking(i);

				//速度(時間経過で速くなる)
				double speed = laser[i].Counter * LASER_REF_SPEED * (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
				//レーザーの移動.
				laser[i].x += laser[i].vx * speed;
				laser[i].y += laser[i].vy * speed;
			}
		}
		break;

		//想定外の値エラー.
		default: assert(false); break;
		}

		//前回描画した位置からの距離.
		DBL_XY pos1 = { laser[i].x,  laser[i].y };
		DBL_XY pos2 = { laser[i].bx, laser[i].by };
		double dis = CalcDist(pos1, pos2);
		//長さが一定以上あれば描画する(DrawLineAAの関係上)
		if (dis >= LASER_LINE_DRAW_LEN) {
			//レーザーの軌跡を生成.
			for (int j = 0; j < LASER_LINE_CNT_MAX; j++)
			{
				if (line[j].ValidFlag == 0)  //未使用の軌跡スロットを探す.
				{
					// 軌跡データの設定
					line[j].x1 = laser[i].bx;	  //開始点X座標.
					line[j].y1 = laser[i].by;	  //開始点Y座標.
					line[j].x2 = laser[i].x;	  //終了点X座標.
					line[j].y2 = laser[i].y;	  //終了点Y座標.
					line[j].Counter = 0;		  //経過時間カウンタ初期化.
					line[j].ValidFlag = 1;		  //軌跡を有効化.
					line[j].type = laser[i].type; //レーザーのタイプに合わせる.
					break;
				}
			}
			//座標を記録.
			laser[i].bx = laser[i].x;
			laser[i].by = laser[i].y;
		}

		//画面外判定.
		int _x = (laser[i].x < -100) || (laser[i].x > WINDOW_WID + 100);
		int _y = (laser[i].y < -100) || (laser[i].y > WINDOW_HEI + 100);
		//画面外に出たレーザーを無効化.
		if (_x || _y)
		{
			DeleteLaser(i);
		}

		// レーザーの経過時間カウンタを増加
		laser[i].Counter += (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
	}
}
//各レーザー描画線の更新.
void LaserManager::UpdateLaserLine() {

	for (int i = 0; i < LASER_LINE_CNT_MAX; i++) {

		// 経過時間カウンタ増加
		line[i].Counter += (p_data->isSlow) ? SLOW_MODE_SPEED : 1;
		// 64フレーム経過したら軌跡を無効化
		if (line[i].Counter >= 64) line[i].ValidFlag = 0;
	}
}

//レーザー召喚.
bool LaserManager::SpawnLaser(DBL_XY pos, DBL_XY vel, LaserType type) {

	// 未使用のレーザースロットを探してレーザーを発射
	for (int i = 0; i < LASER_CNT_MAX; i++)
	{
		if (laser[i].ValidFlag == 0)  // 未使用のレーザースロットを探す
		{
			// レーザーデータの初期化
			laser[i].x = pos.x;	// 初期座標x
			laser[i].y = pos.y;    // 初期座標y
			laser[i].bx = pos.x;    // 初期座標y
			laser[i].by = pos.y;    // 初期座標y
			laser[i].vx = vel.x;    // 初期方向x
			laser[i].vy = vel.y;    // 初期方向y
			laser[i].Counter = 0;	// 経過時間カウンタ初期化
			laser[i].LogNum = 0;	// 軌跡カウンタ初期化
			laser[i].ValidFlag = 1;	// レーザーを有効化
			laser[i].type = type;   // タイプの登録

			//サウンド.
			SoundMng* sound = SoundMng::GetPtr();
			if (type == Laser_Normal) {
				sound->Play(_T("Laser1"), false, 58); //通常レーザー.
			}
			if (type == Laser_Straight) {
				sound->Play(_T("Laser2"), false, 60); //直線レーザー.
			}
			if (type == Laser_Falling) {
				sound->Play(_T("Laser1"), false, 45); //落下レーザー（少し音量小さめ）.
			}

			return true; //召喚成功.
		}
	}
	return false; //召喚失敗.
}
//レーザー消去.
void LaserManager::DeleteLaser(int idx) {

	laser[idx].type = Laser_Normal; //ノーマルモードに戻す.
	laser[idx].goalPos = { 0, 0 };    //目標地点リセット.
	laser[idx].isGoGoal = false;    //目標地点なし.
	laser[idx].ValidFlag = 0;       //無効にする.
}
//レーザー反射.
void LaserManager::ReflectLaser(int idx)
{
	// レーザーからプレイヤーへのベクトルを計算
	double dx = plyPos.x - laser[idx].x;
	double dy = plyPos.y - laser[idx].y;

	// ベクトルの長さを計算
	double length = sqrt(dx * dx + dy * dy);

	// 正規化（長さを1にする）
	if (length > 0)
	{
		dx /= length;
		dy /= length;
	}

	//反射時の元の角度.
	double ang = _deg(atan2(laser[idx].vy, laser[idx].vx));
	//角度を逆方向へ(少しだけランダムでずれる)
	ang += 180 + (float)RandNum(-200, 200)/10;
	//角度反映.
	laser[idx].vx = cos(_rad(ang));
	laser[idx].vy = sin(_rad(ang));

	//エフェクト.
	EffectData data{};
	data.type = Effect_ReflectLaser;
	data.pos = { laser[idx].x, laser[idx].y };
	p_effectMng->SpawnEffect(&data);
	//サウンド.
	SoundMng* sound = SoundMng::GetPtr();
	sound->Play(_T("Laser3"), false, 58);
}

#if false
//レーザー(normal)の隕石追尾.
void LaserManager::LaserNorTracking(int idx)
{
	//一定時間のみ追尾.
	if (laser[idx].Counter < 200)  // 200フレーム（約3.3秒）以内のみ追尾
	{
		double targetAngle = atan2(plyPos.y - laser[idx].y, plyPos.x - laser[idx].x); //プレイヤーへの方向.
		double currentAngle = atan2(laser[idx].vy, laser[idx].vx);                     //移動方向.
		double angleDiff = targetAngle - currentAngle;                                 //角度の差分を計算.

		// 角度差分を-PI～PIの範囲に正規化
		while (angleDiff > +M_PI) angleDiff -= 2 * M_PI;
		while (angleDiff < -M_PI) angleDiff += 2 * M_PI;

		// 最大旋回角度を制限（1フレームにn度まで）
		const double maxTurn = _rad(LASER_NOR_ROT_MAX) * (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		if (angleDiff > +maxTurn) angleDiff = +maxTurn;
		if (angleDiff < -maxTurn) angleDiff = -maxTurn;

		// 新しい角度を計算.
		laser[idx].vx = cos(currentAngle + angleDiff);
		laser[idx].vy = sin(currentAngle + angleDiff);
	}
}
#endif
//レーザー(reflected)の隕石追尾.
void LaserManager::LaserRefTracking(int idx)
{
	//目標地点に向かうなら.
	if (laser[idx].isGoGoal) {
		//一定時間のみ追尾.
		if (laser[idx].Counter > LASER_REF_TRACK_ST_TM &&
			laser[idx].Counter < LASER_REF_TRACK_ED_TM)
		{
			//目標地点までの座標差と方角.
			double targetAngle = atan2(laser[idx].goalPos.y - laser[idx].y, laser[idx].goalPos.x - laser[idx].x);
			//レーザーの現在の移動方向の角度.
			double currentAngle = atan2(laser[idx].vy, laser[idx].vx);
			//角度の差分を計算.
			double angleDiff = targetAngle - currentAngle;

			// 角度差分を-PI～PIの範囲に正規化.
			while (angleDiff > M_PI)
			{
				angleDiff -= 2 * M_PI;
			}
			while (angleDiff < -M_PI)
			{
				angleDiff += 2 * M_PI;
			}

			// 反射レーザーの旋回角度（通常レーザーより少し速く）.
			double maxTurn = _rad(LASER_REF_ROT_MAX) * (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
			if (angleDiff > +maxTurn) angleDiff = +maxTurn;
			if (angleDiff < -maxTurn) angleDiff = -maxTurn;

			//新しい角度を計算して速度を更新
			double newAngle = currentAngle + angleDiff;

			// 方向を計算して設定.
			laser[idx].vx = cos(newAngle);
			laser[idx].vy = sin(newAngle);
		}
	}
}

//レーザーの一括反射.
void LaserManager::LaserReflectRange(Circle* cir) {

	for (int i = 0; i < LASER_CNT_MAX; i++) {
		//有効なレーザー.
		if (laser[i].ValidFlag) {

			Circle cir2 = { {laser[i].x, laser[i].y}, 1, {} };

			//範囲内なら.
			if (HitCirCir(cir, &cir2)) {
				ReflectLaser(i); //その場で反射.
			}
		}
	}
}