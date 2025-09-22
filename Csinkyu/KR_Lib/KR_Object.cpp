/*
   - KR_Object.cpp - (DxLib)
   ver: 2025/09/21

   �I�u�W�F�N�g��ǉ����܂�, �p�����Ďg�����Ƃ��ł��B
   Draw, Calc, Input�̈ꕔ�@�\���I�u�W�F�N�g�w���Ŏg���܂��B
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.h�ɓ����ĂȂ���΂����œ���.
  #include "KR_Calc.h"
  #include "KR_Draw.h"
  #include "KR_Input.h"
#endif
#include "KR_Object.h"

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	InputMng* p_input = InputMng::GetPtr();

// ��*---=[ Object ]=---*�� //

	//�ړ����E���z���Ȃ��悤�ʒu�C��.
	void ObjectShape::FixPosInArea(int left, int up, int right, int down) {
		Calc::FixPosInArea(GetPosPtr(), GetSize().ToIntXY(), left, up, right, down);
	}
	//�G���A���z���Ă��邩�ǂ���.
	bool ObjectShape::IsOutInArea(int left, int up, int right, int down, bool isCompOut) {
		return Calc::IsOutInArea(GetPos(), GetSize().ToIntXY(), left, up, right, down, isCompOut);
	}
	//���������߂�.
	double ObjectShape::CalcDist(DBL_XY pos) {
		return Calc::CalcDist(GetPos(), pos);
	}
	//�p�x�ƒ�������~����̍��W�����߂�.
	DBL_XY ObjectShape::CalcArcPos(double ang, double len) {
		return Calc::CalcArcPos(GetPos(), ang, len);
	}
	//�Ώۍ��W���������̕��������߂�.
	double ObjectShape::CalcFacingAng(DBL_XY targetPos) {
		return Calc::CalcFacingAng(GetPos(), targetPos);
	}

	//�ړ�����.
	void ObjectShape::MoveKey4Dir(float speed) {
		p_input->MoveKey4Dir(GetPosPtr(), speed);
	}
	void ObjectShape::MovePad4Dir(float speed) {
		p_input->MovePad4Dir(GetPosPtr(), speed);
	}
	void ObjectShape::MovePadStick(float speed) {
		p_input->MovePadStick(GetPosPtr(), speed);
	}
	void ObjectShape::MoveMousePos(bool isValidX, bool isValidY) {
		SetPos(p_input->GetMousePos(isValidX, isValidY));
	}
	
	//�摜��`��.
	int ObjectShape::DrawGraph() {

		_return(-1, !isActive); //-1: ��A�N�e�B�u.

		//�摜�f�[�^���Ȃ�.
		if (img == nullptr) {
			DrawShape(); //����ɐ}�`��`��.
			return -2;   //-2: �摜�Ȃ�.
		}
		//���W��offset�𑫂�.
		DBL_XY pos = GetPos() + offset;
		//�`��.
		int err = img->Draw(pos);
		_return(-3, err < 0); //-3: �摜�`��G���[.

		return 0; //����I��.
	}
	int ObjectShape::DrawRectGraph(int left, int up, int right, int down) {

		_return(-1, !isActive); //-1: ��A�N�e�B�u.

		//�摜�f�[�^���Ȃ�.
		if (img == nullptr) {
			DrawShape(); //����ɐ}�`��`��.
			return -2;   //-2: �摜�Ȃ�.
		}
		//���W��offset�𑫂�.
		DBL_XY pos = GetPos() + offset;
		//�`��.
		int err = img->DrawRect(pos, left, up, right, down);
		_return(-3, err < 0); //-3: �摜�`��G���[.

		return 0; //����I��.
	}
	int ObjectShape::DrawExtendGraph(DBL_XY sizeRate) {

		_return(-1, !isActive); //-1: ��A�N�e�B�u.

		//�摜�f�[�^���Ȃ�.
		if (img == nullptr) {
			DrawShape(); //����ɐ}�`��`��.
			return -2;   //-2: �摜�Ȃ�.
		}
		//���W��offset�𑫂�.
		DBL_XY pos = GetPos() + offset;
		//�`��.
		int err = img->DrawExtend(pos, sizeRate);
		_return(-3, err < 0); //-3: �摜�`��G���[.

		return 0; //����I��.
	}
	int ObjectShape::DrawRotaGraph(double ang, double sizeRate, INT_XY pivot) {

		_return(-1, !isActive); //-1: ��A�N�e�B�u.

		//�摜�f�[�^���Ȃ�.
		if (img == nullptr) {
			DrawShape(); //����ɐ}�`��`��.
			return -2;   //-2: �摜�Ȃ�.
		}
		//���W��offset�𑫂�.
		DBL_XY pos = GetPos() + offset;

		//�`��.
		int err = img->DrawRota(pos, sizeRate, ang, pivot);
		_return(-3, err < 0); //-3: �摜�`��G���[.

		return 0; //����I��.
	}

// ��*---=[ ObjectCir ]=---*�� //

	//�~�Ƃ̔���.
	bool ObjectCir::HitCheckCir(const Circle* cir) {
		return Calc::HitCirCir(cir, &this->cir);
	}
	//�l�p�`�Ƃ̔���.
	bool ObjectCir::HitCheckBox(const Box* box) {
		return Calc::HitBoxCir(box, &this->cir);
	}
	//���Ƃ̓����蔻��.
	bool ObjectCir::HitCheckLine(const Line* line) {
		return Calc::HitLineCir(line, &this->cir);
	}
	//�}�`: �~��`��.
	int ObjectCir::DrawShape(bool isFill, bool isAnti) {

		_return(0, !isActive); //��A�N�e�B�u�Ȃ�`�悵�Ȃ�.

		//���W��offset�𑫂�.
		Circle tmpCir = cir;
		tmpCir.pos += offset;
		//�`��.
		int err = DrawCircleKR(&tmpCir, isFill, isAnti);
		return err; //-1: �~�`��G���[.
	}

// ��*---=[ ObjectBox ]=---*�� //

	//�~�Ƃ̔���.
	bool ObjectBox::HitCheckCir(const Circle* cir) {
		return Calc::HitBoxCir(&this->box, cir);
	}
	//�l�p�`�Ƃ̔���.
	bool ObjectBox::HitCheckBox(const Box* box) {
		return Calc::HitBoxBox(&this->box, box);
	}
	//�}�`: �l�p�`��`��.
	int ObjectBox::DrawShape(bool isFill, bool isAnti) {

		_return(0, !isActive); //��A�N�e�B�u�Ȃ�`�悵�Ȃ�.

		//���W��offset�𑫂�.
		Box tmpBox = box;
		tmpBox.pos += offset;
		//�`��.
		int err = DrawBoxKR(&tmpBox, ANC_MID, isFill, isAnti);
		return err; //-1: �~�`��G���[.
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