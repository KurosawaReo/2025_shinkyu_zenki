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
			(float)data->pos[0].x, (float)data->pos[0].y,
			(float)data->pos[1].x, (float)data->pos[1].y,
			(float)data->pos[2].x, (float)data->pos[2].y, data->clr, isFill
		);
		if (err < 0) {
			return -1; //-1: DrawTriangleAA�ŃG���[.
		}
	}
	//�A���`�G�C���A�X�Ȃ�.
	else {
		int err = DrawTriangle(
			_int(data->pos[0].x), _int(data->pos[0].y),
			_int(data->pos[1].x), _int(data->pos[1].y),
			_int(data->pos[2].x), _int(data->pos[2].y), data->clr, isFill
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
int DrawImgST::LoadGraphST(my_string fileName) {

	img.resize(1); //�T�C�Y��ݒ�.

	//�摜�ǂݍ���.
	img[0].handle = LoadGraph(fileName.c_str());
	int err = GetGraphSize(img[0].handle, &img[0].size.x, &img[0].size.y);
	
	if (img[0].handle < 0) {
		return -1; //-1: LoadGraph�G���[.
	}
	if (err < 0) {
		return -2; //-2: GetGraphSize�G���[.
	}
	return 0; //����I��.
}
//LoadDivGraph�̉�����.
int DrawImgST::LoadDivGraphST(my_string fileName, INT_XY size, INT_XY cnt) {

	int* pHandle = new int[cnt.x*cnt.y]; //LoadDivGraph����n���h�����o���p.

	//�摜�����ǂݍ���.
	int err = LoadDivGraph(fileName.c_str(), cnt.x*cnt.y, cnt.x, cnt.y, size.x, size.y, pHandle);
	if (err < 0) {
		return -1; //-1: LoadDivGraph�G���[.
	}
	//IMG�^�z��̃T�C�Y�𕪊����ɍ��킹��.
	img.resize(cnt.x*cnt.y);
	//�������������[�v.
	for (int i = 0; i < cnt.y; i++) {
		for (int j = 0; j < cnt.x; j++) {
			img[j+i*cnt.x].handle = pHandle[j+i*cnt.x]; //�n���h���ۑ�.
			img[j+i*cnt.x].size   = size;               //�T�C�Y�ۑ�.
		}
	}

	//�z��j��.
	delete[] pHandle; pHandle = nullptr;

	return 0; //����I��.
}
//DrawGraph�̉�����.
int DrawImgST::DrawGraphST(int imgNo, INT_XY pos, BOOL isCenter, BOOL isTrans) {

	float x = (float)pos.x;
	float y = (float)pos.y;

	//�������W���[�h.
	if (isCenter) {
		x -= (float)(img[imgNo].size.x-1)/2;
		y -= (float)(img[imgNo].size.y-1)/2;
	}

	if (img[imgNo].handle == 0) {
		return -2; //-2: handle���ݒ�.
	}
	int err = DrawGraph(_int(x), _int(y), img[imgNo].handle, isTrans);
	return err; //-1: DrawGraph�G���[.
}
//DrawRectGraph�̉�����.
//Rect = ��`(�����`�Ⓑ���`�̂���)
int DrawImgST::DrawRectGraphST(int imgNo, INT_XY pos, INT_XY stPxl, INT_XY size, BOOL isTrans) {

	if (img[imgNo].handle == 0) {
		return -2; //-2: handle���ݒ�.
	}
	int err = DrawRectGraph(
		pos.x, pos.y, stPxl.x, stPxl.y, size.x, size.y,
		img[imgNo].handle, isTrans
	);
	return err; //-1: DrawRectGraph�G���[.
}
//DrawExtendGraph�̉�����.
int DrawImgST::DrawExtendGraphST(int imgNo, INT_XY pos, DBL_XY sizeRate, BOOL isCenter, BOOL isTrans) {

	float x1, y1, x2, y2;

	//��������ǂ���.
	if (isCenter) {
		x1 = (float)(pos.x - (float)(img[imgNo].size.x-1)/2 * sizeRate.x);
		y1 = (float)(pos.y - (float)(img[imgNo].size.y-1)/2 * sizeRate.y);
		x2 = (float)(pos.x + (float)(img[imgNo].size.x-1)/2 * sizeRate.x);
		y2 = (float)(pos.y + (float)(img[imgNo].size.y-1)/2 * sizeRate.y);
	}
	else {
		x1 = (float)pos.x;
		y1 = (float)pos.y;
		x2 = (float)(pos.x + (img[imgNo].size.x-1) * sizeRate.x);
		y2 = (float)(pos.y + (img[imgNo].size.y-1) * sizeRate.y);
	}

	int err = DrawExtendGraph(_int(x1), _int(y1), _int(x2), _int(y2), img[imgNo].handle, isTrans);
	return err; //-1: DrawExtendGraph�G���[.
}
//DrawRotaGraph�̉�����.
int DrawImgST::DrawRotaGraphST(int imgNo, INT_XY pos, double extend, double ang, BOOL isCenter, BOOL isTrans) {

	float x = (float)pos.x;
	float y = (float)pos.y;

	//�������W���[�h.
	if (isCenter) {
		x -= (float)(img[imgNo].size.x-1)/2;
		y -= (float)(img[imgNo].size.y-1)/2;
	}

	if (img[imgNo].handle == 0) {
		return -2; //-2: handle���ݒ�.
	}
	int err = DrawRotaGraph(_int(x), _int(y),extend, ang, img[imgNo].handle, isTrans);
	return err; //-1: DrawRotaGraph�G���[.
}

//DrawString�̉�����.
int DrawStrST::DrawStringST(BOOL isCenter, int font) {
	
	float x = (float)str.pos.x;
	float y = (float)str.pos.y;

	//�������W���[�h.
	if (isCenter) {
		x -= (float)(GetTextSize(str.text, font).x-1)/2;
		y -= (float)(GetTextSize(str.text, font).y-1)/2;
	}

	//�f�t�H���g�t�H���g.
	if (font < 0) {
		int err = DrawString(_int(x), _int(y), str.text.c_str(), str.clr);
		if (err < 0) {
			return -1; //-1: DrawString�ŃG���[.
		}
	}
	//�t�H���g�ݒ肠��.
	else {
		int err = DrawStringToHandle(_int(x), _int(y), str.text.c_str(), str.clr, font);
		if (err < 0) {
			return -2; //-2: DrawStringToHandle�ŃG���[.
		}
	}
	return 0; //����I��.
}
//DrawRotaString�̉�����.
int DrawStrST::DrawRotaStringST(INT_XY extend, INT_XY pivot, double ang, BOOL isVertical, int font) {

	double rad = _rad(ang); //�p�x�����W�A���ɕϊ�.

	//�f�t�H���g�t�H���g.
	if (font < 0) {
		int err = DrawRotaString(
			str.pos.x, str.pos.y, extend.x, extend.y, pivot.x, pivot.y,
			rad, str.clr, 0, isVertical, str.text.c_str()
		);
		if (err < 0) {
			return -1; //-1: DrawRotaString�ŃG���[.
		}
	}
	//�t�H���g�ݒ肠��.
	else {
		int err = DrawRotaStringToHandle(
			str.pos.x, str.pos.y, extend.x, extend.y, pivot.x, pivot.y,
			rad, str.clr, font, 0, isVertical, str.text.c_str()
		);
		if (err < 0) {
			return -2; //-2: DrawRotaStringToHandle�ŃG���[.
		}
	}
	return 0; //����I��.
}
//DrawModiString�̉�����.
int DrawStrST::DrawModiStringST(INT_XY luPos, INT_XY ruPos, INT_XY rdPos, INT_XY ldPos, BOOL isVertical, int font) {

	//�f�t�H���g�t�H���g.
	if (font < 0) {
		int err = DrawModiString(
			luPos.x, luPos.y, ruPos.x, ruPos.y,
			rdPos.x, rdPos.y, ldPos.x, ldPos.y,
			str.clr, 0, isVertical, str.text.c_str()
		);
		if (err < 0) {
			return -1; //-1: DrawModiString�ŃG���[.
		}
	}
	//�t�H���g�ݒ肠��.
	else {
		int err = DrawModiStringToHandle(
			luPos.x, luPos.y, ruPos.x, ruPos.y,
			rdPos.x, rdPos.y, ldPos.x, ldPos.y,
			str.clr, font, 0, isVertical, str.text.c_str()
		);
		if (err < 0) {
			return -2; //-2: DrawModiStringToHandle�ŃG���[.
		}
	}
	return 0; //����I��.
}

//�e�L�X�g�̃T�C�Y�擾.
INT_XY DrawStrST::GetTextSize(my_string str, int font) {
	
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