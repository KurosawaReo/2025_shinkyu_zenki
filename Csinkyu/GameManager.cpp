/*
   - GameManager.cpp -
   �Q�[���S�̊Ǘ�.
*/
/*--------------------------------------------------------/
   [TODO]
   2025/05/20:
   ���ŃX���[���[�h�������������A���[�U�[�̓������������B
   �̗͂������������B�\���̓Q�[�W�ŁB
/--------------------------------------------------------*/
#define ODAZIMA //������`����Ə��c����̏�Q���ɐ؂�ւ�.

#include "GameManager.h"
#include "Player.h"
#include "Obstacle.h"
#if defined ODAZIMA
#include "Obstacle2.h"
#include "Obstacle4.h"
#else
#include "Obstacle3.h"
#endif

//�v���C���[�̎���.
Player   player;
//��Q���̎���.
Obstacle obstacle[] = {
	Obstacle(80, 1, 0x00FF00),
	Obstacle(60, 0.5, 0x00FF00),
	Obstacle(100, 1, 0x00FF00),
	Obstacle(200, 1, 0x00FF00)
};

#if defined ODAZIMA
Obstacle2 obstacle2;
Obstacle4 obstacle4;
#else
Obstacle3 obstacle3;
#endif

//������(���̂ݍs��)
void GameManager::Init() {

	srand((unsigned)time(NULL)); //����������.

	data.scene = SCENE_TITLE; //�^�C�g��.

	//��Q��class.
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Init(&data, &player);
	}
#if defined ODAZIMA
	obstacle2.Init(&data, &player);
	obstacle4.Init(&data, &player);
#else
	obstacle3.Init(&player);
#endif
	//�v���C���[class.
	player.Init(&data);

	Reset();
}

//���Z�b�g(����ł��s��)
void GameManager::Reset() {

	data.isSlow = FALSE; //�X���[���[�h����.

	//��Q��class.
	obstacle[0].Reset({ 150, 150 }, 0);
	obstacle[1].Reset({ 400, 150 }, 30);
	obstacle[2].Reset({ 300, 300 }, 60);
	obstacle[3].Reset({ 500, 300 }, 90);
#if defined ODAZIMA
	obstacle2.Reset();
	obstacle4.Reset();
#else
	obstacle3.Reset();
#endif
	//�v���C���[class.
	player.Reset({ 100, 100 }, TRUE);
}

//�X�V.
void GameManager::Update() {

	UpdateKeys(); //�L�[���͍X�V.

	//�V�[����.
	switch (data.scene) {
		case SCENE_TITLE: UpdateTitle(); break;
		case SCENE_GAME:  UpdateGame();  break;
		case SCENE_END:   UpdateEnd();   break;
	
		default: assert(FALSE); break;
	}
}

//�`��.
void GameManager::Draw() {

	//�w�i�F.
	if (data.isSlow) {
		Box box = { {0, 0}, {WINDOW_WID, WINDOW_HEI}, 0x303030 };
		DrawBoxST(&box, FALSE);
	}

	//�V�[����.
	switch (data.scene) {
		case SCENE_TITLE: DrawTitle(); break;
		case SCENE_GAME:  DrawGame();  break;
		case SCENE_END:   DrawEnd();   break;

		default: assert(FALSE); break;
	}
}

//�V�[���ʍX�V.
void GameManager::UpdateTitle() {

	//SPACE�������ꂽ�u�ԁA�Q�[���J�n.
	if (IsPushKeyTime(KEY_INPUT_SPACE) == 1) {
		stTime = clock();        //�J�n����.
		data.scene = SCENE_GAME; //�Q�[���V�[����.
	}
}
void GameManager::UpdateGame() {

	nowTime = clock(); //���ݎ���.

	//�X���[���[�h�؂�ւ�.
	if (IsPushKeyTime(KEY_INPUT_L) == 1) {
		data.isSlow = !data.isSlow;
	}

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
	//�v���C���[class.
	player.Update();
}
void GameManager::UpdateEnd() {

	//SPACE�������ꂽ�u�ԁA�^�C�g����.
	if (IsPushKeyTime(KEY_INPUT_SPACE) == 1) {
		data.scene = SCENE_TITLE; //�Q�[���V�[����.
		Reset();
	}
}

//�V�[���ʕ`��.
void GameManager::DrawTitle() {
	// �Q�[�����J�n����Ă��Ȃ��ꍇ�͊J�n�ē���\��
	DrawFormatString(260, 160, GetColor(255, 255, 255), _T("PUSH SPACE"));
}
void GameManager::DrawGame() {

	DrawObjests();

	//�^�C�}�[�\��.
	DrawFormatString(0, 0, 0xFFFFFF, _T("time:%.3f"), GetTime());
}
void GameManager::DrawEnd() {
	
	DrawObjests();

	//�^�C�}�[�\��.
	DrawFormatString(0, 0, 0xFFFFFF, _T("time:%.3f"), GetTime());
	// �I���ē�.
	DrawFormatString(260, 160, GetColor(255, 0, 0), _T("GAME OVER"));
}

//�I�u�W�F�N�g�̕`��.
void GameManager::DrawObjests() {

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
	//�v���C���[class.
	player.Draw();
}