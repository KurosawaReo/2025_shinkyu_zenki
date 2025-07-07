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

void Obstacle5::GenerateRandomPosition(double& x, double& y)  // 参照渡しに修正
{
	//画面サイズ
	int screnWidth = WINDOW_WID;
	int screnHeight = WINDOW_HEI;
	int margin = 100;//画面端からのマージン大き目.
	x = margin + (rand() % (screnWidth - margin * 2));
	y = margin + (rand() % (screnHeight - margin * 2));
}
bool Obstacle5::CheckDistance(double x, double y)
{
	for (int i = 0; i < OBSTACLE5_FLASH_MAX; i++)
	{
		if (flashEffect[i].ValidFlag == 1)
		{
			double dx = x - flashEffect[i].x;
			double dy = y - flashEffect[i].y;
			double distance = sqrt(dx * dx + dy * dy);  // dy * dy に修正
			if (distance < OBSTACLE5_MIN_DISTANCE)
			{
				return false;
			}
		}
	}
	return true;
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
			flashEffect[i].Duration = OBSTACLE5_WARNING_DURATION + OBSTACLE5_ACTIVE_DURATION;;  // 適切な持続時間に調整
			flashEffect[i].BaseSize = 20;     // 適切な基本サイズに調整
			flashEffect[i].ValidFlag = 1;
			break;
		}
	}
}
void Obstacle5::SpawnObstaclegroup()
{
	//同時出現をランダムに決定.
	int spawnCount = 1 + (rand() % OBSTACLE5_MAX_SIMULTANEOUS);
	for (int i = 0; i < spawnCount; i++)
	{
		double x{}, y{};
		bool validPosition = false;
		int attempts = 0;

		while (!validPosition && attempts < 10)
		{
			GenerateRandomPosition(x, y);
			validPosition = CheckDistance(x, y);
			attempts++;
		}
		if (validPosition)
		{
			StartFlashEffect(x, y);
		}
	}
}
int Obstacle5::GetEffectState(int index)
{
	if (flashEffect[index].Counter < OBSTACLE5_WARNING_DURATION)  // 比較演算子に修正
	{
		return OBSTACLE5_STATE_WARNING;
	}
	else
	{
		return OBSTACLE5_STATE_ACTIVE;
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
		SpawnObstaclegroup();  // ランダム位置に複数生成するように変更
		flashTimer = 0;
	}
}
//更新.
void Obstacle5::Update()
{
	UpdateFlashGeneration();
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

		// エフェクトの状態を確認
		int effectState = GetEffectState(i);

		// 予告状態の場合は当たり判定をスキップ
		if (effectState == OBSTACLE5_STATE_WARNING)
		{
			continue;
		}

		// エフェクトのサイズを時間に応じて拡大（描画と同じ計算）
		float sizeMultiplier = OBSTACLE5_FLASH_SIZE_INIT + (
			flashEffect[i].Counter * OBSTACLE5_FLASH_SIZE_SPREAD / flashEffect[i].Duration
			);
		int effectSize = (int)(flashEffect[i].BaseSize * sizeMultiplier);

		// プレイヤーの位置を取得
		DBL_XY playerPos = player->GetPos();

		// プレイヤーとエフェクト円の距離を計算
		double dx = playerPos.x - flashEffect[i].x;
		double dy = playerPos.y - flashEffect[i].y;
		double distance = sqrt(dx * dx + dy * dy);

		// プレイヤーの当たり判定半径（適切な値に調整してください）
		float playerRadius = 10.0f; // または player->GetHitSize() など、実際のメソッドがあれば使用

		// 円同士の当たり判定
		if (distance < (effectSize * 0.8f + playerRadius))
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
		int effetState = GetEffectState(i);
		if (effetState == OBSTACLE5_STATE_WARNING)
		{
			// 予告状態の描画（赤い点滅エフェクト）
			DrawWarningEffect(i);
		}
		else
		{
			// アクティブ状態の描画（元のフラッシュエフェクト）
			DrawActiveEffect(i);
		}
		// カウンタの更新を修正
		flashEffect[i].Counter += (data->isSlow) ? (float)SLOW_MODE_SPEED : 1.0f;

		//エフェクト時間が終了したら無効化.
		if (flashEffect[i].Counter >= flashEffect[i].Duration)
		{
			flashEffect[i].ValidFlag = 0;
		}
	}
	//通常の描画モードに戻す
	ResetDrawBlendMode();
}
void Obstacle5::DrawWarningEffect(int index)
{
	float blinkRate = 8.0f;
	float blinkPhase = fmod(flashEffect[index].Counter * blinkRate, 60.0f);
	float blinkAlpha = (sin(blinkPhase * 3.14f / 30.0f) + 1.0f) * 0.5f;
	// 脈動効果
	float pulseRate = 4.0f;
	float pulseFactor = 1.0f + 0.4f * sin(flashEffect[index].Counter * pulseRate * 3.14159f / 60.0f);
	int warningSize = (int)(flashEffect[index].BaseSize * pulseFactor);

	int alphaValue = (int)(255 * blinkAlpha * 0.8f);

	// 予告エフェクトを描画（赤色）
	SetDrawBlendModeST(MODE_ADD, alphaValue);
	DrawCircle((int)(flashEffect[index].x), (int)(flashEffect[index].y), warningSize, GetColor(255, 100, 100), FALSE);
	DrawCircle((int)(flashEffect[index].x), (int)(flashEffect[index].y), warningSize / 2, GetColor(255, 150, 150), FALSE);

	// 外周リング
	DrawCircle((int)(flashEffect[index].x), (int)(flashEffect[index].y), warningSize + 5, GetColor(255, 50, 50), FALSE);
}
void Obstacle5::DrawActiveEffect(int index)
{
	// アクティブ状態での進行度
	float activeProgress = (flashEffect[index].Counter - OBSTACLE5_WARNING_DURATION) / OBSTACLE5_ACTIVE_DURATION;

	// 透明度を時間に応じて計算
	float alpha = 1.0f - (activeProgress * OBSTACLE5_FLASH_ALPHA_TM);
	int alphaValue = (int)(255 * max(alpha, 0.0f));

	// エフェクトのサイズを時間に応じて拡大
	float sizeMultiplier = OBSTACLE5_FLASH_SIZE_INIT + (activeProgress * OBSTACLE5_FLASH_SIZE_SPREAD);
	int effectSize = (int)(flashEffect[index].BaseSize * sizeMultiplier);
	int innerSize = effectSize / 2;

	// アクティブエフェクトを円形で描画（シアン色で光る）
	SetDrawBlendModeST(MODE_ADD, alphaValue);
	DrawCircle((int)(flashEffect[index].x), (int)(flashEffect[index].y), effectSize, GetColor(0, 255, 255), FALSE);
	DrawCircle((int)(flashEffect[index].x), (int)(flashEffect[index].y), innerSize, GetColor(0, 255, 200), FALSE);
}