/*
   - Obstacle4.cpp -
   ��Q���Ǘ�.(���c����)
*/
#include "Player.h"
#include "Obstacle4.h"

void Obstacle4::Init(Player* _player)
{
	LoadGraphST(&img, _T("image/enemy.png"));


	player = _player; //�v���C���[�̎��̃A�h���X�����炤.

	for (int i = 0; i < MAX_M; i++)
	{
		Mv[i] = 0;
	}
	//���˃J�E���g�l�����Z�b�g.
	hsc = 30;
}
void Obstacle4::Update()
{
	enemy4Move();
}
void Obstacle4::Draw()
{
	
}

//�G�̈ړ�.
void Obstacle4::enemy4Move()
{
	
}

