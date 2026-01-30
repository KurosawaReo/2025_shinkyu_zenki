/*
   - Obst_StraightLaser.h -

   障害物: 直線レーザー.
*/
#pragma once

//直線レーザー発射台.
class StraightLaserPoint
{
private:
	float  laserSpawnTimer{};  // レーザー発射タイマー.
	float  predictionTimer{};  // 予測線タイマー.
	int    currentDirection{}; // 現在の発射方向
	double nextCenterPos{};    // 次のレーザー発射位置（予測線用）
	int    nextDirection{};    // 次の発射方向
	bool   isShowPreLine{};    // 予測線表示フラグ

public:
	void Init();
	void Reset();
	void Update();
	void Draw();

	void ShotLaser(); //直線レーザー発射.
	void DrawPreLine();
};

//直線レーザー.
class StraightLaser : public ManagerBase
{
//▼ ===== 実体 ===== ▼.
private:
	static StraightLaser inst;
public:
	static StraightLaser& GetInst() {
		return inst;
	}

//▼ ===== 変数 ===== ▼.
private:
	StraightLaserPoint points[2];

//▼ ===== 関数 ===== ▼.
private:
	//コンストラクタ.
	StraightLaser() : ManagerBase(ORDER_STR_LASER_MNG) {}

public:
	void Init()   override;
	void Reset()  override;
	void Update() override;
	void Draw()   override;

	//使用禁止.
	StraightLaser(const StraightLaser&) = delete;
	StraightLaser& operator=(const StraightLaser&) = delete;
};