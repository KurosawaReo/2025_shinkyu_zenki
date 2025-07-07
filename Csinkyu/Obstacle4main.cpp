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
	Hx      = _Hx;                  // 砲台のX座標初期値（画面中央）
	Hy      = _Hy;                  // 砲台のY座標初期値（画面上部）
	Hm      = _Hm;                  // 砲台の移動速度
	Hsc     = OBSTACLE4_SHOT_RESET; // 砲台の発射カウンタ初期値
	HscTm   = OBSTACLE4_SHOT_START; // 砲台の発射タイミング初期値
	moveDir = _moveDir;             // 初期方向を右に設定.
}
//更新.
void Obstacle4main::Update()
{
//	if (p_player->GetActive()) {  // プレイヤーがアクティブな場合のみ
	if (p_data->scene == SCENE_GAME) {  // ゲーム中のみ
		enemy4Move();					// 障害物の移動処理を実行
	}
}
//描画.
void Obstacle4main::Draw()
{
	DrawObstFlash(); // 発射エフェクトの処理.
	
	// 動く砲台を描画.
	//Box box = { {Hx, Hy}, {10, 10}, GetColor(100, 100, 100) }; //{pos}, {size}, color.
	//DrawBoxST(&box, TRUE, FALSE);
}

// 発射エフェクトの処理.
void Obstacle4main::DrawObstFlash() {

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
		int alphaValue = _int(255 * alpha);
		alphaValue = max(alphaValue, 0); //下限は0.

		//エフェクトのサイズを時間に応じて拡大.
		float sizeMultiplier = OBSTACLE4_FLASH_SIZE_INIT + (
			flashEffect[i].Counter * OBSTACLE4_FLASH_SIZE_SPREAD / flashEffect[i].Duration
		);
		int effectSize = _int(flashEffect[i].BaseSize * sizeMultiplier);
		int innerSize = effectSize / 2;

		//エフェクトの位置を時間経過とともにプレイヤー方向に移動
		float progress = flashEffect[i].Counter / flashEffect[i].Duration;
		double currentX = flashEffect[i].x + cos(flashEffect[i].angle) * progress * 60; // 30ピクセル分移動
		double currentY = flashEffect[i].y + sin(flashEffect[i].angle) * progress * 60;

		//三角形の頂点を計算(プレイヤーの方向を向く).
		double angle = flashEffect[i].angle;
		double cos_a = cos(angle);
		double sin_a = sin(angle);
		//外側の三角形(大きい)(なんかすごくなっちゃった)
		int x1 = _int(currentX + cos_a * effectSize);//先端.
		int y1 = _int(currentY + sin_a * effectSize);
		int x2 = _int(currentX - cos_a * effectSize / 3 + sin_a * effectSize / 2);//左後.
		int y2 = _int(currentY - sin_a * effectSize / 3 - cos_a * effectSize / 2);
		int x3 = _int(currentX - cos_a * effectSize / 3 - sin_a * effectSize / 2);//右後.
		int y3 = _int(currentY - sin_a * effectSize / 3 + cos_a * effectSize / 2);
		//内側の三角形(小さい)
		int ix1 = _int(currentX + cos_a * effectSize);//先端.
		int iy1 = _int(currentY + sin_a * effectSize);
		int ix2 = _int(currentX - cos_a * effectSize / 3 + sin_a * effectSize / 2);
		int iy2 = _int(currentY - sin_a * effectSize / 3 - cos_a * effectSize / 2);
		int ix3 = _int(currentX - cos_a * effectSize / 3 - sin_a * effectSize / 2);
		int iy3 = _int(currentY - sin_a * effectSize / 3 + cos_a * effectSize / 2);

		//発射エフェクトを円形で描画(白く光る)
		SetDrawBlendMode(DX_BLENDMODE_ADD, alphaValue);

		//外側の三角形.
		DrawTriangle(x1, y1, x2, y2, x3, y3, GetColor(0, 255, 255), FALSE);

		//内側により明るい三角形を描画.
		//DrawTriangle(ix1, iy1, ix2, iy2, ix3, iy3, GetColor(0, 255, 200), FALSE);

		//エフェクト内に3つの●を描画
		int dotSize = effectSize / 10; // 三角形のサイズに応じて●のサイズを調整
		int dotAlpha = alphaValue / 1; // 少し透明度を下げる
		SetDrawBlendMode(DX_BLENDMODE_ADD, dotAlpha);

		// 3つの●を三角形の内部に配置
		DrawCircle(_int(currentX + cos_a * effectSize / 3), _int(currentY + sin_a * effectSize / 3), dotSize, GetColor(0, 255, 255), FALSE);
		DrawCircle(_int(currentX - cos_a * effectSize / 6 + sin_a * effectSize / 4), _int(currentY - sin_a * effectSize / 6 - cos_a * effectSize / 4), dotSize, GetColor(0, 255, 255), FALSE);
		DrawCircle(_int(currentX - cos_a * effectSize / 6 - sin_a * effectSize / 4), _int(currentY - sin_a * effectSize / 6 + cos_a * effectSize / 4), dotSize, GetColor(0, 255, 255), FALSE);

		//エフェクトのカウンタを更新
		flashEffect[i].Counter += (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		//エフェクト時間が終了したら無効化
		if (flashEffect[i].Counter >= flashEffect[i].Duration)
		{
			flashEffect[i].ValidFlag = 0;
		}
	}

	//通常の描画モードに戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
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

		// 発射カウンタを減少
		Hsc -= (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		// タイミングが来たらレーザー発射
		if (Hsc <= HscTm)
		{
			BOOL ret = p_laserMng->SpawnLaser(Hx, Hy); //レーザー召喚.
			//発射成功したら.
			if (ret) {
				CreateFlashEffect(Hx, Hy); //エフェクトを出す.
			}

			HscTm -= OBSTACLE4_SHOT_SPAN; //発射タイミングを変更.
		}
		//0秒を下回ったらもう一周.
		if (Hsc <= 0) {
			Hsc = OBSTACLE4_SHOT_RESET;  // 発射カウンタをリセット（次の発射までの待機時間）
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