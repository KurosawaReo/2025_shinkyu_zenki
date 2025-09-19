/*
   - MenuManager.cpp -
   メニューシーン
*/
#include "Global.h"
#include "GameManager.h"
#include "MenuManager.h"

// フォントハンドル
static int largeFont = -1;     // メニュー項目用（大）
static int infoFont = -1;      // 操作説明用（中）

// モード画像ハンドル
static int imageStart = -1;
static int imageTutorial = -1;
static int imageBack = -1;

// 初期化
void MenuManager::Init() {

	p_data = GameData::GetPtr();
	p_sound = SoundMng::GetPtr();

	// 入力アクション登録
	InputMng* input = InputMng::GetPtr();
	input->AddAction(_T("MENU_UP"), KEY_UP);
	input->AddAction(_T("MENU_UP"), KEY_W);
	input->AddAction(_T("MENU_DOWN"), KEY_DOWN);
	input->AddAction(_T("MENU_DOWN"), KEY_S);
	input->AddAction(_T("MENU_NEXT"), KEY_SPACE);
	input->AddAction(_T("MENU_NEXT"), KEY_ENTER);

	// フォント作成（1回のみ）
	if (largeFont == -1)
		largeFont = CreateFontToHandle(_T("メイリオ"), 36, 3, DX_FONTTYPE_ANTIALIASING_EDGE);

	if (infoFont == -1)
		infoFont = CreateFontToHandle(_T("メイリオ"), 28, 3, DX_FONTTYPE_ANTIALIASING_EDGE);

	// モードごとの画像読み込み（1回だけ）
	if (imageStart == -1)
		imageStart = LoadGraph(_T("res/menu_start.png")); // ゲーム開始画像

	if (imageTutorial == -1)
		imageTutorial = LoadGraph(_T("res/menu_tutorial.png")); // チュートリアル画像

	if (imageBack == -1)
		imageBack = LoadGraph(_T("res/menu_back.png")); // タイトル戻る画像

	Reset();
}

// リセット
void MenuManager::Reset() {
	selectedIndex = 0; // 0:ゲーム開始、1:チュートリアル、2:タイトルに戻る
}

// 更新
void MenuManager::Update() {

	InputMng* input = InputMng::GetPtr();

	//カーソル移動操作.
	if (input->IsPushActionTime(_T("MENU_UP")) % 20 == 1) {
		selectedIndex = (selectedIndex+3 - 1) % 3; //-1して、3の余り(0～2)をループ.
	}
	if (input->IsPushActionTime(_T("MENU_DOWN")) % 20 == 1) { //長押しにも対応.
		selectedIndex = (selectedIndex + 1) % 3;   //+1して、3の余り(0～2)をループ.
	}

	//決定操作.
	if (input->IsPushActionTime(_T("MENU_NEXT")) == 1) {
		
		switch (selectedIndex) 
		{
			case 0:
				p_data->scene = SCENE_GAME;
				p_data->stage = STAGE_ENDLESS;  //耐久モードへ.
				p_sound->StopAll();
				p_sound->Play(_T("BGM_Endless"), true, 68);
				break;
			case 1:
				p_data->scene = SCENE_GAME;
				p_data->stage = STAGE_TUTORIAL; //チュートリアルへ.
				p_sound->StopAll();
				p_sound->Play(_T("BGM_Tutorial"), true, 50);
				break;
			case 2:
				p_data->scene = SCENE_TITLE;    //タイトルへ.
				GameManager::GetPtr()->Reset(); //リセット.
				break;

			default: assert(FALSE); break;
		}
	}

	counter += 1;
}

// 描画
//なぜかここだけ「あいまいです」エラーが出るため、"DxLib::"というnamespaceをつけている.
void MenuManager::Draw() {

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DxLib::DrawBox(0, 0, WINDOW_WID, WINDOW_HEI, GetColor(0, 0, 0), TRUE);
	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// メニュータイトル（中央）
	DxLib::DrawStringToHandle(WINDOW_WID / 2 - 100, 100, _T("モード選択"), GetColor(0, 255, 255), largeFont);

	// メニュー項目（左寄せ）
	int menuX = 100;
	int menuY = 250;
	int menuSpacing = 100;
	int boxWidth = 400;
	int boxHeight = 70;

	unsigned int textColor    = GetColor(255, 255, 255);   //テキスト色:
	unsigned int frameColor   = GetColor(  0, 255, 255);   //枠色.
	unsigned int normalColor  = GetColor(150, 150, 150);   //未選択色.
	unsigned int selectColor1 = GetColor(100, 255, 255);   //カーソル表.
	unsigned int selectColor2 = GetColor( 50, 150, 255);   //カーソル裏.

	// 各項目描画
	unsigned int color1 = (selectedIndex == 0) ? selectColor1 : normalColor;
	DxLib::DrawBox(menuX, menuY, menuX + boxWidth, menuY + boxHeight, selectColor1, FALSE);
	DxLib::DrawStringToHandle(menuX + 30, menuY + 15, _T("     ゲーム開始"), color1, largeFont);

	unsigned int color2 = (selectedIndex == 1) ? selectColor1 : normalColor;
	DxLib::DrawBox(menuX, menuY + menuSpacing, menuX + boxWidth, menuY + menuSpacing + boxHeight, selectColor1, FALSE);
	DxLib::DrawStringToHandle(menuX + 30, menuY + menuSpacing + 15, _T("   チュートリアル"), color2, largeFont);

	unsigned int color3 = (selectedIndex == 2) ? selectColor1 : normalColor;
	DxLib::DrawBox(menuX, menuY + menuSpacing * 2, menuX + boxWidth, menuY + menuSpacing * 2 + boxHeight, selectColor1, FALSE);
	DxLib::DrawStringToHandle(menuX + 30, menuY + menuSpacing * 2 + 15, _T("   タイトルに戻る"), color3, largeFont);

	// 選択中の矢印（大きめ）
	{
		//基準座標.
		DBL_XY base = {_dbl(menuX - 25), _dbl(menuY + selectedIndex * menuSpacing + 35)};
		//アニメーション値.
		double anim = sin(counter/50*M_PI);
		
		Triangle tri = {{base, base.Add(-20, 10*anim), base.Add(-20, -10*anim)}, {} };
		tri.color = (anim >= 0) ? selectColor1 : selectColor2; //表か裏かで色を変える.
		int err = DrawTriangleST(&tri, true, false);

//		DxLib::DrawStringToHandle(menuX - 50, menuY + selectedIndex * menuSpacing + 15, _T("►"), selectColor, largeFont);
	}

	// ▼ モード画像の枠（右上）
	int imgBoxX = WINDOW_WID - 230;
	int imgBoxY = 40;
	int imgBoxWidth = 180;
	int imgBoxHeight = 180;

	// 画像枠の背景（半透明黒）
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DxLib::DrawBox(imgBoxX, imgBoxY, imgBoxX + imgBoxWidth, imgBoxY + imgBoxHeight, GetColor(0, 0, 0), TRUE);
	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 画像枠の枠線（水色）
	DxLib::DrawBox(imgBoxX, imgBoxY, imgBoxX + imgBoxWidth, imgBoxY + imgBoxHeight, frameColor, FALSE);

	// モード画像
	int imgX = imgBoxX + (imgBoxWidth - 128) / 2; // 中央寄せ（仮に128x128画像想定）
	int imgY = imgBoxY + (imgBoxHeight - 128) / 2;

	switch (selectedIndex) {
	case 0:
		DrawGraph(imgX, imgY, imageStart, TRUE);
		break;
	case 1:
		DrawGraph(imgX, imgY, imageTutorial, TRUE);
		break;
	case 2:
		DrawGraph(imgX, imgY, imageBack, TRUE);
		break;
	}

	// ▼ 説明文の枠（右下）
	int textBoxX = WINDOW_WID - 520;
	int textBoxY = WINDOW_HEI - 140;
	int textBoxWidth = 480;
	int textBoxHeight = 100;

	// 説明文枠の背景（半透明黒）
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DxLib::DrawBox(textBoxX, textBoxY, textBoxX + textBoxWidth, textBoxY + textBoxHeight, GetColor(0, 0, 0), TRUE);
	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 説明文枠の枠線（水色）
	DxLib::DrawBox(textBoxX, textBoxY, textBoxX + textBoxWidth, textBoxY + textBoxHeight, frameColor, FALSE);

	// 説明文（右下）
	int textX = textBoxX + 20;
	int textY = textBoxY + 30;

	switch (selectedIndex) {
	case 0:
		DxLib::DrawStringToHandle(textX, textY, _T("エンドレスモードでスコアを競おう！"), textColor, infoFont);
		break;
	case 1:
		DxLib::DrawStringToHandle(textX, textY, _T("操作方法を学ぶチュートリアルです"), textColor, infoFont);
		break;
	case 2:
		DxLib::DrawStringToHandle(textX, textY, _T("タイトル画面に戻ります"), textColor, infoFont);
		break;
	}

	// 操作説明（左下、大きく）
	int infoX = 50;
	int infoY = WINDOW_HEI - 200;
	int infoWidth = 500;
	int infoHeight = 180;

	DxLib::DrawBox(infoX, infoY, infoX + infoWidth, infoY + infoHeight, frameColor, FALSE); // 水色枠

	DxLib::DrawStringToHandle(infoX + 20, infoY + 20, _T("↑↓ or W/S: 選択"), textColor, infoFont);
	DxLib::DrawStringToHandle(infoX + 20, infoY + 70, _T("SPACE/ENTER: 決定"), textColor, infoFont);
}

