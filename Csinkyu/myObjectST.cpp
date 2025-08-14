/*
   - myObjectST.cpp - (original)
   ver.2025/08/14

   DxLib: �I���W�i���I�u�W�F�N�g�@�\�̒ǉ�.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx���ɓ����ĂȂ���΂����œ���.
  #include "myDrawST.h"
#endif
#include "myObjectST.h"

//�I�u�W�F�N�g(ObjectCir�^)�̕`��.
int ObjectCir::Draw(bool isDrawHit) {

	if (!isActive) {
		return 0; //��A�N�e�B�u�Ȃ�`�悵�Ȃ�.
	}

	//���W��offset�𑫂�.
	Circle tmpCir = {
		cir.pos+offset, cir.r, cir.color
	};
	//�摜���Ȃ��Ȃ�~��`��.
	if (img.GetImage()->handle == 0) {
		DrawCircleST(&tmpCir);
	}
	//�摜�`��.
	else {
		int err = img.DrawGraphST(tmpCir.pos);
		if (err < 0) {
			return -1; //-1: DrawGraphST�ŃG���[.
		}
	}
	//�����蔻��\��.
	if (isDrawHit) {
		int err = DrawCircleST(&cir, false, true);
		if (err < 0) {
			return -2; //-2: DrawCircleST�ŃG���[.
		}
	}
	return 0; //����I��.
}
//�I�u�W�F�N�g(ObjectBox�^)�̕`��.
int ObjectBox::Draw(bool isDrawHit) {

	if (!isActive) {
		return 0; //��A�N�e�B�u�Ȃ�`�悵�Ȃ�.
	}

	//���W��offset�𑫂�.
	Box tmpBox = {
		box.pos+offset, box.size, box.color
	};
	//�摜���Ȃ��Ȃ�l�p��`��.
	if (img.GetImage()->handle == 0) {
		DrawBoxST(&tmpBox);
	}
	//�摜�`��.
	else {
		int err = img.DrawGraphST(tmpBox.pos);
		if (err < 0) {
			return -1; //-1: DrawGraphST�ŃG���[.
		}
	}
	//�����蔻��\��.
	if (isDrawHit) {
		int err = DrawBoxST(&box, ANC_MID, false, true);
		if (err < 0) {
			return -2; //-2: DrawBoxST�ŃG���[.
		}
	}
	return 0; //����I��.
}
//�I�u�W�F�N�g(ObjectGrid�^)�̕`��.
int ObjectGrid::Draw(INT_XY gridPos, INT_XY gridSize) {

	if (!isActive) {
		return 0; //��A�N�e�B�u�Ȃ�`�悵�Ȃ�.
	}

	//���W.
	INT_XY newPos = {
		gridPos.x + pos.x * gridSize.x,
		gridPos.y + pos.y * gridSize.y
	};
	//�摜�`��.
	int err = img.DrawGraphST(_dblXY(newPos), ANC_LU);
	return err; //-1: DrawGraphST�ŃG���[.
}