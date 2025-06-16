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
Obstacle4_1 obstacle4_1;
Obstacle4_2 obstacle4_2;
//�A�C�e���̎���.
Item item;
//�v���C���[�̎���.
Player player;

//������(���̂ݍs��)
void GameManager::Init() {

	srand((unsigned)time(NULL)); //����������.

	//�^�C�g��.
	data.scene = SCENE_TITLE;
	//�t�H���g�쐬.
	data.font1 = CreateFontToHandle(NULL, 30, 1, DX_FONTTYPE_NORMAL);
	data.font2 = CreateFontToHandle(NULL, 20, 1, DX_FONTTYPE_NORMAL);

#if defined ALL_OBSTACLE
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Init(&data, &player);
	}
	obstacle2.Init(&data, &player);
#endif

	//��Q��class.
	obstacle4_1.Init(&data, &player);
	obstacle4_2.Init(&data, &player);
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
	obstacle4_1.Reset(WINDOW_WID/2, 0, 3);
	obstacle4_2.Reset(WINDOW_WID/2, 0, 3);
	//�A�C�e��class.
	item.Reset();
	//�v���C���[class.
	player.Reset({ 100, 100 }, TRUE);
}

//�X�V.
void GameManager::Update() {

	InputST* input = InputST::GetPtr();

	input->UpdateKey();    //�L�[���͍X�V.
	input->UpdatePadBtn(); //�R���g���[���̃{�^�����͍X�V.

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
	InputST* input = InputST::GetPtr();

	//����̑���ŃQ�[���J�n.
	if (input->IsPushKeyTime(KEY_SPACE) == 1 || input->IsPushPadBtnTime(PAD_BTN_X) == 1)
	{
		tmGame.Start();          //�^�C�}�[�J�n.
		data.scene = SCENE_GAME; //�Q�[���V�[����.
	}
}
void GameManager::UpdateGame() {
	
	DrawFormatString(30, 200, 0xFFFFFF, _T("%d"), GetJoypadInputState(DX_INPUT_PAD1));

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

	//��Q��class.
	obstacle4_1.Update();
	obstacle4_2.Update();
	//�A�C�e��class.
	item.Update();
	//�v���C���[class.
	player.Update();
}
void GameManager::UpdateEnd() {

	InputST* input = InputST::GetPtr();

	//����̑���Ń^�C�g����.
	if (input->IsPushKeyTime(KEY_SPACE) == 1 || input->IsPushPadBtnTime(PAD_BTN_A) == 1)
	{
		data.scene = SCENE_TITLE; //�Q�[���V�[����.
		Reset();
	}
}

//�V�[���ʕ`��.
void GameManager::DrawTitle() {
	//�Q�[�����J�n����Ă��Ȃ��ꍇ�͊J�n�ē���\��
	{
		//�e�L�X�g�̐ݒ�.
		STR_DRAW str = { _T("PUSH SPACE"), {WINDOW_WID/2, 160}, 0xFFFFFF };
		//��ʒ����ɕ�����\��.
		DrawStringST(&str, TRUE, data.font2); //font����.
	}
}
void GameManager::DrawGame() {

	DrawObjests();

	//�^�C�}�[�\��.
	DrawFormatStringToHandle(
		0, 0, 0xFFFFFF, data.font2, _T("time:%.3f"), tmGame.GetTime()
	);
	//�J�E���g�_�E����.
	if (tmSlowMode.GetIsMove() && tmSlowMode.GetTime() > 0) 
	{
		//�e�L�X�g�̐ݒ�.
		STR_DRAW str = { _T(""), {WINDOW_WID/2, WINDOW_HEI/2}, 0xFFFFFF };
		sprintf((char*)str.text, "%d", (int)ceil(tmSlowMode.GetTime()));

		//��ʒ����ɐ�����\��.
		DrawStringST(&str, TRUE, data.font1); //font����.
	}
}
void GameManager::DrawEnd() {
	
	DrawObjests();

	//�^�C�}�[�\��.
	DrawFormatStringToHandle(
		0, 0, 0xFFFFFF, data.font2, _T("time:%.3f"), tmGame.GetTime()
	);
	//�I���ē�.
	{
		//�e�L�X�g�̐ݒ�.
		STR_DRAW str = { _T("GAME OVER"), {WINDOW_WID/2, 160}, 0xFF0000 };
		//��ʒ����ɕ�����\��.
		DrawStringST(&str, TRUE, data.font2); //font����.
	}
}

//�I�u�W�F�N�g�̕`��.
void GameManager::DrawObjests() {

#if defined ALL_OBSTACLE
	for (int i = 0; i < _countof(obstacle); i++) {
		obstacle[i].Draw();
	}
	obstacle2.Draw();
#endif

	//��Q��class.
	obstacle4_1.Draw();
	obstacle4_2.Draw();
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