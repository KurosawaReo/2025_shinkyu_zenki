/*
   - BGManager.cpp -
*/
#include "BGManager.h"

// ¥*---=[ BGManager ]=---*¥ //

//‰Šú‰».
void BGManager::Init() {
}
//XV.
void BGManager::Update() {
	
	//Œ»İ‚Ì”wŒi.
	switch (useBgNo) {
		case 0:  bg1.Update();  break;
		default: assert(false); break;
	}
}
//•`‰æ.
void BGManager::Draw() {
	//Œ»İ‚Ì”wŒi.
	switch (useBgNo) {
		case 0:  bg1.Draw();    break;
		default: assert(false); break;
	}
}

//ƒ|[ƒY‚·‚é.
void BGManager::StopAnim() {
	//Œ»İ‚Ì”wŒi.
	switch (useBgNo) {
		case 0:  bg1.StopAnim(); break;
		default: assert(false);	 break;
	}
}
//ƒ|[ƒY‰ğœ.
void BGManager::RestartAnim() {
	//Œ»İ‚Ì”wŒi.
	switch (useBgNo) {
		case 0:  bg1.RestartAnim(); break;
		default: assert(false);	    break;
	}
}