/*
   - Obstacle4.cpp -
   障害物管理クラス (小田島作)
   プレイヤーを追尾するレーザーを発射する障害物を実装
*/
#include "DxLib.h"     // DXライブラリのヘッダーファイルをインクルード
#include <math.h>      // 数学関数を使用するためのヘッダーファイル
#include "Player.h"    // プレイヤークラスのヘッダーファイル
#include "Obstacle4.h" // 自身のヘッダーファイル

/**
 * @brief 障害物の初期化処理
 * @param _player プレイヤーオブジェクトへのポインタ
 */
void Obstacle4::Init(GameData* _data, Player* _player)
{
	data   = _data;
	player = _player;  // プレイヤーオブジェクトを参照として保存
	
	Reset();
}

//リセット.
void Obstacle4::Reset() {

	Hx  = 320;            // 砲台のX座標初期値（画面中央）
	Hy  = 30;             // 砲台のY座標初期値（画面上部）
	Hm  = 3;              // 砲台の移動速度
	Hsc = OBSTACLE4_SPAN; // 砲台の発射カウンタ初期値

	// レーザーデータの初期化
	for (int i = 0; i < OBSTACLE4_MAX_L; i++)
		Ld[i].ValidFlag = 0;  // すべてのレーザーを無効状態に

	// レーザーの軌跡データの初期化
	for (int i = 0; i < OBSTACLE4_LINE_MAX; i++)
		Line[i].ValidFlag = 0;  // すべての軌跡を無効状態に
}

/**
 * @brief 障害物の更新処理
 * プレイヤーが有効な場合のみ障害物の動きを更新
 */
void Obstacle4::Update()
{
	if (player->GetActive()) {  // プレイヤーがアクティブな場合のみ
		enemy4Move();           // 障害物の移動処理を実行
	}
}

/**
 * @brief 障害物の描画処理
 * レーザーの軌跡と砲台を描画
 */
void Obstacle4::Draw()
{
	// 加算合成モードで軌跡を描画（発光エフェクト）
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// レーザーの軌跡の描画処理
	for (int i = 0; i < OBSTACLE4_LINE_MAX; i++)
	{
		if (Line[i].ValidFlag == 0) continue;  // 無効な軌跡はスキップ

		// 軌跡の線を描画（時間経過で色が変化）
		DrawLine(Line[i].x1, Line[i].y1,
			Line[i].x2, Line[i].y2,
			GetColor(0, 255 - Line[i].Counter * 4, 0));  // 緑色で、時間経過で徐々に薄くなる

		// 経過時間カウンタ増加
		Line[i].Counter += (data->isSlow) ? (float)SLOW_MODE_SPEED : 1;
		// 64フレーム経過したら軌跡を無効化
		if (Line[i].Counter >= 64) Line[i].ValidFlag = 0;
	}

	// 通常の描画モードに戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// 動く砲台を描画
	Box box = { {Hx, Hy}, {8, 8}, GetColor(100, 100, 100) }; //{pos}, {size}, color.
	DrawBoxST(&box, TRUE);
}

/**
 * @brief 敵（障害物）の移動処理
 * レーザーの移動とプレイヤーへの追尾、砲台の移動とレーザー発射を管理
 */
void Obstacle4::enemy4Move()
{
	// 各レーザーの処理
	for (int i = 0; i < OBSTACLE4_MAX_L; i++)
	{
		int xb, yb;  // 前回位置を保存する変数
		if (Ld[i].ValidFlag == 0) continue;  // 無効なレーザーはスキップ

		// プレイヤーの現在位置を取得
		DBL_XY playerPos = player->GetPos();
		double Px = playerPos.x;
		double Py = playerPos.y;
		double halfSize = PLAYER_SIZE / 2.0;  // プレイヤーの当たり判定サイズの半分

		// プレイヤーとレーザーの当たり判定
		if ((Ld[i].x > Px - halfSize && Ld[i].x < Px + halfSize) &&
			(Ld[i].y > Py - halfSize && Ld[i].y < Py + halfSize))
		{
			Ld[i].ValidFlag = 0;  // 当たったらレーザーを無効化
			player->PlayerDeath();
			continue;
		}

		// レーザーの追尾処理（発射後一定時間のみ）
		if (Ld[i].Counter < 200)  // 200フレーム（約3.3秒）以内のみ追尾
		{
			// 現在のプレイヤー方向への角度を計算
			double targetAngle = atan2(Py - Ld[i].y, Px - Ld[i].x);
			// レーザーの現在の移動方向の角度
			double currentAngle = atan2(Ld[i].sy, Ld[i].sx);
			// 角度の差分を計算
			double angleDiff = targetAngle - currentAngle;

			// 角度差分を-PI～PIの範囲に正規化
			while (angleDiff >  M_PI) angleDiff -= 2 * M_PI;
			while (angleDiff < -M_PI) angleDiff += 2 * M_PI;

			// 最大旋回角度を制限（1フレームに15度まで）
			const double maxTurn = M_PI/180 * 15;
			if (angleDiff > maxTurn) angleDiff = maxTurn;
			if (angleDiff < -maxTurn) angleDiff = -maxTurn;

			// 新しい角度を計算して速度を更新
			double newAngle = currentAngle + angleDiff;
			Ld[i].sx += (int)(cos(newAngle) * 30);  // X方向速度を更新
			Ld[i].sy += (int)(sin(newAngle) * 30);  // Y方向速度を更新
		}

		// レーザーの経過時間カウンタを増加
		Ld[i].Counter += (data->isSlow) ? (float)SLOW_MODE_SPEED : 1;

		// 移動前の座標を保存
		xb = Ld[i].x;
		yb = Ld[i].y;

		// ミサイルの速度
		double speed = OBSTACLE4_SPEED;
		if (data->isSlow) { speed /= SLOW_MODE_SPEED; }

		// レーザーの位置を更新（速度に基づいて移動）
		Ld[i].x = _int((Ld[i].x * speed + Ld[i].sx)/speed);
		Ld[i].y = _int((Ld[i].y * speed + Ld[i].sy)/speed);

		// レーザーの軌跡を生成
		for (int j = 0; j < OBSTACLE4_LINE_MAX; j++)
		{
			if (Line[j].ValidFlag == 0)  // 未使用の軌跡スロットを探す
			{
				// 軌跡データの設定
				Line[j].x1 = xb;           // 開始点X座標
				Line[j].y1 = yb;           // 開始点Y座標
				Line[j].x2 = Ld[i].x;      // 終了点X座標
				Line[j].y2 = Ld[i].y;      // 終了点Y座標
				Line[j].Counter = 0;       // 経過時間カウンタ初期化
				Line[j].ValidFlag = 1;     // 軌跡を有効化
				break;
			}
		}

		// 画面外に出たレーザーを無効化
		if (Ld[i].x < -100 || Ld[i].x > WINDOW_WID + 100 ||
			Ld[i].y < -100 || Ld[i].y > WINDOW_HEI + 100)
		{
			Ld[i].ValidFlag = 0;
		}
	}

	// 砲台の移動とレーザー発射処理
	{
		// 砲台をX方向に移動
		Hx += Hm * ((data->isSlow) ? (float)SLOW_MODE_SPEED : 1);
		// 画面端で反射
		if (Hm > 0 && Hx > WINDOW_WID - 16) {
			Hm *= -1;
		}
		if (Hm < 0 && Hx < 0) {
			Hm *= -1;
		}

		// 発射カウンタを減少
		Hsc -= (data->isSlow) ? (float)SLOW_MODE_SPEED : 1;
		// タイミングが来たらレーザー発射
		if (Hsc <= HscTm)
		{
			// 未使用のレーザースロットを探してレーザーを発射
			for (int i = 0; i < OBSTACLE4_MAX_L; i++)
			{
				if (Ld[i].ValidFlag == 0)  // 未使用のレーザースロットを見つけた
				{
					// プレイヤー座標取得
					DBL_XY playerPos = player->GetPos();
					double Px = playerPos.x;
					double Py = playerPos.y;

					// 発射位置（砲台の少し下から）
					double startX = Hx + 16;
					double startY = Hy + 16;
					
					// プレイヤー方向への初期角度計算
					double angle = atan2(Py - startY, Px - startX);

					// レーザーデータの初期化
					Ld[i].x = _int(startX);				// 初期X座標
					Ld[i].y = _int(startY);				// 初期Y座標
					Ld[i].sx = (int)(cos(angle) * 30);  // X方向初期速度
					Ld[i].sy = (int)(sin(angle) * 30);  // Y方向初期速度
					Ld[i].Counter = 0;					// 経過時間カウンタ初期化
					Ld[i].LogNum = 0;					// 軌跡カウンタ初期化
					Ld[i].ValidFlag = 1;				// レーザーを有効化
					break;
				}
			}
			HscTm -= 15; //発射タイミングを変更.
		}
		//0秒を下回ったらもう一周.
		if (Hsc <= 0) {
			Hsc = OBSTACLE4_SPAN;  // 発射カウンタをリセット（次の発射までの待機時間）
			HscTm = 30;
		}
	}
}