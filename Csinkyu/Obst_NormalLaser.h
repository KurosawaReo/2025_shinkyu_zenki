/*
   - Obst_NormalLaser.h -

   障害物: レーザー発射台(継承元)
*/
#pragma once

//移動方向(+1すれば右回転)
enum MoveDir
{
	Left,
	Up,
	Right,
	Down,

	Count, //総数.
};
struct MoveInfo
{
	DBL_XY  vec;    //移動方向ベクトル.
	MoveDir dir;    //今の方向(回転用)
	bool    isLeft; //true = 左回り, false = 右回り.
};

//予告エフェクト.
struct FlashEffect
{
	double	x, y;		// エフェクト位置.
	float	counter;	// 経過時間.
	float	Duration;	// エフェクトの持続時間.
	int		BaseSize;   // 基本サイズ
	bool	validFlag;  // 有効フラグ

	double	angle;
};

//レーザー発射台.
class LaserPoint
{
public:
	DBL_XY   pos;       //位置.
	MoveInfo move;      //移動データ.
	float    speed;     //移動速度.
	float    counter;   //経過カウンター.
	float    counterTm; //発射するタイミング.
	bool	 validFlag; //有効フラグ.

	void MoveRand(); //移動方向抽選.
};

//通常レーザー管理クラス.
class NormalLaser : public ManagerBase
{
//▼ ===== 実体 ===== ▼.
public:
	static NormalLaser& GetInst() {
		static NormalLaser inst; //自身のインスタンス.
		return inst;
	}

//▼ ===== 変数 ===== ▼.
private:
	LaserPoint  points[4]; //レーザー発射台.
	FlashEffect flash[LASER_NOR_FLASH_MAX] {};

//▼ ===== 変数 ===== ▼.
public:
	//コンストラクタ.
	NormalLaser() : ManagerBase(ORDER_NOR_LASER_MNG) {}

	//基本処理.
	void Init  () override;
	void Reset () override;
	void Update() override;
	void Draw  () override;

	//更新系.
	void UpdatePoint();
	//描画系.
	void DrawObstFlash();
	void DrawPreLaserDots();
 
	void CreateFlashEffect(double x, double y);

	//何個発射台を使うか.
	static void UseLaserPointCnt(int count);
};
