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

// - �񋓑� -
enum Scene
{
	SCENE_TITLE,
	SCENE_READY,
	SCENE_GAME,
	SCENE_END,
	SCENE_PAUSE, //�|�[�Y���.

	SCENE_COUNT, //����.
};
//���[�U�[�ړ���.
enum MoveDir
{
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN
};

// - �Q�[���f�[�^ -
struct GameData
{
	Scene scene;      //�V�[���̋L�^�p.
	int   stage;      //�X�e�[�W��.

	int   score;      //�X�R�A.
	int   scoreBef;   //�X�R�A(���ԉ��Z�O)
	int   bestScore;  //�x�X�g�X�R�A.
	int   level;	  //���x��.

	float spawnRate;  //��Q���̏o�����Ԋ���.
	float counter;    //�o�ߎ��ԃJ�E���^�[(�X���[�̉e�����󂯂�)

	int   font1;      //�t�H���g.
	int   font2;      //�t�H���g.
	int   font3;      //�t�H���g.
	int   font4;      //�t�H���g.

	bool  isSlow;     //�X���[���[�h���ǂ���.
};

// - Debug -
//��`����ƃf�o�b�O�\��ON.
//#define DEBUG_LASER_ACTIVE
//#define DEBUG_SPAWN_RATE

// - �萔 -
#define FILE_DATA_PATH	(_T("Data"))					//�f�[�^��ۑ�����ꏊ.
#define FILE_DATA		(_T("Data/score.data"))			//�f�[�^��ۑ�����t�@�C��.

#define IS_WINDOW_MODE					(FALSE)			//�E�B���h�E���[�h�ɂ��邩.

#define WINDOW_WID						(1920)			//�E�B���h�E�̉���.
#define WINDOW_HEI						(1080)			//�E�B���h�E�̏c��.
#define WINDOW_COLOR_BIT				(32)			//�E�B���h�E�̃J���[bit��.

#define FPS								(80)			//�t���[�����[�g.

#define SLOW_MODE_TIME					(8)             //�X���[���[�h��������.
#define SLOW_MODE_SPEED					(0.20f)			//�X���[���[�h���x�{��.

#define GAME_START_TIME					(1.0)			//�Q�[���J�n����܂ł̒x��.

#define LEVEL_UP_ANIM_TIME				(120)			//���x���A�b�v�A�j���[�V��������.

#define PLAYER_SIZE						(30)			//�v���C���[�T�C�Y.
#define PLAYER_MOVE_SPEED				(8)				//�v���C���[�ړ����x.
#define PLAYER_AFT_IMG_NUM				(7)             //�c���f�[�^�̐�.
#define PLAYER_DEATH_ANIM_TIME			(10)			//�v���C���[���S�A�j������.

#define ITEM_SIZE						(20)			//�A�C�e���T�C�Y.
#define ITEM_SPEED						(3)				//�A�C�e���ړ��X�s�[�h.  
#define ITEM_RESPAWN_TIME				(400)           //�A�C�e����������.

#define OBSTACLE2_SPAN					(80)			//��Q���̔��ˊԊu.
#define OBSTACLE2_SPEED					(3.0)			//��Q���̑��x.
#define	OBSTACLE2_ROT_MAX				(5.0)			//��Q���̒ǔ���(1�t���[���ŉ�]�ł���ő�x��)
#define OBSTACLE2_LIM_F					(80)			//�ő�ǐՃt���[����.

#define OBSTACLE4_OUTER_MARGIN			(0)				//�C��̎��񎞂̊O���]��.
#define OBSTACLE4_SHOT_RESET			(300)			//�C��̔��˃��Z�b�g����.
#define OBSTACLE4_SHOT_START			(20)			//�C��̔��ˊJ�n����.
#define OBSTACLE4_SHOT_SPAN				(5)				//�C��̔��ˊԊu����.

#define OBSTACLE4_FLASH_MAX				(30)            //�ő�t���b�V���G�t�F�N�g��
#define OBSTACLE4_FLASH_SIZE_INIT		(3.0f)          //�t���b�V���G�t�F�N�g�̏����T�C�Y.
#define OBSTACLE4_FLASH_SIZE_SPREAD		(-7)            //�t���b�V���G�t�F�N�g�̊g���.
#define OBSTACLE4_FLASH_VALID_TM		(100)           //�t���b�V���G�t�F�N�g�̎����t���[��.
#define OBSTACLE4_FLASH_ALPHA_TM		(2)             //�t���b�V���G�t�F�N�g�̓��������x.
#define OBSTACLE4_PRE_LASER1_SIZE		(50)            //���ˑO�G�t�F�N�g1�̃T�C�Y.
#define OBSTACLE4_PRE_LASER2_SIZE		(20)            //���ˑO�G�t�F�N�g2�̃T�C�Y.

#define OBSTACLE5_FLASH_MAX				(30)            //�ő�t���b�V���G�t�F�N�g��
#define OBSTACLE5_FLASH_SIZE_INIT		(5.0f)          //�t���b�V���G�t�F�N�g�̏����T�C�Y.
#define OBSTACLE5_FLASH_SIZE_SPREAD		(3)             //�t���b�V���G�t�F�N�g�̊g���.
#define OBSTACLE5_FLASH_BLINK_TM		(15.0f)         //�t���b�V���G�t�F�N�g�̓_�Ŏ���.
#define OBSTACLE5_FLASH_VALID_TM		(50)            //�t���b�V���G�t�F�N�g�̎����t���[��.
#define OBSTACLE5_FLASH_ALPHA_TM		(2)             //�t���b�V���G�t�F�N�g�̓��������x.
#define OBSTACLE5_STATE_WARNING			(0)				//�\�����.
#define OBSTACLE5_STATE_ACTIVE			(1)				//�A�N�e�B�u���.
#define OBSTACLE5_WARNING_DURATION		(120.0f)		//�\���̎���.
#define OBSTACLE5_ACTIVE_DURATION		(60.0f)			//�A�N�e�B�u�̎���.
#define OBSTACLE5_SPAWN_SPAN			(350)			//�o���Ԋu.
#define OBSTACLE5_MAX_SIMULTANEOUS		(3)				//�ő哯���o����.
#define OBSTACLE5_MIN_DISTANCE			(100)			//�ŏ�����.

#define MGL_LASER_SPAWN_SPAN			(350)			//�������[�U�[�̏o���Ԋu.
#define MGL_LASER_PREDICTION_TIME		(60)			//�������[�U�[�̗\�����̏o�鎞��.

//#define LASER_NOR_ROT_MAX				(0.1)			//���[�U�[(normal)   �̋Ȃ�����E�p�x.
#define LASER_REF_ROT_MAX				(10)			//���[�U�[(reflected)�̋Ȃ�����E�p�x.
#define LASER_REF_TRACK_ST_TM			(10)			//���[�U�[(reflected)�̒ǔ��J�n����.
#define LASER_REF_TRACK_ED_TM			(30)			//���[�U�[(reflected)�̒ǔ��I������.
#define LASER_NOR_SPEED					(0.1)		    //���[�U�[(normal)   �̑��x.
#define LASER_STR_SPEED					(50.0)		    //���[�U�[(straight) �̑��x.
#define LASER_REF_SPEED					(0.5)		    //���[�U�[(reflected)�̑��x.
#define LASER_CNT_MAX					(50)			//���[�U�[�̍ő吔.
#define LASER_LINE_CNT_MAX				(12000)			//���[�U�[�`����̍ő吔.
#define LASER_LINE_DRAW_LEN				(2)				//���[�U�[�`�����`���Œ�̒���(DrawLineAA�̊֌W��)
#define LASER_REF_ANIM_TIME				(20)			//���˃A�j���[�V��������.

#define METEO_CNT_MAX					(50)			//覐΂̍ő�o����.
#define METEO_SPAWN_SPAN				(150)			//覐΂̏o�����ԊԊu.
#define METEO_SPEED						(2)				//�ړ����x.
#define METEO_DEST_OUT_DIS				(50)			//覐΂���ʊO�ŏ����鋗��.
#define METEO_DEST_TIME					(20)			//覐΂̔j�󎞊�.
#define METEO_GOAL_RAND_RANGE			(500)			//覐΂̖ڕW�n�_�̗����͈�.
#define METEO_BREAK_ANIM_TIME			(50)			//覐Δj��j�Ђ̃A�j������.
#define METEO_BREAK_ANIM_CNT			(10)			//覐Δj��j�Ђ̐�.

#define METEO_LINE_CNT_MIN				(5)				//�Œ�n�p�`.
#define METEO_LINE_CNT_MAX				(16)			//�ő�n�p�`.
#define METEO_LINE_DIS_MIN				(40)			//���_�̍ŒZ����.
#define METEO_LINE_DIS_MAX				(60)			//���_�̍ő勗��.

#define EFFECT_MAX						(50)			//�G�t�F�N�g�̍ő�o����.

#define SCORE_TAKE_ITEM					(100)			//�A�C�e������������̃X�R�A.
#define SCORE_BREAK_METEO				(500)			//覐΂��󂵂����̃X�R�A.
#define SCORE_ANIM_TIME					(50)			//�X�R�A�̃A�j���[�V��������.

#define COLOR_PLY_REFLECT				(GetColor(255, 155, 255))
#define COLOR_PLY_DEBUG					(GetColor(255, 150, 150))
#define COLOR_PLY_AFT_NOR				(GetColor(105, 105, 105))	//�v���C���[�̎c���F(�ʏ�)
#define COLOR_PLY_AFT_REF				(GetColor(255,   0, 255))	//�v���C���[�̎c���F(����)
#define COLOR_ITEM						(GetColor( 60, 255,  60))
#define COLOR_PRE_LINE					(GetColor(128, 128, 128))                              //�\����.
#define COLOR_METEO(pos)				(GetColor(0, _int_r(255 * fabs(sin(pos.x/200))), 255)) //覐�.
#define COLOR_BEST_SCORE				(0x20F7DE)
#define COLOR_SCORE						(0x00FFA0)
#define COLOR_TIME						(0x80FF9C)

#endif