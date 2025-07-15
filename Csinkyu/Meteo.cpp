/*
   - Meteo.cpp -
   �~���Ă���覐�.
*/
#include "Meteo.h"

void Meteo::Init(GameData* _data) {
	p_data = _data;
}

void Meteo::Reset() {

	state       = Meteo_Normal;
	pos         = {0, 0};
	vel         = {0, 0};
	active      = FALSE;
	destroyCntr = 0;
}

void Meteo::Update() {

	//覐Ζ{�̂��L���Ȃ�.
	if (active) {

		//�ړ�.
		pos.x += vel.x * METEO_SPEED * (double)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		pos.y += vel.y * METEO_SPEED * (double)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
		//��].
		ang += (p_data->isSlow) ? SLOW_MODE_SPEED : 1;

		//��ԕʏ���.
		switch (state) 
		{
			case Meteo_Normal:
				//��ʊO�ŏ���.
				if (IsOutInArea(pos, { METEO_LINE_DIS_MAX*2, METEO_LINE_DIS_MAX*2 }, 0, 0, WINDOW_WID, WINDOW_HEI, TRUE)){
					active = FALSE; //�����ɂ���.
				}
				break;

			case Meteo_Destroy:
				//�j��ʂ̓x��.
				destroyCntr += (p_data->isSlow) ? SLOW_MODE_SPEED : 1;
				//���Ԃ��I��������.
				if (destroyCntr >= METEO_DEST_TIME) {
					state  = Meteo_Normal; //���ɖ߂�.
					active = FALSE;        //����.
				}
				break;

			default: assert(FALSE); break;
		}
		//覐΍\�����̍X�V.
		UpdateMeteoLine();
	}
}

void Meteo::Draw() {
	
	//覐Ζ{�̂��L���Ȃ�.
	if (active) {
		//�j�󃂁[�h����.
		if (state == Meteo_Destroy) {
			int pow = _int(min(255 * (float)(METEO_DEST_TIME-destroyCntr)/METEO_DEST_TIME, 255)); //����������(255��0)
			SetDrawBlendModeST(MODE_ADD, pow);
		}

		//�L���Ȑ���S�ĕ`��.
		for (int i = 0; i < shape.lineCnt; i++) {
			
			int clr = _int(255 * fabs(sin(pos.x/200))); //�F�̕ω�.
			shape.line[i].clr = GetColor(0, clr, 255);
			DrawLineST(&shape.line[i]);
		}

		ResetDrawBlendMode(); //�`�惂�[�h���Z�b�g.
	}
}

//覐Ώo��.
void Meteo::Spawn() {

	int rnd1 = RndNum(0, 99);
	int rnd2 = RndNum(0, 99);

	INT_XY goalPos{}; //�ڕW���W.

	//50%:�㉺�[����o��.
	if (rnd1 < 50) {
		pos.x = RndNum(0, WINDOW_WID);                                                  //x�̐ݒ�.
		pos.y = (rnd2 < 50) ? 0 - METEO_LINE_DIS_MAX : WINDOW_HEI + METEO_LINE_DIS_MAX; //y�̐ݒ�.
	}
	//50%:���E�[����o��.
	else {
		pos.x = (rnd2 < 50) ? 0 - METEO_LINE_DIS_MAX : WINDOW_WID + METEO_LINE_DIS_MAX; //x�̐ݒ�.
		pos.y = RndNum(0, WINDOW_HEI);                                                  //y�̐ݒ�.
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
		shape.lineCnt = RndNum(METEO_LINE_CNT_MIN, METEO_LINE_CNT_MAX);
		//���_�̈ʒu�𒊑I.
		for (int i = 0; i < shape.lineCnt; i++) {
			shape.lineDis[i] = (float)RndNum(METEO_LINE_DIS_MIN*10, METEO_LINE_DIS_MAX*10)/10; //������1�ʂ܂Œ��I����.
		}
	}

	active = TRUE; //覐΂�L���ɂ���.
}

//覐Δj��.
void Meteo::Destroy() {
	//�j�󂵂ĂȂ��Ȃ�.
	if (state == Meteo_Normal) {
		state = Meteo_Destroy; //�j�󃂁[�h��.
		destroyCntr = 0;       //0����J�n.
	}
}

//覐΂̓����蔻��.
BOOL Meteo::IsHitMeteo(Circle* pos) {

	//�L����覐΂Ȃ�.
	if (active && state == Meteo_Normal) {
		//�S�Ă̐��Ŕ���.
		for (int i = 0; i < shape.lineCnt; i++) {
			//���ƃv���C���[������������.
			if (IsHitLine(&shape.line[i], pos)) {
				return TRUE; //��������.
			}
		}
	}

	return FALSE; //�������Ă��Ȃ�.
}

//覐΂��\��������̍X�V.
void Meteo::UpdateMeteoLine() {

	//���x������邩.
	float rot = (float)360/shape.lineCnt; //360�x���`�����̐�.

	//��]���Ȃ���n�_�ƏI�_��ݒ肵�Ă���.
	for (int i = 0; i < shape.lineCnt; i++) {

		//�v�f����0�����Ȃ�ő�l�ֈړ�����.
		int bef = ((i-1) < 0) ? shape.lineCnt-1 : (i-1);

		shape.line[i].stPos = CalcArcPos(pos, ang+  i*rot, shape.lineDis[i]);   //�n�_: ���݂̊p�x����v�Z.
		shape.line[i].edPos = CalcArcPos(pos, ang+bef*rot, shape.lineDis[bef]); //�I�_: 1�O�̊p�x����v�Z.

		//�j�󎞂̉�]�A�j���[�V����.
		if (state == Meteo_Destroy) {

			//�@覐΂��\��������̏��.
			DBL_XY lineMidPos = CalcMidPos(shape.line[i].stPos, shape.line[i].edPos); //���_�̈ʒu.
			double lineLen    = CalcDis(shape.line[i].stPos, lineMidPos);             //�����̔���.
			double lineAng    = CalcFacingAng(lineMidPos, shape.line[i].stPos);       //�p�x.
			//�A覐΂̒�������ǂ�ǂ񗣂��Ă���.
			double pivotDis   = CalcDis(pos, lineMidPos);                             //覐΂̒�������̋���.
			double pivotAng   = CalcFacingAng(pos, lineMidPos);                       //覐΂̒������猩���p�x.
			DBL_XY newPos     = CalcArcPos(pos, pivotAng, pivotDis+destroyCntr);      //�����𑝂₷.
			//�B�V���Ȑ��̎n�_�ƏI�_.
			shape.line[i].stPos = CalcArcPos(newPos, lineAng    +destroyCntr, lineLen);
			shape.line[i].edPos = CalcArcPos(newPos, lineAng+180+destroyCntr, lineLen);
		}
	}
}