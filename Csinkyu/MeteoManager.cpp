/*
   - MeteoManager.cpp -
   覐΂̏o�����Ǘ�����.
*/
#include "MeteoManager.h"

void MeteoManager::Init(GameData* _data, Player* _player, EffectManager* _effectMng) {

	p_data      = _data;
	p_player    = _player;
	p_effectMng = _effectMng;

	//�S覐΃��[�v.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		meteo[i].Init(_data);
	}
}

void MeteoManager::Reset() {

	timer = METEO_SPAWN_SPAN; //��������.

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
		SpawnMeteo(); //覐ΐ���.
		timer = METEO_SPAWN_SPAN * p_data->spawnRate; //�^�C�}�[�ĊJ(���X�ɒZ���Ȃ�)
	}

	//�S覐΃��[�v.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		meteo[i].Update(); //�X�V.
	}
	//�v���C���[�Ƃ̓����蔻��.
	if (IsHitMeteos(p_player->GetHit(), FALSE)) {
		p_player->PlayerDeath(); //���S.
	}
}

void MeteoManager::Draw() {

	//�S覐΃��[�v.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		meteo[i].Draw(); //�`��.
	}
}

//覐ΐ���.
void MeteoManager::SpawnMeteo(){

	//�󂢂Ă鏊��T��.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		if (!meteo[i].GetActive()) {

			meteo[i].Spawn(); //�o��.
			break;            //�o������.
		}
	}
}

//覐΂̂ǂꂩ1�ł��������Ă��邩.
BOOL MeteoManager::IsHitMeteos(Circle* cir, BOOL isDestroy) {

	BOOL hit;

	//�S覐΃��[�v.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		hit = meteo[i].IsHitMeteo(cir); //1��������.
		//�������.
		if (hit) {
			if (isDestroy) {
				//���ĂȂ�覐΂ł����.
				if (meteo[i].GetState() == Meteo_Normal) {

					meteo[i].Destroy();                                  //覐΂�j��.
					p_data->score += SCORE_BREAK_METEO;                  //�X�R�A���Z.
					p_effectMng->SpawnEffect(Effect_Score500, cir->pos); //�G�t�F�N�g����.

					SoundST* sound = SoundST::GetPtr();
					sound->Play(_T("Break"), FALSE, 80); //�T�E���h.
				}
			}
			return TRUE; //1�ł��������Ă���.
		}
	}
	return FALSE; //�ǂ���������Ă��Ȃ�.
}

//�Ŋ���覐΍��W��T��.
BOOL MeteoManager::GetMeteoPosNearest(DBL_XY _startPos, DBL_XY* _nearPos) {

	BOOL isExistMeteo = FALSE; //1�ł�覐΂����邩.
	double shortest = -1; //�b��̍ŒZ����.

	//�S覐΃��[�v.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		//�L�����A�j�󂳂�ĂȂ��Ȃ�.
		if (meteo[i].GetActive() && meteo[i].GetState() == Meteo_Normal) {

			DBL_XY tmpPos = meteo[i].GetPos();          //1�����W�擾.
			double tmpDis = CalcDis(tmpPos, _startPos); //�������v�Z.

			//�������.
			if (shortest == -1) {
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