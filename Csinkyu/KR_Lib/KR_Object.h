/*
   - KR_Object.h - (kurosawa original)
   ver: 2025/08/22

   DxLib用のオブジェクト機能.
*/
#pragma once

//KR_Libに使う用.
namespace KR_Lib
{
	//オブジェクト(基底)
	class Object
	{
	//▼変数.
	protected:
		DrawImg img{};      //画像.
	public:
		DBL_XY    offset{};   //画像をずらす量.
		bool      isActive{}; //有効かどうか.

	//▼関数.
	public:
		//constructor.
		Object() : isActive(true) {}
		//set.
		void SetImage(Image* _data) {
			img.SetImage(_data);
		}
	};

	//オブジェクト(円)
	class ObjectCir : public Object
	{
	//▼変数.
	public:
		Circle cir{}; //当たり判定と座標.

	//▼関数.
	public:
		//constructor.
		ObjectCir() : Object() {}
		//描画.
		int Draw(bool isDrawHit = false);
	};

	//オブジェクト(四角形)
	class ObjectBox : public Object
	{
	//▼変数.
	public:
		Box box{}; //当たり判定と座標.

	//▼関数.
	public:
		//constructor.
		ObjectBox() : Object() {}
		//描画.
		int Draw(bool isDrawHit = false);
	};

	//オブジェクト(グリッド上専用)
	class ObjectGrid : public Object
	{
	//▼変数.
	public:
		INT_XY pos{}; //座標.

	//▼関数.
	public:
		//constructor.
		ObjectGrid() : Object()	{}
		//描画.
		int Draw(INT_XY gridPos, INT_XY gridSize);
	};
}