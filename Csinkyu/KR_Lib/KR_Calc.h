/*
   - KR_Calc.h - (DxLib)
   ver: 2025/09/11

   計算機能を追加します。
   (オブジェクト指向ver → KR_Object)
*/
#pragma once

//角度変換用.
#define _rad(x) (x)*(M_PI/180)
#define _deg(x) (x)*(180/M_PI)

//KR_Libに使う用.
namespace KR_Lib
{
	//計算用の関数群.
	namespace Calc
	{
		//当たり判定.
		bool		HitCirCir		(const Circle* cir1, const Circle* cir2);
		bool		HitBoxBox		(const Box*    box1, const Box*    box2);
		bool		HitBoxCir		(const Box*    box,  const Circle* cir);
		bool		HitLineCir		(const Line*   line, const Circle* cir);

		//範囲限界.
		void		FixPosInArea	(DBL_XY* pos, INT_XY size, int left, int up, int right, int down);
		bool		IsOutInArea		(DBL_XY  pos, INT_XY size, int left, int up, int right, int down, bool isCompOut);

		//計算(座標,角度,長さ,ベクトル)
		double		CalcDist		(INT_XY pos1,  INT_XY pos2);
		double		CalcDist		(DBL_XY pos1,  DBL_XY pos2);
		DBL_XY		CalcMidPos		(DBL_XY pos1,  DBL_XY pos2);
		DBL_XY		CalcArcPos		(DBL_XY pos, double ang, double len);
		double		CalcFacingAng	(DBL_XY from, DBL_XY to);
		DBL_XY		CalcVectorDeg	(double deg);
		DBL_XY		CalcVectorRad	(double rad);

		//値の曲線変動(アニメーション用)
		double		CalcNumEaseIn	(double time);
		double		CalcNumEaseOut	(double time);
		double		CalcNumEaseInOut(double time);
		double		CalcNumWaveLoop	(double time);

		//値の操作.
		int         RandNum			(int st, int ed,            bool isDxRand = false);
		vector<int> RandNums		(int st, int ed, int count, bool isDxRand = false);
		double      GetDecimal		(double num);

		//<T> 値が上限下限を越えないようにする.
		template<typename T, _type_num_only(T)>
		T ClampNum(T num, T low, T high) {
			return max(low, min(num, high));
		}
	};
}