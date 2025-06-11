/*
   - GameManager.cpp -
   �Q�[���S�̊Ǘ�.
*/
/*--------------------------------------------------------/
   [TODO]
   2025/05/20:
   ���ŃX���[���[�h�������������A���[�U�[�̓������������B
   
   2025/05/26:
   �X���[���[�h�����B���[�U�[�̓����̉������������B
   �E�A�C�e���̎���
   �E�X���[���[�h�̎��Ԑ��� <<< now
   �E��Q��4�̖C�����ʈ��������(�Q�[������??�b�ȍ~)

   2025/06/02:
   �X���[���[�h�̉����܂Ŋ����B
   �E�A�C�e���̗������x�A�萔�������Ă��ς��Ȃ��B
   �E�Ƃ�A���킷���ǂ����邩�l����B

   2025/06/09:
   "���킷"�̕��j����B
   
   1.���ō\�����ꂽ���p�`��覐΂�����I�ɍ~���Ă���(�S�������烉���_��)
   2.�A�C�e�������ƃ��[�U�[�𔽎˂���悤�ɂȂ�A�g�U����悤�ɔ��ł����B
   3.�߂���覐΂�����ꍇ�A覐΂Ɍ������Ĕ��ł����B
   4.���˂������[�U�[��覐΂ɓ�����Ɖ���(�\�Ȃ����A�j���[�V��������ꂽ��)
   �ۑ�_: �ǂ������覐΂̍��W���擾���邩.

   ���c�� �����[�U�[�̔���
   ���V�@ �����ō\�����ꂽ���p�`��覐�

   [�]�T�������]
   �EFPS��m�b�ҋ@�ł͂Ȃ��A���Ԍv���ő��肽��.
/--------------------------------------------------------*/
//#define ALL_OBSTACLE //������`����ƑS�Ă̏�Q�����o��.

#include "Player.h"
#include "Obstacle4.h"
#include "Item.h"
#if defined ALL_OBSTACLE
#include "Obstacle.h"
#include "Obstacle2.h"
#endif

#include "GameManager.h"

#if defined ALL_OBSTACLE
Obstacle obstacle[] = {
	Obstacle( 80, 1,   0x00FF00),
	Obstacle( 60, 0.5, 0x00FF00),
	Obstacle(100, 1,   0x00FF00),
	Obstacle(200, 1,   0x00FF00)
};
Obstacle2 obstacle2;
#endif

//��Q���̎���.
Obstacle4 obstacle4;
Obstacle5 obstacle5;
//�A�C�e���̎���.
Item item;
//�v���C���[�̎���.
Player player;

//������(���̂ݍs��)
void GameManager::Init() {

	srand((unsigned)time(NULL)); //����������.

	data.scene = SCENE_TITLE; //�^�C�g��.

#if defined ALL_OBSTACLE
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Init(&data, &player);
	}
	obstacle2.Init(&data, &player);
#endif

	//��Q��class.
	
		obstacle4.Init(&data, &player);
		obstacle5.Init(&data, &player);
	//�A�C�e��class.
	item.Init(&data, &player);
	//�v���C���[class.
	player.Init(&data);

	Reset();
}

//���Z�b�g(����ł��s��)
void GameManager::Reset() {

	data.isSlow = FALSE; //�X���[���[�h����.

#if defined ALL_OBSTACLE
	obstacle[0].Reset({ 150, 150 }, 0);
	obstacle[1].Reset({ 400, 150 }, 30);
	obstacle[2].Reset({ 300, 300 }, 60);
	obstacle[3].Reset({ 500, 300 }, 90);
	obstacle2.Reset();
#endif

	//��Q��class.
	obstacle4.Reset(0, 30, 3);
	obstacle5.Reset(0, 30, 3);
	//�A�C�e��class.
	item.Reset();
	//�v���C���[class.
	player.Reset({ 100, 100 }, TRUE);
}

//�X�V.
void GameManager::Update() {

	UpdateKey();    //�L�[���͍X�V.
	UpdatePadBtn(); //�R���g���[���̃{�^�����͍X�V.

	//�V�[����.
	switch (data.scene) 
	{
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
	switch (data.scene) 
	{
		case SCENE_TITLE: DrawTitle(); break;
		case SCENE_GAME:  DrawGame();  break;
		case SCENE_END:   DrawEnd();   break;

		default: assert(FALSE); break;
	}
}

//�V�[���ʍX�V.
void GameManager::UpdateTitle() 
{
	//����̑���ŃQ�[���J�n.
	if (IsPushKeyTime(KEY_INPUT_SPACE) == 1 || 
		IsPushPadBtnTime(PAD_INPUT_A) == 1) 
	{
		tmGame.Start();          //�^�C�}�[�J�n.
		data.scene = SCENE_GAME; //�Q�[���V�[����.
	}
}
void GameManager::UpdateGame() {
	
#if false
	//�ғ����ĂȂ����.
	if (!tmSlowMode.GetIsMove()) {
		//L�{�^���ŃX���[���[�h��(��)
		if (IsPushKeyTime(KEY_INPUT_L) == 1) {
			data.isSlow = TRUE;
			tmSlowMode.Start();
		}
	}
#endif
	if (tmSlowMode.GetIsMove()) {
		//���Ԑ؂�ŉ���.
		if(tmSlowMode.GetTime() == 0){
			data.isSlow = FALSE;
			tmSlowMode.Reset();
		}
	}

#if defined ALL_OBSTACLE
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Update();
	}
	obstacle2.Update();
#endif
		obstacle4.Update();
		obstacle5.Update();
	//��Q��class.
	//obstacle4.Update();
	//�A�C�e��class.
	item.Update();
	//�v���C���[class.
	player.Update();
}
void GameManager::UpdateEnd() {

	//����̑���Ń^�C�g����.
	if (IsPushKeyTime(KEY_INPUT_SPACE) == 1 || 
		IsPushPadBtnTime(PAD_INPUT_A) == 1) 
	{
		data.scene = SCENE_TITLE; //�Q�[���V�[����.
		Reset();
	}
}

//�V�[���ʕ`��.
void GameManager::DrawTitle() {
	//�Q�[�����J�n����Ă��Ȃ��ꍇ�͊J�n�ē���\��
	DrawFormatString(260, 160, 0xFFFFFF, _T("PUSH SPACE"));
}
void GameManager::DrawGame() {

	DrawObjests();

	//�^�C�}�[�\��.
	DrawFormatString(0, 0, 0xFFFFFF, _T("time:%.3f"), tmGame.GetTime());
	//�J�E���g�_�E����.
	if (tmSlowMode.GetIsMove() && tmSlowMode.GetTime() > 0) 
	{
		//��ʒ����ɐ�����\��.
		DrawFormatString(WINDOW_WID/2, WINDOW_HEI/2, 0xFFFFFF, _T("%d"), (int)ceil(tmSlowMode.GetTime()));
	}
}
void GameManager::DrawEnd() {
	
	DrawObjests();

	//�^�C�}�[�\��.
	DrawFormatString(0, 0, 0xFFFFFF, _T("time:%.3f"), tmGame.GetTime());
	//�I���ē�.
	DrawFormatString(260, 160, GetColor(255, 0, 0), _T("GAME OVER"));
}

//�I�u�W�F�N�g�̕`��.
void GameManager::DrawObjests() {

#if defined ALL_OBSTACLE
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Draw();
	}
	obstacle2.Draw();
#endif
		obstacle4.Draw();
		obstacle5.Draw();

	//��Q��class.
	//obstacle4.Draw();
	//�A�C�e��class.
	item.Draw();
	//�v���C���[class.
	player.Draw();
}

//�Q�[���I��.
void GameManager::GameEnd() {
	
	data.scene = SCENE_END; //�Q�[���I����.
	
	tmGame.Stop(); //��~.
	data.isSlow = FALSE;
	tmSlowMode.Reset();
}
//�A�C�e�����������.
void GameManager::TakeItem() {

	data.isSlow = TRUE; //�X���[���[�h�ɂ���.
	tmSlowMode.Start(); //�^�C�}�[�J�n.
}