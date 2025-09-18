/*
   - Stage_Endless.cpp -

   �X�e�[�W: �ϋv���[�h.
*/
#include "GameManager.h"
#include "Item.h"
#include "EffectManager.h"
#include "Stage_Endless.h"

//������.
void EndlessStage::Init() {
	//���̎擾.
	p_data      = GameData::GetPtr();
	p_effectMng = EffectManager::GetPtr();
	p_sound     = SoundMng::GetPtr();
}
//���Z�b�g.
void EndlessStage::Reset() {

}
//�X�V.
void EndlessStage::Update() {

	//�ŏ��̂�.
	if (p_data->counter == 0) {
		//�T�E���h.
		p_sound->Play(_T("LevelUp"), false, 100);
		//�G�t�F�N�g.
		EffectData data{};
		data.type = Effect_Endless_Level1;
		data.pos = { WINDOW_WID/2, WINDOW_HEI/2 };
		p_effectMng->SpawnEffect(&data);
	}

	//�J�E���^�[����.
	p_data->counter += ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
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

				GameManager::GetPtr()->ResetStrLaser();
				ItemManager::GetPtr()->AddItemCnt(); //�A�C�e���𑝂₷.

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

				GameManager::GetPtr()->ResetNorLaser();

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
}
//�`��.
void EndlessStage::Draw() {

}