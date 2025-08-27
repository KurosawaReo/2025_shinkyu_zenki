/*
   - KR_Object.cpp - (DxLib)
   ver: 2025/08/25

   �I�u�W�F�N�g��ǉ����܂�, �p�����Ďg�����Ƃ��ł�.
   Draw, Calc, Input�̈ꕔ�@�\���I�u�W�F�N�g�w���Ŏg���܂�.
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.h�ɓ����ĂȂ���΂����œ���.
  #include "KR_Calc.h"
  #include "KR_Draw.h"
  #include "KR_Input.h"
  using namespace KR_Lib;
#endif
#include "KR_Object.h"

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	Calc*     p_calc  = Calc::GetPtr();
	InputMng* p_input = InputMng::GetPtr();

// ��*---=[ ObjectCir ]=---*�� //

	//�~�Ƃ̔���.
	bool ObjectCir::HitCheckCir(const Circle* cir) {
		return p_calc->HitCirCir(cir, &this->cir);
	}
	//�l�p�`�Ƃ̔���.
	bool ObjectCir::HitCheckBox(const Box* box) {
		return p_calc->HitBoxCir(box, &this->cir);
	}
	//���Ƃ̓����蔻��.
	bool ObjectCir::HitCheckLine(const Line* line) {
		return p_calc->HitLineCir(line, &this->cir);
	}

	//�ړ����E���z���Ȃ��悤�ʒu�C��.
	void ObjectCir::FixPosInArea(int left, int up, int right, int down) {
		p_calc->FixPosInArea(&cir.pos, {_int_r(cir.r), _int_r(cir.r)}, left, up, right, down);
	}
	//�G���A���z���Ă��邩�ǂ���.
	bool ObjectCir::IsOutInArea(int left, int up, int right, int down, bool isCompOut) {
		return p_calc->IsOutInArea(cir.pos, {_int_r(cir.r), _int_r(cir.r)}, left, up, right, down, isCompOut);
	}
	//���������߂�.
	double ObjectCir::CalcDist(DBL_XY pos) {
		return p_calc->CalcDist(cir.pos, pos);
	}
	//�p�x�ƒ�������~����̍��W�����߂�.
	DBL_XY ObjectCir::CalcArcPos(double ang, double len) {
		return p_calc->CalcArcPos(cir.pos, ang, len);
	}
	//�Ώۍ��W���������̕��������߂�.
	double ObjectCir::CalcFacingAng(DBL_XY targetPos) {
		return p_calc->CalcFacingAng(cir.pos, targetPos);
	}

	//�ړ�����.
	void ObjectCir::MoveKey4Dir(float speed) {
		p_input->MoveKey4Dir(&cir.pos, speed);
	}
	void ObjectCir::MovePad4Dir(float speed) {
		p_input->MovePad4Dir(&cir.pos, speed);
	}
	void ObjectCir::MovePadStick(float speed) {
		p_input->MovePadStick(&cir.pos, speed);
	}
	void ObjectCir::MoveMousePos(bool isValidX, bool isValidY) {
		p_input->GetMousePos(&cir.pos, isValidX, isValidY);
	}

	//ObjectCir�^: �~��`��.
	int ObjectCir::DrawShape(bool isFill, bool isAnti) {

		_return(0, !isActive); //��A�N�e�B�u�Ȃ�`�悵�Ȃ�.

		//���W��offset�𑫂�.
		Circle tmpCir = cir;
		tmpCir.pos += offset;
		//�`��.
		int err = DrawCircleST(&tmpCir, isFill, isAnti);
		return err; //-1: �~�`��G���[.
	}
	//ObjectCir�^: �摜��`��.
	int ObjectCir::DrawGraph(DrawImg* img, DBL_XY sizeRate) {

		_return(0, !isActive); //��A�N�e�B�u�Ȃ�`�悵�Ȃ�.

		//���W��offset�𑫂�.
		Circle tmpCir = cir;
		tmpCir.pos += offset;
		//�`��.
		int err = img->DrawExtend(tmpCir.pos, sizeRate);
		if (err < 0) {
			DrawShape(); //����ɉ~��`��.
			return -1;   //-1: �摜�`��G���[.
		}
		return 0; //����I��.
	}

// ��*---=[ ObjectBox ]=---*�� //

	//�~�Ƃ̔���.
	bool ObjectBox::HitCheckCir(const Circle* cir) {
		return p_calc->HitBoxCir(&this->box, cir);
	}
	//�l�p�`�Ƃ̔���.
	bool ObjectBox::HitCheckBox(const Box* box) {
		return p_calc->HitBoxBox(&this->box, box);
	}

	//�ړ����E���z���Ȃ��悤�ʒu�C��.
	void ObjectBox::FixPosInArea(int left, int up, int right, int down) {
		p_calc->FixPosInArea(&box.pos, box.size.ToIntXY(), left, up, right, down);
	}
	//�G���A���z���Ă��邩�ǂ���.
	bool ObjectBox::IsOutInArea(int left, int up, int right, int down, bool isCompOut) {
		return p_calc->IsOutInArea(box.pos, box.size.ToIntXY(), left, up, right, down, isCompOut);
	}
	//���������߂�.
	double ObjectBox::CalcDist(DBL_XY pos) {
		return p_calc->CalcDist(box.pos, pos);
	}
	//�p�x�ƒ�������~����̍��W�����߂�.
	DBL_XY ObjectBox::CalcArcPos(double ang, double len) {
		return p_calc->CalcArcPos(box.pos, ang, len);
	}
	//�Ώۍ��W���������̕��������߂�.
	double ObjectBox::CalcFacingAng(DBL_XY targetPos) {
		return p_calc->CalcFacingAng(box.pos, targetPos);
	}

	//�ړ�����.
	void ObjectBox::MoveKey4Dir(float speed) {
		p_input->MoveKey4Dir(&box.pos, speed);
	}
	void ObjectBox::MovePad4Dir(float speed) {
		p_input->MovePad4Dir(&box.pos, speed);
	}
	void ObjectBox::MovePadStick(float speed) {
		p_input->MovePadStick(&box.pos, speed);
	}
	void ObjectBox::MoveMousePos(bool isValidX, bool isValidY) {
		p_input->GetMousePos(&box.pos, isValidX, isValidY);
	}

	//ObjectBox�^: �l�p�`��`��.
	int ObjectBox::DrawShape(bool isFill, bool isAnti) {

		_return(0, !isActive); //��A�N�e�B�u�Ȃ�`�悵�Ȃ�.

		//���W��offset�𑫂�.
		Box tmpBox = box;
		tmpBox.pos += offset;
		//�`��.
		int err = DrawBoxST(&tmpBox, ANC_MID, isFill, isAnti);
		return err; //-1: �~�`��G���[.
	}
	//ObjectBox�^: �摜��`��.
	int ObjectBox::DrawGraph(DrawImg* img, DBL_XY sizeRate) {

		_return(0, !isActive); //��A�N�e�B�u�Ȃ�`�悵�Ȃ�.

		//���W��offset�𑫂�.
		Box tmpBox = box;
		tmpBox.pos += offset;
		//�`��.
		int err = img->DrawExtend(tmpBox.pos, sizeRate);
		if (err < 0) {
			DrawShape(); //����Ɏl�p�`��`��.
			return -1;   //-1: �摜�`��G���[.
		}
		return 0; //����I��.
	}

// ��*---=[ ObjectGrid ]=---*�� //

	//�I�u�W�F�N�g(ObjectGrid�^)�̕`��.
	int ObjectGrid::Draw(DrawImg* img, INT_XY gridPos, INT_XY gridSize) {

		_return(0, !isActive); //��A�N�e�B�u�Ȃ�`�悵�Ȃ�.

		//���W.
		INT_XY newPos = {
			gridPos.x + pos.x * gridSize.x,
			gridPos.y + pos.y * gridSize.y
		};
		//�摜�`��.
		int err = img->Draw(newPos.ToDblXY(), ANC_LU);
		return err; //-1: DrawGraphST�ŃG���[.
	}
}