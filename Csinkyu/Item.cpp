/*
   - Item.cpp -
   Item�Ǘ�.
*/
#include "Player.h"
#include "GameManager.h"
#include "LaserManager.h"
#include "EffectManager.h"

#include "Item.h"

using namespace Calc; //�v�Z�@�\���g�p.

//������.
void ItemManager::Init()
{
	p_gamedata  = GameData::GetPtr();
	p_player    = Player::GetPtr();
	p_laserMng  = LaserManager::GetPtr();
	p_effectMng = EffectManager::GetPtr();

	//�摜.
	imgItem.LoadFile(_T("Resources/Images/item.png"));	
}
//���Z�b�g.
void ItemManager::Reset()
{
	//�S�ď���.
	for (int i = 0; i < _countof(items); i++) {
		ItemErase(i);
	}
	//�ŏ��̓A�C�e��1��.
	itemMaxCnt = 1;
}
//�X�V.
void ItemManager::Update()
{
	for (int i = 0; i < ITEM_COUNT; i++) {

		//�o���ς݃A�C�e��.
		if (items[i].active) {

			//�J�E���^�[.
			items[i].counter += p_gamedata->speedRate;
			//����.
			items[i].pos.y += ITEM_SPEED * p_gamedata->speedRate;
			//�����蔻��.
			CheckHitPlayer(i);

			//��ʉ����𒴂��������.
			//�`���[�g���A���e�L�X�g�p�ɗ]��������.
			if (items[i].pos.y > WINDOW_HEI + ITEM_SIZE + 50) {
				ItemErase(i);
			}
		}
		//���o���A�C�e��.
		else {
			//�����\�Ȃ�.
			if (i+1 <= itemMaxCnt) {
				//���˃��[�h���͉��Z���Ȃ�.
				items[i].spawnCounter += (p_gamedata->isReflectMode) ? 0 : 1;
				//��莞�ԂōĐ���.
				if (items[i].spawnCounter > ITEM_RESPAWN_TIME)
				{
					items[i].spawnCounter = 0; //���Z�b�g.
					ItemSpawn(i);
				}
			}
		}
	}

	//�����҂��Ȃ�(����������������������Ȃ炱����)
	if (isItemUseWait) {
		isItemUseWait = false;
		ItemUse(); //�A�C�e������.
	}
}
//�`��.
void ItemManager::Draw()
{
	for (int i = 0; i < _countof(items); i++) {

		//�L���ȃA�C�e����`��.
		if (items[i].active) {
			//�������o.
			if (items[i].type == Item_Super) {

				Circle cir = { items[i].pos, 30, COLOR_PLY_REFLECT };

				SetDrawBlendModeST(MODE_ADD, 128 + 127*CalcNumWaveLoop(items[i].counter/20)); //�_��.
				DrawCircleST(&cir, false, true);
				ResetDrawBlendMode();
			}
			//�A�C�e���{��.
			{
				//Box box1 = { data[i].pos, {ITEM_SIZE,   ITEM_SIZE  }, COLOR_ITEM }; //{pos}, {size}, color.
				//Box box2 = { data[i].pos, {ITEM_SIZE-2, ITEM_SIZE-2}, COLOR_ITEM }; //{pos}, {size}, color.
				//DrawBoxST(&box1, ANC_MID, false);
				//DrawBoxST(&box2, ANC_MID, false);

				imgItem.DrawExtend(items[i].pos, {0.045, 0.045}, ANC_MID, true, true);

				//�`���[�g���A���p.
				if (p_gamedata->stage == STAGE_TUTORIAL) {
					DrawStr str(_T("�A�C�e��"), items[i].pos.Add(0, -35).ToIntXY(), COLOR_ITEM);
					str.Draw();
				}
			}
		}
	}
}

//�A�C�e������.
void ItemManager::ItemSpawn(int idx) {

	//���W�̐ݒ�.
	items[idx].pos.x = (double)RandNum(ITEM_SIZE, WINDOW_WID-ITEM_SIZE); // X���W�������_���ɐݒ�
	items[idx].pos.y = -ITEM_SIZE;					        		    // ��ʏ㕔�̏����ォ��J�n
	//�^�C�v�����߂�.
	if (p_gamedata->level < 5) {
		items[idx].type = Item_Normal;
	}
	else {
		items[idx].type = Item_Super; //Lv5����͋����ł�.
	}
	// �A�C�e���̏�Ԑݒ�
	items[idx].active = true; //�A�N�e�B�u�t���O
	items[idx].counter = 0;
}
//�A�C�e������.
void ItemManager::ItemErase(int idx) {
	items[idx].active = false;
	items[idx].counter = 0;
	items[idx].spawnCounter = 0;
}
//�A�C�e������.
void ItemManager::ItemUse()
{
	//�A�C�e�����g�p.
	GameManager::GetPtr()->ItemUsed();
	//�T�E���h.
	SoundMng* sound = SoundMng::GetPtr();
	sound->Play(_T("ItemUse"), false, 76); //�|���[��.
}

// �v���C���[�Ƃ̓����蔻��
void ItemManager::CheckHitPlayer(int idx)
{
	//�A�C�e��������or�v���C���[�����Ȃ��Ȃ珈�����Ȃ�.
	if (!items[idx].active || !p_player->GetActive()) {
		return;
	}

	//�v���C���[�̔�����擾.
	Circle plyHit = p_player->GetHit();
	//�����蔻����l�p�`�Ƃ���.
	Box itemBox = { items[idx].pos, {ITEM_SIZE, ITEM_SIZE}, {} };
	
	//���������ꍇ.
	if (HitBoxCir(&itemBox, &plyHit)) {

		//�G�t�F�N�g����.
		EffectData effect{};
		effect.type = Effect_Score100;
		effect.pos = items[idx].pos;
		p_effectMng->SpawnEffect(&effect);
		//�X�R�A���Z.
		p_gamedata->score += SCORE_TAKE_ITEM;

		//�v���C���[�̃��[�h�ݒ�.
		switch (items[idx].type)
		{
			case Item_Normal:
				p_player->SetMode(Player_Reflect);
				break;
			case Item_Super:
				p_player->SetMode(Player_SuperReflect);
				break;

			default: assert(FALSE); break;
		}

		//���W����ʏ�Ɉړ�.
		items[idx].pos = { -100, -100 };
		//�S�ẴA�C�e��.
		for (int i = 0; i < ITEM_COUNT; i++) {
			items[i].active  = false; //�폜(��A�N�e�B�u��)
			items[i].counter = 0;     //�J�E���^�[���Z�b�g.
		}

		isItemUseWait = true; //�����҂�.
	}
}