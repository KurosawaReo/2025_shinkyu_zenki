/*
   - KR_Object.h - (DxLib)
   ver: 2025/10/01

   �I�u�W�F�N�g��ǉ����܂��B

   [�g����]
   ObjectMng: �}�l�[�W���[�N���X�Ɏg���ƕ֗��ł��B
   ObjectCir: �~�`�B�@�p�����Ďg�����ƂŁADraw/Calc/Input�̈ꕔ�@�\���I�u�W�F�N�g�w���Ŏg���܂��B
   ObjectBox: �l�p�`�B�p�����Ďg�����ƂŁADraw/Calc/Input�̈ꕔ�@�\���I�u�W�F�N�g�w���Ŏg���܂��B
*/
#pragma once

/*
   [�摜�ɂ���]

   DrawImg�Łu=�v���Z�q���֎~�ɂ��Ă邽��
   Object�̃����o�ɓ�����Object���̂��u=�v���Z�q���g���Ȃ��Ȃ�.

   ���̂��߁A�O������|�C���^�ő���������g���Ă���.
*/

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	class DrawImg; //�O���錾.

	//�I�u�W�F�N�g(�Ǘ��N���X)[�p���K�{]
	template<typename T, const int MAX_SIZE>
	class ObjectMng
	{
	//���ϐ�.
	protected:
		T object[MAX_SIZE];

	//���֐�.
	protected:
		//constructor.
		ObjectMng(){
			for (auto& i : object) {
				i.isActive = false; //�S�Ė�����.
			}
		}
		//������.
		void InitLoop() {
			for (auto& i : object) {
				i.Init();
			}
		}
		//���Z�b�g.
		void ResetLoop() {
			for (auto& i : object) {
				i.Reset();
			}
		}
		//�X�V.
		void UpdateLoop() {
			for (auto& i : object) {
				if (i.isActive) { i.Update(); }
			}
		}
		//�`��.
		void DrawLoop() {
			for (auto& i : object) {
				if (i.isActive) { i.Draw(); }
			}
		}

	public:
		//get.
		T* GetObjectPtr(int idx) { return &object[idx]; } //�f�[�^�̎擾.
	};

	//�I�u�W�F�N�g(�}�`)[�p���K�{]
	class ObjectShape
	{
	//���ϐ�.
	private:
		DrawImg* img{};      //�摜�f�[�^.
	public:
		DBL_XY   offset{};   //�摜�����炷��.
		bool     isActive{}; //�L�����ǂ���.

	//���֐�.
	protected:
		//constructor.
		ObjectShape() : img(nullptr), isActive(true) {}

	public:
		//virtual(���g���ς�邽�߁A�h���N���X�Őݒ肷��)
		virtual void    SetPos(DBL_XY)       = 0;
		virtual DBL_XY  GetPos()       const = 0;
		virtual DBL_XY* GetPosPtr()          = 0;
		virtual DBL_XY  GetSize()      const = 0;
		virtual int     DrawShape(bool isFill = true, bool isAnti = false) = 0;

		//set.
		void   SetDrawImg     (DrawImg* _img) { img = _img; }
		//�v�Z(Calc�̋@�\)
		void   FixPosInArea   (int left, int up, int right, int down);
		bool   IsOutInArea    (int left, int up, int right, int down, bool isCompOut);
		double CalcDist       (DBL_XY pos);
		DBL_XY CalcArcPos     (double ang, double len);
		double CalcFacingAng  (DBL_XY targetPos);
		//����(Input�̋@�\)
		void   MoveKey4Dir    (float speed);
		void   MovePad4Dir    (float speed);
		void   MovePadStick   (float speed);
		void   MoveMousePos   (bool isValidX = true, bool isValidY = true);
		//�`��(Draw�̋@�\)
		int    DrawGraph      ();
		int    DrawRectGraph  (int left, int up, int right, int down);
		int    DrawExtendGraph(DBL_XY sizeRate);
		int    DrawRotaGraph  (double ang, double sizeRate = 1.0, INT_XY pivot = {0, 0});
	};

	//�I�u�W�F�N�g(�~)
	class ObjectCir : public ObjectShape
	{
	//���ϐ�.
	public:
		Circle cir{}; //�����蔻��ƍ��W.

	//���֐�.
	public:
		//constructor.
		ObjectCir() : ObjectShape() {
			cir.r     = 10;       //�f�t�H���g���a.
			cir.color = 0xFFFFFF; //�f�t�H���g�F.
		}
		//override.
		void    SetPos(DBL_XY _pos) override { cir.pos = _pos; }
		DBL_XY  GetPos()      const override { return cir.pos; }
		DBL_XY* GetPosPtr()         override { return &cir.pos; }
		DBL_XY  GetSize()     const override { return {cir.r, cir.r}; }
		int     DrawShape(bool isFill = true, bool isAnti = false) override;

		//�����蔻��(Calc�̋@�\)
		bool    HitCheckCir (const Circle* cir);
		bool    HitCheckBox (const Box*    box);
		bool    HitCheckLine(const Line*   line);
	};

	//�I�u�W�F�N�g(�l�p�`)
	class ObjectBox : public ObjectShape
	{
	//���ϐ�.
	public:
		Box box{}; //�����蔻��ƍ��W.

	//���֐�.
	public:
		//constructor.
		ObjectBox() : ObjectShape() {
			box.size  = {20, 20}; //�f�t�H���g�T�C�Y.
			box.color = 0xFFFFFF; //�f�t�H���g�F.
		}
		//override.
		void    SetPos(DBL_XY _pos) override { box.pos = _pos; }
		DBL_XY  GetPos()      const override { return box.pos; }
		DBL_XY* GetPosPtr()         override { return &box.pos; }
		DBL_XY  GetSize()     const override { return box.size; }
		int     DrawShape(bool isFill = true, bool isAnti = false) override;

		//�����蔻��(Calc�̋@�\)
		bool    HitCheckCir(const Circle* cir);
		bool    HitCheckBox(const Box* box);
	};

	//�I�u�W�F�N�g(�O���b�h���p)
	class ObjectGrid
	{
	public:
		INT_XY pos{};      //���W.
		bool   isActive{}; //�L�����ǂ���.

		//�`��.
		int Draw(DrawImg* img, INT_XY gridPos, INT_XY gridSize);
	};
}