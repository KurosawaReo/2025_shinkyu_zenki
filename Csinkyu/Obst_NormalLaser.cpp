/*
   - Obst_NormalLaser.cpp -

   障害物: レーザー発射台(継承元)
*/
#include "Obst_NormalLaser.h" //自身のヘッダ.

//依存関係.
#include "Player.h"
#include "LaserManager.h"
#include "Obst_MeteorManager.h"
#include "GameData.h"
#include "GameManager.h"
//参照.
static GameData&      gameData  = GameData::GetInst();
static Player&        player    = Player::GetInst();
static LaserManager&  laserMng  = LaserManager::GetInst();
static MeteorManager& meteorMng = MeteorManager::GetInst();

using namespace Calc; //計算機能を使用.

// ▼*--=<[ LaserPoint ]>=--*▼ //

//移動ランダム.
void LaserPoint::MoveRand()
{
	//どの辺から発射するか.
	move.dir = static_cast<MoveDir>(rand() % MoveDir::Count);
	//どっち周りか.
	move.isLeft = (rand() % 2 == 0);
	//座標抽選.
	switch (move.dir)
	{
	case 0: //上.
		pos.x = _dbl(Calc::RandNum(0, WINDOW_WID - 1));
		pos.y = 0;
		break;
	case 1: //右.
		pos.x = WINDOW_WID;
		pos.y = _dbl(Calc::RandNum(0, WINDOW_HEI - 1));
		break;
	case 2: //下.
		pos.x = _dbl(Calc::RandNum(0, WINDOW_WID - 1));
		pos.y = WINDOW_HEI;
		break;
	case 3: //左.
		pos.x = 0;
		pos.y = _dbl(Calc::RandNum(0, WINDOW_HEI - 1));
		break;
	}
}

// ▼*--=<[ NormalLaser ]>=--*▼ //

//初期化.
void NormalLaser::Init(){
	
}
//リセット.
void NormalLaser::Reset()
{
	//発射台.
	for (auto& i : points) {
		i.counter   = LASER_NOR_SHOT_START + 100;
		i.counterTm = LASER_NOR_SHOT_START;
		i.speed     = 3;
		i.validFlag = false;
		i.MoveRand();
	}
	//フラッシュ.
	for (int i = 0; i < LASER_NOR_FLASH_MAX; i++) {
		flash[i].validFlag = false; //全て無効に.
	}
}
//更新.
void NormalLaser::Update()
{
	//ゲーム中のみ.
	if (SceneMng::GetSceneName() == "Game") {
		
		//発射台カウンター.
		for (auto& i : points) {
			i.counter -= gameData.speedRate;
		}
		//エフェクトカウンター.
		for (int i = 0; i < LASER_NOR_FLASH_MAX; i++) {
			//有効なら.
			if (flash[i].validFlag) {
				flash[i].counter += gameData.speedRate;
			}
		}

		UpdatePoint(); //発射台の処理.
	}
}
//描画.
void NormalLaser::Draw()
{
	DrawObstFlash(); //発射エフェクトの描画.
}

//発射エフェクトの描画.
void NormalLaser::DrawObstFlash() {

	// レーザー発射前の予告●を描画
	DrawPreLaserDots();

	for (int i = 0; i < LASER_NOR_FLASH_MAX; i++)
	{
		//無効ならスキップ.
		if (!flash[i].validFlag) {
			continue;
		}

		//エフェクトの透明度を時間に応じて計算.
		float alpha = 1.0f - (
			flash[i].counter * LASER_NOR_FLASH_ALPHA_TM / flash[i].Duration
		);
		int alphaValue = _int_r(255 * alpha);
		alphaValue = max(alphaValue, 0); //下限は0.

		//エフェクトのサイズを時間に応じて拡大.
		float sizeMultiplier = LASER_NOR_FLASH_SIZE_INIT + (
			flash[i].counter * LASER_NOR_FLASH_SIZE_SPREAD / flash[i].Duration
		);
		int effectSize = _int_r(flash[i].BaseSize * sizeMultiplier);
		int innerSize = effectSize / 2;

		//プレイヤーの方向を計算.
		double angle = flash[i].angle;
		double cos_a = cos(angle);
		double sin_a = sin(angle);

#if false
		//エフェクトを時間経過でプレイヤーの方へ進ませる.
		float progress = flashEffect[i].Counter / flashEffect[i].Duration;
		double currentX = flashEffect[i].x + cos_a * progress * 1000; // nピクセル分移動
		double currentY = flashEffect[i].y + sin_a * progress * 1000;
#else
		double currentX = flash[i].x;
		double currentY = flash[i].y;
#endif

		Triangle tri;
		//三角形の3点.
		tri.pos[0].x = currentX + cos_a * effectSize; //先端.
		tri.pos[0].y = currentY + sin_a * effectSize;
		tri.pos[1].x = currentX - cos_a * effectSize/3 + sin_a * effectSize/2; //左後.
		tri.pos[1].y = currentY - sin_a * effectSize/3 - cos_a * effectSize/2;
		tri.pos[2].x = currentX - cos_a * effectSize/3 - sin_a * effectSize/2; //右後.
		tri.pos[2].y = currentY - sin_a * effectSize/3 + cos_a * effectSize/2;

		Line line1, line2;
		//三角形の2辺を線にする.
		line1.stPos = tri.pos[1];
		line1.edPos = tri.pos[0];
		line2.stPos = tri.pos[0];
		line2.edPos = tri.pos[2];
		line1.color = GetColor(0, 255, 255);
		line2.color = GetColor(0, 255, 255);
		
		{
			DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, alphaValue);
			DrawLineKR(line1, true);
			DrawLineKR(line2, true);
		}
		//エフェクト時間が終了したら無効化
		if (flash[i].counter >= flash[i].Duration)
		{
			flash[i].validFlag = 0;
		}
	}
}
//レーザー発射前の予告●を描画.
void NormalLaser::DrawPreLaserDots() {

	//有効な発射台のみ.
	for (auto& i : points) {
		if (i.validFlag) {

			//予告演出, 発射する前になる度に表示.
			if (i.counter <= i.counterTm + 60) {
				//点滅.
				float blinkProgress = (60 - i.counter) / 60.0f; //0.0～1.0
				int blinkAlpha = _int_r(128 + 127 * sin(blinkProgress * M_PI * 8));

				//サイズを徐々に大きく.
				float dotSize  = (float)(3 + AnimEaseOut(blinkProgress) * LASER_NOR_PRE_LASER1_SIZE);
				float dotSize2 = (float)(3 + AnimEaseOut(blinkProgress) * LASER_NOR_PRE_LASER2_SIZE);
				//円情報.
				Circle cir = { i.pos, dotSize, COLOR_PRE_EFFECT };

				{
					DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, blinkAlpha);

					DrawCircleKR(cir, false, true);
					cir.r = dotSize2;
					DrawCircleKR(cir, false, true);
				}
			}
		}
	}
}

//発射処理.
void NormalLaser::UpdatePoint()
{
	//有効な発射台のみ.
	for (auto& i : points) {
		if (i.validFlag) {

			//移動(方向 * 速度 * 速度倍率)
			i.pos += i.move.vec * i.speed * gameData.speedRate;
			//画面から少しでもはみ出たら.
			if (Calc::IsOutInArea(i.pos, { 0, 0 }, App::GetWindowRect().ToDbl(), false)) {
				//画面内に補正.
				Calc::FixPosInArea(&i.pos, { 0, 0 }, App::GetWindowRect().ToDbl());
				//回転.
				if (i.move.isLeft) {
					i.move.dir = static_cast<MoveDir>((i.move.dir - 1) % MoveDir::Count); //左回り.
				}
				else {
					i.move.dir = static_cast<MoveDir>((i.move.dir + 1) % MoveDir::Count); //右回り.
				}
			}

			//タイミングが来たらレーザー発射.
			if (i.counter <= LASER_NOR_SHOT_START)
			{
				//プレイヤー座標.
				DBL_XY plyPos = player.GetPos();
				//プレイヤー方向への初期角度計算.
				double angle = atan2(plyPos.y - i.pos.y, plyPos.x - i.pos.x);
				DBL_XY vel = {cos(angle), sin(angle)};

				laserMng.SpawnLaser(i.pos, vel, Laser_Normal); //通常レーザー召喚.
				CreateFlashEffect(i.pos.x, i.pos.y); //エフェクトを出す.

				i.counterTm -= LASER_NOR_SHOT_SPAN; //次のレーザーを発射するタイミング.
			}
			//0を下回ったらタイマー再開.
			if (i.counter <= 0) {
				//発射開始時間 + 待機時間(待機時間は徐々に短くなる)
				i.counter   = LASER_NOR_SHOT_START + LASER_NOR_SHOT_RESET * gameData.spawnRate;
				//発射開始時間.
				i.counterTm = LASER_NOR_SHOT_START;

				i.MoveRand();
			}
		}
	}

}

//光るeffectの生成.
void NormalLaser::CreateFlashEffect(double fx, double fy)
{
	DBL_XY pPos = player.GetPos(); //プレイヤー座標取得.

	//未使用のエフェクトスロットを探す.
	for (int i = 0; i < LASER_NOR_FLASH_MAX; i++)
	{
		if (flash[i].validFlag == 0)
		{
			double dx = pPos.x - fx;
			double dy = pPos.y - fy;
			double angle = atan2(dy, dx);

			//エフェクトデータの設定.
			flash[i].x = fx;
			flash[i].y = fy;
			flash[i].angle = angle; // プレイヤーへの角度を保存
			flash[i].counter = 0;
			flash[i].Duration = LASER_NOR_FLASH_VALID_TM; //一定フレーム光る.
			flash[i].BaseSize = 20; //基本サイズ
			flash[i].validFlag = 1;
			break;
		}
	}
}

//何個発射台を使うか.
void NormalLaser::UseLaserPointCnt(int count) {
	
	GetInst().Reset(); //一度リセット.
	
	int tmp = count;
	//必要な数だけ有効に.
	for (auto& i : GetInst().points) {
		if (tmp > 0) {
			i.validFlag = true;
		}
		tmp--;
	}
}