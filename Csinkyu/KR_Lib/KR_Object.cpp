/*
   - KR_Object.cpp - (kurosawa original)
   ver: 2025/08/23

   DxLib�p�̃I�u�W�F�N�g�@�\.
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.h�ɓ����ĂȂ���΂����œ���.
  #include "KR_Draw.h"
  using namespace KR_Lib;
#endif
#include "KR_Object.h"

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	//�I�u�W�F�N�g(ObjectCir�^)�̕`��.
	int ObjectCir::Draw(bool isDrawHit) {

		_return(0, !isActive); //��A�N�e�B�u�Ȃ�`�悵�Ȃ�.

		//���W��offset�𑫂�.
		Circle tmpCir = {
			cir.pos+offset, cir.r, cir.color
		};

		//�~��`��(�摜���Ȃ��ꍇ)
		if (img.GetImage()->handle == 0) {
			int err = DrawCircleST(&tmpCir);
		}
		//�摜�`��.
		else {
			int err = img.Draw(tmpCir.pos);
			_return(-1, err < 0); //-1: DrawGraphST�ŃG���[.
		
			//�����蔻��\��.
			if (isDrawHit) {
				int err = DrawCircleST(&cir, false, true);
				_return(-2, err < 0); //-2: DrawCircleST�ŃG���[.
			}
		}
		return 0; //����I��.
	}
	//�I�u�W�F�N�g(ObjectBox�^)�̕`��.
	int ObjectBox::Draw(bool isDrawHit) {

		_return(0, !isActive); //��A�N�e�B�u�Ȃ�`�悵�Ȃ�.

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
			int err = img.Draw(tmpBox.pos);
			_return(-1, err < 0); //-1: DrawGraphST�ŃG���[.
		
			//�����蔻��\��.
			if (isDrawHit) {
				int err = DrawBoxST(&box, ANC_MID, false, true);
				_return(-2, err < 0); //-2: DrawBoxST�ŃG���[.
			}
		}
		return 0; //����I��.
	}
	//�I�u�W�F�N�g(ObjectGrid�^)�̕`��.
	int ObjectGrid::Draw(INT_XY gridPos, INT_XY gridSize) {

		_return(0, !isActive); //��A�N�e�B�u�Ȃ�`�悵�Ȃ�.

		//���W.
		INT_XY newPos = {
			gridPos.x + pos.x * gridSize.x,
			gridPos.y + pos.y * gridSize.y
		};
		//�摜�`��.
		int err = img.Draw(_dblXY(newPos), ANC_LU);
		return err; //-1: DrawGraphST�ŃG���[.
	}
}