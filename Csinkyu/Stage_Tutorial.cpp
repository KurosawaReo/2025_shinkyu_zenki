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
	p_fireworksMng = FireworksManager::GetPtr();
	p_effectMng    = EffectManager::GetPtr();
	p_input        = InputMng::GetPtr();
	p_sound        = SoundMng::GetPtr();

	font[0].CreateFontH(_T(""), 20, 1, FONT_ANTI);
	font[1].CreateFontH(_T(""), 26, 1, FONT_ANTI);
}
//���Z�b�g.
void TutorialStage::Reset() {
	stepNo = 0; //�ォ��step1�ɂ���.
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

	stepNo++; //���̃X�e�b�v.
}
//�X�V:step1
void TutorialStage::UpdateStep1() {



	if (p_input->IsPushKeyTime(KEY_0) == 1) {

		//�T�E���h.
		p_sound->Play(_T("LevelUp"), false, 100);
		//�G�t�F�N�g.
		EffectData data{};
		data.type = Effect_Tutorial_Step2;		
		data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
		p_effectMng->SpawnEffect(&data);

		stepNo++; //���̃X�e�b�v.
	}
}
//�X�V:step2
void TutorialStage::UpdateStep2() {



	if (p_input->IsPushKeyTime(KEY_0) == 1) {

		//�T�E���h.
		p_sound->Play(_T("LevelUp"), false, 100);
		//�G�t�F�N�g.
		EffectData data{};
		data.type = Effect_Tutorial_Step3;
		data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
		p_effectMng->SpawnEffect(&data);

		stepNo++; //���̃X�e�b�v.
	}
}
//�X�V:step3
void TutorialStage::UpdateStep3() {



	if (p_input->IsPushKeyTime(KEY_0) == 1) {
		
		//�T�E���h.
		p_sound->Play(_T("LevelUp"), false, 100);
		//�G�t�F�N�g.
		EffectData data{};
		data.type = Effect_Tutorial_Step4;		
		data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
		p_effectMng->SpawnEffect(&data);

		stepNo++; //���̃X�e�b�v.
	}
}
//�X�V:step4
void TutorialStage::UpdateStep4() {

	//�`���[�g���A���I��.
	if (p_input->IsPushKeyTime(KEY_0) == 1) {
		//�^�C�g����(�S�ă��Z�b�g)
		p_data->scene = SCENE_TITLE;
		GameManager::GetPtr()->Reset();
	}
}

//�`��:step1
void TutorialStage::DrawStep1() {

	DrawTopText (_T("�v���C���[���ړ������悤"));
	DrawTopText2(_T("�L�[�{�[�h:��������"));

	//��������: �ړ�
}
//�`��:step2
void TutorialStage::DrawStep2() {

	DrawTopText(_T(""));

}
//�`��:step3
void TutorialStage::DrawStep3() {
	DrawTopText(_T(""));

}
//�`��:step4
void TutorialStage::DrawStep4() {
	DrawTopText(_T(""));

}

//��ʏ�Ƀe�L�X�g���o��.
void TutorialStage::DrawTopText(MY_STRING text) {

	//�e�L�X�g.
	DrawStr str(text, {WINDOW_WID/2, 150}, 0xFFFFFF);
	str.Draw(ANC_MID, font[1].GetFont());
	//�g.
	{
		const int margin = 24;

		DBL_XY pos  = (str.pos - str.GetTextSize(font[1].GetFont())/2).Add(-margin/2, -margin/2).ToDblXY();
		DBL_XY size = (str.GetTextSize(font[1].GetFont()) + margin).ToDblXY();
		//�O���f�[�V����������.
		GradLine line;
		line.AddPoint(pos,                     0x00FFFF);
		line.AddPoint(pos.Add(size.x,      0), 0x000000);
		line.AddPoint(pos.Add(size.x, size.y), 0xFF00FF);
		line.AddPoint(pos.Add(     0, size.y), 0x000000);
		line.Draw(true);
	}
}
//��ʏ�Ƀe�L�X�g���o��(2�s��)
void TutorialStage::DrawTopText2(MY_STRING text) {

	//�e�L�X�g.
	DrawStr str(text, {WINDOW_WID/2, 210}, 0xFFFFFF);
	str.Draw(ANC_MID, font[0].GetFont());
	//�g.
	{
		const int margin = 24;

		DBL_XY pos  = (str.pos - str.GetTextSize(font[0].GetFont())/2).Add(-margin/2, -margin/2).ToDblXY();
		DBL_XY size = (str.GetTextSize(font[0].GetFont()) + margin).ToDblXY();
		//�O���f�[�V����������.
		GradLine line;
		line.AddPoint(pos,                     0x00FFFF);
		line.AddPoint(pos.Add(size.x,      0), 0x000000);
		line.AddPoint(pos.Add(size.x, size.y), 0xFF00FF);
		line.AddPoint(pos.Add(     0, size.y), 0x000000);
		line.Draw(true);
	}
}