/*
   - Gloval.h -
   �萔�Ȃǂ��܂Ƃ߂鏊.
*/
#pragma once

#if !define DEF_INT_XY
#define DEF_INT_XY 
//x��y�̋Ïk��.
struct INT_XY
{
	int x;
	int y;
};
#endif

#if !define DEF_DBL_XY
#define DEF_DBL_XY 
//x��y�̋Ïk��.
struct DBL_XY
{
	double x;
	double y;
};
#endif

// - �}�N�� -
#define _int(n)	((int)lround(n))	//int�^�ϊ��}�N��.

// - �萔 -
#define IS_WINDOW_MODE		(TRUE)		//�E�B���h�E���[�h�ɂ��邩.

#define WINDOW_WID			(600)		//�E�B���h�E�̉���.
#define WINDOW_HEI			(480)		//�E�B���h�E�̏c��.
#define WINDOW_COLOR_BIT	(32)		//�E�B���h�E�̃J���[bit��.

#define WAIT_LOOP_MS		(10)		//���[�v�����̑ҋ@����(m�b)

#define PLAYER_SIZE			(20)		//�v���C���[�T�C�Y.
#define PLAYER_MOVE_SPEED	(5)			//�v���C���[�ړ����x.