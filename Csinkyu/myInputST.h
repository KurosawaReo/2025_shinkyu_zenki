/*
   - myInputST.h - (original)
   ver.2025/07/23

   DxLib: オリジナル入力機能の追加.
*/
#pragma once

//キーID(入力しやすくする用)
enum KEY_ID
{
	KEY_DOWN  = KEY_INPUT_DOWN,
	KEY_LEFT  = KEY_INPUT_LEFT,
	KEY_RIGHT = KEY_INPUT_RIGHT,
	KEY_UP    = KEY_INPUT_UP,
	KEY_0     = KEY_INPUT_0,
	KEY_1     = KEY_INPUT_1,
	KEY_2     = KEY_INPUT_2,
	KEY_3     = KEY_INPUT_3,
	KEY_4     = KEY_INPUT_4,
	KEY_5     = KEY_INPUT_5,
	KEY_6     = KEY_INPUT_6,
	KEY_7     = KEY_INPUT_7,
	KEY_8     = KEY_INPUT_8,
	KEY_9     = KEY_INPUT_9,
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
	KEY_ENTER = KEY_INPUT_RETURN, //Enterキー.
};
//マウスID(入力しやすくする用)
enum MOUSE_ID
{
	MOUSE_L = MOUSE_INPUT_LEFT,   //Left.
	MOUSE_R = MOUSE_INPUT_RIGHT,  //Right.
	MOUSE_M = MOUSE_INPUT_MIDDLE, //Middle.
};
//コントローラボタンID(入力しやすくする用)
enum PAD_BTN_ID
{
	//DxLibの定数とは違うため直指定(xboxコントローラ基準)
	PAD_BTN_DOWN  = 0x0001,
	PAD_BTN_LEFT  = 0x0002,
	PAD_BTN_RIGHT = 0x0004,
	PAD_BTN_UP    = 0x0008,
	PAD_BTN_A     = 0x0010,
	PAD_BTN_B     = 0x0020,
	PAD_BTN_X     = 0x0040,
	PAD_BTN_Y     = 0x0080,
	PAD_BTN_L     = 0x0100,
	PAD_BTN_R     = 0x0200,
	PAD_BTN_VIEW  = 0x0400,
	PAD_BTN_MENU  = 0x0800,
	PAD_STICK_L   = 0x1000, //左スティック押し込み.
	PAD_STICK_R   = 0x2000, //右スティック押し込み.
};

//キーやボタンの種類の最大数(変更禁止)
#define KEY_MAX     (256)
#define MOUSE_MAX   (3)
#define PAD_BTN_MAX (32)

//入力管理クラス.
class InputST
{
private: //実体.
	static InputST self; //自身の実体.

private: //データ.
	int tmKey   [KEY_MAX];     //キーを押している時間.
	int tmMouse [MOUSE_MAX];   //マウスを押下している時間.(bitフラグで管理)
	int tmPadBtn[PAD_BTN_MAX]; //コントローラボタンを押下している時間.(bitフラグで管理)

	INT_XY mPos;     //マウス座標.
	INT_XY stickVec; //スティック入力.

public:
	//実体の取得.
	static InputST* GetPtr() {
		return &self;
	}

	//判定.
	BOOL   IsPushKey       (KEY_ID id);
	int    IsPushKeyTime   (KEY_ID id);
	BOOL   IsPushMouse     (MOUSE_ID id);
	int    IsPushMouseTime (MOUSE_ID id);
	BOOL   IsPushPadBtn    (PAD_BTN_ID id);
	int    IsPushPadBtnTime(PAD_BTN_ID id);

	//取得.
	void   GetMousePos     (DBL_XY* pos, BOOL isValidX = TRUE, BOOL isValidY = TRUE);
	void   GetPadStickVec  (DBL_XY* pos);

	//移動系.
	void   InputKey4Dir    (DBL_XY* pos, float speed);
	void   InputPad4Dir    (DBL_XY* pos, float speed);
	void   InputPadStick   (DBL_XY* pos, float speed);
	DBL_XY Move4Dir        (INT_XY  pow);

	void   FixPosInArea    (DBL_XY* pos, INT_XY size, int left, int up, int right, int down);
	BOOL   IsOutInArea     (DBL_XY  pos, INT_XY size, int left, int up, int right, int down);

	//更新.
	void   UpdateKey();
	void   UpdateMouse();
	void   UpdatePad();
};