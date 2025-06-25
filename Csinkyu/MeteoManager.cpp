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
DBL_XY MeteoManager::GetMeteoPosNearest(DBL_XY _pivotPos) {
	
	DBL_XY nearPos;  //�Ŋ����W.
	double shortest; //�b��̍ŒZ����.

	//�S覐΃��[�v.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		//�L���Ȃ�.
		if (meteo[i].GetActive()) {

			DBL_XY tmpPos = meteo[i].GetPos();          //1�����W�擾.
			double tmpDis = CalcDis(tmpPos, _pivotPos); //�������v�Z.

			//�������.
			if (i == 0) {
				shortest = tmpDis; //�b��1��.
				nearPos  = tmpPos;
			}
			//���߂��ꏊ��������΍X�V.
			else if (tmpDis < shortest){
				shortest = tmpDis;
				nearPos  = tmpPos;
			}
		}
	}

	return nearPos; //�Ŋ����W��Ԃ�.
}