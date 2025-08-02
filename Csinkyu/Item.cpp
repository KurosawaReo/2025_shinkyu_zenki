/*
   - Item.cpp -
   Item�Ǘ�.
*/
#include "GameManager.h"
#include "Player.h"
#include "EffectManager.h"

#include "Item.h"

//������.
void ItemManager::Init(GameData* _gamedata, Player* _player, EffectManager* _effectMng)
{
	p_gamedata  = _gamedata;
	p_player    = _player;
	p_effectMng = _effectMng;
}
//���Z�b�g.
void ItemManager::Reset()
{
	//�S�ď���.
	for (int i = 0; i < _countof(data); i++) {
		ItemErase(i);
	}
	//�ŏ��̓A�C�e��1��.
	itemCnt = 1;
}
//�X�V.
void ItemManager::Update()
{
	for (int i = 0; i < _countof(data); i++) {

		if (data[i].active) {

			//�J�E���^�[.
			data[i].counter += ((p_gamedata->isSlow) ? SLOW_MODE_SPEED : 1);
			//����.
			data[i].pos.y += ITEM_SPEED * (double)((p_gamedata->isSlow) ? SLOW_MODE_SPEED : 1);
			//�����蔻��.
			CheckHitPlayer(i);

			//��ʉ����𒴂��������.
			if (data[i].pos.y > WINDOW_HEI + ITEM_SIZE) {
				ItemErase(i);
			}
		}
		else {
			//�����\�Ȃ�.
			if (itemCnt >= i+1) {
				//�X���[���[�h���͉��Z���Ȃ�.
				data[i].spawnCounter += (p_gamedata->isSlow) ? 0 : 1;
				//��莞�ԂōĐ���.
				if (data[i].spawnCounter > ITEM_RESPAWN_TIME)
				{
					data[i].spawnCounter = 0; //���Z�b�g.
					ItemSpawn(i);
				}
			}
		}
	}
}
//�`��.
void ItemManager::Draw()
{
	for (int i = 0; i < _countof(data); i++) {

		//�L���ȃA�C�e����`��.
		if (data[i].active) {
			//�������o.
			if (data[i].type == Item_Super) {

				Circle cir = { data[i].pos, 30, COLOR_PLY_REFLECT };

				SetDrawBlendModeST(MODE_ADD, 128 + 127*CalcNumWaveLoop(data[i].counter/20)); //�_��.
				DrawCircleST(&cir, FALSE, TRUE);
				ResetDrawBlendMode();
			}
			//�A�C�e���{��.
			{
				Box box1 = { data[i].pos, {ITEM_SIZE,   ITEM_SIZE  }, COLOR_ITEM }; //{pos}, {size}, color.
				Box box2 = { data[i].pos, {ITEM_SIZE-2, ITEM_SIZE-2}, COLOR_ITEM }; //{pos}, {size}, color.
				DrawBoxST(&box1, ANC_MID, FALSE);
				DrawBoxST(&box2, ANC_MID, FALSE);
			}
		
			// �摜���g�p����ꍇ�̃R�[�h��
			// if (itemGraph != -1) {
			//     DrawGraph((int)itemX, (int)itemY, itemGraph, TRUE);
			// }
		}
	}
}

//�A�C�e������.
void ItemManager::ItemSpawn(int idx) {

	//���W�̐ݒ�.
	data[idx].pos.x = (double)RandNum(ITEM_SIZE, WINDOW_WID-ITEM_SIZE); // X���W�������_���ɐݒ�
	data[idx].pos.y = -ITEM_SIZE;	 								    // ��ʏ㕔�̏����ォ��J�n
	//�^�C�v�����߂�.
	if (p_gamedata->level <= 4) {
		data[idx].type = Item_Normal;
	}
	else {
		data[idx].type = Item_Super; //Lv4����͋����ł�.
	}
	// �A�C�e���̏�Ԑݒ�
	data[idx].active = TRUE; //�A�N�e�B�u�t���O
	data[idx].counter = 0;
}
//�A�C�e������.
void ItemManager::ItemErase(int idx) {
	data[idx].active = FALSE;
	data[idx].counter = 0;
	data[idx].spawnCounter = 0;
}

// �v���C���[�Ƃ̓����蔻��
void ItemManager::CheckHitPlayer(int idx)
{
	//�A�C�e��������or�v���C���[�����Ȃ��Ȃ珈�����Ȃ�.
	if (!data[idx].active || !p_player->GetActive()) {
		return;
	}

	//�v���C���[�̔�����擾.
	Circle* plyHit = p_player->GetHit();
	//�����蔻����l�p�`�Ƃ���.
	Box plyBox  = { plyHit->pos,   {PLAYER_SIZE, PLAYER_SIZE}, {} };
	Box itemBox = { data[idx].pos, {ITEM_SIZE,   ITEM_SIZE},   {} };
	
	//���������ꍇ.
	if (HitBox(&plyBox, &itemBox)) {
		OnHitPlayer(idx);
	}
}

// �v���C���[�Ɠ��������Ƃ��̏���
void ItemManager::OnHitPlayer(int idx)
{
	//�A�C�e�������������.
	GameManager::GetPtr()->TakeItem();
	//�T�E���h.
	SoundST* sound = SoundST::GetPtr();
	sound->Play(_T("TakeItem"),   FALSE, 76); //�|���[��.
	//�G�t�F�N�g����.
	EffectData effect{};
	effect.type = Effect_Score100;
	effect.pos = data[idx].pos;
	p_effectMng->SpawnEffect(&effect);

	/*Circle cir = { p_player.GetPos(), 1000, {} };
	p_laserMng.LaserReflectRange(&cir);*/

	//�v���C���[�̃��[�h�ݒ�.
	switch (data[idx].type)
	{
		case Item_Normal:
			p_player->SetMode(Player_Reflect);
			break;
		case Item_Super:
			p_player->SetMode(Player_SuperReflect);
			break;

		default: assert(FALSE); break;
	}
	//�A�C�e�����폜�i��A�N�e�B�u�ɂ���j
	data[idx].active = FALSE;
	data[idx].counter = 0; //�J�E���^�[�����Z�b�g���čĐ����^�C�}�[�J�n.
	//���W����ʊO�Ɉړ��i�O�̂��߁j
	data[idx].pos = {-100, -100};
}