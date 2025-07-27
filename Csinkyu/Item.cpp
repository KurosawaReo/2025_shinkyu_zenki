/*
   - Item.cpp -
   Item�Ǘ�.
*/
#include "GameManager.h"
#include "Player.h"
#include "EffectManager.h"

#include "Item.h"

//������.
void Item::Init(GameData* _gamedata, Player* _player, EffectManager* _effectMng)
{
	p_gamedata  = _gamedata;
	p_player    = _player;
	p_effectMng = _effectMng;
}
//���Z�b�g.
void Item::Reset()
{
	ItemSpawn();
}
//�X�V.
void Item::Update()
{
	//�J�E���^.
	itemCounter += (float)((p_gamedata->isSlow) ? SLOW_MODE_SPEED : 1);

	if (active) {
		ItemMove();

		// ��ʉ����𒴂�����Đ���
		if (pos.y > WINDOW_HEI + size.y) {
			ItemSpawn(); // �V�����A�C�e���Ƃ��čĐ���
		}
	}
	else
	{
		//�A�C�e������������ĂȂ����ł��`�F�b�N.
		if (itemCounter > ITEM_RESPAWN_TIME)//�t���[��1�b�ɐ���.
		{
			ItemSpawn();
		}
	}

	CheckHitPlayer(); //�����蔻��.
}
//�`��.
void Item::Draw()
{
	if (active) {

		//�������o.
		if (type == Item_Super) {

			Circle cir = { pos, 30, COLOR_PLY_REFLECT };

			SetDrawBlendModeST(MODE_ADD, 128 + 127*CalcNumWaveLoop(itemCounter/20)); //�_��.
			DrawCircleST(&cir, FALSE, TRUE);
			ResetDrawBlendMode();
		}
		//�A�C�e���{��.
		{
			Box box1 = { pos, {size.x,   size.y  }, COLOR_ITEM }; //{pos}, {size}, color.
			Box box2 = { pos, {size.x-2, size.y-2}, COLOR_ITEM }; //{pos}, {size}, color.
			DrawBoxST(&box1, TRUE, FALSE);
			DrawBoxST(&box2, TRUE, FALSE);
		}
		
		// �摜���g�p����ꍇ�̃R�[�h��
		// if (itemGraph != -1) {
		//     DrawGraph((int)itemX, (int)itemY, itemGraph, TRUE);
		// }
	}
}

//�A�C�e���ړ�.
void Item::ItemMove()
{
	//����.
	pos.y += ITEM_SPEED * (double)((p_gamedata->isSlow) ? SLOW_MODE_SPEED : 1);
}
//�A�C�e������.
void Item::ItemSpawn() {

	//���W�̐ݒ�.
	pos.x = (double)RandNum(ITEM_SIZE, WINDOW_WID-ITEM_SIZE); // X���W�������_���ɐݒ�
	pos.y = -1000;											  // ��ʏ㕔�̏����ォ��J�n
	//�T�C�Y�ƐF�̐ݒ�.
	size.x = ITEM_SIZE;
	size.y = ITEM_SIZE;
	//�^�C�v�����߂�.
	if (p_gamedata->level <= 3) {
		type = Item_Normal;
	}
	else {
		type = Item_Super; //Lv4����͋����ł�.
	}

	// �A�C�e���̏�Ԑݒ�
	active = TRUE;						  // �A�N�e�B�u�t���O
	itemCounter = 0;                      // �J�E���^�[������
	// itemGraph = LoadGraph("item.png"); // �摜���g�p����ꍇ
}

// �v���C���[�Ƃ̓����蔻��
BOOL Item::CheckHitPlayer()
{
	//�A�C�e��������or�v���C���[�����Ȃ��Ȃ珈�����Ȃ�.
	if (!active || !p_player->GetActive()) {
		return FALSE;
	}

	//�v���C���[�̔�����擾.
	Circle* plyHit = p_player->GetHit();
	//�����蔻����l�p�`�Ƃ���.
	Box plyBox = { plyHit->pos, {PLAYER_SIZE, PLAYER_SIZE}, {} };
	Box itemBox = { pos, size, {} };
	
	//���������ꍇ.
	if (HitBox(&plyBox, &itemBox, TRUE)) {
		OnHitPlayer();
		return TRUE;
	}

	return FALSE;
}

// �v���C���[�Ɠ��������Ƃ��̏���
void Item::OnHitPlayer()
{
	//�A�C�e�������������.
	GameManager::GetPtr()->TakeItem();
	//�T�E���h.
	SoundST* sound = SoundST::GetPtr();
	sound->Play(_T("TakeItem"),   FALSE, 76); //�|���[��.
	//�G�t�F�N�g����.
	EffectData data{};
	data.type = Effect_Score100;
	data.pos = pos;
	p_effectMng->SpawnEffect(&data);

	/*Circle cir = { p_player.GetPos(), 1000, {} };
	p_laserMng.LaserReflectRange(&cir);*/

	//�v���C���[�̃��[�h�ݒ�.
	switch (type) 
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
	active = FALSE;
	itemCounter = 0;//�J�E���^�[�����Z�b�g���čĐ����^�C�}�[�J�n.
	//���W����ʊO�Ɉړ��i�O�̂��߁j
	pos = {-100, -100}; 
}