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
   �EFPS��m�b�ҋ@�ł͂Ȃ��A���Ԍv���ő��肽��

   2025/06/23:
   ����覐΂��~��̂���������A���킩�ǂ������������B
   ����isSlow�ɂ��X���[�ɂȂ鏊��double�^�ɂ��܂��L���X�g�ł��Ă��炸
   ��U�S�Ă̑��x���������Ă鏊���m�F�������B

   2025/06/26:
   覐΂͑�̐���ɂł����Ǝv����B
   ���[�U�[�̔��˂��A�O�p�`�̓G�̐�[����o��悤�ɂł�����ǂ������B
   �ł����ɎO�p�`����]������B

   2025/06/30:
   ���ő��p�`�͊��������B
   �����ӂ����܂��q����Ȃ����߁A���̃��W�b�N�����������B
   (���_�̈ʒu����]���g���đ���΍s����C������)

   2025/07/14:
   ���܂�i���Ȃ��B���˃��[�U�[�̉�]���͈�U���������A�����͉������B
   �O�����\��܂łɂ��̕ӂ͂���Ă�������
   �E覐΂����鎞�A�\�����Ă�����o���o���ɂȂ�悤�ɂ���
   �E�ǔ����[�U�[�Ƃ͕ʂɁA�������[�U�[��ǉ�����
   �E�T�E���h�֌W

   2025/07/15:
   ���ˉ������B���̃Q�[���̕��j�������Ă����B
   �u覐΂�j�󂷂�ƃX�R�A�𓾂��A���̃X�R�A�������Q�[���v�ōs����C������B
/--------------------------------------------------------*/

#include "MeteoManager.h"
#include "LaserManager.h"
#include "MapGimmickLaserManager.h"
#include "MapGimmickLaser.h"
#include "Obstacle4.h"
#include "Obstacle4main.h"
#include "Obstacle5.h"

#include "Item.h"
#include "Player.h"

#include "GameManager.h"

//��Q���̎���.
Obstacle4_1 obstacle4_1;
Obstacle4_2 obstacle4_2;
Obstacle4_3 obstacle4_3;
Obstacle4_4 obstacle4_4;
Obstacle5   obstacle5;
MapGimmickLaserManager mglMng;
MapGimmickLaser mgl;
//��Q���Ǘ��̎���.
MeteoManager meteoMng;
LaserManager laserMng;
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
	data.font1 = CreateFontToHandle(NULL, 30, 1);
	data.font2 = CreateFontToHandle(NULL, 20, 1);
	//�摜�ǂݍ���.
	int ret = LoadGraphST(&data.imgLogo, _T("Resources/Images/REFLINE���S.png"));
	//�T�E���h�ǂݍ���.
	SoundST* sound = SoundST::GetPtr();
	sound->LoadFile(_T("Resources/Sounds/audiostock_132563.mp3"),  _T("BGM1"));
	sound->LoadFile(_T("Resources/Sounds/audiostock_1535055.mp3"), _T("BGM2"));

	//��Q��class.
	obstacle4_1.Init(&data, &player, &meteoMng, &laserMng);
	obstacle4_2.Init(&data, &player, &meteoMng, &laserMng);
	//obstacle4_3.Init(&data, &player, &meteoMng, &laserMng);
	//obstacle4_4.Init(&data, &player, &meteoMng, &laserMng);
	obstacle5.Init(&data, &player);
	//��Q���Ǘ�class.
	meteoMng.Init(&data, &player);
	laserMng.Init(&data, &player, &meteoMng);
	mglMng.Init(&data, &player, &meteoMng);
	mgl.Init(&data, &player, &meteoMng);
	//�A�C�e��class.
	item.Init(&data, &player);
	//�v���C���[class.
	player.Init(&data);

	Reset();
}

//���Z�b�g(����ł��s��)
void GameManager::Reset() {

	data.score  = 0;     //�X�R�A���Z�b�g.
	data.isSlow = FALSE; //�X���[���[�h����.

	SoundST* sound = SoundST::GetPtr();
	sound->FadeInPlay(_T("BGM1"), 80, 3, TRUE);

	//��Q��class.
	obstacle4_1.Reset(WINDOW_WID/2,    0, 3, MOVE_RIGHT);
	obstacle4_2.Reset(WINDOW_WID/2,    0, 3, MOVE_LEFT);
	//obstacle4_3.Reset(WINDOW_WID/2, 1070, 3, MOVE_RIGHT);
	//obstacle4_4.Reset(WINDOW_WID/2, 1070, 3, MOVE_LEFT);
	//obstacle5.Reset(WINDOW_WID/2, WINDOW_HEI/1, 0, 0); // ��ʒ����ɔz�u.
	mglMng.Reset();
	mgl.Reset();
	//覐ΊǗ�class.
	meteoMng.Reset();
	laserMng.Reset();
	//�A�C�e��class.
	item.Reset();
	//�v���C���[class.
	player.Reset({ WINDOW_WID/2, WINDOW_HEI/2 }, TRUE);
}

//�X�V.
void GameManager::Update() {

	InputST* input = InputST::GetPtr(); //input�N���X���g����悤��.
	SoundST* sound = SoundST::GetPtr(); //sound�N���X���g����悤��.

	input->UpdateKey();    //�L�[���͍X�V.
	input->UpdatePadBtn(); //�R���g���[���̃{�^�����͍X�V.
	sound->Update();       //�T�E���h�X�V.

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

	DrawBG();

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
	
//	DrawFormatString(30, 200, 0xFFFFFF, _T("%d"), GetJoypadInputState(DX_INPUT_PAD1));

	if (tmSlowMode.GetIsMove()) {
		//���Ԑ؂�ŉ���.
		if(tmSlowMode.GetPassTime() == 0){
			data.isSlow = FALSE;
			player.SetReflectionMode(FALSE); //���˃��[�h�I��.
			tmSlowMode.Reset();
		}
	}

	//��Q��class.
	obstacle4_1.Update();
	obstacle4_2.Update();
	//obstacle4_3.Update();
	//obstacle4_4.Update();
	//obstacle5.Update();
	mglMng.Update();
	mgl.Update();
	//��Q���Ǘ�class.
	meteoMng.Update();
	laserMng.Update();
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
	
	//�摜�̕\��.
	IMG_DRAW_EXTEND img = { data.imgLogo, {WINDOW_WID/2, WINDOW_HEI/2}, {data.imgLogo.size.x/2, data.imgLogo.size.y/2} };
	DrawExtendGraphST(&img, TRUE);

	//�e�L�X�g�̕\��..
	STR_DRAW str = { _T("PUSH SPACE"), {WINDOW_WID/2, 160}, 0xFFFFFF };
	DrawStringST(&str, TRUE, data.font2); //font����.
	
}
void GameManager::DrawGame() {

	DrawObjects();

	//UI�\��.
	DrawFormatStringToHandle(
		0, 0, 0xFFFFFF, data.font2, _T("time:%.3f"), tmGame.GetPassTime()
	);
	DrawFormatStringToHandle(
		0, 20, 0xFFFFFF, data.font2, _T("score:%d"), data.score
	);
	//�X���[���[�h���o.
	DrawSlowMode();
}
void GameManager::DrawEnd() {
	
	DrawObjects();

	//�^�C�}�[�\��.
	DrawFormatStringToHandle(
		0, 0, 0xFFFFFF, data.font2, _T("time:%.3f"), tmGame.GetPassTime()
	);
	//�I���ē�.
	{
		//�e�L�X�g�̐ݒ�.
		STR_DRAW str = { _T("GAME OVER"), {WINDOW_WID/2, 160}, 0xFF0000 };
		STR_DRAW str2 = { {}, {WINDOW_WID / 2, WINDOW_HEI / 2}, 0xFFFFFF };
		swprintf(str2.text, _T("time:%.3f"), tmGame.GetPassTime());

		//��ʒ����ɕ�����\��.
		DrawStringST(&str, TRUE, data.font2); //font����.
		DrawStringST(&str2, TRUE, data.font2);
	}
}

//�w�i�̕`��.
void GameManager::DrawBG() {

	//�w�i�f�U�C��.
	for (int x = 0; x < WINDOW_WID; x += 5) {

		int clr = _int(20 * fabs(sin((double)x / 200))); //�F�̕ω�.
		Line line = { {(double)x, 0},{(double)x, WINDOW_HEI}, GetColor(0, clr, clr) };
		DrawLineST(&line, 5);
	}
	//�w�i(�X���[���[�h).
	if (data.isSlow) {
		//�w�i�F.
		{
			Box box = { {0, 0}, {WINDOW_WID, WINDOW_HEI}, 0x303030 };
			DrawBoxST(&box, FALSE);
		}
		//�g���A�j���[�V����.
		{
			//�ŏ���0.5�b
			float time = 0.5f-(tmSlowMode.GetPassTime()-(SLOW_MODE_TIME-0.5f));
			time = CalcNumEaseOut(time); //�l�̋Ȑ��ϓ�.
			
			Box box = { {WINDOW_WID/2, WINDOW_HEI/2}, {WINDOW_WID * time, WINDOW_HEI * time}, COLOR_PLY_REFLECT };
			DrawBoxST(&box, TRUE, FALSE);
		}
	}
}
//�I�u�W�F�N�g�̕`��.
void GameManager::DrawObjects() {

	//��Q��class.
	obstacle4_1.Draw();
	obstacle4_2.Draw();
	//obstacle4_3.Draw();
	//obstacle4_4.Draw();
	//obstacle5.Draw();
	mglMng.Draw();
	mgl.Draw();
	//��Q���Ǘ�class.
	meteoMng.Draw();
	laserMng.Draw();
	//�A�C�e��class.
	item.Draw();
	//�v���C���[class.
	player.Draw();
}
//�X���[���[�h���o.
void GameManager::DrawSlowMode() {

	//�J�E���g�_�E����.
	if (tmSlowMode.GetIsMove() && tmSlowMode.GetPassTime() > 0)
	{
		//�e�L�X�g������p.
		STR_DRAW str = { {}, {WINDOW_WID / 2, WINDOW_HEI / 2}, 0x00FF00 };
		//�e�L�X�g�̐ݒ�.
		swprintf(str.text, _T("%d"), (int)ceil(tmSlowMode.GetPassTime())); //TCHAR�^�ɕϐ�����.

		//��ʒ����ɐ�����\��.
		{
			double dec = GetDecimal(tmSlowMode.GetPassTime()); //�����������o��.
			SetDrawBlendModeST(MODE_ADD, _int(255 * dec));     //1�b���Ƃɔ����Ȃ鉉�o.
			DrawStringST(&str, TRUE, data.font1);              //font����.
			ResetDrawBlendMode();                              //�߂�.
		}
	}
}

//�Q�[���I��.
void GameManager::GameEnd() {
	
	data.scene = SCENE_END; //�Q�[���I����.
	
	tmGame.Stop(); //��~.
	data.isSlow = FALSE;
	tmSlowMode.Reset();

	SoundST* sound = SoundST::GetPtr();
	sound->FadeOutPlay(_T("BGM1"), 3);
}
//�A�C�e�����������.
void GameManager::TakeItem() {

	data.isSlow = TRUE;             //�X���[���[�h�ɂ���.
	player.SetReflectionMode(TRUE); //���˃��[�h�J�n.
	tmSlowMode.Start();             //�^�C�}�[�J�n.
}