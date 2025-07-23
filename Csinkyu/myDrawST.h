/*
   - myDrawST.h - (original)
   ver.2025/07/24

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
	MODE_ALPHA = DX_BLENDMODE_ALPHA,   //���u�����h.
	MODE_ADD   = DX_BLENDMODE_ADD,     //���Z�u�����h.
	MODE_SUB   = DX_BLENDMODE_SUB,     //���Z�u�����h.
	MODE_MUL   = DX_BLENDMODE_MUL      //��Z�u�����h.
};

//�摜�`��Ɏg���p.
struct DrawImg
{
	Image  img;    //�摜�f�[�^.
	INT_XY pos;    //��ʂ̂ǂ��ɕ`�悷�邩.
};
struct DrawImgRect : public DrawImg
{
	INT_XY stPxl;  //�n�_pixel.
	INT_XY size;   //�؂���T�C�Y.
};
struct DrawImgExtend : public DrawImg
{
	INT_XY size;   //�`�悷��T�C�Y.
};
struct DrawImgRota : public DrawImg
{
	double extend; //�T�C�Y�{��.
	double ang;    //�p�x.
};
//�����`��Ɏg���p.
struct DrawStr
{
	TCHAR  text[256]{};      //�e�L�X�g.
	INT_XY pos;              //��ʂ̂ǂ��ɕ`�悷�邩.
	UINT   color = 0xFFFFFF; //�����̐F.
};
struct DrawStrRota : public DrawStr
{
	INT_XY extend = {1, 1};  //�L�k�{��.
	INT_XY pivot  = {0, 0};  //��]��_.
	double ang    = 0;       //��]�x.
};
struct DrawStrModi : public DrawStr
{
	INT_XY luPos;            //�e�L�X�g�̍�����W.
	INT_XY ruPos;            //�e�L�X�g�̉E����W.
	INT_XY rdPos;            //�e�L�X�g�̉E�����W.
	INT_XY ldPos;            //�e�L�X�g�̍������W.
};

//�}�`.
int    DrawCircleST		 (const Circle* data, BOOL isFill = TRUE, int thick = 1);
int    DrawBoxST		 (const Box*    data, BOOL isCenter, BOOL isFill = TRUE);
int    DrawLineST		 (const Line*   data, int  thick = 1);
int    DrawWindowGrid	 (int wid, int hei, int size, UINT clrWid = 0xA0A0FF, UINT clrHei = 0xFFA0A0);

//�摜.
int    LoadGraphST		 (Image* img, const TCHAR fileName[]);
int    LoadDivGraphST	 (vector<Image>* img, const TCHAR fileName[], INT_XY size, INT_XY cnt);
int    DrawGraphST		 (const DrawImg*       data, BOOL isCenter, BOOL isTrans = TRUE);
int    DrawRectGraphST	 (const DrawImgRect*   data, BOOL isTrans = TRUE);
int    DrawExtendGraphST (const DrawImgExtend* data, BOOL isCenter, BOOL isTrans = TRUE);
int    DrawRotaGraphST	 (const DrawImgRota*   data, BOOL isCenter, BOOL isTrans = TRUE);

//�e�L�X�g.
int    DrawStringST		 (const DrawStr*     data, BOOL isCenter,   int font = -1);
int    DrawRotaStringST	 (const DrawStrRota* data, BOOL isVertical, int font = -1);
int    DrawModiStringST	 (const DrawStrModi* data, BOOL isVertical, int font = -1);
INT_XY GetTextSize		 (const TCHAR str[], int font = -1);

//�t�H���g.
int    CreateFontH		 (int size, int thick, FontTypeID fontId = FONT_NONE);

//�I�u�W�F�N�g.
int    DrawObjectGrid	 (const ObjectGrid* data, INT_XY gridPos, INT_XY gridSize);
int    DrawObjectBox	 (const ObjectBox*  data, BOOL isDrawHit = FALSE);
int    DrawObjectCir	 (const ObjectCir*  data, BOOL isDrawHit = FALSE);

//�`�惂�[�h.
int    SetDrawBlendModeST(BlendModeID id, int    power = 255);
int    SetDrawBlendModeST(BlendModeID id, double power = 255);
int    ResetDrawBlendMode();