/*
   - myDraw.cpp - (original)

   DxLib�Ŏg���p�̃I���W�i���`��֐�.
   ��ST��struct�̗�.
*/
#pragma once

struct INT_XY //x��y�̋Ïk��.
{
	int x;
	int y;
};

//�摜�`��Ɏg���p.
struct IMG_DRAW
{
	INT_XY pos;     //��ʂ̂ǂ��ɕ`�悷�邩.(������W�)

	INT_XY size;    //�摜�̃T�C�Y.

	int    handle;  //�摜�f�[�^.
	BOOL   isTrans; //���߂̉�.
};
struct IMG_DRAW_RECT
{
	INT_XY pos;     //��ʂ̂ǂ��ɕ`�悷�邩.(������W�)

	INT_XY stPxl;   //�n�_pixel.
	INT_XY size;    //�؂���T�C�Y.

	int    handle;  //�摜�f�[�^.
	BOOL   isTrans; //���߂̉�.
};

INT_XY DrawLineAng    (INT_XY pos, float ang, float len, int clr);
int    DrawGraphST    (const IMG_DRAW* img, BOOL isDrawCenter);
int    DrawRectGraphST(const IMG_DRAW_RECT* img);