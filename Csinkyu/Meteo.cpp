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
		//printfDx(_T("�A x:%f, y:%f\n"), vel.x, vel.y);
		//printfDx(_T("�B x:%f, y:%f\n"), pos.x, pos.y);
		//��ʊO�ŏ���.
		if (IsOutInArea(pos, {}, 0, 0, WINDOW_WID, WINDOW_HEI)){
			active = FALSE; //�����ɂ���.
			//printfDx(_T("�����ɂȂ���\n"));
		}
	}
}

void Meteo::Draw() {
	
	//�L���Ȃ�.
	if (active) {
		DrawCircle(pos.x, pos.y, 20, 0xFFFFFF); //kari
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
		double ang = atan2(goalPos.y - pos.y, goalPos.x - pos.x);
		//x��y��vector�ɕ���.
		vel = CalcAngToPos(ang);

		printfDx(_T("ang:%f\n"), ang*180/M_PI);
		printfDx(_T("x:%f, y:%f\n"), vel.x, vel.y);
	}
}