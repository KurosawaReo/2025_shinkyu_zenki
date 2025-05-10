/*
   - GameManager.cpp -
   �Q�[���S�̊Ǘ�.
*/
#include "GameManager.h"
#include "Player.h"
#include "Obstacle2.h"

Player player;
Obstacle2 obstacle2;

//������.
void GameManager::Init() {
	player.Init();
	obstacle2.Init();
}

//�X�V.
void GameManager::Update() {
	player.Update();
	obstacle2.Update();
}

//�`��.
void GameManager::Draw() {
	player.Draw();
	obstacle2.Draw();
}