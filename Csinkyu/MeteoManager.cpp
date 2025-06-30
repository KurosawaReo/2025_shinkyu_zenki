/*
   - MeteoManager.cpp -
   覐΂̏o�����Ǘ�����.
*/
#include "MeteoManager.h"

void MeteoManager::Init(GameData* _data) {

	p_data = _data;

	//�S覐΃��[�v.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		meteo[i].Init(_data);
	}
}

void MeteoManager::Reset() {

	timer = 0;

	//�S覐΃��[�v.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		meteo[i].Reset();
	}
}

void MeteoManager::Update() {

	//�^�C�}�[���c���Ă����.
	if (timer > 0) {
		timer -= (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
	}
	//�^�C�}�[��0�ɂȂ�����.
	else {
		GenerateMeteo(); //覐ΐ���.
	}

	//�S覐΃��[�v.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		meteo[i].Update(); //�X�V.
	}
}

void MeteoManager::Draw() {
	//�S覐΃��[�v.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		meteo[i].Draw(); //�`��.
	}
}

//覐ΐ���.
void MeteoManager::GenerateMeteo(){

	//�󂢂Ă鏊��T��.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		if (!meteo[i].GetActive()) {
			meteo[i].Spawn();         //�o��.
			timer = METEO_SPAWN_SPAN; //�^�C�}�[�ĊJ.

			break; //�o������.
		}
	}
}

//�Ŋ���覐΍��W��T��.
BOOL MeteoManager::GetMeteoPosNearest(DBL_XY _startPos, DBL_XY* _nearPos) {
	
	BOOL isExistMeteo = FALSE; //1�ł�覐΂����邩.

	double shortest = 0; //�b��̍ŒZ����.

	//�S覐΃��[�v.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		//�L���Ȃ�.
		if (meteo[i].GetActive()) {

			DBL_XY tmpPos = meteo[i].GetPos();          //1�����W�擾.
			double tmpDis = CalcDis(tmpPos, _startPos); //�������v�Z.

			//�������.
			if (i == 0) {
				shortest  = tmpDis; //�b��1��.
				*_nearPos = tmpPos;
			}
			//���߂��ꏊ��������΍X�V.
			else if (tmpDis < shortest){
				shortest  = tmpDis;
				*_nearPos = tmpPos;
			}

			isExistMeteo = TRUE; //覐΂�����.
		}
	}

	return isExistMeteo;
}