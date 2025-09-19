/*
   - Global.h -

   REFLINE�p�̃O���[�o��.
   KR_Library�p�̃O���[�o���͕��ލς�.
*/
#pragma once

//�Ē�`�h�~�p(TODO:�Ȃ���������O���ƍĒ�`�G���[�ɂȂ�)
#if !defined GLOBAL
#define GLOBAL

using namespace KR_Lib;

//====================================================================//
//�y�񋓑́z

//�V�[��.
enum Scene
{
	SCENE_TITLE,
	SCENE_MENU,     //���j���[���.
	SCENE_GAME,
	SCENE_END,
	SCENE_PAUSE,    //�|�[�Y���.

	SCENE_COUNT,    //����.
};
//�ړ�����.
//���[�U�[(normal)�C��p.
enum MoveDir
{
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN
};
//�X�e�[�W���,
enum StageType
{
	STAGE_ENDLESS,
	STAGE_TUTORIAL,
};

//====================================================================//
//�yDebug�z

//��`����ƃf�o�b�O�\��ON.
//#define DEBUG_LASER_ACTIVE
//#define DEBUG_SPAWN_RATE

//====================================================================//
//�y�萔�z

//DxLib�ݒ�.
#define FILE_DATA_PATH	(_T("Data"))					//�f�[�^��ۑ�����ꏊ.
#define FILE_DATA		(_T("Data/score.data"))			//�f�[�^��ۑ�����t�@�C��.

#define IS_WINDOW_MODE					(FALSE)			//�E�B���h�E���[�h�ɂ��邩.

#define WINDOW_WID						(1920)			//�E�B���h�E�̉���.
#define WINDOW_HEI						(1080)			//�E�B���h�E�̏c��.
#define WINDOW_COLOR_BIT				(32)			//�E�B���h�E�̃J���[bit��.

#define FPS								(80)			//�t���[�����[�g.

//�Q�[���ݒ�.
#define GAME_START_TIME					(1.0)			//�Q�[���J�n����܂ł̒x��.

#define SLOW_MODE_TIME					(8)             //�X���[���[�h��������.
#define SLOW_MODE_SPEED					(0.20f)			//�X���[���[�h���x�{��.

#define MIDDLE_ANIM_TIME				(120)			//���x���A�b�v�A�j���[�V��������.

//�v���C���[.
#define PLAYER_SIZE						(17)			//�v���C���[�T�C�Y.
#define PLAYER_MOVE_SPEED				(8)				//�v���C���[�ړ����x.
#define PLAYER_AFT_IMG_NUM				(9)             //�c���f�[�^�̐�.
#define PLAYER_DEATH_ANIM_TIME			(10)			//�v���C���[���S�A�j������.

//�A�C�e��.
#define ITEM_SIZE						(25)			//�A�C�e���T�C�Y.
#define ITEM_SPEED						(3)				//�A�C�e���ړ��X�s�[�h.  
#define ITEM_RESPAWN_TIME				(400)           //�A�C�e����������.

//���[�U�[����.
#define LASER_REF_ROT_MAX				(10)			//���[�U�[(reflected)�̋Ȃ�����E�p�x.
#define LASER_REF_TRACK_ST_TM			(10)			//���[�U�[(reflected)�̒ǔ��J�n����.
#define LASER_REF_TRACK_ED_TM			(30)			//���[�U�[(reflected)�̒ǔ��I������.
#define LASER_NOR_SPEED					(0.1)		    //���[�U�[(normal)   �̑��x.
#define LASER_STR_SPEED					(50.0)		    //���[�U�[(straight) �̑��x.
#define LASER_REF_SPEED					(0.5)		    //���[�U�[(reflected)�̑��x.
#define LASER_CNT_MAX					(80)			//���[�U�[�̍ő吔.
#define LASER_LINE_CNT_MAX				(14000)			//���[�U�[�`����̍ő吔.
#define LASER_LINE_DRAW_LEN				(2)				//���[�U�[�`�����`���Œ�̒���(DrawLineAA�̊֌W��)
#define LASER_REF_ANIM_TIME				(20)			//���˃A�j���[�V��������.

//��Q��: �ʏ탌�[�U�[.
#define LASER_NOR_OUTER_MARGIN			(0)				//�C��̎��񎞂̊O���]��.
#define LASER_NOR_SHOT_RESET			(300)			//�C��̔��˃��Z�b�g����.
#define LASER_NOR_SHOT_START			(20)			//�C��̔��ˊJ�n����.
#define LASER_NOR_SHOT_SPAN				(5)				//�C��̔��ˊԊu����.

#define LASER_NOR_FLASH_MAX				(30)            //�ő�t���b�V���G�t�F�N�g��
#define LASER_NOR_FLASH_SIZE_INIT		(3.0f)          //�t���b�V���G�t�F�N�g�̏����T�C�Y.
#define LASER_NOR_FLASH_SIZE_SPREAD		(-7)            //�t���b�V���G�t�F�N�g�̊g���.
#define LASER_NOR_FLASH_VALID_TM		(100)           //�t���b�V���G�t�F�N�g�̎����t���[��.
#define LASER_NOR_FLASH_ALPHA_TM		(2)             //�t���b�V���G�t�F�N�g�̓��������x.
#define LASER_NOR_PRE_LASER1_SIZE		(50)            //���ˑO�G�t�F�N�g1�̃T�C�Y.
#define LASER_NOR_PRE_LASER2_SIZE		(20)            //���ˑO�G�t�F�N�g2�̃T�C�Y.

//��Q��: ���O���[�U�[.
#define LASER_STR_SPAWN_SPAN			(350)			//�������[�U�[�̏o���Ԋu.
#define LASER_STR_PREDICTION_TIME		(60)			//�������[�U�[�̗\�����̏o�鎞��.

//��Q��: 覐�.
#define METEOR_CNT_MAX					(50)			//覐΂̍ő�o����.
#define METEOR_SPAWN_SPAN				(150)			//覐΂̏o�����ԊԊu.
#define METEOR_SPEED					(2)				//�ړ����x.
#define METEOR_DEST_OUT_DIS				(50)			//覐΂���ʊO�ŏ����鋗��.
#define METEOR_DEST_TIME				(20)			//覐΂̔j�󎞊�.
#define METEOR_GOAL_RAND_RANGE			(500)			//覐΂̖ڕW�n�_�̗����͈�.
#define METEOR_BREAK_ANIM_TIME			(50)			//覐Δj��j�Ђ̃A�j������.
#define METEOR_BREAK_ANIM_CNT			(10)			//覐Δj��j�Ђ̐�.

#define METEOR_LINE_CNT_MIN				(5)				//�Œ�n�p�`.
#define METEOR_LINE_CNT_MAX				(16)			//�ő�n�p�`.
#define METEOR_LINE_DIS_MIN				(40)			//���_�̍ŒZ����.
#define METEOR_LINE_DIS_MAX				(60)			//���_�̍ő勗��.

//��Q��: �g��.
#define RIPPLES_FLASH_MAX				(30)            //�ő�t���b�V���G�t�F�N�g��
#define RIPPLES_FLASH_SIZE_INIT			(5.0f)          //�t���b�V���G�t�F�N�g�̏����T�C�Y.
#define RIPPLES_FLASH_SIZE_SPREAD		(3)             //�t���b�V���G�t�F�N�g�̊g���.
#define RIPPLES_FLASH_BLINK_TM			(15.0f)         //�t���b�V���G�t�F�N�g�̓_�Ŏ���.
#define RIPPLES_FLASH_VALID_TM			(50)            //�t���b�V���G�t�F�N�g�̎����t���[��.
#define RIPPLES_FLASH_ALPHA_TM			(2)             //�t���b�V���G�t�F�N�g�̓��������x.
#define RIPPLES_STATE_WARNING			(0)				//�\�����.
#define RIPPLES_STATE_ACTIVE			(1)				//�A�N�e�B�u���.
#define RIPPLES_WARNING_DURATION		(120.0f)		//�\���̎���.
#define RIPPLES_ACTIVE_DURATION			(60.0f)			//�A�N�e�B�u�̎���.
#define RIPPLES_SPAWN_SPAN				(350)			//�o���Ԋu.
#define RIPPLES_MAX_SIMULTANEOUS		(3)				//�ő哯���o����.
#define RIPPLES_MIN_DISTANCE			(100)			//�ŏ�����.

//��Q��: �ԉ�.
#define FIREWORKS_CNT_MAX				(10)			//�ő哯���o����
#define FIREWORKS_RND_MAX				(2)				//�ԉΏo���ő吔
#define FIREWORKS_SPAWN_SPAN			(600)			//�ԉΐ����Ԋu�i�t���[���j
#define FIREWORKS_WARNING_DURATION		(120)			//�\�����o�������i�t���[���j
#define FIREWORKS_LAUNCH_HEIGHT			(50)			//�ł��グ���x
#define FIREWORKS_EXPLOSION_RADIUS		(100)			//�������a
#define FIREWORKS_SPARKS_COUNT			(16)			//�ΉԂ̐��i�x�[�X�j
#define FIREWORKS_MIN_DISTANCE			(120)			//�ԉΓ��m�̍ŏ�����
#define FIREWORKS_GRAVITY				(0.3f)			//�d�͉����x

//�G�t�F�N�g.
#define EFFECT_MAX						(50)			//�G�t�F�N�g�̍ő�o����.

//�X�R�A.
#define SCORE_TAKE_ITEM					(100)			//�A�C�e������������̃X�R�A.
#define SCORE_BREAK_METEO				(500)			//覐΂��󂵂����̃X�R�A.
#define SCORE_ANIM_TIME					(50)			//�X�R�A�̃A�j���[�V��������.

//�J���[.
#define COLOR_PLY_REFLECT				(GetColor(255, 155, 255))
#define COLOR_PLY_DEBUG					(GetColor(255, 150, 150))
#define COLOR_PLY_AFT_NOR				(GetColor(105, 105, 105))	//�v���C���[�̎c���F(�ʏ�)
#define COLOR_PLY_AFT_REF				(GetColor(255,   0, 255))	//�v���C���[�̎c���F(����)
#define COLOR_ITEM						(GetColor( 60, 255,  60))
#define COLOR_PRE_EFFECT				(GetColor(128, 128, 128))                              //�\�����o.
#define COLOR_METEO(pos)				(GetColor(0, _int_r(255 * fabs(sin(pos.x/200))), 255)) //覐�.
#define COLOR_BEST_SCORE				(0x20F7DE)
#define COLOR_SCORE						(0x00FFA0)
#define COLOR_TIME						(0x80FF9C)

#endif