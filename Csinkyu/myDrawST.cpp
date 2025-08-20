/*
   - myDrawST.cpp - (original)
   ver.2025/08/20
   
   DxLib: �I���W�i���`��@�\�̒ǉ�.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx���ɓ����ĂȂ���΂����œ���.
#endif
#include "myDrawST.h"

/*
   [�I�_�̒���]

   DrawBox, DrawLine, DrawExtendGraph�Ȃǂ̏I�_��ݒ肷����̂�
   �n�_����I�_-1�܂ŕ`�悳���d�l(���̕��������I���ƍ�҂͔��f��������)

   ��: DrawBox(1, 1, 5, 5, color, FALSE)�Ƃ����ꍇ

   �@�P�Q�R�S�T
   �P��������
   �Q���@�@��
   �R���@�@��
   �S��������
   �T
*/

//�A���J�[���W.
static const DBL_XY anchorPos[9] = {
	{0.0, 0.0}, {0.5, 0.0}, {1.0, 0.0},
	{0.0, 0.5}, {0.5, 0.5}, {1.0, 0.5},
	{0.0, 1.0}, {0.5, 1.0}, {1.0, 1.0}
};

// ��*---=[ DrawImgST / DrawDivImgST ]=---*�� //

//LoadGraph�̉�����.
int DrawImgST::LoadGraphST(MY_STRING fileName) {

	//�摜�ǂݍ���.
	data.handle = LoadGraph(fileName.c_str());
	int err = GetGraphSize(data.handle, &data.size.x, &data.size.y);
	
	_return(-1, data.handle < 0) //-1: LoadGraph�G���[.
	_return(-2, err < 0)         //-2: GetGraphSize�G���[.
	return 0;                    // 0: ����I��.
}
//LoadDivGraph�̉�����.
int DrawDivImgST::LoadDivGraphST(MY_STRING fileName, INT_XY size, INT_XY cnt) {

	int* pHandle = new int[cnt.x*cnt.y]; //LoadDivGraph����n���h�����o���p.

	//�摜�����ǂݍ���.
	int err = LoadDivGraph(fileName.c_str(), cnt.x*cnt.y, cnt.x, cnt.y, size.x, size.y, pHandle);
	_return(-1, err < 0) //-1: LoadDivGraph�G���[.
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
int DrawImgST::DrawGraphST(DBL_XY pos, Anchor anc, bool isTrans, bool isFloat) {

	_return(-3, data.handle == 0) //-3: handle���ݒ�.

	//float�^���ǂ���.
	if (isFloat) {
		//��_�ɍ��W�����炷.
		float x = (float)(pos.x - (data.size.x) * anchorPos[anc].x);
		float y = (float)(pos.y - (data.size.y) * anchorPos[anc].y);
		//�`��.
		int err = DrawGraphF(x, y, data.handle, isTrans);
		_return(-1, err < 0) //-1: DrawGraphF�G���[.
	}
	else {
		//��_�ɍ��W�����炷.
		int x = (int)(pos.x - (data.size.x-1) * anchorPos[anc].x);
		int y = (int)(pos.y - (data.size.y-1) * anchorPos[anc].y);
		//�`��.
		int err = DrawGraph(x, y, data.handle, isTrans);
		_return(-2, err < 0) //-2: DrawGraph�G���[.
	}
	return 0; //����I��.
}
int DrawDivImgST::DrawGraphST(int imgNo, DBL_XY pos, Anchor anc, bool isTrans, bool isFloat) {

	_return(-3, data[imgNo].handle == 0) //-3: handle���ݒ�.

	//float�^���ǂ���.
	if (isFloat) {
		//��_�ɍ��W�����炷.
		float x = (float)(pos.x - (data[imgNo].size.x) * anchorPos[anc].x);
		float y = (float)(pos.y - (data[imgNo].size.y) * anchorPos[anc].y);
		//�`��.
		int err = DrawGraphF(x, y, data[imgNo].handle, isTrans);
		_return(-1, err < 0) //-1: DrawGraphF�G���[.
	}
	else {
		//��_�ɍ��W�����炷.
		int x = (int)(pos.x - (data[imgNo].size.x-1) * anchorPos[anc].x);
		int y = (int)(pos.y - (data[imgNo].size.y-1) * anchorPos[anc].y);
		//�`��.
		int err = DrawGraph(x, y, data[imgNo].handle, isTrans);
		_return(-2, err < 0) //-2: DrawGraph�G���[.
	}
	return 0; //����I��.
}

//DrawRectGraph�̉�����.
//Rect = ��`(�����`�Ⓑ���`�̂���)
int DrawImgST::DrawRectGraphST(DBL_XY pos, INT_XY stPixel, INT_XY size, bool isTrans, bool isFloat) {

	_return(-3, data.handle == 0) //-3: handle���ݒ�.

	//float�^���ǂ���.
	if (isFloat) {
		int err = DrawRectGraphF(
			(float)pos.x, (float)pos.y,	stPixel.x, stPixel.y, size.x, size.y, data.handle, isTrans
		);
		_return(-1, err < 0) //-1: DrawRectGraphF�G���[.
	}
	else {
		int err = DrawRectGraph(
			_int(pos.x), _int(pos.y), stPixel.x, stPixel.y, size.x, size.y, data.handle, isTrans
		);
		_return(-2, err < 0) //-2: DrawRectGraph�G���[.
	}
	return 0; //����I��.
}
int DrawDivImgST::DrawRectGraphST(int imgNo, DBL_XY pos, INT_XY stPixel, INT_XY size, bool isTrans, bool isFloat) {

	_return(-3, data[imgNo].handle == 0) //-3: handle���ݒ�.

	//float�^���ǂ���.
	if (isFloat) {
		int err = DrawRectGraphF(
			(float)pos.x, (float)pos.y,	stPixel.x, stPixel.y, size.x, size.y, data[imgNo].handle, isTrans
		);
		_return(-1, err < 0) //-1: DrawRectGraphF�G���[.
	}
	else {
		int err = DrawRectGraph(
			_int(pos.x), _int(pos.y), stPixel.x, stPixel.y, size.x, size.y, data[imgNo].handle, isTrans
		);
		_return(-2, err < 0) //-2: DrawRectGraph�G���[.
	}
	return 0; //����I��.
}

//DrawExtendGraph�̉�����.
int DrawImgST::DrawExtendGraphST(DBL_XY pos, DBL_XY sizeRate, Anchor anc, bool isTrans, bool isFloat) {

	_return(-3, data.handle == 0) //-3: handle���ݒ�.

	//float�^���ǂ���.
	if (isFloat) {
		//�n�_�����߂�.
		float x1 = (float)(pos.x - (data.size.x * sizeRate.x) * anchorPos[anc].x);
		float y1 = (float)(pos.y - (data.size.y * sizeRate.y) * anchorPos[anc].y);
		//�I�_�����߂�.
		float x2 = (float)(x1 + data.size.x * sizeRate.x);
		float y2 = (float)(y1 + data.size.y * sizeRate.y);

		int err = DrawExtendGraphF(x1, y1, x2+1, y2+1, data.handle, isTrans);
		_return(-1, err < 0) //-1: DrawExtendGraphF�G���[.
	}
	else {
		//�n�_�����߂�.
		int x1 = (int)(pos.x - ((data.size.x * sizeRate.x)-1) * anchorPos[anc].x);
		int y1 = (int)(pos.y - ((data.size.y * sizeRate.y)-1) * anchorPos[anc].y);
		//�I�_�����߂�.
		int x2 = (int)(x1 + ((data.size.x * sizeRate.x)-1));
		int y2 = (int)(y1 + ((data.size.y * sizeRate.y)-1));

		int err = DrawExtendGraph(x1, y1, x2+1, y2+1, data.handle, isTrans);
		_return(-2, err < 0) //-2: DrawExtendGraph�G���[.
	}
	return 0; //����I��.
}
int DrawDivImgST::DrawExtendGraphST(int imgNo, DBL_XY pos, DBL_XY sizeRate, Anchor anc, bool isTrans, bool isFloat) {

	_return(-3, data[imgNo].handle == 0) //-3: handle���ݒ�.

	//float�^���ǂ���.
	if (isFloat) {
		//�n�_�����߂�.
		float x1 = (float)(pos.x - (data[imgNo].size.x * sizeRate.x) * anchorPos[anc].x);
		float y1 = (float)(pos.y - (data[imgNo].size.y * sizeRate.y) * anchorPos[anc].y);
		//�I�_�����߂�.
		float x2 = (float)(x1 + data[imgNo].size.x * sizeRate.x);
		float y2 = (float)(y1 + data[imgNo].size.y * sizeRate.y);

		int err = DrawExtendGraphF(x1, y1, x2+1, y2+1, data[imgNo].handle, isTrans);
		_return(-1, err < 0) //-1: DrawExtendGraphF�G���[.
	}
	else {
		//�n�_�����߂�.
		int x1 = (int)(pos.x - ((data[imgNo].size.x * sizeRate.x)-1) * anchorPos[anc].x);
		int y1 = (int)(pos.y - ((data[imgNo].size.y * sizeRate.y)-1) * anchorPos[anc].y);
		//�I�_�����߂�.
		int x2 = (int)(x1 + ((data[imgNo].size.x * sizeRate.x)-1));
		int y2 = (int)(y1 + ((data[imgNo].size.y * sizeRate.y)-1));

		int err = DrawExtendGraph(x1, y1, x2+1, y2+1, data[imgNo].handle, isTrans);
		_return(-2, err < 0) //-2: DrawExtendGraph�G���[.
	}
	return 0; //����I��.
}

//DrawRotaGraph�̉�����.
int DrawImgST::DrawRotaGraphST(DBL_XY pos, double extend, double ang, Anchor anc, bool isTrans, bool isFloat) {

	_return(-3, data.handle == 0) //-3: handle���ݒ�.

	//float�^���ǂ���.
	if (isFloat) {
		//��_�ɍ��W�����炷.
		float x = (float)(pos.x - (data.size.x-1) * anchorPos[anc].x);
		float y = (float)(pos.y - (data.size.y-1) * anchorPos[anc].y);
	
		int err = DrawRotaGraphF(x, y, extend, ang, data.handle, isTrans);
		_return(-1, err < 0) //-1: DrawRotaGraphF�G���[.
	}
	else {
		//��_�ɍ��W�����炷.
		int x = (int)(pos.x - (data.size.x-1) * anchorPos[anc].x);
		int y = (int)(pos.y - (data.size.y-1) * anchorPos[anc].y);
	
		int err = DrawRotaGraph(x, y, extend, ang, data.handle, isTrans);
		_return(-2, err < 0) //-2: DrawRotaGraph�G���[.
	}
	return 0; //����I��.
}
int DrawDivImgST::DrawRotaGraphST(int imgNo, DBL_XY pos, double extend, double ang, Anchor anc, bool isTrans, bool isFloat) {

	_return(-3, data[imgNo].handle == 0) //-3: handle���ݒ�.

	//float�^���ǂ���.
	if (isFloat) {
		//��_�ɍ��W�����炷.
		float x = (float)(pos.x - (data[imgNo].size.x-1) * anchorPos[anc].x);
		float y = (float)(pos.y - (data[imgNo].size.y-1) * anchorPos[anc].y);
	
		int err = DrawRotaGraphF(x, y, extend, ang, data[imgNo].handle, isTrans);
		_return(-1, err < 0) //-1: DrawRotaGraphF�G���[.
	}
	else {
		//��_�ɍ��W�����炷.
		int x = (int)(pos.x - (data[imgNo].size.x-1) * anchorPos[anc].x);
		int y = (int)(pos.y - (data[imgNo].size.y-1) * anchorPos[anc].y);
	
		int err = DrawRotaGraph(x, y, extend, ang, data[imgNo].handle, isTrans);
		_return(-2, err < 0) //-2: DrawRotaGraph�G���[.
	}
	return 0; //����I��.
}

//DrawModiGraph�̉�����.
int DrawImgST::DrawModiGraphST(DBL_XY luPos, DBL_XY ruPos, DBL_XY rdPos, DBL_XY ldPos, bool isTrans, bool isFloat) {
	
	_return(-3, data.handle == 0) //-3: handle���ݒ�.

	//float�^���ǂ���.
	if (isFloat) {
		int err = DrawModiGraphF(
			(float)luPos.x, (float)luPos.y, (float)ruPos.x, (float)ruPos.y, 
			(float)rdPos.x, (float)rdPos.y, (float)ldPos.x, (float)ldPos.y, data.handle, isTrans
		);
		_return(-1, err < 0) //-1: DrawModiGraphF�G���[.
	}
	else {
		int err = DrawModiGraph(
			_int(luPos.x), _int(luPos.y), _int(ruPos.x), _int(ruPos.y),
			_int(rdPos.x), _int(rdPos.y), _int(ldPos.x), _int(ldPos.y), data.handle, isTrans
		);
		_return(-2, err < 0) //-2: DrawModiGraph�G���[.
	}
	return 0; //����I��.
}
int DrawDivImgST::DrawModiGraphST(int imgNo, DBL_XY luPos, DBL_XY ruPos, DBL_XY rdPos, DBL_XY ldPos, bool isTrans, bool isFloat) {

	_return(-3, data[imgNo].handle == 0) //-3: handle���ݒ�.

	//float�^���ǂ���.
	if (isFloat) {
		int err = DrawModiGraphF(
			(float)luPos.x, (float)luPos.y, (float)ruPos.x, (float)ruPos.y, 
			(float)rdPos.x, (float)rdPos.y, (float)ldPos.x, (float)ldPos.y, data[imgNo].handle, isTrans
		);
		_return(-1, err < 0) //-1: DrawModiGraphF�G���[.
	}
	else {
		int err = DrawModiGraph(
			_int(luPos.x), _int(luPos.y), _int(ruPos.x), _int(ruPos.y),
			_int(rdPos.x), _int(rdPos.y), _int(ldPos.x), _int(ldPos.y), data[imgNo].handle, isTrans
		);
		_return(-2, err < 0) //-2: DrawModiGraph�G���[.
	}
	return 0; //����I��.
}

//DrawString�̉�����.
int DrawStrST::DrawStringST(Anchor anc, int font) {
	
	//��_�ɍ��W�����炷.
	float x = (float)(data.pos.x - (GetTextSize(data.text, font).x-1) * anchorPos[anc].x);
	float y = (float)(data.pos.y - (GetTextSize(data.text, font).y-1) * anchorPos[anc].y);

	//�f�t�H���g�t�H���g.
	if (font < 0) {
		int err = DrawString((int)x, (int)y, data.text.c_str(), data.color);
		_return(-1, err < 0) //-1: DrawString�G���[.
	}
	//�t�H���g�ݒ肠��.
	else {
		int err = DrawStringToHandle((int)x, (int)y, data.text.c_str(), data.color, font);
		_return(-2, err < 0) //-2: DrawStringToHandle�G���[.
	}
	return 0; //����I��.
}
//DrawRotaString�̉�����.
int DrawStrST::DrawRotaStringST(INT_XY extend, INT_XY pivot, double ang, bool isVertical, int font) {

	double rad = M_PI/180 * ang; //�p�x�����W�A���ɕϊ�.

	//�f�t�H���g�t�H���g.
	if (font < 0) {
		int err = DrawRotaString(
			data.pos.x, data.pos.y, extend.x, extend.y, pivot.x, pivot.y,
			rad, data.color, 0, isVertical, data.text.c_str()
		);
		_return(-1, err < 0) //-1: DrawRotaString�G���[.
	}
	//�t�H���g�ݒ肠��.
	else {
		int err = DrawRotaStringToHandle(
			data.pos.x, data.pos.y, extend.x, extend.y, pivot.x, pivot.y,
			rad, data.color, font, 0, isVertical, data.text.c_str()
		);
		_return(-2, err < 0) //-2 DrawRotaStringToHandle�G���[.
	}
	return 0; //����I��.
}
//DrawModiString�̉�����.
int DrawStrST::DrawModiStringST(INT_XY luPos, INT_XY ruPos, INT_XY rdPos, INT_XY ldPos, bool isVertical, int font) {

	//�f�t�H���g�t�H���g.
	if (font < 0) {
		int err = DrawModiString(
			luPos.x, luPos.y, ruPos.x, ruPos.y,
			rdPos.x, rdPos.y, ldPos.x, ldPos.y,
			data.color, 0, isVertical, data.text.c_str()
		);
		_return(-1, err < 0) //-1: DrawModiString�G���[.
	}
	//�t�H���g�ݒ肠��.
	else {
		int err = DrawModiStringToHandle(
			luPos.x, luPos.y, ruPos.x, ruPos.y,
			rdPos.x, rdPos.y, ldPos.x, ldPos.y,
			data.color, font, 0, isVertical, data.text.c_str()
		);
		_return(-2, err < 0) //-2: DrawModiStringToHandle�G���[.
	}
	return 0; //����I��.
}

//�e�L�X�g�̃T�C�Y�擾.
INT_XY DrawStrST::GetTextSize(MY_STRING str, int font) {
	
	INT_XY size{};

	TCHAR name[256]{}; //����.
	int   line{};      //����.
	int   thick{};     //����.

	//�f�t�H���g�t�H���g.
	if (font < 0) {
		GetDrawStringSize(&size.x, &size.y, &line, str.c_str(), 255);
	}
	//�t�H���g�ݒ肠��.
	else {
		GetDrawStringSizeToHandle(&size.x, &size.y, &line, str.c_str(), 255, font);
		GetFontStateToHandle(name, &size.y, &thick, font); //size.y�̓t�H���g����擾.
	}

	return size;
}

// ��*---=[ function ]=---*�� //

//DrawCircle�̉�����.
int DrawCircleST(const Circle* data, bool isFill, bool isAnti, float thick) {

	//�A���`�G�C���A�X����.
	if (isAnti) {
		//posnum(�p�`��)��60�ɐݒ肷��.
		int err = DrawCircleAA((float)data->pos.x, (float)data->pos.y, data->r, 60, data->color, isFill, thick);
		_return(-1, err < 0) //-1: DrawCircleAA�G���[.
	}
	//�A���`�G�C���A�X�Ȃ�.
	else{
		int err = DrawCircle(_int(data->pos.x), _int(data->pos.y), _int(data->r), data->color, isFill, (int)thick);
		_return(-2, err < 0) //-2: DrawCircle�G���[.
	}
	return 0; //����I��.
}
//DrawBox�̉�����.
int DrawBoxST(const Box* data, Anchor anc, bool isFill, bool isAnti) {

	_return(-3, data->size.x <= 0.0 || data->size.y <= 0.0) //-3: �T�C�Y��0.0�ȉ�.

	//�n�_�����߂�.
	float x1 = (float)(data->pos.x - (data->size.x-1) * anchorPos[anc].x);
	float y1 = (float)(data->pos.y - (data->size.y-1) * anchorPos[anc].y);
	//�I�_�����߂�.
	float x2 = (float)(x1 + data->size.x-1);
	float y2 = (float)(y1 + data->size.y-1);

	//�A���`�G�C���A�X����.
	if (isAnti) {
		int err = DrawBoxAA(x1, y1, x2+1, y2+1, data->color, isFill);
		_return(-1, err < 0) //-1: DrawBoxAA�G���[.
	}
	//�A���`�G�C���A�X�Ȃ�.
	else {
		int err = DrawBox((int)x1, (int)y1, (int)x2+1, (int)y2+1, data->color, isFill);
		_return(-2, err < 0) //-2: DrawBox�G���[.
	}
	return 0; //����I��.
}
//DrawTriangle�̉�����.
int DrawTriangleST(const Triangle* data, bool isFill, bool isAnti) {

	//�A���`�G�C���A�X����.
	if (isAnti) {
		int err = DrawTriangleAA(
			(float)data->pos[0].x, (float)data->pos[0].y,
			(float)data->pos[1].x, (float)data->pos[1].y,
			(float)data->pos[2].x, (float)data->pos[2].y, data->color, isFill
		);
		_return(-1, err < 0) //-1: DrawTriangleAA�G���[.
	}
	//�A���`�G�C���A�X�Ȃ�.
	else {
		int err = DrawTriangle(
			_int(data->pos[0].x), _int(data->pos[0].y),
			_int(data->pos[1].x), _int(data->pos[1].y),
			_int(data->pos[2].x), _int(data->pos[2].y), data->color, isFill
		);
		_return(-2, err < 0) //-2: DrawTriangle�G���[.
	}
	return 0; //����I��.
}
//DrawLine�̉�����.
int DrawLineST(const Line* data, bool isAnti, float thick) {

	//�A���`�G�C���A�X����.
	if (isAnti) {
		int err = DrawLineAA(
			(float)data->stPos.x, (float)data->stPos.y,
			(float)data->edPos.x, (float)data->edPos.y, data->color, thick
		);
		_return(-1, err < 0) //-1: DrawLineAA�G���[.
	}
	//�A���`�G�C���A�X�Ȃ�.
	else {
		int err = DrawLine(
			_int(data->stPos.x), _int(data->stPos.y), 
			_int(data->edPos.x), _int(data->edPos.y), data->color, (int)thick
		);
		_return(-2, err < 0) //-2: DrawLine�G���[.
	}
	return 0; //����I��.
}
//��ʑS�̂ɃO���b�h����`��.
int DrawWindowGrid(int wid, int hei, int size, UINT clrWid, UINT clrHei) {

	//�c���̕`��.
	for (int x = 0; x < wid; x += size) {

		Line line = { {(double)x, 0}, {(double)x, (double)hei}, clrHei };
		int err = DrawLineST(&line);
		_return(-1, err < 0) //-1: �c���ŃG���[.
	}
	//�����̕`��.
	for (int y = 0; y < hei; y += size) {

		Line line = { {0, (double)y}, {(double)wid, (double)y}, clrWid };
		int err = DrawLineST(&line);
		_return(-2, err < 0) //-2: �����ŃG���[.
	}
	return 0; //����I��.
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