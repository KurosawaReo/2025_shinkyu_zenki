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

	try {
		//初期化処理.
		App::InitDx(WINDOW_WID, WINDOW_HEI, IS_WINDOW_MODE, FPS, false);
	}
	catch (const ErrorMsg& err) {
		Debug::Log(_T("InitDx"), err.GetResult());
	}

	try {
		//ループ処理.
		App::LoopDx();
	}
	catch (const ErrorMsg& err) {
		Debug::Log(_T("LoopDx"), err.GetResult());
	}

	return 0;
}