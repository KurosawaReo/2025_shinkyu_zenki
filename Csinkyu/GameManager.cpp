/*
   - GameManager.cpp -
   �Q�[���S�̊Ǘ�.
*/
#include "GameManager.h"
#include "Player.h"

//������.
void GameManager::Init() {

}

//�X�V.
void GameManager::Update() {
	m_ang += 1;
}

//�`��.
void GameManager::Draw() {
	INT_XY pos = { 100, 100 };
	DrawLineAng(pos, m_ang, 100, GetColor(0, 255, 0));
}