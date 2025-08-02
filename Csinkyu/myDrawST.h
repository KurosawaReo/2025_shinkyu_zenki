/*
   - myDrawST.h - (original)
   ver.2025/08/02

   DxLib: �I���W�i���`��@�\�̒ǉ�.
*/
#pragma once

//�t�H���g�^�C�vID(���͂��₷������p)
enum FontTypeID
{
	FONT_NORMAL = DX_FONTTYPE_NORMAL,
	FONT_EDGE   = DX_FONTTYPE_EDGE,
	FONT_ANTI   = DX_FONTTYPE_ANTIALIASING, //�A���`�G�C���A�X(���炩�ɂȂ�)

	FONT_NONE   = -1, //�w��Ȃ�.
};
//�`�惂�[�hID(���͂��₷������p)
enum BlendModeID
{
	MODE_NONE  = DX_BLENDMODE_NOBLEND, //�f�t�H���g.
	MODE_ALPHA = DX_BLENDMODE_ALPHA,   //���u�����h.  (�d�Ȃ�Ɠ��߂���)
	MODE_ADD   = DX_BLENDMODE_ADD,     //���Z�u�����h.(�d�Ȃ�Ɩ��x�����邭�Ȃ�)
	MODE_SUB   = DX_BLENDMODE_SUB,     //���Z�u�����h.(�d�Ȃ�Ɩ��x���Â��Ȃ�)
	MODE_MUL   = DX_BLENDMODE_MUL      //��Z�u�����h.
};

//�摜�f�[�^.
struct Image
{
	int    handle; //�n���h��.
	INT_XY size;   //�摜�̃T�C�Y.
};
//������f�[�^.
struct String
{
	MY_STRING text; //�e�L�X�g.
	INT_XY    pos;  //��ʂ̂ǂ��ɕ`�悷�邩.
	UINT      clr;  //�����̐F.
};

//�摜�`��N���X.
class DrawImgST
{
private:
	vector<Image> data; //�摜�f�[�^.

public:
	//�ǂݍ���.
	int LoadGraphST   (MY_STRING fileName);
	int LoadDivGraphST(MY_STRING fileName, INT_XY size, INT_XY cnt);
	//�`��.
	int DrawGraphST      (int imgNo, INT_XY pos, BOOL isCenter, BOOL isTrans = TRUE);
	int DrawRectGraphST  (int imgNo, INT_XY pos, INT_XY stPos, INT_XY size, BOOL isTrans = TRUE);
	int DrawExtendGraphST(int imgNo, INT_XY pos, DBL_XY sizeRate, BOOL isCenter, BOOL isTrans = TRUE);
	int DrawRotaGraphST  (int imgNo, INT_XY pos, double extend, double ang, BOOL isCenter, BOOL isTrans = TRUE);
};

//�e�L�X�g�`��N���X.
class DrawStrST
{
private:
	String data; //������f�[�^.

public:
	//�������p.
	DrawStrST(MY_STRING _text, INT_XY _pos, UINT _clr) :
		data{_text, _pos, _clr}
	{}
	//set.
	void SetText(MY_STRING _text) {
		data.text = _text;
	}
	void SetPos(int _x, int _y) {
		data.pos = {_x, _y};
	}
	void SetColor(UINT _color) {
		data.clr = _color;
	}
	//get.
	INT_XY GetPos() {
		return data.pos;
	}
	//�`��.
	int    DrawStringST	   (BOOL isCenter, int font = -1);
	int    DrawRotaStringST(INT_XY extend, INT_XY pivot, double ang, BOOL isVertical, int font = -1);
	int    DrawModiStringST(INT_XY luPos, INT_XY ruPos, INT_XY rdPos, INT_XY ldPos, BOOL isVertical, int font = -1);
	INT_XY GetTextSize 	   (MY_STRING str, int font = -1);
};

//�}�`.
int    DrawCircleST		 (const Circle*   data, BOOL isFill = TRUE, BOOL isAnti = FALSE, float thick = 1);
int    DrawBoxST		 (const Box*      data, BOOL isCenter, BOOL isFill = TRUE, BOOL isAnti = FALSE);
int    DrawTriangleST	 (const Triangle* data, BOOL isFill = TRUE, BOOL isAnti = FALSE);
int    DrawLineST		 (const Line*     data, BOOL isAnti = FALSE, float thick = 1.0f);
int    DrawWindowGrid	 (int wid, int hei, int size, UINT clrWid = 0xA0A0FF, UINT clrHei = 0xFFA0A0);

//�t�H���g.
int    CreateFontH       (int size, int thick, FontTypeID fontId = FONT_NONE);

//�`�惂�[�h.
int    SetDrawBlendModeST(BlendModeID id, int    power = 255);
int    SetDrawBlendModeST(BlendModeID id, double power = 255);
int    ResetDrawBlendMode();