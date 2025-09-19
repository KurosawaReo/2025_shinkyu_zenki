/*
   - Obst_Fireworks.h -

   障害物: 花火.
*/
#pragma once

class GameData; //前方宣言.
class Player;   //前方宣言.

// 花火の状態
enum FireworksState {
	FIREWORKS_STATE_WARNING,    // 予告状態
	FIREWORKS_STATE_EXPLODING,  // 爆発中
	FIREWORKS_STATE_FALLING     // 落下中
};

// 花火データ構造
struct FireworksData {
	int ValidFlag;              // 有効フラグ
	float x, y;                 // 座標
	float targetX, targetY;     // 目標座標（爆発位置）
	float vx, vy;              // 速度
	float Counter;             // カウンタ
	float Duration;            // 持続時間
	FireworksState state;      // 現在の状態
	int sparkCount;            // 火花数

	int fallDelay;   // 落下までの遅延
	bool hasFallen;  // 落下済みか
};

//花火管理.[継承不可]
class FireworksManager final 
{
public: //実体.
	static FireworksManager* GetPtr() {
		static FireworksManager inst; //自身のインスタンス.
		return &inst;
	}

private: //変数.
	FireworksData fireworks[FIREWORKS_MAX];
	float spawnTimer;

	GameData*     p_data;
	Player*       p_player;
	LaserManager* p_laserMng;

private: //関数.
	void GenerateRandomPosition(float& x, float& y);
	bool CheckDistance(float x, float y);
	void StartFireworks(float x, float y);
	void UpdateFireworksGeneration();
	void UpdateIndividualFireworks();
	void ExplodeFireworks(int index);
	void CreateFireworksSparks(float x, float y);

	// 描画関数
	void DrawWarningEffect(int index);

public:
	void Init();
	void Reset();
	void Update();
	void Draw();
};