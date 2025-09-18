/*
   - Ripples.cpp -

   障害物: 波紋.
*/
#include "GameManager.h"
#include "Player.h"

#include "Obst_Ripples.h"

//初期化(一回のみ行う)
//リセット(何回でも行う)
void Ripples::Init()
{
	//実体のアドレスをもらう.
	p_data   = GameData::GetPtr();
	p_player = Player::GetPtr();

	// フラッシュエフェクトの初期化
	for (int i = 0; i < RIPPLES_FLASH_MAX; i++) {
		flashEffect[i].ValidFlag = 0;
		flashEffect[i].Counter = 0.0f;
		flashEffect[i].Duration = 0.0f;
		flashEffect[i].x = 0.0;
		flashEffect[i].y = 0.0;
		flashEffect[i].BaseSize = 0;
	}
}
void Ripples::Reset()
{
	flashTimer = 80; //最初は少しだけ待機.

	// リセット時に既存のフラッシュエフェクトをすべてクリア
	for (int i = 0; i < RIPPLES_FLASH_MAX; i++) {
		flashEffect[i].ValidFlag = 0;
		flashEffect[i].Counter = 0.0f;
		flashEffect[i].Duration = 0.0f;
		flashEffect[i].x = 0.0;
		flashEffect[i].y = 0.0;
		flashEffect[i].BaseSize = 0;
	}
}

void Ripples::GenerateRandomPosition(double& x, double& y)  // 参照渡しに修正
{
	//画面サイズ
	int screnWidth = WINDOW_WID;
	int screnHeight = WINDOW_HEI;
	int margin = 100;//画面端からのマージン大き目.
	x = margin + (rand() % (screnWidth - margin * 2));
	y = margin + (rand() % (screnHeight - margin * 2));
}
bool Ripples::CheckDistance(double x, double y)
{
	for (int i = 0; i < RIPPLES_FLASH_MAX; i++)
	{
		if (flashEffect[i].ValidFlag == 1)
		{
			double dx = x - flashEffect[i].x;
			double dy = y - flashEffect[i].y;
			double distance = sqrt(dx * dx + dy * dy);  // dy * dy に修正
			if (distance < RIPPLES_MIN_DISTANCE)
			{
				return false;
			}
		}
	}
	return true;
}
// フラッシュエフェクトを開始する関数を追加
void Ripples::StartFlashEffect(double x, double y)
{
	// 空いているスロットを探す
	for (int i = 0; i < RIPPLES_FLASH_MAX; i++) {
		if (flashEffect[i].ValidFlag == 0) {
			flashEffect[i].x = x;
			flashEffect[i].y = y;
			flashEffect[i].Duration = RIPPLES_WARNING_DURATION + RIPPLES_ACTIVE_DURATION;
			flashEffect[i].Counter = flashEffect[i].Duration;  // 持続時間から開始（カウントダウン）
			flashEffect[i].BaseSize = 20;     // 適切な基本サイズに調整
			flashEffect[i].ValidFlag = 1;
			break;
		}
	}
}
void Ripples::SpawnObstaclegroup()
{
	//同時出現をランダムに決定.
	int spawnCount = 1 + (rand() % RIPPLES_MAX_SIMULTANEOUS);
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
int Ripples::GetEffectState(int index)
{
	if (flashEffect[index].Counter > RIPPLES_ACTIVE_DURATION)  // 残り時間がアクティブ時間より大きければ警告状態
	{
		return RIPPLES_STATE_WARNING;
	}
	else
	{
		return RIPPLES_STATE_ACTIVE;
	}
}

// 定期的にエフェクトを生成する関数を追加
void Ripples::UpdateFlashGeneration()
{
	//タイマー減少.
	flashTimer -= ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
	//0以下になったら実行.
	if (flashTimer <= 0) {
		// 新しいフラッシュエフェクトを生成
		SpawnObstaclegroup();  // ランダム位置に複数生成するように変更

		// GameDataのspawnRateを使用してインターバルを調整
		flashTimer = RIPPLES_SPAWN_SPAN * p_data->spawnRate;
	}

	//全フラッシュ.
	for (int i = 0; i < RIPPLES_FLASH_MAX; i++)
	{
		if (flashEffect[i].ValidFlag == 0)
		{
			continue;//無効なエフェクトをスキップ.
		}

		//カウントダウン.
		flashEffect[i].Counter -= (p_data->isSlow) ? (float)SLOW_MODE_SPEED : 1.0f;
		//エフェクト時間が終了したら無効化.
		if (flashEffect[i].Counter <= 0)  // 0以下になったら終了
		{
			flashEffect[i].ValidFlag = 0;
			flashEffect[i].AlreadyHit = false; //当たり判定のリセット.
		}
	}
}
//更新.
void Ripples::Update()
{
	UpdateFlashGeneration();
	Hitjudgment();
}

//描画.
void Ripples::Draw()
{
	DrawObstFlash();
}
//当たり判定.
void Ripples::Hitjudgment()
{
	bool isPlaySound = false; //一度のみサウンドを流す用.

	for (int i = 0; i < RIPPLES_FLASH_MAX; i++) {
		if (flashEffect[i].ValidFlag == 0 || flashEffect[i].Counter <= 0) {
			continue;
		}

		int effectState = GetEffectState(i);
		if (effectState == RIPPLES_STATE_WARNING) {
			continue;
		}

		// 経過時間の計算
		float elapsedTime = flashEffect[i].Duration - flashEffect[i].Counter;
		float activeElapsedTime = elapsedTime - RIPPLES_WARNING_DURATION;
		float activeProgress = activeElapsedTime / RIPPLES_ACTIVE_DURATION;

		// アクティブ状態になった直後だけ判定
		if (effectState == RIPPLES_STATE_ACTIVE && !flashEffect[i].AlreadyHit) {

			float sizeMultiplier = RIPPLES_FLASH_SIZE_INIT + (activeProgress * RIPPLES_FLASH_SIZE_SPREAD);
			int effectSize = (int)(flashEffect[i].BaseSize * sizeMultiplier);

			DBL_XY playerPos = p_player->GetPos();
			double dx = playerPos.x - flashEffect[i].x;
			double dy = playerPos.y - flashEffect[i].y;
			double distance = sqrt(dx * dx + dy * dy);
			float playerRadius = 10.0f;

			if (distance < (effectSize * 0.8f + playerRadius)) {
				p_player->PlayerDeath();
			}

			//サウンド.
			if (!isPlaySound) {
				SoundMng* sound = SoundMng::GetPtr();
				sound->Play(_T("Ripples"), false, 73);
				isPlaySound = true; //もう再生しない.
			}

			// 一度判定を行ったらフラグを立てて、以後は無効に
			flashEffect[i].AlreadyHit = true;
		}
	}
}

void Ripples::DrawObstFlash()
{
	for (int i = 0; i < RIPPLES_FLASH_MAX; i++)
	{
		if (flashEffect[i].ValidFlag == 0)
		{
			continue;//無効なエフェクトをスキップ.
		}
		int effetState = GetEffectState(i);
		if (effetState == RIPPLES_STATE_WARNING)
		{
			// 予告状態の描画（赤い点滅エフェクト）
			DrawWarningEffect(i);
		}
		else
		{
			// アクティブ状態の描画（元のフラッシュエフェクト）
			DrawActiveEffect(i);
		}
	}
	//通常の描画モードに戻す
	ResetDrawBlendMode();
}

void Ripples::DrawWarningEffect(int index)
{
	//残り時間から経過時間を計算.
	float elapsedTime = flashEffect[index].Duration - flashEffect[index].Counter;

	//1: 透明度の計算(点滅)
	int alphaValue;
	//攻撃前になるまで点滅.
	if (elapsedTime < 90) {
		double blinkPhase = fmod(elapsedTime, RIPPLES_FLASH_BLINK_TM);
		double blinkAlpha = sin(blinkPhase * M_PI/RIPPLES_FLASH_BLINK_TM); //0.0～1.0を往復するっぽい.
		alphaValue = (int)(255 - 200*blinkAlpha);
	}
	else {
		alphaValue = 255; //最大値.
	}

	//2: サイズの計算.
	int warningSize;
	//攻撃前になったら脈動開始.
	if (elapsedTime >= 90) {
		const float pulseRate = 4.0f;
		double pulseFactor = 1.0f + 0.4f * sin(elapsedTime * pulseRate * M_PI/60.0f);
		warningSize = (int)(flashEffect[index].BaseSize * pulseFactor);
	}
	else {
		warningSize = flashEffect[index].BaseSize; //固定サイズ.
	}

	// 予告エフェクトを描画.
	SetDrawBlendModeST(MODE_ALPHA, alphaValue);

	Circle cir;
	cir = { {flashEffect[index].x, flashEffect[index].y}, (float)warningSize,   GetColor(150, 150, 150) };
	DrawCircleST(&cir, false, true);
	cir = { {flashEffect[index].x, flashEffect[index].y}, (float)warningSize/2, GetColor(200, 200, 200) };
	DrawCircleST(&cir, false, true);
	cir = { {flashEffect[index].x, flashEffect[index].y}, (float)warningSize+5, GetColor(120, 120, 120) }; // 外周リング
	DrawCircleST(&cir, false, true);

	//通常の描画モードに戻す
	ResetDrawBlendMode();
}

void Ripples::DrawActiveEffect(int index)
{
	// 残り時間から経過時間を計算
	float elapsedTime = flashEffect[index].Duration - flashEffect[index].Counter;
	float activeElapsedTime = elapsedTime - RIPPLES_WARNING_DURATION;

	// アクティブ状態での進行度
	float activeProgress = activeElapsedTime / RIPPLES_ACTIVE_DURATION;

	// 透明度を時間に応じて計算
	float alpha = 1.0f - (activeProgress * RIPPLES_FLASH_ALPHA_TM);
	int alphaValue = (int)(255 * max(alpha, 0.0f));

	// エフェクトのサイズを時間に応じて拡大
	float sizeMultiplier = RIPPLES_FLASH_SIZE_INIT + (activeProgress * RIPPLES_FLASH_SIZE_SPREAD);
	int effectSize = (int)(flashEffect[index].BaseSize * sizeMultiplier);
	int innerSize = effectSize / 2;

	// アクティブエフェクトを円形で描画（シアン色で光る）
	SetDrawBlendModeST(MODE_ADD, alphaValue);

	Circle cir;
	cir = {{flashEffect[index].x, flashEffect[index].y}, (float)effectSize, GetColor(0, 255, 255)};
	DrawCircleST(&cir, false, true);
	cir = {{flashEffect[index].x, flashEffect[index].y}, (float)innerSize,  GetColor(0, 255, 200)};
	DrawCircleST(&cir, false, true);

	//通常の描画モードに戻す
	ResetDrawBlendMode();
}