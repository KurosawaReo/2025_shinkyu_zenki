/*
   - KR_Input.h - (kurosawa original)
   ver: 2025/08/23

   DxLib用の入力操作機能.
*/
#pragma once

//KR_Libに使う用.
namespace KR_Lib
{
	//キーボードID.
	enum KeyID
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
	//マウスID.
	enum MouseID
	{
		MOUSE_L, //0x0001: Left.
		MOUSE_R, //0x0002: Right.
		MOUSE_M, //0x0004: Middle.
	};
	//コントローラボタンID(xbox基準)
	enum PadXboxID
	{
		PAD_XBOX_DOWN,		//0x0001
		PAD_XBOX_LEFT,		//0x0002
		PAD_XBOX_RIGHT,		//0x0004
		PAD_XBOX_UP,		//0x0008
		PAD_XBOX_A,			//0x0010: 下のボタン.
		PAD_XBOX_B,			//0x0020: 右のボタン.
		PAD_XBOX_X,			//0x0040: 左のボタン.
		PAD_XBOX_Y,			//0x0080: 上のボタン.
		PAD_XBOX_L,			//0x0100
		PAD_XBOX_R,			//0x0200
		PAD_XBOX_VIEW,		//0x0400
		PAD_XBOX_MENU,		//0x0800
		PAD_XBOX_STICK_L,   //0x1000: 左スティック押し込み.
		PAD_XBOX_STICK_R,   //0x2000: 右スティック押し込み.
	};
	//コントローラボタンID(switch基準)
	enum PadSwitchID
	{
		PAD_SWT_DOWN,		//0x00001
		PAD_SWT_LEFT,		//0x00002
		PAD_SWT_RIGHT,		//0x00004
		PAD_SWT_UP,			//0x00008
		PAD_SWT_B,			//0x00010: 下のボタン.
		PAD_SWT_A,			//0x00020: 右のボタン.
		PAD_SWT_Y,			//0x00040: 左のボタン.
		PAD_SWT_X,			//0x00080: 上のボタン.
		PAD_SWT_L,			//0x00100
		PAD_SWT_R,			//0x00200
		PAD_SWT_ZL,			//0x00400
		PAD_SWT_ZR,			//0x00800
		PAD_SWT_MINUS,		//0x01000: -ボタン.
		PAD_SWT_PLUS,		//0x02000: +ボタン.
		PAD_SWT_STICK_L,	//0x04000: 左スティック押し込み.
		PAD_SWT_STICK_R,	//0x08000: 右スティック押し込み.
		PAD_SWT_HOME,		//0x10000: ホームボタン.
		PAD_SWT_CAPTURE,	//0x20000: キャプチャーボタン.
	};

	//キーやボタンの種類の最大数(変更禁止)
	constexpr int KEY_MAX     = 256;
	constexpr int MOUSE_MAX   = 3;
	constexpr int PAD_BTN_MAX = 32;

	//入力管理クラス.
	class Input
	{
	private: //実体.
		static Input inst; //自身のインスタンス.

	private: //データ.
		int tmKey   [KEY_MAX];     //キーを押している時間.
		int tmMouse [MOUSE_MAX];   //マウスを押下している時間.(bitフラグで管理)
		int tmPadBtn[PAD_BTN_MAX]; //コントローラボタンを押下している時間.(bitフラグで管理)

		INT_XY mPos;     //マウス座標.
		INT_XY stickVec; //スティック入力.

	public:
		//実体の取得.
		static Input* GetPtr() {
			return &inst;
		}

		//判定.
		bool   IsPushKey       (KeyID id);
		int    IsPushKeyTime   (KeyID id);
		bool   IsPushMouse     (MouseID id);
		int    IsPushMouseTime (MouseID id);
		bool   IsPushPadBtn    (PadXboxID   id);
		bool   IsPushPadBtn    (PadSwitchID id);
		int    IsPushPadBtnTime(PadXboxID   id);
		int    IsPushPadBtnTime(PadSwitchID id);

		//取得.
		void   GetMousePos     (DBL_XY* pos, bool isValidX = true, bool isValidY = true);
		void   GetPadStickVec  (DBL_XY* pos);

		//移動系.
		void   InputKey4Dir    (DBL_XY* pos, float speed);
		void   InputPad4Dir    (DBL_XY* pos, float speed);
		void   InputPadStick   (DBL_XY* pos, float speed);
		DBL_XY Move4Dir        (INT_XY  pow);

		//更新.
		void   UpdateKey();
		void   UpdateMouse();
		void   UpdatePad();
	};
}
