/*
   - myObjectST.h - (original)
   ver.2025/08/15

   DxLib: �I���W�i���I�u�W�F�N�g�@�\�̒ǉ�.
*/
#pragma once

//�I�u�W�F�N�g(���)
class Object
{
//���ϐ�.
protected:
	DrawImgST img{};      //�摜.
public:
	DBL_XY    offset{};   //�摜�����炷��.
	bool      isActive{}; //�L�����ǂ���.

//���֐�.
public:
	//�R���X�g���N�^.
	Object() : isActive(true) {}
	//set.
	void SetImage(Image* _data) {
		img.SetImage(_data);
	}
};

//�I�u�W�F�N�g(�~)
class ObjectCir : public Object
{
//���ϐ�.
public:
	Circle cir{}; //�����蔻��ƍ��W.

//���֐�.
public:
	//�R���X�g���N�^.
	ObjectCir() : Object() {}
	//�`��.
	int Draw(bool isDrawHit = false);
};

//�I�u�W�F�N�g(�l�p�`)
class ObjectBox : public Object
{
//���ϐ�.
public:
	Box box{}; //�����蔻��ƍ��W.

//���֐�.
public:
	//�R���X�g���N�^.
	ObjectBox() : Object() {}
	//�`��.
	int Draw(bool isDrawHit = false);
};

//�I�u�W�F�N�g(�O���b�h���p)
class ObjectGrid : public Object
{
//���ϐ�.
public:
	INT_XY pos{}; //���W.

//���֐�.
public:
	//�R���X�g���N�^.
	ObjectGrid() : Object()	{}
	//�`��.
	int Draw(INT_XY gridPos, INT_XY gridSize);
};