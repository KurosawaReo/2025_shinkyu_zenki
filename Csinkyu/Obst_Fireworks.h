/*
   - Obst_Fireworks.h -

   障害物: 花火.
*/
#pragma once

// 花火の状態
enum FireworksState {
	FIREWORKS_STATE_WARNING,    // 予告状態
	FIREWORKS_STATE_EXPLODING,  // 爆発中
	FIREWORKS_STATE_FALLING     // 落下中
};

// 花火データ構造
struct FireworksData 
{
	FireworksState state;      // 現在の状態.

	float x, y;                // 座標
	float targetX, targetY;    // 目標座標（爆発位置）
	float vx, vy;              // 速度
	float counter;             // カウンタ
	int   sparkCount;          // 火花数

	int   fallDelay;           // 落下までの遅延
	bool  hasFallen;           // 落下済みか
};

//花火管理.
class FireworksManager : public ManagerBase
{
//▼ ===== 実体 ===== ▼.
public:
	static FireworksManager& GetInst() {
		static FireworksManager inst; //自身のインスタンス.
		return inst;
	}

//▼データ.
private:
	list<FireworksData> fireworks;
	float				spawnTimer{};

//▼ ===== 関数 ===== ▼.
private:
	//コンストラクタ
	FireworksManager() : ManagerBase(ORDER_FIREWORKS_MNG) {}

	void GenerateRandomPosition   (float& x, float& y);
	bool CheckDistance            (float x, float y);
	void SpawnFireworks           (float x, float y);
	void UpdateFireworksGeneration();
	void UpdateIndividualFireworks();
	void CreateFireworksSparks    (float x, float y);

	//描画用.
	void DrawWarningEffect(list<FireworksData>::iterator it);

public:
	void Init()   override;
	void Reset()  override;
	void Update() override;
	void Draw()   override;

	//使用禁止.
	FireworksManager(const FireworksManager&) = delete;
	FireworksManager& operator=(const FireworksManager&) = delete;
};