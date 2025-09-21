/*
   - Stage_Tutorial.cpp -
   
   �X�e�[�W: �`���[�g���A��.
*/
#include "GameManager.h"
#include "EffectManager.h"
#include "Stage_Tutorial.h"

//������.
void TutorialStage::Init() {
	p_data      = GameData::GetPtr();
	p_effectMng = EffectManager::GetPtr();
	p_input     = InputMng::GetPtr();
	p_sound     = SoundMng::GetPtr();
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

	DrawTopText(_T("�v���C���[���ړ������悤\n"));

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
	str.Draw(ANC_MID, p_data->font2);
	//�g.
	{
		DBL_XY pos  = (str.pos - str.GetTextSize(p_data->font2)/2).Add(-8, -8).ToDblXY();
		DBL_XY size = (str.GetTextSize(p_data->font2) + 20).ToDblXY();
		//�O���f�[�V����������.
		GradLine line;
		line.AddPoint(pos,                     0x00FFFF);
		line.AddPoint(pos.Add(size.x,      0), 0x000000);
		line.AddPoint(pos.Add(size.x, size.y), 0xFF00FF);
		line.AddPoint(pos.Add(     0, size.y), 0x000000);
		line.Draw(true);
	}
}