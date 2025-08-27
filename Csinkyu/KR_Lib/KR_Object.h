/*
   - KR_Object.h - (DxLib)
   ver: 2025/08/25

   オブジェクトを追加します, 継承して使うことも可です.
   Draw, Calc, Inputの一部機能をオブジェクト指向で使えます.
*/
#pragma once

/*
   [画像について]

   DrawImgで「=」演算子を禁止にしてるため
   Objectのメンバに入れるとObject自体も「=」演算子が使えなくなる.

   そのため、外部からポインタで送る方式を使っている.
*/

//KR_Libに使う用.
namespace KR_Lib
{
	class DrawImg; //前方宣言.

	//オブジェクト[継承必須]
	class Object
	{
	public:
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
		ObjectCir() : Object() {
			cir.r     = 10;       //デフォルト半径.
			cir.color = 0xFFFFFF; //デフォルト色.
		}

		//当たり判定(Calcの機能)
		bool   HitCheckCir   (const Circle* cir);
		bool   HitCheckBox   (const Box*    box);
		bool   HitCheckLine  (const Line*   line);
		//計算(Calcの機能)
		void   FixPosInArea  (int left, int up, int right, int down);
		bool   IsOutInArea   (int left, int up, int right, int down, bool isCompOut);
		double CalcDist      (DBL_XY pos);
		DBL_XY CalcArcPos    (double ang, double len);
		double CalcFacingAng (DBL_XY targetPos);
		//操作(Inputの機能)
		void   MoveKey4Dir   (float speed);
		void   MovePad4Dir   (float speed);
		void   MovePadStick  (float speed);
		void   MoveMousePos  (bool isValidX = true, bool isValidY = true);
		//描画(Drawの機能)
		int    DrawShape     (bool isFill = true, bool isAnti = false);
		int    DrawGraph     (DrawImg* img, DBL_XY sizeRate = {1.0, 1.0});
	};

	//オブジェクト(四角形)
	class ObjectBox : public Object
	{
	public:
		Box box{}; //当たり判定と座標.

		//constructor.
		ObjectBox() : Object() {
			box.size  = {20, 20}; //デフォルトサイズ.
			box.color = 0xFFFFFF; //デフォルト色.
		}

		//当たり判定(Calcの機能)
		bool   HitCheckCir   (const Circle* cir);
		bool   HitCheckBox   (const Box* box);
		//計算(Calcの機能)
		void   FixPosInArea  (int left, int up, int right, int down);
		bool   IsOutInArea   (int left, int up, int right, int down, bool isCompOut);
		double CalcDist      (DBL_XY pos);
		DBL_XY CalcArcPos    (double ang, double len);
		double CalcFacingAng (DBL_XY targetPos);
		//操作(Inputの機能)
		void   MoveKey4Dir   (float speed);
		void   MovePad4Dir   (float speed);
		void   MovePadStick  (float speed);
		void   MoveMousePos  (bool isValidX = true, bool isValidY = true);
		//描画(Drawの機能)
		int    DrawShape     (bool isFill = true, bool isAnti = false);
		int    DrawGraph     (DrawImg* img, DBL_XY sizeRate = {1.0, 1.0});
	};

	//オブジェクト(グリッド上専用)
	class ObjectGrid : public Object
	{
	public:
		INT_XY pos{}; //座標.

		//constructor.
		ObjectGrid() : Object()	{}
		//描画.
		int Draw(DrawImg* img, INT_XY gridPos, INT_XY gridSize);
	};
}