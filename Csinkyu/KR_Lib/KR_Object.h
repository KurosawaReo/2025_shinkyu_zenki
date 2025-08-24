/*
   - KR_Object.h - (DxLib)
   ver: 2025/08/24

   �I�u�W�F�N�g��ǉ����܂�, �p�����Ďg�����Ƃ��ł�.
   Draw, Calc�̈ꕔ�@�\���I�u�W�F�N�g�w���Ŏg���܂�.
*/
#pragma once

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	//�I�u�W�F�N�g[�p���K�{]
	class Object
	{
	public:
		DrawImg img{};      //�摜.
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
		ObjectCir() : Object() {}

		//�����蔻��(Calc�̋@�\)
		bool   HitCheckCircle(const Circle* cir);
		bool   HitCheckLine  (const Line*   line);
		//�v�Z(Calc�̋@�\)
		void   FixPosInArea  (int left, int up, int right, int down);
		bool   IsOutInArea   (int left, int up, int right, int down, bool isCompOut);
		double CalcDist      (DBL_XY pos);
		DBL_XY CalcArcPos    (double ang, double len);
		double CalcFacingAng (DBL_XY targetPos);
		//�`��(Draw�̋@�\)
		int    Draw          (bool isDrawHit = false);
	};

	//�I�u�W�F�N�g(�l�p�`)
	class ObjectBox : public Object
	{
	public:
		Box box{}; //�����蔻��ƍ��W.

		//constructor.
		ObjectBox() : Object() {}

		//�����蔻��(Calc�̋@�\)
		bool   HitCheckBox  (const Box* box);
		//�v�Z(Calc�̋@�\)
		void   FixPosInArea (int left, int up, int right, int down);
		bool   IsOutInArea  (int left, int up, int right, int down, bool isCompOut);
		double CalcDist     (DBL_XY pos);
		DBL_XY CalcArcPos   (double ang, double len);
		double CalcFacingAng(DBL_XY targetPos);
		//�`��(Draw�̋@�\)
		int    Draw         (bool isDrawHit = false);
	};

	//�I�u�W�F�N�g(�O���b�h���p)
	class ObjectGrid : public Object
	{
	public:
		INT_XY pos{}; //���W.

		//constructor.
		ObjectGrid() : Object()	{}
		//�`��.
		int Draw(INT_XY gridPos, INT_XY gridSize);
	};
}