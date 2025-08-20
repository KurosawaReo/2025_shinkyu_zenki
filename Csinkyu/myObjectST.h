/*
   - myObjectST.h - (original)
   ver.2025/08/15

   DxLib: オリジナルオブジェクト機能の追加.
*/
#pragma once

//オブジェクト(基底)
class Object
{
//▼変数.
protected:
	DrawImgST img{};      //画像.
public:
	DBL_XY    offset{};   //画像をずらす量.
	bool      isActive{}; //有効かどうか.

//▼関数.
public:
	//コンストラクタ.
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
	//コンストラクタ.
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
	//コンストラクタ.
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
	//コンストラクタ.
	ObjectGrid() : Object()	{}
	//描画.
	int Draw(INT_XY gridPos, INT_XY gridSize);
};