/*
   - Stage_Tutorial.cpp -
   
   �X�e�[�W: �`���[�g���A��.
*/
#include "LaserManager.h"
#include "Obst_NormalLaser.h"
#include "Obst_StraightLaser.h"
#include "Obst_MeteorManager.h"
#include "Obst_Ripples.h"
#include "Obst_Fireworks.h"
#include "Item.h"
#include "EffectManager.h"
#include "GameManager.h"

#include "Stage_Tutorial.h"

//������.
void TutorialStage::Init() {
	//���̎擾.
	p_data         = GameData::GetPtr();
	p_gameMng      = GameManager::GetPtr();
	p_laserMng     = LaserManager::GetPtr();
	p_meteorMng    = MeteorManager::GetPtr();
	p_ripples      = Ripples::GetPtr();
	p_itemMng      = ItemManager::GetPtr();
	p_player       = Player::GetPtr();
	p_fireworksMng = FireworksManager::GetPtr();
	p_effectMng    = EffectManager::GetPtr();
	p_input        = InputMng::GetPtr();
	p_sound        = SoundMng::GetPtr();

	font[0].CreateFontH(_T(""), 20, 1, FONT_ANTI);
	font[1].CreateFontH(_T(""), 26, 1, FONT_ANTI);

	//�^�C�}�[
	startTimer = Timer(COUNT_UP, 0);
	endTimer   = Timer(COUNT_UP, 0);
}
//���Z�b�g.
void TutorialStage::Reset() {
	startTimer.Reset();
	endTimer.Reset();
	stepNo   = 0; //�ォ��step1�ɂ���.
	stepInNo = 0;
}
//�X�V.
void TutorialStage::Update() {

	//�X�e�b�v��.
	switch (stepNo)
	{
		case 0: UpdateStep0(); break;
		case 1: UpdateStep1(); break;
		case 2: UpdateStep2(); break;
		case 3: UpdateStep3(); break;
		case 4: UpdateStep4(); break;

		default: assert(FALSE); break;
	}
}
//�`��.
void TutorialStage::Draw() {

	//�X�e�b�v��.
	switch (stepNo)
	{
		case 0:              break; //�`��Ȃ�.
		case 1: DrawStep1(); break;
		case 2: DrawStep2(); break;
		case 3: DrawStep3(); break;
		case 4: DrawStep4(); break;

		default: assert(FALSE); break;
	}
}

//�X�V:step0
void TutorialStage::UpdateStep0() {

	//�T�E���h.
	p_sound->Play(_T("LevelUp"), false, 100);
	//�G�t�F�N�g.
	EffectData data{};
	data.type = Effect_Tutorial_Step1;
	data.pos = { WINDOW_WID/2, WINDOW_HEI/2 };
	p_effectMng->SpawnEffect(&data);

	startTimer.Start(); //�J�n.
	stepNo++;           //���̃X�e�b�v.
	stepInNo = 0;
}
//�X�V:step1
void TutorialStage::UpdateStep1() {

	//�X�e�b�v������.
	switch (stepInNo) 
	{
		case 0:
		{
			plyMoveSum += p_player->GetMoveDist(); //�v���C���[�ړ��������v��.

			//��苗���ړ�������.
			if (!endTimer.GetIsMove() && plyMoveSum >= 2000) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				startTimer.Reset(); //���Z�b�g.
				endTimer.Reset();   //���Z�b�g.
				startTimer.Start(); //�J�n.
				stepInNo++;
			}
		}
		break;

		case 1:
		{
			//�ŏ��̈�莞�Ԃ͒�~.
			if (startTimer.GetPassTime() < TUTORIAL_START_WAIT_TIME) { break; }

			p_gameMng->laserNor1->Update();
			p_laserMng->Update();

			//��莞�Ԍo�߂�����.
			if (!endTimer.GetIsMove() && startTimer.GetPassTime() >= 8.0) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//�T�E���h.
				p_sound->Play(_T("LevelUp"), false, 100);
				//�G�t�F�N�g.
				EffectData data{};
				data.type = Effect_Tutorial_Step2;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				p_effectMng->SpawnEffect(&data);

				//�I�u�W�F�N�g���Z�b�g.
				p_gameMng->ResetNorLaser();
				p_laserMng->Reset();

				startTimer.Reset(); //���Z�b�g.
				endTimer.Reset();   //���Z�b�g.
				startTimer.Start(); //�J�n.
				stepNo++;           //���̃X�e�b�v.
				stepInNo = 0;
			}
		}
		break;
	}
}
//�X�V:step2
void TutorialStage::UpdateStep2() {

	//�X�e�b�v������.
	switch (stepInNo) 
	{
		case 0:
		{
			//�ŏ��̈�莞�Ԃ͒�~.
			if (startTimer.GetPassTime() < TUTORIAL_START_WAIT_TIME) { break; }

			//��莞�Ԍo�߂�����.
			if (!endTimer.GetIsMove() && startTimer.GetPassTime() >= 1.0) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				startTimer.Reset(); //���Z�b�g.
				endTimer.Reset();   //���Z�b�g.
				startTimer.Start(); //�J�n.
				stepInNo++;
			}
		}
		break;

		case 1:
		{
			//�ŏ��̈�莞�Ԃ͒�~.
			if (startTimer.GetPassTime() < TUTORIAL_START_WAIT_TIME) { break; }

			//��莞�Ԍo�߂�����.
			if (!endTimer.GetIsMove() && startTimer.GetPassTime() >= 1.0) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//�T�E���h.
				p_sound->Play(_T("LevelUp"), false, 100);
				//�G�t�F�N�g.
				EffectData data{};
				data.type = Effect_Tutorial_Step3;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				p_effectMng->SpawnEffect(&data);

				startTimer.Reset(); //���Z�b�g.
				endTimer.Reset();   //���Z�b�g.
				startTimer.Start(); //�J�n.
				stepNo++;           //���̃X�e�b�v.
				stepInNo = 0;
			}
		}
		break;
	}
}
//�X�V:step3
void TutorialStage::UpdateStep3() {

	//�X�e�b�v������.
	switch (stepInNo) 
	{
		case 0:
		{
			//�ŏ��̈�莞�Ԃ͒�~.
			if (startTimer.GetPassTime() < TUTORIAL_START_WAIT_TIME) { break; }

			//��莞�Ԍo�߂�����.
			if (!endTimer.GetIsMove() && startTimer.GetPassTime() >= 1.0) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				startTimer.Reset(); //���Z�b�g.
				endTimer.Reset();   //���Z�b�g.
				startTimer.Start(); //�J�n.
				stepInNo++;
			}
		}
		break;

		case 1:
		{
			//�ŏ��̈�莞�Ԃ͒�~.
			if (startTimer.GetPassTime() < TUTORIAL_START_WAIT_TIME) { break; }

			//��莞�Ԍo�߂�����.
			if (!endTimer.GetIsMove() && startTimer.GetPassTime() >= 1.0) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//�T�E���h.
				p_sound->Play(_T("LevelUp"), false, 100);
				//�G�t�F�N�g.
				EffectData data{};
				data.type = Effect_Tutorial_Step3;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				p_effectMng->SpawnEffect(&data);

				startTimer.Reset(); //���Z�b�g.
				endTimer.Reset();   //���Z�b�g.
				startTimer.Start(); //�J�n.
				stepNo++;           //���̃X�e�b�v.
				stepInNo = 0;
			}
		}
		break;
	}
}
//�X�V:step4
void TutorialStage::UpdateStep4() {

	//�X�e�b�v������.
	switch (stepInNo) 
	{
		case 0:
		{
			//�ŏ��̈�莞�Ԃ͒�~.
			if (startTimer.GetPassTime() < TUTORIAL_START_WAIT_TIME) { break; }

			//��莞�Ԍo�߂�����.
			if (!endTimer.GetIsMove() && startTimer.GetPassTime() >= 1.0) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				startTimer.Reset(); //���Z�b�g.
				endTimer.Reset();   //���Z�b�g.
				startTimer.Start(); //�J�n.
				stepInNo++;
			}
		}
		break;

		case 1:
		{
			//�ŏ��̈�莞�Ԃ͒�~.
			if (startTimer.GetPassTime() < TUTORIAL_START_WAIT_TIME) { break; }

			//��莞�Ԍo�߂�����.
			if (!endTimer.GetIsMove() && startTimer.GetPassTime() >= 1.0) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//�`���[�g���A���I��.
				p_data->scene = SCENE_TITLE;
				GameManager::GetPtr()->Reset(); //�S�ă��Z�b�g.
			}
		}
		break;
	}
}

//�`��:step1
void TutorialStage::DrawStep1() {

	//�J�n�^�C�}�[�ƏI���^�C�}�[�̑g�ݍ��킹�œ��߃A�j���[�V���������.
	double alpha1 = Calc::CalcNumEaseIn (startTimer.GetPassTime());
	double alpha2 = Calc::CalcNumEaseOut(endTimer.GetPassTime());
	double alpha  = alpha1 * (1 - alpha2); //�����ɍ쓮���Ă��q����悤��.

    //�X�e�b�v������.
    switch (stepInNo) 
    {
        case 0:
        {
            DrawTopText1(_T("�v���C���[���ړ�������"), alpha);
            DrawTopText2(_T("�L�[�{�[�h����: WASD/��������"), alpha);
            DrawTopText3(_T("�R���g���[���[����: ���X�e�B�b�N"), alpha);
        }
        break;

        case 1:
        {
            DrawTopText1(_T("�U����������"), alpha);
            DrawTopText2(_T("�����͓̂G�ł��B������Ƒ������܂��B"), alpha);
            DrawTopText3(_T("�D�F: �\���@�F: �U��"), alpha);

            p_gameMng->laserNor1->Draw();
            p_laserMng->Draw();
        }
        break;
    }
}
//�`��:step2
void TutorialStage::DrawStep2() {

	//�J�n�^�C�}�[�ƏI���^�C�}�[�̑g�ݍ��킹�œ��߃A�j���[�V���������.
	double alpha1 = Calc::CalcNumEaseIn(startTimer.GetPassTime());
	double alpha2 = Calc::CalcNumEaseOut(endTimer.GetPassTime());
	double alpha  = alpha1 * (1 - alpha2); //�����ɍ쓮���Ă��q����悤��.

    //�X�e�b�v������.
    switch (stepInNo) 
    {
        case 0:
        {
            DrawTopText1(_T("�A�C�e�����Ƃ�"), alpha);
            DrawTopText2(_T("�A�C�e���͉�ʏォ��~���Ă��܂��B�G���Ǝ��܂��B"), alpha);
        }
        break;

        case 1:
        {
            DrawTopText1(_T("�A�C�e������"), alpha);
            DrawTopText2(_T("�G���Ǝ����Ō��ʂ��������A��莞�Ԍo�Ɖ�������܂�"), alpha);
        }
        break;
    }
}
//�`��:step3
void TutorialStage::DrawStep3() {

	//�J�n�^�C�}�[�ƏI���^�C�}�[�̑g�ݍ��킹�œ��߃A�j���[�V���������.
	double alpha1 = Calc::CalcNumEaseIn(startTimer.GetPassTime());
	double alpha2 = Calc::CalcNumEaseOut(endTimer.GetPassTime());
	double alpha  = alpha1 * (1 - alpha2); //�����ɍ쓮���Ă��q����悤��.

    //�X�e�b�v������.
    switch (stepInNo) 
    {
        case 0:
        {
            DrawTopText1(_T("���˃��[�h"), alpha);
            DrawTopText2(_T("�A�C�e�������ƁA���˃��[�h�ɂȂ�܂�"), alpha);
        }
        break;

        case 1:
        {
            DrawTopText1(_T("���[�U�[�𒵂˕Ԃ�"), alpha);
            DrawTopText2(_T("���˃��[�h���́A���[�U�[�ɓ�����ƒ��˕Ԃ��܂�"), alpha);
        }
        break;

        case 2:
        {
            DrawTopText1(_T("覐΂����킷"), alpha);
            DrawTopText2(_T("���˕Ԃ������[�U�[�́A覐΂Ɍ������Ĕ��ł����܂�"), alpha);
        }
        break;
    }
}
//�`��:step4
void TutorialStage::DrawStep4() {

	//�J�n�^�C�}�[�ƏI���^�C�}�[�̑g�ݍ��킹�œ��߃A�j���[�V���������.
	double alpha1 = Calc::CalcNumEaseIn(startTimer.GetPassTime());
	double alpha2 = Calc::CalcNumEaseOut(endTimer.GetPassTime());
	double alpha  = alpha1 * (1 - alpha2); //�����ɍ쓮���Ă��q����悤��.

    //�X�e�b�v������.
    switch (stepInNo) 
    {
        case 0:
        {
            DrawTopText1(_T("�X�R�A�𑝂₷"), alpha);
            DrawTopText2(_T("�A�C�e�����Ƃ��+100 / 覐΂����킷��+500 �����܂�"), alpha);
        }
        break;

        case 1:
        {
            DrawTopText1(_T("��ʂ�v���C"), alpha);
            DrawTopText2(_T("�����遨�Ƃ遨���킷 ���J��Ԃ��X�R�A�𑝂₷�B���ꂪ��ȗ���ł��B"), alpha);
            DrawTopText3(_T("�Ō��5000�_�҂��ł݂܂��傤�B"), alpha);
        }
        break;
    }
} 


//��ʏ�Ƀe�L�X�g���o��.
//alpha��0.0�`1.0
void TutorialStage::DrawTopText1(MY_STRING text, double alpha) {

	DrawStr str(text, {WINDOW_WID/2, 150}, 0xFFFFFF);
	const int useFont = font[1].GetFont();

	{
		const int margin = 24;
		DBL_XY pos  = (str.pos - str.GetTextSize(useFont)/2).Add(-margin/2, -margin/2).ToDblXY();
		DBL_XY size = (str.GetTextSize(useFont) + margin).ToDblXY();
		Box box = {pos, size, 0x000000};

		//�g�w�i.
		SetDrawBlendModeKR(MODE_ALPHA, 100*alpha);
		DrawBoxKR(&box, ANC_LU);
		//�e�L�X�g.
		SetDrawBlendModeKR(MODE_ALPHA, 255*alpha);
		str.Draw(ANC_MID, useFont);
		ResetDrawBlendMode();

		//�g���O���f�[�V����.
		GradLine line;
		line.AddPoint(pos,                     {  0, 255, 255, _int_r(255*alpha)});
		line.AddPoint(pos.Add(size.x,      0), {  0,   0,   0, _int_r(255*alpha)});
		line.AddPoint(pos.Add(size.x, size.y), {255,   0, 255, _int_r(255*alpha)});
		line.AddPoint(pos.Add(     0, size.y), {  0,   0,   0, _int_r(255*alpha)});
		line.Draw(true);
	}
}
//��ʏ�Ƀe�L�X�g���o��(2�s��)
//alpha��0.0�`1.0
void TutorialStage::DrawTopText2(MY_STRING text, double alpha) {

	DrawStr str(text, {WINDOW_WID/2, 150+60}, 0xFFFFFF);
	const int useFont = font[0].GetFont();

	{
		const int margin = 24;
		DBL_XY pos  = (str.pos - str.GetTextSize(useFont)/2).Add(-margin/2, -margin/2).ToDblXY();
		DBL_XY size = (str.GetTextSize(useFont) + margin).ToDblXY();
		Box box = {pos, size, 0x000000};

		//�g�w�i.
		SetDrawBlendModeKR(MODE_ALPHA, 100*alpha);
		DrawBoxKR(&box, ANC_LU);
		//�e�L�X�g.
		SetDrawBlendModeKR(MODE_ALPHA, 255*alpha);
		str.Draw(ANC_MID, useFont);
		ResetDrawBlendMode();

		//�g���O���f�[�V����.
		GradLine line;
		line.AddPoint(pos,                     {  0, 255, 255, _int_r(255*alpha)});
		line.AddPoint(pos.Add(size.x,      0), {  0,   0,   0, _int_r(255*alpha)});
		line.AddPoint(pos.Add(size.x, size.y), {255,   0, 255, _int_r(255*alpha)});
		line.AddPoint(pos.Add(     0, size.y), {  0,   0,   0, _int_r(255*alpha)});
		line.Draw(true);
	}
}
//��ʏ�Ƀe�L�X�g���o��(3�s��)
//alpha��0.0�`1.0
void TutorialStage::DrawTopText3(MY_STRING text, double alpha) {

	DrawStr str(text, {WINDOW_WID/2, 150+60+50}, 0xFFFFFF);
	const int useFont = font[0].GetFont();

	{
		const int margin = 24;
		DBL_XY pos  = (str.pos - str.GetTextSize(useFont)/2).Add(-margin/2, -margin/2).ToDblXY();
		DBL_XY size = (str.GetTextSize(useFont) + margin).ToDblXY();
		Box box = {pos, size, 0x000000};

		//�g�w�i.
		SetDrawBlendModeKR(MODE_ALPHA, 100*alpha);
		DrawBoxKR(&box, ANC_LU);
		//�e�L�X�g.
		SetDrawBlendModeKR(MODE_ALPHA, 255*alpha);
		str.Draw(ANC_MID, useFont);
		ResetDrawBlendMode();

		//�g���O���f�[�V����.
		GradLine line;
		line.AddPoint(pos,                     {  0, 255, 255, _int_r(255*alpha)});
		line.AddPoint(pos.Add(size.x,      0), {  0,   0,   0, _int_r(255*alpha)});
		line.AddPoint(pos.Add(size.x, size.y), {255,   0, 255, _int_r(255*alpha)});
		line.AddPoint(pos.Add(     0, size.y), {  0,   0,   0, _int_r(255*alpha)});
		line.Draw(true);
	}
}