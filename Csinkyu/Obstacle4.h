/*
   - Obstacle3.h -
   ��Q���Ǘ�.
*/
#pragma once
#include "Player.h"
#include"Obstacle4main.h"

//#define MAX_L 100 //�~�T�C������ԍő勗��.
//#define PI 3.14159//�~����.
//#define LINE_MAXNUM 3000//�`�悷����̍ő吔.


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