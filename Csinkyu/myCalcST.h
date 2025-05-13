/*
   - myCalcST.h - (original)

   DxLib�Ŏg���p�̃I���W�i���v�Z�֐�.
   2025/05/14
*/
#pragma once

#if !defined DEF_INT_XY
#define DEF_INT_XY
//int�^�̋Ïkxy.
struct INT_XY
{
	int x;
	int y;
};
#endif

#if !defined DEF_DBL_XY
#define DEF_DBL_XY
//double�^�̋Ïkxy.
struct DBL_XY
{
	double x;
	double y;
};
#endif

#if !defined DEF_SHAPES
#define DEF_SHAPES
//�~�f�[�^.
struct Circle
{
	DBL_XY pos;  //���W.
	int    r;    //���a.
	UINT   clr;  //�F.
};
//�l�p�`�f�[�^.
struct Box
{
	DBL_XY pos;  //���W.
	INT_XY size; //�T�C�Y.
	UINT   clr;  //�F.
};
//���f�[�^.
struct Line
{
	DBL_XY stPos; //�n�_���W.
	DBL_XY edPos; //�I�_���W.
	UINT   clr;   //�F.
};
#endif

BOOL   IsHitCircle(DBL_XY pos1, int r1, DBL_XY pos2, int r2);
BOOL   IsHitBox   (DBL_XY pos1, INT_XY size1, DBL_XY pos2, INT_XY size2, BOOL isCenter);
BOOL   IsHitLine  (const Line* line, const Circle* circle);

double CalcDis    (DBL_XY pos1, DBL_XY pos2);
DBL_XY CalcMidPos (DBL_XY pos1, DBL_XY pos2);
DBL_XY CalcLineAng(DBL_XY stPos, float ang, float len);