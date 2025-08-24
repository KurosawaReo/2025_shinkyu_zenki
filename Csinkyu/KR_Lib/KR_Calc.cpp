/*
   - KR_Calc.cpp - (DxLib)
   ver: 2025/08/24

   �v�Z�@�\��ǉ����܂�.
   (�I�u�W�F�N�g�w��ver �� KR_Object)
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.h�ɓ����ĂȂ���΂����œ���.
  using namespace KR_Lib;
#endif
#include "KR_Calc.h"

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	Calc Calc::inst; //�C���X�^���X�𐶐�.

	//�����蔻��(�~�Ɖ~)
	bool Calc::HitCheckCircle(const Circle* cir1, const Circle* cir2) {

		//������.
		double x = cir1->pos.x - cir2->pos.x;
		double y = cir1->pos.y - cir2->pos.y;
		//���������a�̍��v���Z����Γ������Ă���.
		//(����팸���邽�߂�2�悵�Čv�Z)
		if (x*x + y*y <= pow(cir1->r+cir2->r, 2)) {
			return true;
		}
		else {
			return false;
		}
	}
	//�����蔻��(�l�p�Ǝl�p)
	bool Calc::HitCheckBox(const Box* box1, const Box* box2) {

		//��������W�ł̔���.
		if (fabs(box1->pos.x - box2->pos.x) <= (box1->size.x + box2->size.x)/2 &&
			fabs(box1->pos.y - box2->pos.y) <= (box1->size.y + box2->size.y)/2
		){
			return true;
		}
		else {
			return false;
		}
	}
	//�����蔻��(���Ɖ~)
	bool Calc::HitCheckLine(const Line* line, const Circle* cir) {

		//���̎n�_�ƏI�_����X�������߂�.
		double katamuki;
		{
			double x = line->edPos.x - line->stPos.x;
			double y = line->edPos.y - line->stPos.y;
			if (x != 0) {
				katamuki = y / x;
			}
			else {
				katamuki = 999; //0���΍�.
			}
		}
		//����������ɂ������̐ؕ�.
		double seppen = line->stPos.y - line->stPos.x * katamuki;

		//���`�~�̋���.
		double dis1;
		{
			//����: ax + by + c = 0
			//b��1�Ƃ��āuy = �v�̌`�ɂ��遨 y = -ax - c
			double a = -katamuki;
			double b = 1;
			double c = -seppen;
			//����: d = |ax + by + c|/��(a^2 + b^2)
			dis1 = fabs(a*cir->pos.x + b*cir->pos.y + c) / sqrt(a*a + b*b);
		}
		//���̒��_�`�~�̒��S�̋���.
		double dis2;
		{
			double x = cir->pos.x - CalcMidPos(line->stPos, line->edPos).x;
			double y = cir->pos.y - CalcMidPos(line->stPos, line->edPos).y;
			//����: d = ��(x^2 + y^2) (�O�����̒藝)
			dis2 = sqrt(x*x + y*y);
		}

		//hit����.
		if (dis1 <= cir->r &&                                     //����1:���ɐG��Ă���.
			dis2 <= CalcDist(line->stPos, line->edPos)/2 + cir->r //����2:���𒼌a�Ƃ���~�ɐG��Ă���.
		){
			return true;
		}
		else {
			return false;
		}
	}

	//�͈͓��ɍ��W��␳����.
	void Calc::FixPosInArea(DBL_XY* pos, INT_XY size, int left, int up, int right, int down) {

		if (pos->x < left  + size.x/2) { pos->x = left  + size.x/2; }
		if (pos->y < up    + size.y/2) { pos->y = up    + size.y/2; }
		if (pos->x > right - size.x/2) { pos->x = right - size.x/2; }
		if (pos->y > down  - size.y/2) { pos->y = down  - size.y/2; }
	}
	//�G���A�͈̔͊O���ǂ���.
	bool Calc::IsOutInArea(DBL_XY pos, INT_XY size, int left, int up, int right, int down, bool isCompOut) {

		//���S�ɏo����͈͊O�Ƃ���.
		if (isCompOut) {
			if (pos.x < left  - size.x/2) { return true; }
			if (pos.y < up    - size.y/2) { return true; }
			if (pos.x > right + size.x/2) { return true; }
			if (pos.y > down  + size.y/2) { return true; }
		}
		//������Ƃł��o����͈͊O�Ƃ���.
		else {
			if (pos.x < left  + size.x/2) { return true; }
			if (pos.y < up    + size.y/2) { return true; }
			if (pos.x > right - size.x/2) { return true; }
			if (pos.y > down  - size.y/2) { return true; }
		}

		return false; //�͈͓�.
	}

	//���������߂�.
	//[���W1,���W2 �� ����]
	double Calc::CalcDist(INT_XY pos1, INT_XY pos2) {

		double x = pos1.x - pos2.x; //x�̍�.
		double y = pos1.y - pos2.y; //y�̍�.

		return sqrt(x*x + y*y); //�Εӂ̒�����Ԃ�.
	}
	double Calc::CalcDist(DBL_XY pos1, DBL_XY pos2) {

		double x = pos1.x - pos2.x; //x�̍�.
		double y = pos1.y - pos2.y; //y�̍�.

		return sqrt(x*x + y*y); //�Εӂ̒�����Ԃ�.
	}
	//���_���W�����߂�.
	//[���W1,���W2 �� ���_���W]
	DBL_XY Calc::CalcMidPos(DBL_XY pos1, DBL_XY pos2) {

		double x = (pos1.x + pos2.x)/2; //x�̕���.
		double y = (pos1.y + pos2.y)/2; //y�̕���.

		return { x, y };
	}
	//�p�x�ƒ�������~����̍��W�����߂�.
	//[���W1,�p�x,���� �� ���W2]
	DBL_XY Calc::CalcArcPos(DBL_XY stPos, double ang, double len) {

		//�p�x��rad�ɕϊ����A���W�̌v�Z.
		double x = cos(_rad(ang)) * len;
		double y = sin(_rad(ang)) * len;

		return { stPos.x+x, stPos.y+y }; //�I�_���W��Ԃ�.
	}
	//�n�_���W����Ώۍ��W�ւ̕��������߂�.
	//[���W1,���W2 �� �p�x]
	double Calc::CalcFacingAng(DBL_XY stPos, DBL_XY targetPos) {
		//���W��.
		double disX = targetPos.x - stPos.x;
		double disY = targetPos.y - stPos.y;
		//rad��dig�ɂ��ĕԂ�.
		return _deg(atan2(disY, disX));
	}
	//�p�x������W�����߂�.
	DBL_XY Calc::CalcVectorDeg(double deg) {
		//���Wvector(-1.0�`+1.0)��Ԃ�.
		return { cos(_rad(deg)), sin(_rad(deg)) };
	}
	//�p�x������W�����߂�.
	DBL_XY Calc::CalcVectorRad(double rad) {
		//���Wvector(-1.0�`+1.0)��Ԃ�.
		return { cos(rad), sin(rad) };
	}

	//ease-int: ���X�ɉ���.
	double Calc::CalcNumEaseIn(double time) {
		time = min(time, 1.0); //�����1.0
		time = max(time, 0.0); //������0.0
		return time * time;
	}
	//ease-out: ���X�Ɍ���.
	double Calc::CalcNumEaseOut(double time) {
		time = min(time, 1.0); //�����1.0
		time = max(time, 0.0); //������0.0
		return 1 - (1-time) * (1-time);
	}
	//ease-in-out: ���X�ɉ������Č���.
	double Calc::CalcNumEaseInOut(double time) {
		time = min(time, 1.0); //�����1.0
		time = max(time, 0.0); //������0.0
		return 0.5 * (1.0 - cos(M_PI*time)); //cos�̕Ԃ�l��1.0 �� -1.0
	}
	//wave loop: cos�g�̃��[�v(0.0�`1.0)
	double Calc::CalcNumWaveLoop(double time) {
		return 0.5 - cos(M_PI*time)/2;
	}

	//�l�̒��I.
	int Calc::RandNum(int st, int ed, bool isDxRnd) {

		int rnd = 0;

		//ed��st�ȏ�̎��̂ݒ��I.
		_if_check(st <= ed) {

			//DxLib�p�̗������g�����ǂ���.
			if (isDxRnd) {
				rnd = GetRand(ed - st); //st�`end�̍��Œ��I.
			}
			else {
				rnd = rand() % ((ed - st) + 1); //st�`end�̍��Œ��I.
			}
		}
		return st + rnd;
	}
	//�l�̒��I(�d���Ȃ�����)
	vector<int> Calc::RandNums(int st, int ed, int count, bool isDxRnd) {

		int unUsedCnt = (ed-st)+1;      //���g�p�����͂������邩.
		vector<bool> isUsed((ed-st)+1); //�e�������g�p�ς��ǂ���.
		vector<int>  ret   (count);     //���I���ʂ�����p.
	
		//���I����񐔕����[�v.
		for (int i = 0; i < count; i++) {

			//���g�p�������牽�Ԗڂ�I�Ԃ����I.
			int cnt = RandNum(1, unUsedCnt, isDxRnd);
		
			//st�`ed�̒��Ő�����I��.
			for (int j = 0; j <= ed-st; j++) {
				//���g�p�����Ȃ�.
				if (!isUsed[j]) {
					cnt--; //�J�E���g-1
					if (cnt == 0) {
						ret[i] = st+j;    //���̐����𒊑I���ʂɕۑ�.
						isUsed[j] = true; //���̐����͎g�p��.
						unUsedCnt--;      //���g�p�g-1.
						break;
					}
				}
			}
		}

		//���I���ʂ�Ԃ�.
		return ret;
	}
	//�l���珬���������o��.
	double Calc::GetDecimal(double num) {
		return fmod(num, 1.0); //1.0�Ŋ������]��.
	}
}