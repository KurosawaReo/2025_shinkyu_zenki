/*
   - Obst_NormalLaser.cpp -

   障害物: レーザー発射台(継承先)
   個体によって違う動きをするため、overrideを使用.
*/
#include "Obst_NormalLaser.h"

//依存関係.
#include "GameData.h"
//参照.
static GameData& gameData = GameData::GetInst();

/*
   ▼リセット処理.
*/
void NormalLaser_1::Reset() {

	NormalLaserMain::Reset();

	Hx = WINDOW_WID / 2;  //砲台のX座標初期値.
	Hy = 0;				  //砲台のY座標初期値.
	Hm = 3;				  //砲台の移動速度.
	moveDir = MOVE_RIGHT; //初期方向.
}
void NormalLaser_2::Reset() {

	NormalLaserMain::Reset();

	Hx = WINDOW_WID / 2;
	Hy = 0;
	Hm = 3;
	moveDir = MOVE_LEFT;
}
void NormalLaser_3::Reset() {

	NormalLaserMain::Reset();

	Hx = WINDOW_WID / 2;
	Hy = WINDOW_HEI;
	Hm = 3;
	moveDir = MOVE_RIGHT;
}
void NormalLaser_4::Reset() {

	NormalLaserMain::Reset();

	Hx = WINDOW_WID / 2;
	Hy = WINDOW_HEI;
	Hm = 3;
	moveDir = MOVE_LEFT;
}

/*
   ▼移動処理.
*/
void NormalLaser_1::Move()
{
	// 移動速度
	float moveSpeed = Hm * gameData.speedRate;

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
void NormalLaser_2::Move()
{
	// 移動速度
	float moveSpeed = Hm * gameData.speedRate;

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
void NormalLaser_3::Move()
{
	// 移動速度
	float moveSpeed = Hm * gameData.speedRate;

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
void NormalLaser_4::Move()
{
	// 移動速度
	float moveSpeed = Hm * gameData.speedRate;

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
