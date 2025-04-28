/*
   - myDraw.cpp - (original)
   
   DxLib�Ŏg���p�̃I���W�i���`��֐�.
   ��ST��struct�̗�.
*/
#if false
  #include "stdafx.h" //stdafx������Ȃ炱�������g��.
#else
  #define _USE_MATH_DEFINES //math�萔���g���̂ɕK�v.
  #include <math.h>
  #include "DxLib.h"
#endif

#include "myDraw.h"

//int�^�ϊ��}�N��.
#define _int(n) (int)(round(n))

//���̕`��֐�.
INT_XY DrawLineAng(INT_XY stPos, float ang, float len, int clr, int _thickness) {

	//�p�x��rad�ɕϊ����A���W�̌v�Z.
	int y = _int(sin(ang * M_PI/180) * len);
	int x = _int(cos(ang * M_PI/180) * len);
	//�I�_���W.
	INT_XY edPos = { stPos.x+x, stPos.y+y };
	//�n�_����I�_�֕`��.
	DrawLine(stPos.x, stPos.y, edPos.x, edPos.y, clr, _thickness);

	return edPos; //�I�_���W��Ԃ�.
}

//LoadGraph�̉�����.
int LoadGraphST(IMG* img, const TCHAR* fileName) {

	//�摜�ǂݍ���.
	img->handle = LoadGraph(fileName);
	int ret = GetGraphSize(img->handle, &img->size.x, &img->size.y);
	
	if (img->handle == -1) {
		return -1; //-1: LoadGraph�G���[.
	}
	if (ret == -1) {
		return -2; //-2: GetGraphSize�G���[.
	}
	return 0; //0: ����I��.
}

//DrawGraph�̉�����.
int DrawGraphST(const IMG_DRAW* img, BOOL isDrawCenter) {

	if (img->handle == 0) {
		return -2; //-2: handle���ݒ�.
	}

	int x = img->pos.x;
	int y = img->pos.y;

	//�������W���[�h.
	if (isDrawCenter) {
		x -= img->size.x / 2; //(size/2)���炷.
		y -= img->size.y / 2;
	}

	int err = DrawGraph(x, y, img->handle, img->isTrans);
	return err; //-1: DrawGraph�G���[.
}

//DrawRectGraph�̉�����.
//Rect = ��`(�����`�Ⓑ���`�̂���)
int DrawRectGraphST(const IMG_DRAW_RECT* img) {

	if (img->handle == 0) {
		return -2; //-2: handle���ݒ�.
	}
	int err = DrawRectGraph(
		img->pos.x,   img->pos.y,
		img->stPxl.x, img->stPxl.y,
		img->size.x,  img->size.y,
		img->handle,  img->isTrans
	);
	return err; //-1: DrawRectGraph�G���[.
}