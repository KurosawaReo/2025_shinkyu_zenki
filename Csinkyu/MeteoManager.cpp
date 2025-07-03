/*
   - MeteoManager.cpp -
   覐΂̏o�����Ǘ�����.
*/
#include "MeteoManager.h"

void MeteoManager::Init(GameData* _data, Player* _player) {

	p_data = _data;

	//�S覐΃��[�v.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		meteo[i].Init(_data, _player);
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

#if true
		int x =   0 + 10 * (i%100);
		int y = 100 + 20 * (i/100);
		DrawString(0, 80, _T("覐΂�active"), 0xFF00FF);
		DrawFormatString(x, y, 0xFF00FF, _T("%d"), meteo[i].GetActive());
#endif
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

//覐΂̂ǂꂩ1�ł��������Ă��邩.
BOOL MeteoManager::IsHitMeteos(Circle* pos) {

	BOOL hit;
	
	//�S覐΃��[�v.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		if (meteo[i].GetActive()) {
			
			hit = meteo[i].IsHitMeteo(pos); //1��������.
			if (hit) {
				meteo[i].Destroy(); //覐΂�j��.
				return TRUE; //1�ł��������Ă���.
			}
		}
	}
	return FALSE; //�ǂ���������Ă��Ȃ�.
}