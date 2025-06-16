/*
   - myInputST.h - (original)
   ver.2025/06/15

   DxLib�Ŏg���p�̃I���W�i�����͊֐�.
*/
#pragma once

//�L�[ID(�s���Ȓl����͂ł��Ȃ��悤��)
enum KEY_ID
{
	KEY_LEFT  = KEY_INPUT_LEFT,
	KEY_UP    = KEY_INPUT_UP,
	KEY_RIGHT = KEY_INPUT_RIGHT,
	KEY_DOWN  = KEY_INPUT_DOWN,
	KEY_A     = KEY_INPUT_A,
	KEY_B     = KEY_INPUT_B,
	KEY_C     = KEY_INPUT_C,
	KEY_D     = KEY_INPUT_D,
	KEY_E     = KEY_INPUT_E,
	KEY_F     = KEY_INPUT_F,
	KEY_G     = KEY_INPUT_G,
	KEY_H     = KEY_INPUT_H,
	KEY_I     = KEY_INPUT_I,
	KEY_J     = KEY_INPUT_J,
	KEY_K     = KEY_INPUT_K,
	KEY_L     = KEY_INPUT_L,
	KEY_M     = KEY_INPUT_M,
	KEY_N     = KEY_INPUT_N,
	KEY_O     = KEY_INPUT_O,
	KEY_P     = KEY_INPUT_P,
	KEY_Q     = KEY_INPUT_Q,
	KEY_R     = KEY_INPUT_R,
	KEY_S     = KEY_INPUT_S,
	KEY_T     = KEY_INPUT_T,
	KEY_U     = KEY_INPUT_U,
	KEY_V     = KEY_INPUT_V,
	KEY_W     = KEY_INPUT_W,
	KEY_X     = KEY_INPUT_X,
	KEY_Y     = KEY_INPUT_Y,
	KEY_Z     = KEY_INPUT_Z,
	KEY_SPACE = KEY_INPUT_SPACE,
	KEY_ENTER = KEY_INPUT_RETURN, //Enter�L�[.
};
//�}�E�XID(�s���Ȓl����͂ł��Ȃ��悤��)
enum MOUSE_ID
{
	MOUSE_L = MOUSE_INPUT_LEFT,   //Left.
	MOUSE_R = MOUSE_INPUT_RIGHT,  //Right.
	MOUSE_M = MOUSE_INPUT_MIDDLE, //Middle.
};
//�R���g���[���{�^��ID(�s���Ȓl����͂ł��Ȃ��悤��)
enum PAD_BTN_ID
{
	PAD_BTN_LEFT  = PAD_INPUT_LEFT,
	PAD_BTN_UP    = PAD_INPUT_UP,
	PAD_BTN_RIGHT = PAD_INPUT_RIGHT,
	PAD_BTN_DOWN  = PAD_INPUT_DOWN,
	PAD_BTN_A     = PAD_INPUT_A,
	PAD_BTN_B     = PAD_INPUT_B,
	PAD_BTN_X     = PAD_INPUT_X,
	PAD_BTN_Y     = PAD_INPUT_Y,
};

//�L�[��{�^���̎�ނ̍ő吔(�ύX�֎~)
#define KEY_MAX     (256)
#define MOUSE_MAX   (3)
#define PAD_BTN_MAX (32)

//���͊Ǘ��N���X.
class InputST
{
private: //����.
	static InputST self; //���g�̎���.

private: //�f�[�^.
	int tmKey   [KEY_MAX];     //�L�[�������Ă��鎞��.
	int tmMouse [MOUSE_MAX];   //�}�E�X���������Ă��鎞��.(bit�t���O�ŊǗ�)
	int tmPadBtn[PAD_BTN_MAX]; //�R���g���[���{�^�����������Ă��鎞��.(bit�t���O�ŊǗ�)

	INT_XY mPos; //�}�E�X���W.

public:
	//���̂̎擾.
	static InputST* GetPtr() {
		return &self;
	}

	//����.
	BOOL   IsPushKey       (KEY_ID id);
	int    IsPushKeyTime   (KEY_ID id);
	BOOL   IsPushMouse     (MOUSE_ID id);
	int    IsPushMouseTime (MOUSE_ID id);
	BOOL   IsPushPadBtn    (PAD_BTN_ID id);
	int    IsPushPadBtnTime(PAD_BTN_ID id);

	//�擾.
	void   GetMousePos     (DBL_XY* pos, BOOL isValidX = TRUE, BOOL isValidY = TRUE);
	void   GetPadStick     ();

	//�ړ��n.
	void   InputKey4Dir    (DBL_XY* pos, float speed);
	void   InputPad4Dir    (DBL_XY* pos, float speed);
	DBL_XY Move4Dir        (INT_XY  pow);

	void   FixPosInArea    (DBL_XY* pos, INT_XY size, int left, int up, int right, int down);

	//�X�V.
	void   UpdateKey();
	void   UpdateMouse();
	void   UpdatePadBtn();
};