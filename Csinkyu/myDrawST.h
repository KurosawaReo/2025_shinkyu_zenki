/*
   - myDrawST.h - (original)
   ver.2025/07/20

   DxLib: �I���W�i���`��@�\�̒ǉ�.
*/
#pragma once

//�t�H���g�^�C�vID(���͂��₷������p)
enum FONTTYPE_ID
{
	FONT_NORMAL = DX_FONTTYPE_NORMAL,
	FONT_EDGE   = DX_FONTTYPE_EDGE,
	FONT_ANTI   = DX_FONTTYPE_ANTIALIASING, //�A���`�G�C���A�X(���炩�ɂȂ�)

	FONT_NONE   = -1, //�w��Ȃ�.
};
//�`�惂�[�hID(���͂��₷������p)
enum BLENDMODE_ID
{
	MODE_NONE  = DX_BLENDMODE_NOBLEND, //�f�t�H���g.
	MODE_ALPHA = DX_BLENDMODE_ALPHA,   //���u�����h.
	MODE_ADD   = DX_BLENDMODE_ADD,     //���Z�u�����h.
	MODE_SUB   = DX_BLENDMODE_SUB,     //���Z�u�����h.
	MODE_MUL   = DX_BLENDMODE_MUL      //��Z�u�����h.
};

//�摜�`��Ɏg���p.
struct IMG_DRAW
{
	IMG    img;      //�摜�f�[�^.
	INT_XY pos;      //��ʂ̂ǂ��ɕ`�悷�邩.
};
struct IMG_DRAW_RECT
{
	IMG    img;      //�摜�f�[�^.
	INT_XY pos;      //��ʂ̂ǂ��ɕ`�悷�邩.(������W�)
	INT_XY stPxl;    //�n�_pixel.
	INT_XY size;     //�؂���T�C�Y.
};
struct IMG_DRAW_EXTEND
{
	IMG    img;		 //�摜�f�[�^.
	INT_XY pos;		 //��_.
	INT_XY size;	 //�`�悷��T�C�Y.
};
struct IMG_DRAW_ROTA
{
	IMG    img;      //�摜�f�[�^.
	INT_XY pos;      //��ʂ̂ǂ��ɕ`�悷�邩.
	double extend;   //�T�C�Y�{��.
	double ang;      //�p�x.
};
//�����`��Ɏg���p.
struct STR_DRAW
{
	TCHAR  text[256]{};        //�e�L�X�g.
	INT_XY pos;                //��ʂ̂ǂ��ɕ`�悷�邩.
	UINT   color = 0xFFFFFF;   //�����̐F.
};
struct STR_DRAW_ROTA
{
	TCHAR  text[256]{};        //�e�L�X�g.
	INT_XY pos;                //��ʂ̂ǂ��ɕ`�悷�邩.
	INT_XY extend = {1, 1};    //�L�k�{��.
	INT_XY pivot  = {0, 0};    //��]��_.
	double ang    = 0;         //��]�x.
	UINT   color  = 0xFFFFFF;  //�����̐F.
};
struct STR_DRAW_MODI
{
	TCHAR  text[256]{};        //�e�L�X�g.
	INT_XY luPos;              //�e�L�X�g�̍�����W.
	INT_XY ruPos;              //�e�L�X�g�̉E����W.
	INT_XY rdPos;              //�e�L�X�g�̉E�����W.
	INT_XY ldPos;              //�e�L�X�g�̍������W.
	UINT   color = 0xFFFFFF;   //�����̐F.
};

//�}�`.
int    DrawCircleST		 (const Circle* data, BOOL isFill = TRUE, int thick = 1);
int    DrawBoxST		 (const Box*    data, BOOL isCenter, BOOL isFill = TRUE);
int    DrawLineST		 (const Line*   data, int  thick = 1);
int    DrawWindowGrid	 (int wid, int hei, int size, UINT clrWid = 0xA0A0FF, UINT clrHei = 0xFFA0A0);

//�摜.
int    LoadGraphST		 (IMG* img, const TCHAR fileName[]);
int    LoadDivGraphST	 (vector<IMG>* img, const TCHAR fileName[], INT_XY size, INT_XY cnt);
int    DrawGraphST		 (const IMG_DRAW*        data, BOOL isCenter, BOOL isTrans = TRUE);
int    DrawRectGraphST	 (const IMG_DRAW_RECT*   data, BOOL isTrans = TRUE);
int    DrawExtendGraphST (const IMG_DRAW_EXTEND* data, BOOL isCenter, BOOL isTrans = TRUE);
int    DrawRotaGraphST	 (const IMG_DRAW_ROTA*   data, BOOL isCenter, BOOL isTrans = TRUE);

//�e�L�X�g.
int    DrawStringST		 (const STR_DRAW*      data, BOOL isCenter,   int font = -1);
int    DrawRotaStringST	 (const STR_DRAW_ROTA* data, BOOL isVertical, int font = -1);
int    DrawModiStringST	 (const STR_DRAW_MODI* data, BOOL isVertical, int font = -1);
INT_XY GetTextSize		 (const TCHAR str[], int font = -1);

//�t�H���g.
int    CreateFontH		 (int size, int thick, FONTTYPE_ID fontId = FONT_NONE);

//�I�u�W�F�N�g.
int    DrawObjectGrid	 (const ObjectGrid* data, INT_XY gridPos, INT_XY gridSize);
int    DrawObjectBox	 (const ObjectBox*  data, BOOL isDrawHit = FALSE);
int    DrawObjectCir	 (const ObjectCir*  data, BOOL isDrawHit = FALSE);

//�`�惂�[�h.
int    SetDrawBlendModeST(BLENDMODE_ID id, int power = 255);
int    ResetDrawBlendMode();