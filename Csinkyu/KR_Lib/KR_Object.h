/*
   - KR_Object.h - (DxLib)
   ver: 2025/08/24

   オブジェクトを追加します, 継承して使うことも可です.
   Draw, Calcの一部機能をオブジェクト指向で使えます.
*/
#pragma once

//KR_Libに使う用.
namespace KR_Lib
{
	//オブジェクト[継承必須]
	class Object
	{
	public:
		DrawImg img{};      //画像.
		DBL_XY  offset{};   //画像をずらす量.
		bool    isActive{}; //有効かどうか.

	protected:
		//constructor.
		Object() : isActive(true) {}
	};

	//オブジェクト(円)
	class ObjectCir : public Object
	{
	public:
		Circle cir{}; //当たり判定と座標.

		//constructor.
		ObjectCir() : Object() {}

		//当たり判定(Calcの機能)
		bool   HitCheckCircle(const Circle* cir);
		bool   HitCheckLine  (const Line*   line);
		//計算(Calcの機能)
		void   FixPosInArea  (int left, int up, int right, int down);
		bool   IsOutInArea   (int left, int up, int right, int down, bool isCompOut);
		double CalcDist      (DBL_XY pos);
		DBL_XY CalcArcPos    (double ang, double len);
		double CalcFacingAng (DBL_XY targetPos);
		//描画(Drawの機能)
		int    Draw          (bool isDrawHit = false);
	};

	//オブジェクト(四角形)
	class ObjectBox : public Object
	{
	public:
		Box box{}; //当たり判定と座標.

		//constructor.
		ObjectBox() : Object() {}

		//当たり判定(Calcの機能)
		bool   HitCheckBox  (const Box* box);
		//計算(Calcの機能)
		void   FixPosInArea (int left, int up, int right, int down);
		bool   IsOutInArea  (int left, int up, int right, int down, bool isCompOut);
		double CalcDist     (DBL_XY pos);
		DBL_XY CalcArcPos   (double ang, double len);
		double CalcFacingAng(DBL_XY targetPos);
		//描画(Drawの機能)
		int    Draw         (bool isDrawHit = false);
	};

	//オブジェクト(グリッド上専用)
	class ObjectGrid : public Object
	{
	public:
		INT_XY pos{}; //座標.

		//constructor.
		ObjectGrid() : Object()	{}
		//描画.
		int Draw(INT_XY gridPos, INT_XY gridSize);
	};
}