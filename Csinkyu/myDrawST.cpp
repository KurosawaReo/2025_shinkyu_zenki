/*
   - myDrawST.cpp - (original)
   ver.2025/06/18
   
   DxLib�Ŏg���p�̃I���W�i���`��֐�.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx���Ȃ���΂����Œ�`.
#endif

#include "myDrawST.h"

//DrawCircle�̉�����.
int DrawCircleST(const Circle* data, BOOL isFill, int thick) {

	int ret = DrawCircle(_int(data->pos.x), _int(data->pos.y), data->r, data->clr, isFill, thick);
	return ret;
}
//DrawBox�̉�����.
int DrawBoxST(const Box* data, BOOL isCenter, BOOL isFill) {

	double x1, x2, y1, y2;

	//��������ǂ���.
	if (isCenter) {
		x1 = data->pos.x - data->size.x/2;
		x2 = data->pos.x + data->size.x/2;
		y1 = data->pos.y - data->size.y/2;
		y2 = data->pos.y + data->size.y/2;
	}
	else {
		x1 = data->pos.x;
		x2 = data->pos.x + data->size.x;
		y1 = data->pos.y;
		y2 = data->pos.y + data->size.y;
	}

	int ret = DrawBox(_int(x1), _int(y1), _int(x2), _int(y2), data->clr, isFill);
	return ret;
}
//DrawLine�̉�����.
int DrawLineST(const Line* data, int thick) {

	int ret = DrawLine(
		_int(data->stPos.x), _int(data->stPos.y), 
		_int(data->edPos.x), _int(data->edPos.y), data->clr, thick
	);
	return ret;
}

//LoadGraph�̉�����.
int LoadGraphST(IMG* img, const TCHAR fileName[]) {

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

	int x = data->pos.x;
	int y = data->pos.y;

	//�������W���[�h.
	if (data->isCenter) {
		x -= data->img.size.x / 2; //(size/2)���炷.
		y -= data->img.size.y / 2;
	}

	if (data->img.handle == 0) {
		return -2; //-2: handle���ݒ�.
	}
	int err = DrawGraph(x, y, data->img.handle, data->isTrans);
	return err; //-1: DrawGraph�G���[.
}

//DrawRotaGraph�̉�����.
int DrawRotaGraphST(const IMG_DRAW_ROTA* data) {

	int x = data->pos.x;
	int y = data->pos.y;

	//�������W���[�h.
	if (data->isCenter) {
		x -= data->img.size.x / 2; //(size/2)���炷.
		y -= data->img.size.y / 2;
	}

	if (data->img.handle == 0) {
		return -2; //-2: handle���ݒ�.
	}
	int err = DrawRotaGraph(x, y, data->extend, data->ang, data->img.handle, data->isTrans);
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
int DrawStringST(const STR_DRAW* data, BOOL isCenter, int font) {
	
	int ret = 0;
	int x = data->pos.x;
	int y = data->pos.y;

	//�f�t�H���g�t�H���g.
	if (font < 0) {
		//�������W���[�h.
		if (isCenter) {
			x = data->pos.x - GetTextSize(data->text).x/2;
			y = data->pos.y - GetTextSize(data->text).y/2;
		}
		ret = DrawString(x, y, data->text, data->color);
	}
	//�t�H���g�ݒ肠��.
	else {
		//�������W���[�h.
		if (isCenter) {
			x = data->pos.x - GetTextSize(data->text, font).x/2;
			y = data->pos.y - GetTextSize(data->text, font).y/2;
		}
		ret = DrawStringToHandle(x, y, data->text, data->color, font);
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

//�e�L�X�g�̃T�C�Y�擾.
INT_XY GetTextSize(const TCHAR str[], int font) {
	
	INT_XY size;
	int    line; //����.

	//�f�t�H���g�t�H���g.
	if (font < 0) {
		GetDrawStringSize(&size.x, &size.y, &line, str, 255);
	}
	//�t�H���g�ݒ肠��.
	else {
		GetDrawStringSizeToHandle(&size.x, &size.y, &line, str, 255, font);
	}

	return size;
}

//�t�H���g�쐬.
int CreateFontH(int size, int thick, FONTTYPE_ID fontId) {
	return CreateFontToHandle(NULL, size, thick, fontId);
}

//�I�u�W�F�N�g(ObjectBox�^)�̕`��.
int DrawObjectBox(const ObjectBox* data, BOOL isDrawHit) {

	int ret = 0;

	//�摜�ݒ�.
	IMG_DRAW draw = { data->img, {}, TRUE, TRUE };
	draw.pos.x = _int(data->box.pos.x + data->offset.x);
	draw.pos.y = _int(data->box.pos.y + data->offset.y);
	//�摜�`��.
	ret = DrawGraphST(&draw);
	if (ret < 0) {
		return -1; //-1:DrawGraphST�Ŗ�蔭��.
	}

	//�����蔻��\��.
	if (isDrawHit) {
		ret = DrawBoxST(&data->box, TRUE, FALSE);
		if (ret < 0) {
			return -2; //-2:DrawBoxST�Ŗ�蔭��.
		}
	}

	return 0; //����I��.
}
//�I�u�W�F�N�g(ObjectCir�^)�̕`��.
int DrawObjectCir(const ObjectCir* data, BOOL isDrawHit) {

	int ret = 0;

	//�摜�ݒ�.
	IMG_DRAW draw = { data->img, {}, TRUE, TRUE };
	draw.pos.x = _int(data->cir.pos.x + data->offset.x);
	draw.pos.y = _int(data->cir.pos.y + data->offset.y);
	//�摜�`��.
	ret = DrawGraphST(&draw);
	if (ret < 0) {
		return -1; //-1:DrawGraphST�Ŗ�蔭��.
	}

	//�����蔻��\��.
	if (isDrawHit) {
		ret = DrawCircleST(&data->cir, FALSE);
		if (ret < 0) {
			return -2; //-2:DrawBoxST�Ŗ�蔭��.
		}
	}

	return 0; //����I��.
}