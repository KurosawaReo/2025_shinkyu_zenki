/*
   - Scene_Menu.cpp -
*/
#include "Scene_Menu.h"

//依存関係.
#include "BGManager.h"
#include "GameData.h"
#include "GameManager.h"
//参照.
static GameData&  gameData = GameData::GetInst();
static BGManager& p_bg   = BGManager::GetInst();

// 初期化
void MenuScene::Init() {

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

	//電気の設定.
//	electr.color = 0xffff00;

	Reset();
}

// リセット
void MenuScene::Reset() {
	selectedIndex = 0;
	tmBlink.Start();
}

// 更新
void MenuScene::Update() {

	//カーソル移動操作.
	if (InputMng::IsPushActionTime("MENU_UP") % 20 == 1) {
		selectedIndex = (selectedIndex + 3 - 1) % 3; //-1して、3の余り(0～2)をループ.
		OnCursorMove();
	}
	if (InputMng::IsPushActionTime("MENU_DOWN") % 20 == 1) { //長押しにも対応.
		selectedIndex = (selectedIndex + 1) % 3;     //+1して、3の余り(0～2)をループ.
		OnCursorMove();
	}
	//点滅終了.
	if (tmBlink.GetPassTime() <= 0) {
		isBlink = false;
	}

	//決定操作.
	if (InputMng::IsPushActionTime("MENU_NEXT") == 1) {

		switch (selectedIndex)
		{
			case 0:
				gameData.scene = SCENE_GAME;
				gameData.stage = STAGE_ENDLESS; //耐久モードへ.
				p_bg.SetBgNo(1);              //背景変更.
#if !defined BGM_NONE
				//BGM.
				SoundMng::StopAll();
				if (auto i = SoundMng::Get("BGM_Endless")) {
					i->Play(true, 68); //再生.
				}
#endif
				break;
			case 1:
				gameData.scene = SCENE_GAME;
				gameData.stage = STAGE_TUTORIAL; //チュートリアルへ.
				p_bg.SetBgNo(1);               //背景変更.
#if !defined BGM_NONE
				//BGM.
				SoundMng::StopAll();
				if (auto i = SoundMng::Get("BGM_Tutorial")) {
					i->Play(true, 68); //再生.
				}
#endif
				break;
			case 2:
				gameData.scene = SCENE_TITLE;    //タイトルへ.
				GameManager::GetInst().Reset(); //リセット.
				break;

			default: assert(FALSE); break;
		}

		//サウンド.
		if (auto i = SoundMng::Get("MenuOK")) {
			i->Play(false, 70);
		}
	}

	//経過時間.
	counter += 1;
}

// 描画
void MenuScene::Draw() {

	//アニメーション値.
	//この値を基準にメニューのアニメーションを制御する.
	const double anim1 = sin(counter/ 50 * M_PI);
	const double anim2 = sin(counter/100 * M_PI);
	const double anim3 = Calc::AnimEaseOutIn(fmod(counter, 120)/120);
	const double anim4 = sin(fmod(counter, 120)/120 * M_PI);
	const double anim5 = Calc::AnimEaseOutIn(fmod(counter-20, 120)/120);
	const double anim6 = sin(fmod(counter-20, 120)/120 * M_PI);

	//▼メニュー全体の背景.
	{
		DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 128);

		Box box = {{0, 0}, {WINDOW_WID, WINDOW_HEI}, 0x000000};
		DrawBoxKR(box, Anchor::LU, true);
	}
	//▼メニュータイトル.
	{
		//基準地.
		const DBL_XY basePos = { WINDOW_WID / 2, 80 };

		{
			DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * anim4);

			Line lines[4] = {
			//「<」.
				{ basePos.Add(-55-100*anim3, 30), basePos.Add(-85-100*anim3,   0), 0x00FFFF },
				{ basePos.Add(-85-100*anim3,  0), basePos.Add(-55-100*anim3, -30), 0x00FFFF },
			//「>」.
				{ basePos.Add(+55+100*anim3, 30), basePos.Add(+85+100*anim3,   0), 0x00FFFF },
				{ basePos.Add(+85+100*anim3,  0), basePos.Add(+55+100*anim3, -30), 0x00FFFF }
			};
			//線描画.
			for (auto& i : lines) {
				DrawLineKR(i, true, 2);
			}
		}
		{
			DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * anim6);

			Line lines[4] = {
			//「<」.
				{ basePos.Add(-55-100*anim5, 30), basePos.Add(-85-100*anim5,   0), 0x00FFFF },
				{ basePos.Add(-85-100*anim5,  0), basePos.Add(-55-100*anim5, -30), 0x00FFFF },
			//「>」.
				{ basePos.Add(+55+100*anim5, 30), basePos.Add(+85+100*anim5,   0), 0x00FFFF },
				{ basePos.Add(+85+100*anim5,  0), basePos.Add(+55+100*anim5, -30), 0x00FFFF }
			};
			//線描画.
			for (auto& i : lines) {
				DrawLineKR(i, true, 2);
			}
		}

		DrawStr str(_T("モード選択"), basePos.ToInt(), 0x00FFFF);
		str.Draw(Anchor::Mid, fontMenu[1].GetFont());
	}

	//▼各選択肢.
	{
		//テキスト & 枠線用.
		Box box = { mLayout.menuPos, mLayout.menuSize, mColor.select1 };
		DrawStr str(_T(""), mLayout.menuPos.ToInt(), {});
		//選択肢テキスト.
		MY_STRING texts[] = {
			_T("ゲーム開始"), _T("チュートリアル"), _T("タイトルに戻る")
		};
		//テキスト色.
		unsigned int colors[] = {
			(selectedIndex == 0) ? mColor.select1 : mColor.normal,
			(selectedIndex == 1) ? mColor.select1 : mColor.normal,
			(selectedIndex == 2) ? mColor.select1 : mColor.normal
		};

		INT_XY savePos; //保存用.

		//全選択肢ループ.
		for (int i = 0; i < 3; i++) {

			str.text  = texts[i];
			str.color = colors[i];
			savePos   = str.pos;  //前の座標を保存.
			//枠.
			DrawBoxKR(box, Anchor::Mid, false);
			
			int alpha = 255; //透明度.
			//ブレる処理.
			if (isBlink && selectedIndex == i) {
				const int add = Calc::RandNum(-5, 5); //ずらす量.
				str.pos += add;						  //位置をずらす.
				alpha = 128;
			}
			//テキスト.
			{
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, alpha);
				str.Draw(Anchor::Mid, fontMenu[1].GetFont());
			}
			
			//リセット.
			str.pos = savePos;
			//スペースを空ける.
			box.pos.y += mLayout.menuSpace;
			str.pos.y += mLayout.menuSpace;
		}
	}

	//▼カーソルの三角.
	{
		//基準座標.
		DBL_XY base = mLayout.menuPos.Add(
			-mLayout.menuSize.x/2 - 20,			//横にずらす.
			+mLayout.menuSpace * selectedIndex	//縦にずらす.
		);

		Triangle tri = { {base, base.Add(-20, 10 * anim1), base.Add(-20, -10 * anim1)}, {} };
		tri.color = (anim1 >= 0) ? mColor.select1 : mColor.select2; //表か裏かで色を変える.
		DrawTriangleKR(tri, true, true);
	}

	//画像サイズ保存用.
	DBL_XY imgSize;

	//▼サムネ画像.
	{
		const double extend = 0.4; //画像描画倍率.
		const int    margin = 10;  //枠を画像よりどれだけ大きくするか.
	
		string name = "menu" + to_string(selectedIndex);
		if (auto i = DrawImgMng::Get(name)) {
			//画像描画.
			{
				DrawMode _(DrawModeID::Bilinear, DrawBlendModeID::None, 255); //画像を滑らかに.
				i->DrawExtend(mLayout.imgPos, {extend , extend});
			}
			//画像のサイズ(Extend倍率分小さくする)
			imgSize = i->GetSize().ToDbl() * extend + margin;
			//画像の枠線(位置とサイズは画像に合わせる)
			Box box = { mLayout.imgPos, imgSize, mColor.frame };
			DrawBoxKR(box, Anchor::Mid, false);
		}
	}

	//▼説明文の枠（右下）- 画像の幅に合わせる
	int textBoxWidth  = _int_r(imgSize.x);
	int textBoxHeight = 260;
	int textBoxX      = _int_r(mLayout.imgPos.x - textBoxWidth/2);  // 画像と同じ中心位置
	int textBoxY      = WINDOW_HEI - 300;

	//▼選択項目から画像、説明文エリアまでの線を描画
	{
		int imgLeftX   = (int)(mLayout.imgPos.x - imgSize.x/2); //画像の左端座標.
		int imgCenterY = (int) mLayout.imgPos.y;
		int imgBottomY = (int)(mLayout.imgPos.y + imgSize.y/2); //画像の下端座標.

		// 説明文エリアの上端中央座標
		int textBoxCenterX = textBoxX + textBoxWidth / 2;
		int textBoxTopY = textBoxY;

		{
			//線の透明度(155～255)
			const int alpha = _int_r(155 + 100 * (anim2 + 1.0) / 2.0);
			DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, alpha);

			//1.メニュー項目から画像への線（メニュー項目右端から画像左端まで）
			{
				//線データ.
				Line line = {
					mLayout.menuPos.Add(mLayout.menuSize.x/2, 0),            //始点.
					DBL_XY(mLayout.imgPos.x-imgSize.x/2, mLayout.menuPos.y), //終点.
					mColor.line                                              //色.
				};
				//選択してる所にずらす.
				line.stPos.y += mLayout.menuSpace * selectedIndex;
				line.edPos.y += mLayout.menuSpace * selectedIndex;
				//線描画.
				DrawLineKR(line, false, 3.0f);
			}

			//2.画像から説明文エリアへの線（画像下端から説明文上端まで）
			{
				Line line = {
					DBL_XY(mLayout.imgPos.x-30, imgBottomY),  //始点.
					DBL_XY(mLayout.imgPos.x-30, textBoxTopY), //終点.
					mColor.line								  //色.
				};
				//線1.
				DrawLineKR(line, false, 3.0f);
				//線2.
				line.stPos.x += 60;
				line.edPos.x += 60;
				DrawLineKR(line, false, 3.0f);
			}
		}
	}

	//▼操作説明（左下）
	{
		int infoWidth = 500;
		int infoHeight = textBoxHeight;
		int infoX = _int_r(mLayout.menuPos.x - _dbl(infoWidth)/2);
		int infoY = textBoxY;

		Box     box = { DBL_XY(infoX, infoY), DBL_XY(infoWidth, infoHeight), mColor.select1 };
		DrawStr str = { _T(""), INT_XY(infoX, infoY) + mLayout.loreInner, mColor.normal };

		DrawStr str2(_T("操作"), { infoX + 10, infoY - 10 }, 0x00FFFF);
		str2.Draw(Anchor::LD, fontMenu[0].GetFont());

		DrawBoxKR(box, Anchor::LU, false);

		str.text = _T("選択: ↑↓ or W/S");
		str.Draw(Anchor::LU, fontMenu[0].GetFont());

		str.pos.y += mLayout.loreLineSpace; //次の行へ.
		str.pos.y += mLayout.loreLineSpace; //次の行へ.
		str.text = _T("決定: SPACE/ENTER/Ⓐ");
		str.Draw(Anchor::LU, fontMenu[0].GetFont());
	}

	//▼モード説明タイトル（説明文枠の上に表示）
	{
		DrawStr str2(_T("モード説明"), { textBoxX+10, textBoxY-10 }, 0x00FFFF);
		str2.Draw(Anchor::LD, fontMenu[0].GetFont());

		// 説明文枠の枠線（水色）	
		Box box = { DBL_XY(textBoxX, textBoxY), DBL_XY(textBoxWidth, textBoxHeight), mColor.frame};
		DrawBoxKR(box, Anchor::LU, false);

		//説明文用.
		DrawStr str(_T(""), INT_XY(textBoxX, textBoxY)+mLayout.loreInner, mColor.normal);

		switch (selectedIndex)
		{
			case 0:
			{
				MY_STRING texts[] = {
					_T("ゲームオーバーになるまで続くエンドレスモード。"),
					_T("ハイスコアを目指して頑張ろう！"),
					_T(""),
					_T("[スコア]"),
					_T("隕石を壊す　　: +500"),
					_T("アイテムを取る: +100"),
					_T("タイムボーナス: 1秒ごとに +10")
				};
				//1行ずつ表示.
				for (auto& i : texts) {
					str.text = i;
					str.Draw(Anchor::LU, fontMenu[0].GetFont());
					str.pos.y += mLayout.loreLineSpace; //次の行へ.
				}
			}
			break;

			case 1:
			{
				MY_STRING texts[] = {
					_T("基本操作とルールを確認できます。"),
					_T("STEP1～4まであり、目安は数分で終わります。"),
					_T(""),
					_T("STEP1: 基本について"),
					_T("STEP2: アイテムについて"),
					_T("STEP3: 反射について"),
					_T("STEP4: スコアについて")
				};
				//1行ずつ表示.
				for (auto& i : texts) {
					str.text = i;
					str.Draw(Anchor::LU, fontMenu[0].GetFont());
					str.pos.y += mLayout.loreLineSpace; //次の行へ.
				}
			}
			break;

		case 2:
			str.text = _T("タイトル画面に戻ります。");
			str.Draw(Anchor::LU, fontMenu[0].GetFont());
			break;
		}
	}
}

//カーソル移動時の処理.
void MenuScene::OnCursorMove() {

	isBlink = true;  //点滅させる.
	tmBlink.Start(); //点滅時間計測.

	//サウンド.
	if (auto i = SoundMng::Get("MenuCursor")) {
		i->Play(false, 70);
	}
}