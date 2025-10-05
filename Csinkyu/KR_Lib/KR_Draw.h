/*
   - KR_Draw.h - (DxLib)
   ver: 2025/10/05

   �`��@�\��ǉ����܂��B
   (�I�u�W�F�N�g�w��ver �� KR_Object)
*/
#pragma once

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	//�t�H���g�^�C�vID(���͂��₷������p)
	enum class FontTypeID
	{
		Normal   = DX_FONTTYPE_NORMAL,
		Edge     = DX_FONTTYPE_EDGE,
		Anti     = DX_FONTTYPE_ANTIALIASING,      //�A���`�G�C���A�X(���炩�ɂȂ�)
		AntiEdge = DX_FONTTYPE_ANTIALIASING_EDGE, //�A���`�G�C���A�X & �G�b�W

		None     = -1, //�w��Ȃ�.
	};
	//�`�惂�[�hID(���͂��₷������p)
	enum class BlendModeID
	{
		None  = DX_BLENDMODE_NOBLEND, //�f�t�H���g.
		Alpha = DX_BLENDMODE_ALPHA,   //���u�����h.  (�d�Ȃ�Ɠ��߂���)
		Add   = DX_BLENDMODE_ADD,     //���Z�u�����h.(�d�Ȃ�Ɩ��x�����邭�Ȃ�)
		Sub   = DX_BLENDMODE_SUB,     //���Z�u�����h.(�d�Ȃ�Ɩ��x���Â��Ȃ�)
		Mul   = DX_BLENDMODE_MUL      //��Z�u�����h.
	};

	//�摜�f�[�^.
	struct Image
	{
		int    handle; //�n���h��.
		INT_XY size;   //�摜�̃T�C�Y.
	};
	//�A���J�[(�`��̊�_)
	enum Anchor
	{
		LU,	U,   RU, //��: Anchor::LU = Left Up.
		L,  Mid, R,
		DL,	D,   DR,
	};

	//�摜�`��N���X.
	class DrawImg
	{
	private:
		Image data{}; //�摜�f�[�^.

	public:
		//constructor, destructor.
		DrawImg();
		~DrawImg();
		//get.
		INT_XY GetSize() const { return data.size; }
		//�ǂݍ���.
		int LoadFile  (MY_STRING fileName);
		//�`��.
		int Draw      (DBL_XY pos,                                                    Anchor anc = Anchor::Mid, bool isTrans = true, bool isFloat = false);
		int DrawRect  (DBL_XY pos, int left, int up, int right, int down,             Anchor anc = Anchor::Mid, bool isTrans = true, bool isFloat = false);
		int DrawExtend(DBL_XY pos, DBL_XY sizeRate,                                   Anchor anc = Anchor::Mid, bool isTrans = true, bool isFloat = false);
		int DrawRota  (DBL_XY pos, double extend,  double ang, INT_XY pivot = {0, 0}, Anchor anc = Anchor::Mid, bool isTrans = true, bool isFloat = false);
		int DrawModi  (DBL_XY luPos, DBL_XY ruPos, DBL_XY rdPos, DBL_XY ldPos,                                  bool isTrans = true, bool isFloat = false);

		//�g�p�֎~(�u=�v�Ŏ��̂���������āA�Ӑ}�����f�X�g���N�^�����s�����̂�h������)
		DrawImg& operator=(const DrawImg&) = delete;
	};

	//�摜�`��N���X(�����ǂݍ���)
	class DrawDivImg
	{
	private:
		vector<Image> data{}; //�摜�f�[�^.

	public:
		//constructor, destructor.
		DrawDivImg();
		~DrawDivImg();
		//get.
		INT_XY GetSize(int imgNo) const { return data[imgNo].size; }
		//�ǂݍ���.
		int LoadFile  (MY_STRING fileName, INT_XY size, INT_XY cnt);
		//�`��.
		int Draw      (int imgNo, DBL_XY pos,                                                   Anchor anc = Anchor::Mid, bool isTrans = true, bool isFloat = false);
		int DrawRect  (int imgNo, DBL_XY pos, int left, int up, int right, int down,            Anchor anc = Anchor::Mid, bool isTrans = true, bool isFloat = false);
		int DrawExtend(int imgNo, DBL_XY pos, DBL_XY sizeRate,                                  Anchor anc = Anchor::Mid, bool isTrans = true, bool isFloat = false);
		int DrawRota  (int imgNo, DBL_XY pos, double extend, double ang, INT_XY pivot = {0, 0}, Anchor anc = Anchor::Mid, bool isTrans = true, bool isFloat = false);
		int DrawModi  (int imgNo, DBL_XY luPos, DBL_XY ruPos, DBL_XY rdPos, DBL_XY ldPos,                                 bool isTrans = true, bool isFloat = false);

		//�g�p�֎~(�u=�v�Ŏ��̂���������āA�Ӑ}�����f�X�g���N�^�����s�����̂�h������)
		DrawDivImg& operator=(const DrawDivImg&) = delete;
	};

	//�e�L�X�g�`��N���X.
	class DrawStr
	{
	public:
		MY_STRING text;  //�e�L�X�g.
		INT_XY    pos;   //��ʂ̂ǂ��ɕ`�悷�邩.
		MY_COLOR  color; //�����̐F.

		//constructor.
		DrawStr(MY_STRING _text, INT_XY _pos, MY_COLOR _color) : text(_text), pos(_pos), color(_color) {}

		//�`��.
		int    Draw	   (Anchor anc = Anchor::Mid, int font = -1);
		int    DrawRota(INT_XY extend, INT_XY pivot, double ang, bool isVertical, int font = -1);
		int    DrawModi(INT_XY luPos, INT_XY ruPos, INT_XY rdPos, INT_XY ldPos, bool isVertical, int font = -1);
		//���̑�.
		INT_XY GetTextSize(int font = -1);
	};

	//�t�H���g�N���X.
	class Font
	{
	private:
		int handle;

	public:
		//constructor, destructor.
		Font();
		~Font();
		//get.
		int GetFont() const { return handle; }
		//�t�H���g�쐬.
		void CreateFontH(MY_STRING fontName, int size, int thick, FontTypeID fontId = FontTypeID::None);

		//�g�p�֎~(�u=�v�Ŏ��̂���������āA�Ӑ}�����f�X�g���N�^�����s�����̂�h������)
		Font& operator=(const Font&) = delete;
	};

	//�O���f�[�V������.
	class GradLine
	{
	private:
		vector<VERTEX2D> points; //���_�f�[�^.

	public:
		//���_�ǉ�.
		void AddPoint(DBL_XY pos, MY_COLOR color);
		//�`��.
		void Draw(bool isClose = false);
	};

	//�}�`.
	int    DrawCircleKR		 (const Circle*   data,                           bool isFill = true, bool isAnti = false, float thick = 1.0f);
	int    DrawBoxKR		 (const Box*      data, Anchor anc = Anchor::Mid, bool isFill = true, bool isAnti = false);
	int    DrawTriangleKR	 (const Triangle* data,                           bool isFill = true, bool isAnti = false, float thick = 1.0f);
	int    DrawLineKR		 (const Line*     data,                                               bool isAnti = false, float thick = 1.0f);
	int    DrawPieKR		 (const Pie* pie,                                                     bool isAnti = false, float thick = 1.0f);
	int    DrawArcKR		 (const Pie* pie,                                                     bool isAnti = false, float thick = 1.0f);
	int    DrawWindowGrid	 (int wid, int hei, int size, MY_COLOR clrWid = {160, 160, 255}, MY_COLOR clrHei = {255, 160, 160});

	//�`�惂�[�h.
	int    SetDrawBlendModeKR(BlendModeID id, int    power = 255);
	int    SetDrawBlendModeKR(BlendModeID id, double power = 255);
	int    ResetDrawBlendMode();
}