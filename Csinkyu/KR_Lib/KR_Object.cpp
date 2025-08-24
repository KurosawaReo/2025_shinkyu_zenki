/*
   - KR_Object.cpp - (DxLib)
   ver: 2025/08/24

   �I�u�W�F�N�g��ǉ����܂�, �p�����Ďg�����Ƃ��ł�.
   Draw, Calc�̈ꕔ�@�\���I�u�W�F�N�g�w���Ŏg���܂�.
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.h�ɓ����ĂȂ���΂����œ���.
  #include "KR_Calc.h"
  #include "KR_Draw.h"
  using namespace KR_Lib;
#endif
#include "KR_Object.h"

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
// ��*---=[ ObjectCir ]=---*�� //

	//�~�Ƃ̔���.
	bool ObjectCir::HitCheckCircle(const Circle* cir) {
		Calc::GetPtr()->HitCheckCircle(&this->cir, cir);
	}
	//���Ƃ̓����蔻��.
	bool ObjectCir::HitCheckLine(const Line* line) {
		Calc::GetPtr()->HitCheckLine(line, &this->cir);
	}

	//�ړ����E���z���Ȃ��悤�ʒu�C��.
	void ObjectCir::FixPosInArea(int left, int up, int right, int down) {
		Calc::GetPtr()->FixPosInArea(&cir.pos, {_int_r(cir.r), _int_r(cir.r)}, left, up, right, down);
	}
	//�G���A���z���Ă��邩�ǂ���.
	bool ObjectCir::IsOutInArea(int left, int up, int right, int down, bool isCompOut) {
		return Calc::GetPtr()->IsOutInArea(cir.pos, {_int_r(cir.r), _int_r(cir.r)}, left, up, right, down, isCompOut);
	}
	//���������߂�.
	double ObjectCir::CalcDist(DBL_XY pos) {
		return Calc::GetPtr()->CalcDist(cir.pos, pos);
	}
	//�p�x�ƒ�������~����̍��W�����߂�.
	DBL_XY ObjectCir::CalcArcPos(double ang, double len) {
		return Calc::GetPtr()->CalcArcPos(cir.pos, ang, len);
	}
	//�Ώۍ��W���������̕��������߂�.
	double ObjectCir::CalcFacingAng(DBL_XY targetPos) {
		return Calc::GetPtr()->CalcFacingAng(cir.pos, targetPos);
	}

	//�I�u�W�F�N�g(ObjectCir�^)�̕`��.
	int ObjectCir::Draw(bool isDrawHit) {

		_return(0, !isActive); //��A�N�e�B�u�Ȃ�`�悵�Ȃ�.

		//���W��offset�𑫂�.
		Circle tmpCir = {
			cir.pos+offset, cir.r, cir.color
		};

		//�~��`��(�摜���Ȃ��ꍇ)
		if (img.GetHandle() == 0) {
			int err = DrawCircleST(&tmpCir);
			_return(-1, err < 0); //-1: �~�`��G���[.
		}
		//�摜�`��.
		else {
			int err = img.Draw(tmpCir.pos);
			_return(-2, err < 0); //-2: �摜�`��G���[.
		
			//�����蔻��\��.
			if (isDrawHit) {
				int err = DrawCircleST(&cir, false, true);
				_return(-3, err < 0); //-3: �����蔻��`��G���[.
			}
		}
		return 0; //����I��.
	}

// ��*---=[ ObjectBox ]=---*�� //

	//�l�p�Ƃ̔���.
	bool ObjectBox::HitCheckBox(const Box* box) {
		Calc::GetPtr()->HitCheckBox(&this->box, box);
	}

	//�ړ����E���z���Ȃ��悤�ʒu�C��.
	void ObjectBox::FixPosInArea(int left, int up, int right, int down) {
		Calc::GetPtr()->FixPosInArea(&box.pos, box.size.ToIntXY(), left, up, right, down);
	}
	//�G���A���z���Ă��邩�ǂ���.
	bool ObjectBox::IsOutInArea(int left, int up, int right, int down, bool isCompOut) {
		return Calc::GetPtr()->IsOutInArea(box.pos, box.size.ToIntXY(), left, up, right, down, isCompOut);
	}
	//���������߂�.
	double ObjectBox::CalcDist(DBL_XY pos) {
		return Calc::GetPtr()->CalcDist(box.pos, pos);
	}
	//�p�x�ƒ�������~����̍��W�����߂�.
	DBL_XY ObjectBox::CalcArcPos(double ang, double len) {
		return Calc::GetPtr()->CalcArcPos(box.pos, ang, len);
	}
	//�Ώۍ��W���������̕��������߂�.
	double ObjectBox::CalcFacingAng(DBL_XY targetPos) {
		return Calc::GetPtr()->CalcFacingAng(box.pos, targetPos);
	}

	//�I�u�W�F�N�g(ObjectBox�^)�̕`��.
	int ObjectBox::Draw(bool isDrawHit) {

		_return(0, !isActive); //��A�N�e�B�u�Ȃ�`�悵�Ȃ�.

		//���W��offset�𑫂�.
		Box tmpBox = {
			box.pos+offset, box.size, box.color
		};

		//�摜���Ȃ��Ȃ�l�p��`��.
		if (img.GetHandle() == 0) {
			int err = DrawBoxST(&tmpBox);
			_return(-1, err < 0); //-1: �l�p�`��G���[.
		}
		//�摜�`��.
		else {
			int err = img.Draw(tmpBox.pos);
			_return(-2, err < 0); //-2: �摜�`��G���[.
		
			//�����蔻��\��.
			if (isDrawHit) {
				int err = DrawBoxST(&box, ANC_MID, false, true);
				_return(-3, err < 0); //-3: �����蔻��`��G���[.
			}
		}
		return 0; //����I��.
	}

// ��*---=[ ObjectGrid ]=---*�� //

	//�I�u�W�F�N�g(ObjectGrid�^)�̕`��.
	int ObjectGrid::Draw(INT_XY gridPos, INT_XY gridSize) {

		_return(0, !isActive); //��A�N�e�B�u�Ȃ�`�悵�Ȃ�.

		//���W.
		INT_XY newPos = {
			gridPos.x + pos.x * gridSize.x,
			gridPos.y + pos.y * gridSize.y
		};
		//�摜�`��.
		int err = img.Draw(newPos.ToDblXY(), ANC_LU);
		return err; //-1: DrawGraphST�ŃG���[.
	}
}