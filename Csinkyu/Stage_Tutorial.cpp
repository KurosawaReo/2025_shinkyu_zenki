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
#include "UIManager.h"
#include "GameManager.h"

#include "Stage_Tutorial.h"

//������.
void TutorialStage::Init() {
	//���̎擾.
	p_data         = &GameData::GetInst();
	p_gameMng      = &GameManager::GetInst();
	p_laserMng     = &LaserManager::GetInst();
	p_meteorMng    = &MeteorManager::GetInst();
	p_ripples      = &Ripples::GetInst();
	p_itemMng      = &ItemManager::GetInst();
	p_player       = &Player::GetInst();
	p_fireworksMng = &FireworksManager::GetInst();
	p_effectMng    = &EffectManager::GetInst();
	p_uiMng        = &UIManager::GetInst();
	p_input        = &InputMng::GetInst();
	p_sound        = &SoundMng::GetInst();

	font[0].CreateFontH(_T(""), 25, 1, FontTypeID::Anti);
	font[1].CreateFontH(_T(""), 30, 1, FontTypeID::Anti);

	//�^�C�}�[
	startTimer = Timer(COUNT_UP, 0);
	endTimer   = Timer(COUNT_UP, 0);
}
//���Z�b�g.
void TutorialStage::Reset() {

	startTimer.Reset();
	endTimer.Reset();
	stepNo   = 0;    //�ォ��step1�ɂ���.
	stepInNo = 0;    //0�X�^�[�g.

	plyMoveSum = 0; 
	ResetSignFlag(); //sign�t���Ooff.
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

//�T�C���t���O�̃��Z�b�g.
void TutorialStage::ResetSignFlag() {
	isTakeItem      = false;
	isReflectLaser  = false;
	isReflectFinish = false;
	isBreakMeteor   = false;
}
//���ڂ��I���x�̏���.
void TutorialStage::StepInEnd() {

	startTimer.Reset(); //���Z�b�g.
	endTimer.Reset();   //���Z�b�g.
	startTimer.Start(); //�J�n.

	ResetSignFlag(); //sign�t���Ooff.
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

			//[�I������] ��苗���ړ�������.
			if (!endTimer.GetIsMove() && plyMoveSum >= 1500) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				StepInEnd(); //�I������.
				stepInNo++;
			}
		}
		break;

		case 1:
		{
			//�ŏ��̈�莞�Ԃ͒�~.
			if (startTimer.GetPassTime() < TUTORIAL_START_WAIT_TIME) { break; }

			p_laserMng->Update();
			p_gameMng->laserNor1->Update();

			//[�I������] ��莞�Ԍo�߂�����.
			if (!endTimer.GetIsMove() && startTimer.GetPassTime() >= 9.0) {
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
				p_laserMng->Reset();
				p_gameMng->ResetNorLaser();
				//�A�C�e������.
				p_itemMng->ItemSpawn(0);

				StepInEnd();  //�I������.
				stepNo++;     //���̃X�e�b�v.
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

			p_itemMng->Update();

			//[�I������] �A�C�e�����������.
			if (!endTimer.GetIsMove() && isTakeItem) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				StepInEnd(); //�I������.
				stepInNo++;
			}
		}
		break;

		case 1:
		{
			//�ŏ��̈�莞�Ԃ͒�~.
			if (startTimer.GetPassTime() < TUTORIAL_START_WAIT_TIME) { break; }

			p_itemMng->Update();

			//[�I������] ���˃��[�h���I�������.
			if (!endTimer.GetIsMove() && isReflectFinish) {
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

				//�A�C�e������.
				p_itemMng->ItemSpawn(0);

				StepInEnd();  //�I������.
				stepNo++;     //���̃X�e�b�v.
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

			p_itemMng->Update();

			//[�I������] �A�C�e�����������.
			if (!endTimer.GetIsMove() && isTakeItem) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				StepInEnd(); //�I������.
				stepInNo++;
			}
		}
		break;

		case 1:
		{
			//�ŏ��̈�莞�Ԃ͒�~.
			if (startTimer.GetPassTime() < TUTORIAL_START_WAIT_TIME) { break; }

			p_itemMng->Update();
			p_laserMng->Update();
			p_gameMng->laserNor1->Update();

			//[�I������] ���[�U�[�𔽎˂��� && ���˃��[�h���I�������.
			if (!endTimer.GetIsMove() && isReflectLaser && isReflectFinish) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//�����\��.
				p_meteorMng->SetIsSpawnAble(true);

				StepInEnd(); //�I������.
				stepInNo++;
			}
		}
		break;

		case 2:
		{
			p_itemMng->Update();
			p_laserMng->Update();
			p_meteorMng->Update();
			p_gameMng->laserNor1->Update();

			//[�I������] 覐΂��󂵂� & ���˃��[�h���I�������.
			if (!endTimer.GetIsMove() && isBreakMeteor && isReflectFinish) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				StepInEnd(); //�I������.
				stepInNo++;
			}
		}
		break;

		case 3:
		{
			p_itemMng->Update();
			p_laserMng->Update();
			p_meteorMng->Update();
			p_gameMng->laserNor1->Update();

			//[�I������] ��莞�Ԃ��o�߂�����.
			if (!endTimer.GetIsMove() && startTimer.GetPassTime() >= 6.0) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//�T�E���h.
				p_sound->Play(_T("LevelUp"), false, 100);
				//�G�t�F�N�g.
				EffectData data{};
				data.type = Effect_Tutorial_Step4;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				p_effectMng->SpawnEffect(&data);

				//�X�R�A���Z�b�g.
				p_data->scoreBef = p_data->score = 0;
				//�X�R�A�\��.
				p_uiMng->SignIsShowScore();
				//�����\��.
				p_itemMng->SetIsSpawnAble(true);

				StepInEnd();  //�I������.
				stepNo++;     //���̃X�e�b�v.
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
			p_itemMng->Update();
			p_laserMng->Update();
			p_meteorMng->Update();
			p_gameMng->laserNor1->Update();

			//[�I������] ���X�R�A���z���� & ���˃��[�h���I�������.
			if (!endTimer.GetIsMove() && p_data->score >= 2000 && isReflectFinish) {
				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//�I�u�W�F�N�g���Z�b�g.
				p_itemMng->Reset();
				p_laserMng->Reset();
				p_meteorMng->Reset();
				p_gameMng->ResetNorLaser();

				StepInEnd(); //�I������.
				stepInNo++;
			}
		}
		break;

		case 1:
		{
			//[�I������] ��莞�Ԃ��o�߂�����
			if (!endTimer.GetIsMove() && startTimer.GetPassTime() >= 5.0) {
				//BGM�t�F�[�h�A�E�g.
				p_sound->FadeOutPlay(_T("BGM_Tutorial"), TUTORIAL_END_NEXT_TIME);

				endTimer.Start();
			}
			if (endTimer.GetPassTime() >= TUTORIAL_END_NEXT_TIME) {
				//�`���[�g���A���I��.
				p_data->scene = SCENE_TITLE;
				p_gameMng->Reset(); //�S�ă��Z�b�g.
			}
		}
		break;
	}
}

//�`��:step1
void TutorialStage::DrawStep1() {

	//�J�n�^�C�}�[�ƏI���^�C�}�[�̑g�ݍ��킹�œ��߃A�j���[�V���������.
	double alpha1 = Calc::CalcNumEaseIn ((startTimer.GetPassTime()-0.5)*2);
	double alpha2 = Calc::CalcNumEaseOut(endTimer.GetPassTime()*2);
	double alpha  = alpha1 * (1-alpha2); //�����ɍ쓮���Ă��q����悤��.

    //�X�e�b�v������.
    switch (stepInNo) 
    {
        case 0:
        {
            DrawTopText1(_T("�v���C���[���ړ�������"), alpha);
            DrawTopText2(_T("�L�[�{�[�h����: WASD / ��������"), alpha);
            DrawTopText3(_T("�R���g���[���[����: ���X�e�B�b�N"), alpha);
        }
        break;

        case 1:
        {
            DrawTopText1(_T("�U�����悯��"), alpha);
            DrawTopText2(_T("�����͓̂G�ł��B������Ƒ������܂��B"), alpha);
            DrawTopText3(_T("�D�F:�\�� / �F:�U��"), alpha);

            p_gameMng->laserNor1->Draw();
            p_laserMng->Draw();
        }
        break;
    }
}
//�`��:step2
void TutorialStage::DrawStep2() {

	//�J�n�^�C�}�[�ƏI���^�C�}�[�̑g�ݍ��킹�œ��߃A�j���[�V���������.
	double alpha1 = Calc::CalcNumEaseIn ((startTimer.GetPassTime()-0.5)*2);
	double alpha2 = Calc::CalcNumEaseOut(endTimer.GetPassTime()*2);
	double alpha  = alpha1 * (1-alpha2); //�����ɍ쓮���Ă��q����悤��.

    //�X�e�b�v������.
    switch (stepInNo) 
    {
        case 0:
        {
            DrawTopText1(_T("�A�C�e�����Ƃ�"), alpha);
            DrawTopText2(_T("�A�C�e���͉�ʏォ��~���Ă��܂��B�G���Ǝ��܂��B"), alpha);

			p_itemMng->Draw();
        }
        break;

        case 1:
        {
            DrawTopText1(_T("�A�C�e������"), alpha);
            DrawTopText2(_T("�G���Ǝ����Ō��ʂ��������A��莞�Ԍo�Ɖ�������܂��B"), alpha);

			p_itemMng->Draw();
        }
        break;
    }
}
//�`��:step3
void TutorialStage::DrawStep3() {

	//�J�n�^�C�}�[�ƏI���^�C�}�[�̑g�ݍ��킹�œ��߃A�j���[�V���������.
	double alpha1 = Calc::CalcNumEaseIn ((startTimer.GetPassTime()-0.5)*2);
	double alpha2 = Calc::CalcNumEaseOut(endTimer.GetPassTime()*2);
	double alpha  = alpha1 * (1-alpha2); //�����ɍ쓮���Ă��q����悤��.

    //�X�e�b�v������.
    switch (stepInNo) 
    {
        case 0:
        {
            DrawTopText1(_T("���˃��[�h"), alpha);
            DrawTopText2(_T("�A�C�e�������Ɣ��˃��[�h�ɂȂ�܂��B"), alpha);

			p_itemMng->Draw();
        }
        break;

        case 1:
        {
            DrawTopText1(_T("���[�U�[�𒵂˕Ԃ�"), alpha);
            DrawTopText2(_T("���˃��[�h���́A���[�U�[�ɓ�����ƒ��˕Ԃ��܂��B"), alpha);

			p_itemMng->Draw();
			p_laserMng->Draw();
			p_meteorMng->Draw();
			p_gameMng->laserNor1->Draw();
        }
        break;

        case 2:
        {
            DrawTopText1(_T("覐΂����킷"), alpha);
            DrawTopText2(_T("���˕Ԃ������[�U�[�́A覐΂Ɍ������Ĕ��ł����܂��B"), alpha);

			p_itemMng->Draw();
			p_laserMng->Draw();
			p_meteorMng->Draw();
			p_gameMng->laserNor1->Draw();
        }
        break;

		case 3:
		{
			DrawTopText1(_T("���˃��[�h�̒���"), alpha);
			DrawTopText2(_T("���G�ł͂Ȃ��̂ŁA���[�U�[�ȊO�ɓ�����Ǝ��ɂ܂��B"), alpha);

			p_itemMng->Draw();
			p_laserMng->Draw();
			p_meteorMng->Draw();
			p_gameMng->laserNor1->Draw();
		}
		break;
    }
}
//�`��:step4
void TutorialStage::DrawStep4() {

	//�J�n�^�C�}�[�ƏI���^�C�}�[�̑g�ݍ��킹�œ��߃A�j���[�V���������.
	double alpha1 = Calc::CalcNumEaseIn ((startTimer.GetPassTime()-0.5)*2);
	double alpha2 = Calc::CalcNumEaseOut(endTimer.GetPassTime()*2);
	double alpha  = alpha1 * (1-alpha2); //�����ɍ쓮���Ă��q����悤��.

    //�X�e�b�v������.
    switch (stepInNo) 
    {
        case 0:
        {
            DrawTopText2(_T("�X�R�A���҂��ōŌ��2000�_�҂��ł݂܂��傤�B"), alpha);
			DrawTopText3(_T("�A�C�e�������:+100, 覐΂���:+500"), alpha);

			p_itemMng->Draw();
			p_laserMng->Draw();
			p_meteorMng->Draw();
			p_gameMng->laserNor1->Draw();
        }
        break;

		case 1:
		{
			DrawTopText2(_T("����Ń`���[�g���A���͈ȏ�ł��B"), alpha);
			DrawTopText3(_T("�����Ń^�C�g���ɖ߂�܂�..."), alpha);
		}
		break;
    }
} 


//��ʏ�Ƀe�L�X�g���o��.
//alpha��0.0�`1.0
void TutorialStage::DrawTopText1(MY_STRING text, double alpha) {

	DrawStr str(text, {WINDOW_WID/2, 155}, {0, 255, 255});
	const int useFont = font[1].GetFont();

	{
		const int margin = 24;
		DBL_XY pos  = (str.pos - str.GetTextSize(useFont)/2).Add(-margin/2, -margin/2).ToDblXY();
		DBL_XY size = (str.GetTextSize(useFont) + margin).ToDblXY();
		Box    box  = {pos, size, 0x000000};

		//�g�w�i.
		SetDrawBlendModeKR(BlendModeID::Alpha, 100*alpha);
		DrawBoxKR(&box, Anchor::LU);
		//�e�L�X�g.
		SetDrawBlendModeKR(BlendModeID::Alpha, 255*alpha);
		str.Draw(Anchor::Mid, useFont);
		ResetDrawBlendMode();

		//�g���O���f�[�V����.
		GradLine line;
		line.AddPoint(pos,                     {  0, 255, 255, _int_r(255*alpha)});
		line.AddPoint(pos.Add(size.x,      0), {  0, 100, 255, _int_r(255*alpha)});
		line.AddPoint(pos.Add(size.x, size.y), {  0, 255, 255, _int_r(255*alpha)});
		line.AddPoint(pos.Add(     0, size.y), {  0, 100, 255, _int_r(255*alpha)});
		line.Draw(true);
	}
}
//��ʏ�Ƀe�L�X�g���o��(2�s��)
//alpha��0.0�`1.0
void TutorialStage::DrawTopText2(MY_STRING text, double alpha) {

	DrawStr str(text, {WINDOW_WID/2, 155+70}, {255, 255, 255});
	const int useFont = font[0].GetFont();

	{
		const int margin = 24;
		DBL_XY pos  = (str.pos - str.GetTextSize(useFont)/2).Add(-margin/2, -margin/2).ToDblXY();
		DBL_XY size = (str.GetTextSize(useFont) + margin).ToDblXY();
		Box    box  = {pos, size, 0x000000};

		//�g�w�i.
		SetDrawBlendModeKR(BlendModeID::Alpha, 100*alpha);
		DrawBoxKR(&box, Anchor::LU);
		//�e�L�X�g.
		SetDrawBlendModeKR(BlendModeID::Alpha, 255*alpha);
		str.Draw(Anchor::Mid, useFont);
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

	DrawStr str(text, {WINDOW_WID/2, 155+70+55}, {255, 255, 255});
	const int useFont = font[0].GetFont();
	
	{
		const int margin = 24;
		DBL_XY pos  = (str.pos - str.GetTextSize(useFont)/2).Add(-margin/2, -margin/2).ToDblXY();
		DBL_XY size = (str.GetTextSize(useFont) + margin).ToDblXY();
		Box    box  = {pos, size, 0x000000};

		//�g�w�i.
		SetDrawBlendModeKR(BlendModeID::Alpha, 100*alpha);
		DrawBoxKR(&box, Anchor::LU);
		//�e�L�X�g.
		SetDrawBlendModeKR(BlendModeID::Alpha, 255*alpha);
		str.Draw(Anchor::Mid, useFont);
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