/*
   - myObjectST.h - (original)
   ver.2025/08/02

   DxLib: �I���W�i���I�u�W�F�N�g�@�\�̒ǉ�.
*/
#pragma once

//�I�u�W�F�N�g(��{)
class Object
{
protected:
	DrawImgST img{};      //�摜.
	DBL_XY    offset{};   //�摜�����炷��.
	BOOL      isActive{}; //�L�����ǂ���.

public:
	//�������p.
	Object(DBL_XY _offset, BOOL _isActive) :
		offset  (_offset),
		isActive(_isActive)
	{}
	//set.
	void SetImage(Image* _data) {
		img.SetImage(_data);
	}
};

//�I�u�W�F�N�g(�~)
class ObjectCir : public Object
{
protected:
	Circle cir{}; //�����蔻��ƍ��W.

public:
	//�������p.
	ObjectCir(DBL_XY _pos, float _r, UINT _clr, DBL_XY _offset, BOOL _isActive) :
		cir   ({ _pos, _r, _clr }), 
		Object(_offset, _isActive)
	{}
	//�`��.
	int Draw(BOOL isDrawHit = FALSE);
};

//�I�u�W�F�N�g(�l�p�`)
class ObjectBox : public Object
{
protected:
	Box box{}; //�����蔻��ƍ��W.

public:
	//�������p.
	ObjectBox(DBL_XY _pos, DBL_XY _size, UINT _clr, DBL_XY _offset, BOOL _isActive) :
		box   ({_pos, _size, _clr}), 
		Object(_offset, _isActive)
	{}
	//�`��.
	int Draw(BOOL isDrawHit = FALSE);
};

//�I�u�W�F�N�g(�O���b�h���p)
class ObjectGrid : public Object
{
protected:
	INT_XY pos{}; //���W.

public:
	//�������p(��������)
	ObjectGrid(INT_XY _pos, DBL_XY _offset, BOOL _isActive) :
		pos   (_pos),
		Object(_offset, _isActive)
	{}
	//�`��.
	int Draw(INT_XY gridPos, INT_XY gridSize);
};