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
	p_sound->LoadFile(_T("Resources/Sounds/bgm/Scarlet Radiance.mp3"),   _T("BGM1"));
	p_sound->LoadFile(_T("Resources/Sounds/bgm/audiostock_1603723.mp3"), _T("BGM2"));		//���g�p(BGM���)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_63721.mp3"),    _T("PowerDown"));	//�A�C�e������.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_104974.mp3"),   _T("Break"));		//覐Δj��.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_461339.mp3"),   _T("TakeItem"));
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_1296254.mp3"),  _T("Laser1"));		//���[�U�[(����)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_1296256.mp3"),  _T("Laser2"));		//���[�U�[(������)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_218404.mp3"),   _T("Laser3"));		//���[�U�[(����)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_936158.mp3"),   _T("Ripples"));	//�g��.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_981051.mp3"),   _T("PlayerDeath"));
	p_sound->LoadFile(_T("Resources/Sounds/se/����{�^��������23.mp3"),  _T("LevelUp"));
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_184924.mp3"),   _T("BestScore"));  //�ō��X�R�A�X�V.
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
		FILE* fp = fopen(FILE_DATA_PATH, "r");
		assert(fp != NULL); //�ǂݍ��݃G���[.

		char str[256];              //������i�[�p.
		fgets(str, 256, fp);        //�t�@�C�����當���ǂݍ���.
		data.bestScore = atoi(str); //int�^�ɕϊ����ēo�^.

		fclose(fp);
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
	data.level = 1; //�ŏ���Lv1
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
		player.Reset({ WINDOW_WID/2, WINDOW_HEI/2+200 }, TRUE);
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
			//�ŏI���x��.
			break;

		default: assert(FALSE); break;
	}

	//�X���[���[�h.
	if (tmSlowMode.GetIsMove()) {
		//���Ԑ؂�ŉ���.
		if (tmSlowMode.GetPassTime() == 0) {
			
			player.SetReflectionMode(FALSE); //���˃��[�h�I��.
			p_sound->Play(_T("PowerDown"), FALSE, 78); //�T�E���h.
			
			//���Z�b�g.
			tmSlowMode.Reset();
			data.isSlow = FALSE;
		}
	}

	UpdateObjects();    //�I�u�W�F�N�g.
	player.Update();    //�v���C���[.
	effectMng.Update(); //�G�t�F�N�g.
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
	const float delay2 = 1.4f;
	const float delay3 = 3;
	const float delay4 = 3;

	//�摜�̕\��.
	{	
		//�؂�ւ��O.
		if (tmScene[SCENE_TITLE].GetPassTime() < delay1) {
			//�A�j���[�V�����l.
			double anim = CalcNumEaseInOut(tmScene[SCENE_TITLE].GetPassTime()/delay1);
			//�摜�ݒ�.
			DrawImgExtend draw;
			draw.img  = data.imgLogo[0];
			draw.pos  = {WINDOW_WID/2, WINDOW_HEI/2 - 50};
			draw.size = {data.imgLogo[0].size.x/2, data.imgLogo[0].size.y/2};
			//���S1����.
			SetDrawBlendModeST(MODE_ADD, 255 * anim);
			DrawExtendGraphST(&draw, TRUE);
		}
		//�؂�ւ���.
		else {
			//�A�j���[�V�����l.
			double anim = CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay1)/1.8);
			//�摜�ݒ�.
			DrawImgExtend img1; 
			img1.img  = data.imgLogo[0];
			img1.pos  = {WINDOW_WID/2, _int(WINDOW_HEI/2 - 50 - anim*100)};
			img1.size = data.imgLogo[0].size/2;
			DrawImgExtend img2;
			img2.img  = data.imgLogo[1];
			img2.pos  = {WINDOW_WID/2, _int(WINDOW_HEI/2 - 50 - anim*100)};
			img2.size = data.imgLogo[1].size/2;
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

	//best score.
	if (tmScene[SCENE_TITLE].GetPassTime() > delay2) {

		//�A�j���[�V�����l.
		double anim = CalcNumEaseInOut(tmScene[SCENE_TITLE].GetPassTime()-delay2);
		//�e�L�X�g.
		DrawStr str = { {}, {WINDOW_WID/2, WINDOW_HEI/2+100}, COLOR_BEST_SCORE };
		swprintf(str.text, _T("BEST SCORE: %d"), data.bestScore); //�x�X�g�X�R�A.

		SetDrawBlendModeST(MODE_ADD, 255*anim);
		DrawStringST(&str, TRUE, data.font2);
		ResetDrawBlendMode();
	}
	//PUSH SPACE.
	if (tmScene[SCENE_TITLE].GetPassTime() > delay3) {
		//�A�j���[�V�����l.
		double anim = CalcNumWaveLoop(tmScene[SCENE_TITLE].GetPassTime()-delay3);
		//�e�L�X�g.
		DrawStr str = { _T("Push SPACE or  X"), {WINDOW_WID/2-5, WINDOW_HEI/2+300}, 0xFFFFFF };
		Circle cir = { {WINDOW_WID/2+92, WINDOW_HEI/2+297}, 18, 0xFFFFFF };
		
		SetDrawBlendModeST(MODE_ADD, 255*anim);
		DrawStringST(&str, TRUE, data.font1); //�e�L�X�g.
		DrawCircleST(&cir, FALSE);            //X�{�^���̉~.
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

				double newDig = dig + (float)RandNum(-400, 400)/10; //�����p�x�����炷.

				EffectData data{}; 
				data.type  = Effect_BreakMeteo;
				data.pos   = { 600, 350 };
				data.vec   = CalcDigToPos(newDig);              //���炵���p�x�𔽉f.
				data.speed = ((float)RandNum(5, 40)  /10)*1.4f; //���x���I.
				data.len   = ((float)RandNum(30, 180)/10)*1.4f; //�������I.
				data.ang   =  (float)RandNum(0, 3599)/10;       //�p�x���I.
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

		//�e�L�X�g�̐ݒ�.
		DrawStr str1 = { _T("- GAME OVER -"), {WINDOW_WID/2, _int(370+30*anim)}, 0xA0A0A0 };
		DrawStr str2 = { _T("Time Bonus"),    {WINDOW_WID/2, WINDOW_HEI/2-20}, 0xFFFFFF };
		DrawStr str3 = { {},                  {WINDOW_WID/2, WINDOW_HEI/2+20}, 0xFFFFFF };
		//�X�R�A�\��.
		swprintf(
			str3.text, 
			_T("%d + %d(%.3f�b) = %d�_"),
			data.scoreBef, (int)(tmScene[SCENE_GAME].GetPassTime() * 10), tmScene[SCENE_GAME].GetPassTime(), data.score
		);
		//��ʒ����ɕ�����\��.
		SetDrawBlendModeST(MODE_ADD, 255*anim);
		DrawStringST(&str1, TRUE, data.font3);
		DrawStringST(&str2, TRUE, data.font1);
		DrawStringST(&str3, TRUE, data.font1);
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
			DrawStr str = { _T("NEW RECORD!"), {WINDOW_WID/2, _int(WINDOW_HEI/2-380+anim*20)}, 0xEFFFA0 };
			//�`��.
			SetDrawBlendModeST(MODE_ADD, 255*anim);
			DrawStringST(&str, TRUE, data.font2);
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
		DrawStr str = { _T("Push SPACE or  A"), {WINDOW_WID/2-5, WINDOW_HEI/2+145}, 0xFFFFFF };
		Circle cir = { {WINDOW_WID/2+92, WINDOW_HEI/2+143}, 18, 0xFFFFFF };
		
		SetDrawBlendModeST(MODE_ADD, 255*anim);
		DrawStringST(&str, TRUE, data.font1); //�e�L�X�g.
		DrawCircleST(&cir, FALSE);            //A�{�^���̉~.
		ResetDrawBlendMode();
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
			DrawBoxST(&box, TRUE, FALSE);
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
		double alpha1   = CalcNumEaseInOut(tmScene[SCENE_READY].GetPassTime());
		double alpha2   = CalcNumEaseInOut(tmScene[SCENE_READY].GetPassTime()-0.1);
		double alpha3   = CalcNumEaseInOut(tmScene[SCENE_READY].GetPassTime()-0.2);
		double animSin1 = sin(M_PI* tmScene[SCENE_READY].GetPassTime());
		double animSin2 = sin(M_PI*(tmScene[SCENE_READY].GetPassTime()-0.1));
		double animSin3 = sin(M_PI*(tmScene[SCENE_READY].GetPassTime()-0.2));

		//�e�L�X�g�ݒ�.
#if false
		STR_DRAW str1 = { {}, {WINDOW_WID/2, 0+100}, COLOR_BEST_SCORE };
		STR_DRAW str2 = { {}, {WINDOW_WID/2, 0+150}, COLOR_SCORE };
		STR_DRAW str3 = { {}, {WINDOW_WID/2, 0+200}, COLOR_TIME };
#else
		DrawStr str1 = { {}, {WINDOW_WID/2-380, 100}, COLOR_BEST_SCORE };
		DrawStr str2 = { {}, {WINDOW_WID/2,     100}, COLOR_SCORE };
		DrawStr str3 = { {}, {WINDOW_WID/2+380, 100}, COLOR_TIME };
#endif
		swprintf(str1.text, _T("BEST SCORE:%05d"), data.bestScore);
		swprintf(str2.text, _T("SCORE:%05d"),      data.score);
		swprintf(str3.text, _T("TIME:%.3f"),       tmScene[SCENE_GAME].GetPassTime());
		//�e�L�X�g(main)
		SetDrawBlendModeST(MODE_ALPHA, 255 * alpha1);
		DrawStringST(&str1, TRUE, data.font3);
		SetDrawBlendModeST(MODE_ALPHA, 255 * alpha2);
		DrawStringST(&str2, TRUE, data.font3);
		SetDrawBlendModeST(MODE_ALPHA, 255 * alpha3);
		DrawStringST(&str3, TRUE, data.font3);
		//�e�L�X�g(����p)
		str1.color = 0xFFFFFF;
		str2.color = 0xFFFFFF;
		str3.color = 0xFFFFFF;
		SetDrawBlendModeST(MODE_ALPHA, 100 * animSin1);
		DrawStringST(&str1, TRUE, data.font3);
		SetDrawBlendModeST(MODE_ALPHA, 100 * animSin2);
		DrawStringST(&str2, TRUE, data.font3);
		SetDrawBlendModeST(MODE_ALPHA, 100 * animSin3);
		DrawStringST(&str3, TRUE, data.font3);
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
		DrawStr str1 = { _T("Reflect"), {WINDOW_WID/2, WINDOW_HEI/2}, COLOR_ITEM };
		DrawStr str2 = { {},            {WINDOW_WID/2, WINDOW_HEI/2}, COLOR_ITEM };
		swprintf(str2.text, _T("%d"), (int)ceil(tmSlowMode.GetPassTime())); //TCHAR�^�ɕϐ�����.

		//��ʒ����ɐ�����\��.
		{
			double dec = GetDecimal(tmSlowMode.GetPassTime()); //�����������o��.
			SetDrawBlendModeST(MODE_ADD, _int(255 * dec));     //1�b���Ƃɔ����Ȃ鉉�o.
			//�e�L�X�g�؂�ւ�.
			if (tmSlowMode.GetPassTime() > SLOW_MODE_TIME-1) {
				DrawStringST(&str1, TRUE, data.font3); //���˃��[�h.
			}
			else {
				DrawStringST(&str2, TRUE, data.font3); //����.
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

	data.scoreBef = data.score;                                  //���ԉ��Z�O�̃X�R�A���L�^.
	data.score += (int)(tmScene[SCENE_GAME].GetPassTime() * 10); //���ԃ{�[�i�X���Z.

	//�ō��X�R�A�X�V�Ȃ�ۑ�.
	if (data.score > data.bestScore) {

		FILE* fp = fopen(FILE_DATA_PATH, "w");
		assert(fp != NULL); //�ǂݍ��݃G���[.

		char str[256];
		_itoa(data.score, str, 10); //score��char�^�ɕϊ�(10�i��)
		fputs(str, fp);             //�t�@�C���ɕ�����������.

		fclose(fp);
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