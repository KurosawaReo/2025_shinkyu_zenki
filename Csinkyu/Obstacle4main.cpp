/*
   - Obstacle4main.cpp -

   レーザー砲台の継承元クラス.

   プレイヤーを追尾するレーザーを発射する障害物を実装.
   レーザー反射機能追加.
*/
#include "Player.h"    // プレイヤークラスのヘッダーファイル
#include "Obstacle4.h" // 自身のヘッダーファイル

//初期化.
void Obstacle4main::Init(GameData* _data, Player* _player, MeteoManager* _meteoMng, LaserManager* _laserMng)
{
	// オブジェクトを参照として保存
	p_data     = _data;
	p_player   = _player;
	p_meteoMng = _meteoMng;
	p_laserMng = _laserMng;
}
//リセット.
void Obstacle4main::Reset(float _Hx, float _Hy, float _Hm, MoveDir _moveDir)
{
	Hx      = _Hx;                      // 砲台のX座標初期値（画面中央）
	Hy      = _Hy;                      // 砲台のY座標初期値（画面上部）
	Hm      = _Hm;                      // 砲台の移動速度
	Hsc     = OBSTACLE4_SHOT_START+100; // 砲台の発射カウンタ初期値 
	HscTm   = OBSTACLE4_SHOT_START;     // 砲台の発射タイミング初期値
	moveDir = _moveDir;                 // 初期方向を右に設定.

	//フラッシュを無効化.
	for (int i = 0; i < OBSTACLE4_FLASH_MAX; i++) {
		flashEffect[i].ValidFlag = 0;
	}
}
//更新.
void Obstacle4main::Update()
{
//	if (p_player->GetActive()) {  // プレイヤーがアクティブな場合のみ
	if (p_data->scene == SCENE_GAME) {  // ゲーム中のみ
		
		//発射カウンタを減少.
		Hsc -= (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);

		//エフェクトのカウンタを更新.
		for (int i = 0; i < OBSTACLE4_FLASH_MAX; i++) {
			//有効なら.
			if (flashEffect[i].ValidFlag)
			{
				flashEffect[i].Counter += (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
			}
		}

		enemy4Move();					// 障害物の移動処理
		UpdateObstFlash();              // 発射エフェクトの更新.
	}
}
//描画.
void Obstacle4main::Draw()
{
	DrawObstFlash(); // 発射エフェクトの描画.
	
	// 動く砲台を描画.
	//Box box = { {Hx, Hy}, {10, 10}, GetColor(100, 100, 100) }; //{pos}, {size}, color.
	//DrawBoxST(&box, true, false);
}

//発射エフェクトの更新.
void Obstacle4main::UpdateObstFlash() {

}
//発射エフェクトの描画.
void Obstacle4main::DrawObstFlash() {

	// レーザー発射前の予告●を描画
	DrawPreLaserDots();

	for (int i = 0; i < OBSTACLE4_FLASH_MAX; i++)
	{
		if (flashEffect[i].ValidFlag == 0)
		{
			continue;//無効なエフェクトをスキップ.
		}

		//エフェクトの透明度を時間に応じて計算.
		float alpha = 1.0f - (
			flashEffect[i].Counter * OBSTACLE4_FLASH_ALPHA_TM / flashEffect[i].Duration
		);
		int alphaValue = _int_r(255 * alpha);
		alphaValue = max(alphaValue, 0); //下限は0.

		//エフェクトのサイズを時間に応じて拡大.
		float sizeMultiplier = OBSTACLE4_FLASH_SIZE_INIT + (
			flashEffect[i].Counter * OBSTACLE4_FLASH_SIZE_SPREAD / flashEffect[i].Duration
		);
		int effectSize = _int_r(flashEffect[i].BaseSize * sizeMultiplier);
		int innerSize = effectSize / 2;

		//プレイヤーの方向を計算.
		double angle = flashEffect[i].angle;
		double cos_a = cos(angle);
		double sin_a = sin(angle);

#if false
		//エフェクトを時間経過でプレイヤーの方へ進ませる.
		float progress = flashEffect[i].Counter / flashEffect[i].Duration;
		double currentX = flashEffect[i].x + cos_a * progress * 1000; // nピクセル分移動
		double currentY = flashEffect[i].y + sin_a * progress * 1000;
#else
		double currentX = flashEffect[i].x;
		double currentY = flashEffect[i].y;
#endif

		Triangle tri;
		//三角形の3点(なんかすごくなっちゃった)
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

		//描画モード設定(光る)
		SetDrawBlendMode(DX_BLENDMODE_ADD, alphaValue);

		DrawLineST(&line1, true);
		DrawLineST(&line2, true);

		//エフェクト時間が終了したら無効化
		if (flashEffect[i].Counter >= flashEffect[i].Duration)
		{
			flashEffect[i].ValidFlag = 0;
		}
	}

	//通常の描画モードに戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);  
}

// レーザー発射前の予告●を描画
void Obstacle4main::DrawPreLaserDots() {

	// 発射タイミングが近づいている場合のみ●を表示
	if (Hsc <= HscTm + 60) { // 発射60フレーム前から表示
		// 点滅効果を作成
		float blinkProgress = (HscTm + 60 - Hsc) / 60.0f; // 0.0から1.0
		int blinkAlpha = _int_r(128 + 127 * sin(blinkProgress * M_PI * 8)); // 点滅

		//サイズを徐々に大きく.
		float dotSize  = (float)(3 + CalcNumEaseOut(blinkProgress) * OBSTACLE4_PRE_LASER1_SIZE);
		float dotSize2 = (float)(3 + CalcNumEaseOut(blinkProgress) * OBSTACLE4_PRE_LASER2_SIZE);
		//円情報.
		Circle cir = {{Hx, Hy}, dotSize, GetColor(0, 255, 255)};
		SetDrawBlendMode(DX_BLENDMODE_ADD, blinkAlpha);

		// 砲台の位置に●を描画
		DrawCircleST(&cir, false, true);
		cir.r = dotSize2;
		DrawCircleST(&cir, false, true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}

/**
 * @brief 敵（障害物）の移動処理
 * レーザーの移動とプレイヤーへの追尾、砲台の移動とレーザー発射を管理
 */
void Obstacle4main::enemy4Move()
{
	// 砲台の移動とレーザー発射処理
	{
		//移動処理.
		Move();

		// タイミングが来たらレーザー発射
		if (Hsc <= HscTm)
		{
			//プレイヤー座標.
			DBL_XY plyPos = p_player->GetPos();
			//プレイヤー方向への初期角度計算.
			double angle = atan2(plyPos.y - Hy, plyPos.x - Hx);
			DBL_XY vel = {cos(angle), sin(angle)};

			//通常レーザー召喚.
			bool ret = p_laserMng->SpawnLaser({Hx, Hy}, vel, Laser_Normal);
			//発射成功したら.
			if (ret) {
				CreateFlashEffect(Hx, Hy); //エフェクトを出す.
			}

			HscTm -= OBSTACLE4_SHOT_SPAN; //発射タイミングを変更.
		}
		//0秒を下回ったらもう一周.
		if (Hsc <= 0) {
			//タイマー再開(徐々に短くなる)
			//発射開始時間より短くならないよう時間を設定.
			Hsc   = OBSTACLE4_SHOT_START + OBSTACLE4_SHOT_RESET * p_data->spawnRate;
			HscTm = OBSTACLE4_SHOT_START;
		}
	}
}

//光るeffectの生成.
void Obstacle4main::CreateFlashEffect(double fx, double fy)
{
	DBL_XY pPos = p_player->GetPos(); //プレイヤー座標取得.

	//未使用のエフェクトスロットを探す.
	for (int i = 0; i < OBSTACLE4_FLASH_MAX; i++)
	{
		if (flashEffect[i].ValidFlag == 0)
		{
			double dx = pPos.x - fx;
			double dy = pPos.y - fy;
			double angle = atan2(dy, dx);

			//エフェクトデータの設定.
			flashEffect[i].x = fx;
			flashEffect[i].y = fy;
			flashEffect[i].angle = angle; // プレイヤーへの角度を保存
			flashEffect[i].Counter = 0;
			flashEffect[i].Duration = OBSTACLE4_FLASH_VALID_TM; //一定フレーム光る.
			flashEffect[i].BaseSize = 20; //基本サイズ
			flashEffect[i].ValidFlag = 1;
			break;
		}
	}
}