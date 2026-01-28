/*
   - main.cpp -
   プログラムの開始地点.
*/

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

	ResultInt err = App::InitDx(WINDOW_WID, WINDOW_HEI, IS_WINDOW_MODE, FPS, false);
	if (err.GetCode() < 0) { return -1; } //初期化エラー.

	App::LoopDx();

	return 0;
}