/*
   - KR_Object.h - (DxLib)
   ver: 2025/10/01

   オブジェクトを追加します。

   [使い方]
   ObjectMng: マネージャークラスに使うと便利です。
   ObjectCir: 円形。　継承して使うことで、Draw/Calc/Inputの一部機能をオブジェクト指向で使えます。
   ObjectBox: 四角形。継承して使うことで、Draw/Calc/Inputの一部機能をオブジェクト指向で使えます。
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

	//オブジェクト(管理クラス)[継承必須]
	template<typename T, const int MAX_SIZE>
	class ObjectMng
	{
	//▼変数.
	protected:
		T object[MAX_SIZE];

	//▼関数.
	protected:
		//constructor.
		ObjectMng(){
			for (auto& i : object) {
				i.isActive = false; //全て無効に.
			}
		}
		//初期化.
		void InitLoop() {
			for (auto& i : object) {
				i.Init();
			}
		}
		//リセット.
		void ResetLoop() {
			for (auto& i : object) {
				i.Reset();
			}
		}
		//更新.
		void UpdateLoop() {
			for (auto& i : object) {
				if (i.isActive) { i.Update(); }
			}
		}
		//描画.
		void DrawLoop() {
			for (auto& i : object) {
				if (i.isActive) { i.Draw(); }
			}
		}

	public:
		//get.
		T* GetObjectPtr(int idx) { return &object[idx]; } //データの取得.
	};

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
		ObjectShape() : img(nullptr), isActive(true) {}

	public:
		//virtual(中身が変わるため、派生クラスで設定する)
		virtual void    SetPos(DBL_XY)       = 0;
		virtual DBL_XY  GetPos()       const = 0;
		virtual DBL_XY* GetPosPtr()          = 0;
		virtual DBL_XY  GetSize()      const = 0;
		virtual int     DrawShape(bool isFill = true, bool isAnti = false) = 0;

		//set.
		void   SetDrawImg     (DrawImg* _img) { img = _img; }
		//計算(Calcの機能)
		void   FixPosInArea   (int left, int up, int right, int down);
		bool   IsOutInArea    (int left, int up, int right, int down, bool isCompOut);
		double CalcDist       (DBL_XY pos);
		DBL_XY CalcArcPos     (double ang, double len);
		double CalcFacingAng  (DBL_XY targetPos);
		//操作(Inputの機能)
		void   MoveKey4Dir    (float speed);
		void   MovePad4Dir    (float speed);
		void   MovePadStick   (float speed);
		void   MoveMousePos   (bool isValidX = true, bool isValidY = true);
		//描画(Drawの機能)
		int    DrawGraph      ();
		int    DrawRectGraph  (int left, int up, int right, int down);
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
		void    SetPos(DBL_XY _pos) override { cir.pos = _pos; }
		DBL_XY  GetPos()      const override { return cir.pos; }
		DBL_XY* GetPosPtr()         override { return &cir.pos; }
		DBL_XY  GetSize()     const override { return {cir.r, cir.r}; }
		int     DrawShape(bool isFill = true, bool isAnti = false) override;

		//当たり判定(Calcの機能)
		bool    HitCheckCir (const Circle* cir);
		bool    HitCheckBox (const Box*    box);
		bool    HitCheckLine(const Line*   line);
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
		void    SetPos(DBL_XY _pos) override { box.pos = _pos; }
		DBL_XY  GetPos()      const override { return box.pos; }
		DBL_XY* GetPosPtr()         override { return &box.pos; }
		DBL_XY  GetSize()     const override { return box.size; }
		int     DrawShape(bool isFill = true, bool isAnti = false) override;

		//当たり判定(Calcの機能)
		bool    HitCheckCir(const Circle* cir);
		bool    HitCheckBox(const Box* box);
	};

	//オブジェクト(グリッド上専用)
	class ObjectGrid
	{
	public:
		INT_XY pos{};      //座標.
		bool   isActive{}; //有効かどうか.

		//描画.
		int Draw(DrawImg* img, INT_XY gridPos, INT_XY gridSize);
	};
}