/*
   - KR_Calc.h - (DxLib)
   ver: 2025/09/11

   �v�Z�@�\��ǉ����܂��B
   (�I�u�W�F�N�g�w��ver �� KR_Object)
*/
#pragma once

//�p�x�ϊ��p.
#define _rad(x) (x)*(M_PI/180)
#define _deg(x) (x)*(180/M_PI)

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	//�v�Z�p�̊֐��Q.
	namespace Calc
	{
		//�����蔻��.
		bool		HitCirCir		(const Circle* cir1, const Circle* cir2);
		bool		HitBoxBox		(const Box*    box1, const Box*    box2);
		bool		HitBoxCir		(const Box*    box,  const Circle* cir);
		bool		HitLineCir		(const Line*   line, const Circle* cir);

		//�͈͌��E.
		void		FixPosInArea	(DBL_XY* pos, INT_XY size, int left, int up, int right, int down);
		bool		IsOutInArea		(DBL_XY  pos, INT_XY size, int left, int up, int right, int down, bool isCompOut);

		//�v�Z(���W,�p�x,����,�x�N�g��)
		double		CalcDist		(INT_XY pos1,  INT_XY pos2);
		double		CalcDist		(DBL_XY pos1,  DBL_XY pos2);
		DBL_XY		CalcMidPos		(DBL_XY pos1,  DBL_XY pos2);
		DBL_XY		CalcArcPos		(DBL_XY pos, double ang, double len);
		double		CalcFacingAng	(DBL_XY from, DBL_XY to);
		DBL_XY		CalcVectorDeg	(double deg);
		DBL_XY		CalcVectorRad	(double rad);

		//�l�̋Ȑ��ϓ�(�A�j���[�V�����p)
		double		CalcNumEaseIn	(double time);
		double		CalcNumEaseOut	(double time);
		double		CalcNumEaseInOut(double time);
		double		CalcNumWaveLoop	(double time);

		//�l�̑���.
		int         RandNum			(int st, int ed,            bool isDxRand = false);
		vector<int> RandNums		(int st, int ed, int count, bool isDxRand = false);
		double      GetDecimal		(double num);

		//<T> �l������������z���Ȃ��悤�ɂ���.
		template<typename T, _type_num_only(T)>
		T ClampNum(T num, T low, T high) {
			return max(low, min(num, high));
		}
	};
}