/*
   - Stage_Endless.cpp -

   �X�e�[�W: �ϋv���[�h.
*/
#include "LaserManager.h"
#include "Obst_NormalLaser.h"
#include "Obst_StraightLaser.h"
#include "Obst_MeteorManager.h"
#include "Obst_Ripples.h"
#include "Obst_Fireworks.h"
#include "Item.h"
#include "EffectManager.h"
#include "GameManager.h"

#include "Stage_Endless.h"

//������.
void EndlessStage::Init() {
	//���̎擾.
	p_data         = &GameData::GetInst();
	p_gameMng      = &GameManager::GetInst();
	p_laserMng     = &LaserManager::GetInst();
	p_meteorMng    = &MeteorManager::GetInst();
	p_ripples      = &Ripples::GetInst();
	p_itemMng      = &ItemManager::GetInst();
	p_fireworksMng = &FireworksManager::GetInst();
	p_effectMng    = &EffectManager::GetInst();
	p_input        = &InputMng::GetInst();
	p_sound        = &SoundMng::GetInst();
}
//���Z�b�g.
void EndlessStage::Reset() {

}
//�X�V.
void EndlessStage::Update() {

#if defined _DEBUG //Release�ł͓���Ȃ�.
	//�^�C�}�[����(Debug)
	if (p_input->IsPushKey(KeyID::L) == 1) {
		p_data->counter += 30;
	}
#endif

	//�ŏ��̂�.
	if (p_data->counter == 0) {
		//�T�E���h.
		p_sound->Play(_T("LevelUp"), false, 100);
		//�G�t�F�N�g.
		EffectData data{};
		data.type = Effect_Endless_Level1;
		data.pos = { WINDOW_WID/2, WINDOW_HEI/2 };
		p_effectMng->SpawnEffect(&data);

		//�����\�ɂ���.
		p_meteorMng->SetIsSpawnAble(true);
		p_itemMng->  SetIsSpawnAble(true);
	}

	//�J�E���^�[����.
	p_data->counter += p_data->speedRate;
	//�o���Ԋu.
	p_data->spawnRate = 1.0f/(1+(p_data->counter/8000)); //100%���班��������.
	//���x���Ǘ�.
	switch (p_data->level)
	{
		case 1:
			if (p_data->counter >= 1500) { //1500 = �o���Ԋu��??%�n�_.
				p_data->level = 2; //Lv2��.

				//�T�E���h.
				p_sound->Play(_T("LevelUp"), false, 100);
				//�G�t�F�N�g.
				EffectData data{};
				data.type = Effect_Endless_Level2;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				p_effectMng->SpawnEffect(&data);
			}
			break;
		case 2:
			if (p_data->counter >= 3500) { //3500 = �o���Ԋu��??%�n�_.
				p_data->level = 3; //Lv3��.

				//�T�E���h.
				p_sound->Play(_T("LevelUp"), false, 100);
				//�G�t�F�N�g.
				EffectData data{};
				data.type = Effect_Endless_Level3;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				p_effectMng->SpawnEffect(&data);
			}
			break;
		case 3:
			if (p_data->counter >= 6000) { //6000 = �o���Ԋu��??%�n�_.
				p_data->level = 4; //Lv4��.

				p_itemMng->AddItemCnt(); //�A�C�e���𑝂₷.

				//�T�E���h.
				p_sound->Play(_T("LevelUp"), false, 100);
				//�G�t�F�N�g.
				EffectData data{};
				data.type = Effect_Endless_Level4;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				p_effectMng->SpawnEffect(&data);
			}
			break;
		case 4:
			if (p_data->counter >= 9000) { //9000 = �o���Ԋu��??%�n�_.
				p_data->level = 5; //Lv5��.

				p_gameMng->ResetNorLaser();

				//�T�E���h.
				p_sound->Play(_T("LevelUp"), false, 100);
				//�G�t�F�N�g.
				EffectData data{};
				data.type = Effect_Endless_Level5;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				p_effectMng->SpawnEffect(&data);
			}
			break;
		case 5:
			//�ŏI���x��.
			break;

		default: assert(FALSE); break;
	}

	UpdateObjects();
}
//�`��.
void EndlessStage::Draw() {
	DrawObjects();
}

//�I�u�W�F�N�g�̍X�V.
void EndlessStage::UpdateObjects() {

	//Lv1�ȏ�.
	p_laserMng->Update();
	p_gameMng->laserNor1->Update();
	p_gameMng->laserNor2->Update();
	p_meteorMng->Update();
	p_itemMng->Update();
	//Lv2�ȏ�.
	if (p_data->level >= 2) {
		p_gameMng->laserStr[0]->Update();
		p_gameMng->laserStr[1]->Update();
	}
	//Lv3�ȏ�.
	if (p_data->level >= 3) {
		p_ripples->Update();
	}
	//Lv4�ȏ�.
	if (p_data->level >= 4) {
		p_fireworksMng->Update();
	}
	//Lv5�ȏ�.
	if (p_data->level >= 5) {
		p_gameMng->laserNor3->Update();
		p_gameMng->laserNor4->Update();
	}
}
//�I�u�W�F�N�g�̕`��.
void EndlessStage::DrawObjects() {

	//Lv1�ȏ�.
	p_laserMng->Draw();
	p_gameMng->laserNor1->Draw();
	p_gameMng->laserNor2->Draw();
	p_meteorMng->Draw();
	p_itemMng->Draw();
	//Lv2�ȏ�.
	if (p_data->level >= 2) {
		p_gameMng->laserStr[0]->Draw();
		p_gameMng->laserStr[1]->Draw();
	}
	//Lv3�ȏ�.
	if (p_data->level >= 3) {
		p_ripples->Draw();
	}
	//Lv4�ȏ�.
	if (p_data->level >= 4) {
		p_fireworksMng->Draw();
	}
	//Lv5�ȏ�.
	if (p_data->level >= 5) {
		p_gameMng->laserNor3->Draw();
		p_gameMng->laserNor4->Draw();
	}
}