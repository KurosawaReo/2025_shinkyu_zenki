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

   2025/08/15:
   �z���vector�ɕς������B
   push_back�Ƃ����֐��ŗv�f�̒ǉ����ł��邽�߁A��������Ƃ��͂���Œǉ�����B

   �ő�T�C�Y�̒萔�͂��̂܂܎c���Ă����C������
   ��: if (size() < MAX_SIZE) {}

   2025/08/23:
   �V��Q���u�ԉ΁v��ǉ�����BLevel4�œo��\��B
   �ڂ����͌�����k, �Ȃ��Ƃɍ���Ă��炤?

   2025/08/27:
   �J�n���A������@��������ĈȌ�̐�������ς������B
   �EKEY_SPACE �����������Push SPACE (�L�[�{�[�h����)
   �EPAD_XBOX_A�����������Push A     (�p�b�h����)
   �ȂǁB

/---------------------------------------------------------/
   �O�����\��� �ύX���e

   �EUI�≉�o�ɉ摜��ǉ��B
   �EUI�̃��C�A�E�g�ύX�A�����̒ǉ��B�uTIME�v��uLEVEL�v���܂Ƃ߂��B
   �E�w�i�摜�����ŗp�ӁB
   �E�A�C�e���̏I���^�C�~���O��������悤�A�Ō��3�b�����\�����A�����ǉ��B
   �E�g��̔�������^�C�~���O��������悤�A���o�𒲐��B
   �E覐΂̔j�Ђ̔�юU��������A�����ۂ��Ȃ�悤�����B
   �E�|�[�Y�@�\���ǉ��B(P�L�[)
   �E�}�`����̃A���`�G�C���A�X�����B���炩���Y��ȕ`��ɂȂ����B
   �E���[�U�[�ŒZ���������`�悵�Ȃ��悤�ɁB(�����y���Ɍq����)
   �E�����A�C�e���ǉ��B���˃��[�U�[��覐΂ɓ������Ă����˂���B

   [���݂�Level�z��]
   Level1: �ʏ탌�[�U�[�~2, 覐�
   Level2: �������[�U�[�~2
   Level3: �g��
   Level4: �������[�U�[�~4, �A�C�e���~2
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

   [�`���[�g���A���z��] ����
   tutorial1: ������
   tutorial2: ���
   tutorial3: ��
   tutorial4: �G
   Level�Ɠ����悤�ȉ��o���o���Bstep�𓥂�ŗ��K������B
/--------------------------------------------------------*/
/*
   - GameManager.cpp -
   �Q�[���S�̊Ǘ�.
*/

#include "MeteoManager.h"
#include "LaserManager.h"
#include "EffectManager.h"

#include "Obstacle4.h"
#include "Obstacle4main.h"
#include "Obstacle5.h"
#include "MapGimmickLaser.h"

#include "Item.h"
#include "Player.h"

#include "BackGround.h"
#include "GameManager.h"

//�Ǘ��N���X�̎���.
BackGround    bg;
MeteoManager  meteoMng;
LaserManager  laserMng;
EffectManager effectMng;
//��Q���̎���.
Obstacle4_1 obstacle4_1;
Obstacle4_2 obstacle4_2;
Obstacle4_3 obstacle4_3;
Obstacle4_4 obstacle4_4;
Obstacle5   obstacle5;
MapGimmickLaser mgl[4];
//�A�C�e���̎���.
ItemManager item;
//�v���C���[�̎���.
Player player;

//������(���̂ݍs��)
void GameManager::Init() {

	srand((unsigned)time(NULL)); //����������.
	
	//���̎擾.
	p_input = InputMng::GetPtr();
	p_sound = SoundMng::GetPtr();
	p_calc  = Calc    ::GetPtr();

	//�^�C�g��.
	data.scene = SCENE_TITLE;
	//�t�H���g�쐬.
	data.font1 = CreateFontToHandle(NULL, 26, 1);
	data.font2 = CreateFontToHandle(NULL, 30, 1, DX_FONTTYPE_ANTIALIASING);
	data.font3 = CreateFontToHandle(NULL, 35, 1, DX_FONTTYPE_ANTIALIASING);
	data.font4 = CreateFontToHandle(NULL, 40, 1, DX_FONTTYPE_ANTIALIASING);
	//�摜�ǂݍ���.
	imgLogo[0].  LoadFile(_T("Resources/Images/REFLINE���S_�ꕔ.png"));
	imgLogo[1].  LoadFile(_T("Resources/Images/REFLINE���S.png"));
	imgUI[0].    LoadFile(_T("Resources/Images/ui_back_level.png"));
	imgUI[1].    LoadFile(_T("Resources/Images/ui_back_best_score.png"));
	imgUI[2].    LoadFile(_T("Resources/Images/ui_back_score.png"));
	imgUI[3].    LoadFile(_T("Resources/Images/ui_back_time.png"));
	imgNewRecord.LoadFile(_T("Resources/Images/new_record.png"));
	imgGameOver. LoadFile(_T("Resources/Images/gameover.png"));
	imgReflect.  LoadFile(_T("Resources/Images/reflect.png"));
	//�T�E���h�ǂݍ���.
	p_sound->LoadFile(_T("Resources/Sounds/bgm/Scarlet Radiance.mp3"),		_T("BGM1"));
	p_sound->LoadFile(_T("Resources/Sounds/bgm/audiostock_1603723.mp3"),	_T("BGM2"));
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
		bg.Init(&data);
		laserMng.Init(&data, &player, &meteoMng, &effectMng);
		meteoMng.Init(&data, &player, &effectMng);
		effectMng.Init(&data);
		//��Q��class.
		for (int i = 0; i < _countof(mgl); i++) {
			mgl[i].Init(&data, &player, &laserMng, &meteoMng);
		}
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
		File file;
		file.Open(FILE_DATA, _T("r"));   //�t�@�C�����J��.
		data.bestScore = file.ReadInt(); //������ǂݍ���œo�^.
	}
	
	data.stage = 1; //test

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
	data.isSlow = false;
	data.counter = 0;
	data.spawnRate = 1.0; //�ŏ���100%
	data.level = 1;       //�ŏ���Lv1
	isTitleAnim = false;
	isBestScoreSound = false;
	//�T�E���h.
	switch (data.stage) 
	{
		case 1:
			p_sound->Stop(_T("BGM1"));
			p_sound->Play(_T("BGM1"), true, 68);
			break;
		case 2:
			p_sound->Stop(_T("BGM2"));
			p_sound->FadeInPlay(_T("BGM2"), true, 68, 3);
			break;

		default: assert(false); break;
	}
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
		ResetNorLaser();
		ResetStrLaser();
		obstacle5.Reset();
		//�A�C�e��class.
		item.Reset();
		//�v���C���[class.
		player.Reset({ WINDOW_WID/2, WINDOW_HEI/2+185 }, true);
	}
}

//�X�V.
bool GameManager::Update() {

	p_input->UpdateKey(); //�L�[���͍X�V.
	p_input->UpdatePad(); //�R���g���[�����͍X�V.
	p_sound->Update();    //�T�E���h�X�V.

	bg.Update(); //�w�i.

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

	//����̑���ŃQ�[���I��
	if (p_input->IsPushPadBtnTime(PAD_ACD_BTN_START) >= FPS * 1) {
		return true; //➑�START�{�^���������ŏI��
	}
	else if (p_input->IsPushKey(KEY_ESC)) {
		return true; //ESCAPE�L�[���������瑦�I��.
	}
	return false; //���s.
}

//�`��.
void GameManager::Draw() {

	bg.Draw(); //�w�i.

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
//�������[�U�[�̃��Z�b�g.
void GameManager::ResetStrLaser() {

	for (int i = 0; i < _countof(mgl); i++) {
		mgl[i].Reset();
	}
}

//�V�[���ʍX�V.
void GameManager::UpdateTitle() 
{
	player.Update();    //�v���C���[.
	effectMng.Update(); //�G�t�F�N�g.

	//����̑���ŃQ�[���J�n.
	if (p_input->IsPushKeyTime(KEY_SPACE) == 1 || p_input->IsPushPadBtnTime(PAD_ACD_BTN_UPPER_1) == 1)
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
		p_sound->Play(_T("LevelUp"), false, 100);
		//�G�t�F�N�g.
		EffectData data{};
		data.type = Effect_Level1;
		data.pos = { WINDOW_WID/2, WINDOW_HEI/2 };
		effectMng.SpawnEffect(&data);
	}
}
void GameManager::UpdateGame() {
	
#if defined _DEBUG //Release�ł͓���Ȃ�.
	//�^�C�}�[����(Debug)
	if (p_input->IsPushKey(KEY_L) == 1) {
		data.counter += 10;
	}
#endif

	//�J�E���^�[����.
	data.counter += ((data.isSlow) ? SLOW_MODE_SPEED : 1);
	//�o���Ԋu.
	data.spawnRate = 1.0f/(1 + (data.counter/8000)); //100%���班��������.
	//���x���Ǘ�.
	switch (data.level)
	{
		case 1:
			if (data.counter >= 1500) { //1500 = �o���Ԋu��??%�n�_.
				data.level = 2; //Lv2��.

				//�T�E���h.
				p_sound->Play(_T("LevelUp"), false, 100);
				//�G�t�F�N�g.
				EffectData data{};
				data.type = Effect_Level2;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);
			}
			break;
		case 2:
			if (data.counter >= 3500) { //3500 = �o���Ԋu��??%�n�_.
				data.level = 3; //Lv3��.

				//�T�E���h.
				p_sound->Play(_T("LevelUp"), false, 100);
				//�G�t�F�N�g.
				EffectData data{};
				data.type = Effect_Level3;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);
			}
			break;
		case 3:
			if (data.counter >= 6000) { //6000 = �o���Ԋu��??%�n�_.
				data.level = 4; //Lv4��.

				ResetStrLaser();
				item.AddItemCnt(); //�A�C�e���𑝂₷.

				//�T�E���h.
				p_sound->Play(_T("LevelUp"), false, 100);
				//�G�t�F�N�g.
				EffectData data{};
				data.type = Effect_Level4;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);
			}
			break;
		case 4:
			if (data.counter >= 9000) { //9000 = �o���Ԋu��??%�n�_.
				data.level = 5; //Lv5��.

				ResetNorLaser();

				//�T�E���h.
				p_sound->Play(_T("LevelUp"), false, 100);
				//�G�t�F�N�g.
				EffectData data{};
				data.type = Effect_Level5;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);
			}
			break;
		case 5:
			//�ŏI���x��.
			break;

		default: assert(false); break;
	}

	//�X���[���[�h.
	if (tmSlowMode.GetIsMove()) {
		//3�b�ȉ��ɂȂ����΂���̎�.
		if (tmSlowMode.GetPassTime() <= 3){
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
			
			player.SetMode(Player_Normal); //���˃��[�h�I��.
			p_sound->Play(_T("PowerDown"), false, 78); //�Đ�.
			
			//���Z�b�g.
			tmSlowMode.Reset();
			data.isSlow = false;
			for (int i = 0; i < _countof(isItemCountDownSound); i++) {
				isItemCountDownSound[i] = false;
			}
		}
	}

	UpdateObjects();    //�I�u�W�F�N�g.
	player.Update();    //�v���C���[.
	effectMng.Update(); //�G�t�F�N�g.
	
	//�|�[�Y����.
	if((p_input->IsPushKeyTime(KEY_P) == 1) || (p_input->IsPushPadBtnTime(PAD_ACD_BTN_UPPER_2) == 1)){
		data.scene = SCENE_PAUSE;
		tmScene[SCENE_GAME].Stop(); //�ꎞ��~.
		tmSlowMode.Stop();          //�ꎞ��~.
	}
}
void GameManager::UpdateEnd() {

	effectMng.Update(); //�G�t�F�N�g.

	//����̑���Ń^�C�g����.
	if ((p_input->IsPushKeyTime(KEY_SPACE) == 1) || (p_input->IsPushPadBtnTime(PAD_ACD_BTN_UPPER_1) == 1))
	{
		data.scene = SCENE_TITLE; //�Q�[���V�[����.
		Reset();
	}
}
void GameManager::UpdatePause() {

	//�|�[�Y����.
	if ((p_input->IsPushKeyTime(KEY_P) == 1) || (p_input->IsPushPadBtnTime(PAD_ACD_BTN_UPPER_2) == 1)) {

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
		mgl[2].Update();
		mgl[3].Update();
	}
	//Lv5�ȏ�.
	if (data.level >= 5) {
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
	const float delay2 = 1.4f;
	const float delay3 = 1.6f;
	const float delay4 = 3;
	const float delay5 = 3;

	//�摜�̕\��.
	{
		const int logoY = WINDOW_HEI/2 - 75;
	
		//�؂�ւ��O.
		if (tmScene[SCENE_TITLE].GetPassTime() < delay1) {
			//�A�j���[�V�����l.
			double anim = p_calc->CalcNumEaseInOut(tmScene[SCENE_TITLE].GetPassTime()/delay1);
			//���S1����.
			SetDrawBlendModeST(MODE_ALPHA, 255 * anim);
			imgLogo[0].DrawExtend({WINDOW_WID/2, logoY}, {0.5, 0.5}, ANC_MID, true, true);
		}
		//�؂�ւ���.
		else {
			//�A�j���[�V�����l.
			double anim1 = p_calc->CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay1    )/1.8);
			double anim2 = p_calc->CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay1-0.4)/1.8); //�����x������.
			//���S1����.
			SetDrawBlendModeST(MODE_ALPHA, 255 * (1-anim2));
			imgLogo[0].DrawExtend({WINDOW_WID/2, logoY - anim1*100}, {0.5, 0.5}, ANC_MID, true, true);
			//���S2����.
			SetDrawBlendModeST(MODE_ALPHA, 255 * anim1);
			imgLogo[1].DrawExtend({WINDOW_WID/2, logoY - anim1*100}, {0.5, 0.5}, ANC_MID, true, true);
		}
		//�`�惂�[�h���Z�b�g.
		ResetDrawBlendMode();
	}

	//best score.
	if (tmScene[SCENE_TITLE].GetPassTime() > delay2) {

		const int scoreY = WINDOW_HEI/2 + 60;

		//�A�j���[�V�����l.
		double anim1 = p_calc->CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay3)/1.5);
		double anim2 = p_calc->CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay2)/1.5);
		//�e�L�X�g.
		TCHAR text[256];
		_stprintf(text, _T("BEST SCORE: %d"), data.bestScore); //�x�X�g�X�R�A.
		DrawStr str(text, {WINDOW_WID/2, scoreY+1}, COLOR_BEST_SCORE);

		SetDrawBlendModeST(MODE_ALPHA, 255*anim1);
		str.Draw(ANC_MID, data.font2); //�X�R�A�l.
		SetDrawBlendModeST(MODE_ALPHA, 255*anim2);
		imgUI[1].DrawExtend({WINDOW_WID/2, scoreY + (10+18*anim2)}, {0.5, 0.4}, ANC_MID, true, true);
		imgUI[1].DrawExtend({WINDOW_WID/2, scoreY - (10+18*anim2)}, {0.5, 0.4}, ANC_MID, true, true);
		ResetDrawBlendMode();
	}
	//PUSH SPACE.
	if (tmScene[SCENE_TITLE].GetPassTime() > delay4) {
		//�A�j���[�V�����l.
		double anim = p_calc->CalcNumWaveLoop(tmScene[SCENE_TITLE].GetPassTime()-delay4);
		//�e�L�X�g.
		DrawStr str(_T("Push SPACE or  X"), {WINDOW_WID/2-5, WINDOW_HEI/2+285}, 0xFFFFFF);
		Circle cir = { {WINDOW_WID/2+92, WINDOW_HEI/2+285-2}, 18, 0xFFFFFF };
		
		SetDrawBlendModeST(MODE_ALPHA, 255*anim);
		str.Draw(ANC_MID, data.font1);    //�e�L�X�g.
		DrawCircleST(&cir, false, false); //X�{�^���̉~.
		ResetDrawBlendMode();
	}
	//覐Δj��.
	if (tmScene[SCENE_TITLE].GetPassTime() > delay5) {
		//�܂��o���ĂȂ����.
		if (!isTitleAnim) {
			isTitleAnim = true; //��x����.

			double dig = -130; //�p�x.

			//�G�t�F�N�g���������o��.
			for (int i = 0; i < METEO_BREAK_ANIM_CNT; i++) {
				
				double newDig = dig + (float)p_calc->RandNum(-300, 300)/10; //�����p�x�����炷.

				EffectData data{}; 
				data.type  = Effect_BreakMeteo;
				data.pos   = { 600, 338 };
				data.vec   = p_calc->CalcVectorDeg(newDig);               //���炵���p�x�𔽉f.
				data.speed = ((float)p_calc->RandNum( 20,  100)/10)*1.4f; //���x���I.
				data.len   = ((float)p_calc->RandNum( 10,  150)/10)*1.4f; //�������I.
				data.ang   =  (float)p_calc->RandNum(  0, 3599)/10;       //�p�x���I.
				//�G�t�F�N�g����.
				effectMng.SpawnEffect(&data);
			}
			//�T�E���h.
			p_sound->Play(_T("Break"), false, 65);
		}
	}
}
void GameManager::DrawReady() {
	
#if false
	bg.Draw(); //�w�i.
	{
		float anim = min(tmScene[SCENE_READY].GetPassTime(), 1); //�A�j���[�V�����l.
		Box box = { {0, 0}, {WINDOW_WID, WINDOW_HEI}, 0x000000 };

		SetDrawBlendModeST(MODE_ALPHA, 255*(1-anim));
		DrawBoxST(&box, ANC_LU);
		ResetDrawBlendMode();
	}
#endif

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

//	DrawFormatString(100, 300, 0xFFFFFF, _T("pad:%d"), GetJoypadInputState(DX_INPUT_PAD1));
}
void GameManager::DrawEnd() {
	
	DrawObjects();    //�I�u�W�F�N�g.
	effectMng.Draw(); //�G�t�F�N�g.
	{
		float anim = min(tmScene[SCENE_END].GetPassTime(), 1); //�A�j���[�V�����l.
		Box box = { {0, 0}, {WINDOW_WID, WINDOW_HEI}, 0x000000 };

		SetDrawBlendModeST(MODE_ALPHA, 128*anim);
		DrawBoxST(&box, ANC_LU); //��ʂ��Â�����(UI�ȊO)
		ResetDrawBlendMode();
	}
	DrawUI();

	//�I���ē�.
	{
		//�A�j���[�V�����l.
		double anim = p_calc->CalcNumEaseOut(tmScene[SCENE_END].GetPassTime());

		//�X�R�A�\��.
		TCHAR text[256];
		_stprintf(
			text, _T("%d + %d(%.3f�b) = %d�_"),
			data.scoreBef, (int)(tmScene[SCENE_GAME].GetPassTime() * 10), tmScene[SCENE_GAME].GetPassTime(), data.score
		);
		//�e�L�X�g�̐ݒ�.
		DrawStr str1(_T("Time Bonus"), {WINDOW_WID/2, WINDOW_HEI/2-20}, 0xFFFFFF);
		DrawStr str2(text,             {WINDOW_WID/2, WINDOW_HEI/2+20}, 0xFFFFFF);
		//��ʒ����ɕ�����\��.
		SetDrawBlendModeST(MODE_ALPHA, 255*anim);
		imgGameOver.DrawExtend({WINDOW_WID/2, 370+30*anim}, {0.5, 0.5}, ANC_MID, true, true); //GAME OVER
		str1.Draw(ANC_MID, data.font1);
		str2.Draw(ANC_MID, data.font1);
		ResetDrawBlendMode();
	}

	const float delay1 = 1.2f;
	const float delay2 = 1.5f;

	//��莞�Ԃ��o������.
	if (tmScene[SCENE_END].GetPassTime() > delay1) {
		//�x�X�g�X�R�A�X�V.
		if (data.score > data.bestScore) {

			//�A�j���[�V�����l.
			double anim = p_calc->CalcNumEaseOut((tmScene[SCENE_END].GetPassTime()-delay1)*2);
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
		double anim = p_calc->CalcNumWaveLoop(tmScene[SCENE_END].GetPassTime()-delay2);
		//�e�L�X�g.
		DrawStr str(_T("Push SPACE or  A"), {WINDOW_WID/2-5, WINDOW_HEI/2+145}, 0xFFFFFF);
		Circle cir = { {WINDOW_WID/2+92, WINDOW_HEI/2+145-1}, 18, 0xFFFFFF };
		
		SetDrawBlendModeST(MODE_ALPHA, 255*anim);
		str.Draw(ANC_MID, data.font1);    //�e�L�X�g.
		DrawCircleST(&cir, false, false); //A�{�^���̉~.
		ResetDrawBlendMode();
	}
}
void GameManager::DrawPause() {

	DrawGame(); //�Q�[���V�[���Ɠ���.
}

//UI�̕`��.
void GameManager::DrawUI() {

#if defined DEBUG_SPAWN_RATE
	//�J�E���^�[.
	DrawFormatStringToHandle(
		10, WINDOW_HEI-75, 0xFFFFFF, data.font2, _T("Counter: %.2f"), data.counter
	);
	//�o���Ԋu����.
	DrawFormatStringToHandle(
		10, WINDOW_HEI-40, 0xFFFFFF, data.font2, _T("Spawn  : %.2f%%"), data.spawnRate*100
	);
#endif

	//�A�j���[�V�����l.
	double alpha1   = p_calc->CalcNumEaseInOut( tmScene[SCENE_READY].GetPassTime()-0.1);
	double alpha2   = p_calc->CalcNumEaseInOut( tmScene[SCENE_READY].GetPassTime()-0.2);
	double alpha3   = p_calc->CalcNumEaseInOut( tmScene[SCENE_READY].GetPassTime()-0.3);
	double alpha4   = p_calc->CalcNumEaseInOut((tmScene[SCENE_READY].GetPassTime()-1.0)*2);
	double animSin1 = sin(M_PI* tmScene[SCENE_READY].GetPassTime()-0.1);
	double animSin2 = sin(M_PI*(tmScene[SCENE_READY].GetPassTime()-0.2));
	double animSin3 = sin(M_PI*(tmScene[SCENE_READY].GetPassTime()-0.3));

	//�e�L�X�g�ݒ�.
	DrawStr str[4] = {
		DrawStr({}, {WINDOW_WID/2,      70+2}, 0xFFFFFF),
		DrawStr({}, {WINDOW_WID/2-350, 150  }, COLOR_BEST_SCORE),
		DrawStr({}, {WINDOW_WID/2,     150  }, COLOR_SCORE),
		DrawStr({}, {WINDOW_WID/2+350, 150  }, COLOR_TIME),
	};
	TCHAR text[256];
	_stprintf(text, _T("LEVEL %d"),        data.level);
	str[0].data.text = text;
	_stprintf(text, _T("BEST SCORE:%05d"), data.bestScore);
	str[1].data.text = text;
	_stprintf(text, _T("SCORE:%05d"),      data.score);
	str[2].data.text = text;
	_stprintf(text, _T("TIME:%.3f"),       tmScene[SCENE_GAME].GetPassTime());
	str[3].data.text = text;
		
	//�w�i�摜.
	imgUI[0].DrawExtend({WINDOW_WID/2, 70}, {0.4, 0.35});
	//�e�L�X�g(main)
	SetDrawBlendModeST(MODE_ALPHA, 255 * alpha4);
	str[0].Draw(ANC_MID, data.font4);
	SetDrawBlendModeST(MODE_ALPHA, 255 * alpha1);
	str[1].Draw(ANC_MID, data.font3);
	imgUI[1].DrawExtend({(double)str[1].data.pos.x, (double)str[1].data.pos.y+28}, {0.4, 0.4});
	SetDrawBlendModeST(MODE_ALPHA, 255 * alpha2);
	str[2].Draw(ANC_MID, data.font3);
	imgUI[2].DrawExtend({(double)str[2].data.pos.x, (double)str[2].data.pos.y+28}, {0.4, 0.4});
	SetDrawBlendModeST(MODE_ALPHA, 255 * alpha3);
	str[3].Draw(ANC_MID, data.font3);
	imgUI[3].DrawExtend({(double)str[3].data.pos.x, (double)str[3].data.pos.y+28}, {0.4, 0.4});
	//�e�L�X�g(����p)
	str[1].data.color = 0xFFFFFF;
	str[2].data.color = 0xFFFFFF;
	str[3].data.color = 0xFFFFFF;
	SetDrawBlendModeST(MODE_ALPHA, 100 * animSin1);
	str[1].Draw(ANC_MID, data.font3);
	SetDrawBlendModeST(MODE_ALPHA, 100 * animSin2);
	str[2].Draw(ANC_MID, data.font3);
	SetDrawBlendModeST(MODE_ALPHA, 100 * animSin3);
	str[3].Draw(ANC_MID, data.font3);

	//�`�惂�[�h���Z�b�g.
	ResetDrawBlendMode();
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
		mgl[2].Draw();
		mgl[3].Draw();
	}
	//Lv5�ȏ�.
	if (data.level >= 5){
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
		DrawStr str(text, {WINDOW_WID/2, WINDOW_HEI/2}, COLOR_ITEM);

		//��ʒ����ɐ�����\��.
		{
			double dec  = p_calc->GetDecimal(tmSlowMode.GetPassTime()); //�����������o��.
			double anim = p_calc->CalcNumEaseOut(dec);
			
			SetDrawBlendModeST(MODE_ALPHA, _int_r(255 * dec)); //1�b���Ƃɔ����Ȃ鉉�o.
			//�ŏ���1�b.
			if (tmSlowMode.GetPassTime() > SLOW_MODE_TIME-1) {
				imgReflect.DrawExtend({WINDOW_WID/2, WINDOW_HEI/2}, {0.3+0.2*anim, 0.3+0.2*anim});
			}
			//�Ō��3�b.
			if (tmSlowMode.GetPassTime() <= 3) {
				str.Draw(ANC_MID, data.font4); //����.
			}
			ResetDrawBlendMode();
		}
	}
}

//�Q�[���I��.
void GameManager::GameEnd() {
	
	//�܂��I����ĂȂ��Ȃ�(�O�̂���2�d���s����邱�Ƃ�h��)
	if (data.scene != SCENE_END) {

		data.scene = SCENE_END; //�Q�[���I����.
	
		tmScene[SCENE_GAME].Stop(); //��~.
		tmScene[SCENE_END].Start(); //�J�n.
		data.isSlow = false;
		tmSlowMode.Reset();

		//�L�^���Z�b�g.
		for (int i = 0; i < _countof(isItemCountDownSound); i++) {
			isItemCountDownSound[i] = false;
		}

		data.scoreBef = data.score;                                  //���ԉ��Z�O�̃X�R�A���L�^.
		data.score += (int)(tmScene[SCENE_GAME].GetPassTime() * 10); //���ԃ{�[�i�X���Z.

		//�ō��X�R�A�X�V�Ȃ�ۑ�.
		if (data.score > data.bestScore) {

			File file;
			file.MakeDir(FILE_DATA_PATH);  //�t�H���_�쐬.
			file.Open(FILE_DATA, _T("w")); //�t�@�C�����J��.
			file.WriteInt(data.score);     //�X�R�A��ۑ�.
		}

		//�T�E���h.
		switch (data.stage) 
		{
			case 1:
				p_sound->FadeOutPlay(_T("BGM1"), 2);
				break;
			case 2:
				p_sound->FadeOutPlay(_T("BGM2"), 2);
				break;

			default: assert(false); break;
		}
	}
}
//�A�C�e�����������.
void GameManager::TakeItem() {

	data.isSlow = true;             //�X���[���[�h�ɂ���.
	data.score += SCORE_TAKE_ITEM;  //�X�R�A���Z.
	tmSlowMode.Start();             //�X���[���[�h�v���J�n.

	//�L�^���Z�b�g.
	for (int i = 0; i < _countof(isItemCountDownSound); i++) {
		isItemCountDownSound[i] = false;
	}
}