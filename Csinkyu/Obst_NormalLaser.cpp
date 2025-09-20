/*
   - Obst_NormalLaser.cpp -

   障害物: レーザー発射台(継承先)
   個体によって違う動きをするため、overrideを使用.
*/
#include "GameManager.h"
#include "Obst_NormalLaser.h"

//obstacle4mainのMove関数をobstacle4用に上書き.
void NormalLaser_1::Move()
{
	// 移動速度
	float moveSpeed = Hm * p_data->speedRate;

	// 矩形経路の移動(右回り)
	switch (moveDir)
	{
	case MOVE_LEFT:
		Hx -= moveSpeed;
		if (Hx < 0 + LASER_NOR_OUTER_MARGIN) {
			Hx = 0 + LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_UP;
		}
		break;
	case MOVE_RIGHT:
		Hx += moveSpeed;
		if (Hx > WINDOW_WID - LASER_NOR_OUTER_MARGIN) {
			Hx = WINDOW_WID - LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_DOWN;
		}
		break;
	case MOVE_DOWN:
		Hy += moveSpeed;
		if (Hy > WINDOW_HEI - LASER_NOR_OUTER_MARGIN) {
			Hy = WINDOW_HEI - LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_LEFT;
		}
		break;
	case MOVE_UP:
		Hy -= moveSpeed;
		if (Hy < 0 + LASER_NOR_OUTER_MARGIN) {
			Hy = 0 + LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_RIGHT;
		}
		break;
	}
}

//obstacle4mainのMove関数をobstacle5用に上書き.
void NormalLaser_2::Move()
{
	// 移動速度
	float moveSpeed = Hm * p_data->speedRate;

	// 矩形経路の移動(左回り)
	switch (moveDir)
	{
	case MOVE_LEFT:
		Hx -= moveSpeed;
		if (Hx < 0 + LASER_NOR_OUTER_MARGIN) {
			Hx = 0 + LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_DOWN;
		}
		break;
	case MOVE_RIGHT:
		Hx += moveSpeed;
		if (Hx > WINDOW_WID - LASER_NOR_OUTER_MARGIN) {
			Hx = WINDOW_WID - LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_UP;
		}
		break;
	case MOVE_DOWN:
		Hy += moveSpeed;
		if (Hy > WINDOW_HEI - LASER_NOR_OUTER_MARGIN) {
			Hy = WINDOW_HEI - LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_RIGHT;
		}
		break;
	case MOVE_UP:
		Hy -= moveSpeed;
		if (Hy < 0 + LASER_NOR_OUTER_MARGIN) {
			Hy = 0 + LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_LEFT;
		}
		break;
	}
}

//obstacle4mainのMove関数をobstacle5用に上書き.
void NormalLaser_3::Move()
{
	// 移動速度
	float moveSpeed = Hm * p_data->speedRate;

	// 矩形経路の移動(左回り)
	switch (moveDir)
	{
	case MOVE_LEFT:
		Hx -= moveSpeed;
		if (Hx < 0 + LASER_NOR_OUTER_MARGIN) {
			Hx = 0 + LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_DOWN;
		}
		break;
	case MOVE_RIGHT:
		Hx += moveSpeed;
		if (Hx > WINDOW_WID - LASER_NOR_OUTER_MARGIN) {
			Hx = WINDOW_WID - LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_UP;
		}
		break;
	case MOVE_DOWN:
		Hy += moveSpeed;
		if (Hy > WINDOW_HEI - LASER_NOR_OUTER_MARGIN) {
			Hy = WINDOW_HEI - LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_RIGHT;
		}
		break;
	case MOVE_UP:
		Hy -= moveSpeed;
		if (Hy < 0 + LASER_NOR_OUTER_MARGIN) {
			Hy = 0 + LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_LEFT;
		}
		break;
	}
}

//obstacle4mainのMove関数をobstacle4用に上書き.
void NormalLaser_4::Move()
{
	// 移動速度
	float moveSpeed = Hm * p_data->speedRate;

	// 矩形経路の移動(右回り)
	switch (moveDir)
	{
	case MOVE_LEFT:
		Hx -= moveSpeed;
		if (Hx < 0 + LASER_NOR_OUTER_MARGIN) {
			Hx = 0 + LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_UP;
		}
		break;
	case MOVE_RIGHT:
		Hx += moveSpeed;
		if (Hx > WINDOW_WID - LASER_NOR_OUTER_MARGIN) {
			Hx = WINDOW_WID - LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_DOWN;
		}
		break;
	case MOVE_DOWN:
		Hy += moveSpeed;
		if (Hy > WINDOW_HEI - LASER_NOR_OUTER_MARGIN) {
			Hy = WINDOW_HEI - LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_LEFT;
		}
		break;
	case MOVE_UP:
		Hy -= moveSpeed;
		if (Hy < 0 + LASER_NOR_OUTER_MARGIN) {
			Hy = 0 + LASER_NOR_OUTER_MARGIN;
			moveDir = MOVE_RIGHT;
		}
		break;
	}
}
