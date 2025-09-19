/*
   - Obst_NormalLaser.h -

   障害物: レーザー発射台(継承先)
   個体によって違う動きをするため、overrideを使用.
*/
#pragma once
#include "Obst_NormalLaserMain.h"

//#define MAX_L 100 //ミサイルが飛ぶ最大距離.
//#define PI 3.14159//円周率.
//#define LINE_MAXNUM 3000//描画する線の最大数.

//継承先クラス(子1)
class NormalLaser_1 : public NormalLaserMain
{
public:
	void Move() override;
};

//継承先クラス(子2)
class NormalLaser_2 : public NormalLaserMain
{
public:
	void Move() override;
};

//継承先クラス(子3)
class NormalLaser_3 : public NormalLaserMain
{
public:
	void Move() override;
};

//継承先クラス(子4)
class NormalLaser_4 : public NormalLaserMain
{
public:
	void Move() override;
};