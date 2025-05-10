/*
   - GameManager.cpp -
   �Q�[���S�̊Ǘ�.
*/
#include "GameManager.h"
#include "Player.h"
#include"Obstacle2.h"

Player player;
Obstacle2 obstacle2;
//������.
void GameManager::Init() {
	player.Init();
  obstacle2.Init();
}

//�X�V.
void GameManager::Update() {
	m_ang += 1;
	player.Update();
	obstacle2.Update();
}

//�`��.
void GameManager::Draw() {
	INT_XY pos = { 100, 100 };
	DrawLineAng(pos, m_ang, 100, GetColor(0, 255, 0));
	player.Draw();
	obstacle2.Draw();
}