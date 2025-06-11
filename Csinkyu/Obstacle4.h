/*
   - Obstacle3.h -
   障害物管理.
*/
#pragma once
#include "Player.h"
#include"Obstacle4main.h"

//#define MAX_L 100 //ミサイルが飛ぶ最大距離.
//#define PI 3.14159//円周率.
//#define LINE_MAXNUM 3000//描画する線の最大数.

//継承先クラス(子1)
class Obstacle4_1 : public Obstacle4main
{
public:
	void Init(GameData*, Player*);
	void Reset(float _Hx, float _Hy, float _Hm) override;
	void Move() override;
};

//継承先クラス(子2)
class Obstacle4_2 : public Obstacle4main
{
public:
	void Init(GameData*, Player*);
	void Reset(float _Hx, float _Hy, float _Hm) override;
	void Move() override;
};