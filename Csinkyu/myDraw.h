/*
   - myDraw.cpp - (original)

   DxLib�Ŏg���p�̃I���W�i���`��֐�.
   ��ST��struct�̗�.
*/
#pragma once

//�摜�f�[�^�i�[�p.
struct IMG
{
	int    handle;	//�n���h��.
	INT_XY size;	//�摜�̃T�C�Y.
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

INT_XY DrawLineAng    (INT_XY pos, float ang, float len, int clr, int _thickness = 1);

int    LoadGraphST    (IMG* img, const TCHAR* fileName);
int    DrawGraphST    (const IMG_DRAW* img, BOOL isDrawCenter = FALSE);
int    DrawRectGraphST(const IMG_DRAW_RECT* img);