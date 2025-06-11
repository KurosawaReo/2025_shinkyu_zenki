/*
   - Global.h -
   ver.2025/06/06

   ���ʂŎg�p����^��}�N�������鏊.
*/
#pragma once

//����Global.h����`����Ă��邩���ʂ���p.
#define DEF_GLOBAL_H

//stdafx������Ȃ炢��Ȃ�.
#if true
  #define _USE_MATH_DEFINES  //math�萔���g���̂ɕK�v.
  #define _CRT_SECURE_NO_WARNINGS
  #include <assert.h>
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

#if !defined DEF_OBJECT
#define DEF_OBJECT
//�~�f�[�^.
struct Circle
{
	DBL_XY pos;  //���W.
	float  r;    //���a.
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
//�摜�f�[�^�i�[�p.
struct IMG
{
	int    handle;	 //�n���h��.
	INT_XY size;	 //�摜�̃T�C�Y.
};

//�I�u�W�F�N�g(�l�p�`)
struct ObjectBox
{
	Box box{}; //�����蔻��ƍ��W.
	IMG img{}; //�摜.

	ObjectBox(DBL_XY _pos, INT_XY _size, UINT _clr) :
		box({ _pos, _size, _clr })
	{}
};
//�I�u�W�F�N�g(�~)
struct ObjectCir
{
	Circle cir{}; //�����蔻��ƍ��W.
	IMG    img{}; //�摜.

	ObjectCir(DBL_XY pos, float r, UINT clr) :
		cir({ pos, r, clr })
	{}
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
//���[�U�[�ړ���.
enum MoveDir 
{
	MOVE_RIGHT,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_UP
};
// - �Q�[���f�[�^ -
struct GameData
{
	Scene scene;     //�V�[���̋L�^�p.
	BOOL  isSlow;    //�X���[���[�h���ǂ���.
};

// - �萔 -
#define IS_WINDOW_MODE				(TRUE)			//�E�B���h�E���[�h�ɂ��邩.

#define WINDOW_WID					(600)			//�E�B���h�E�̉���.
#define WINDOW_HEI					(480)			//�E�B���h�E�̏c��.
#define WINDOW_COLOR_BIT			(32)			//�E�B���h�E�̃J���[bit��.

#define WAIT_LOOP_MS				(1000/80)		//���[�v�����̑ҋ@����(m�b)

#define SLOW_MODE_TIME				(5)             //�X���[���[�h��������.
#define SLOW_MODE_SPEED				(0.20f)			//�X���[���[�h���x�{��.

#define PLAYER_SIZE					(20)			//�v���C���[�T�C�Y.
#define PLAYER_MOVE_SPEED			(4)				//�v���C���[�ړ����x.
#define PLAYER_HIT_R				(10)			//�v���C���[�̓����蔻��~�̔��a.

#define ITEM_SIZE					(20)			//�A�C�e���T�C�Y.
#define ITEM_SPEED					(9)				//�A�C�e���ړ��X�s�[�h.  
#define ITEM_RESPAWN_TIME			(480)           //�A�C�e����������.

#define OBSTACLE2_SPAN				(80)			//��Q���̔��ˊԊu.
#define OBSTACLE2_SPEED				(3.0)			//��Q���̑��x.
#define	OBSTACLE2_ROT_MAX			(5.0)			//��Q���̒ǔ���(1�t���[���ŉ�]�ł���ő�x��)
#define OBSTACLE2_LIM_F				(80)			//�ő�ǐՃt���[����.

#define OBSTACLE3_SIZE				(20)			//��Q���T�C�Y.
#define OBSTACLE3_TRACK_POW			(8)				//��Q���̒ǔ���.
#define OBSTACLE3_SPEED				(3)				//��Q���̑��x.

#define OBSTACLE4_OUTER_MARGIN		(20)			//�C��̎��񎞂̊O���]��.
#define OBSTACLE4_SHOT_RESET		(60)			//�C��̔��˃��Z�b�g����.
#define OBSTACLE4_SHOT_START		(20)			//�C��̔��ˊJ�n����.
#define OBSTACLE4_SHOT_SPAN			(10)			//�C��̔��ˊԊu����.
#define OBSTACLE4_LASER_SPEED		(100)			//���[�U�[�̑��x.
#define OBSTACLE4_LASER_LIM			(100)			//���[�U�[����ԍő勗��.
#define OBSTACLE4_LASER_LINE_MAX	(1000)			//���[�U�[�ŕ`�悷����̍ő吔.
