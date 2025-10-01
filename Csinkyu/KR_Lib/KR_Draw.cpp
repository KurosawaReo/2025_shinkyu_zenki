/*
   - KR_Draw.cpp - (DxLib)
   ver: 2025/10/02

   �`��@�\��ǉ����܂��B
   (�I�u�W�F�N�g�w��ver �� KR_Object)
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.h�ɓ����ĂȂ���΂����œ���.
  #include "KR_Calc.h"
#endif
#include "KR_Draw.h"

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

   [�T�C�Y��-1�ɂ���]
   �摜��e�L�X�g�̕`��ŁA�����ŃT�C�Y��-1���Ă���B
   -1���K�v���ǂ����͔Y�܂������A���ꂪ�Ȃ��Ɖ摜���^�C���̂悤�ɕ��ׂ����ɂ��ꂪ�N����B
*/

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	constexpr int NONE_HANDLE = -1; //�n���h���Ȃ�.

	//�A���J�[���W.
	static const DBL_XY ANCHOR_POS[9] = {
		{0.0, 0.0}, {0.5, 0.0}, {1.0, 0.0},
		{0.0, 0.5}, {0.5, 0.5}, {1.0, 0.5},
		{0.0, 1.0}, {0.5, 1.0}, {1.0, 1.0}
	};

// ��*---=[ DrawImgST / DrawDivImgST ]=---*�� //

	//constructor, destructor.
	DrawImg::DrawImg() {
		data.handle = NONE_HANDLE;
	}
	DrawImg::~DrawImg() {
		DeleteGraph(data.handle); //�摜���.
	}

	//constructor, destructor.
	DrawDivImg::DrawDivImg() {
		for (auto& i : data) {
			i.handle = NONE_HANDLE;
		}
	}
	DrawDivImg::~DrawDivImg() {
		for (auto& i : data) {
			DeleteGraph(i.handle); //�摜���.
		}
	}

	//LoadGraph�̉�����.
	int DrawImg::LoadFile(MY_STRING fileName) {

		//�ߋ��ɓǂݍ��񂾉摜�͉��.
		if (data.handle != NONE_HANDLE) {
			DeleteGraph(data.handle); //�摜���.
			data.handle = NONE_HANDLE;
		}
		//�摜�ǂݍ���.
		data.handle = LoadGraph(fileName.c_str());
		int err = GetGraphSize(data.handle, &data.size.x, &data.size.y);
	
		_return(-1, data.handle < 0) //-1: LoadGraph�G���[.
		_return(-2, err < 0)         //-2: GetGraphSize�G���[.
		return 0;                    // 0: ����I��.
	}
	//LoadDivGraph�̉�����.
	int DrawDivImg::LoadFile(MY_STRING fileName, INT_XY size, INT_XY cnt) {

		//�ߋ��ɓǂݍ��񂾉摜�͉��.
		for (auto& i : data) {
			DeleteGraph(i.handle); //�摜���.
			i.handle = NONE_HANDLE;
		}

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
	int DrawImg::Draw(DBL_XY pos, Anchor anc, bool isTrans, bool isFloat) {

		_return(-3, data.handle == NONE_HANDLE) //-3: handle���ݒ�.

		//float�^���ǂ���.
		if (isFloat) {
			//��_�ɍ��W�����炷.
			float x = _flt(pos.x - (data.size.x) * ANCHOR_POS[anc].x);
			float y = _flt(pos.y - (data.size.y) * ANCHOR_POS[anc].y);
			//�`��.
			int err = DrawGraphF(x, y, data.handle, isTrans);
			_return(-1, err < 0) //-1: DrawGraphF�G���[.
		}
		else {
			//��_�ɍ��W�����炷.
			int x = _int(pos.x - (data.size.x-1) * ANCHOR_POS[anc].x);
			int y = _int(pos.y - (data.size.y-1) * ANCHOR_POS[anc].y);
			//�`��.
			int err = DrawGraph(x, y, data.handle, isTrans);
			_return(-2, err < 0) //-2: DrawGraph�G���[.
		}
		return 0; //����I��.
	}
	int DrawDivImg::Draw(int imgNo, DBL_XY pos, Anchor anc, bool isTrans, bool isFloat) {

		_return(-3, data[imgNo].handle == NONE_HANDLE) //-3: handle���ݒ�.

		//float�^���ǂ���.
		if (isFloat) {
			//��_�ɍ��W�����炷.
			float x = _flt(pos.x - (data[imgNo].size.x) * ANCHOR_POS[anc].x);
			float y = _flt(pos.y - (data[imgNo].size.y) * ANCHOR_POS[anc].y);
			//�`��.
			int err = DrawGraphF(x, y, data[imgNo].handle, isTrans);
			_return(-1, err < 0) //-1: DrawGraphF�G���[.
		}
		else {
			//��_�ɍ��W�����炷.
			int x = _int(pos.x - (data[imgNo].size.x-1) * ANCHOR_POS[anc].x);
			int y = _int(pos.y - (data[imgNo].size.y-1) * ANCHOR_POS[anc].y);
			//�`��.
			int err = DrawGraph(x, y, data[imgNo].handle, isTrans);
			_return(-2, err < 0) //-2: DrawGraph�G���[.
		}
		return 0; //����I��.
	}

	//DrawRectGraph�̉�����.
	//Rect = ��`(�����`�Ⓑ���`�̂���)
	int DrawImg::DrawRect(DBL_XY pos, int left, int up, int right, int down, Anchor anc, bool isTrans, bool isFloat) {

		_return(-3, data.handle == NONE_HANDLE) //-3: handle���ݒ�.

		//�A���J�[���܂߂��`����W.
		DBL_XY drawPos = {
			pos.x - data.size.x * ANCHOR_POS[anc].x,
			pos.y - data.size.y * ANCHOR_POS[anc].y
		};
		//�摜�̋�`.
		INT_XY stPxl = {0, 0};
		INT_XY size  = data.size;

		//�N���b�s���O(�摜�̐؂��菈��)
		if (drawPos.x < left) {
			stPxl.x += _int(left - drawPos.x);
			size.x  -= _int(left - drawPos.x);
			drawPos.x = left;
		}
		if (drawPos.y < up) {
			stPxl.y += _int(up - drawPos.y);
			size.y  -= _int(up - drawPos.y);
			drawPos.y = up;
		}
		if (drawPos.x + size.x > right) {
			size.x -= _int((drawPos.x + size.x) - right);
		}
		if (drawPos.y + size.y > down) {
			size.y -= _int((drawPos.y + size.y) - down);
		}

		//�`�悷��͈͂�����Ȃ�`��.
		if (size.x > 0 && size.y > 0) {
			if (isFloat) {
				int err = DrawRectGraphF(_flt(drawPos.x), _flt(drawPos.y), stPxl.x, stPxl.y, size.x, size.y, data.handle, isTrans);
				_return(-1, err < 0) //-1: DrawRectGraphF�G���[.
			}
			else {
				int err = DrawRectGraph(_int(drawPos.x), _int(drawPos.y), stPxl.x, stPxl.y, size.x, size.y, data.handle, isTrans);
				_return(-2, err < 0) //-2: DrawRectGraph�G���[.
			}
		}

		return 0; //����I��.
	}
	int DrawDivImg::DrawRect(int imgNo, DBL_XY pos, int left, int up, int right, int down, Anchor anc, bool isTrans, bool isFloat) {

		_return(-3, data[imgNo].handle == NONE_HANDLE) //-3: handle���ݒ�.

		//�\�[�X��`.
		INT_XY stPxl = {0, 0};           //�摜�̎n�_�s�N�Z��.
		INT_XY size  = data[imgNo].size; //�n�_����̃T�C�Y.

		//���ɂ͂ݏo�Ă�Ȃ�.
		if (pos.x < left) {
			stPxl.x -= _int_r(pos.x); //�\�[�X���E�ɂ��炷.
			size .x += _int_r(pos.x); //�`�敝�����炷(pos.x�͕��̒l�Ȃ̂ŉ��Z)
		}
		//��ɂ͂ݏo�Ă�Ȃ�.
		if (pos.y < up) {
			stPxl.y -= _int_r(pos.y);
			size .y += _int_r(pos.y);
		}
		//�E�ɂ͂ݏo�Ă�Ȃ�.
		if (pos.x + data[imgNo].size.x * ANCHOR_POS[anc].x > right) {
			size.x = _int_r((right - pos.x) * ANCHOR_POS[anc].x); //�������.
		}
		//���ɂ͂ݏo�Ă�Ȃ�.
		if (pos.y + data[imgNo].size.y * ANCHOR_POS[anc].y > down) {
			size.y = _int_r((down - pos.y) * ANCHOR_POS[anc].y); //�������.
		}
		//�`�悷��͈͂�����Ȃ�.
		if (size.x > 0 && size.y > 0) {
			//float�^���ǂ���.
			if (isFloat) {
				//��_�ɍ��W�����炷.
				float x = _flt(pos.x - (data[imgNo].size.x) * ANCHOR_POS[anc].x);
				float y = _flt(pos.y - (data[imgNo].size.y) * ANCHOR_POS[anc].y);
				//�`��.
				int err = DrawRectGraphF(
					x, y, stPxl.x, stPxl.y, size.x, size.y, data[imgNo].handle, isTrans
				);
				_return(-1, err < 0) //-1: DrawRectGraphF�G���[.
			}
			else {
				//��_�ɍ��W�����炷.
				int x = _int(pos.x - (data[imgNo].size.x-1) * ANCHOR_POS[anc].x);
				int y = _int(pos.y - (data[imgNo].size.y-1) * ANCHOR_POS[anc].y);
				//�`��.
				int err = DrawRectGraph(
					_int_r(pos.x), _int_r(pos.y), stPxl.x, stPxl.y, size.x, size.y, data[imgNo].handle, isTrans
				);
				_return(-2, err < 0) //-2: DrawRectGraph�G���[.
			}
		}
		return 0; //����I��.
	}

	//DrawExtendGraph�̉�����.
	int DrawImg::DrawExtend(DBL_XY pos, DBL_XY sizeRate, Anchor anc, bool isTrans, bool isFloat) {

		_return(-3, data.handle == NONE_HANDLE) //-3: handle���ݒ�.

		//float�^���ǂ���.
		if (isFloat) {
			//�n�_�����߂�.
			float x1 = _flt(pos.x - (data.size.x * sizeRate.x) * ANCHOR_POS[anc].x);
			float y1 = _flt(pos.y - (data.size.y * sizeRate.y) * ANCHOR_POS[anc].y);
			//�I�_�����߂�.
			float x2 = _flt(x1 + data.size.x * sizeRate.x);
			float y2 = _flt(y1 + data.size.y * sizeRate.y);

			int err = DrawExtendGraphF(x1, y1, x2+1, y2+1, data.handle, isTrans);
			_return(-1, err < 0) //-1: DrawExtendGraphF�G���[.
		}
		else {
			//�n�_�����߂�.
			int x1 = _int(pos.x - ((data.size.x * sizeRate.x)-1) * ANCHOR_POS[anc].x);
			int y1 = _int(pos.y - ((data.size.y * sizeRate.y)-1) * ANCHOR_POS[anc].y);
			//�I�_�����߂�.
			int x2 = _int(x1 + ((data.size.x * sizeRate.x)-1));
			int y2 = _int(y1 + ((data.size.y * sizeRate.y)-1));

			int err = DrawExtendGraph(x1, y1, x2+1, y2+1, data.handle, isTrans);
			_return(-2, err < 0) //-2: DrawExtendGraph�G���[.
		}
		return 0; //����I��.
	}
	int DrawDivImg::DrawExtend(int imgNo, DBL_XY pos, DBL_XY sizeRate, Anchor anc, bool isTrans, bool isFloat) {

		_return(-3, data[imgNo].handle == NONE_HANDLE) //-3: handle���ݒ�.

		//float�^���ǂ���.
		if (isFloat) {
			//�n�_�����߂�.
			float x1 = _flt(pos.x - (data[imgNo].size.x * sizeRate.x) * ANCHOR_POS[anc].x);
			float y1 = _flt(pos.y - (data[imgNo].size.y * sizeRate.y) * ANCHOR_POS[anc].y);
			//�I�_�����߂�.
			float x2 = _flt(x1 + data[imgNo].size.x * sizeRate.x);
			float y2 = _flt(y1 + data[imgNo].size.y * sizeRate.y);

			int err = DrawExtendGraphF(x1, y1, x2+1, y2+1, data[imgNo].handle, isTrans);
			_return(-1, err < 0) //-1: DrawExtendGraphF�G���[.
		}
		else {
			//�n�_�����߂�.
			int x1 = _int_r(pos.x - ((data[imgNo].size.x * sizeRate.x)-1) * ANCHOR_POS[anc].x);
			int y1 = _int_r(pos.y - ((data[imgNo].size.y * sizeRate.y)-1) * ANCHOR_POS[anc].y);
			//�I�_�����߂�.
			int x2 = _int_r(x1 + ((data[imgNo].size.x * sizeRate.x)-1));
			int y2 = _int_r(y1 + ((data[imgNo].size.y * sizeRate.y)-1));

			int err = DrawExtendGraph(x1, y1, x2+1, y2+1, data[imgNo].handle, isTrans);
			_return(-2, err < 0) //-2: DrawExtendGraph�G���[.
		}
		return 0; //����I��.
	}

	//DrawRotaGraph�̉�����.
	//DrawRotaGraph�̓f�t�H���g�Œ�����̂��߁A�A���J�[��-0.5����.
	int DrawImg::DrawRota(DBL_XY pos, double extend, double ang, INT_XY pivot, Anchor anc, bool isTrans, bool isFloat) {

		_return(-3, data.handle == NONE_HANDLE) //-3: handle���ݒ�.

		//float�^���ǂ���.
		if (isFloat) {
			//��_�ɍ��W�����炷.
			float x = _flt(pos.x - (data.size.x-1) * (ANCHOR_POS[anc].x-0.5));
			float y = _flt(pos.y - (data.size.y-1) * (ANCHOR_POS[anc].y-0.5));
			//pivot(�f�t�H���g�͉摜�̒��S)
			float px = _flt(data.size.x/2 + pivot.x);
			float py = _flt(data.size.y/2 + pivot.y);

			int err = DrawRotaGraph2F(x, y, px, py, extend, _rad(ang), data.handle, isTrans);
			_return(-1, err < 0) //-1: DrawRotaGraphF�G���[.
		}
		else {
			//��_�ɍ��W�����炷.
			int x = _int(pos.x - (data.size.x-1) * (ANCHOR_POS[anc].x-0.5));
			int y = _int(pos.y - (data.size.y-1) * (ANCHOR_POS[anc].y-0.5));
			//pivot(�f�t�H���g�͉摜�̒��S)
			int px = data.size.x/2 + pivot.x;
			int py = data.size.y/2 + pivot.y;
	
			int err = DrawRotaGraph2(x, y, px, py, extend, _rad(ang), data.handle, isTrans);
			_return(-2, err < 0) //-2: DrawRotaGraph�G���[.
		}
		return 0; //����I��.
	}
	int DrawDivImg::DrawRota(int imgNo, DBL_XY pos, double extend, double ang, INT_XY pivot, Anchor anc, bool isTrans, bool isFloat) {

		_return(-3, data[imgNo].handle == NONE_HANDLE) //-3: handle���ݒ�.

		//float�^���ǂ���.
		if (isFloat) {
			//��_�ɍ��W�����炷.
			float x = _flt(pos.x - (data[imgNo].size.x-1) * (ANCHOR_POS[anc].x-0.5));
			float y = _flt(pos.y - (data[imgNo].size.y-1) * (ANCHOR_POS[anc].y-0.5));
			//pivot(�f�t�H���g�͉摜�̒��S)
			float px = _flt(data[imgNo].size.x/2 + pivot.x);
			float py = _flt(data[imgNo].size.y/2 + pivot.y);

			int err = DrawRotaGraph2F(x, y, px, py, extend, _rad(ang), data[imgNo].handle, isTrans);
			_return(-1, err < 0) //-1: DrawRotaGraphF�G���[.
		}
		else {
			//��_�ɍ��W�����炷.
			int x = _int(pos.x - (data[imgNo].size.x-1) * (ANCHOR_POS[anc].x-0.5));
			int y = _int(pos.y - (data[imgNo].size.y-1) * (ANCHOR_POS[anc].y-0.5));
			//pivot(�f�t�H���g�͉摜�̒��S)
			int px = data[imgNo].size.x/2 + pivot.x;
			int py = data[imgNo].size.y/2 + pivot.y;
	
			int err = DrawRotaGraph2(x, y, px, py, extend, _rad(ang), data[imgNo].handle, isTrans);
			_return(-2, err < 0) //-2: DrawRotaGraph�G���[.
		}
		return 0; //����I��.
	}

	//DrawModiGraph�̉�����.
	int DrawImg::DrawModi(DBL_XY luPos, DBL_XY ruPos, DBL_XY rdPos, DBL_XY ldPos, bool isTrans, bool isFloat) {
	
		_return(-3, data.handle == NONE_HANDLE) //-3: handle���ݒ�.

		//float�^���ǂ���.
		if (isFloat) {
			int err = DrawModiGraphF(
				_flt(luPos.x), _flt(luPos.y), _flt(ruPos.x), _flt(ruPos.y), 
				_flt(rdPos.x), _flt(rdPos.y), _flt(ldPos.x), _flt(ldPos.y), data.handle, isTrans
			);
			_return(-1, err < 0) //-1: DrawModiGraphF�G���[.
		}
		else {
			int err = DrawModiGraph(
				_int_r(luPos.x), _int_r(luPos.y), _int_r(ruPos.x), _int_r(ruPos.y),
				_int_r(rdPos.x), _int_r(rdPos.y), _int_r(ldPos.x), _int_r(ldPos.y), data.handle, isTrans
			);
			_return(-2, err < 0) //-2: DrawModiGraph�G���[.
		}
		return 0; //����I��.
	}
	int DrawDivImg::DrawModi(int imgNo, DBL_XY luPos, DBL_XY ruPos, DBL_XY rdPos, DBL_XY ldPos, bool isTrans, bool isFloat) {

		_return(-3, data[imgNo].handle == NONE_HANDLE) //-3: handle���ݒ�.

		//float�^���ǂ���.
		if (isFloat) {
			int err = DrawModiGraphF(
				_flt(luPos.x), _flt(luPos.y), _flt(ruPos.x), _flt(ruPos.y),
				_flt(rdPos.x), _flt(rdPos.y), _flt(ldPos.x), _flt(ldPos.y), data[imgNo] .handle, isTrans
			);
			_return(-1, err < 0) //-1: DrawModiGraphF�G���[.
		}
		else {
			int err = DrawModiGraph(
				_int_r(luPos.x), _int_r(luPos.y), _int_r(ruPos.x), _int_r(ruPos.y),
				_int_r(rdPos.x), _int_r(rdPos.y), _int_r(ldPos.x), _int_r(ldPos.y), data[imgNo].handle, isTrans
			);
			_return(-2, err < 0) //-2: DrawModiGraph�G���[.
		}
		return 0; //����I��.
	}

// ��*---=[ DrawStr ]=---*�� //

	//DrawString�̉�����.
	int DrawStr::Draw(Anchor anc, int font) {
	
		//��_�ɍ��W�����炷.
		float x = _flt(pos.x - (GetTextSize(font).x-1) * ANCHOR_POS[anc].x);
		float y = _flt(pos.y - (GetTextSize(font).y-1) * ANCHOR_POS[anc].y);

		//�f�t�H���g�t�H���g.
		if (font < 0) {
			int err = DrawString(_int(x), _int(y), text.c_str(), color.GetColorCode());
			_return(-1, err < 0) //-1: DrawString�G���[.
		}
		//�t�H���g�ݒ肠��.
		else {
			int err = DrawStringToHandle(_int(x), _int(y), text.c_str(), color.GetColorCode(), font);
			_return(-2, err < 0) //-2: DrawStringToHandle�G���[.
		}
		return 0; //����I��.
	}
	//DrawRotaString�̉�����.
	int DrawStr::DrawRota(INT_XY extend, INT_XY pivot, double ang, bool isVertical, int font) {

		//�f�t�H���g�t�H���g.
		if (font < 0) {
			int err = DrawRotaString(
				pos.x, pos.y, extend.x, extend.y, pivot.x, pivot.y,
				_rad(ang), color.GetColorCode(), 0, isVertical, text.c_str()
			);
			_return(-1, err < 0) //-1: DrawRotaString�G���[.
		}
		//�t�H���g�ݒ肠��.
		else {
			int err = DrawRotaStringToHandle(
				pos.x, pos.y, extend.x, extend.y, pivot.x, pivot.y,
				_rad(ang), color.GetColorCode(), font, 0, isVertical, text.c_str()
			);
			_return(-2, err < 0) //-2 DrawRotaStringToHandle�G���[.
		}
		return 0; //����I��.
	}
	//DrawModiString�̉�����.
	int DrawStr::DrawModi(INT_XY luPos, INT_XY ruPos, INT_XY rdPos, INT_XY ldPos, bool isVertical, int font) {

		//�f�t�H���g�t�H���g.
		if (font < 0) {
			int err = DrawModiString(
				luPos.x, luPos.y, ruPos.x, ruPos.y,
				rdPos.x, rdPos.y, ldPos.x, ldPos.y,
				color.GetColorCode(), 0, isVertical, text.c_str()
			);
			_return(-1, err < 0) //-1: DrawModiString�G���[.
		}
		//�t�H���g�ݒ肠��.
		else {
			int err = DrawModiStringToHandle(
				luPos.x, luPos.y, ruPos.x, ruPos.y,
				rdPos.x, rdPos.y, ldPos.x, ldPos.y,
				color.GetColorCode(), font, 0, isVertical, text.c_str()
			);
			_return(-2, err < 0) //-2: DrawModiStringToHandle�G���[.
		}
		return 0; //����I��.
	}

	//�e�L�X�g�̃T�C�Y�擾.
	INT_XY DrawStr::GetTextSize(int font) {
	
		INT_XY size{};

		TCHAR name[256]{}; //����.
		int   line{};      //����.
		int   thick{};     //����.

		//�f�t�H���g�t�H���g.
		if (font < 0) {
			GetDrawStringSize(&size.x, &size.y, &line, text.c_str(), 255);
		}
		//�t�H���g�ݒ肠��.
		else {
			GetDrawStringSizeToHandle(&size.x, &size.y, &line, text.c_str(), 255, font);
			GetFontStateToHandle(name, &size.y, &thick, font); //size.y�̓t�H���g����擾.
		}

		return size;
	}

// ��*---=[ Font ]=---*�� //

	//constructor, destructor.
	Font::Font() {
		handle = NONE_HANDLE;
	}
	Font::~Font() {
		//�n���h���������.
		if (handle != NONE_HANDLE) {
			DeleteFontToHandle(handle); //���.
		}
	}
	//�t�H���g�쐬.
	void Font::CreateFontH(MY_STRING fontName, int size, int thick, FontTypeID fontId) {
		handle = CreateFontToHandle(fontName.c_str(), size, thick, _int(fontId));
	}

// ��*---=[ GradLine ]=---*�� //
	
	//���_�ǉ�.
	void GradLine::AddPoint(DBL_XY pos, MY_COLOR color) {

		VERTEX2D point;
		point.pos = VGet(_flt(pos.x), _flt(pos.y), 0); //VECTOR�^�ɂ��ēo�^.
		point.dif = color.GetColorU8();                //COLOR_U8�œo�^.
		point.rhw = 1.0f;                              //2D�ł͕s�v?
		point.u = point.v = 0.0f;                      //�e�N�X�`��UV�͎g��Ȃ�.

		points.push_back(point); //���_�ǉ�.
	}
	//�`��.
	void GradLine::Draw(bool isClose) {

		//���_�̐�.
		int count = _int((isClose) ? points.size()+1 : points.size());
		//���_�z��.
		vector<VERTEX2D> tmp(count);

		//���_�f�[�^���R�s�[.
		for (int i = 0; i < points.size(); i++) {
			tmp[i] = points[i];
		}
		if (isClose) {
			tmp[points.size()] = tmp[0]; //�I�_�Ɏn�_������.
		}

		//�`��.
		SetDrawBlendModeKR(BlendModeID::Alpha, 255); //���߂𔽉f�����邽�߂ɃA���t�@���[�h�ɂ���.
		DrawPrimitive2D(tmp.data(), count, DX_PRIMTYPE_LINESTRIP, DX_NONE_GRAPH, FALSE); //TODO: DX_PRIMTYPE_LINESTRIP�ȊO�̋@�\.
		ResetDrawBlendMode();
	}

// ��*---=[ function ]=---*�� //

	//DrawCircle�̉�����.
	int DrawCircleKR(const Circle* data, bool isFill, bool isAnti, float thick) {

		//�A���`�G�C���A�X����.
		if (isAnti) {
			//posnum(�p�`��)��60�ɐݒ肷��.
			int err = DrawCircleAA(_flt(data->pos.x), _flt(data->pos.y), data->r, 60, data->color.GetColorCode(), isFill, thick);
			_return(-1, err < 0) //-1: DrawCircleAA�G���[.
		}
		//�A���`�G�C���A�X�Ȃ�.
		else{
			int err = DrawCircle(_int_r(data->pos.x), _int_r(data->pos.y), _int_r(data->r), data->color.GetColorCode(), isFill, _int_r(thick));
			_return(-2, err < 0) //-2: DrawCircle�G���[.
		}
		return 0; //����I��.
	}
	//DrawBox�̉�����.
	int DrawBoxKR(const Box* data, Anchor anc, bool isFill, bool isAnti) {

		_return(-3, data->size.x <= 0.0 || data->size.y <= 0.0) //-3: �T�C�Y��0.0�ȉ�.

		//�n�_�����߂�.
		float x1 = _flt(data->pos.x - (data->size.x-1) * ANCHOR_POS[anc].x);
		float y1 = _flt(data->pos.y - (data->size.y-1) * ANCHOR_POS[anc].y);
		//�I�_�����߂�.
		float x2 = _flt(x1 + data->size.x-1);
		float y2 = _flt(y1 + data->size.y-1);

		//�A���`�G�C���A�X����.
		if (isAnti) {
			int err = DrawBoxAA(x1, y1, x2+1, y2+1, data->color.GetColorCode(), isFill);
			_return(-1, err < 0) //-1: DrawBoxAA�G���[.
		}
		//�A���`�G�C���A�X�Ȃ�.
		else {
			int err = DrawBox(_int(x1), _int(y1), _int(x2+1), _int(y2+1), data->color.GetColorCode(), isFill);
			_return(-2, err < 0) //-2: DrawBox�G���[.
		}
		return 0; //����I��.
	}
	//DrawTriangle�̉�����.
	int DrawTriangleKR(const Triangle* data, bool isFill, bool isAnti) {

		//�A���`�G�C���A�X����.
		if (isAnti) {
			int err = DrawTriangleAA(
				_flt(data->pos[0].x), _flt(data->pos[0].y),
				_flt(data->pos[1].x), _flt(data->pos[1].y),
				_flt(data->pos[2].x), _flt(data->pos[2].y), data->color.GetColorCode(), isFill
			);
			_return(-1, err < 0) //-1: DrawTriangleAA�G���[.
		}
		//�A���`�G�C���A�X�Ȃ�.
		else {
			int err = DrawTriangle(
				_int_r(data->pos[0].x), _int_r(data->pos[0].y),
				_int_r(data->pos[1].x), _int_r(data->pos[1].y),
				_int_r(data->pos[2].x), _int_r(data->pos[2].y), data->color.GetColorCode(), isFill
			);
			_return(-2, err < 0) //-2: DrawTriangle�G���[.
		}
		return 0; //����I��.
	}
	//DrawLine�̉�����.
	int DrawLineKR(const Line* data, bool isAnti, float thick) {

		//�A���`�G�C���A�X����.
		if (isAnti) {
			int err = DrawLineAA(
				_flt(data->stPos.x), _flt(data->stPos.y),
				_flt(data->edPos.x), _flt(data->edPos.y), data->color.GetColorCode(), thick
			);
			_return(-1, err < 0) //-1: DrawLineAA�G���[.
		}
		//�A���`�G�C���A�X�Ȃ�.
		else {
			int err = DrawLine(
				_int_r(data->stPos.x), _int_r(data->stPos.y), 
				_int_r(data->edPos.x), _int_r(data->edPos.y), data->color.GetColorCode(), _int(thick)
			);
			_return(-2, err < 0) //-2: DrawLine�G���[.
		}
		return 0; //����I��.
	}
	//��ʑS�̂ɃO���b�h����`��.
	int DrawWindowGrid(int wid, int hei, int size, MY_COLOR clrWid, MY_COLOR clrHei) {

		//�c���̕`��.
		for (int x = 0; x < wid; x += size) {

			Line line = { {_dbl(x), 0}, {_dbl(x), _dbl(hei)}, clrHei };
			int err = DrawLineKR(&line);
			_return(-1, err < 0) //-1: �c���ŃG���[.
		}
		//�����̕`��.
		for (int y = 0; y < hei; y += size) {

			Line line = { {0, _dbl(y)}, {_dbl(wid), _dbl(y)}, clrWid };
			int err = DrawLineKR(&line);
			_return(-2, err < 0) //-2: �����ŃG���[.
		}
		return 0; //����I��.
	}

	//�`�惂�[�h�ύX.
	int SetDrawBlendModeKR(BlendModeID id, int power) {
		return SetDrawBlendMode(_int(id), power);
	}
	int SetDrawBlendModeKR(BlendModeID id, double power) {
		return SetDrawBlendMode(_int(id), _int_r(power));
	}
	//�`�惂�[�h���Z�b�g.
	int ResetDrawBlendMode() {
		return SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}