/*
   - GameManager.cpp -
   �Q�[���S�̊Ǘ�.
*/
#define ODAZIMA //������`����Ə��c����̏�Q���ɐ؂�ւ�.

#include "GameManager.h"
#include "Player.h"
#include "Obstacle.h"
#if defined ODAZIMA
#include "Obstacle2.h"
#else
#include "Obstacle3.h"
#endif

//��class�̎���.
Player    player;
Obstacle  obstacle;

#if defined ODAZIMA
Obstacle2 obstacle2;
#else
Obstacle3 obstacle3;
#endif

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
#if defined ODAZIMA
	obstacle2.Init(&player);
#else
	obstacle3.Init(&player);
#endif
}

//�X�V.
void GameManager::Update() {

	//�������̂ݍX�V.
	if (player.GetActive()) {
		nowTime = clock(); //���ݎ���.
	}

	player.Update();
	//obstacle.Update();
#if defined ODAZIMA
	obstacle2.Update();
#else
	obstacle3.Update();
#endif
}

//�`��.
void GameManager::Draw() {
	player.Draw();
	//obstacle.Draw();
#if defined ODAZIMA
	obstacle2.Draw();
#else
	obstacle3.Draw();
#endif

	//�^�C�}�[�\��.
	DrawFormatString(0, 0, 0xFFFFFF, _T("time:%.3f"), GetTime());
}