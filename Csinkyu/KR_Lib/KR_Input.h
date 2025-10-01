/*
   - KR_Input.h - (DxLib)
   ver: 2025/10/01

   ���͑���@�\��ǉ����܂��B
   (�I�u�W�F�N�g�w��ver �� KR_Object)
*/
#pragma once

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	//�L�[�{�[�hID.
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
		Esc   = KEY_INPUT_ESCAPE, //ESC�L�[.
		Space = KEY_INPUT_SPACE,
		Enter = KEY_INPUT_RETURN, //ENTER�L�[.
	};
	//�}�E�XID.
	enum class MouseID
	{
		Left,   //0x0001
		Right,  //0x0002
		Middle, //0x0004
	};
	//�R���g���[��ID(xbox�)
	enum class PadXboxID
	{
		Down,	//0x0001
		Left,	//0x0002
		Right,	//0x0004
		Up,		//0x0008
		A,		//0x0010: ���̃{�^��.
		B,		//0x0020: �E�̃{�^��.
		X,		//0x0040: ���̃{�^��.
		Y,		//0x0080: ��̃{�^��.
		L,		//0x0100
		R,		//0x0200
		View,	//0x0400
		Menu,	//0x0800
		StickL, //0x1000: ���X�e�B�b�N��������.
		StickR, //0x2000: �E�X�e�B�b�N��������.
	};
	//�R���g���[��ID(switch�)
	enum class PadSwitchID
	{
		Down,	 //0x00001
		Left,	 //0x00002
		Right,	 //0x00004
		Up,		 //0x00008
		B,		 //0x00010: ���̃{�^��.
		A,		 //0x00020: �E�̃{�^��.
		Y,		 //0x00040: ���̃{�^��.
		X,		 //0x00080: ��̃{�^��.
		L,		 //0x00100
		R,		 //0x00200
		ZL,		 //0x00400
		ZR,		 //0x00800
		Minus,	 //0x01000: -�{�^��.
		Plus,	 //0x02000: +�{�^��.
		StickL,	 //0x04000: ���X�e�B�b�N��������.
		StickR,	 //0x08000: �E�X�e�B�b�N��������.
		Home,	 //0x10000: �z�[���{�^��.
		Capture, //0x20000: �L���v�`���[�{�^��.
	};
	//�R���g���[��ID(�A�[�P�[�h➑�)
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
		Unknown1,  //�s��.
		BtnUpper3,
		Unknown2,  //�s��.
		BtnLower3,
		Unknown3,  //�s��.
		BtnStart,
	};
	//���̑��삩(Action�o�^�p)
	enum class InputType
	{
		Key,
		Mouse,
		PadXbox,
		PadSwitch,
		PadArcade
	};

	//���̓f�[�^(�P��)
	struct InputData
	{
		InputType type; //���̑��삩.
		int       id;   //����ID.
	};
	//�A�N�V�����f�[�^.
	struct ActionData
	{
		vector<InputData> inputs; //�o�^������̓f�[�^.
		int time;                 //���͎���.
	};

	//�L�[��{�^���̎�ނ̍ő吔(�ύX�֎~)
	constexpr int KEY_MAX     = 256;
	constexpr int MOUSE_MAX   = 3;
	constexpr int PAD_BTN_MAX = 32;

	//���͊Ǘ��N���X[�p���s��]
	class InputMng final
	{
	//�����̊֌W.
	public:
		//���̎擾�p.
		static InputMng& GetInst() {
			static InputMng inst; //���g�̃C���X�^���X.
			return inst;
		}
		//�g�p�֎~.
		InputMng(const InputMng&) = delete;
		InputMng& operator=(const InputMng&) = delete;
	private: 
		//constructor(�V�K�쐬���ł��Ȃ�����)
		InputMng(){}

	//���f�[�^.
	private:
		int tmKey   [KEY_MAX]{};     //�L�[�������Ă��鎞��.
		int tmMouse [MOUSE_MAX]{};   //�}�E�X���������Ă��鎞��.            (index: bit�t���O)
		int tmPadBtn[PAD_BTN_MAX]{}; //�R���g���[���{�^�����������Ă��鎞��.(index: bit�t���O)

		INT_XY mPos{};     //�}�E�X���W.
		INT_XY stickVec{}; //�X�e�B�b�N����.

		map<MY_STRING, ActionData> actions{}; //�A�N�V�����L�^�p.

	private: //�֐�.
		DBL_XY GetVector4Dir(INT_XY pow);

	public:

		//���씻��.
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

		//�A�N�V����.
		void   AddAction       (MY_STRING name, KeyID       id);
		void   AddAction       (MY_STRING name, MouseID     id);
		void   AddAction       (MY_STRING name, PadXboxID   id);
		void   AddAction       (MY_STRING name, PadSwitchID id);
		void   AddAction       (MY_STRING name, PadArcadeID id);

		//�ړ��n.
		void   MoveKey4Dir     (DBL_XY* pos, float speed);
		void   MovePad4Dir     (DBL_XY* pos, float speed);
		void   MovePadStick    (DBL_XY* pos, float speed);

		//�擾.
		DBL_XY GetMousePos     (bool isValidX = true, bool isValidY = true);
		DBL_XY GetPadStickXY   ();

		//�X�V.
		void   UpdateKey();
		void   UpdateMouse();
		void   UpdatePad();
		void   UpdateAction();
	};
	//����.
	static InputMng& InstInputMng = InputMng::GetInst();
}
