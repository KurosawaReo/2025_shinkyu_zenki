/*
   - myDrawST.cpp - (original)
   ver.2025/07/27
   
   DxLib: �I���W�i���`��@�\�̒ǉ�.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx���ɓ����ĂȂ���΂����œ���.
#endif
#include "myDrawST.h"

/*
   [size�ɂ���]
   �[����[�܂ł̒�����size�Ƃ���.
   ���̎��A�n�_���W+(size-1)�ƌv�Z���邱�Ƃɒ���.
   ������̏ꍇ�A(size-1)/2���点��ok.

   �P�Q�R�S
   ��������
   ���@�@��
   ���@�@��
   ��������
*/

//DrawCircle�̉�����.
int DrawCircleST(const Circle* data, BOOL isFill, BOOL isAnti, float thick) {

	//�A���`�G�C���A�X����.
	if (isAnti) {
		//posnum(�p�`��)��60�ɐݒ肷��.
		int err = DrawCircleAA((float)data->pos.x, (float)data->pos.y, data->r, 60, data->clr, isFill, thick);
		if (err < 0) {
			return -1; //-1: DrawCircleAA�ŃG���[.
		}
	}
	//�A���`�G�C���A�X�Ȃ�.
	else{
		int err = DrawCircle(_int(data->pos.x), _int(data->pos.y), _int(data->r), data->clr, isFill, (int)thick);
		if (err < 0) {
			return -2; //-2: DrawCircle�ŃG���[.
		}
	}
	return 0; //����I��.
}
//DrawBox�̉�����.
int DrawBoxST(const Box* data, BOOL isCenter, BOOL isFill, BOOL isAnti) {

	if (data->size.x <= 0 || data->size.y <= 0) {
		return -3; //-3: �T�C�Y��0�ȉ�.
	}

	double x1, x2, y1, y2;

	//��������ǂ���.
	if (isCenter) {
		x1 = data->pos.x - (data->size.x-1)/2;
		y1 = data->pos.y - (data->size.y-1)/2;
		x2 = data->pos.x + (data->size.x-1)/2;
		y2 = data->pos.y + (data->size.y-1)/2;
	}
	else {
		x1 = data->pos.x;
		y1 = data->pos.y;
		x2 = data->pos.x + (data->size.x-1);
		y2 = data->pos.y + (data->size.y-1);
	}

	//�A���`�G�C���A�X����.
	if (isAnti) {
		int err = DrawBoxAA((float)x1, (float)y1, (float)x2, (float)y2, data->clr, isFill);
		if (err < 0) {
			return -1; //-1: DrawBoxAA�ŃG���[.
		}
	}
	//�A���`�G�C���A�X�Ȃ�.
	else {
		int err = DrawBox(_int(x1), _int(y1), _int(x2), _int(y2), data->clr, isFill);
		if (err < 0) {
			return -2; //-2: DrawBox�ŃG���[.
		}
	}
	return 0; //����I��.
}
//DrawTriangle�̉�����.
int DrawTriangleST(const Triangle* data, BOOL isFill, BOOL isAnti) {

	//�A���`�G�C���A�X����.
	if (isAnti) {
		int err = DrawTriangleAA(
			data->pos[0].x, data->pos[0].y,
			data->pos[1].x, data->pos[1].y,
			data->pos[2].x, data->pos[2].y, data->clr, isFill
		);
		if (err < 0) {
			return -1; //-1: DrawTriangleAA�ŃG���[.
		}
	}
	//�A���`�G�C���A�X�Ȃ�.
	else {
		int err = DrawTriangle(
			data->pos[0].x, data->pos[0].y,
			data->pos[1].x, data->pos[1].y,
			data->pos[2].x, data->pos[2].y, data->clr, isFill
		);
		if (err < 0) {
			return -2; //-2: DrawTriangle�ŃG���[.
		}
	}
	return 0; //����I��.
}
//DrawLine�̉�����.
int DrawLineST(const Line* data, BOOL isAnti, float thick) {

	//�A���`�G�C���A�X����.
	if (isAnti) {
		int err = DrawLineAA(
			(float)data->stPos.x, (float)data->stPos.y,
			(float)data->edPos.x, (float)data->edPos.y, data->clr, thick
		);
		if (err < 0) {
			return -1; //-1: DrawLineAA�ŃG���[.
		}
	}
	//�A���`�G�C���A�X�Ȃ�.
	else {
		int err = DrawLine(
			_int(data->stPos.x), _int(data->stPos.y), 
			_int(data->edPos.x), _int(data->edPos.y), data->clr, (int)thick
		);
		if (err < 0) {
			return -2; //-2: DrawLine�ŃG���[.
		}
	}
	return 0; //����I��.
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
	return 0; //����I��.
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

	int* pHandle = new int[cnt.x*cnt.y]; //LoadDivGraph����n���h�����o���p.
	vector<Image> tmpImg;                //���ۑ��p.

	//�摜�����ǂݍ���.
	int err = LoadDivGraph(fileName.c_str(), cnt.x*cnt.y, cnt.x, cnt.y, size.x, size.y, pHandle);
	if (err < 0) {
		return -1; //-1: LoadDivGraph�G���[.
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

	return 0; //����I��.
}

//DrawGraph�̉�����.
int DrawGraphST(const DrawImg* data, BOOL isCenter, BOOL isTrans) {

	float x = (float)data->pos.x;
	float y = (float)data->pos.y;

	//�������W���[�h.
	if (isCenter) {
		x -= (float)(data->img.size.x-1)/2;
		y -= (float)(data->img.size.y-1)/2;
	}

	if (data->img.handle == 0) {
		return -2; //-2: handle���ݒ�.
	}
	int err = DrawGraph(_int(x), _int(y), data->img.handle, isTrans);
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

	float x1, y1, x2, y2;

	//��������ǂ���.
	if (isCenter) {
		x1 = (float)(data->pos.x - (float)(data->img.size.x-1)/2 * data->sizeRate.x);
		y1 = (float)(data->pos.y - (float)(data->img.size.y-1)/2 * data->sizeRate.y);
		x2 = (float)(data->pos.x + (float)(data->img.size.x-1)/2 * data->sizeRate.x);
		y2 = (float)(data->pos.y + (float)(data->img.size.y-1)/2 * data->sizeRate.y);
	}
	else {
		x1 = (float)data->pos.x;
		y1 = (float)data->pos.y;
		x2 = (float)(data->pos.x + (data->img.size.x-1) * data->sizeRate.x);
		y2 = (float)(data->pos.y + (data->img.size.y-1) * data->sizeRate.y);
	}

	int err = DrawExtendGraph(_int(x1), _int(y1), _int(x2), _int(y2), data->img.handle, isTrans);
	return err; //-1: DrawExtendGraph�G���[.
}
//DrawRotaGraph�̉�����.
int DrawRotaGraphST(const DrawImgRota* data, BOOL isCenter, BOOL isTrans) {

	float x = (float)data->pos.x;
	float y = (float)data->pos.y;

	//�������W���[�h.
	if (isCenter) {
		x -= (float)(data->img.size.x-1)/2;
		y -= (float)(data->img.size.y-1)/2;
	}

	if (data->img.handle == 0) {
		return -2; //-2: handle���ݒ�.
	}
	int err = DrawRotaGraph(_int(x), _int(y), data->extend, data->ang, data->img.handle, isTrans);
	return err; //-1: DrawRotaGraph�G���[.
}

//DrawString�̉�����.
int DrawStringST(const DrawStr* data, BOOL isCenter, int font) {
	
	float x = (float)data->pos.x;
	float y = (float)data->pos.y;

	//�f�t�H���g�t�H���g.
	if (font < 0) {
		//�������W���[�h.
		if (isCenter) {
			x -= (float)(GetTextSize(data->text).x-1)/2;
			y -= (float)(GetTextSize(data->text).y-1)/2;
		}
		int err = DrawString(_int(x), _int(y), data->text, data->color);
		if (err < 0) {
			return -1; //-1: DrawString�ŃG���[.
		}
	}
	//�t�H���g�ݒ肠��.
	else {
		//�������W���[�h.
		if (isCenter) {
			x -= (float)(GetTextSize(data->text, font).x-1)/2;
			y -= (float)(GetTextSize(data->text, font).y-1)/2;
			printfDx(L"size:%d\n", GetTextSize(data->text, font).y);
			printfDx(L"x:%f y:%f\n", x, y);
		}
		int err = DrawStringToHandle(_int(x), _int(y), data->text, data->color, font);
		if (err < 0) {
			return -2; //-2: DrawStringToHandle�ŃG���[.
		}
	}
	return 0; //����I��.
}
//DrawRotaString�̉�����.
int DrawRotaStringST(const DrawStrRota* data, BOOL isVertical, int font) {

	double rad = _rad(data->ang); //�p�x�����W�A���ɕϊ�.

	//�f�t�H���g�t�H���g.
	if (font < 0) {
		int err = DrawRotaString(
			data->pos.x,    data->pos.y,
			data->extend.x, data->extend.y,
			data->pivot.x,  data->pivot.y,
			rad, data->color, 0, isVertical, data->text
		);
		if (err < 0) {
			return -1; //-1: DrawRotaString�ŃG���[.
		}
	}
	//�t�H���g�ݒ肠��.
	else {
		int err = DrawRotaStringToHandle(
			data->pos.x,    data->pos.y,
			data->extend.x, data->extend.y,
			data->pivot.x,  data->pivot.y,
			rad, data->color, font, 0, isVertical, data->text
		);
		if (err < 0) {
			return -2; //-2: DrawRotaStringToHandle�ŃG���[.
		}
	}
	return 0; //����I��.
}
//DrawModiString�̉�����.
int DrawModiStringST(const DrawStrModi* data, BOOL isVertical, int font) {

	//�f�t�H���g�t�H���g.
	if (font < 0) {
		int err = DrawModiString(
			data->luPos.x, data->luPos.y, data->ruPos.x, data->ruPos.y,
			data->rdPos.x, data->rdPos.y, data->ldPos.x, data->ldPos.y,
			data->color, 0, isVertical, data->text
		);
		if (err < 0) {
			return -1; //-1: DrawModiString�ŃG���[.
		}
	}
	//�t�H���g�ݒ肠��.
	else {
		int err = DrawModiStringToHandle(
			data->luPos.x, data->luPos.y, data->ruPos.x, data->ruPos.y,
			data->rdPos.x, data->rdPos.y, data->ldPos.x, data->ldPos.y,
			data->color, font, 0, isVertical, data->text
		);
		if (err < 0) {
			return -2; //-2: DrawModiStringToHandle�ŃG���[.
		}
	}
	return 0; //����I��.
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
	size.y -= 2; //2pixel�̂��ꂪ���邽�ߒ���.

	return size;
}

//�t�H���g�쐬.
int CreateFontH(int size, int thick, FontTypeID fontId) {
	return CreateFontToHandle(NULL, size, thick, fontId);
}

//�I�u�W�F�N�g(ObjectCir�^)�̕`��.
int DrawObjectCir(const ObjectCir* data, BOOL isDrawHit) {

	//�摜�ݒ�.
	DrawImg draw = { data->img, {} };
	draw.pos.x = _int(data->cir.pos.x + data->offset.x);
	draw.pos.y = _int(data->cir.pos.y + data->offset.y);
	//�摜�`��.
	int err = DrawGraphST(&draw, TRUE);
	if (err < 0) {
		return -1; //-1: DrawGraphST�ŃG���[.
	}
	//�����蔻��\��.
	if (isDrawHit) {
		int err = DrawCircleST(&data->cir, FALSE, TRUE);
		if (err < 0) {
			return -2; //-2: DrawCircleST�ŃG���[.
		}
	}
	return 0; //����I��.
}
//�I�u�W�F�N�g(ObjectBox�^)�̕`��.
int DrawObjectBox(const ObjectBox* data, BOOL isDrawHit) {

	//�摜�ݒ�.
	DrawImg draw = { data->img, {} };
	draw.pos.x = _int(data->box.pos.x + data->offset.x);
	draw.pos.y = _int(data->box.pos.y + data->offset.y);
	//�摜�`��.
	int err = DrawGraphST(&draw, TRUE);
	if (err < 0) {
		return -1; //-1: DrawGraphST�ŃG���[.
	}
	//�����蔻��\��.
	if (isDrawHit) {
		int err = DrawBoxST(&data->box, TRUE, FALSE, TRUE);
		if (err < 0) {
			return -2; //-2: DrawBoxST�ŃG���[.
		}
	}
	return 0; //����I��.
}
//�I�u�W�F�N�g(ObjectGrid�^)�̕`��.
int DrawObjectGrid(const ObjectGrid* data, INT_XY gridPos, INT_XY gridSize) {

	//�摜�ݒ�.
	DrawImg draw = { data->img, {} };
	draw.pos.x = gridPos.x + data->pos.x * gridSize.x;
	draw.pos.y = gridPos.y + data->pos.y * gridSize.y;
	//�摜�`��.
	int err = DrawGraphST(&draw, FALSE);
	return err; //-1: DrawGraphST�ŃG���[.
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