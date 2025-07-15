/*
   - myCalcST.cpp - (original)
   ver.2025/07/15

   DxLib: �I���W�i���v�Z�@�\�̒ǉ�.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx���ɓ����ĂȂ���΂����œ���.
#endif

#include "myCalcST.h"

//�����蔻��(�~�Ɖ~)
BOOL IsHitCircle(const Circle* cir1, const Circle* cir2) {

	//������.
	double x = cir1->pos.x - cir2->pos.x;
	double y = cir1->pos.y - cir2->pos.y;
    //���������a�̍��v���Z����Γ������Ă���.
	//(����팸���邽�߂�2�悵�Čv�Z)
    if (x*x + y*y <= pow(cir1->r+cir2->r, 2)) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}
//�����蔻��(�l�p�Ǝl�p)
BOOL IsHitBox(const Box* box1, const Box* box2, BOOL isCenter) {

    BOOL hit = FALSE;

    //��������W�ł̔���.
    if (isCenter) {
        if (fabs(box1->pos.x - box2->pos.x) <= (box1->size.x + box2->size.x)/2 &&
            fabs(box1->pos.y - box2->pos.y) <= (box1->size.y + box2->size.y)/2)
        {
            hit = TRUE;
        }
    }
    //�������W�ł̔���.
    else {
        if (box1->pos.x + box1->size.x >= box2->pos.x && box2->pos.x + box2->size.x >= box1->pos.x &&
            box1->pos.y + box1->size.y >= box2->pos.y && box2->pos.y + box2->size.y >= box1->pos.y)
        {
            hit = TRUE;
        }
    }
    return hit;
}
//�����蔻��(���Ɖ~)
BOOL IsHitLine(const Line* line, const Circle* cir) {

	//���̎n�_�ƏI�_����X�������߂�.
	double katamuki;
	{
		double x = line->edPos.x - line->stPos.x;
		double y = line->edPos.y - line->stPos.y;
		if (x != 0) {
			katamuki = y / x;
		}
		else {
			katamuki = 999; //0���΍�.
		}
	}
	//����������ɂ������̐ؕ�.
	double seppen = line->stPos.y - line->stPos.x * katamuki;

	//���`�~�̋���.
	double dis1;
	{
		//����: ax + by + c = 0
		//b��1�Ƃ��āuy = �v�̌`�ɂ��遨 y = -ax - c
		double a = -katamuki;
		double b = 1;
		double c = -seppen;
		//����: d = |ax + by + c|/��(a^2 + b^2)
		dis1 = fabs(a*cir->pos.x + b*cir->pos.y + c) / sqrt(a*a + b*b);
	}
	//���̒��_�`�~�̒��S�̋���.
	double dis2;
	{
		double x = cir->pos.x - CalcMidPos(line->stPos, line->edPos).x;
		double y = cir->pos.y - CalcMidPos(line->stPos, line->edPos).y;
		//����: d = ��(x^2 + y^2) (�O�����̒藝)
		dis2 = sqrt(x*x + y*y);
	}

	//hit����.
	if (dis1 <= cir->r &&                                    //����1:���ɐG��Ă���.
		dis2 <= CalcDis(line->stPos, line->edPos)/2 + cir->r //����2:���𒼌a�Ƃ���~�ɐG��Ă���.
	){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

//�ړ��\�͈͓��ɕ␳����.
void FixPosInArea(DBL_XY* pos, INT_XY size, int left, int up, int right, int down) {

	if (pos->x < left  + size.x/2) { pos->x = left  + size.x/2; }
	if (pos->y < up    + size.y/2) { pos->y = up    + size.y/2; }
	if (pos->x > right - size.x/2) { pos->x = right - size.x/2; }
	if (pos->y > down  - size.y/2) { pos->y = down  - size.y/2; }
}
//�͈͊O���ǂ���.
BOOL IsOutInArea(DBL_XY pos, INT_XY size, int left, int up, int right, int down, BOOL isCompOut) {

	//���S�ɏo����͈͊O�Ƃ���.
	if (isCompOut) {
		if (pos.x < left  - size.x/2) { return TRUE; }
		if (pos.y < up    - size.y/2) { return TRUE; }
		if (pos.x > right + size.x/2) { return TRUE; }
		if (pos.y > down  + size.y/2) { return TRUE; }
	}
	//�G�ꂽ�u�Ԃɔ͈͊O�Ƃ���.
	else {
		if (pos.x < left  + size.x/2) { return TRUE; }
		if (pos.y < up    + size.y/2) { return TRUE; }
		if (pos.x > right - size.x/2) { return TRUE; }
		if (pos.y > down  - size.y/2) { return TRUE; }
	}

	return FALSE; //�͈͓�.
}

//�����v�Z.
double CalcDis(INT_XY pos1, INT_XY pos2) {

	double x = pos1.x - pos2.x; //x�̍�.
    double y = pos1.y - pos2.y; //y�̍�.

	return sqrt(x*x + y*y); //�Εӂ̒�����Ԃ�.
}
double CalcDis(DBL_XY pos1, DBL_XY pos2) {

	double x = pos1.x - pos2.x; //x�̍�.
    double y = pos1.y - pos2.y; //y�̍�.

	return sqrt(x*x + y*y); //�Εӂ̒�����Ԃ�.
}
//2�̍��W�̒��_���v�Z.
DBL_XY CalcMidPos(DBL_XY pos1, DBL_XY pos2) {

	double x = (pos1.x + pos2.x)/2; //x�̕���.
    double y = (pos1.y + pos2.y)/2; //y�̕���.

	return { x, y };
}
//�n�_����p�x�ƒ�������ꂽ���W���v�Z.
DBL_XY CalcArcPos(DBL_XY stPos, double ang, double len) {

    //�p�x��rad�ɕϊ����A���W�̌v�Z.
    double y = sin(_rad(ang)) * len;
    double x = cos(_rad(ang)) * len;

    return { stPos.x+x, stPos.y+y }; //�I�_���W��Ԃ�.
}
//�n�_����ڕW���������̊p�x���v�Z.
double CalcFacingAng(DBL_XY stPos, DBL_XY targetPos) {
	//���W��.
    double disX = targetPos.x - stPos.x;
	double disY = targetPos.y - stPos.y;
	//rad��dig�ɂ��ĕԂ�.
	return _dig(atan2(disY, disX));
}
//�p�x������W�����߂�.
DBL_XY CalcDigToPos(double dig) {
	//���Wvector(�l��-1�`+1�ɂȂ�)��Ԃ�.
	return { cos(_rad(dig)), sin(_rad(dig)) };
}
//�p�x������W�����߂�.
DBL_XY CalcRadToPos(double rad) {
	//���Wvector(�l��-1�`+1�ɂȂ�)��Ԃ�.
	return { cos(rad), sin(rad) };
}

//ease-out:���񂾂񌸑�.
float CalcNumEaseOut(float time) {
	time = min(time, 1.0f); //�����1.0
	time = max(time, 0.0f); //������0.0
	return 1 - (1-time) * (1-time);
}

//�l�̒��I.
int RndNum(int st, int ed, BOOL isDxRnd) {

	int rnd = 0;

	//ed��st�ȏ�̎��̂ݒ��I.
	_if_check(st <= ed) {

		//DxLib�p�̗������g�����ǂ���.
		if (isDxRnd) {
			rnd = GetRand(ed - st); //st�`end�̍��Œ��I.
		}
		else {
			rnd = rand() % ((ed - st) + 1); //st�`end�̍��Œ��I.
		}
	}
	return st + rnd;
}
//�l���珬���������o��.
double GetDecimal(double num) {

	double n = 0; //������.
	double f = 0; //������.
	f = modf(num, &n); //�����������o��.

	return f;
}