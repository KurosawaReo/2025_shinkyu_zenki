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

//������.
void GameManager::Init() {
	player.Init();
	obstacle.Init();
	obstacle2.Init();
}

//�X�V.
void GameManager::Update() {
	player.Update();
	obstacle.Update();
	obstacle2.Update();
}

//�`��.
void GameManager::Draw() {
	player.Draw();
	obstacle.Draw();
	obstacle2.Draw();
}