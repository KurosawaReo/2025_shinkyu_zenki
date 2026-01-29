/*
   - Obst_NormalLaserMain.h -

   障害物: レーザー発射台(継承元)
*/
#pragma once

//移動方向.
//レーザー(normal)砲台用.
enum MoveDir
{
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN
};

struct FlashEffect
{
	double	x, y;		// エフェクト位置.
	float	counter;	// 経過時間.
	float	Duration;	// エフェクトの持続時間.
	int		BaseSize;   // 基本サイズ
	int		validFlag;  // 有効フラグ

	double	angle;
};

//継承元となるクラス(親)
class NormalLaserMain : public ManagerBase
{
protected:
	float   Hx{}, Hy{};  //砲台の位置.
	float   Hm{};        //砲台の移動方向.
	float   Hsc{};       //砲台のショット間隔カウンタ.
	float   HscTm{};     //砲台がショットする時間.
	MoveDir moveDir{};   //現在の移動方向.

	FlashEffect    flash[LASER_NOR_FLASH_MAX]{};

public:
	//コンストラクタ.
	NormalLaserMain() : ManagerBase(ORDER_NOR_LASER_MNG) {}

	//基本処理.
	void Init  () override;
	void Reset () override;
	void Update() override;
	void Draw  () override;

	//更新系.
	void UpdateObstFlash();
	//描画系.
	void DrawObstFlash();
	void DrawPreLaserDots();
	//移動系.
	void enemy4Move();
	virtual void Move() = 0; //砲台によって動きが違う→overrideを利用し、"動き"だけを変える.
	//ランダムMove
	void MoveRand();
	//出る直前の点滅.
	void CreateFlashEffect(double x, double y);
};
