/*
   - myObjectST.cpp - (original)
   ver.2025/08/02

   DxLib: �I���W�i���I�u�W�F�N�g�@�\�̒ǉ�.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx���ɓ����ĂȂ���΂����œ���.
  #include "myDrawST.h"
#endif
#include "myObjectST.h"

//�摜�ǂݍ���.
int Object::LoadGraphST(MY_STRING fileName) {
	return img.LoadGraphST(fileName);
}
int Object::LoadDivGraphST(MY_STRING fileName, INT_XY size, INT_XY cnt) {
	return img.LoadDivGraphST(fileName, size, cnt);
}

//�I�u�W�F�N�g(ObjectCir�^)�̕`��.
int ObjectCir::Draw(int imgNo, BOOL isDrawHit) {

	//���W.
	INT_XY pos = {
		_int(cir.pos.x + offset.x),
		_int(cir.pos.y + offset.y)
	};
	//�摜�`��.
	int err = img.DrawGraphST(imgNo, pos, TRUE);
	if (err < 0) {
		return -1; //-1: DrawGraphST�ŃG���[.
	}
	//�����蔻��\��.
	if (isDrawHit) {
		int err = DrawCircleST(&cir, FALSE, TRUE);
		if (err < 0) {
			return -2; //-2: DrawCircleST�ŃG���[.
		}
	}
	return 0; //����I��.
}
//�I�u�W�F�N�g(ObjectBox�^)�̕`��.
int ObjectBox::Draw(int imgNo, BOOL isDrawHit) {

	//���W.
	INT_XY pos = {
		_int(box.pos.x + offset.x),
		_int(box.pos.y + offset.y)
	};
	//�摜�`��.
	int err = img.DrawGraphST(imgNo, pos, TRUE);
	if (err < 0) {
		return -1; //-1: DrawGraphST�ŃG���[.
	}
	//�����蔻��\��.
	if (isDrawHit) {
		int err = DrawBoxST(&box, TRUE, FALSE, TRUE);
		if (err < 0) {
			return -2; //-2: DrawBoxST�ŃG���[.
		}
	}
	return 0; //����I��.
}
//�I�u�W�F�N�g(ObjectGrid�^)�̕`��.
int ObjectGrid::Draw(int imgNo, INT_XY gridPos, INT_XY gridSize) {

	//���W.
	INT_XY pos{};
	pos = {
		gridPos.x + pos.x * gridSize.x,
		gridPos.y + pos.y * gridSize.y
	};
	//�摜�`��.
	int err = img.DrawGraphST(imgNo, pos, FALSE);
	return err; //-1: DrawGraphST�ŃG���[.
}