/*
   - MenuManager.cpp -
   メニューシーン
*/
#include "Global.h"
#include "GameManager.h"
#include "MenuManager.h"

// 初期化
void MenuManager::Init() {

	p_data = &GameData::GetInst();

	// 入力アクション登録
	InputMng::AddAction("MENU_UP",   KeyID::Up);
	InputMng::AddAction("MENU_UP",   KeyID::W);
	InputMng::AddAction("MENU_UP",   PadXboxID::Up);
	InputMng::AddAction("MENU_DOWN", KeyID::Down);
	InputMng::AddAction("MENU_DOWN", KeyID::S);
	InputMng::AddAction("MENU_DOWN", PadXboxID::Down);
	InputMng::AddAction("MENU_NEXT", KeyID::Space);
	InputMng::AddAction("MENU_NEXT", KeyID::Enter);
	InputMng::AddAction("MENU_NEXT", PadXboxID::A);

	//フォント作成.
	fontMenu[0].CreateFontH(_T("メイリオ"), 28, 3, FontTypeID::Edge);
	fontMenu[1].CreateFontH(_T("メイリオ"), 36, 3, FontTypeID::Edge);

	//モードごとの画像読み込み.
	DrawImgMng::LoadFile(_T("Resources/Images/menu_endless.png"),  "menu0"); //ゲーム開始.
	DrawImgMng::LoadFile(_T("Resources/Images/menu_tutorial.png"), "menu1"); //チュートリアル.
	DrawImgMng::LoadFile(_T("Resources/Images/menu_title.png"),    "menu2"); //タイトルに戻る.

	Reset();
}

// リセット
void MenuManager::Reset() {
	selectedIndex = 0;
	tmBlink.Start();
}

// 更新
void MenuManager::Update() {

	//カーソル移動操作.
	if (InputMng::IsPushActionTime("MENU_UP") % 20 == 1) {
		selectedIndex = (selectedIndex + 3 - 1) % 3; //-1して、3の余り(0～2)をループ.
	}
	if (InputMng::IsPushActionTime("MENU_DOWN") % 20 == 1) { //長押しにも対応.
		selectedIndex = (selectedIndex + 1) % 3;     //+1して、3の余り(0～2)をループ.
	}

	//決定操作.
	if (InputMng::IsPushActionTime("MENU_NEXT") == 1) {

		switch (selectedIndex)
		{
			case 0:
				p_data->scene = SCENE_GAME;
				p_data->stage = STAGE_ENDLESS;  //耐久モードへ.
				//BGM.
				SoundMng::StopAll();
				if (auto i = SoundMng::Get("BGM_Endless")) {
					i->Play(true, 68); //再生.
				}
				break;
			case 1:
				p_data->scene = SCENE_GAME;
				p_data->stage = STAGE_TUTORIAL; //チュートリアルへ.
				//BGM.
				SoundMng::StopAll();
				if (auto i = SoundMng::Get("BGM_Tutorial")) {
					i->Play(true, 68); //再生.
				}
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
void MenuManager::Draw() {

	//アニメーション値.
	//この値を基準にメニューのアニメーションを制御する.
	const double cntrAnim1 = sin(counter/ 50 * M_PI);
	const double cntrAnim2 = sin(counter/100 * M_PI);
	//デジタル風の点滅用.
	if (tmBlink.IntervalTime()) {
		//一定確率で点滅する.
		isBlink = Calc::RandNum(0, 100) < 10;
	}

	//▼メニュー全体の背景.
	SetDrawBlendModeKR(BlendModeID::Alpha, 128);
	{
		Box box = {{0, 0}, {WINDOW_WID, WINDOW_HEI}, 0x000000};
		DrawBoxKR(box, Anchor::LU, true);
	}
	ResetDrawBlendMode();

	//▼メニュータイトル.
	{
		//基準地.
		const DBL_XY basePos = { WINDOW_WID / 2, 80 };
		//アニメーション値.
		const double anim1 = Calc::CalcNumEaseOutIn(fmod(counter, 120)/120);
		const double anim2 = sin(fmod(counter, 120)/120 * M_PI);

		Line lines[4] = {
		//「<」.
			{ basePos.Add(-55-100*anim1, 30), basePos.Add(-85-100*anim1,   0), 0x00FFFF },
			{ basePos.Add(-85-100*anim1,  0), basePos.Add(-55-100*anim1, -30), 0x00FFFF },
		//「>」.
			{ basePos.Add(+55+100*anim1, 30), basePos.Add(+85+100*anim1,   0), 0x00FFFF },
			{ basePos.Add(+85+100*anim1,  0), basePos.Add(+55+100*anim1, -30), 0x00FFFF }
		};

		//線描画.
		SetDrawBlendModeKR(BlendModeID::Alpha, 255 * anim2 * ((isBlink) ? 0.5 : 1.0));
		for (auto& i : lines) {
			//点滅時は位置をずらす.
			if (isBlink) {
				const int add = Calc::RandNum(-5, 5);
				i.stPos += add;
				i.edPos += add;
			}
			DrawLineKR(i, true, 2);
		}
		ResetDrawBlendMode();

		DrawStr str(_T("モード選択"), basePos.ToInt(), 0x00FFFF);
		str.Draw(Anchor::Mid, fontMenu[1].GetFont());
	}

	//▼メニュー項目.
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

	//▼各選択肢.
	{
		unsigned int color1 = (selectedIndex == 0) ? selectColor1 : normalColor;
		unsigned int color2 = (selectedIndex == 1) ? selectColor1 : normalColor;
		unsigned int color3 = (selectedIndex == 2) ? selectColor1 : normalColor;

		Box box = {DBL_XY(menuX, menuY), DBL_XY(boxWidth, boxHeight), selectColor1};
		DrawStr str(_T("     ゲーム開始"), { menuX+30, menuY+15 }, color1);
		DrawBoxKR(box, Anchor::LU, false);
		str.Draw(Anchor::LU, fontMenu[1].GetFont());

		box.pos.y += menuSpacing; //スペースを空ける.
		str.pos.y += menuSpacing; //スペースを空ける.
		str.text  = _T(" 　チュートリアル");
		str.color = color2;
		DrawBoxKR(box, Anchor::LU, false);
		str.Draw(Anchor::LU, fontMenu[1].GetFont());

		box.pos.y += menuSpacing; //スペースを空ける.
		str.pos.y += menuSpacing; //スペースを空ける.
		str.text  = _T("   タイトルに戻る");
		str.color = color3;
		DrawBoxKR(box, Anchor::LU, false);
		str.Draw(Anchor::LU, fontMenu[1].GetFont());
	}

	//▼カーソルの三角.
	{
		//基準座標.
		DBL_XY base = DBL_XY(menuX - 25, menuY + selectedIndex * menuSpacing + 35);

		Triangle tri = { {base, base.Add(-20, 10 * cntrAnim1), base.Add(-20, -10 * cntrAnim1)}, {} };
		tri.color = (cntrAnim1 >= 0) ? selectColor1 : selectColor2; //表か裏かで色を変える.
		DrawTriangleKR(tri, true, true);
	}

	//画像の座標(ここを中心とする)
	DBL_XY imgPos = { WINDOW_WID - 450, 450 };
	DBL_XY imgSize;

	//▼サムネ画像.
	{
		const double ext    = 0.4; //画像描画倍率.
		const int    margin = 10;  //枠を画像よりどれだけ大きくするか.
	
		string name = "menu" + to_string(selectedIndex);
		if (auto i = DrawImgMng::Get(name)) {
			//画像描画.
			i->DrawExtend(imgPos, {ext , ext});
			//画像のサイズ(Extend倍率分小さくする)
			imgSize = i->GetSize().ToDbl() * ext + margin;
			//画像の枠線(位置とサイズは画像を元にする)
			Box box = { imgPos, imgSize, frameColor };
			DrawBoxKR(box, Anchor::Mid, false);
		}
	}

	//▼説明文の枠（右下）- 画像の幅に合わせる
	int textBoxWidth = (int)imgSize.x;  // 画像の幅 + 余白（両端）
	int textBoxHeight = 260;
	int textBoxX = (int)(imgPos.x - textBoxWidth / 2);  // 画像と同じ中心位置
	int textBoxY = WINDOW_HEI - 300;

	//▼選択項目から画像、説明文エリアまでの線を描画
	{
		// 選択されたメニュー項目の右端座標
		int menuItemRightX = menuX + boxWidth;
		int menuItemCenterY = menuY + selectedIndex * menuSpacing + boxHeight / 2;

		int imgLeftX   = (int)(imgPos.x - imgSize.x/2); //画像の左端座標.
		int imgCenterY = (int)imgPos.y;
		int imgBottomY = (int)(imgPos.y + imgSize.y/2); //画像の下端座標.

		// 説明文エリアの上端中央座標
		int textBoxCenterX = textBoxX + textBoxWidth / 2;
		int textBoxTopY = textBoxY;

		// 線の太さ
		int lineThickness = 3;

		//線の透明度(155～255)
		const int alpha = 155 + 100 * (cntrAnim2 + 1.0) / 2.0;
		SetDrawBlendModeKR(BlendModeID::Alpha, alpha * ((isBlink) ? 0.5 : 1));

		// 1. メニュー項目から画像への線（水平線→垂直線）
		// 水平線（メニュー項目右端から画像左端まで）
		for (int i = 0; i < lineThickness; i++) {
			Line line = {
				DBL_XY(menuItemRightX, menuItemCenterY + i - lineThickness / 2),
				DBL_XY(imgLeftX,       menuItemCenterY + i - lineThickness / 2), 
				lineColor
			};
			//点滅時が位置をずらす.
			if (isBlink) {
				const int add = Calc::RandNum(-5, 5);
				line.stPos += add;
				line.edPos += add;
			}
			DrawLineKR(line);
		}

		// 2. 画像から説明文エリアへの線（垂直線のみ）
		// 垂直線（画像下端から説明文上端まで）
		for (int i = 0; i < lineThickness; i++) {
			Line line = {
				DBL_XY(imgPos.x + i - lineThickness / 2, imgBottomY),
				DBL_XY(imgPos.x + i - lineThickness / 2, textBoxTopY), 
				lineColor
			};
			//点滅時が位置をずらす.
			if (isBlink) {
				const int add = Calc::RandNum(-5, 5);
				line.stPos += add;
				line.edPos += add;
			}
			DrawLineKR(line);
		}

		ResetDrawBlendMode();
	}

	//▼モード説明タイトル（説明文枠の上に表示）
	int titleY = textBoxY - 40;  // 説明文枠の40ピクセル上に配置
	DrawStr str(_T("モード説明"), { textBoxX + 20, titleY }, 0x00FFFF);
	str.Draw(Anchor::LU, fontMenu[1].GetFont());

	////説明文枠の背景.
	//SetDrawBlendModeKR(BlendModeID::Alpha, 150);
	//{
	//	Box box = { DBL_XY(textBoxX, textBoxY), DBL_XY(textBoxWidth, textBoxHeight), 0x000000 };
	//	DrawBoxKR(box, Anchor::LU, true);
	//}
	//ResetDrawBlendMode();

	// 説明文枠の枠線（水色）
	{
		Box box = { DBL_XY(textBoxX, textBoxY), DBL_XY(textBoxWidth, textBoxHeight), frameColor};
		DrawBoxKR(box, Anchor::LU, false);
	}

	{
		int textX = textBoxX + 10;
		int textY = textBoxY + 20;

		//説明文用.
		DrawStr str(_T(""), {textX, textY}, normalColor);

		switch (selectedIndex)
		{
		case 0:
			str.text = _T("時間経過でLevelが上がり、");
			str.Draw(Anchor::LU, fontMenu[0].GetFont());
			
			str.pos.y += 30; //次の行へ.
			str.text = _T("ゲームオーバーになるまで続く");
			str.Draw(Anchor::LU, fontMenu[0].GetFont());

			str.pos.y += 30; //次の行へ.
			str.text = _T("エンドレスモード。");
			str.Draw(Anchor::LU, fontMenu[0].GetFont());

			str.pos.y += 30; //次の行へ.
			str.text = _T("・隕石を壊す : +500");
			str.Draw(Anchor::LU, fontMenu[0].GetFont());

			str.pos.y += 30; //次の行へ.
			str.text = _T("・アイテムを取る : +100");
			str.Draw(Anchor::LU, fontMenu[0].GetFont());

			str.pos.y += 30; //次の行へ.
			str.text = _T("・タイムボーナス : 1秒ごとに +10");
			str.Draw(Anchor::LU, fontMenu[0].GetFont());

			str.pos.y += 30; //次の行へ.
			str.text = _T("ハイスコアを目指して頑張ろう！");
			str.Draw(Anchor::LU, fontMenu[0].GetFont());
			break;

		case 1:
			str.text = _T("ゲームの基本操作を学べます。");
			str.Draw(Anchor::LU, fontMenu[0].GetFont());

			str.pos.y += 30; //次の行へ.
			str.text = _T("初めての方は最初に");
			str.Draw(Anchor::LU, fontMenu[0].GetFont());

			str.pos.y += 30; //次の行へ.
			str.text = _T("プレイしてください。");
			str.Draw(Anchor::LU, fontMenu[0].GetFont());
			break;

		case 2:
			str.text = _T("タイトル画面に戻ります。");
			str.Draw(Anchor::LU, fontMenu[0].GetFont());
			break;
		}
	}

	//▼操作説明（左下）
	int infoX = 50;
	int infoY = WINDOW_HEI - 200;
	int infoWidth = 500;
	int infoHeight = 180;
	
	{
		Box     box = { DBL_XY(infoX, infoY), DBL_XY(infoWidth, infoHeight), selectColor1 };
		DrawStr str = { _T(""), {infoX, infoY}, normalColor };

		DrawBoxKR(box, Anchor::LU, false);

		str.text = _T("選択 :↑↓ or W/S:");
		str.Draw(Anchor::LU, fontMenu[0].GetFont());

		str.pos.y += 50; //次の行へ.
		str.text = _T("決定 :SPACE/ENTER/Ⓐ");
		str.Draw(Anchor::LU, fontMenu[0].GetFont());
	}
}