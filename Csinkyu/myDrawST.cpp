/*
   - myDrawST.cpp - (original)
   ver.2025/07/26
   
   DxLib: �I���W�i���`��@�\�̒ǉ�.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx���ɓ����ĂȂ���΂����œ���.
#endif
#include "myDrawST.h"

//DrawCircle�̉�����.
int DrawCircleST(const Circle* data, BOOL isFill, BOOL isAnti, float thick) {

	int ret;
	//�A���`�G�C���A�X����.
	if (isAnti) {
		//posnum(�p�`��)��60�ɐݒ肷��.
		ret = DrawCircleAA((float)data->pos.x, (float)data->pos.y, data->r, 60, data->clr, isFill, thick);
	}
	//�A���`�G�C���A�X�Ȃ�.
	else{
		ret = DrawCircle(_int(data->pos.x), _int(data->pos.y), _int(data->r), data->clr, isFill, (int)thick);
	}
	return ret;
}
//DrawBox�̉�����.
int DrawBoxST(const Box* data, BOOL isCenter, BOOL isFill, BOOL isAnti) {

	int ret;
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

	//�A���`�G�C���A�X����.
	if (isAnti) {
		ret = DrawBoxAA((float)x1, (float)y1, (float)x2, (float)y2, data->clr, isFill);
	}
	//�A���`�G�C���A�X�Ȃ�.
	else {
		ret = DrawBox(_int(x1), _int(y1), _int(x2), _int(y2), data->clr, isFill);
	}
	return ret;
}
//DrawTriangle�̉�����.
int DrawTriangleST(const Triangle* data, BOOL isFill, BOOL isAnti) {

	int ret;
	//�A���`�G�C���A�X����.
	if (isAnti) {
		ret = DrawTriangleAA(
			data->pos[0].x, data->pos[0].y,
			data->pos[1].x, data->pos[1].y,
			data->pos[2].x, data->pos[2].y, data->clr, isFill
		);
	}
	//�A���`�G�C���A�X�Ȃ�.
	else {
		ret = DrawTriangle(
			data->pos[0].x, data->pos[0].y,
			data->pos[1].x, data->pos[1].y,
			data->pos[2].x, data->pos[2].y, data->clr, isFill
		);
	}
	return ret;
}
//DrawLine�̉�����.
int DrawLineST(const Line* data, BOOL isAnti, float thick) {

	int ret;
	//�A���`�G�C���A�X����.
	if (isAnti) {
		ret = DrawLineAA(
			(float)data->stPos.x, (float)data->stPos.y,
			(float)data->edPos.x, (float)data->edPos.y, data->clr, thick
		);
	}
	//�A���`�G�C���A�X�Ȃ�.
	else {
		ret = DrawLine(
			_int(data->stPos.x), _int(data->stPos.y), 
			_int(data->edPos.x), _int(data->edPos.y), data->clr, (int)thick
		);
	}
	return ret;
}
//��ʑS�̂ɃO���b�h����`��.
int DrawWindowGrid(int wid, int hei, int size, UINT clrWid, UINT clrHei) {

	//�c���̕`��.
	for (int x = 0; x < wid; x += size) {

		Line line = { {(double)x, 0}, {(double)x, (double)hei}, clrHei };
		int err = DrawLineST(&line);
		if (err < 0) {
			return -1; //-1: �c���ŃG���[.
		}
	}
	//�����̕`��.
	for (int y = 0; y < hei; y += size) {

		Line line = { {0, (double)y}, {(double)wid, (double)y}, clrWid };
		int err = DrawLineST(&line);
		if (err < 0) {
			return -2; //-2: �����ŃG���[.
		}
	}

	return 0;
}

//LoadGraph�̉�����.
int LoadGraphST(Image* img, my_string fileName) {

	//�摜�ǂݍ���.
	img->handle = LoadGraph(fileName.c_str());
	int err = GetGraphSize(img->handle, &img->size.x, &img->size.y);
	
	if (img->handle < 0) {
		return -1; //-1: LoadGraph�G���[.
	}
	if (err < 0) {
		return -2; //-2: GetGraphSize�G���[.
	}
	return 0; //����I��.
}
//LoadDivGraph�̉�����.
int LoadDivGraphST(vector<Image>* img, my_string fileName, INT_XY size, INT_XY cnt) {

	int ret = 0; //�G���[�l.

	int* pHandle = new int[cnt.x*cnt.y]; //LoadDivGraph����n���h�����o���p.
	vector<Image> tmpImg;                //���ۑ��p.

	//�摜�����ǂݍ���.
	int err = LoadDivGraph(fileName.c_str(), cnt.x*cnt.y, cnt.x, cnt.y, size.x, size.y, pHandle);
	if (err < 0) {
		ret = -1; //-1: LoadDivGraph�G���[.
	}
	//IMG�^�z��̃T�C�Y�𕪊����ɍ��킹��.
	tmpImg.resize(cnt.x*cnt.y);
	//�������������[�v.
	for (int i = 0; i < cnt.y; i++) {
		for (int j = 0; j < cnt.x; j++) {
			tmpImg[j+i*cnt.x].handle = pHandle[j+i*cnt.x]; //�n���h���ۑ�.
			tmpImg[j+i*cnt.x].size   = size;               //�T�C�Y�ۑ�.
		}
	}

	//������IMG�^�z��Ƀf�[�^��n��.
	*img = tmpImg;
	//�z��j��.
	delete[] pHandle; pHandle = nullptr;

	return ret;
}

//DrawGraph�̉�����.
int DrawGraphST(const DrawImg* data, BOOL isCenter, BOOL isTrans) {

	int x = data->pos.x;
	int y = data->pos.y;

	//�������W���[�h.
	if (isCenter) {
		x -= data->img.size.x / 2; //(size/2)���炷.
		y -= data->img.size.y / 2;
	}

	if (data->img.handle == 0) {
		return -2; //-2: handle���ݒ�.
	}
	int err = DrawGraph(x, y, data->img.handle, isTrans);
	return err; //-1: DrawGraph�G���[.
}
//DrawRectGraph�̉�����.
//Rect = ��`(�����`�Ⓑ���`�̂���)
int DrawRectGraphST(const DrawImgRect* data, BOOL isTrans) {

	if (data->img.handle == 0) {
		return -2; //-2: handle���ݒ�.
	}
	int err = DrawRectGraph(
		data->pos.x,      data->pos.y,
		data->stPxl.x,    data->stPxl.y,
		data->size.x,     data->size.y,
		data->img.handle, isTrans
	);
	return err; //-1: DrawRectGraph�G���[.
}
//DrawExtendGraph�̉�����.
int DrawExtendGraphST(const DrawImgExtend* data, BOOL isCenter, BOOL isTrans) {

	INT_XY pos1, pos2;

	//��������ǂ���.
	if (isCenter) {
		pos1.x = data->pos.x - data->size.x/2;
		pos1.y = data->pos.y - data->size.y/2;
		pos2.x = data->pos.x + data->size.x/2;
		pos2.y = data->pos.y + data->size.y/2;
	}
	else {
		pos1   = data->pos;
		pos2.x = data->pos.x + data->size.x;
		pos2.y = data->pos.y + data->size.y;
	}

	int err = DrawExtendGraph(pos1.x, pos1.y, pos2.x, pos2.y, data->img.handle, isTrans);
	return err; //-1: DrawExtendGraph�G���[.
}
//DrawRotaGraph�̉�����.
int DrawRotaGraphST(const DrawImgRota* data, BOOL isCenter, BOOL isTrans) {

	int x = data->pos.x;
	int y = data->pos.y;

	//�������W���[�h.
	if (isCenter) {
		x -= data->img.size.x / 2; //(size/2)���炷.
		y -= data->img.size.y / 2;
	}

	if (data->img.handle == 0) {
		return -2; //-2: handle���ݒ�.
	}
	int err = DrawRotaGraph(x, y, data->extend, data->ang, data->img.handle, isTrans);
	return err; //-1: DrawRotaGraph�G���[.
}

//DrawString�̉�����.
int DrawStringST(const DrawStr* data, BOOL isCenter, int font) {
	
	int err = 0;
	int x = data->pos.x;
	int y = data->pos.y;

	//�f�t�H���g�t�H���g.
	if (font < 0) {
		//�������W���[�h.
		if (isCenter) {
			x = data->pos.x - GetTextSize(data->text).x/2;
			y = data->pos.y - GetTextSize(data->text).y/2;
		}
		err = DrawString(x, y, data->text, data->color);
	}
	//�t�H���g�ݒ肠��.
	else {
		//�������W���[�h.
		if (isCenter) {
			x = data->pos.x - GetTextSize(data->text, font).x/2;
			y = data->pos.y - GetTextSize(data->text, font).y/2;
		}
		err = DrawStringToHandle(x, y, data->text, data->color, font);
	}

	return err;
}
//DrawRotaString�̉�����.
int DrawRotaStringST(const DrawStrRota* data, BOOL isVertical, int font) {

	int err = 0;
	double rad = data->ang * M_PI/180; //�p�x�����W�A���ɕϊ�.

	//�f�t�H���g�t�H���g.
	if (font < 0) {
		err = DrawRotaString(
			data->pos.x,    data->pos.y,
			data->extend.x, data->extend.y,
			data->pivot.x,  data->pivot.y,
			rad, data->color, 0, isVertical, data->text
		);
	}
	//�t�H���g�ݒ肠��.
	else {
		err = DrawRotaStringToHandle(
			data->pos.x,    data->pos.y,
			data->extend.x, data->extend.y,
			data->pivot.x,  data->pivot.y,
			rad, data->color, font, 0, isVertical, data->text
		);
	}

	return err;
}
//DrawModiString�̉�����.
int DrawModiStringST(const DrawStrModi* data, BOOL isVertical, int font) {

	int err = 0;

	//�f�t�H���g�t�H���g.
	if (font < 0) {
		err = DrawModiString(
			data->luPos.x, data->luPos.y, data->ruPos.x, data->ruPos.y,
			data->rdPos.x, data->rdPos.y, data->ldPos.x, data->ldPos.y,
			data->color, 0, isVertical, data->text
		);
	}
	//�t�H���g�ݒ肠��.
	else {
		err = DrawModiStringToHandle(
			data->luPos.x, data->luPos.y, data->ruPos.x, data->ruPos.y,
			data->rdPos.x, data->rdPos.y, data->ldPos.x, data->ldPos.y,
			data->color, font, 0, isVertical, data->text
		);
	}

	return err;
}

//�e�L�X�g�̃T�C�Y�擾.
INT_XY GetTextSize(my_string str, int font) {
	
	INT_XY size{};
	int    line{}; //����.

	//�f�t�H���g�t�H���g.
	if (font < 0) {
		GetDrawStringSize(&size.x, &size.y, &line, str.c_str(), 255);
	}
	//�t�H���g�ݒ肠��.
	else {
		GetDrawStringSizeToHandle(&size.x, &size.y, &line, str.c_str(), 255, font);
	}

	return size;
}

//�t�H���g�쐬.
int CreateFontH(int size, int thick, FontTypeID fontId) {
	return CreateFontToHandle(NULL, size, thick, fontId);
}

//�I�u�W�F�N�g(ObjectCir�^)�̕`��.
int DrawObjectCir(const ObjectCir* data, BOOL isDrawHit) {

	int err = 0;

	//�摜�ݒ�.
	DrawImg draw = { data->img, {} };
	draw.pos.x = _int(data->cir.pos.x + data->offset.x);
	draw.pos.y = _int(data->cir.pos.y + data->offset.y);
	//�摜�`��.
	err = DrawGraphST(&draw, TRUE);
	if (err < 0) {
		return -1; //-1: DrawGraphST�ŃG���[.
	}
	//�����蔻��\��.
	if (isDrawHit) {
		err = DrawCircleST(&data->cir, FALSE, TRUE);
		if (err < 0) {
			return -2; //-2: DrawCircleST�ŃG���[.
		}
	}
	return 0; //����I��.
}
//�I�u�W�F�N�g(ObjectBox�^)�̕`��.
int DrawObjectBox(const ObjectBox* data, BOOL isDrawHit) {

	int err = 0;

	//�摜�ݒ�.
	DrawImg draw = { data->img, {} };
	draw.pos.x = _int(data->box.pos.x + data->offset.x);
	draw.pos.y = _int(data->box.pos.y + data->offset.y);
	//�摜�`��.
	err = DrawGraphST(&draw, TRUE);
	if (err < 0) {
		return -1; //-1: DrawGraphST�ŃG���[.
	}
	//�����蔻��\��.
	if (isDrawHit) {
		err = DrawBoxST(&data->box, TRUE, FALSE, TRUE);
		if (err < 0) {
			return -2; //-2: DrawBoxST�ŃG���[.
		}
	}
	return 0; //����I��.
}
//�I�u�W�F�N�g(ObjectGrid�^)�̕`��.
int DrawObjectGrid(const ObjectGrid* data, INT_XY gridPos, INT_XY gridSize) {

	int err = 0;

	//�摜�ݒ�.
	DrawImg draw = { data->img, {} };
	draw.pos.x = gridPos.x + data->pos.x * gridSize.x;
	draw.pos.y = gridPos.y + data->pos.y * gridSize.y;
	//�摜�`��.
	err = DrawGraphST(&draw, FALSE);
	if (err < 0) {
		return -1; //-1: DrawGraphST�ŃG���[.
	}
	return 0; //����I��.
}

//�`�惂�[�h�ύX.
int SetDrawBlendModeST(BlendModeID id, int power) {
	return SetDrawBlendMode(id, power);
}
int SetDrawBlendModeST(BlendModeID id, double power) {
	return SetDrawBlendMode(id, _int(power));
}
//�`�惂�[�h���Z�b�g.
int ResetDrawBlendMode() {
	return SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}