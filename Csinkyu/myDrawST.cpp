/*
   - myDrawST.cpp - (original)
   ver.2025/08/03
   
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

//�A���J�[���W.
static const DBL_XY anchorPos[9] = {
	{0.0, 0.0}, {0.5, 0.0}, {1.0, 0.0},
	{0.0, 0.5}, {0.5, 0.5}, {1.0, 0.5},
	{0.0, 1.0}, {0.5, 1.0}, {1.0, 1.0}
};

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
int DrawBoxST(const Box* data, Anchor anc, BOOL isFill, BOOL isAnti) {

	if (data->size.x <= 0 || data->size.y <= 0) {
		return -3; //-3: �T�C�Y��0�ȉ�.
	}

	//�n�_�����߂�.
	float x1 = (float)(data->pos.x - (data->size.x-1) * anchorPos[anc].x);
	float y1 = (float)(data->pos.y - (data->size.y-1) * anchorPos[anc].y);
	//�I�_�����߂�.
	float x2 = (float)(data->pos.x + (data->size.x-1) * (1-anchorPos[anc].x));
	float y2 = (float)(data->pos.y + (data->size.y-1) * (1-anchorPos[anc].y));

	//�A���`�G�C���A�X����.
	if (isAnti) {
		int err = DrawBoxAA(x1, y1, x2, y2, data->clr, isFill);
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
int DrawImgST::LoadGraphST(MY_STRING fileName) {

	//�摜�ǂݍ���.
	data.handle = LoadGraph(fileName.c_str());
	int err = GetGraphSize(data.handle, &data.size.x, &data.size.y);
	
	if (data.handle < 0) {
		return -1; //-1: LoadGraph�G���[.
	}
	if (err < 0) {
		return -2; //-2: GetGraphSize�G���[.
	}
	return 0; //����I��.
}
//LoadDivGraph�̉�����.
int DrawDivImgST::LoadDivGraphST(MY_STRING fileName, INT_XY size, INT_XY cnt) {

	int* pHandle = new int[cnt.x*cnt.y]; //LoadDivGraph����n���h�����o���p.

	//�摜�����ǂݍ���.
	int err = LoadDivGraph(fileName.c_str(), cnt.x*cnt.y, cnt.x, cnt.y, size.x, size.y, pHandle);
	if (err < 0) {
		return -1; //-1: LoadDivGraph�G���[.
	}
	//Image�^�z��̃T�C�Y�𕪊����ɍ��킹��.
	data.resize(cnt.x*cnt.y);
	//�������������[�v.
	for (int i = 0; i < cnt.y; i++) {
		for (int j = 0; j < cnt.x; j++) {
			data[j+i*cnt.x].handle = pHandle[j+i*cnt.x]; //�n���h���ۑ�.
			data[j+i*cnt.x].size   = size;               //�T�C�Y�ۑ�.
		}
	}

	//�z��j��.
	delete[] pHandle; pHandle = nullptr;

	return 0; //����I��.
}

//DrawGraph�̉�����.
int DrawImgST::DrawGraphST(INT_XY pos, Anchor anc, BOOL isTrans) {

	//��_�ɍ��W�����炷.
	float x = (float)(pos.x - (data.size.x-1) * anchorPos[anc].x);
	float y = (float)(pos.y - (data.size.y-1) * anchorPos[anc].y);

	if (data.handle == 0) {
		return -2; //-2: handle���ݒ�.
	}
	int err = DrawGraph(_int(x), _int(y), data.handle, isTrans);
	return err; //-1: DrawGraph�G���[.
}
int DrawDivImgST::DrawGraphST(int imgNo, INT_XY pos, Anchor anc, BOOL isTrans) {

	//��_�ɍ��W�����炷.
	float x = (float)(pos.x - (data[imgNo].size.x-1) * anchorPos[anc].x);
	float y = (float)(pos.y - (data[imgNo].size.y-1) * anchorPos[anc].y);

	if (data[imgNo].handle == 0) {
		return -2; //-2: handle���ݒ�.
	}
	int err = DrawGraph(_int(x), _int(y), data[imgNo].handle, isTrans);
	return err; //-1: DrawGraph�G���[.
}
//DrawRectGraph�̉�����.
//Rect = ��`(�����`�Ⓑ���`�̂���)
int DrawImgST::DrawRectGraphST(INT_XY pos, INT_XY stPos, INT_XY size, BOOL isTrans) {

	if (data.handle == 0) {
		return -2; //-2: handle���ݒ�.
	}
	int err = DrawRectGraph(
		pos.x, pos.y, stPos.x, stPos.y, size.x, size.y,
		data.handle, isTrans
	);
	return err; //-1: DrawRectGraph�G���[.
}
int DrawDivImgST::DrawRectGraphST(int imgNo, INT_XY pos, INT_XY stPos, INT_XY size, BOOL isTrans) {

	if (data[imgNo].handle == 0) {
		return -2; //-2: handle���ݒ�.
	}
	int err = DrawRectGraph(
		pos.x, pos.y, stPos.x, stPos.y, size.x, size.y,
		data[imgNo].handle, isTrans
	);
	return err; //-1: DrawRectGraph�G���[.
}
//DrawExtendGraph�̉�����.
int DrawImgST::DrawExtendGraphST(INT_XY pos, DBL_XY sizeRate, Anchor anc, BOOL isTrans) {

	//�n�_�����߂�.
	float x1 = (float)(pos.x - (data.size.x-1) * anchorPos[anc].x * sizeRate.x);
	float y1 = (float)(pos.y - (data.size.y-1) * anchorPos[anc].y * sizeRate.y);
	//�I�_�����߂�.
	float x2 = (float)(pos.x + (data.size.x-1) * (1-anchorPos[anc].x) * sizeRate.x);
	float y2 = (float)(pos.y + (data.size.y-1) * (1-anchorPos[anc].y) * sizeRate.y);

	int err = DrawExtendGraph(_int(x1), _int(y1), _int(x2), _int(y2), data.handle, isTrans);
	return err; //-1: DrawExtendGraph�G���[.
}
int DrawDivImgST::DrawExtendGraphST(int imgNo, INT_XY pos, DBL_XY sizeRate, Anchor anc, BOOL isTrans) {

	//�n�_�����߂�.
	float x1 = (float)(pos.x - (data[imgNo].size.x-1) * anchorPos[anc].x * sizeRate.x);
	float y1 = (float)(pos.y - (data[imgNo].size.y-1) * anchorPos[anc].y * sizeRate.y);
	//�I�_�����߂�.
	float x2 = (float)(pos.x + (data[imgNo].size.x-1) * (1-anchorPos[anc].x) * sizeRate.x);
	float y2 = (float)(pos.y + (data[imgNo].size.y-1) * (1-anchorPos[anc].y) * sizeRate.y);

	int err = DrawExtendGraph(_int(x1), _int(y1), _int(x2), _int(y2), data[imgNo].handle, isTrans);
	return err; //-1: DrawExtendGraph�G���[.
}
//DrawRotaGraph�̉�����.
int DrawImgST::DrawRotaGraphST(INT_XY pos, double extend, double ang, Anchor anc, BOOL isTrans) {

	//��_�ɍ��W�����炷.
	float x = (float)(pos.x - (data.size.x-1) * anchorPos[anc].x);
	float y = (float)(pos.y - (data.size.y-1) * anchorPos[anc].y);

	if (data.handle == 0) {
		return -2; //-2: handle���ݒ�.
	}
	int err = DrawRotaGraph(_int(x), _int(y),extend, ang, data.handle, isTrans);
	return err; //-1: DrawRotaGraph�G���[.
}
int DrawDivImgST::DrawRotaGraphST(int imgNo, INT_XY pos, double extend, double ang, Anchor anc, BOOL isTrans) {

	//��_�ɍ��W�����炷.
	float x = (float)(pos.x - (data[imgNo].size.x-1) * anchorPos[anc].x);
	float y = (float)(pos.y - (data[imgNo].size.y-1) * anchorPos[anc].y);

	if (data[imgNo].handle == 0) {
		return -2; //-2: handle���ݒ�.
	}
	int err = DrawRotaGraph(_int(x), _int(y),extend, ang, data[imgNo].handle, isTrans);
	return err; //-1: DrawRotaGraph�G���[.
}

//DrawString�̉�����.
int DrawStrST::DrawStringST(Anchor anc, int font) {
	
	//��_�ɍ��W�����炷.
	float x = (float)(data.pos.x - (GetTextSize(data.text, font).x-1) * anchorPos[anc].x);
	float y = (float)(data.pos.y - (GetTextSize(data.text, font).y-1) * anchorPos[anc].y);

	//�f�t�H���g�t�H���g.
	if (font < 0) {
		int err = DrawString(_int(x), _int(y), data.text.c_str(), data.clr);
		if (err < 0) {
			return -1; //-1: DrawString�ŃG���[.
		}
	}
	//�t�H���g�ݒ肠��.
	else {
		int err = DrawStringToHandle(_int(x), _int(y), data.text.c_str(), data.clr, font);
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
			data.pos.x, data.pos.y, extend.x, extend.y, pivot.x, pivot.y,
			rad, data.clr, 0, isVertical, data.text.c_str()
		);
		if (err < 0) {
			return -1; //-1: DrawRotaString�ŃG���[.
		}
	}
	//�t�H���g�ݒ肠��.
	else {
		int err = DrawRotaStringToHandle(
			data.pos.x, data.pos.y, extend.x, extend.y, pivot.x, pivot.y,
			rad, data.clr, font, 0, isVertical, data.text.c_str()
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
			data.clr, 0, isVertical, data.text.c_str()
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
			data.clr, font, 0, isVertical, data.text.c_str()
		);
		if (err < 0) {
			return -2; //-2: DrawModiStringToHandle�ŃG���[.
		}
	}
	return 0; //����I��.
}

//�e�L�X�g�̃T�C�Y�擾.
INT_XY DrawStrST::GetTextSize(MY_STRING str, int font) {
	
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