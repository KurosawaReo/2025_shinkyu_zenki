/*
   - GameManager.cpp -
   �Q�[���S�̊Ǘ�.
*/
#include "GameManager.h"
#include "Player.h"
#include "Obstacle.h"
#include "Obstacle3.h"

//��class�̎���.
Player    player;
Obstacle  obstacle;
Obstacle3 obstacle3;

//get.
float GameManager::GetTime() {
	return (float)(nowTime - stTime)/1000; //�����̍�.
}

//������.
void GameManager::Init() {

	srand((unsigned)time(NULL)); //����������.

	stTime = clock(); //�J�n����.

	player.Init();
	//obstacle.Init();
	obstacle3.Init(&player);
}

//�X�V.
void GameManager::Update() {

	//�������̂ݍX�V.
	if (player.GetActive()) {
		nowTime = clock(); //���ݎ���.
	}

	player.Update();
	//obstacle.Update();
	obstacle3.Update();
}

//�`��.
void GameManager::Draw() {
	player.Draw();
	//obstacle.Draw();
	obstacle3.Draw();

	//�^�C�}�[�\��.
	DrawFormatString(0, 0, 0xFFFFFF, _T("time:%.3f"), GetTime());
}