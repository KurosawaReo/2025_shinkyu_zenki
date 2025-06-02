/*
   - myCalcST.cpp - (original)
   ver.2025/06/02

   DxLib�Ŏg���p�̃I���W�i���v�Z�֐�.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx���Ȃ���΂����Œ�`.
#endif

#include "myCalcST.h"

//�����蔻��(�~�Ɖ~)
BOOL IsHitCircle(const Circle* cir1, const Circle* cir2) {

    //���������a�̍��v���Z����Γ������Ă���.
    if (CalcDis(cir1->pos, cir2->pos) <= cir1->r + cir2->r) {
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
//���_���W�v�Z.
DBL_XY CalcMidPos(DBL_XY pos1, DBL_XY pos2) {

	double x = (pos1.x + pos2.x)/2; //x�̕���.
    double y = (pos1.y + pos2.y)/2; //y�̕���.

	return { x, y };
}
//���̏I�_�v�Z.
DBL_XY CalcLineAng(DBL_XY stPos, float ang, float len) {

    //�p�x��rad�ɕϊ����A���W�̌v�Z.
    double y = sin(ang * M_PI/180) * len;
    double x = cos(ang * M_PI/180) * len;

    return { stPos.x+x, stPos.y+y }; //�I�_���W��Ԃ�.
}