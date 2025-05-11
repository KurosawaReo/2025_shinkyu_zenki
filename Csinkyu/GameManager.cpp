/*
   - GameManager.cpp -
   �Q�[���S�̊Ǘ�.
*/
#include "GameManager.h"
#include "Player.h"
#include "Obstacle.h"
#include "Obstacle2.h"

//��class�̎���.
Player player;
Obstacle  obstacle;
Obstacle2 obstacle2;

//get.
float GameManager::GetTime() {
	return (float)(nowTime - stTime)/1000; //�����̍�.
}

//������.
void GameManager::Init() {
	stTime = clock(); //�J�n����.

	player.Init();
	obstacle.Init();
	obstacle2.Init();
}

//�X�V.
void GameManager::Update() {

	nowTime = clock(); //���ݎ���.

	player.Update();
	obstacle.Update();
	obstacle2.Update();
}

//�`��.
void GameManager::Draw() {
	player.Draw();
	obstacle.Draw();
	obstacle2.Draw();

	//�^�C�}�[�\��.
	DrawFormatString(0, 0, 0xFFFFFF, _T("time:%.3f"), GetTime());
}