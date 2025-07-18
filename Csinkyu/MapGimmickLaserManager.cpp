/*
   - MapGimmickLaserManager.cpp -
   マップギミック用の直線レーザー管理.
*/
#include "Player.h"
#include "MeteoManager.h"
#include "MapGimmickLaserManager.h"
/// <summary>
/// リセットするぜ.
/// </summary>
/// <param name="_data"></param>
/// <param name="_player"></param>
/// <param name="_meteoMng"></param>
void MapGimmickLaserManager::Init(GameData* _data, Player* _player, MeteoManager* _meteoMng)
{
	//実態取得するぜ.
	p_data     = _data;
	p_player   = _player;
	p_meteoMng = _meteoMng;

	laserSpawnTimer = 0;
	nextLaserIndex  = 0;

}
/// <summary>
/// リセットするよ～ん
/// </summary>
void MapGimmickLaserManager::Reset()
{
	//レーザーデータの初期化.
	for (int i = 0; i < 3; i++)
	{
		DeleteLaser(i);//全て削除するぜ.

	}

	//レーザーの軌跡データの初期化.
	for (int i = 0; i < OBSTACLE6_LINE_MAX; i++)
	{
		line[i].ValidFlag = 0;//全ての軌跡を無効化状態に.
	}
	laserSpawnTimer = 0;
	nextLaserIndex  = 0;
}
/// <summary>
/// 更新するぜ.
/// </summary>
void MapGimmickLaserManager::Update()
{
	plyPos = p_player->GetPos();//プレイヤーの現在位置を取得.

	//レーザー発射タイマー更新.
	laserSpawnTimer += (p_data->isSlow) ? SLOW_MODE_SPEED : 1;

	//180フレーム(約3秒)ごとに直線レーザーを発射.
	if (laserSpawnTimer >= 180)
	{
		SpawnStraightLaser();
		laserSpawnTimer = 0;
	}

	UpdateLaser();    //各レーザーの更新.
	UpdateLaserLine();//各レーザー描画線の更新.

}
/// <summary>
/// 描画処理だぜ～
/// </summary>
void MapGimmickLaserManager::Draw()
{
	//レーザーの軌跡の描画処理.
	for (int i = 0; i < OBSTACLE6_LINE_MAX; i++)
	{
		if (line[i].ValidFlag == 0) continue;  // 無効な軌跡はスキップ

		//時間経過で徐々に薄くする.
		int clr = _int(255 - line[i].Counter * 4);
		clr = max(clr, 0); //最低値を0にする.

		//加算合成モードで軌跡を描画(発光エフェクト)
		SetDrawBlendMode(DX_BLENDMODE_ADD, clr);

		//軌跡の線設定.
		Line tmpLine = { {line[i].x1,line[i].y1} , { line[i].x2,line[i].y2 }, {} };

		//直線のレーザー(青色にしたぜ)
		tmpLine.clr = GetColor(50, clr, 255);
		DrawLineST(&tmpLine);//描画.

	}
	//通常の描画モードに戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

/// <summary>
/// 各レーザーの更新(むずいぜ)
/// </summary>
void MapGimmickLaserManager::UpdateLaser()
{
	const double pSizeHalf = PLAYER_SIZE / 2.0;//プレイヤーの当たり判定サイズの半分.

	//各レーザーの更新.
	for (int i = 0; i < 3; i++)
	{
		if (laser[i].ValidFlag == 0)continue; //無効なレーザーはスキップ.

		//プレイヤーとレーザーの当たり判定
		int x = (laser[i].x > plyPos.x - pSizeHalf && laser[i].x < plyPos.x + pSizeHalf);
		int y = (laser[i].y > plyPos.y - pSizeHalf && laser[i].y < plyPos.y + pSizeHalf);

		//プレイヤーとレーザーの当たり判定
		if (x && y)
		{
			DeleteLaser(i);
			p_player->PlayerDeath(); //プレイヤー死亡.
			continue;
		}

		//レーザーの通過時間カウンタを増加.
		laser[i].Counter += (float)(p_data->isSlow) ? SLOW_MODE_SPEED : 1;
		
		//移動前の座標を保存.
		DBL_XY befPos = { laser[i].x,laser[i].y };

		//速度(直線レーザーなので一定速度)
		double speed = 8.0 * (float)(p_data->isSlow) ? SLOW_MODE_SPEED : 1;

		//レーザーの移動.
		laser[i].x += laser[i].vx * speed;
		laser[i].y += laser[i].vy * speed;

		//レーザーの軌跡を生成.
		for (int j = 0; j < OBSTACLE6_LINE_MAX; j++)
		{
			if (line[j].ValidFlag == 0) //未使用の軌跡スロット.
			{
				//軌跡データの設定.
				line[j].x1 = befPos.x;   //開始点X座標.
				line[j].y1 = befPos.y;   //開始点Y座標.
				line[j].x2 = laser[i].x; //終了点X座標.
				line[j].y2 = laser[i].y; //終了点Y座標.
				line[j].Counter   = 0;   //通過時間カウンタ初期化.
				line[j].ValidFlag = 1;   //軌跡を有効化.
				break;
			}
		}
		int _x = laser[i].x < -100 || laser[i].x>WINDOW_WID + 100;
		int _y = laser[i].y <-100 || laser[i].y>WINDOW_HEI + 100;
		//画面外に出たレーザーを無効化.
		if (_x || _y)
		{
			DeleteLaser(i);
		}
	}

}
/// <summary>
/// 各レーザー描画線の更新(いやむずて～).
/// </summary>
void MapGimmickLaserManager::UpdateLaserLine()
{
	for (int i = 0; i < OBSTACLE6_LINE_MAX; i++)
	{
		if (line[i].ValidFlag == 0)continue;

		//通過時間カウンタ増加.
		line[i].Counter += (p_data->isSlow) ? SLOW_MODE_SPEED : 1;
		// 64フレーム経過したら軌跡を無効化
		if (line[i].Counter >= 64) line[i].ValidFlag = 0;
	}
}

/// <summary>
/// //直線レーザー発射(コードおもれー)
/// </summary>
void MapGimmickLaserManager::SpawnStraightLaser()
{
	// 画面左端から右に向かって発射.
	double startX = -50;  // 画面左端の少し外側.
	// 画面を3分割して、上・中・下の位置から発射.
	double positions[3] = {
		WINDOW_HEI * 0.25,  // 上部
		WINDOW_HEI * 0.5,   // 中央
		WINDOW_HEI * 0.75   // 下部
	};
	double startY = positions[nextLaserIndex];

	// 右方向への移動ベクトル.
	double vx = 1.0;  // 右方向
	double vy = 0.0;  // 水平

	// レーザーデータの初期化
	laser[nextLaserIndex].x = startX;       // 初期座標x
	laser[nextLaserIndex].y = startY;       // 初期座標y
	laser[nextLaserIndex].vx = vx;          // 初期方向x
	laser[nextLaserIndex].vy = vy;          // 初期方向y
	laser[nextLaserIndex].Counter = 0;      // 経過時間カウンタ初期化
	laser[nextLaserIndex].ValidFlag = 1;    // レーザーを有効化

	// 次のレーザーインデックスを更新（0, 1, 2をループ）
	nextLaserIndex = (nextLaserIndex + 1) % 3;
}
///レーザー消去.
void MapGimmickLaserManager::DeleteLaser(int idx) {
	laser[idx].ValidFlag = 0;       //無効にする.
	laser[idx].Counter = 0;         //カウンターリセット.
}