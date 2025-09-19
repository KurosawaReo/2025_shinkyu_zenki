/*
   - Obst_Fireworks.cpp -

   障害物: 花火.
*/
#include "Player.h"
#include "GameManager.h"
#include "LaserManager.h"
#include "Obst_Fireworks.h"
//#include <cmath>    KRライブラリに定義が入ってるため不要.
//#include <cstdlib>

// 初期化
void FireworksManager::Init() {

	p_data     = GameData::GetPtr();
	p_player   = Player::GetPtr();
	p_laserMng = LaserManager::GetPtr();

	// 花火データの初期化
	for (int i = 0; i < FIREWORKS_CNT_MAX; i++) {
		fireworks[i].ValidFlag = 0;
		fireworks[i].x = 0.0f;
		fireworks[i].y = 0.0f;
		fireworks[i].targetX = 0.0f;
		fireworks[i].targetY = 0.0f;
		fireworks[i].vx = 0.0f;
		fireworks[i].vy = 0.0f;
		fireworks[i].Counter = 0.0f;
		fireworks[i].state = FIREWORKS_STATE_WARNING;
		fireworks[i].sparkCount = 0;
	}
}

// リセット
void FireworksManager::Reset() {
	spawnTimer = 120; // 最初は少し待機

	// 既存の花火をすべてクリア
	for (int i = 0; i < FIREWORKS_CNT_MAX; i++) {
		fireworks[i].ValidFlag = 0;
		fireworks[i].Counter = 0.0f;
		fireworks[i].state = FIREWORKS_STATE_WARNING;
	}
}

// ランダム位置生成
void FireworksManager::GenerateRandomPosition(float& x, float& y) {
	int margin = 80;
	x = (float)(margin + (rand() % (WINDOW_WID - margin * 2)));
	y = (float)(margin + (rand() % (WINDOW_HEI - margin * 2 - FIREWORKS_LAUNCH_HEIGHT)));
}

// 距離チェック(近すぎる花火がなければtrue)
bool FireworksManager::CheckDistance(float x, float y) {
	for (int i = 0; i < FIREWORKS_CNT_MAX; i++) {
		if (fireworks[i].ValidFlag == 1) {
			float dx = x - fireworks[i].targetX;
			float dy = y - fireworks[i].targetY;
			float distance = sqrt(dx * dx + dy * dy);
			if (distance < FIREWORKS_MIN_DISTANCE) {
				return false;
			}
		}
	}
	return true;
}

// 花火開始
void FireworksManager::StartFireworks(float x, float y) {
	for (int i = 0; i < FIREWORKS_CNT_MAX; i++) {
		if (fireworks[i].ValidFlag == 0) {
			fireworks[i].targetX = x;
			fireworks[i].targetY = y;
			fireworks[i].x = x;
			fireworks[i].y = y;
			fireworks[i].vx = 0.0f;
			fireworks[i].vy = 0.0f;
//			fireworks[i].Duration = FIREWORKS_WARNING_DURATION + 120; // 予告+爆発時間 //追記:いらない気がする
			fireworks[i].Counter = FIREWORKS_WARNING_DURATION;
			fireworks[i].state = FIREWORKS_STATE_WARNING;
			fireworks[i].sparkCount = FIREWORKS_SPARKS_COUNT + (rand() % 8);
			fireworks[i].ValidFlag = 1;
			break;
		}
	}
}

// 花火生成更新
void FireworksManager::UpdateFireworksGeneration() {
	spawnTimer -= (p_data->isSlow) ? SLOW_MODE_SPEED : 1;

	if (spawnTimer <= 0) {
		//1～3個の花火をランダム生成.
		int spawnCount = 1 + (rand() % FIREWORKS_RND_MAX);

		for (int i = 0; i < spawnCount; i++) {
			float x, y;
			bool validPosition = false;
			int attempts = 0;

			while (!validPosition && attempts < 10) {
				GenerateRandomPosition(x, y);
				validPosition = CheckDistance(x, y);
				attempts++;
			}

			if (validPosition) {
				StartFireworks(x, y);
			}
		}
		//出現カウンターリセット.
		spawnTimer = FIREWORKS_SPAWN_SPAN * p_data->spawnRate;
	}
}

// 個別花火更新
void FireworksManager::UpdateIndividualFireworks() {

	for (int i = 0; i < FIREWORKS_CNT_MAX; i++) {
		if (fireworks[i].ValidFlag == 0) continue;

		fireworks[i].Counter -= (p_data->isSlow) ? SLOW_MODE_SPEED : 1.0f;

		//警告表示.
		if (fireworks[i].Counter > 0) {
			fireworks[i].state = FIREWORKS_STATE_WARNING;
		}
		//爆発.
		else {
			////爆発モードじゃないなら変更.
			//if (fireworks[i].state != FIREWORKS_STATE_EXPLODING) {
			//	fireworks[i].state = FIREWORKS_STATE_EXPLODING;
			//	ExplodeFireworks(i);
			//}
			fireworks[i].ValidFlag = 0; //花火本体消滅.
			ExplodeFireworks(i);
		}
	}
}

// 爆発処理
void FireworksManager::ExplodeFireworks(int index) {
	CreateFireworksSparks(fireworks[index].x, fireworks[index].y);

	// 爆発音
	SoundMng* sound = SoundMng::GetPtr();
	sound->Play(_T("Explosion"), false, 70);
}

// 花火の火花作成（LaserManagerを使用）- 落下効果付き
void FireworksManager::CreateFireworksSparks(float x, float y) {
	int sparkCount = fireworks[0].sparkCount; // 仮で0番の火花数を使用

	for (int i = 0; i < sparkCount; i++) {
		float angle = _flt((2.0f * M_PI * i) / sparkCount);

		// 初期速度をランダムに調整
		float baseSpeed = 2.5f + (float)(rand() % 3); // 2.5~4.5の範囲
		float speedVariation = 0.8f + (float)(rand() % 4) / 10.0f; // 0.8~1.1の範囲
		float speed = baseSpeed * speedVariation;

		// 角度に少しランダム性を追加
		float angleVariation = _flt((float)(rand() % 40 - 20) * M_PI / 180.0f); // ±20度
		angle += angleVariation;

		DBL_XY pos = { x, y };
		DBL_XY vel = {
			cos(angle) * speed,
			sin(angle) * speed - 0.5f // 上向きにバイアスをかける
		};

		// 落下するレーザーとして生成
		p_laserMng->SpawnLaser(pos, vel, Laser_Falling);
	}
}

// 更新
void FireworksManager::Update() {
	UpdateFireworksGeneration();
	UpdateIndividualFireworks();
}

// 描画
void FireworksManager::Draw() {
	for (int i = 0; i < FIREWORKS_CNT_MAX; i++) {
		if (fireworks[i].ValidFlag == 0) continue;

		DrawWarningEffect(i);

//		if (fireworks[i].state == FIREWORKS_STATE_WARNING) {
//			DrawWarningEffect(i);
//		}
		// 爆発エフェクトは描画しない（波紋削除のため）
	}

	// 描画モードをリセット
	ResetDrawBlendMode();
}

// 予告エフェクト描画
void FireworksManager::DrawWarningEffect(int index) {

	const float sepTime = 30; //区切り時間.

	float elapsedTime = fireworks[index].Counter;

	// 点滅エフェクト
	int alphaValue;
	if (elapsedTime < sepTime) {
		double blinkPhase = fmod(elapsedTime, 20);
		double blinkAlpha = sin(blinkPhase * M_PI/20);
		alphaValue = (int)(255 - 150 * blinkAlpha);
	}
	else {
		alphaValue = 255;
	}

	// 脈動サイズ
	int warningSize;
	if (elapsedTime >= sepTime) {
		double pulseFactor = 1.0f + 0.3f * sin(elapsedTime * 4.0f * M_PI / 60.0f);
		warningSize = (int)(30 * pulseFactor);
	}
	else {
		warningSize = 30;
	}

	SetDrawBlendModeST(MODE_ALPHA, alphaValue);

	Circle cir;
	// 外側の円灰色
	cir = { {fireworks[index].targetX, fireworks[index].targetY}, (float)warningSize, GetColor(128, 128, 128) };
	DrawCircleST(&cir, false, true);
	// 内側の円灰色
	cir = { {fireworks[index].targetX, fireworks[index].targetY}, (float)(warningSize / 2), GetColor(128, 128, 128) };
	DrawCircleST(&cir, false, true);
	// 中心点灰色
	cir = { {fireworks[index].targetX, fireworks[index].targetY}, 5, GetColor(128,128, 128) };
	DrawCircleST(&cir, false, true);
}