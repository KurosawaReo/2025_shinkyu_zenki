/*
   - KR_Calc.h - (DxLib)
   ver: 2025/12/17

   計算機能を追加。
*/
#pragma once
//KR_Globalが入ってなければここで導入.
#if !defined DEF_KR_DX_GLOBAL
  #include "KR_Global.h"
#endif

//角度変換用.
#define _rad(x) (x)*(M_PI/180)
#define _deg(x) (x)*(180/M_PI)

//KrLib名前空間.
namespace KR
{
	//計算用の関数群.
	namespace Calc
	{
		//当たり判定.
		bool		HitCirCir			(const Circle& cir1, const Circle& cir2);
		bool		HitBoxBox			(const Box&    box1, const Box&    box2);
		bool		HitBoxCir			(const Box&    box,  const Circle& cir);
		bool		HitLineCir			(const Line&   line, const Circle& cir);
		bool        HitPie				(const Pie&    pie,  DBL_XY pos);

		//範囲限界.
		void		FixPosInArea		(DBL_XY* pos, INT_XY size, DBL_RECT rect);
		bool		IsOutInArea			(DBL_XY  pos, INT_XY size, DBL_RECT rect, bool isCompOut);

		//計算(座標,角度,長さ,ベクトル)
		double		Dist				(INT_XY pos1,  INT_XY pos2);
		double		Dist				(DBL_XY pos1,  DBL_XY pos2);
		DBL_XY		MidPos				(DBL_XY pos1,  DBL_XY pos2);
		DBL_XY		ArcPos				(DBL_XY pos, double ang, double len);
		double		FacingAng			(DBL_XY from, DBL_XY to);
		DBL_XY		VectorDeg			(double deg);
		DBL_XY		VectorRad			(double rad);

		//物理系.
		void        PhysicsSpeedInertia	(double* speed, double maxSpeed, double accel, double fric);

		//値の曲線変動(アニメーション用)
		double		AnimEaseIn			(double time);
		double		AnimEaseOut			(double time);
		double		AnimEaseInOut		(double time);
		double      AnimEaseOutIn		(double time);
		double		AnimWaveLoop		(double time);

		//値の操作.
		int         RandNum				(int st, int ed, bool isDxRand = false);
		vector<int> RandNums			(int st, int ed, int count, bool isDxRand = false);
		double      GetDecimal			(double num);

		//<T> 数値の上限.
		template<typename T, _type_num_only(T)>
		void NumLimMax(T* _num, T _max) {
			*_num = min(*_num, _max);
		}
		//<T> 数値の下限.
		template<typename T, _type_num_only(T)>
		void NumLimMin(T* _num, T _min) {
			*_num = max(*_num, _min);
		}
		//<T> 数値の範囲.
		template<typename T, _type_num_only(T)>
		void NumLimRange(T* num, T low, T high) {
			*num = max(low, min(*num, high));
		}
	};
}