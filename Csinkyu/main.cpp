/*
   - main.cpp -
   �v���O�����̊J�n�n�_.
*/
#include "GameManager.h"

GameManager* gm; //���̂�����p.

void App::Init() {
	gm = &GameManager::GetInst(); //GameManager������̎擾.
	gm->Init();
}

void App::Update() {
	gm->Update();
}

void App::Draw() {
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

	int err = InstApp.InitDx(WINDOW_WID, WINDOW_HEI, IS_WINDOW_MODE, FPS, false);
	_return(-1, err < 0); //�������G���[.

	InstApp.LoopDx();

	return 0;
}