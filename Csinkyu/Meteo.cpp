/*
   - Meteo.cpp -
   �~���Ă���覐�.
*/
#include "Meteo.h"

void Meteo::Init(GameData* _data) {
	p_data   = _data;
	shapeCnt = 4;
}

void Meteo::Reset() {

	pos    = {0, 0};
	vel    = {0, 0};
	active = FALSE;
}

void Meteo::Update() {

	InputST* input = InputST::GetPtr();

	if (input->IsPushKeyTime(KEY_1) == 1) {
		shapeCnt++;
		if (shapeCnt > METEO_LINE_MAX) {
			shapeCnt = METEO_LINE_MAX;
		}
	}
	if (input->IsPushKeyTime(KEY_2) == 1) {
		shapeCnt--;
		if (shapeCnt < 3) {
			shapeCnt = 3;
		}
	}

	//覐Ζ{�̂��L���Ȃ�.
	if (active) {
		//�ړ�.
		pos.x += vel.x * METEO_SPEED * (double)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		pos.y += vel.y * METEO_SPEED * (double)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		//��ʊO�ŏ���.
		if (IsOutInArea(pos, {}, 0, 0, WINDOW_WID, WINDOW_HEI)){
			active = FALSE; //�����ɂ���.
		}
		//��].
		ang += (p_data->isSlow) ? SLOW_MODE_SPEED : 1;

		UpdateMeteoLine();
	}
}

void Meteo::Draw() {
	
	//覐Ζ{�̂��L���Ȃ�.
	if (active) {

		Circle cir = {pos, 8, 0xFFFFFF};
		DrawCircleST(&cir, FALSE);

		//�L���Ȑ���S�ĕ`��.
		for (int i = 0; i < shapeCnt; i++) {
			
			int g = _int(255 * fabs(sin(pos.x/200))); //�F�̕ω�.
			line[i].clr = GetColor(0, g, 255);
			DrawLineST(&line[i]);
		}
	}
}

//覐Ώo��.
void Meteo::Spawn() {

	int rnd1 = RndNum(0, 99);
	int rnd2 = RndNum(0, 99);

	INT_XY goalPos{}; //�ڕW���W.

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

//覐΂��\��������̍X�V.
void Meteo::UpdateMeteoLine() {

	float rot = 360/shapeCnt; //�}�`��1�̊p�̊p�x.
	float len = 120/shapeCnt; //�}�`��1�̕ӂ̒���.

	for (int i = 0; i < shapeCnt; i++) {
		
		//��ƂȂ�ʒu�Ɗp�x.
		float  mainAng = ang+i*rot;
		DBL_XY mainPos = CalcLineAng(pos, mainAng, 30);
		
		line[i].stPos = CalcLineAng(mainPos, mainAng+90, len);
		line[i].edPos = CalcLineAng(mainPos, mainAng-90, len);
	}
}