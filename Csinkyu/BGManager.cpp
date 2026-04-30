/*
   - BGManager.cpp -
*/
#include "BGManager.h"

//ˆË‘¶ŠÖŒW.
#include "GameData.h"
//QÆ.
static GameData* gameData;

// ¥*---=[ BGManager ]=---*¥ //

//‰Šú‰».
void BGManager::Init() {
	//QÆæ“¾.
	gameData = ManagerInsts::Get<GameData>();

	bg1.Init();
	bg2.Init();
}
//ƒŠƒZƒbƒg.
void BGManager::Reset() {
	useBgNo = 1;
}
//XV.
void BGManager::Update() {

	//ƒ|[ƒY’†‚ÌXV‚Í‚µ‚È‚¢.
	if (gameData->isPause) { return; }

	counter += gameData->speedRate; //Œo‰ßŠÔ.

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
void BGManager::Pause() {

	switch (useBgNo) {
		case 0:                 break; //”wŒi‚È‚µ.
		case 1:  bg1.Pause();	break; //”wŒi1.
		case 2:  bg2.Pause();	break; //”wŒi2.
		default: assert(false); break;
	}
}
//ƒ|[ƒY‰ğœ.
void BGManager::PauseEnd() {

	switch (useBgNo) {
		case 0:                  break; //”wŒi‚È‚µ.
		case 1:  bg1.PauseEnd(); break; //”wŒi1.
		case 2:  bg2.PauseEnd(); break; //”wŒi2.
		default: assert(false);  break;
	}
}