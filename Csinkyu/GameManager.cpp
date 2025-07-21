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
#include "EffectManager.h"

#include "Obstacle4.h"
#include "Obstacle4main.h"
#include "Obstacle5.h"
#include "MapGimmickLaser.h"

#include "Item.h"
#include "Player.h"

#include "GameManager.h"

//�Ǘ��N���X�̎���.
MeteoManager  meteoMng;
LaserManager  laserMng;
EffectManager effectMng;
//��Q���̎���.
Obstacle4_1 obstacle4_1;
Obstacle4_2 obstacle4_2;
Obstacle4_3 obstacle4_3;
Obstacle4_4 obstacle4_4;
Obstacle5   obstacle5;
MapGimmickLaser mgl[2];
//�A�C�e���̎���.
Item item;
//�v���C���[�̎���.
Player player;

//������(���̂ݍs��)
void GameManager::Init() {

	srand((unsigned)time(NULL)); //����������.
	
	p_input = InputST::GetPtr();
	p_sound = SoundST::GetPtr();
	
	//�^�C�g��.
	data.scene = SCENE_TITLE;
	//�t�H���g�쐬.
	data.font1 = CreateFontToHandle(NULL, 26, 1);
	data.font2 = CreateFontToHandle(NULL, 30, 1, DX_FONTTYPE_ANTIALIASING);
	data.font3 = CreateFontToHandle(NULL, 40, 1, DX_FONTTYPE_ANTIALIASING);
	//�摜�ǂݍ���.
	LoadGraphST(&data.imgLogo[0], _T("Resources/Images/REFLINE���S_�ꕔ.png"));
	LoadGraphST(&data.imgLogo[1], _T("Resources/Images/REFLINE���S.png"));
	//�T�E���h�ǂݍ���.
	p_sound->LoadFile(_T("Resources/Sounds/bgm/audiostock_132563.mp3"),  _T("BGM1"));
	p_sound->LoadFile(_T("Resources/Sounds/bgm/audiostock_1175043.mp3"), _T("BGM2"));
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_63721.mp3"),    _T("PowerDown"));
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_104974.mp3"),   _T("Break"));
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_157393.mp3"),   _T("TakeItem1"));
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_461339.mp3"),   _T("TakeItem2"));
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_326830.mp3"),   _T("Laser1"));
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_218404.mp3"),   _T("Laser2"));

	//Init����
	{
		//�Ǘ�class.
		laserMng.Init(&data, &player, &meteoMng);
		meteoMng.Init(&data, &player, &effectMng);
		effectMng.Init(&data);
		//��Q��class.
		mgl[0].Init(&data, &player, &laserMng, &meteoMng);
		mgl[1].Init(&data, &player, &laserMng, &meteoMng);
		obstacle4_1.Init(&data, &player, &meteoMng, &laserMng);
		obstacle4_2.Init(&data, &player, &meteoMng, &laserMng);
		obstacle4_3.Init(&data, &player, &meteoMng, &laserMng);
		obstacle4_4.Init(&data, &player, &meteoMng, &laserMng);
		obstacle5.Init(&data, &player);
		//�A�C�e��class.
		item.Init(&data, &player, &effectMng);
		//�v���C���[class.
		player.Init(&data);
	}

	Reset();
}

//���Z�b�g(����ł��s��)
void GameManager::Reset() {

	if (data.bestScore < data.score) {
		data.bestScore = data.score; //�n�C�X�R�A�L�^.
	}

	//���Z�b�g.
	data.scoreBef = 0;
	data.score = 0;
	data.isSlow = FALSE;
	data.spawnRate = 1.0; //�ŏ���100%
	data.counter = 0;
	//�T�E���h.
	p_sound->Stop(_T("BGM2"));
	p_sound->FadeInPlay(_T("BGM2"), 80, 3, TRUE);
	//�^�C�}�[.
	tmScene[SCENE_TITLE].Start();
	tmScene[SCENE_READY].Reset();
	tmScene[SCENE_GAME].Reset();
	tmScene[SCENE_END].Reset();

	{
		//�Ǘ�class.
		laserMng.Reset();
		meteoMng.Reset();
		effectMng.Reset();
		//��Q��class.
		mgl[0].Reset();
		mgl[1].Reset();
		obstacle4_1.Reset(WINDOW_WID/2, 0, 3, MOVE_RIGHT);
		obstacle4_2.Reset(WINDOW_WID/2, 0, 3, MOVE_LEFT);
		obstacle4_3.Reset(WINDOW_WID/2, 1070, 3, MOVE_RIGHT);
		obstacle4_4.Reset(WINDOW_WID/2, 1070, 3, MOVE_LEFT);
		obstacle5.Reset(WINDOW_WID/2, WINDOW_HEI/1, 0, 0); // ��ʒ����ɔz�u.
		//�A�C�e��class.
		item.Reset();
		//�v���C���[class.
		player.Reset({ WINDOW_WID/2, WINDOW_HEI/2+200 }, TRUE);
	}
}

//�X�V.
void GameManager::Update() {

	p_input->UpdateKey();    //�L�[���͍X�V.
	p_input->UpdatePadBtn(); //�R���g���[���̃{�^�����͍X�V.
	p_sound->Update();       //�T�E���h�X�V.

	//�V�[����.
	switch (data.scene) 
	{
		case SCENE_TITLE: UpdateTitle(); break;
		case SCENE_READY: UpdateReady();  break;
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
		case SCENE_READY: DrawReady(); break;
		case SCENE_GAME:  DrawGame();  break;
		case SCENE_END:   DrawEnd();   break;

		default: assert(FALSE); break;
	}
}

//�V�[���ʍX�V.
void GameManager::UpdateTitle() 
{
	//�v���C���[class.
	player.Update();

	//����̑���ŃQ�[���J�n.
	if (p_input->IsPushKeyTime(KEY_SPACE) == 1 || p_input->IsPushPadBtnTime(PAD_BTN_X) == 1)
	{
		tmScene[SCENE_READY].Start(); //�^�C�}�[�J�n.
		data.scene = SCENE_READY;     //�����V�[����.
	}
}
void GameManager::UpdateReady() {

	player.Update(); //�v���C���[.
	UpdateObjects(); //�I�u�W�F�N�g.
	
	//��莞�Ԍo������.
	if (tmScene[SCENE_READY].GetPassTime() >= GAME_START_TIME) {
		tmScene[SCENE_GAME].Start(); //�Q�[���J�n.
		data.scene = SCENE_GAME;     //�Q�[���V�[����.
	}
}
void GameManager::UpdateGame() {
	
//	DrawFormatString(30, 200, 0xFFFFFF, _T("%d"), GetJoypadInputState(DX_INPUT_PAD1));

	//�J�E���^�[����.
	data.counter += ((data.isSlow) ? SLOW_MODE_SPEED : 1);
	//�o���Ԋu.
	data.spawnRate = 1.0/(1 + (data.counter/5000));  //100%���班��������.

	//�X���[���[�h.
	if (tmSlowMode.GetIsMove()) {
		//���Ԑ؂�ŉ���.
		if (tmSlowMode.GetPassTime() == 0) {
			
			player.SetReflectionMode(FALSE); //���˃��[�h�I��.
			p_sound->Play(_T("PowerDown"), FALSE); //�T�E���h.
			
			//���Z�b�g.
			tmSlowMode.Reset();
			data.isSlow = FALSE;
		}
	}

	player.Update(); //�v���C���[.
	UpdateObjects(); //�I�u�W�F�N�g.
}
void GameManager::UpdateEnd() {

	//����̑���Ń^�C�g����.
	if (p_input->IsPushKeyTime(KEY_SPACE) == 1 || p_input->IsPushPadBtnTime(PAD_BTN_A) == 1)
	{
		data.scene = SCENE_TITLE; //�Q�[���V�[����.
		Reset();
	}
}
//�I�u�W�F�N�g�̍X�V.
void GameManager::UpdateObjects() {

	//�Ǘ�class.
	meteoMng.Update();
	laserMng.Update();
	effectMng.Update();
	//��Q��class.
	mgl[0].Update();
	mgl[1].Update();
	obstacle4_1.Update();
	obstacle4_2.Update();
	obstacle4_3.Update();
	obstacle4_4.Update();
	obstacle5.Update();
	//�A�C�e��class.
	item.Update();
}

//�V�[���ʕ`��.
void GameManager::DrawTitle() {
	
	//�v���C���[class.
	player.Draw();

	//�摜�̕\��.
	{
		const int delay = 1; //�؂�ւ��|�C���g.
	
		//�؂�ւ��O.
		if (tmScene[SCENE_TITLE].GetPassTime() < delay) {
			//�A�j���[�V�����l.
			float anim = CalcNumEaseIn(tmScene[SCENE_TITLE].GetPassTime()/delay);
			//�摜�ݒ�.
			IMG_DRAW_EXTEND img = { 
				data.imgLogo[0],
				{WINDOW_WID/2, WINDOW_HEI/2}, 
				{data.imgLogo[0].size.x/2, data.imgLogo[0].size.y/2}
			};
			//���S1����.
			SetDrawBlendModeST(MODE_ADD, 255 * anim);
			DrawExtendGraphST(&img, TRUE);
		}
		//�؂�ւ���.
		else {
			//�A�j���[�V�����l.
			float anim = CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay)/2);
			//�摜�ݒ�.
			IMG_DRAW_EXTEND img1 = { 
				data.imgLogo[0],
				{WINDOW_WID/2, WINDOW_HEI/2-anim*100}, 
				{data.imgLogo[0].size.x/2, data.imgLogo[0].size.y/2}
			};
			IMG_DRAW_EXTEND img2 = {
				data.imgLogo[1],
				{WINDOW_WID/2, WINDOW_HEI/2 - anim * 100},
				{data.imgLogo[1].size.x/2, data.imgLogo[1].size.y/2}
			};
			//���S1����.
			SetDrawBlendModeST(MODE_ADD, 255 * anim);
			DrawExtendGraphST(&img2, TRUE);
			//���S2����.
			SetDrawBlendModeST(MODE_ADD, 255 * (1-anim));
			DrawExtendGraphST(&img1, TRUE);
		}
		//�`�惂�[�h���Z�b�g.
		ResetDrawBlendMode();
	}

	//�e�L�X�g�̕\��.
	{
		STR_DRAW str  = { _T("PUSH SPACE"), {WINDOW_WID/2, 160}, 0xFFFFFF };
		STR_DRAW str2 = { {}, {WINDOW_WID/2, WINDOW_HEI/2+300}, 0xFFFFFF };
		swprintf(str2.text, _T("best score: %d"), data.bestScore); //�x�X�g�X�R�A.

		DrawStringST(&str,  TRUE, data.font1);
		DrawStringST(&str2, TRUE, data.font1);
	}
}
void GameManager::DrawReady() {
	
	player.Draw();  //�v���C���[.
	DrawUI();
}
void GameManager::DrawGame() {

	player.Draw();  //�v���C���[.
	DrawObjects();  //�I�u�W�F�N�g.
	DrawUI();
	DrawSlowMode(); //�X���[���[�h���o.
}
void GameManager::DrawEnd() {
	
	DrawObjects();
	{
		float anim = min(tmScene[SCENE_END].GetPassTime(), 1); //�A�j���[�V�����l.
		Box box = { {0, 0}, {WINDOW_WID, WINDOW_HEI}, 0x000000 };

		SetDrawBlendModeST(MODE_ALPHA, 128*anim);
		DrawBoxST(&box, FALSE); //��ʂ��Â�����(UI�ȊO)
		ResetDrawBlendMode();
	}
	DrawUI();

	//�I���ē�.
	{
		//�e�L�X�g�̐ݒ�.
		STR_DRAW str1 = { _T("- GAME OVER -"), {WINDOW_WID/2, 450}, 0xFF0000 };
		STR_DRAW str2 = { {}, {WINDOW_WID/2, WINDOW_HEI/2+100}, 0xFFFFFF };
		//�X�R�A�\��.
		swprintf(
			str2.text, 
			_T("[score] %d�_ + %d�_(time:%.3f)\n[total] %d�_"),
			data.scoreBef, (int)(tmScene[SCENE_GAME].GetPassTime() * 10), tmScene[SCENE_GAME].GetPassTime(), data.score
		);
		//��ʒ����ɕ�����\��.
		DrawStringST(&str1, TRUE, data.font2);
		DrawStringST(&str2, TRUE, data.font1);
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
		//�ŏ���0.5�b
		float time = 0.5f-(tmSlowMode.GetPassTime()-(SLOW_MODE_TIME-0.5f));
		time = CalcNumEaseOut(time); //�l�̋Ȑ��ϓ�.
		//�w�i�F.
		{
			Box box = { {0, 0}, {WINDOW_WID, WINDOW_HEI}, 0x303030 };
			SetDrawBlendModeST(MODE_ADD, 100*time);
			DrawBoxST(&box, FALSE);
			ResetDrawBlendMode();
		}
		//�g��.
		{
			Box box = { {WINDOW_WID/2, WINDOW_HEI/2}, {WINDOW_WID * time, WINDOW_HEI * time}, COLOR_PLY_REFLECT };
			DrawBoxST(&box, TRUE, FALSE);
		}
	}
}
//UI�̕`��.
void GameManager::DrawUI() {

	//�Q�[������.
	DrawFormatStringToHandle(
		10, 10, 0xFFFFFF, data.font2, _T("time:%.3f"), tmScene[SCENE_GAME].GetPassTime()
	);
	//�o���Ԋu����.
	DrawFormatStringToHandle(
		10, WINDOW_HEI-40, 0xFFFFFF, data.font2, _T("�o���Ԋu: %.2f%%"), data.spawnRate*100
	);

	//�n�C�X�R�A�\��.
	{
		//�A�j���[�V�����l.
		float anim1    = CalcNumEaseInOut(tmScene[SCENE_READY].GetPassTime());
		float anim2    = CalcNumEaseInOut(tmScene[SCENE_READY].GetPassTime());
		float animSin1 = sin(M_PI*tmScene[SCENE_READY].GetPassTime());
		float animSin2 = sin(M_PI*tmScene[SCENE_READY].GetPassTime()-1);

		//�e�L�X�g�ݒ�.
		STR_DRAW str1 = { {}, {WINDOW_WID/2, 0+100}, COLOR_BEST_SCORE };
		STR_DRAW str2 = { {}, {WINDOW_WID/2, 0+150}, COLOR_SCORE };
		swprintf(str1.text, _T("best score: %d"), data.bestScore);
		swprintf(str2.text, _T("score: %d"),      data.score);
		//�e�L�X�g(main)
		SetDrawBlendModeST(MODE_ALPHA, 255 * anim1);
		DrawStringST(&str1, TRUE, data.font3);
		SetDrawBlendModeST(MODE_ALPHA, 255 * anim2);
		DrawStringST(&str2, TRUE, data.font3);
		//�e�L�X�g(����p)
		str1.color = 0xFFFFFF;
		str2.color = 0xFFFFFF;
		SetDrawBlendModeST(MODE_ALPHA, 128 * animSin1);
		DrawStringST(&str1, TRUE, data.font3);
		SetDrawBlendModeST(MODE_ALPHA, 128 * animSin2);
		DrawStringST(&str2, TRUE, data.font3);
		//�`�惂�[�h���Z�b�g.
		ResetDrawBlendMode();
	}
}
//�I�u�W�F�N�g�̕`��.
void GameManager::DrawObjects() {

	//�Ǘ�class.
	meteoMng.Draw();
	laserMng.Draw();
	effectMng.Draw();
	//��Q��class.
	mgl[0].Draw();
	mgl[1].Draw();
	obstacle4_1.Draw();
	obstacle4_2.Draw();
	obstacle4_3.Draw();
	obstacle4_4.Draw();
	obstacle5.Draw();
	//�A�C�e��class.
	item.Draw();
}
//�X���[���[�h���o.
void GameManager::DrawSlowMode() {

	//�J�E���g�_�E����.
	if (tmSlowMode.GetIsMove() && tmSlowMode.GetPassTime() > 0)
	{
		//�e�L�X�g������p.
		STR_DRAW str = { {}, {WINDOW_WID/2, WINDOW_HEI/2}, 0x00FF00 };
		//�e�L�X�g�̐ݒ�.
		swprintf(str.text, _T("%d"), (int)ceil(tmSlowMode.GetPassTime())); //TCHAR�^�ɕϐ�����.

		//��ʒ����ɐ�����\��.
		{
			double dec = GetDecimal(tmSlowMode.GetPassTime()); //�����������o��.
			SetDrawBlendModeST(MODE_ADD, _int(255 * dec));     //1�b���Ƃɔ����Ȃ鉉�o.
			DrawStringST(&str, TRUE, data.font3);              //font����.
			ResetDrawBlendMode();                              //�߂�.
		}
	}
}

//�Q�[���I��.
void GameManager::GameEnd() {
	
	data.scene = SCENE_END; //�Q�[���I����.
	
	tmScene[SCENE_GAME].Stop(); //��~.
	tmScene[SCENE_END].Start(); //�J�n.
	data.isSlow = FALSE;
	tmSlowMode.Reset();

	data.scoreBef = data.score;                                  //���ԉ��Z�O�̃X�R�A���L�^.
	data.score += (int)(tmScene[SCENE_GAME].GetPassTime() * 10); //���ԃ{�[�i�X���Z.

	//�T�E���h.
	p_sound->FadeOutPlay(_T("BGM2"), 3);
}
//�A�C�e�����������.
void GameManager::TakeItem() {

	data.isSlow = TRUE;             //�X���[���[�h�ɂ���.
	data.score += SCORE_TAKE_ITEM;  //�X�R�A���Z.
	tmSlowMode.Start();             //�X���[���[�h�v���J�n.
	player.SetReflectionMode(TRUE); //���˃��[�h�J�n.

	//�T�E���h.
//	p_sound->Play(_T("TakeItem1"), FALSE);
	p_sound->Play(_T("TakeItem2"), FALSE);
}