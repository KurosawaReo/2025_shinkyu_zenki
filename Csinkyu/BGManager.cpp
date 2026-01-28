/*
   - BGManager.cpp -
*/
#include "BGManager.h"

//ˆË‘¶ŠÖŒW.
#include "GameData.h"

// ¥*---=[ BGManager ]=---*¥ //

//‰Šú‰».
void BGManager::Init() {
	useBgNo = 0;
	bg1.Init();
	bg2.Init();
}
//ƒŠƒZƒbƒg.
void BGManager::Reset() {

}
//XV.
void BGManager::Update() {

	counter += GameData::GetInst().speedRate; //Œo‰ßŠÔ.

	switch (useBgNo) {
		case 0:                 break; //”wŒi‚È‚µ.
		case 1:  bg1.Update();  break; //”wŒi1.
		case 2:  bg2.Update();  break; //”wŒi2.
		default: assert(false); break;
	}
}
//•`‰æ.
void BGManager::Draw() {

	switch (useBgNo) {
		case 0:                 break; //”wŒi‚È‚µ.
		case 1:  bg1.Draw();    break; //”wŒi1.
		case 2:  bg2.Draw();    break; //”wŒi2.
		default: assert(false); break;
	}
}

//ƒ|[ƒY‚·‚é.
void BGManager::PauseAnim() {

	switch (useBgNo) {
		case 0:                   break; //”wŒi‚È‚µ.
		case 1:  bg1.PauseAnim(); break; //”wŒi1.
		case 2:  bg2.PauseAnim(); break; //”wŒi2.
		default: assert(false);   break;
	}
}
//ƒ|[ƒY‰ğœ.
void BGManager::RestartAnim() {

	switch (useBgNo) {
		case 0:                     break; //”wŒi‚È‚µ.
		case 1:  bg1.RestartAnim(); break; //”wŒi1.
		case 2:  bg2.RestartAnim(); break; //”wŒi2.
		default: assert(false);     break;
	}
}