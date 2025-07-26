/*
   - Obstacle4main.h -

   レーザー砲台の継承元クラス.
*/
#pragma once

#include "LaserManager.h" //レーザー管理のヘッダーファイル.

typedef struct tagFLASHEFFECT
{
	double x, y;    // エフェクト位置.
	float Counter;  // 経過時間.
	float Duration; // エフェクトの持続時間.
	int BaseSize;   // 基本サイズ
	int ValidFlag; // 有効フラグ

	double angle;
}FLASHEFFECT;

//継承元となるクラス(親)
class Obstacle4main
{
protected:
	float   Hx{}, Hy{};  //砲台の位置.
	float   Hm{};        //砲台の移動方向.
	float   Hsc{};       //砲台のショット間隔カウンタ.
	float   HscTm{};     //砲台がショットする時間.
	MoveDir moveDir{};   //現在の移動方向.

//	IMG         img{};
	FLASHEFFECT flashEffect[OBSTACLE4_FLASH_MAX]{};	// クラスのメンバ変数として追加

	GameData*     p_data{};
	Player*       p_player{};
	MeteoManager* p_meteoMng{};
	LaserManager* p_laserMng{};

public:
	//基本処理.
	void Init  (GameData*, Player*, MeteoManager*, LaserManager*);
	void Reset (float _Hx, float _Hy, float _Hm, MoveDir);
	void Update();
	void Draw  ();
	//更新系.
	void UpdateObstFlash();
	//描画系.
	void DrawObstFlash();
	void DrawPreLaserDots();
	//移動系.
	void enemy4Move();
	virtual void Move() = 0; //砲台によって動きが違う→overrideを利用し、"動き"だけを変える.

	//出る直前の点滅.
	void CreateFlashEffect(double x, double y);
};
