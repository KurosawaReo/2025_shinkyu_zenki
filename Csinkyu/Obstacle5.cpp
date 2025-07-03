#include "GameManager.h"
#include "Player.h"

#include "Obstacle5.h"

//初期化(一回のみ行う)
//リセット(何回でも行う)
void Obstacle5::Init(GameData* data, Player* player)
{
	//実体のアドレスをもらう.
	this->data = data;
	this->player = player;

	// フラッシュエフェクトの初期化
	for (int i = 0; i < OBSTACLE5_FLASH_MAX; i++) {
		flashEffect[i].ValidFlag = 0;
		flashEffect[i].Counter = 0.0f;
		flashEffect[i].Duration = 0.0f;
		flashEffect[i].x = 0.0;
		flashEffect[i].y = 0.0;
		flashEffect[i].BaseSize = 0;
	}
}
void Obstacle5::Reset(double x, double y, float speed, int direction)
{
	line.stPos.x = x;
	line.stPos.y = y;
	this->speed = speed;
	// direction は必要に応じて使用

	// リセット時にフラッシュエフェクトを開始
	StartFlashEffect(x, y);
}

// フラッシュエフェクトを開始する関数を追加
void Obstacle5::StartFlashEffect(double x, double y)
{
	// 空いているスロットを探す
	for (int i = 0; i < OBSTACLE5_FLASH_MAX; i++) {
		if (flashEffect[i].ValidFlag == 0) {
			flashEffect[i].x = x;
			flashEffect[i].y = y;
			flashEffect[i].Counter = 0.0f;
			flashEffect[i].Duration = 60.0f;  // 適切な持続時間に調整
			flashEffect[i].BaseSize = 20;     // 適切な基本サイズに調整
			flashEffect[i].ValidFlag = 1;
			break;
		}
	}
}

// 定期的にエフェクトを生成する関数を追加
void Obstacle5::UpdateFlashGeneration()
{
	static int flashTimer = 0;
	static int flashInterval = 120; // 2秒間隔（60FPS想定）

	flashTimer++;
	if (flashTimer >= flashInterval) {
		// 新しいフラッシュエフェクトを生成
		StartFlashEffect(line.stPos.x, line.stPos.y);
		flashTimer = 0;
	}
}
//更新.
void Obstacle5::Update()
{
	Hitjudgment();
}


//描画.
void Obstacle5::Draw()
{
	DrawObstFlash();
}
void Obstacle5::Hitjudgment()
{

	// フラッシュエフェクトとプレイヤーの当たり判定
	for (int i = 0; i < OBSTACLE5_FLASH_MAX; i++)
	{
		if (flashEffect[i].ValidFlag == 0)
		{
			continue; // 無効なエフェクトをスキップ
		}

		// エフェクトのサイズを時間に応じて拡大（描画と同じ計算）
		float sizeMultiplier = OBSTACLE5_FLASH_SIZE_INIT + (
			flashEffect[i].Counter * OBSTACLE5_FLASH_SIZE_SPREAD / flashEffect[i].Duration
			);
		int effectSize = _int(flashEffect[i].BaseSize * sizeMultiplier);

		// プレイヤーの位置を取得
		DBL_XY playerPos = player->GetPos();

		// プレイヤーとエフェクト円の距離を計算
		double dx = playerPos.x - flashEffect[i].x;
		double dy = playerPos.y - flashEffect[i].y;
		double distance = sqrt(dx * dx + dy * dy);

		// プレイヤーの当たり判定半径（適切な値に調整してください）
		float playerRadius = 10.0f; // または player->GetHitSize() など、実際のメソッドがあれば使用

		// 円同士の当たり判定
		if (distance < (effectSize + playerRadius))
		{
			player->PlayerDeath();
			return; // 一度死んだら処理終了
		}
	}

}
void Obstacle5::DrawObstFlash()
{
	for (int i = 0; i < OBSTACLE5_FLASH_MAX; i++)
	{
		if (flashEffect[i].ValidFlag == 0)
		{
			continue;//無効なエフェクトをスキップ.
		}
		//エフェクトの透明度を時間に応じて計算.
		float alpha = 1.0f - (
			flashEffect[i].Counter * OBSTACLE5_FLASH_ALPHA_TM / flashEffect[i].Duration
			);
		int alphaValue = (int)(255 * alpha);
		alphaValue = max(alphaValue, 0); //下限は0.
		//エフェクトのサイズを時間に応じて拡大.
		float sizeMultiplier = OBSTACLE5_FLASH_SIZE_INIT + (
			flashEffect[i].Counter * OBSTACLE5_FLASH_SIZE_SPREAD / flashEffect[i].Duration
			);
		int effectSize = (int)(flashEffect[i].BaseSize * sizeMultiplier);
		int innerSize = effectSize / 2;

		//発射エフェクトを円形で描画(白く光る)
		SetDrawBlendModeST(MODE_ADD, alphaValue);
		DrawCircle((int)(flashEffect[i].x), (int)(flashEffect[i].y), effectSize, GetColor(0, 255, 255), FALSE);
		DrawCircle((int)(flashEffect[i].x), (int)(flashEffect[i].y), innerSize, GetColor(0, 255, 200), FALSE); // 内側により明るい円を描画

		//エフェクトのカウンタを更新
		flashEffect[i].Counter += (data->isSlow) ? (float)SLOW_MODE_SPEED : 1.0f;

		//エフェクト時間が終了したら無効化して新しいエフェクトを開始
		if (flashEffect[i].Counter >= flashEffect[i].Duration)
		{
			// 現在の位置を保存
			double currentX = flashEffect[i].x;
			double currentY = flashEffect[i].y;

			// 現在のエフェクトを無効化
			flashEffect[i].ValidFlag = 0;

			// 新しいエフェクトを開始（連続表示するため）
			StartFlashEffect(currentX, currentY);
		}
	}
	//通常の描画モードに戻す
	ResetDrawBlendMode();
}