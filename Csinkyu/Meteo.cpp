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

	//覐Ζ{�̂��L���Ȃ�.
	if (active) {
		//�ړ�.
		pos.x += vel.x * METEO_SPEED * (double)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		pos.y += vel.y * METEO_SPEED * (double)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		//��ʊO�ŏ���.
		if (IsOutInArea(pos, { METEO_LINE_DIS_MAX*2, METEO_LINE_DIS_MAX*2 }, 0, 0, WINDOW_WID, WINDOW_HEI, TRUE)){
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
		for (int i = 0; i < shape.lineCnt; i++) {
			
			int g = _int(255 * fabs(sin(pos.x/200))); //�F�̕ω�.
			shape.line[i].clr = GetColor(0, g, 255);
			DrawLineST(&shape.line[i]);
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

	//覐΂̐ݒ�.
	{
		//���p�`�ɂ��邩.
		shape.lineCnt = RndNum(3, METEO_LINE_CNT_MAX);
		//���_�̈ʒu�𒊑I.
		for (int i = 0; i < shape.lineCnt; i++) {
			shape.lineDis[i] = RndNum(METEO_LINE_DIS_MIN, METEO_LINE_DIS_MAX);
		}
	}

	active = TRUE; //覐΂�L���ɂ���.
}

//覐΂��\��������̍X�V.
void Meteo::UpdateMeteoLine() {

	float rot = 360/shape.lineCnt; //�}�`��1�̊p�̊p�x.

	//��]���Ȃ���n�_�ƏI�_��ݒ肵�Ă���.
	for (int i = 0; i < shape.lineCnt; i++) {
		
		//�v�f����0�����Ȃ�ő�l�ֈړ�����.
		int i2 = ((i-1) < 0) ? shape.lineCnt-1 : (i-1);

		shape.line[i].stPos = CalcLineAng(pos, ang +  i  *rot, shape.lineDis[i]);  //���݂̊p�x����v�Z.
		shape.line[i].edPos = CalcLineAng(pos, ang + (i2)*rot, shape.lineDis[i2]); //1�O�̊p�x����v�Z.
	}
}