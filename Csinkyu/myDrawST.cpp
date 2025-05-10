/*
   - myDrawST.cpp - (original)
   
   DxLib�Ŏg���p�̃I���W�i���`��֐�.
*/
#if false
  #include "stdafx.h" //stdafx������Ȃ炱�������g��.
#else
  #define _USE_MATH_DEFINES //math�萔���g���̂ɕK�v.
  #include <math.h>
  #include "DxLib.h"
#endif

#include "myDrawST.h"

//���̕`��֐�.
INT_XY DrawLineAng(INT_XY stPos, float ang, float len, int clr, int thick) {

	//�p�x��rad�ɕϊ����A���W�̌v�Z.
	int y = _int(sin(ang * M_PI/180) * len);
	int x = _int(cos(ang * M_PI/180) * len);
	//�I�_���W.
	INT_XY edPos = { stPos.x+x, stPos.y+y };
	//�n�_����I�_�֕`��.
	DrawLine(stPos.x, stPos.y, edPos.x, edPos.y, clr, thick);

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
int DrawGraphST(const IMG_DRAW* data) {

	if (data->img.handle == 0) {
		return -2; //-2: handle���ݒ�.
	}

	int x = data->pos.x;
	int y = data->pos.y;

	//�������W���[�h.
	if (data->isCenter) {
		x -= data->img.size.x / 2; //(size/2)���炷.
		y -= data->img.size.y / 2;
	}

	int err = DrawGraph(x, y, data->img.handle, data->isTrans);
	return err; //-1: DrawGraph�G���[.
}

//DrawRectGraph�̉�����.
//Rect = ��`(�����`�Ⓑ���`�̂���)
int DrawRectGraphST(const IMG_DRAW_RECT* data) {

	if (data->img.handle == 0) {
		return -2; //-2: handle���ݒ�.
	}
	int err = DrawRectGraph(
		data->pos.x,      data->pos.y,
		data->stPxl.x,    data->stPxl.y,
		data->size.x,     data->size.y,
		data->img.handle, data->isTrans
	);
	return err; //-1: DrawRectGraph�G���[.
}

//DrawString�̉�����.
int DrawStringST(const STR_DRAW* data, int font) {
	
	int ret = 0;

	//�f�t�H���g�t�H���g.
	if (font < 0) {
		ret = DrawString(data->pos.x, data->pos.y, data->text, data->color);
	}
	//�t�H���g�ݒ肠��.
	else {
		ret = DrawStringToHandle(data->pos.x, data->pos.y, data->text, data->color, font);
	}

	return ret;
}
//DrawRotaString�̉�����.
int DrawRotaStringST(const STR_DRAW_ROTA* data, int font) {

	int ret = 0;
	double rad = data->ang * M_PI/180; //�p�x�����W�A���ɕϊ�.

	//�f�t�H���g�t�H���g.
	if (font < 0) {
		ret = DrawRotaString(
			data->pos.x,    data->pos.y,
			data->extend.x, data->extend.y,
			data->pivot.x,  data->pivot.y,
			rad, data->color, 0, data->isVertical, data->text
		);
	}
	//�t�H���g�ݒ肠��.
	else {
		ret = DrawRotaStringToHandle(
			data->pos.x,    data->pos.y,
			data->extend.x, data->extend.y,
			data->pivot.x,  data->pivot.y,
			rad, data->color, font, 0, data->isVertical, data->text
		);
	}

	return ret;
}
//DrawModiString�̉�����.
int DrawModiStringST(const STR_DRAW_MODI* data, int font) {

	int ret = 0;

	//�f�t�H���g�t�H���g.
	if (font < 0) {
		ret = DrawModiString(
			data->luPos.x, data->luPos.y, data->ruPos.x, data->ruPos.y,
			data->rdPos.x, data->rdPos.y, data->ldPos.x, data->ldPos.y,
			data->color, 0, data->isVertical, data->text
		);
	}
	//�t�H���g�ݒ肠��.
	else {
		ret = DrawModiStringToHandle(
			data->luPos.x, data->luPos.y, data->ruPos.x, data->ruPos.y,
			data->rdPos.x, data->rdPos.y, data->ldPos.x, data->ldPos.y,
			data->color, font, 0, data->isVertical,	data->text
		);
	}

	return ret;
}