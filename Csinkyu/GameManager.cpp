/*
   - GameManager.cpp -
   �Q�[���S�̊Ǘ�.
*/
#include "GameManager.h"
#include "Player.h"
#include "Obstacle.h"

//��class�̎���.
Player   player;
Obstacle obstacle;

//������.
void GameManager::Init() {
	player.Init();
    obstacle.Init();
}

//�X�V.
void GameManager::Update() {
	player.Update();
	obstacle.Update();
}

//�`��.
void GameManager::Draw() {
	player.Draw();
	obstacle.Draw();
}