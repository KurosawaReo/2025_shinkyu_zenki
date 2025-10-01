/*
   - KR_Input.h - (DxLib)
   ver: 2025/10/01

   入力操作機能を追加します。
   (オブジェクト指向ver → KR_Object)
*/
#pragma once

//KR_Libに使う用.
namespace KR_Lib
{
	//キーボードID.
	enum class KeyID
	{
		Down  = KEY_INPUT_DOWN,
		Left  = KEY_INPUT_LEFT,
		Right = KEY_INPUT_RIGHT,
		Up    = KEY_INPUT_UP,
		Num0  = KEY_INPUT_0,
		Num1  = KEY_INPUT_1,
		Num2  = KEY_INPUT_2,
		Num3  = KEY_INPUT_3,
		Num4  = KEY_INPUT_4,
		Num5  = KEY_INPUT_5,
		Num6  = KEY_INPUT_6,
		Num7  = KEY_INPUT_7,
		Num8  = KEY_INPUT_8,
		Num9  = KEY_INPUT_9,
		A     = KEY_INPUT_A,
		B     = KEY_INPUT_B,
		C     = KEY_INPUT_C,
		D     = KEY_INPUT_D,
		E     = KEY_INPUT_E,
		F     = KEY_INPUT_F,
		G     = KEY_INPUT_G,
		H     = KEY_INPUT_H,
		I     = KEY_INPUT_I,
		J     = KEY_INPUT_J,
		K     = KEY_INPUT_K,
		L     = KEY_INPUT_L,
		M     = KEY_INPUT_M,
		N     = KEY_INPUT_N,
		O     = KEY_INPUT_O,
		P     = KEY_INPUT_P,
		Q     = KEY_INPUT_Q,
		R     = KEY_INPUT_R,
		S     = KEY_INPUT_S,
		T     = KEY_INPUT_T,
		U     = KEY_INPUT_U,
		V     = KEY_INPUT_V,
		W     = KEY_INPUT_W,
		X     = KEY_INPUT_X,
		Y     = KEY_INPUT_Y,
		Z     = KEY_INPUT_Z,
		Esc   = KEY_INPUT_ESCAPE, //ESCキー.
		Space = KEY_INPUT_SPACE,
		Enter = KEY_INPUT_RETURN, //ENTERキー.
	};
	//マウスID.
	enum class MouseID
	{
		Left,   //0x0001
		Right,  //0x0002
		Middle, //0x0004
	};
	//コントローラID(xbox基準)
	enum class PadXboxID
	{
		Down,	//0x0001
		Left,	//0x0002
		Right,	//0x0004
		Up,		//0x0008
		A,		//0x0010: 下のボタン.
		B,		//0x0020: 右のボタン.
		X,		//0x0040: 左のボタン.
		Y,		//0x0080: 上のボタン.
		L,		//0x0100
		R,		//0x0200
		View,	//0x0400
		Menu,	//0x0800
		StickL, //0x1000: 左スティック押し込み.
		StickR, //0x2000: 右スティック押し込み.
	};
	//コントローラID(switch基準)
	enum class PadSwitchID
	{
		Down,	 //0x00001
		Left,	 //0x00002
		Right,	 //0x00004
		Up,		 //0x00008
		B,		 //0x00010: 下のボタン.
		A,		 //0x00020: 右のボタン.
		Y,		 //0x00040: 左のボタン.
		X,		 //0x00080: 上のボタン.
		L,		 //0x00100
		R,		 //0x00200
		ZL,		 //0x00400
		ZR,		 //0x00800
		Minus,	 //0x01000: -ボタン.
		Plus,	 //0x02000: +ボタン.
		StickL,	 //0x04000: 左スティック押し込み.
		StickR,	 //0x08000: 右スティック押し込み.
		Home,	 //0x10000: ホームボタン.
		Capture, //0x20000: キャプチャーボタン.
	};
	//コントローラID(アーケード筐体)
	enum class PadArcadeID
	{
		Down,
		Left,
	    Right,
		Up,
		BtnUpper1,
		BtnLower1,
		BtnLower2,
		BtnUpper2,
		Unknown1,  //不明.
		BtnUpper3,
		Unknown2,  //不明.
		BtnLower3,
		Unknown3,  //不明.
		BtnStart,
	};
	//何の操作か(Action登録用)
	enum class InputType
	{
		Key,
		Mouse,
		PadXbox,
		PadSwitch,
		PadArcade
	};

	//入力データ(単体)
	struct InputData
	{
		InputType type; //何の操作か.
		int       id;   //操作ID.
	};
	//アクションデータ.
	struct ActionData
	{
		vector<InputData> inputs; //登録する入力データ.
		int time;                 //入力時間.
	};

	//キーやボタンの種類の最大数(変更禁止)
	constexpr int KEY_MAX     = 256;
	constexpr int MOUSE_MAX   = 3;
	constexpr int PAD_BTN_MAX = 32;

	//入力管理クラス[継承不可]
	class InputMng final
	{
	//▼実体関係.
	public:
		//実体取得用.
		static InputMng& GetInst() {
			static InputMng inst; //自身のインスタンス.
			return inst;
		}
		//使用禁止.
		InputMng(const InputMng&) = delete;
		InputMng& operator=(const InputMng&) = delete;
	private: 
		//constructor(新規作成をできなくする)
		InputMng(){}

	//▼データ.
	private:
		int tmKey   [KEY_MAX]{};     //キーを押している時間.
		int tmMouse [MOUSE_MAX]{};   //マウスを押下している時間.            (index: bitフラグ)
		int tmPadBtn[PAD_BTN_MAX]{}; //コントローラボタンを押下している時間.(index: bitフラグ)

		INT_XY mPos{};     //マウス座標.
		INT_XY stickVec{}; //スティック入力.

		map<MY_STRING, ActionData> actions{}; //アクション記録用.

	private: //関数.
		DBL_XY GetVector4Dir(INT_XY pow);

	public:

		//操作判定.
		bool   IsPushKey       (KeyID id);
		int    IsPushKeyTime   (KeyID id);
		bool   IsPushMouse     (MouseID id);
		int    IsPushMouseTime (MouseID id);
		bool   IsPushPadBtn    (PadXboxID   id);
		bool   IsPushPadBtn    (PadSwitchID id);
	    bool   IsPushPadBtn    (PadArcadeID id);
		int    IsPushPadBtnTime(PadXboxID   id);
		int    IsPushPadBtnTime(PadSwitchID id);
		int    IsPushPadBtnTime(PadArcadeID id);
		bool   IsPushAction    (MY_STRING name);
		int    IsPushActionTime(MY_STRING name);

		//アクション.
		void   AddAction       (MY_STRING name, KeyID       id);
		void   AddAction       (MY_STRING name, MouseID     id);
		void   AddAction       (MY_STRING name, PadXboxID   id);
		void   AddAction       (MY_STRING name, PadSwitchID id);
		void   AddAction       (MY_STRING name, PadArcadeID id);

		//移動系.
		void   MoveKey4Dir     (DBL_XY* pos, float speed);
		void   MovePad4Dir     (DBL_XY* pos, float speed);
		void   MovePadStick    (DBL_XY* pos, float speed);

		//取得.
		DBL_XY GetMousePos     (bool isValidX = true, bool isValidY = true);
		DBL_XY GetPadStickXY   ();

		//更新.
		void   UpdateKey();
		void   UpdateMouse();
		void   UpdatePad();
		void   UpdateAction();
	};
	//実体.
	static InputMng& InstInputMng = InputMng::GetInst();
}
