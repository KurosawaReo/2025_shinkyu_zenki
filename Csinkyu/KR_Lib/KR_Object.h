/*
   - KR_Object.h - (DxLib)
   ver: 2025/08/25

   �I�u�W�F�N�g��ǉ����܂�, �p�����Ďg�����Ƃ��ł�.
   Draw, Calc, Input�̈ꕔ�@�\���I�u�W�F�N�g�w���Ŏg���܂�.
*/
#pragma once

/*
   [�摜�ɂ���]

   DrawImg�Łu=�v���Z�q���֎~�ɂ��Ă邽��
   Object�̃����o�ɓ�����Object���̂��u=�v���Z�q���g���Ȃ��Ȃ�.

   ���̂��߁A�O������|�C���^�ő���������g���Ă���.
*/

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	class DrawImg; //�O���錾.

	//�I�u�W�F�N�g[�p���K�{]
	class Object
	{
	public:
		DBL_XY  offset{};   //�摜�����炷��.
		bool    isActive{}; //�L�����ǂ���.

	protected:
		//constructor.
		Object() : isActive(true) {}
	};

	//�I�u�W�F�N�g(�~)
	class ObjectCir : public Object
	{
	public:
		Circle cir{}; //�����蔻��ƍ��W.

		//constructor.
		ObjectCir() : Object() {
			cir.r     = 10;       //�f�t�H���g���a.
			cir.color = 0xFFFFFF; //�f�t�H���g�F.
		}

		//�����蔻��(Calc�̋@�\)
		bool   HitCheckCir   (const Circle* cir);
		bool   HitCheckBox   (const Box*    box);
		bool   HitCheckLine  (const Line*   line);
		//�v�Z(Calc�̋@�\)
		void   FixPosInArea  (int left, int up, int right, int down);
		bool   IsOutInArea   (int left, int up, int right, int down, bool isCompOut);
		double CalcDist      (DBL_XY pos);
		DBL_XY CalcArcPos    (double ang, double len);
		double CalcFacingAng (DBL_XY targetPos);
		//����(Input�̋@�\)
		void   MoveKey4Dir   (float speed);
		void   MovePad4Dir   (float speed);
		void   MovePadStick  (float speed);
		void   MoveMousePos  (bool isValidX = true, bool isValidY = true);
		//�`��(Draw�̋@�\)
		int    DrawShape     (bool isFill = true, bool isAnti = false);
		int    DrawGraph     (DrawImg* img, DBL_XY sizeRate = {1.0, 1.0});
	};

	//�I�u�W�F�N�g(�l�p�`)
	class ObjectBox : public Object
	{
	public:
		Box box{}; //�����蔻��ƍ��W.

		//constructor.
		ObjectBox() : Object() {
			box.size  = {20, 20}; //�f�t�H���g�T�C�Y.
			box.color = 0xFFFFFF; //�f�t�H���g�F.
		}

		//�����蔻��(Calc�̋@�\)
		bool   HitCheckCir   (const Circle* cir);
		bool   HitCheckBox   (const Box* box);
		//�v�Z(Calc�̋@�\)
		void   FixPosInArea  (int left, int up, int right, int down);
		bool   IsOutInArea   (int left, int up, int right, int down, bool isCompOut);
		double CalcDist      (DBL_XY pos);
		DBL_XY CalcArcPos    (double ang, double len);
		double CalcFacingAng (DBL_XY targetPos);
		//����(Input�̋@�\)
		void   MoveKey4Dir   (float speed);
		void   MovePad4Dir   (float speed);
		void   MovePadStick  (float speed);
		void   MoveMousePos  (bool isValidX = true, bool isValidY = true);
		//�`��(Draw�̋@�\)
		int    DrawShape     (bool isFill = true, bool isAnti = false);
		int    DrawGraph     (DrawImg* img, DBL_XY sizeRate = {1.0, 1.0});
	};

	//�I�u�W�F�N�g(�O���b�h���p)
	class ObjectGrid : public Object
	{
	public:
		INT_XY pos{}; //���W.

		//constructor.
		ObjectGrid() : Object()	{}
		//�`��.
		int Draw(DrawImg* img, INT_XY gridPos, INT_XY gridSize);
	};
}