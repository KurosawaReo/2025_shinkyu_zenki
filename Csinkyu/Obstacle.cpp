/*
   - Obstacle.cpp -
   è·äQï®ä«óù.(çï‡VçÏ)
*/
#include "Obstacle.h"

void Obstacle::Init()
{
	
}
void Obstacle::Update()
{
	ang += 1;
}
void Obstacle::Draw()
{
	INT_XY pos = { 100, 100 };
	DrawLineAng(pos, ang, 100, GetColor(0, 255, 0));
}