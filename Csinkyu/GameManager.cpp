/*
   - GameManager.cpp -
   �Q�[���S�̊Ǘ�.
*/
//#define ODAZIMA //������`����Ə��c����̏�Q���ɐ؂�ւ�.

#include "GameManager.h"
#include "Player.h"
#include "Obstacle.h"
#if defined ODAZIMA
#include "Obstacle2.h"
#include "Obstacle4.h"
#else
#include "Obstacle3.h"


//�v���C���[�̎���.
Player    player({100, 100}, TRUE);
//��Q���̎���.
Obstacle  obstacle[] = {
	Obstacle({150, 150}, 0,  50, 0x00FF00),
	Obstacle({400, 150}, 30, 50, 0x00FF00),
	Obstacle({300, 300}, 60, 80, 0x00FF00)
};

#if defined ODAZIMA
Obstacle2 obstacle2;
Obstacle4 obstacle4;
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

	//�v���C���[class.
	player.Init();
	//��Q��class.
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Init(&player);
	}
#if defined ODAZIMA
	obstacle2.Init(&player);
	obstacle4.Init(&player);
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

	//�v���C���[class.
	player.Update();
	//��Q��class.
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Update();
	}
#if defined ODAZIMA
	obstacle2.Update();
	obstacle4.Update();
#else
	obstacle3.Update();
#endif
}

//�`��.
void GameManager::Draw() {

	//�v���C���[class.
	player.Draw();
	//��Q��class.
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Draw();
	}
#if defined ODAZIMA
	obstacle2.Draw();
	obstacle4.Draw();
#else
	obstacle3.Draw();
#endif

	//�^�C�}�[�\��.
	DrawFormatString(0, 0, 0xFFFFFF, _T("time:%.3f"), GetTime());
}