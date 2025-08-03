/*
   - myObjectST.h - (original)
   ver.2025/08/03

   DxLib: オリジナルオブジェクト機能の追加.
*/
#pragma once

//オブジェクト(基本)
class Object
{
protected:
	DrawImgST img{};      //画像.
	DBL_XY    offset{};   //画像をずらす量.
	bool      isActive{}; //有効かどうか.

public:
	//初期化用.
	Object() :
		isActive(true)
	{}
	Object(DBL_XY _offset, bool _isActive) :
		offset  (_offset),
		isActive(_isActive)
	{}
	//set.
	void SetImage(Image* _data) {
		img.SetImage(_data);
	}
};

//オブジェクト(円)
class ObjectCir : public Object
{
protected:
	Circle cir{}; //当たり判定と座標.

public:
	//初期化用.
	ObjectCir() : Object() {
	}
	ObjectCir(DBL_XY _pos, float _r, UINT _clr, DBL_XY _offset, bool _isActive) :
		cir   ({ _pos, _r, _clr }), 
		Object(_offset, _isActive)
	{}
	//set, add, get.
	void SetPos(DBL_XY _pos) {
		cir.pos = _pos;
	}
	void AddPos(DBL_XY _pos) {
		cir.pos += _pos;
	}
	DBL_XY GetPos() {
		return cir.pos;
	}
	//描画.
	int Draw(bool isDrawHit = false);
};

//オブジェクト(四角形)
class ObjectBox : public Object
{
protected:
	Box box{}; //当たり判定と座標.

public:
	//初期化用.
	ObjectBox() : Object() {
	}
	ObjectBox(DBL_XY _pos, DBL_XY _size, UINT _clr, DBL_XY _offset, bool _isActive) :
		box   ({_pos, _size, _clr}), 
		Object(_offset, _isActive)
	{}
	//set, add, get.
	void SetPos(DBL_XY _pos) {
		box.pos = _pos;
	}
	void AddPos(DBL_XY _pos) {
		box.pos += _pos;
	}
	DBL_XY GetPos() {
		return box.pos;
	}
	//描画.
	int Draw(bool isDrawHit = false);
};

//オブジェクト(グリッド上専用)
class ObjectGrid : public Object
{
protected:
	INT_XY pos{}; //座標.

public:
	//初期化用.
	ObjectGrid() : Object()	{
	}
	ObjectGrid(INT_XY _pos, DBL_XY _offset, bool _isActive) :
		pos   (_pos),
		Object(_offset, _isActive)
	{}
	//set, add, get.
	void SetPos(INT_XY _pos) {
		pos = _pos;
	}
	void AddPos(INT_XY _pos) {
		pos += _pos;
	}
	INT_XY GetPos() {
		return pos;
	}
	//描画.
	int Draw(INT_XY gridPos, INT_XY gridSize);
};