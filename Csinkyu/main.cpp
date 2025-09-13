/*
   - main.cpp -
   �v���O�����̊J�n�n�_.
*/
#include "GameManager.h"

GameManager* gm; //���̂�����p.

void DxLibMain::Init() {
	gm = GameManager::GetPtr(); //GameManager������̎擾.
	gm->Init();
}

void DxLibMain::Update() {
	gm->Update();
}

void DxLibMain::Draw() {
	gm->Draw();
}

#if false
int main() {
#else
int WINAPI WinMain(
	_In_     HINSTANCE hinstance, 
	_In_opt_ HINSTANCE hPrevinstance,
	_In_     LPSTR     lpCmdLine, 
	_In_     int       nCmdShow
){
#endif

	int err = DxLibMain::GetPtr()->InitDx(WINDOW_WID, WINDOW_HEI, IS_WINDOW_MODE, FPS, false);
	_return(-1, err < 0); //�������G���[.

	DxLibMain::GetPtr()->LoopDx();

	return 0;
}