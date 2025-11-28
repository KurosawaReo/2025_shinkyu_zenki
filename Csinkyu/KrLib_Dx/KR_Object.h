/*
   - KR_Object.h - (DxLib)
   ver: 2025/11/29

   オブジェクトを追加。(継承して使うことも可)
   Draw, Calc, Inputの一部機能をオブジェクト指向で使える。

   [使い方]
   ObjectMng: マネージャークラスに使うと便利。
   ObjectCir: 円形。　継承して使うことで、Draw/Calc/Inputの一部機能をオブジェクト指向で使える。
   ObjectBox: 四角形。継承して使うことで、Draw/Calc/Inputの一部機能をオブジェクト指向で使える。
*/
#pragma once
//KR_Globalが入ってなければここで導入.
#if !defined DEF_KR_DXLIB_GLOBAL
  #include "KR_Global.h"
#endif
#include "KR_Calc.h"
#include "KR_Draw.h"
#include "KR_Input.h"

/*
   [画像について]

   DrawImgで「=」演算子を禁止にしてるため
   Objectのメンバに入れるとObject自体も「=」演算子が使えなくなる.

   そのため、外部からポインタで送る方式を使っている.
*/

//KrLib名前空間.
namespace KR
{
	//オブジェクト(図形)[継承必須]
	class ObjectShape
	{
	//▼変数.
	private:
		DrawImg* img{};      //画像データ.
	public:
		DBL_XY   offset{};   //画像をずらす量.
		bool     isActive{}; //有効かどうか.

	//▼関数.
	protected:
		//constructor.
		ObjectShape() : img(nullptr), offset(0, 0), isActive(true) {}

	public:
		//virtual(中身が変わるため、派生クラスで設定する)
		virtual void    SetPos(DBL_XY)       = 0;
		virtual DBL_XY  GetPos()       const = 0;
		virtual DBL_XY* GetPosPtr()          = 0;
		virtual DBL_XY  GetSize()      const = 0;
		virtual int     DrawShape(bool isFill = true, bool isAnti = false) = 0;

		//set.
		void   SetDrawImg     (DrawImg& _img) { img = &_img; }
		//計算(Calcの機能)
		void   FixPosInArea   (DBL_RECT rect);
		bool   IsOutInArea    (DBL_RECT rect, bool isCompOut);
		double CalcDist       (DBL_XY pos);
		DBL_XY CalcArcPos     (double ang, double len);
		double CalcFacingAng  (DBL_XY targetPos);
		//操作(Inputの機能)
		void   MoveKey4Dir    (float speed);
		void   MovePad4Dir    (float speed);
		void   MovePadStick   (float speed);
		void   MoveMousePos   (bool isMoveX = true, bool isMoveY = true);
		//描画(Drawの機能)
		int    DrawGraph      ();
		int    DrawRectGraph  (DBL_RECT rect);
		int    DrawExtendGraph(DBL_XY sizeRate);
		int    DrawRotaGraph  (double ang, double sizeRate = 1.0, INT_XY pivot = {0, 0});
	};

	//オブジェクト(円)
	class ObjectCir : public ObjectShape
	{
	//▼変数.
	public:
		Circle cir{}; //当たり判定と座標.

	//▼関数.
	public:
		//constructor.
		ObjectCir() : ObjectShape() {
			cir.r     = 10;       //デフォルト半径.
			cir.color = 0xFFFFFF; //デフォルト色.
		}
		//override.
		void    SetPos(DBL_XY _pos)       override { cir.pos = _pos; }
		DBL_XY  GetPos()            const override { return cir.pos; }
		DBL_XY* GetPosPtr()               override { return &cir.pos; }
		DBL_XY  GetSize()           const override { return {cir.r, cir.r}; }
		int     DrawShape(bool isFill = true, bool isAnti = false) override;

		//当たり判定(Calcの機能)
		bool    HitCheckCir (const Circle& cir);
		bool    HitCheckBox (const Box&    box);
		bool    HitCheckLine(const Line&   line);
	};

	//オブジェクト(四角形)
	class ObjectBox : public ObjectShape
	{
	//▼変数.
	public:
		Box box{}; //当たり判定と座標.

	//▼関数.
	public:
		//constructor.
		ObjectBox() : ObjectShape() {
			box.size  = {20, 20}; //デフォルトサイズ.
			box.color = 0xFFFFFF; //デフォルト色.
		}
		//override.
		void    SetPos(DBL_XY _pos)       override { box.pos = _pos; }
		DBL_XY  GetPos()            const override { return box.pos; }
		DBL_XY* GetPosPtr()               override { return &box.pos; }
		DBL_XY  GetSize()           const override { return box.size; }
		int     DrawShape(bool isFill = true, bool isAnti = false) override;

		//当たり判定(Calcの機能)
		bool    HitCheckCir(const Circle& cir);
		bool    HitCheckBox(const Box&    box);
	};

	//オブジェクト(グリッド上専用)
	class ObjectGrid
	{
	public:
		INT_XY pos{};      //座標.
		bool   isActive{}; //有効かどうか.

		//描画.
		int Draw(const DrawImg& img, INT_XY gridPos, INT_XY gridSize);
	};
}