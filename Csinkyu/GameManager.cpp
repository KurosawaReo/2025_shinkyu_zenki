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

   �O�����\���: �ύX���e
   �EUI���C�A�E�g�̕ύX�B"BEST SCORE","SCORE","TIME"��3�����ɂ����B
   �E�A�C�e���̏I����������₷���Ȃ�悤�A������3�b�����\�����ĉ��𑫂����B
   �E�|�[�Y�@�\���ǉ��B(P�L�[)
   �E�}�`����̃A���`�G�C���A�X����, ��芊�炩�ȕ`�悪�\�ɁB
   �E���[�U�[�ŒZ���������`�悵�Ȃ��悤�ɁB(�����y���Ɍq����)
   �E覐΂̔j�Ђ̔�юU����𒲐�
   �E���˃��[�U�[��覐΂ɓ������Ă����˂���悤��
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
	imgLogo[0].LoadGraphST(_T("Resources/Images/REFLINE���S_�ꕔ.png"));
	imgLogo[1].LoadGraphST(_T("Resources/Images/REFLINE���S.png"));
	imgUI.     LoadGraphST(_T("Resources/Images/testUI.png"));
	//�T�E���h�ǂݍ���.
	p_sound->LoadFile(_T("Resources/Sounds/bgm/Scarlet Radiance.mp3"),		_T("BGM1"));
	p_sound->LoadFile(_T("Resources/Sounds/bgm/audiostock_1603723.mp3"),	_T("BGM2"));		//���g�p(BGM���)
	p_sound->LoadFile(_T("Resources/Sounds/bgm/GB_Shooting_2025.0725.mp3"),	_T("BGM3"));
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_461339.mp3"),		_T("TakeItem"));	//�A�C�e�����.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_1116927_cut.mp3"),	_T("CountDown"));	//�J�E���g�_�E��.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_63721.mp3"),		_T("PowerDown"));	//�A�C�e������.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_1296254.mp3"),		_T("Laser1"));		//���[�U�[(����)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_1296256.mp3"),		_T("Laser2"));		//���[�U�[(������)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_218404.mp3"),		_T("Laser3"));		//���[�U�[(����)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_936158.mp3"),		_T("Ripples"));		//�g��.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_104974.mp3"),		_T("Break"));		//覐Δj��.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_981051.mp3"),		_T("PlayerDeath"));
	p_sound->LoadFile(_T("Resources/Sounds/se/����{�^��������23.mp3"),		_T("LevelUp"));
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_184924.mp3"),		_T("BestScore"));	//�ō��X�R�A�X�V.
	//Init����
	{
		//�Ǘ�class.
		laserMng.Init(&data, &player, &meteoMng, &effectMng);
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
		player.Init(&data, &effectMng);
	}

	//�X�R�A�ǂݍ���.
	{
		FileST file;
		int ret = file.Open(FILE_DATA_PATH, _T("r")); //�t�@�C�����J��.
		data.bestScore = file.ReadInt();    //������ǂݍ���œo�^.
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
	data.counter = 0;
	data.spawnRate = 1.0; //�ŏ���100%
	data.level = 1;       //�ŏ���Lv1
	isFinTitleAnim = FALSE;
	isFinScoreAnim = FALSE;
	//�T�E���h.
	p_sound->Stop(_T("BGM1"));
	p_sound->Play(_T("BGM1"), TRUE, 68);
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
		ResetNorLaser();
		obstacle5.Reset();
		//�A�C�e��class.
		item.Reset();
		//�v���C���[class.
		player.Reset({ WINDOW_WID/2, WINDOW_HEI/2+185 }, TRUE);
	}
}

//�X�V.
void GameManager::Update() {

	p_input->UpdateKey(); //�L�[���͍X�V.
	p_input->UpdatePad(); //�R���g���[�����͍X�V.
	p_sound->Update();    //�T�E���h�X�V.

	//�V�[����.
	switch (data.scene) 
	{
		case SCENE_TITLE: UpdateTitle(); break;
		case SCENE_READY: UpdateReady(); break;
		case SCENE_GAME:  UpdateGame();  break;
		case SCENE_END:   UpdateEnd();   break;
		case SCENE_PAUSE: UpdatePause(); break;
	
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
		case SCENE_PAUSE: DrawPause(); break;

		default: assert(FALSE); break;
	}
}

//�ʏ탌�[�U�[�̃��Z�b�g.
void GameManager::ResetNorLaser() {

	obstacle4_1.Reset(WINDOW_WID/2, 0, 3, MOVE_RIGHT);
	obstacle4_2.Reset(WINDOW_WID/2, 0, 3, MOVE_LEFT);
	obstacle4_3.Reset(WINDOW_WID/2, WINDOW_HEI, 3, MOVE_RIGHT);
	obstacle4_4.Reset(WINDOW_WID/2, WINDOW_HEI, 3, MOVE_LEFT);
}

//�V�[���ʍX�V.
void GameManager::UpdateTitle() 
{
	player.Update();    //�v���C���[.
	effectMng.Update(); //�G�t�F�N�g.

	//����̑���ŃQ�[���J�n.
	if (p_input->IsPushKeyTime(KEY_SPACE) == 1 || p_input->IsPushPadBtnTime(PAD_BTN_X) == 1)
	{
		tmScene[SCENE_READY].Start(); //�^�C�}�[�J�n.
		data.scene = SCENE_READY;     //�����V�[����.
	}
}
void GameManager::UpdateReady() {

	player.Update();    //�v���C���[.
	effectMng.Update(); //�G�t�F�N�g.
	
	//��莞�Ԍo������.
	if (tmScene[SCENE_READY].GetPassTime() >= GAME_START_TIME) {

		tmScene[SCENE_GAME].Start(); //�Q�[���J�n.
		data.scene = SCENE_GAME;     //�Q�[���V�[����.
//		data.level = 1;              //Lv1�ɂ���.

		//�T�E���h.
		SoundST* sound = SoundST::GetPtr();
		sound->Play(_T("LevelUp"), FALSE, 100);
		//�G�t�F�N�g.
		EffectData data{};
		data.type = Effect_Level1;
		data.pos = { WINDOW_WID/2, WINDOW_HEI/2 };
		effectMng.SpawnEffect(&data);
	}
}
void GameManager::UpdateGame() {

	//�J�E���^�[����.
	data.counter += ((data.isSlow) ? SLOW_MODE_SPEED : 1);
	//�o���Ԋu.
	data.spawnRate = 1.0f/(1 + (data.counter/8000)); //100%���班��������.
	//���x���Ǘ�.
	switch (data.level) 
	{
		case 1:
			if (data.spawnRate <= 0.85) { //85%�ȉ�.
				data.level = 2; //Lv2��.

				//�T�E���h.
				SoundST* sound = SoundST::GetPtr();
				sound->Play(_T("LevelUp"), FALSE, 100);
				//�G�t�F�N�g.
				EffectData data{};
				data.type = Effect_Level2;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);
			}
			break;
		case 2:
			if (data.spawnRate <= 0.65) { //65%�ȉ�.
				data.level = 3; //Lv3��.

				//�T�E���h.
				SoundST* sound = SoundST::GetPtr();
				sound->Play(_T("LevelUp"), FALSE, 100);
				//�G�t�F�N�g.
				EffectData data{};
				data.type = Effect_Level3;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);
			}
			break;
		case 3:
			if (data.spawnRate <= 0.5) { //50%�ȉ�.
				data.level = 4; //Lv4��.
				ResetNorLaser();

				//�T�E���h.
				SoundST* sound = SoundST::GetPtr();
				sound->Play(_T("LevelUp"), FALSE, 100);
				//�G�t�F�N�g.
				EffectData data{};
				data.type = Effect_Level4;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);
			}
			break;
		case 4:
		case 5:
			//�ŏI���x��.
			break;

		default: assert(FALSE); break;
	}

	//�X���[���[�h.
	if (tmSlowMode.GetIsMove()) {
		//3�b�ȉ��ɂȂ����΂���̎�.
		if (tmSlowMode.GetPassTime() <= 3){
			if (!isItemCount[2]) {
				p_sound->Play(_T("CountDown"), FALSE, 78); //�Đ�.
				isItemCount[2] = TRUE;
			}
		}
		//2�b�ȉ��ɂȂ����΂���̎�.
		if (tmSlowMode.GetPassTime() <= 2) {
			if (!isItemCount[1]) {
				p_sound->Play(_T("CountDown"), FALSE, 78); //�Đ�.
				isItemCount[1] = TRUE;
			}
		}
		//1�b�ȉ��ɂȂ����΂���̎�.
		if (tmSlowMode.GetPassTime() <= 1) {
			if (!isItemCount[0]) {
				p_sound->Play(_T("CountDown"), FALSE, 78); //�Đ�.
				isItemCount[0] = TRUE;
			}
		}
		//���Ԑ؂�ŉ���.
		if (tmSlowMode.GetPassTime() <= 0) {
			
			player.SetReflectionMode(FALSE); //���˃��[�h�I��.
			p_sound->Play(_T("PowerDown"), FALSE, 78); //�Đ�.
			
			//���Z�b�g.
			tmSlowMode.Reset();
			data.isSlow = FALSE;
			for (int i = 0; i < _countof(isItemCount); i++) {
				isItemCount[i] = FALSE;
			}
		}
	}

	UpdateObjects();    //�I�u�W�F�N�g.
	player.Update();    //�v���C���[.
	effectMng.Update(); //�G�t�F�N�g.
	
	//�|�[�Y����.
	if(p_input->IsPushKeyTime(KEY_P) == 1){
		data.scene = SCENE_PAUSE;
		tmScene[SCENE_GAME].Stop(); //�ꎞ��~.
		tmSlowMode.Stop();          //�ꎞ��~.
	}
}
void GameManager::UpdateEnd() {

	effectMng.Update(); //�G�t�F�N�g.

	//����̑���Ń^�C�g����.
	if (p_input->IsPushKeyTime(KEY_SPACE) == 1 || p_input->IsPushPadBtnTime(PAD_BTN_A) == 1)
	{
		data.scene = SCENE_TITLE; //�Q�[���V�[����.
		Reset();
	}
}
void GameManager::UpdatePause() {

	//�|�[�Y����.
	if (p_input->IsPushKeyTime(KEY_P) == 1) {

		data.scene = SCENE_GAME;
		tmScene[SCENE_GAME].Start(); //�ĊJ.
		//�X���[���[�h���������Ȃ�.
		if (tmSlowMode.GetPassTime() < SLOW_MODE_TIME) {
			tmSlowMode.Start(); //�ĊJ.
		}
	}
}

//�I�u�W�F�N�g�̍X�V.
void GameManager::UpdateObjects() {

	//Lv1�ȏ�.
	laserMng.Update();
	meteoMng.Update();
	obstacle4_1.Update();
	obstacle4_2.Update();
	item.Update();
	//Lv2�ȏ�.
	if (data.level >= 2) {
		mgl[0].Update();
		mgl[1].Update();
	}
	//Lv3�ȏ�.
	if (data.level >= 3) {
		obstacle5.Update();
	}
	//Lv4�ȏ�.
	if (data.level >= 4) {
		obstacle4_3.Update();
		obstacle4_4.Update();
	}
}

//�V�[���ʕ`��.
void GameManager::DrawTitle() {
	
	player.Draw();    //�v���C���[. 
	effectMng.Draw(); //�G�t�F�N�g�Ǘ�.

	//�A�j���[�V�����؂�ւ��|�C���g.
	const float delay1 = 1;
	const float delay2 = 1.6f;
	const float delay3 = 3;
	const float delay4 = 3;

	const int logoY = WINDOW_HEI/2 - 70;

	//�摜�̕\��.
	{	
		//�؂�ւ��O.
		if (tmScene[SCENE_TITLE].GetPassTime() < delay1) {
			//�A�j���[�V�����l.
			double anim = CalcNumEaseInOut(tmScene[SCENE_TITLE].GetPassTime()/delay1);
			//���S1����.
			SetDrawBlendModeST(MODE_ADD, 255 * anim);
			imgLogo[0].DrawExtendGraphST(0, {WINDOW_WID/2, logoY}, {0.5, 0.5}, TRUE);
		}
		//�؂�ւ���.
		else {
			//�A�j���[�V�����l.
			double anim = CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay1)/1.8);
			//���S1����.
			SetDrawBlendModeST(MODE_ADD, 255 * anim);
			imgLogo[1].DrawExtendGraphST(0, {WINDOW_WID/2, _int(logoY - anim*100)}, {0.5, 0.5}, TRUE);
			//���S2����.
			SetDrawBlendModeST(MODE_ADD, 255 * (1-anim));
			imgLogo[0].DrawExtendGraphST(0, {WINDOW_WID/2, _int(logoY - anim*100)}, {0.5, 0.5}, TRUE);
		}
		//�`�惂�[�h���Z�b�g.
		ResetDrawBlendMode();
	}

	//best score.
	if (tmScene[SCENE_TITLE].GetPassTime() > delay2) {

		//�A�j���[�V�����l.
		double anim = CalcNumEaseInOut(tmScene[SCENE_TITLE].GetPassTime()-delay2);
		//�e�L�X�g.
		TCHAR text[256];
		_stprintf(text, _T("BEST SCORE: %d"), data.bestScore); //�x�X�g�X�R�A.
		DrawStrST str(text, {WINDOW_WID/2, WINDOW_HEI/2+85}, COLOR_BEST_SCORE);

		SetDrawBlendModeST(MODE_ADD, 255*anim);
		str.DrawStringST(TRUE, data.font2);
		ResetDrawBlendMode();
	}
	//PUSH SPACE.
	if (tmScene[SCENE_TITLE].GetPassTime() > delay3) {
		//�A�j���[�V�����l.
		double anim = CalcNumWaveLoop(tmScene[SCENE_TITLE].GetPassTime()-delay3);
		//�e�L�X�g.
		DrawStrST str(_T("Push SPACE or  X"), {WINDOW_WID/2-5, WINDOW_HEI/2+285}, 0xFFFFFF);
		Circle cir = { {WINDOW_WID/2+93, WINDOW_HEI/2+285-1}, 18, 0xFFFFFF };
		
		SetDrawBlendModeST(MODE_ADD, 255*anim);
		str.DrawStringST(TRUE, data.font1); //�e�L�X�g.
		DrawCircleST(&cir, FALSE, FALSE);   //X�{�^���̉~.
		ResetDrawBlendMode();
	}
	//覐Δj��.
	if (tmScene[SCENE_TITLE].GetPassTime() > delay4) {
		//�܂��o���ĂȂ����.
		if (!isFinTitleAnim) {
			isFinTitleAnim = TRUE; //��x����.

			double dig = -130; //�p�x.

			//�G�t�F�N�g���������o��.
			for (int i = 0; i < 8; i++) {

				double newDig = dig + (float)RandNum(-300, 300)/10; //�����p�x�����炷.

				EffectData data{}; 
				data.type  = Effect_BreakMeteo;
				data.pos   = { 600, 338 };
				data.vec   = CalcDigToPos(newDig);                //���炵���p�x�𔽉f.
				data.speed = ((float)RandNum( 60,  100)/10)*1.4f; //���x���I.
				data.len   = ((float)RandNum( 30,  150)/10)*1.4f; //�������I.
				data.ang   =  (float)RandNum(  0, 3599)/10;       //�p�x���I.
				//�G�t�F�N�g����.
				effectMng.SpawnEffect(&data);
			}
			//�T�E���h.
			p_sound->Play(_T("Break"), FALSE, 65);
		}
	}
}
void GameManager::DrawReady() {
	
	player.Draw();    //�v���C���[.
	effectMng.Draw(); //�G�t�F�N�g�Ǘ�.
	DrawUI();
}
void GameManager::DrawGame() {

	DrawObjects();     //�I�u�W�F�N�g.
	player.Draw();     //�v���C���[.
	effectMng.Draw();  //�G�t�F�N�g.
	DrawUI();
	DrawReflectMode(); //���˃��[�h���o.
}
void GameManager::DrawEnd() {
	
	DrawObjects();
	effectMng.Draw(); //�G�t�F�N�g.
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
		//�A�j���[�V�����l.
		double anim = CalcNumEaseOut(tmScene[SCENE_END].GetPassTime());

		//�X�R�A�\��.
		TCHAR text[256];
		_stprintf(
			text, _T("%d + %d(%.3f�b) = %d�_"),
			data.scoreBef, (int)(tmScene[SCENE_GAME].GetPassTime() * 10), tmScene[SCENE_GAME].GetPassTime(), data.score
		);
		//�e�L�X�g�̐ݒ�.
		DrawStrST str1(_T("- GAME OVER -"), {WINDOW_WID/2, _int(370+30*anim)}, 0xA0A0A0);
		DrawStrST str2(_T("Time Bonus"),    {WINDOW_WID/2, WINDOW_HEI/2-20},   0xFFFFFF);
		DrawStrST str3(text,                {WINDOW_WID/2, WINDOW_HEI/2+20},   0xFFFFFF);
		//��ʒ����ɕ�����\��.
		SetDrawBlendModeST(MODE_ADD, 255*anim);
		str1.DrawStringST(TRUE, data.font3);
		str2.DrawStringST(TRUE, data.font1);
		str3.DrawStringST(TRUE, data.font1);
		ResetDrawBlendMode();
	}

	const float delay1 = 1.2f;
	const float delay2 = 1.5f;

	//��莞�Ԃ��o������.
	if (tmScene[SCENE_END].GetPassTime() > delay1) {
		//�x�X�g�X�R�A�X�V.
		if (data.score > data.bestScore) {

			//�A�j���[�V�����l.
			double anim = CalcNumEaseOut((tmScene[SCENE_END].GetPassTime()-delay1)*2);
			//�e�L�X�g.
			DrawStrST str = { _T("NEW RECORD!"), {WINDOW_WID/2, _int(WINDOW_HEI/2-350+anim*20)}, 0xEFFFA0 };
			//�`��.
			SetDrawBlendModeST(MODE_ADD, 255*anim);
			str.DrawStringST(TRUE, data.font2);
			ResetDrawBlendMode();
			//�T�E���h.
			if (!isFinScoreAnim) {
				isFinScoreAnim = TRUE; //��x�̂�.
				p_sound->Play(_T("BestScore"), FALSE, 65);
			}
		}
	}
	//��莞�Ԃ��o������.
	if (tmScene[SCENE_END].GetPassTime() > delay2) {
		
		//�A�j���[�V�����l.
		double anim = CalcNumWaveLoop(tmScene[SCENE_END].GetPassTime()-delay2);
		//�e�L�X�g.
		DrawStrST str(_T("Push SPACE or  A"), {WINDOW_WID/2-5, WINDOW_HEI/2+145}, 0xFFFFFF);
		Circle cir = { {WINDOW_WID/2+93, WINDOW_HEI/2+145}, 18, 0xFFFFFF };
		
		SetDrawBlendModeST(MODE_ADD, 255*anim);
		str.DrawStringST(TRUE, data.font1); //�e�L�X�g.
		DrawCircleST(&cir, FALSE, FALSE);   //A�{�^���̉~.
		ResetDrawBlendMode();
	}
}
void GameManager::DrawPause() {

	DrawObjects();     //�I�u�W�F�N�g.
	player.Draw();     //�v���C���[.
	effectMng.Draw();  //�G�t�F�N�g.
	DrawUI();
	DrawReflectMode(); //���˃��[�h���o.
}

//�w�i�̕`��.
void GameManager::DrawBG() {

	//�w�i�f�U�C��.
	for (int x = 0; x < WINDOW_WID; x += 5) {

		int clr = _int(20 * fabs(sin((double)x/200))); //�F�̕ω�.
		Line line = { {(double)x, 0},{(double)x, WINDOW_HEI}, GetColor(0, clr, clr) };
		DrawLineST(&line, FALSE, 5);
	}
	//�w�i(�X���[���[�h).
	if (data.isSlow) {
		//�ŏ���0.5�b
		double time = 0.5-(tmSlowMode.GetPassTime()-(SLOW_MODE_TIME-0.5));
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
			DrawBoxST(&box, TRUE, FALSE, TRUE);
		}
	}
}
//UI�̕`��.
void GameManager::DrawUI() {

#if false
	//���x��(debug)
	DrawFormatStringToHandle(
		10, WINDOW_HEI-75, 0xFFFFFF, data.font2, _T("Level: %d"), data.level
	);
	//�o���Ԋu����(debug)
	DrawFormatStringToHandle(
		10, WINDOW_HEI-40, 0xFFFFFF, data.font2, _T("Spawn: %.2f%%"), data.spawnRate*100
	);
#endif

	//�n�C�X�R�A�\��.
	{
		//�A�j���[�V�����l.
		double alpha1   = CalcNumEaseInOut( tmScene[SCENE_READY].GetPassTime()-0.1);
		double alpha2   = CalcNumEaseInOut( tmScene[SCENE_READY].GetPassTime()-0.2);
		double alpha3   = CalcNumEaseInOut( tmScene[SCENE_READY].GetPassTime()-0.3);
		double alpha4   = CalcNumEaseInOut((tmScene[SCENE_READY].GetPassTime()-1.0)*2);
		double animSin1 = sin(M_PI* tmScene[SCENE_READY].GetPassTime()-0.1);
		double animSin2 = sin(M_PI*(tmScene[SCENE_READY].GetPassTime()-0.2));
		double animSin3 = sin(M_PI*(tmScene[SCENE_READY].GetPassTime()-0.3));

#if true
		//test.
		imgUI.DrawExtendGraphST(0, {WINDOW_WID/2,      70}, {0.6, 0.3}, TRUE, TRUE);
		imgUI.DrawExtendGraphST(0, {WINDOW_WID/2-380, 150}, {0.6, 0.3}, TRUE, TRUE);
		imgUI.DrawExtendGraphST(0, {WINDOW_WID/2,     150}, {0.6, 0.3}, TRUE, TRUE);
		imgUI.DrawExtendGraphST(0, {WINDOW_WID/2+380, 150}, {0.6, 0.3}, TRUE, TRUE);
#endif

		//�e�L�X�g�ݒ�.
		TCHAR text[256];
		_stprintf(text, _T("LEVEL:%d"),        data.level);
		DrawStrST str1(text, {WINDOW_WID/2,      70}, 0xFFFFFF);
		_stprintf(text, _T("BEST SCORE:%05d"), data.bestScore);
		DrawStrST str2(text, {WINDOW_WID/2-380, 150}, COLOR_BEST_SCORE);
		_stprintf(text, _T("SCORE:%05d"),      data.score);
		DrawStrST str3(text, {WINDOW_WID/2,     150}, COLOR_SCORE);
		_stprintf(text, _T("TIME:%.3f"),       tmScene[SCENE_GAME].GetPassTime());
		DrawStrST str4(text, {WINDOW_WID/2+380, 150}, COLOR_TIME);
		//�e�L�X�g(main)
		SetDrawBlendModeST(MODE_ALPHA, 255 * alpha4);
		str1.DrawStringST(TRUE, data.font3);
		SetDrawBlendModeST(MODE_ALPHA, 255 * alpha1);
		str2.DrawStringST(TRUE, data.font3);
		SetDrawBlendModeST(MODE_ALPHA, 255 * alpha2);
		str3.DrawStringST(TRUE, data.font3);
		SetDrawBlendModeST(MODE_ALPHA, 255 * alpha3);
		str4.DrawStringST(TRUE, data.font3);
		//�e�L�X�g(����p)
		str2.SetColor(0xFFFFFF);
		str3.SetColor(0xFFFFFF);
		str4.SetColor(0xFFFFFF);
		SetDrawBlendModeST(MODE_ALPHA, 100 * animSin1);
		str2.DrawStringST(TRUE, data.font3);
		SetDrawBlendModeST(MODE_ALPHA, 100 * animSin2);
		str3.DrawStringST(TRUE, data.font3);
		SetDrawBlendModeST(MODE_ALPHA, 100 * animSin3);
		str4.DrawStringST(TRUE, data.font3);
		//�`�惂�[�h���Z�b�g.
		ResetDrawBlendMode();
	}
}
//�I�u�W�F�N�g�̕`��.
void GameManager::DrawObjects() {

	//Lv1�ȏ�.
	laserMng.Draw();
	meteoMng.Draw();
	obstacle4_1.Draw();
	obstacle4_2.Draw();
	item.Draw();
	//Lv2�ȏ�.
	if (data.level >= 2) {
		mgl[0].Draw();
		mgl[1].Draw();
	}
	//Lv3�ȏ�.
	if (data.level >= 3) {
		obstacle5.Draw();
	}
	//Lv4�ȏ�.
	if (data.level >= 4) {
		obstacle4_3.Draw();
		obstacle4_4.Draw();
	}
}
//���˃��[�h���o.
void GameManager::DrawReflectMode() {

	//�J�E���g�_�E����.
	if (tmSlowMode.GetIsMove() && tmSlowMode.GetPassTime() > 0)
	{
		//�e�L�X�g�̐ݒ�.
		TCHAR text[256];
		_stprintf(text, _T("%d"), (int)ceil(tmSlowMode.GetPassTime())); //TCHAR�^�ɕϐ�����.
		DrawStrST str1(_T("REFLECT"), {WINDOW_WID/2, WINDOW_HEI/2}, COLOR_ITEM);
		DrawStrST str2(text,          {WINDOW_WID/2, WINDOW_HEI/2}, COLOR_ITEM);

		//��ʒ����ɐ�����\��.
		{
			double dec = GetDecimal(tmSlowMode.GetPassTime()); //�����������o��.
			SetDrawBlendModeST(MODE_ADD, _int(255 * dec));     //1�b���Ƃɔ����Ȃ鉉�o.
			//�ŏ���1�b.
			if (tmSlowMode.GetPassTime() > SLOW_MODE_TIME-1) {
				str1.DrawStringST(TRUE, data.font3); //���˃��[�h.
			}
			//�Ō��3�b.
			if (tmSlowMode.GetPassTime() <= 3) {
				str2.DrawStringST(TRUE, data.font3); //����.
			}
			ResetDrawBlendMode();
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

	for (int i = 0; i < _countof(isItemCount); i++) {
		isItemCount[i] = FALSE;
	}

	data.scoreBef = data.score;                                  //���ԉ��Z�O�̃X�R�A���L�^.
	data.score += (int)(tmScene[SCENE_GAME].GetPassTime() * 10); //���ԃ{�[�i�X���Z.

	//�ō��X�R�A�X�V�Ȃ�ۑ�.
	if (data.score > data.bestScore) {

		FileST file;
		file.Open(FILE_DATA_PATH, _T("w")); //�t�@�C�����J��.
		file.WriteInt(data.score);          //�X�R�A��ۑ�.
	}

	//�T�E���h.
	p_sound->FadeOutPlay(_T("BGM1"), 2);
}
//�A�C�e�����������.
void GameManager::TakeItem() {

	data.isSlow = TRUE;             //�X���[���[�h�ɂ���.
	data.score += SCORE_TAKE_ITEM;  //�X�R�A���Z.
	tmSlowMode.Start();             //�X���[���[�h�v���J�n.
	player.SetReflectionMode(TRUE); //���˃��[�h�J�n.
}