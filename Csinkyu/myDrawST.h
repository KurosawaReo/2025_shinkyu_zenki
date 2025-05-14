/*
   - myDrawST.cpp - (original)

   DxLib�Ŏg���p�̃I���W�i���`��֐�.
   2025/05/14
*/
#pragma once

#if !defined DEF_INT_XY
#define DEF_INT_XY
//int�^�̋Ïkxy.
struct INT_XY
{
	int x;
	int y;
};
#endif

#if !defined DEF_DBL_XY
#define DEF_DBL_XY
//double�^�̋Ïkxy.
struct DBL_XY
{
	double x;
	double y;
};
#endif

#if !defined DEF_SHAPES
#define DEF_SHAPES
//�~�f�[�^.
struct Circle
{
	DBL_XY pos;  //���W.
	int    r;    //���a.
	UINT   clr;  //�F.
};
//�l�p�`�f�[�^.
struct Box
{
	DBL_XY pos;  //���W.
	INT_XY size; //�T�C�Y.
	UINT   clr;  //�F.
};
//���f�[�^.
struct Line
{
	DBL_XY stPos; //�n�_���W.
	DBL_XY edPos; //�I�_���W.
	UINT   clr;   //�F.
};
#endif

//�摜�f�[�^�i�[�p.
struct IMG
{
	int    handle;	 //�n���h��.
	INT_XY size;	 //�摜�̃T�C�Y.
};
//�摜�`��Ɏg���p.
struct IMG_DRAW
{
	IMG    img;      //�摜�f�[�^.
	
	INT_XY pos;      //��ʂ̂ǂ��ɕ`�悷�邩.

	BOOL   isCenter; //������ɂ��邩.
	BOOL   isTrans;  //���߂̉�.
};
struct IMG_DRAW_ROTA
{
	IMG    img;      //�摜�f�[�^.

	INT_XY pos;      //��ʂ̂ǂ��ɕ`�悷�邩.
	double extend;   //�T�C�Y�{��.
	double ang;      //�p�x.

	BOOL   isCenter; //������ɂ��邩.
	BOOL   isTrans;  //���߂̉�.
};
struct IMG_DRAW_RECT
{
	IMG    img;      //�摜�f�[�^.

	INT_XY pos;      //��ʂ̂ǂ��ɕ`�悷�邩.(������W�)
	INT_XY stPxl;    //�n�_pixel.
	INT_XY size;     //�؂���T�C�Y.

	BOOL   isTrans;  //���߂̉�.
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

	BOOL   isVertical = FALSE; //�c�����ɂ��邩.
};
struct STR_DRAW_MODI
{
	TCHAR  text[256]{};        //�e�L�X�g.
	INT_XY luPos;              //�e�L�X�g�̍�����W.
	INT_XY ruPos;              //�e�L�X�g�̉E����W.
	INT_XY rdPos;              //�e�L�X�g�̉E�����W.
	INT_XY ldPos;              //�e�L�X�g�̍������W.
	UINT   color = 0xFFFFFF;   //�����̐F.

	BOOL   isVertical = FALSE; //�c�����ɂ��邩.
};

int    DrawCircleST    (const Circle* data);
int    DrawBoxST       (const Box*    data, BOOL isCenter, BOOL isFill);
int    DrawLineST      (const Line*   data);

int    LoadGraphST     (IMG* img, const TCHAR* fileName);
int    DrawGraphST     (const IMG_DRAW*      data);
int    DrawRotaGraphST (const IMG_DRAW_ROTA* data);
int    DrawRectGraphST (const IMG_DRAW_RECT* data);

int    DrawStringST    (const STR_DRAW*      data, int font = -1);
int    DrawRotaStringST(const STR_DRAW_ROTA* data, int font = -1);
int    DrawModiStringST(const STR_DRAW_MODI* data, int font = -1);