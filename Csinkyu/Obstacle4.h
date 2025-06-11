/*
   - Obstacle3.h -
   áŠQ•¨ŠÇ—.
*/
#pragma once
#include "Player.h"
#include"Obstacle4main.h"

//#define MAX_L 100 //ƒ~ƒTƒCƒ‹‚ª”ò‚ÔÅ‘å‹——£.
//#define PI 3.14159//‰~ü—¦.
//#define LINE_MAXNUM 3000//•`‰æ‚·‚éü‚ÌÅ‘å”.


class Obstacle5 : public Obstacle4main
{

public:
	void Reset(float _Hx, float _Hy, float _Hm)override;
	void idou() override;
};

class Obstacle4 : public Obstacle4main

{
private:

public:
	void Reset(float _Hx, float _Hy, float _Hm)override;
	void idou() override;

};