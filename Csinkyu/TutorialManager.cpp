/*
   - TutorialManager.cpp -
   チュートリアルシーン.
*/
#include "TutorialManager.h"

//初期化.
void TutorialManager::Init() {

}
//リセット.
void TutorialManager::Reset() {
	stepNo = 1; //step1から開始.
}
//更新.
void TutorialManager::Update() {

	//ステップ別.
	switch (stepNo) 
	{
		case 1: UpdateStep1(); break;
		case 2: UpdateStep2(); break;
		case 3: UpdateStep3(); break;
		case 4: UpdateStep4(); break;

		default: assert(FALSE); break;
	}
}
//描画.
void TutorialManager::Draw() {

	//ステップ別.
	switch (stepNo)
	{
		case 1: DrawStep1(); break;
		case 2: DrawStep2(); break;
		case 3: DrawStep3(); break;
		case 4: DrawStep4(); break;

		default: assert(FALSE); break;
	}
}

//更新:step1
void TutorialManager::UpdateStep1() {

	//テキスト.
	DrawStr str({_T("↑↓←→ | 移動"), {0, 0}, 0x00FFFF});
	str.Draw();



#if false
	if (/*条件*/) {
		stepNo++; //次のステップ.
	}
#endif
}
//更新:step2
void TutorialManager::UpdateStep2() {



#if false
	if (/*条件*/) {
		stepNo++; //次のステップ.
	}
#endif
}
//更新:step3
void TutorialManager::UpdateStep3() {



#if false
	if (/*条件*/) {
		stepNo++; //次のステップ.
	}
#endif
}
//更新:step4
void TutorialManager::UpdateStep4() {

	//どこかでチュートリアル終了.
}

//描画:step1
void TutorialManager::DrawStep1() {

}
//描画:step2
void TutorialManager::DrawStep2() {

}
//描画:step3
void TutorialManager::DrawStep3() {

}
//描画:step4
void TutorialManager::DrawStep4() {

}