/*
   - MenuManager.cpp -
   メニューシーン
*/
#include "Global.h"
#include "GameManager.h"
#include "MenuManager.h"

// 初期化
void MenuManager::Init() {

	p_data  = &GameData::GetInst();
	p_sound = &SoundMng::GetInst();

	// 入力アクション登録
	InstInputMng.AddAction(_T("MENU_UP"),   KeyID::Up);
	InstInputMng.AddAction(_T("MENU_UP"),   KeyID::W);
	InstInputMng.AddAction(_T("MENU_UP"),   PadXboxID::Up);
	InstInputMng.AddAction(_T("MENU_DOWN"), KeyID::Down);
	InstInputMng.AddAction(_T("MENU_DOWN"), KeyID::S);
	InstInputMng.AddAction(_T("MENU_DOWN"), PadXboxID::Down);
	InstInputMng.AddAction(_T("MENU_NEXT"), KeyID::Space);
	InstInputMng.AddAction(_T("MENU_NEXT"), KeyID::Enter);
	InstInputMng.AddAction(_T("MENU_NEXT"), PadXboxID::A);

	//フォント作成.
	fontMenu[0].CreateFontH(_T("メイリオ"), 28, 3, FontTypeID::Edge);
	fontMenu[1].CreateFontH(_T("メイリオ"), 36, 3, FontTypeID::Edge);

	//モードごとの画像読み込み.
	imgMenu[0].LoadFile(_T("Resources/Images/menu_start.png"));    //ゲーム開始.
	imgMenu[1].LoadFile(_T("Resources/Images/menu_tutorial.png")); //チュートリアル.
	imgMenu[2].LoadFile(_T("Resources/Images/menu_back.png"));     //タイトルに戻る.

	Reset();
}

// リセット
void MenuManager::Reset() {
	selectedIndex = 0; // 0:ゲーム開始、1:チュートリアル、2:タイトルに戻る
}

// 更新
void MenuManager::Update() {

	//カーソル移動操作.
	if (InstInputMng.IsPushActionTime(_T("MENU_UP")) % 20 == 1) {
		selectedIndex = (selectedIndex + 3 - 1) % 3; //-1して、3の余り(0～2)をループ.
	}
	if (InstInputMng.IsPushActionTime(_T("MENU_DOWN")) % 20 == 1) { //長押しにも対応.
		selectedIndex = (selectedIndex + 1) % 3;   //+1して、3の余り(0～2)をループ.
	}

	//決定操作.
	if (InstInputMng.IsPushActionTime(_T("MENU_NEXT")) == 1) {

		switch (selectedIndex)
		{
			case 0:
				p_data->scene = SCENE_GAME;
				p_data->stage = STAGE_ENDLESS;  //耐久モードへ.
				//BGM.
				p_sound->StopAll();
				p_sound->Play(_T("BGM_Endless"), true, 68);
				break;
			case 1:
				p_data->scene = SCENE_GAME;
				p_data->stage = STAGE_TUTORIAL; //チュートリアルへ.
				//BGM.
				p_sound->StopAll();
				p_sound->Play(_T("BGM_Tutorial"), true, 50);
				break;
			case 2:
				p_data->scene = SCENE_TITLE;    //タイトルへ.
				GameManager::GetInst().Reset(); //リセット.
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
	DxLib::DrawStringToHandle(WINDOW_WID / 2 - 100, 100, _T("モード選択"), GetColor(0, 255, 255), fontMenu[1].GetFont());

	// メニュー項目
	int menuX = 100;
	int menuY = 250;
	int menuSpacing = 100;
	int boxWidth = 400;
	int boxHeight = 70;

	unsigned int textColor    = GetColor(255, 255, 255); //テキスト色:
	unsigned int frameColor   = GetColor(0, 255, 255);   //枠色.
	unsigned int normalColor  = GetColor(150, 150, 150); //未選択色.
	unsigned int selectColor1 = GetColor(100, 255, 255); //カーソル表.
	unsigned int selectColor2 = GetColor(50, 150, 255);  //カーソル裏.
	unsigned int lineColor    = GetColor(0, 255, 255);   //線の色（黄色）.

	// 各項目描画
	unsigned int color1 = (selectedIndex == 0) ? selectColor1 : normalColor;
	DxLib::DrawBox(menuX, menuY, menuX + boxWidth, menuY + boxHeight, selectColor1, FALSE);
	DxLib::DrawStringToHandle(menuX + 30, menuY + 15, _T("     ゲーム開始"), color1, fontMenu[1].GetFont());

	unsigned int color2 = (selectedIndex == 1) ? selectColor1 : normalColor;
	DxLib::DrawBox(menuX, menuY + menuSpacing, menuX + boxWidth, menuY + menuSpacing + boxHeight, selectColor1, FALSE);
	DxLib::DrawStringToHandle(menuX + 30, menuY + menuSpacing + 15, _T("   チュートリアル"), color2, fontMenu[1].GetFont());

	unsigned int color3 = (selectedIndex == 2) ? selectColor1 : normalColor;
	DxLib::DrawBox(menuX, menuY + menuSpacing * 2, menuX + boxWidth, menuY + menuSpacing * 2 + boxHeight, selectColor1, FALSE);
	DxLib::DrawStringToHandle(menuX + 30, menuY + menuSpacing * 2 + 15, _T("   タイトルに戻る"), color3, fontMenu[1].GetFont());

	// 選択中の矢印（大きめ）
	{
		//基準座標.
		DBL_XY base = { _dbl(menuX - 25), _dbl(menuY + selectedIndex * menuSpacing + 35) };
		//アニメーション値.
		double anim = sin(counter / 50 * M_PI);

		Triangle tri = { {base, base.Add(-20, 10 * anim), base.Add(-20, -10 * anim)}, {} };
		tri.color = (anim >= 0) ? selectColor1 : selectColor2; //表か裏かで色を変える.
		DrawTriangleKR(&tri, true, true);
	}

	//画像の座標(ここを中心とする)
	DBL_XY imgPos = { WINDOW_WID - 450, 450 };
	//画像のサイズ.
	DBL_XY imgSize = imgMenu[selectedIndex].GetSize().ToDblXY();
	//枠を画像よりどれだけ大きくするか.
	const int margin = 10;

	//画像.
	imgMenu[selectedIndex].Draw(imgPos);
	//画像の枠線(位置とサイズは画像を元にする)
	Box box = { imgPos, imgSize + margin, frameColor };
	DrawBoxKR(&box, Anchor::Mid, false);

	// ▼ 説明文の枠（右下）- 画像の幅に合わせる
	int textBoxWidth = (int)imgSize.x + margin * 2;  // 画像の幅 + 余白（両端）
	int textBoxHeight = 260;
	int textBoxX = (int)(imgPos.x - textBoxWidth / 2);  // 画像と同じ中心位置
	int textBoxY = WINDOW_HEI - 300;

	// ▼ 選択項目から画像、説明文エリアまでの線を描画
	{
		// 選択されたメニュー項目の右端座標
		int menuItemRightX = menuX + boxWidth;
		int menuItemCenterY = menuY + selectedIndex * menuSpacing + boxHeight / 2;

		int imgLeftX   = (int)(imgPos.x - imgSize.x/2) - margin/2; //画像の左端座標.
		int imgCenterY = (int)imgPos.y;
		int imgBottomY = (int)(imgPos.y + imgSize.y/2) + margin/2; //画像の下端座標.

		// 説明文エリアの上端中央座標
		int textBoxCenterX = textBoxX + textBoxWidth / 2;
		int textBoxTopY = textBoxY;

		// 線の太さ
		int lineThickness = 3;

		// アニメーション効果（点滅）
		double pulseAnim = (sin(counter * 0.1) + 1.0) / 2.0; // 0.0～1.0の範囲
		int alpha = (int)(128 + 127 * pulseAnim); // 128～255の範囲でアルファ値変化

		DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		// 1. メニュー項目から画像への線（水平線→垂直線）
		// 水平線（メニュー項目右端から画像左端まで）
		for (int i = 0; i < lineThickness; i++) {
			DxLib::DrawLine(
				menuItemRightX, menuItemCenterY+i-lineThickness/2,
				imgLeftX,       menuItemCenterY+i-lineThickness/2, lineColor
			);
		}

		// 2. 画像から説明文エリアへの線（垂直線のみ）
		// 垂直線（画像下端から説明文上端まで）
		for (int i = 0; i < lineThickness; i++) {
			DxLib::DrawLine(
				(int)imgPos.x+i-lineThickness/2, imgBottomY,
				(int)imgPos.x+i-lineThickness/2, textBoxTopY, lineColor
			);
		}

		DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// モード説明タイトル（説明文枠の上に表示）
	int titleY = textBoxY - 40;  // 説明文枠の40ピクセル上に配置
	DxLib::DrawStringToHandle(textBoxX + 20, titleY, _T("モード説明"), GetColor(0, 255, 255), fontMenu[1].GetFont());

	// 説明文枠の背景（半透明黒）
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DxLib::DrawBox(textBoxX, textBoxY, textBoxX + textBoxWidth, textBoxY + textBoxHeight, GetColor(0, 0, 0), TRUE);
	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 説明文枠の枠線（水色）
	DxLib::DrawBox(textBoxX, textBoxY, textBoxX + textBoxWidth, textBoxY + textBoxHeight, frameColor, FALSE);

	int textX = textBoxX + 10;
	int textY = textBoxY + 20;

	switch (selectedIndex)
	{
	case 0:
		DrawStringToHandle(textX, textY + 0, _T("時間経過でLevelが上がり、"), normalColor, fontMenu[0].GetFont());
		DrawStringToHandle(textX, textY + 30, _T("ゲームオーバーになるまで続く"), normalColor, fontMenu[0].GetFont());
		DrawStringToHandle(textX, textY + 60, _T("エンドレスモード。"), normalColor, fontMenu[0].GetFont());
		DrawStringToHandle(textX, textY + 90, _T("・隕石を壊す : +500"), normalColor, fontMenu[0].GetFont());
		DrawStringToHandle(textX, textY + 120, _T("・アイテムを取る : +100"), normalColor, fontMenu[0].GetFont());
		DrawStringToHandle(textX, textY + 150, _T("・タイムボーナス : 1秒ごとに +10"), normalColor, fontMenu[0].GetFont());
		DrawStringToHandle(textX, textY + 180, _T("ハイスコアを目指して頑張ろう！"), normalColor, fontMenu[0].GetFont());
		break;
	case 1:
		DrawStringToHandle(textX, textY + 0, _T("ゲームの基本操作を学べます。"), normalColor, fontMenu[0].GetFont());
		DrawStringToHandle(textX, textY + 40, _T("初めての方は最初に"), normalColor, fontMenu[0].GetFont());
		DrawStringToHandle(textX, textY + 80, _T("プレイしてください。"), normalColor, fontMenu[0].GetFont());
		break;
	case 2:
		DrawStringToHandle(textX, textY + 0, _T("タイトル画面に戻ります。"), normalColor, fontMenu[0].GetFont());
		break;
	}

	// ▼ 操作説明（左下）
	int infoX = 50;
	int infoY = WINDOW_HEI - 200;
	int infoWidth = 500;
	int infoHeight = 180;

	DrawBox(infoX, infoY, infoX + infoWidth, infoY + infoHeight, selectColor1, FALSE);
	DrawStringToHandle(infoX + 20, infoY + 20, _T("選択 :↑↓ or W/S:"), normalColor, fontMenu[0].GetFont());
	DrawStringToHandle(infoX + 20, infoY + 70, _T("決定 :SPACE/ENTER/Ⓐ"), normalColor, fontMenu[0].GetFont());
}