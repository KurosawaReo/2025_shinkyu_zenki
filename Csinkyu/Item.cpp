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

// �A�C�e���̃��Z�b�g�i�Đ����p�j
void Item::Reset()
{
	// ���W�̏�����
	pos.x = (double)RndNum(ITEM_SIZE, WINDOW_WID- ITEM_SIZE); // X���W�������_���ɐݒ�
	pos.y = -1000;											  // ��ʏ㕔�̏����ォ��J�n
	// �T�C�Y�ƐF�̐ݒ�
	size.x = ITEM_SIZE;
	size.y = ITEM_SIZE;

	// �A�C�e���̏�Ԑݒ�
	active = TRUE;						  // �A�N�e�B�u�t���O
	itemCounter = 0;                      // �J�E���^�[������
	// itemGraph = LoadGraph("item.png"); // �摜���g�p����ꍇ
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
			Reset(); // �V�����A�C�e���Ƃ��čĐ���
		}
	}
	else
	{
		//�A�C�e������������ĂȂ����ł��`�F�b�N.
		if (itemCounter > ITEM_RESPAWN_TIME)//�t���[��1�b�ɐ���.
		{
			Reset();
		}
	}

	CheckHitPlayer(); //�����蔻��.
}

// �v���C���[�Ƃ̓����蔻��
BOOL Item::CheckHitPlayer()
{
	//�A�C�e��������or�v���C���[�����Ȃ��Ȃ珈�����Ȃ�.
	if (!active || !p_player->GetActive()) {
		return FALSE;
	}

	// �v���C���[�̈ʒu�Ɠ����蔻��~���擾
	Circle* playerHit = p_player->GetHit();

	// �A�C�e���̋�`�ƃv���C���[�̉~�̓����蔻��
	double dx = pos.x - playerHit->pos.x;
	double dy = pos.y - playerHit->pos.y;
	double distance = sqrt(dx * dx + dy * dy);
	// �A�C�e���̃T�C�Y���l�����������蔻��
	double itemRadius = size.x / 2.0; // �A�C�e���̔��a�Ƃ��Čv�Z

	if (distance < (playerHit->r + itemRadius)) {
		// ���������ꍇ�̏���
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
	//�G�t�F�N�g����.
	EffectData data{};
	data.type = Effect_Score100;
	data.pos = pos;
	p_effectMng->SpawnEffect(&data);

	// �A�C�e�����폜�i��A�N�e�B�u�ɂ���j
	active = FALSE;
	itemCounter = 0;//�J�E���^�[�����Z�b�g���čĐ����^�C�}�[�J�n.
	// ���W����ʊO�Ɉړ��i�O�̂��߁j
	pos = {-100, -100}; 
}

//�`��.
void Item::Draw()
{
	if (active) {

		// �`��i�����̃R�[�h�����p�j
		Box box1 = { pos, {size.x,   size.y  }, COLOR_ITEM }; //{pos}, {size}, color.
		Box box2 = { pos, {size.x-2, size.y-2}, COLOR_ITEM }; //{pos}, {size}, color.

		DrawBoxST(&box1, TRUE, FALSE);
		DrawBoxST(&box2, TRUE, FALSE);

		// �摜���g�p����ꍇ�̃R�[�h��
		// if (itemGraph != -1) {
		//     DrawGraph((int)itemX, (int)itemY, itemGraph, TRUE);
		// }
	}
}

void Item::ItemMove()
{
	//����.
	pos.y += ITEM_SPEED * (double)((p_gamedata->isSlow) ? SLOW_MODE_SPEED : 1);

#if false //�悭�������@�\.
	// ���E�ɂ����������_���ȓ�����ǉ��i�I�v�V�����j
	if ((int)itemCounter % 20 == 0) {  // ���Ԋu�ō��E�Ɉړ�
		double moveX = ((rand() % 3) - 1) * 0.5;  // -0.5, 0, 0.5�̂����ꂩ
		itemX += moveX;

		// ��ʊO�ɏo�Ȃ��悤�ɐ���
		if (itemX < 0)   itemX = 0;
		if (itemX > 620) itemX = 620;
	}
#endif
}