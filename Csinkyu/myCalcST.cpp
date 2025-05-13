/*
   - myCalcST.cpp - (original)

   DxLib�Ŏg���p�̃I���W�i���v�Z�֐�.
   2025/05/14
*/
#if false
  #include "stdafx.h" //stdafx������Ȃ炱�������g��.
#else
  #define _USE_MATH_DEFINES //math�萔���g���̂ɕK�v.
  #include <math.h>
  #include "DxLib.h"
#endif

#include "myCalcST.h"

//int�^�ϊ��}�N��.
#define _int(n) (int)(round(n))

//�����蔻��(�~�Ɖ~)
BOOL IsHitCircle(DBL_XY pos1, int r1, DBL_XY pos2, int r2) {

    double disX = pos1.x - pos2.x;
    double disY = pos1.y - pos2.y;

    if (sqrt(disX * disX + disY * disY) <= r1 + r2) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}
//�����蔻��(�l�p�Ǝl�p)
BOOL IsHitBox(DBL_XY pos1, INT_XY size1, DBL_XY pos2, INT_XY size2, BOOL isCenter) {

    BOOL hit = FALSE;

    //��������W�ł̔���.
    if (isCenter) {
        if (fabs(pos1.x - pos2.x) <= (size1.x + size2.x)/2 &&
            fabs(pos1.y - pos2.y) <= (size1.y + size2.y)/2)
        {
            hit = TRUE;
        }
    }
    //�������W�ł̔���.
    else {
        if (pos1.x + size1.x >= pos2.x && pos2.x + size2.x >= pos1.x &&
            pos1.y + size1.y >= pos2.y && pos2.y + size2.y >= pos1.y)
        {
            hit = TRUE;
        }
    }
    return hit;
}
//�����蔻��(���Ɖ~)
BOOL IsHitLine(const Line* line, const Circle* circle) {

	//���̎n�_�ƏI�_����X�������߂�.
	double katamuki;
	{
		double x = line->edPos.x - line->stPos.x;
		double y = line->edPos.y - line->stPos.y;
		if (x != 0) {
			katamuki = y / x;
		}
		else {
			katamuki = 100; //0���΍�.
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
		dis1 = fabs(a*circle->pos.x + b*circle->pos.y + c) / sqrt(a*a + b*b);
	}
	//���̒��_�`�~�̒��S�̋���.
	double dis2;
	{
		double x = circle->pos.x - CalcMidPos(line->stPos, line->edPos).x;
		double y = circle->pos.y - CalcMidPos(line->stPos, line->edPos).y;
		//����: d = ��(x^2 + y^2) (�O�����̒藝)
		dis2 = sqrt(x*x + y*y);
	}

	//hit����.
	if (dis1 <= circle->r &&                                    //����1:���ɐG��Ă���.
		dis2 <= CalcDis(line->stPos, line->edPos)/2 + circle->r //����2:���𒼌a�Ƃ���~�ɐG��Ă���.
	){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

//�����v�Z.
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