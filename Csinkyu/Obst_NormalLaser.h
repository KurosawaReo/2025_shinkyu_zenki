/*
   - Obst_NormalLaser.h -

   障害物: レーザー発射台(継承先)
   個体によって違う動きをするため、overrideを使用.
*/
#pragma once
#include "Obst_NormalLaserMain.h"

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