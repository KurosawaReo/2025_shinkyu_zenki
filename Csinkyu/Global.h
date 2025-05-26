/*
   - Global.h -
   ver.2025/05/21

   ���ʂŎg�p����^��}�N�������鏊.
*/
#pragma once

//����Global.h����`����Ă��邩���ʂ���p.
#define DEF_GLOBAL_H

//stdafx������Ȃ炢��Ȃ�.
#if true
#define _USE_MATH_DEFINES  //math�萔���g���̂ɕK�v.
#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <time.h>
#include "DxLib.h"
#endif

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

#if !defined DEF_VARTYPE_MACRO
#define DEF_VARTYPE_MACRO
#define _int(n)   (int)(round(n))            //int�^�ϊ��}�N��.
#define _intXY(n) {_int(n.x), _int(n.y)}     //INT_XY�^�ϊ��}�N��.
#define _dblXY(n) {(double)n.x, (double)n.y} //DBL_XY�^�ϊ��}�N��.
#endif

// - �񋓑� -
enum Scene
{
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_END,
};

// - �Q�[���f�[�^ -
struct GameData
{
	Scene scene;  //�V�[���̋L�^�p.
	BOOL  isSlow; //�X���[���[�h���ǂ���.
};

// - �萔 -
#define IS_WINDOW_MODE			(TRUE)			//�E�B���h�E���[�h�ɂ��邩.

#define WINDOW_WID				(600)			//�E�B���h�E�̉���.
#define WINDOW_HEI				(480)			//�E�B���h�E�̏c��.
#define WINDOW_COLOR_BIT		(32)			//�E�B���h�E�̃J���[bit��.

#define WAIT_LOOP_MS			(10)			//���[�v�����̑ҋ@����(m�b)

#define SLOW_MODE_SPEED			(0.25)			//�X���[���[�h���x�{��.

#define PLAYER_SIZE				(20)			//�v���C���[�T�C�Y.
#define PLAYER_MOVE_SPEED		(4)				//�v���C���[�ړ����x.
#define PLAYER_HIT_R			(10)			//�v���C���[�̓����蔻��~�̔��a.

#define OBSTACLE2_SPAN			(50)			//��Q���̔��ˊԊu.
#define OBSTACLE2_SPEED			(4.0)			//��Q���̑��x.
#define OBSTACLE2_LIM_F			(80)			//�ő�ǐՃt���[����.

#define OBSTACLE3_SIZE			(20)			//��Q���T�C�Y.
#define OBSTACLE3_TRACK_POW		(8)				//��Q���̒ǔ���.
#define OBSTACLE3_SPEED			(3)				//��Q���̑��x.

#define OBSTACLE4_SHOT_RESET	(50)			//��Q���̔��˃��Z�b�g����.
#define OBSTACLE4_SHOT_START	(30)			//��Q���̔��ˊJ�n����.
#define OBSTACLE4_SHOT_SPAN		(1)			//��Q���̔��ˊԊu����.
#define OBSTACLE4_SPEED			(100)			//��Q���̑��x.
#define OBSTACLE4_MAX_L			(100)			//��Q������ԍő勗��.
#define OBSTACLE4_LINE_MAX		(2000)			//��Q���ŕ`�悷����̍ő吔.

// - �֐� -