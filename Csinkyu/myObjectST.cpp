/*
   - myObjectST.cpp - (original)
   ver.2025/08/03

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

	//���W.
	INT_XY pos = {
		_int(cir.pos.x + offset.x),
		_int(cir.pos.y + offset.y)
	};
	//�摜�`��.
	int err = img.DrawGraphST(pos);
	if (err < 0) {
		return -1; //-1: DrawGraphST�ŃG���[.
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

	//���W.
	INT_XY pos = {
		_int(box.pos.x + offset.x),
		_int(box.pos.y + offset.y)
	};
	//�摜�`��.
	int err = img.DrawGraphST(pos);
	if (err < 0) {
		return -1; //-1: DrawGraphST�ŃG���[.
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
	int err = img.DrawGraphST(newPos, ANC_LU);
	return err; //-1: DrawGraphST�ŃG���[.
}