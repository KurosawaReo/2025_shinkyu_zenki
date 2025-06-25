/*
   - Meteo.cpp -
   �~���Ă���覐�.
*/
#include "Meteo.h"

void Meteo::Init(GameData* _data) {
	p_data = _data;
}

void Meteo::Reset() {

	pos    = {0, 0};
	vel    = {0, 0};
	active = FALSE;
}

void Meteo::Update() {

	//�L���Ȃ�.
	if (active) {
		//�ړ�.
		pos.x += vel.x * METEO_SPEED * (double)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		pos.y += vel.y * METEO_SPEED * (double)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		//��ʊO�ŏ���.
		if (IsOutInArea(pos, {}, 0, 0, WINDOW_WID, WINDOW_HEI)){
			active = FALSE; //�����ɂ���.
		}
	}
}

void Meteo::Draw() {
	
	//�L���Ȃ�.
	if (active) {

		float g = 255 * fabs(sin(pos.x/200)); //�F�̕ω�.

		Circle cir = {pos, 80, GetColor(0, g, 255)};
		DrawCircleST(&cir, FALSE);
	}
}

//覐Ώo��.
void Meteo::Spawn() {

	int rnd1 = RndNum(0, 99);
	int rnd2 = RndNum(0, 99);

	INT_XY goalPos; //�ڕW���W.

	//50%:�㉺�[����o��.
	if (rnd1 < 50) {
		pos.x = RndNum(0, WINDOW_WID);        //x�̐ݒ�.
		pos.y = (rnd2 < 50) ? 0 : WINDOW_HEI; //y�̐ݒ�.
	}
	//50%:���E�[����o��.
	else {
		pos.x = (rnd2 < 50) ? 0 : WINDOW_WID; //x�̐ݒ�.
		pos.y = RndNum(0, WINDOW_HEI);        //y�̐ݒ�.
	}

	//�ڕW�n�_�̒��I.
	{
		goalPos.x = RndNum(WINDOW_WID/2 - METEO_GOAL_RAND_RANGE, WINDOW_WID/2 + METEO_GOAL_RAND_RANGE);
		goalPos.y = RndNum(WINDOW_HEI/2 - METEO_GOAL_RAND_RANGE, WINDOW_HEI/2 + METEO_GOAL_RAND_RANGE);
		//�ڕW�n�_�܂ł̊p�x�����߂�.
		double rad = atan2(goalPos.y - pos.y, goalPos.x - pos.x);
		//x��y��vector�ɕ���.
		vel = CalcRadToPos(rad);
	}

	active = TRUE; //�L���ɂ���.
}