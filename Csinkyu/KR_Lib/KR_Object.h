/*
   - KR_Object.h - (kurosawa original)
   ver: 2025/08/22

   DxLib�p�̃I�u�W�F�N�g�@�\.
*/
#pragma once

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	//�I�u�W�F�N�g(���)
	class Object
	{
	//���ϐ�.
	protected:
		DrawImg img{};      //�摜.
	public:
		DBL_XY    offset{};   //�摜�����炷��.
		bool      isActive{}; //�L�����ǂ���.

	//���֐�.
	public:
		//constructor.
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
		//constructor.
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
		//constructor.
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
		//constructor.
		ObjectGrid() : Object()	{}
		//�`��.
		int Draw(INT_XY gridPos, INT_XY gridSize);
	};
}