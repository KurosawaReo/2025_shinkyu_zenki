/*
   - TutorialManager.cpp -
   �`���[�g���A���V�[��.
*/
#include "TutorialManager.h"

//������.
void TutorialManager::Init() {

}
//���Z�b�g.
void TutorialManager::Reset() {
	stepNo = 1; //step1����J�n.
}
//�X�V.
void TutorialManager::Update() {

	//�X�e�b�v��.
	switch (stepNo) 
	{
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
		case 1: DrawStep1(); break;
		case 2: DrawStep2(); break;
		case 3: DrawStep3(); break;
		case 4: DrawStep4(); break;

		default: assert(FALSE); break;
	}
}

//�X�V:step1
void TutorialManager::UpdateStep1() {


	DrawStr str(_T("�������� : �ړ�"), {WINDOW_WID-100, WINDOW_HEI/2}, 0x00FFFF);
	str.Draw();

	//�g.
	Box box = { str.pos.Add(0, -1).ToDblXY(), {150, 30}, 0x00FFFF };
	DrawBoxST(&box, ANC_MID, false);

#if false
	if (/*����*/) {
		stepNo++; //���̃X�e�b�v.
	}
#endif
}
//�X�V:step2
void TutorialManager::UpdateStep2() {



#if false
	if (/*����*/) {
		stepNo++; //���̃X�e�b�v.
	}
#endif
}
//�X�V:step3
void TutorialManager::UpdateStep3() {



#if false
	if (/*����*/) {
		stepNo++; //���̃X�e�b�v.
	}
#endif
}
//�X�V:step4
void TutorialManager::UpdateStep4() {

	//�ǂ����Ń`���[�g���A���I��.
}

//�`��:step1
void TutorialManager::DrawStep1() {

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