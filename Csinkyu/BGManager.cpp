/*
   - BGManager.cpp -
*/
#include "BGManager.h"

#include "BG1.h"
#include "GameManager.h"

// ▼*---=[ BGManager ]=---*▼ //

//初期化.
void BGManager::Init() {

	BG1::GetInst().Init();
}
//更新.
void BGManager::Update() {
	
	BG1::GetInst().Update(); //TODO: switch文での切り替え.
}
//描画.
void BGManager::Draw() {

	BG1::GetInst().Draw(); //TODO: switch文での切り替え.
}

//ポーズする.
void BGManager::StopAnim() {
	BG1::GetInst().StopAnim(); //TODO: switch文での切り替え.
}
//ポーズ解除.
void BGManager::RestartAnim() {
	BG1::GetInst().RestartAnim(); //TODO: switch文での切り替え.
}