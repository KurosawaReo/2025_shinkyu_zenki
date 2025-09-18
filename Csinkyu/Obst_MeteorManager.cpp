/*
   - Obst_MeteorManager.cpp -

   ��Q��: 覐Ώo���Ǘ�.
*/
#include "GameManager.h"
#include "EffectManager.h"
#include "Obst_MeteorManager.h"

using namespace Calc; //�v�Z�@�\���g�p.

void MeteorManager::Init() {

	p_data      = GameData::GetPtr();
	p_player    = Player::GetPtr();
	p_effectMng = EffectManager::GetPtr();

	//�S覐΃��[�v.
	for (int i = 0; i < METEOR_CNT_MAX; i++) {
		meteor[i].Init();
	}
}

void MeteorManager::Reset() {

	timer = METEOR_SPAWN_SPAN; //��������.

	//�S覐΃��[�v.
	for (int i = 0; i < METEOR_CNT_MAX; i++) {
		meteor[i].Reset();
	}
}

void MeteorManager::Update() {

	//�^�C�}�[���c���Ă����.
	if (timer > 0) {
		timer -= (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
	}
	//�^�C�}�[��0�ɂȂ�����.
	else {
		SpawnMeteor(); //覐ΐ���.
		timer = METEOR_SPAWN_SPAN * p_data->spawnRate; //�^�C�}�[�ĊJ(���X�ɒZ���Ȃ�)
	}

	//�S覐΃��[�v.
	for (int i = 0; i < METEOR_CNT_MAX; i++) {
		meteor[i].Update(); //�X�V.
	}
	//�v���C���[�Ƃ̓����蔻��.
	if (IsHitMeteors(p_player->GetHit(), false)) {
		p_player->PlayerDeath(); //���S.
	}
}

void MeteorManager::Draw() {

	//�S覐΃��[�v.
	for (int i = 0; i < METEOR_CNT_MAX; i++) {
		meteor[i].Draw(); //�`��.
	}
}

//覐ΐ���.
void MeteorManager::SpawnMeteor(){
	
	//�󂢂Ă鏊��T��.
	for (int i = 0; i < METEOR_CNT_MAX; i++) {
		if (!meteor[i].GetActive()) {

			meteor[i].Spawn(); //�o��.
			break;            //�o������.
		}
	}
}

//覐΂̂ǂꂩ1�ł��������Ă��邩.
bool MeteorManager::IsHitMeteors(Circle* cir, bool isDestroy) {

	bool hit;

	//�S覐΃��[�v.
	for (int i = 0; i < METEOR_CNT_MAX; i++) {
		hit = meteor[i].IsHitMeteor(cir); //1��������.
		//�������.
		if (hit) {
			if (isDestroy) {
				//���ĂȂ�覐΂ł����.
				if (meteor[i].GetState() == Meteor_Normal) {

					meteor[i].Destroy();                 //覐΂�j��.
					p_data->score += SCORE_BREAK_METEO; //�X�R�A���Z.

					//�G�t�F�N�g.
					EffectData data{};
					data.type = Effect_Score500;
					data.pos = cir->pos;
					p_effectMng->SpawnEffect(&data);
					//�T�E���h.
					SoundMng* sound = SoundMng::GetPtr();
					sound->Play(_T("Break"), false, 74);
				}
			}
			return true; //1�ł��������Ă���.
		}
	}
	return false; //�ǂ���������Ă��Ȃ�.
}

//�Ŋ���覐΍��W��T��.
bool MeteorManager::GetMeteorPosNearest(DBL_XY _startPos, DBL_XY* _nearPos) {

	bool isExistMeteo = false; //1�ł�覐΂����邩.
	double shortest = -1; //�b��̍ŒZ����.

	//�S覐΃��[�v.
	for (int i = 0; i < METEOR_CNT_MAX; i++) {
		//�L�����A�j�󂳂�ĂȂ��Ȃ�.
		if (meteor[i].GetActive() && meteor[i].GetState() == Meteor_Normal) {

			DBL_XY tmpPos = meteor[i].GetPos();           //1�����W�擾.
			double tmpDis = CalcDist(tmpPos, _startPos); //�������v�Z.

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

			isExistMeteo = true; //覐΂�����.
		}
	}

	return isExistMeteo;
}