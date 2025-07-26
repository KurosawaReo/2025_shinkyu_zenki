/*
   - myObjectST.h - (original)
   ver.2025/07/27

   DxLib: オリジナルオブジェクト機能の追加.
*/
#pragma once

//オブジェクト(基本)
class Object
{
protected:
	DrawImgST img{};      //画像.
	DBL_XY    offset{};   //画像をずらす量.
	BOOL      isActive{}; //有効かどうか.

public:
	//初期化用.
	Object(DBL_XY _offset, BOOL _isActive) :
		offset  (_offset),
		isActive(_isActive)
	{}

	//画像読み込み.
	int LoadGraphST   (my_string fileName);
	int LoadDivGraphST(my_string fileName, INT_XY size, INT_XY cnt);
};

//オブジェクト(円)
class ObjectCir : public Object
{
protected:
	Circle cir{}; //当たり判定と座標.

public:
	//初期化用.
	ObjectCir(DBL_XY _pos, float _r, UINT _clr, DBL_XY _offset, BOOL _isActive) :
		cir   ({ _pos, _r, _clr }), 
		Object(_offset, _isActive)
	{}
	//描画.
	int Draw(int imgNo, BOOL isDrawHit = FALSE);
};

//オブジェクト(四角形)
class ObjectBox : public Object
{
protected:
	Box box{}; //当たり判定と座標.

public:
	//初期化用.
	ObjectBox(DBL_XY _pos, DBL_XY _size, UINT _clr, DBL_XY _offset, BOOL _isActive) :
		box   ({_pos, _size, _clr}), 
		Object(_offset, _isActive)
	{}
	//描画.
	int Draw(int imgNo, BOOL isDrawHit = FALSE);
};

//オブジェクト(グリッド上専用)
class ObjectGrid : public Object
{
protected:
	INT_XY pos{}; //座標.

public:
	//初期化用(引数あり)
	ObjectGrid(INT_XY _pos, DBL_XY _offset, BOOL _isActive) :
		pos   (_pos),
		Object(_offset, _isActive)
	{}
	//描画.
	int Draw(int imgNo, INT_XY gridPos, INT_XY gridSize);
};