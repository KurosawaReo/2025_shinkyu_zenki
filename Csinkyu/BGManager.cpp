/*
   - BGManager.cpp -
*/
#include "BGManager.h"

//ˆË‘¶ŠÖŒW.
#include "BG1.h"
#include "GameData.h"

// ¥*---=[ BGManager ]=---*¥ //

//‰Šú‰».
void BGManager::Init() {
	useBgNo = 0;
	bg1.Init();
}
//XV.
void BGManager::Update() {

	counter += GameData::GetInst().speedRate; //Œo‰ßŠÔ.

	switch (useBgNo) {
		case 0:  bg1.Update();  break; //”wŒi1.
		default: assert(false); break;
	}
}
//•`‰æ.
void BGManager::Draw() {

	switch (useBgNo) {
		case 0:  bg1.Draw();    break; //”wŒi1.
		default: assert(false); break;
	}
}

//ƒ|[ƒY‚·‚é.
void BGManager::StopAnim() {

	switch (useBgNo) {
		case 0:  bg1.StopAnim(); break; //”wŒi1.
		default: assert(false);  break;
	}
}
//ƒ|[ƒY‰ğœ.
void BGManager::RestartAnim() {

	switch (useBgNo) {
		case 0:  bg1.RestartAnim(); break; //”wŒi1.
		default: assert(false);     break;
	}
}