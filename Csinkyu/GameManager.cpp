/*--------------------------------------------------------/
   - REFLECT LINE -

   (���{��\�L: ���t���N�g���C��)
   (���́@�@�@: REFLINE/���t���C��)
/---------------------------------------------------------/
   TODO����

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

   2025/08/02:
   UI�ɔw�i�摜�����Œǉ��������A�[�̕��𓧉߂��������B

   2025/08/04:
   Ex�X�e�[�W�������Ă����������B
   ����̏����ōs�����Ƃ��ł��āA���ʂȃ��[�������銴���ŁB
   ���ʊ��̂���BGM��w�i�ɕς���B

   2025/08/23:
   �V��Q���u�ԉ΁v��ǉ�����BLevel4�œo��\��B
   �ڂ����͌�����k, �Ȃ��Ƃɍ���Ă��炤?

   2025/08/27:
   �J�n���A������@��������ĈȌ�̐�������ς������B
   �EKEY_SPACE �����������Push SPACE (�L�[�{�[�h����)
   �EPAD_XBOX_A�����������Push A     (�p�b�h����)
   �ȂǁB

   2025/09/08:
   �E�ԉ΂̃o�O�C��(�X���[���[�h�ɑΉ����ĂȂ�, ���܂ɕs������)
   �E�z���vector�ɕς���B�ŏ���reserve�ŕK�v���m�ۂ��A�f�X�g���N�^�ŉ������΂����B
   �ECalc.h��Calc�N���X�͂Ȃ��Ă����B�֐��Q�Ƃ��Ēu���AKR_Lib���O��ԓ���Calc�Ƃ������O��Ԃ�u����OK�B

   2025/09/09:
   �E�Q�[���I�[�o�[��ʂɃq���g��1���o������肽���B�����Ń��[�������̕�Ԃ�����B

   2025/09/16:
   �^�C�g�����烁�j���[�ɍs���Ƃ��A�p�b�Ɖ�ʂ�ς����Ƀt�F�[�h�A�E�g�Ŋ��炩�Ɉړ�����悤�ɂ������B

   2025/09/21:
   [�i��]
   �E�A�C�e���̎g�p�^�C�~���O��ύX
   �E�X���[���[�h�̑Ή����uspeedRate�v�������邾���ŗǂ���������
   �@��: counter -= (p_data->isSlow) ? SLOW_MODE_SPEED : 1;
	 �V: counter -= p_data->speedRate;
   [���P�_]
   �ELevelUp���o, Step���o���G�t�F�N�g�̂��߁A�G�t�F�N�g������܂ŏo�Ă�ƕ\�����o�Ȃ��Ȃ���

/---------------------------------------------------------/
   [�`���[�g���A���z��]
   step1: ������ 
�@   ��莞�ԑς����玟�ցB
   step2: �Ƃ�
�@   �A�C�e����1�����ĉ������ꂽ�玟�ցB
   step3: ���킷
�@   �܂��͎����ŃA�C�e��������ă��[�U�[�����˂���l�q���݂���B
�@   ���̌�A�����ő��삳���Ď���������B覐΂�n�󂹂��玟�ցB
   step4: ��ʂ�v���C
�@   �Ō�Ɉ�ʂ�v���C���Ċm�F������B��莞�Ԍo������`���[�g���A���I���B

   ���X�R�A�̐����̓`���[�g���A���ɂ͂���Ȃ�
   �����j���[�Ƀ��[�h���Ƃ̐���������(�n�C�X�R�A��ڎw���`�Ȃ�)

   [���݂�Level�z��]
   Level1: �ʏ탌�[�U�[�~2, 覐�
   Level2: �������[�U�[�~2
   Level3: �g��
   Level4: �ԉ�, �A�C�e���~2
   Level5: �ʏ탌�[�U�[�~4, �A�C�e��������
/---------------------------------------------------------/
   �y����̐���\��z

   ���킷���\�܂�:
   �E��Q���u�ԉ΁v�ǉ�
   �E�^�C�g�����S�ύX(�Q�[�����ύX�̂���)

   TGS�W���܂�:
   �E�J�n���̑�����@����(�ł����)
   �E�Q�[�����`���[�g���A��
   �ESCORE�����L���O����
   �E�|�X�^�[ver2 & �A���P�[�g���
   
   �ŏI�ڕW:
   �ESCORE���E�����L���O��
   �Esteam�̔�

   [BGM]
   youtube�uTak_mfk�v����g�p�B
   steam�̔��̎��ɂ̓��C�Z���X�ɒ��ӁB
/--------------------------------------------------------*/
/*
   - GameManager.cpp -
   �Q�[���S�̊Ǘ�.
*/

#include "BackGround.h"
#include "MenuManager.h"
#include "Stage_Tutorial.h"
#include "Stage_Endless.h"

#include "LaserManager.h"
#include "Obst_NormalLaser.h"
#include "Obst_NormalLaserMain.h"
#include "Obst_StraightLaser.h"
#include "Obst_MeteorManager.h"
#include "Obst_Ripples.h"
#include "Obst_Fireworks.h"

#include "Item.h"
#include "Player.h"

#include "EffectManager.h"
#include "UIManager.h"

#include "GameManager.h"

//�|�C���^.
GameData         *gameData     = GameData::GetPtr();
BackGround       *bg           = BackGround::GetPtr();
MenuManager      *menuMng      = MenuManager::GetPtr();
TutorialStage    *tutorialStg  = TutorialStage::GetPtr();
EndlessStage     *endlessStg   = EndlessStage::GetPtr();
LaserManager     *laserMng     = LaserManager::GetPtr();
MeteorManager    *meteorMng    = MeteorManager::GetPtr();
Ripples          *ripples      = Ripples::GetPtr();
FireworksManager *fireworksMng = FireworksManager::GetPtr();
ItemManager      *item         = ItemManager::GetPtr();
Player           *player       = Player::GetPtr();
EffectManager    *effectMng    = EffectManager::GetPtr();
UIManager        *uiMng        = UIManager::GetPtr();
//��Q���̎���.
NormalLaser_1 laserNor1;
NormalLaser_2 laserNor2;
NormalLaser_3 laserNor3;
NormalLaser_4 laserNor4;
StraightLaser mgl[4];

using namespace Calc; //�v�Z�@�\���g�p.

//������(���̂ݍs��)
void GameManager::Init() {

	srand((unsigned)time(NULL)); //����������.
	
	//���̎擾.
	p_input = InputMng::GetPtr();
	p_sound = SoundMng::GetPtr();

	//�t�H���g�쐬.
	gameData->font1 = CreateFontToHandle(NULL, 26, 1);
	gameData->font2 = CreateFontToHandle(NULL, 30, 1, DX_FONTTYPE_ANTIALIASING);
	gameData->font3 = CreateFontToHandle(NULL, 35, 1, DX_FONTTYPE_ANTIALIASING);
	gameData->font4 = CreateFontToHandle(NULL, 40, 1, DX_FONTTYPE_ANTIALIASING);
	//�摜�ǂݍ���.
	imgLogo[0].  LoadFile(_T("Resources/Images/REFLINE���S_�ꕔ.png"));
	imgLogo[1].  LoadFile(_T("Resources/Images/REFLINE���S.png"));
	imgUI.       LoadFile(_T("Resources/Images/ui_back_best_score.png"));
	imgNewRecord.LoadFile(_T("Resources/Images/new_record.png"));
	imgGameOver. LoadFile(_T("Resources/Images/gameover.png"));
	imgReflect.  LoadFile(_T("Resources/Images/reflect.png"));
	//�T�E���h�ǂݍ���.
	p_sound->LoadFile(_T("Resources/Sounds/bgm/Virtual Terminal.mp3"),	    _T("BGM_Menu"));     //���j���[BGM.
	p_sound->LoadFile(_T("Resources/Sounds/bgm/audiostock_1603723.mp3"),	_T("BGM_Tutorial")); //�`���[�g���A��BGM.
	p_sound->LoadFile(_T("Resources/Sounds/bgm/Scarlet Radiance.mp3"),		_T("BGM_Endless"));  //�ϋv���[�hBGM.
	p_sound->LoadFile(_T("Resources/Sounds/bgm/���i�L�҃m��.mp3"),		    _T("BGM_Over"));     //�Q�[���I�[�o�[BGM.

	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_461339.mp3"),		_T("ItemUse")); 	 //�A�C�e������.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_1116927_cut.mp3"),	_T("CountDown"));	 //�J�E���g�_�E��.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_63721.mp3"),		_T("PowerDown"));	 //�A�C�e������.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_1296254.mp3"),		_T("Laser1"));		 //���[�U�[(����)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_1296256.mp3"),		_T("Laser2"));		 //���[�U�[(������)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_218404.mp3"),		_T("Laser3"));		 //���[�U�[(����)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_936158.mp3"),		_T("Ripples"));		 //�g��.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_104974.mp3"),		_T("Break"));		 //覐Δj��.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_981051.mp3"),		_T("PlayerDeath"));
	p_sound->LoadFile(_T("Resources/Sounds/se/����{�^��������23.mp3"),		_T("LevelUp"));
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_184924.mp3"),		_T("BestScore"));	 //�ō��X�R�A�X�V.
	
	//�A�N�V�����o�^.
	p_input->AddAction(_T("GameNext"),  KEY_SPACE);           //�L�[����.
	p_input->AddAction(_T("GameNext"),  PAD_ACD_BTN_UPPER_1); //�A�[�P�[�h����.
	p_input->AddAction(_T("GamePause"), KEY_P);               //�L�[����.
	p_input->AddAction(_T("GamePause"), PAD_ACD_BTN_UPPER_2); //�A�[�P�[�h����.

	//�^�C�}�[������.
	for(int i = 0; i < SCENE_COUNT; i++){
		tmScene[i] = Timer(COUNT_UP, 0);
	}
	tmGameTime = Timer(COUNT_UP, 0);
	tmSlowMode = Timer(COUNT_DOWN, REFLECT_MODE_TIME);

	//Init����
	{
		//��Q��.
		for (int i = 0; i < _countof(mgl); i++) {
			mgl[i].Init();
		}
		laserNor1.Init();
		laserNor2.Init();
		laserNor3.Init();
		laserNor4.Init();

		bg->Init();
		menuMng->Init();
		tutorialStg->Init();
		endlessStg->Init();
		laserMng->Init();
		meteorMng->Init();
		ripples->Init();
		fireworksMng->Init();
		item->Init();
		player->Init();
		effectMng->Init();
		uiMng->Init();
	}

	//�X�R�A�ǂݍ���.
	{
		File file;
		file.Open(FILE_DATA, _T("r"));        //�t�@�C�����J��.
		gameData->bestScore = file.ReadInt(); //������ǂݍ���œo�^.
	}

	Reset();
}

//���Z�b�g(����ł��s��)
void GameManager::Reset() {

	if (gameData->bestScore < gameData->score) {
		gameData->bestScore = gameData->score; //�n�C�X�R�A�L�^.
	}

	//�f�[�^.
	gameData->scoreBef      = 0;
	gameData->score         = 0;
	gameData->counter       = 0;
	gameData->speedRate     = 1.0;   //�ʏ��100%
	gameData->spawnRate     = 1.0;   //�ŏ���100%
	gameData->level         = 1;     //�ŏ���Lv1
	gameData->isReflectMode = false; //�ŏ���Lv1
	isTitleAnim             = false;
	isBestScoreSound        = false;
	isGameStart             = false;
	//�T�E���h.
	p_sound->StopAll();
	p_sound->Play(_T("BGM_Menu"), true, 90); //���j���[BGM�𗬂�.
	//�^�C�}�[(�S�V�[��)
	for (int i = 0; i < SCENE_COUNT; i++) {
		tmScene[i].Reset();
	}
	tmGameTime.Reset();

	{
		//���[�U�[�n.
		ResetNorLaser();
		ResetStrLaser();

		menuMng->Reset();
		tutorialStg->Reset();
		laserMng->Reset();
		meteorMng->Reset();
		ripples->Reset();
		fireworksMng->Reset();
		effectMng->Reset();
		item->Reset();
		player->Reset({ WINDOW_WID/2, WINDOW_HEI/2+250 }, true);
	}
}

//�X�V.
void GameManager::Update() {

	p_input->UpdateKey();    //�L�[���͍X�V.
	p_input->UpdatePad();    //�R���g���[�����͍X�V.
	p_input->UpdateAction(); //�A�N�V�����X�V.
	p_sound->Update();       //�T�E���h�X�V.

	//�|�[�Y���ĂȂ����.
	if (gameData->scene != SCENE_PAUSE) {
		bg->Update();        //�w�i.
		effectMng->Update(); //�G�t�F�N�g.
	}

	//�V�[����.
	switch (gameData->scene) 
	{
		case SCENE_TITLE:    UpdateTitle();    break;
		case SCENE_MENU:     UpdateMenu();     break;
		case SCENE_GAME:     UpdateGame();     break;
		case SCENE_END:      UpdateEnd();      break;
		case SCENE_PAUSE:    UpdatePause();    break;
	
		default: assert(FALSE); break;
	}

	//����̑���ŃQ�[���I��
	if (p_input->IsPushPadBtnTime(PAD_ACD_BTN_START) >= FPS * 1) {
		DxLibMain::GetPtr()->GameEnd(); //➑�START�{�^���������ŏI��.
	}
	else if (p_input->IsPushKey(KEY_ESC)) {
		DxLibMain::GetPtr()->GameEnd(); //ESCAPE�L�[���������瑦�I��.
	}
}

//�`��.
void GameManager::Draw() {

	bg->Draw(); //�w�i.

	//�V�[����.
	switch (gameData->scene) 
	{
		case SCENE_TITLE:    DrawTitle();    break;
		case SCENE_MENU:     DrawMenu();     break;
		case SCENE_GAME:     DrawGame();     break;
		case SCENE_END:      DrawEnd();      break;
		case SCENE_PAUSE:    DrawPause();    break;

		default: assert(FALSE); break;
	}

	effectMng->Draw(); //�G�t�F�N�g.
}

//�ʏ탌�[�U�[�̃��Z�b�g.
void GameManager::ResetNorLaser() {

	laserNor1.Reset(WINDOW_WID/2, 0, 3, MOVE_RIGHT);
	laserNor2.Reset(WINDOW_WID/2, 0, 3, MOVE_LEFT);
	laserNor3.Reset(WINDOW_WID/2, WINDOW_HEI, 3, MOVE_RIGHT);
	laserNor4.Reset(WINDOW_WID/2, WINDOW_HEI, 3, MOVE_LEFT);
}
//�������[�U�[�̃��Z�b�g.
void GameManager::ResetStrLaser() {

	for (int i = 0; i < _countof(mgl); i++) {
		mgl[i].Reset();
	}
}

//�V�[���ʍX�V.
void GameManager::UpdateTitle()
{
	//�V�[���^�C�}�[�J�n.
	if (!tmScene[SCENE_TITLE].GetIsMove()) {
		tmScene[SCENE_TITLE].Start();
	}

	//����̑���ŃQ�[���J�n.
	if (p_input->IsPushActionTime(_T("GameNext")) == 1)
	{
		gameData->scene = SCENE_MENU; //���j���[�V�[����.

		//覐Δj��A�j���[�V����.
		{
			double dig = -130; //�p�x.

			//�G�t�F�N�g���������o��.
			for (int i = 0; i < METEOR_BREAK_ANIM_CNT; i++) {

				double newDig = dig + (float)RandNum(-300, 300)/10; //�����p�x�����炷.

				EffectData data{};
				data.type  = Effect_BreakMeteo;
				data.pos   = { 600, 338 };
				data.vec   = CalcVectorDeg(newDig);               //���炵���p�x�𔽉f.
				data.speed = ((float)RandNum(20, 100)/10) * 1.4f; //���x���I.
				data.len   = ((float)RandNum(10, 150)/10) * 1.4f; //�������I.
				data.ang   =  (float)RandNum(0, 3599)/10;         //�p�x���I.
				//�G�t�F�N�g����.
				effectMng->SpawnEffect(&data);
			}
			//�T�E���h.
			p_sound->Play(_T("Break"), false, 65);
		}
	}
}
void GameManager::UpdateMenu() {
	menuMng->Update();
}
void GameManager::UpdateGame() {
	
#if defined _DEBUG //Release�ł͓���Ȃ�.
	//�^�C�}�[����(Debug)
	if (p_input->IsPushKey(KEY_L) == 1) {
		gameData->counter += 30;
	}
#endif

	//�V�[���^�C�}�[�J�n.
	if (!tmScene[SCENE_GAME].GetIsMove()) {
		tmScene[SCENE_GAME].Start();
	}

	//�Q�[���J�n�O.
	if (!isGameStart) {
		//��莞�Ԍo������.
		if (tmScene[SCENE_GAME].GetPassTime() >= GAME_START_TIME) {

			tmGameTime.Start(); //�Q�[�����Ԍv���J�n.
			isGameStart = true; //�Q�[���J�n.
		}
	}
	//�Q�[���J�n��.
	else{

		UpdateObjects();  //�I�u�W�F�N�g.
		UpdateSlowMode(); //�X���[���[�h.

		//�X�e�[�W��.
		switch (gameData->stage) 
		{
			case STAGE_TUTORIAL: tutorialStg->Update(); break;
			case STAGE_ENDLESS:  endlessStg->Update();  break;

			default: assert(FALSE); break;
		}
		//�|�[�Y.
		if (p_input->IsPushActionTime(_T("GamePause")) == 1) {
			gameData->scene = SCENE_PAUSE;
			tmGameTime.Stop(); //�ꎞ��~.
			tmSlowMode.Stop(); //�ꎞ��~.
		}
	}

	player->Update(); //�v���C���[.
}
void GameManager::UpdateEnd() {

	//�V�[���^�C�}�[�J�n.
	if (!tmScene[SCENE_END].GetIsMove()) {
		tmScene[SCENE_END].Start();
	}

	//����̑���Ń^�C�g����.
	if (p_input->IsPushActionTime(_T("GameNext")) == 1)
	{
		gameData->scene = SCENE_TITLE; //�Q�[���V�[����.
		Reset();
	}
}
void GameManager::UpdatePause() {
	
	//�|�[�Y����.
	if (p_input->IsPushActionTime(_T("GamePause")) == 1) {

		gameData->scene = SCENE_GAME;
		tmGameTime.Start(); //�ĊJ.
		//�X���[���[�h���������Ȃ�.
		if (tmSlowMode.GetPassTime() < REFLECT_MODE_TIME) {
			tmSlowMode.Start(); //�ĊJ.
		}
	}
}

//�I�u�W�F�N�g�̍X�V.
void GameManager::UpdateObjects() {

	//Lv1�ȏ�.
	laserMng->Update();
	laserNor1.Update();
	laserNor2.Update();
	meteorMng->Update();
	item->Update();

	//Lv2�ȏ�.
	if (gameData->level >= 2) {
		mgl[0].Update();
		mgl[1].Update();
	}
	//Lv3�ȏ�.
	if (gameData->level >= 3) {
		ripples->Update();
	}
	//Lv4�ȏ�.
	if (gameData->level >= 4) {
		fireworksMng->Update();
	}
	//Lv5�ȏ�.
	if (gameData->level >= 5) {
		laserNor3.Update();
		laserNor4.Update();
	}
}
//�X���[���[�h�̍X�V.
void GameManager::UpdateSlowMode() {

	//�X���[���[�h���Ԕ���.
	if (gameData->slowBufCntr > 0) {
		gameData->speedRate  = SLOW_MODE_SPEED; //���x�{����x������.
		gameData->slowBufCntr--;                //�J�E���g�����炷.
	}
	else {
		gameData->speedRate  = 1.0; //���x�{����߂�.
	}

	//�X���[���[�h��.
	if (tmSlowMode.GetIsMove()) {
		//3�b�ȉ��ɂȂ����΂���̎�.
		if (tmSlowMode.GetPassTime() <= 3) {
			if (!isItemCountDownSound[2]) {
				p_sound->Play(_T("CountDown"), false, 78); //�Đ�.
				isItemCountDownSound[2] = true;
			}
		}
		//2�b�ȉ��ɂȂ����΂���̎�.
		if (tmSlowMode.GetPassTime() <= 2) {
			if (!isItemCountDownSound[1]) {
				p_sound->Play(_T("CountDown"), false, 78); //�Đ�.
				isItemCountDownSound[1] = true;
			}
		}
		//1�b�ȉ��ɂȂ����΂���̎�.
		if (tmSlowMode.GetPassTime() <= 1) {
			if (!isItemCountDownSound[0]) {
				p_sound->Play(_T("CountDown"), false, 78); //�Đ�.
				isItemCountDownSound[0] = true;
			}
		}
		//���Ԑ؂�ŉ���.
		if (tmSlowMode.GetPassTime() <= 0) {
			
			p_sound->Play(_T("PowerDown"), false, 78); //�Đ�.
			
			gameData->isReflectMode = false; //���˃��[�h����.
			gameData->speedRate     = 1.0;   //���x�{����100%�ɖ߂�.
			gameData->slowBufCntr   = 0;     //�J�E���^�[��0��.
			tmSlowMode.Reset();
			player->SetMode(Player_Normal);  //�ʏ��Ԃɖ߂�.
			
			for (int i = 0; i < _countof(isItemCountDownSound); i++) {
				isItemCountDownSound[i] = false;
			}
		}
	}
}

//�V�[���ʕ`��.
void GameManager::DrawTitle() {
	
	//�A�j���[�V�����؂�ւ��|�C���g.
	const float delay1 = 1;
	const float delay2 = 1.4f;
	const float delay3 = 1.6f;
	const float delay4 = 3;
	const float delay5 = 3;

	//�摜�̕\��.
	{
		const int    logoY   = WINDOW_HEI/2 - 85;
		const DBL_XY imgSize = {0.7, 0.7};
	
		//�؂�ւ��O.
		if (tmScene[SCENE_TITLE].GetPassTime() < delay1) {
			//�A�j���[�V�����l.
			double anim = CalcNumEaseInOut(tmScene[SCENE_TITLE].GetPassTime()/delay1);
			//���S1����.
			SetDrawBlendModeST(MODE_ALPHA, 255 * anim);
			imgLogo[0].DrawExtend({WINDOW_WID/2, logoY}, imgSize, ANC_MID, true, true);
		}
		//�؂�ւ���.
		else {
			//�A�j���[�V�����l.
			double anim1 = CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay1    )/1.8);
			double anim2 = CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay1-0.4)/1.8); //�����x������.
			//���S1����.
			SetDrawBlendModeST(MODE_ALPHA, 255 * (1-anim2));
			imgLogo[0].DrawExtend({WINDOW_WID/2, logoY - anim1*100}, imgSize, ANC_MID, true, true);
			//���S2����.
			SetDrawBlendModeST(MODE_ALPHA, 255 * anim1);
			imgLogo[1].DrawExtend({WINDOW_WID/2, logoY - anim1*100}, imgSize, ANC_MID, true, true);
		}
		//�`�惂�[�h���Z�b�g.
		ResetDrawBlendMode();
	}

	//best score.
	if (tmScene[SCENE_TITLE].GetPassTime() > delay2) {

		const int drawY = WINDOW_HEI/2 + 130;

		//�A�j���[�V�����l.
		double anim1 = CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay3)/1.5);
		double anim2 = CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay2)/1.5);
		//�e�L�X�g.
		TCHAR text[256];
		_stprintf(text, _T("BEST SCORE: %d"), gameData->bestScore); //�x�X�g�X�R�A.
		DrawStr str(text, {WINDOW_WID/2, drawY+1}, COLOR_BEST_SCORE);

		SetDrawBlendModeST(MODE_ALPHA, 255*anim1);
		str.Draw(ANC_MID, gameData->font2); //�X�R�A�l.
		SetDrawBlendModeST(MODE_ALPHA, 255*anim2);
		imgUI.DrawExtend({WINDOW_WID/2, drawY + (10+18*anim2)}, {0.45, 0.4}, ANC_MID, true, true);
		imgUI.DrawExtend({WINDOW_WID/2, drawY - (10+18*anim2)}, {0.45, 0.4}, ANC_MID, true, true);
		ResetDrawBlendMode();
	}
	//PUSH SPACE.
	if (tmScene[SCENE_TITLE].GetPassTime() > delay4) {

		const int drawY = WINDOW_HEI/2+310;

		//�A�j���[�V�����l.
		double anim = CalcNumWaveLoop(tmScene[SCENE_TITLE].GetPassTime()-delay4);
		//�e�L�X�g.
		DrawStr str(_T("Push SPACE or  X"), {WINDOW_WID/2-5, drawY}, 0xFFFFFF);
		Circle cir = { {WINDOW_WID/2+92, drawY-2}, 18, 0xFFFFFF };
		
		SetDrawBlendModeST(MODE_ALPHA, 255*anim);
		str.Draw(ANC_MID, gameData->font1); //�e�L�X�g.
		DrawCircleST(&cir, false, false);   //X�{�^���̉~.
		ResetDrawBlendMode();
	}
}
void GameManager::DrawMenu() {
	menuMng->Draw();
}
void GameManager::DrawGame() {

	DrawObjects();      //�I�u�W�F�N�g.
	player->Draw();     //�v���C���[.
	DrawReflectMode();  //���˃��[�h���o.
	uiMng->Draw();      //UI.
}
void GameManager::DrawEnd() {
	
	DrawObjects(); //�I�u�W�F�N�g.
	{
		float anim = min(tmScene[SCENE_END].GetPassTime(), 1); //�A�j���[�V�����l.
		Box box = { {0, 0}, {WINDOW_WID, WINDOW_HEI}, 0x000000 };

		SetDrawBlendModeST(MODE_ALPHA, 128*anim);
		DrawBoxST(&box, ANC_LU); //��ʂ��Â�����(UI�ȊO)
		ResetDrawBlendMode();
	}
	uiMng->Draw(); //UI.

	//�I���ē�.
	{
		//�A�j���[�V�����l.
		double anim = CalcNumEaseOut(tmScene[SCENE_END].GetPassTime());

		//�X�R�A�\��.
		TCHAR text[256];
		_stprintf(
			text, _T("%d + %d(%.3f�b) = %d�_"),
			gameData->scoreBef, _int(tmGameTime.GetPassTime() * 10), tmGameTime.GetPassTime(), gameData->score
		);
		//�e�L�X�g�̐ݒ�.
		DrawStr str1(_T("Time Bonus"), {WINDOW_WID/2, WINDOW_HEI/2-20}, 0xFFFFFF);
		DrawStr str2(text,             {WINDOW_WID/2, WINDOW_HEI/2+20}, 0xFFFFFF);
		//��ʒ����ɕ�����\��.
		SetDrawBlendModeST(MODE_ALPHA, 255*anim);
		imgGameOver.DrawExtend({WINDOW_WID/2, 370+30*anim}, {0.5, 0.5}, ANC_MID, true, true); //GAME OVER
		str1.Draw(ANC_MID, gameData->font1);
		str2.Draw(ANC_MID, gameData->font1);
		ResetDrawBlendMode();
	}

	const float delay1 = 1.2f;
	const float delay2 = 1.5f;

	//��莞�Ԃ��o������.
	if (tmScene[SCENE_END].GetPassTime() > delay1) {
		//�x�X�g�X�R�A�X�V.
		if (gameData->score > gameData->bestScore) {

			//�A�j���[�V�����l.
			double anim = CalcNumEaseOut((tmScene[SCENE_END].GetPassTime()-delay1)*2);
			//�`��.
			SetDrawBlendModeST(MODE_ALPHA, 255*anim);
			imgNewRecord.DrawExtend({WINDOW_WID/2, WINDOW_HEI/2-330+anim*20}, {0.4, 0.4}, ANC_MID, true, true); //NEW RECORD
			ResetDrawBlendMode();
			//�T�E���h.
			if (!isBestScoreSound) {
				p_sound->Play(_T("BestScore"), false, 65);
				isBestScoreSound = true; //��x�̂�.
			}
		}
	}
	//��莞�Ԃ��o������.
	if (tmScene[SCENE_END].GetPassTime() > delay2) {
		
		//�A�j���[�V�����l.
		double anim = CalcNumWaveLoop(tmScene[SCENE_END].GetPassTime()-delay2);
		//�e�L�X�g.
		DrawStr str(_T("Push SPACE or  A"), {WINDOW_WID/2-5, WINDOW_HEI/2+145}, 0xFFFFFF);
		Circle cir = { {WINDOW_WID/2+92, WINDOW_HEI/2+145-1}, 18, 0xFFFFFF };
		
		SetDrawBlendModeST(MODE_ALPHA, 255*anim);
		str.Draw(ANC_MID, gameData->font1); //�e�L�X�g.
		DrawCircleST(&cir, false, false);   //A�{�^���̉~.
		ResetDrawBlendMode();
	}
}
void GameManager::DrawPause() {

	DrawGame(); //�Q�[���V�[���Ɠ���.
}

//�I�u�W�F�N�g�̕`��.
void GameManager::DrawObjects() {

	//Lv1�ȏ�.
	laserMng->Draw();
	laserNor1.Draw();
	laserNor2.Draw();
	meteorMng->Draw();
	item->Draw();
	//Lv2�ȏ�.
	if (gameData->level >= 2) {
		mgl[0].Draw();
		mgl[1].Draw();
	}
	//Lv3�ȏ�.
	if (gameData->level >= 3) {
		ripples->Draw();
	}
	//Lv4�ȏ�.
	if (gameData->level >= 4) {
		fireworksMng->Draw();
	}
	//Lv5�ȏ�.
	if (gameData->level >= 5) {
		laserNor3.Draw();
		laserNor4.Draw();
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
		DrawStr str(text, {WINDOW_WID/2, WINDOW_HEI/2}, COLOR_ITEM);

		//��ʒ����ɐ�����\��.
		{
			double dec  = GetDecimal(tmSlowMode.GetPassTime()); //�����������o��.
			double anim = CalcNumEaseOut(dec);
			
			SetDrawBlendModeST(MODE_ALPHA, _int_r(255 * dec)); //1�b���Ƃɔ����Ȃ鉉�o.
			//�ŏ���1�b.
			if (tmSlowMode.GetPassTime() > REFLECT_MODE_TIME-1) {
				imgReflect.DrawExtend({WINDOW_WID/2, WINDOW_HEI/2}, {0.3+0.2*anim, 0.3+0.2*anim});
			}
			//�Ō��3�b.
			if (tmSlowMode.GetPassTime() <= 3) {
				str.Draw(ANC_MID, gameData->font4); //����.
			}
			ResetDrawBlendMode();
		}
	}
}

//�Q�[���I��.
void GameManager::GameEnd() {
	
	//�܂��I����ĂȂ��Ȃ�(�O�̂���2�d���s����邱�Ƃ�h��)
	if (gameData->scene != SCENE_END) {

		gameData->scene = SCENE_END; //�Q�[���I����.
	
		tmGameTime.Stop(); //��~.
		tmSlowMode.Reset();
		gameData->speedRate = 1.0; //���x�{����100%�ɖ߂�.

		//�L�^���Z�b�g.
		for (int i = 0; i < _countof(isItemCountDownSound); i++) {
			isItemCountDownSound[i] = false;
		}

		gameData->scoreBef = gameData->score;                   //���ԉ��Z�O�̃X�R�A���L�^.
		gameData->score += _int(tmGameTime.GetPassTime() * 10); //���ԃ{�[�i�X���Z.

		//�ō��X�R�A�X�V�Ȃ�ۑ�.
		if (gameData->score > gameData->bestScore) {

			File file;
			file.MakeDir(FILE_DATA_PATH);   //�t�H���_�쐬.
			file.Open(FILE_DATA, _T("w"));  //�t�@�C�����J��.
			file.WriteInt(gameData->score); //�X�R�A��ۑ�.
		}

		//�T�E���h.
		switch (gameData->stage) 
		{
			case STAGE_TUTORIAL:
				p_sound->FadeOutPlay(_T("BGM_Tutorial"), 2);
				break;
			case STAGE_ENDLESS:
				p_sound->FadeOutPlay(_T("BGM_Endless"), 2);
				break;

			default: assert(FALSE); break;
		}
		//�Q�[���I�[�o�[BGM.
		p_sound->Play(_T("BGM_Over"), true, 68);
	}
}
//�A�C�e�����g�p������.
void GameManager::ItemUsed() {

	gameData->isReflectMode = true; //���˃��[�h�ɂ���.
	tmSlowMode.Start();             //�X���[���[�h�v���J�n.

	//�L�^���Z�b�g.
	for (int i = 0; i < _countof(isItemCountDownSound); i++) {
		isItemCountDownSound[i] = false;
	}
}