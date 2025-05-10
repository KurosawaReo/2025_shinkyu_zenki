/*
   - myDrawST.cpp - (original)

   DxLib�Ŏg���p�̃I���W�i���`��֐�.
*/
#pragma once

#if !defined DEF_INT_XY
#define DEF_INT_XY
//x��y�̋Ïk��.
struct INT_XY
{
	int x;
	int y;
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
	INT_XY pos   = {0, 0};     //��ʂ̂ǂ��ɕ`�悷�邩.
	UINT   color = 0xFFFFFF;   //�����̐F.
};
struct STR_DRAW_ROTA
{
	TCHAR  text[256]{};        //�e�L�X�g.
	INT_XY pos    = {0, 0};    //��ʂ̂ǂ��ɕ`�悷�邩.
	INT_XY extend = {1, 1};    //�L�k�{��.
	INT_XY pivot  = {0, 0};    //��]��_.
	double ang    = 0;         //��]�x.
	UINT   color  = 0xFFFFFF;  //�����̐F.

	BOOL   isVertical = FALSE; //�c�����ɂ��邩.
};
struct STR_DRAW_MODI
{
	TCHAR  text[256]{};        //�e�L�X�g.
	INT_XY luPos = {  0,  0};  //�e�L�X�g�̍�����W.
	INT_XY ruPos = {100,  0};  //�e�L�X�g�̉E����W.
	INT_XY rdPos = {100, 30};  //�e�L�X�g�̉E�����W.
	INT_XY ldPos = {  0, 30};  //�e�L�X�g�̍������W.
	UINT   color = 0xFFFFFF;   //�����̐F.

	BOOL   isVertical = FALSE; //�c�����ɂ��邩.
};

INT_XY DrawLineAng     (INT_XY pos, float ang, float len, int clr, int thick = 1);

int    LoadGraphST     (IMG* img, const TCHAR* fileName);
int    DrawGraphST     (const IMG_DRAW*      data);
int    DrawRectGraphST (const IMG_DRAW_RECT* data);

int    DrawStringST    (const STR_DRAW*      data, int font = -1);
int    DrawRotaStringST(const STR_DRAW_ROTA* data, int font = -1);
int    DrawModiStringST(const STR_DRAW_MODI* data, int font = -1);