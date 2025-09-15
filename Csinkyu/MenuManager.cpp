/*
   - MenuManager.cpp -
   メニューシーン
*/
#include "Global.h"
#include "GameManager.h"
#include "MenuManager.h"

// 初期化
void MenuManager::Init() {

	//GameDataのポインタを取得
	p_data = GameData::GetPtr();

	//アクションを登録する(新機能)
	InputMng* input = InputMng::GetPtr();
	input->AddAction(_T("MENU_UP"),   KEY_UP);
	input->AddAction(_T("MENU_UP"),   KEY_W);
	input->AddAction(_T("MENU_DOWN"), KEY_DOWN);
	input->AddAction(_T("MENU_DOWN"), KEY_S);
	input->AddAction(_T("MENU_NEXT"), KEY_SPACE);
	input->AddAction(_T("MENU_NEXT"), KEY_ENTER);

	Reset(); // リセット処理
}

// リセット
void MenuManager::Reset() {
	selectedIndex = 0; // 選択項目を初期化（0:ゲーム開始、1:チュートリアル）
}

// 更新
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
		if (selectedIndex == 0) {
			// ゲーム開始
			p_data->scene = SCENE_READY;
		}
		else if (selectedIndex == 1) {
			// チュートリアル
			p_data->scene = SCENE_TUTORIAL;
		}
	}

	// ESCキーでタイトルに戻る
	if (input->IsPushKeyTime(KEY_ESC) == 1) {
		p_data->scene = SCENE_TITLE;
	}
}

// 描画
void MenuManager::Draw() {

	// 背景を暗くする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 0, WINDOW_WID, WINDOW_HEI, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// メニュータイトル
	DrawString(WINDOW_WID / 2 - 50, 200, _T("MENU"), GetColor(255, 255, 255));

	// メニュー項目の描画
	int menuX = WINDOW_WID / 2 - 100; // 左端のX座標
	int menuY = 400;
	int menuSpacing = 80;
	int boxWidth = 200;
	int boxHeight = 50;

	unsigned int normalColor = GetColor(255, 255, 255);   // 白
	unsigned int selectColor = GetColor(0, 255, 255);     // 水色

	// ゲーム開始
	unsigned int color1 = (selectedIndex == 0) ? selectColor : normalColor;
	DrawBox(menuX, menuY, menuX + boxWidth, menuY + boxHeight, selectColor, FALSE); // 水色の枠
	DrawString(menuX + 20, menuY + 15, _T("ゲーム開始"), color1);

	// チュートリアル
	unsigned int color2 = (selectedIndex == 1) ? selectColor : normalColor;
	DrawBox(menuX, menuY + menuSpacing, menuX + boxWidth, menuY + menuSpacing + boxHeight, selectColor, FALSE); // 水色の枠
	DrawString(menuX + 20, menuY + menuSpacing + 15, _T("チュートリアル"), color2);

	// 操作説明エリア
	int infoX = 50;
	int infoY = WINDOW_HEI - 170;
	int infoWidth = 400;
	int infoHeight = 120;
	DrawBox(infoX, infoY, infoX + infoWidth, infoY + infoHeight, selectColor, FALSE); // 水色枠

	DrawString(infoX + 10, infoY + 10, _T("↑↓ or W/S: 選択"), normalColor);
	DrawString(infoX + 10, infoY + 40, _T("SPACE/ENTER: 決定"), normalColor);
	DrawString(infoX + 10, infoY + 70, _T("ESC: タイトルに戻る"), normalColor);

	// 選択中の項目に矢印を表示（水色）
	DrawString(menuX - 30, menuY + selectedIndex * menuSpacing + 15, _T("►"), selectColor);
}
