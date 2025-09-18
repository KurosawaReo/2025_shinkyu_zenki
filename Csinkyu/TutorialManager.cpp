/*
   - TutorialManager.cpp -
   �`���[�g���A���V�[��.
*/
#include "GameManager.h"
#include "EffectManager.h"
#include "TutorialManager.h"

//������.
void TutorialManager::Init() {
	p_data      = GameData::GetPtr();
	p_effectMng = EffectManager::GetPtr();
	p_input     = InputMng::GetPtr();
	p_sound     = SoundMng::GetPtr();
}
//���Z�b�g.
void TutorialManager::Reset() {
	stepNo = 0; //�ォ��step1�ɂ���.
}
//�X�V.
void TutorialManager::Update() {

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
void TutorialManager::Draw() {

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
void TutorialManager::UpdateStep0() {



	if (p_input->IsPushKeyTime(KEY_0) == 1) {

		//�T�E���h.
		p_sound->Play(_T("LevelUp"), false, 100);
		//�G�t�F�N�g.
		EffectData data{};
		data.type = Effect_Tutorial_Step1;		
		data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
		p_effectMng->SpawnEffect(&data);

		stepNo++; //���̃X�e�b�v.
	}
}
//�X�V:step1
void TutorialManager::UpdateStep1() {

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
void TutorialManager::UpdateStep2() {



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
void TutorialManager::UpdateStep3() {



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
void TutorialManager::UpdateStep4() {

	//�`���[�g���A���I��.
	if (p_input->IsPushKeyTime(KEY_0) == 1) {
		//�^�C�g����(�S�ă��Z�b�g)
		GameManager::GetPtr()->Reset();
	}
}

//�`��:step1
void TutorialManager::DrawStep1() {


	DrawStr str(_T("��������: �ړ�"), {WINDOW_WID/2-500, WINDOW_HEI/2}, 0x00FFFF);
	str.Draw(ANC_MID, p_data->font1);

	//�g.
	Box box = { str.pos.Add(0, 0).ToDblXY(), str.GetTextSize(p_data->font1).ToDblXY()+12, 0x00FFFF};
	DrawBoxST(&box, ANC_MID, false);
}
//�`��:step2
void TutorialManager::DrawStep2() {

}
//�`��:step3
void TutorialManager::DrawStep3() {

}
//�`��:step4
void TutorialManager::DrawStep4() {

}