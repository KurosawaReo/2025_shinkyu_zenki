/*
   - MenuManager.cpp -
   メニューシーン.
*/
#include "Global.h"
#include "GameManager.h"
#include "MenuManager.h"
//#include "KR_Input.h"  // InputMngクラスの完全な定義のために追加

//初期化.
void MenuManager::Init() {

	//GameDataのポインタを取得
	p_data  = GameData::GetPtr();
	p_sound = SoundMng::GetPtr();

	//アクションを登録する(新機能)
	InputMng* input = InputMng::GetPtr();
	input->AddAction(_T("MENU_UP"),   KEY_UP);
	input->AddAction(_T("MENU_UP"),   KEY_W);
	input->AddAction(_T("MENU_DOWN"), KEY_DOWN);
	input->AddAction(_T("MENU_DOWN"), KEY_S);
	input->AddAction(_T("MENU_NEXT"), KEY_SPACE);
	input->AddAction(_T("MENU_NEXT"), KEY_ENTER);

	Reset(); //リセット処理.
}

//リセット.
void MenuManager::Reset() {
	selectedIndex = 0; //選択項目を初期化（0:ゲーム開始、1:チュートリアル）
}

//更新.
void MenuManager::Update() {

	InputMng* input = InputMng::GetPtr();

	// 上下キーで選択項目を変更（トリガー判定：押した瞬間のみ）
//	if (input->IsPushKeyTime(KEY_UP) == 1 || input->IsPushKeyTime(KEY_W) == 1) {
	if (input->IsPushActionTime(_T("MENU_UP")) == 1) {
		selectedIndex = (selectedIndex - 1 + 2) % 2; // 0と1の間をループ
	}
//	if (input->IsPushKeyTime(KEY_DOWN) == 1 || input->IsPushKeyTime(KEY_S) == 1) {
	if (input->IsPushActionTime(_T("MENU_DOWN")) == 1) {
		selectedIndex = (selectedIndex + 1) % 2; // 0と1の間をループ
	}

	// スペースキーまたはエンターキーで決定
//	if (input->IsPushKeyTime(KEY_SPACE) == 1 || input->IsPushKeyTime(KEY_ENTER) == 1) {
	if (input->IsPushActionTime(_T("MENU_NEXT")) == 1) {

		if (selectedIndex== 0) {
			//ゲーム開始(耐久モードへ)
			p_data->scene = SCENE_READY;
			p_data->stage = STAGE_ENDLESS;
			//BGM.
			p_sound->StopAll();
			p_sound->Play(_T("BGM_Endless"), true, 68);
		}
		else if (selectedIndex == 1) {
			//チュートリアルモードへ.
			p_data->scene = SCENE_TUTORIAL;
			p_data->stage = STAGE_TUTORIAL;
			//BGM.
			p_sound->StopAll();
			p_sound->Play(_T("BGM_Tutorial"), true, 68);
		}
	}

	// ESCキーでタイトルに戻る
	if (input->IsPushKeyTime(KEY_ESC) == 1) {
		p_data->scene = SCENE_TITLE;
	}
}

//描画.
void MenuManager::Draw() {

	// 背景を暗くする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 0, WINDOW_WID, WINDOW_HEI, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// メニュータイトル
	DrawString(WINDOW_WID / 2 - 50, 200, _T("MENU"), GetColor(255, 255, 255));

	// メニュー項目
	int menuY = 400;
	int menuSpacing = 80;

	// ゲーム開始
	unsigned int color1 = (selectedIndex == 0) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);
	DrawString(WINDOW_WID / 2 - 60, menuY, _T("ゲーム開始"), color1);

	// チュートリアル
	unsigned int color2 = (selectedIndex == 1) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);
	DrawString(WINDOW_WID / 2 - 80, menuY + menuSpacing, _T("チュートリアル"), color2);

	// 操作説明
	DrawString(50, WINDOW_HEI - 150, _T("↑↓ or W/S: 選択"), GetColor(200, 200, 200));
	DrawString(50, WINDOW_HEI - 120, _T("SPACE/ENTER: 決定"), GetColor(200, 200, 200));
	DrawString(50, WINDOW_HEI - 90, _T("ESC: タイトルに戻る"), GetColor(200, 200, 200));

	// 選択中の項目にカーソル表示
	DrawString(WINDOW_WID / 2 - 90, menuY + selectedIndex * menuSpacing, _T("►"), GetColor(255, 255, 0));
}