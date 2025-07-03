/*
   - Obstacle4.cpp -

   レーザーの継承先クラス.
   砲台(不可視)を左右で違う動きにするため、overrideを使用.
*/
#include "Player.h"    // プレイヤークラスのヘッダーファイル
#include "Obstacle4.h" // 自身のヘッダーファイル

//obstacle4mainのMove関数をobstacle4用に上書き.
void Obstacle4_1::Move()
{
	// 移動速度
	float moveSpeed = Hm * (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);

	// 矩形経路の移動(右回り)
	switch (moveDir)
	{
	case MOVE_LEFT:
		Hx -= moveSpeed;
		if (Hx < 0 + OBSTACLE4_OUTER_MARGIN) {
			Hx = 0 + OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_UP;
		}
		break;
	case MOVE_RIGHT:
		Hx += moveSpeed;
		if (Hx > WINDOW_WID - OBSTACLE4_OUTER_MARGIN) {
			Hx = WINDOW_WID - OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_DOWN;
		}
		break;
	case MOVE_DOWN:
		Hy += moveSpeed;
		if (Hy > WINDOW_HEI - OBSTACLE4_OUTER_MARGIN) {
			Hy = WINDOW_HEI - OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_LEFT;
		}
		break;
	case MOVE_UP:
		Hy -= moveSpeed;
		if (Hy < 0 + OBSTACLE4_OUTER_MARGIN) {
			Hy = 0 + OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_RIGHT;
		}
		break;
	}
}

//obstacle4mainのMove関数をobstacle5用に上書き.
void Obstacle4_2::Move()
{
	// 移動速度
	float moveSpeed = Hm * (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);

	// 矩形経路の移動(左回り)
	switch (moveDir)
	{
	case MOVE_LEFT:
		Hx -= moveSpeed;
		if (Hx < 0 + OBSTACLE4_OUTER_MARGIN) {
			Hx = 0 + OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_DOWN;
		}
		break;
	case MOVE_RIGHT:
		Hx += moveSpeed;
		if (Hx > WINDOW_WID - OBSTACLE4_OUTER_MARGIN) {
			Hx = WINDOW_WID - OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_UP;
		}
		break;
	case MOVE_DOWN:
		Hy += moveSpeed;
		if (Hy > WINDOW_HEI - OBSTACLE4_OUTER_MARGIN) {
			Hy = WINDOW_HEI - OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_RIGHT;
		}
		break;
	case MOVE_UP:
		Hy -= moveSpeed;
		if (Hy < 0 + OBSTACLE4_OUTER_MARGIN) {
			Hy = 0 + OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_LEFT;
		}
		break;
	}
}

//obstacle4mainのMove関数をobstacle5用に上書き.
void Obstacle4_3::Move()
{
	// 移動速度
	float moveSpeed = Hm * ((p_data->isSlow) ? (float)SLOW_MODE_SPEED : 1);

	// 矩形経路の移動(左回り)
	switch (moveDir)
	{
	case MOVE_LEFT:
		Hx -= moveSpeed;
		if (Hx < 0 + OBSTACLE4_OUTER_MARGIN) {
			Hx = 0 + OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_DOWN;
		}
		break;
	case MOVE_RIGHT:
		Hx += moveSpeed;
		if (Hx > WINDOW_WID - OBSTACLE4_OUTER_MARGIN) {
			Hx = WINDOW_WID - OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_UP;
		}
		break;
	case MOVE_DOWN:
		Hy += moveSpeed;
		if (Hy > WINDOW_HEI - OBSTACLE4_OUTER_MARGIN) {
			Hy = WINDOW_HEI - OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_RIGHT;
		}
		break;
	case MOVE_UP:
		Hy -= moveSpeed;
		if (Hy < 0 + OBSTACLE4_OUTER_MARGIN) {
			Hy = 0 + OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_LEFT;
		}
		break;
	}
}

//obstacle4mainのMove関数をobstacle4用に上書き.
void Obstacle4_4::Move()
{
	// 移動速度
	float moveSpeed = Hm * ((p_data->isSlow) ? (float)SLOW_MODE_SPEED : 1);

	// 矩形経路の移動(右回り)
	switch (moveDir)
	{
	case MOVE_LEFT:
		Hx -= moveSpeed;
		if (Hx < 0 + OBSTACLE4_OUTER_MARGIN) {
			Hx = 0 + OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_UP;
		}
		break;
	case MOVE_RIGHT:
		Hx += moveSpeed;
		if (Hx > WINDOW_WID - OBSTACLE4_OUTER_MARGIN) {
			Hx = WINDOW_WID - OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_DOWN;
		}
		break;
	case MOVE_DOWN:
		Hy += moveSpeed;
		if (Hy > WINDOW_HEI - OBSTACLE4_OUTER_MARGIN) {
			Hy = WINDOW_HEI - OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_LEFT;
		}
		break;
	case MOVE_UP:
		Hy -= moveSpeed;
		if (Hy < 0 + OBSTACLE4_OUTER_MARGIN) {
			Hy = 0 + OBSTACLE4_OUTER_MARGIN;
			moveDir = MOVE_RIGHT;
		}
		break;
	}
}
