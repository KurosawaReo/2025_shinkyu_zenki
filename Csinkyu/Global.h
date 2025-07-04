/*
   - Global.h -

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
  #include <stdlib.h>
  #include <time.h>
  #include "DxLib.h"
#endif

//int�^�̋Ïkxy.
struct INT_XY
{
	int x;
	int y;
};
//double�^�̋Ïkxy.
struct DBL_XY
{
	double x;
	double y;
};
//�摜�f�[�^�i�[�p.
struct IMG
{
	int    handle;	 //�n���h��.
	INT_XY size;	 //�摜�̃T�C�Y.
};

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
	DBL_XY size; //�T�C�Y.
	UINT   clr;  //�F.
};
//���f�[�^.
struct Line
{
	DBL_XY stPos; //�n�_���W.
	DBL_XY edPos; //�I�_���W.
	UINT   clr;   //�F.
};
//�I�u�W�F�N�g(�l�p�`)
struct ObjectBox
{
	Box    box{};      //�����蔻��ƍ��W.
	DBL_XY offset{};   //�摜�����炷��.
	IMG    img{};      //�摜.
	BOOL   isActive{}; //�L�����ǂ���.

	//�������p.
	ObjectBox(){}
	//�������p(��������)
	ObjectBox(DBL_XY _pos, DBL_XY _size, DBL_XY _offset, UINT _clr, BOOL _isActive) :
		box     ({_pos, _size, _clr}), 
		offset  (_offset), 
		isActive(_isActive)
	{}
};
//�I�u�W�F�N�g(�~)
struct ObjectCir
{
	Circle cir{};      //�����蔻��ƍ��W.
	DBL_XY offset{};   //�摜�����炷��.
	IMG    img{};      //�摜.
	BOOL   isActive{}; //�L�����ǂ���.

	//�������p.
	ObjectCir(){}
	//�������p(��������)
	ObjectCir(DBL_XY _pos, float _r, DBL_XY _offset, UINT _clr, BOOL _isActive) :
		cir     ({ _pos, _r, _clr }), 
		offset  (_offset), 
		isActive(_isActive)
	{}
};

//�^�ϊ��}�N��.
#define _int(n)   (int)(round(n))            //int   �^�ϊ��}�N��.
#define _intXY(n) {_int(n.x), _int(n.y)}     //INT_XY�^�ϊ��}�N��.
#define _dblXY(n) {(double)n.x, (double)n.y} //DBL_XY�^�ϊ��}�N��.

#define _if_check(n) assert(n); if(n)        //if���̑O�ɓ�������assert������.

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
	int   font1;     //�t�H���g.
	int   font2;     //�t�H���g.
};

// - Debug -
#define DEBUG_LASER_ACTIVE //��`����ƃf�o�b�O�\��ON.

// - �萔 -
#define IS_WINDOW_MODE				(TRUE)			//�E�B���h�E���[�h�ɂ��邩.

#define WINDOW_WID					(1920)			//�E�B���h�E�̉���.
#define WINDOW_HEI					(1080)			//�E�B���h�E�̏c��.
#define WINDOW_COLOR_BIT			(32)			//�E�B���h�E�̃J���[bit��.

#define FPS							(80)			//�t���[�����[�g.

#define SLOW_MODE_TIME				(5)             //�X���[���[�h��������.
#define SLOW_MODE_SPEED				(0.20f)			//�X���[���[�h���x�{��.

#define PLAYER_SIZE					(20)			//�v���C���[�T�C�Y.
#define PLAYER_MOVE_SPEED			(6)				//�v���C���[�ړ����x.
#define PLAYER_HIT_R				(10)			//�v���C���[�̓����蔻��~�̔��a.
#define PLAYER_REF_COOLDOWN			(0)				//���˃N�[���_�E������.
#define PLAYER_AFT_IMG_NUM	        (10)            //�c���f�[�^�̐�.

#define ITEM_SIZE					(20)			//�A�C�e���T�C�Y.
#define ITEM_SPEED					(3)				//�A�C�e���ړ��X�s�[�h.  
#define ITEM_RESPAWN_TIME			(300)           //�A�C�e����������.

#define OBSTACLE2_SPAN				(80)			//��Q���̔��ˊԊu.
#define OBSTACLE2_SPEED				(3.0)			//��Q���̑��x.
#define	OBSTACLE2_ROT_MAX			(5.0)			//��Q���̒ǔ���(1�t���[���ŉ�]�ł���ő�x��)
#define OBSTACLE2_LIM_F				(80)			//�ő�ǐՃt���[����.

#define OBSTACLE3_SIZE				(20)			//��Q���T�C�Y.
#define OBSTACLE3_TRACK_POW			(8)				//��Q���̒ǔ���.
#define OBSTACLE3_SPEED				(3)				//��Q���̑��x.

#define OBSTACLE4_OUTER_MARGIN		(0)				//�C��̎��񎞂̊O���]��.
#define OBSTACLE4_SHOT_RESET		(80)			//�C��̔��˃��Z�b�g����.
#define OBSTACLE4_SHOT_START		(30)			//�C��̔��ˊJ�n����.
#define OBSTACLE4_SHOT_SPAN			(10)			//�C��̔��ˊԊu����.
#define OBSTACLE4_LASER_SPEED		(150)			//���[�U�[�̑��x.
#define OBSTACLE4_ROT_LIMIT			(90)			//�Ȃ�����E�p�x.
#define OBSTACLE4_LASER_LIM			(100)			//���[�U�[�̍ő吔.
#define OBSTACLE4_LINE_MAX			(10000)			//���[�U�[�ŕ`�悷����̍ő吔.

#define OBSTACLE4_FLASH_MAX         (30)            //�ő�t���b�V���G�t�F�N�g��
#define OBSTACLE4_FLASH_SIZE_INIT   (5.0f)          //�t���b�V���G�t�F�N�g�̏����T�C�Y.
#define OBSTACLE4_FLASH_SIZE_SPREAD (3)             //�t���b�V���G�t�F�N�g�̊g���.
#define OBSTACLE4_FLASH_VALID_TM	(50)            //�t���b�V���G�t�F�N�g�̎����t���[��.
#define OBSTACLE4_FLASH_ALPHA_TM	(2)             //�t���b�V���G�t�F�N�g�̓��������x.

#define OBSTACLE5_FLASH_MAX         (30)            //�ő�t���b�V���G�t�F�N�g��
#define OBSTACLE5_FLASH_SIZE_INIT   (5.0f)          //�t���b�V���G�t�F�N�g�̏����T�C�Y.
#define OBSTACLE5_FLASH_SIZE_SPREAD (3)             //�t���b�V���G�t�F�N�g�̊g���.
#define OBSTACLE5_FLASH_VALID_TM	(50)            //�t���b�V���G�t�F�N�g�̎����t���[��.
#define OBSTACLE5_FLASH_ALPHA_TM	(2)             //�t���b�V���G�t�F�N�g�̓��������x.

#define METEO_CNT_MAX				(256)			//覐΂̍ő�o����.
#define METEO_SPAWN_SPAN			(10)			//覐΂̏o�����ԊԊu.
#define METEO_SPEED					(5)				//�ړ����x.
#define METEO_ERASE_OUT_DIS			(50)			//覐΂���ʊO�ŏ����鋗��.
#define METEO_GOAL_RAND_RANGE		(500)			//覐΂̖ڕW�n�_�̗����͈�.

#define METEO_LINE_CNT_MIN			(5)				//�Œ�n�p�`.
#define METEO_LINE_CNT_MAX			(16)			//�ő�n�p�`.
#define METEO_LINE_DIS_MIN			(40)			//���_�̍ŒZ����.
#define METEO_LINE_DIS_MAX			(60)			//���_�̍ő勗��.