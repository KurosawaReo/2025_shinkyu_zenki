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

	//�e�L�X�g.
	DrawStr str({_T("�������� | �ړ�"), {0, 0}, 0x00FFFF});
	str.Draw();



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