/*
   - main.cpp -
   プログラムの開始地点.
*/
#include "GameManager.h"

GameManager* gm; //実体を入れる用.

void App::Init() {
	gm = &GameManager::GetInst(); //GameManagerから実体取得.
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
	_return(-1, err < 0); //初期化エラー.

	InstApp.LoopDx();

	return 0;
}