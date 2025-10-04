/*--------------------------------------------------------/
   - REFLECT LINE -

   (日本語表記: リフレクトライン)
   (略称　　　: REFLINE/リフライン)
/---------------------------------------------------------/
   TODOメモ

   2025/05/20:
   仮でスローモードを実装したが、レーザーの動きが怪しい。
   
   2025/05/26:
   スローモード完成。レーザーの動きの怪しさも解決。
   ・アイテムの実装
   ・スローモードの時間制限 <<< now
   ・障害物4の砲台を画面一周動かす(ゲーム時間??秒以降)

   2025/06/02:
   スローモードの解除まで完成。
   ・アイテムの落下速度、定数いじっても変わらない。
   ・とる、こわすをどうするか考える。

   2025/06/09:
   "こわす"の方針決定。
   
   1.線で構成された多角形の隕石が定期的に降ってくる(全方向からランダム)
   2.アイテムを取るとレーザーを反射するようになり、拡散するように飛んでいく。
   3.近くに隕石がある場合、隕石に向かって飛んでいく。
   4.反射したレーザーが隕石に当たると壊れる(可能なら壊れるアニメーションを入れたい)
   課題点: どうやって隕石の座標を取得するか.

   小田島 →レーザーの反射
   黒澤　 →線で構成された多角形の隕石

   [余裕があれば]
   ・FPSはm秒待機ではなく、時間計測で測りたい

   2025/06/23:
   仮で隕石が降るのを作ったが、正常かどうかが怪しい。
   特にisSlowによりスローになる所でdouble型にうまくキャストできておらず
   一旦全ての速度調整をしてる所を確認したい。

   2025/06/26:
   隕石は大体正常にできたと思われる。
   レーザーの発射を、三角形の敵の先端から出るようにできたら良さそう。
   打つ方向に三角形を回転させる。

   2025/06/30:
   仮で多角形は完成した。
   ただ辺がうまく繋がらないため、そのロジックだけ見直す。
   (頂点の位置を回転を使って測れば行ける気がする)

   2025/07/14:
   あまり進捗なし。反射レーザーの回転問題は一旦直したが、挙動は怪しい。
   前期発表会までにこの辺はやっておきたい
   ・隕石が壊れる時、構成してる線がバラバラになるようにする
   ・追尾レーザーとは別に、直線レーザーを追加する
   ・サウンド関係

   2025/07/15:
   反射仮完成。このゲームの方針も見えてきた。
   「隕石を破壊するとスコアを得られ、そのスコアを競うゲーム」で行ける気がする。

   2025/08/02:
   UIに背景画像を仮で追加したが、端の方を透過させたい。

   2025/08/04:
   Exステージ実装してもいいかも。
   特定の条件で行くことができて、特別なルールがある感じで。
   特別感のあるBGMや背景に変える。

   2025/08/23:
   新障害物「花火」を追加する。Level4で登場予定。
   詳しくは後日相談, なおとに作ってもらう?

   2025/08/27:
   開始時、操作方法分岐を入れて以後の説明文を変えたい。
   ・KEY_SPACE を押したら⇒Push SPACE (キーボード操作)
   ・PAD_XBOX_Aを押したら⇒Push A     (パッド操作)
   など。

   2025/09/08:
   ・花火のバグ修正(スローモードに対応してない, たまに不発する)
   ・配列をvectorに変える。最初にreserveで必要分確保し、デストラクタで解放すればいい。
   ・Calc.hのCalcクラスはなくていい。関数群として置き、KR_Lib名前空間内にCalcという名前空間を置けばOK。

   2025/09/09:
   ・ゲームオーバー画面にヒントが1文出るやつを作りたい。そこでルール説明の補間をする。

   2025/09/16:
   タイトルからメニューに行くとき、パッと画面を変えずにフェードアウトで滑らかに移動するようにしたい。

   2025/09/21:
   [進捗]
   ・反射モードのスローになるタイミングを変更
   ・スローモードの対応を「speedRate」をかけるだけで良くしたこと
   　旧: counter -= (p_data->isSlow) ? SLOW_MODE_SPEED : 1;
	 新: counter -= p_data->speedRate;
   [改善点]
   ・LevelUp演出, Step演出もエフェクトのため、エフェクトが上限まで出てると表示が出なくなる問題

/---------------------------------------------------------/
   [チュートリアル配分]
   step1: 移動, よける
   step2: アイテム
   step3: 反射モード
   step4: スコア

   [現在のLevel配分]
   Level1: 通常レーザー×2, 隕石
   Level2: 直線レーザー×2
   Level3: 波紋
   Level4: 花火, アイテム×2
   Level5: 通常レーザー×4, アイテムが強化
/---------------------------------------------------------/
   TGS展示後、変更内容メモ
   
   ・レーザーの先端が光るように
   ・若干プレイヤーを拡大
   ・プレイヤーの当たり判定を、レーザーが反射する時のみ大きくなるように(違和感がない程度)
   ・レーザーにかなり接近した時のみスローになるように調整
   ・反射モード中、継続中だと分かりやすくなるよう画面にグラデーションを追加
   ・強化アイテムは発光するように
/---------------------------------------------------------/
   【今後の制作予定】

   こわす発表まで:
   ・障害物「花火」追加
   ・タイトルロゴ変更(ゲーム名変更のため)

   TGS展示まで:
   ・開始時の操作方法分岐(できれば)
   ・ゲーム内チュートリアル
   ・SCOREランキング実装
   ・ポスターver2 & アンケート作る
   
   最終目標:
   ・SCORE世界ランキング化
   ・steam販売

   [BGM]
   youtube「Tak_mfk」から使用。
   steam販売の時にはライセンスに注意。
   
   [実績案]
   ・直線レーザー
     耐久モードでLevel2に到達する
   ・波紋
   　耐久モードでLevel3に到達する
   ・花火
   　耐久モードでLevel4に到達する
   ・大波乱
   　耐久モードでLevel5に到達する
   ・即死王
   　耐久モードでゲームオーバー時にスコアを20点未満にする
   ・発売年
     耐久モードでゲームオーバー時にスコアを2025点にする
   ・チュートリアルマスター
   　チュートリアルモードSTEP4でスコアを3000点獲得する
   ・サバイバルマスター
     耐久モードでアイテムを取らずにスコアを1000点獲得する
   ・スーパーサバイバルマスター
	 耐久モードでアイテムを取らずにスコアを1500点獲得する
   ・REFLECT LINE
     レーザー反射数が計10000回を超える
/--------------------------------------------------------*/
/*
   - GameManager.cpp -
   ゲーム全体管理.
*/

#include "BackGround.h"
#include "MenuManager.h"
#include "Stage_Tutorial.h"
#include "Stage_Endless.h"

#include "LaserManager.h"
#include "Obst_NormalLaser.h"
#include "Obst_NormalLaserMain.h"
#include "Obst_StraightLaser.h"
#include "Obst_MeteorManager.h"
#include "Obst_Ripples.h"
#include "Obst_Fireworks.h"

#include "Item.h"
#include "Player.h"

#include "EffectManager.h"
#include "UIManager.h"

#include "GameManager.h"

//ポインタ.
GameData         *gameData     = &GameData::GetInst();
BackGround       *bg           = &BackGround::GetInst();
MenuManager      *menuMng      = &MenuManager::GetInst();
TutorialStage    *tutorialStg  = &TutorialStage::GetInst();
EndlessStage     *endlessStg   = &EndlessStage::GetInst();
LaserManager     *laserMng     = &LaserManager::GetInst();
MeteorManager    *meteorMng    = &MeteorManager::GetInst();
Ripples          *ripples      = &Ripples::GetInst();
FireworksManager *fireworksMng = &FireworksManager::GetInst();
ItemManager      *item         = &ItemManager::GetInst();
Player           *player       = &Player::GetInst();
EffectManager    *effectMng    = &EffectManager::GetInst();
UIManager        *uiMng        = &UIManager::GetInst();

using namespace Calc; //計算機能を使用.

//destructor.
GameManager::~GameManager() {
	//解放.
	delete laserNor1;
	delete laserNor2;
	delete laserNor3;
	delete laserNor4;
	delete laserStr[0];
	delete laserStr[1];
}
//初期化(一回のみ行う)
void GameManager::Init() {

	srand((unsigned)time(NULL)); //乱数初期化.
	
	//実体生成.
	laserNor1   = new NormalLaser_1();
	laserNor2   = new NormalLaser_2();
	laserNor3   = new NormalLaser_3();
	laserNor4   = new NormalLaser_4();
	laserStr[0] = new StraightLaser();
	laserStr[1] = new StraightLaser();
	//実体取得.
	p_input = &InputMng::GetInst();
	p_sound = &SoundMng::GetInst();

	//フォント作成.
	gameData->font1 = CreateFontToHandle(NULL, 26, 1);
	gameData->font2 = CreateFontToHandle(NULL, 30, 1, DX_FONTTYPE_ANTIALIASING);
	gameData->font3 = CreateFontToHandle(NULL, 35, 1, DX_FONTTYPE_ANTIALIASING);
	gameData->font4 = CreateFontToHandle(NULL, 40, 1, DX_FONTTYPE_ANTIALIASING);
	//画像読み込み.
	imgLogo[0].  LoadFile(_T("Resources/Images/REFLINEロゴ_一部.png"));
	imgLogo[1].  LoadFile(_T("Resources/Images/REFLINEロゴ.png"));
	imgUI.       LoadFile(_T("Resources/Images/ui_back_best_score.png"));
	imgNewRecord.LoadFile(_T("Resources/Images/new_record.png"));
	imgGameOver. LoadFile(_T("Resources/Images/gameover.png"));
	imgReflect.  LoadFile(_T("Resources/Images/reflect.png"));
	//サウンド読み込み.
	p_sound->LoadFile(_T("Resources/Sounds/bgm/Virtual Terminal.mp3"),	    _T("BGM_Menu"));     //メニューBGM.
	p_sound->LoadFile(_T("Resources/Sounds/bgm/audiostock_1603723.mp3"),	_T("BGM_Tutorial")); //チュートリアルBGM.
	p_sound->LoadFile(_T("Resources/Sounds/bgm/Scarlet Radiance.mp3"),		_T("BGM_Endless"));  //耐久モードBGM.
	p_sound->LoadFile(_T("Resources/Sounds/bgm/命ナキ者ノ詩.mp3"),		    _T("BGM_Over"));     //ゲームオーバーBGM.

	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_461339.mp3"),		_T("ItemUse")); 	 //アイテム発動.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_1116927_cut.mp3"),	_T("CountDown"));	 //カウントダウン.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_63721.mp3"),		_T("PowerDown"));	 //アイテム解除.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_1296254.mp3"),		_T("Laser1"));		 //レーザー(発射)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_1296256.mp3"),		_T("Laser2"));		 //レーザー(強発射)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_218404.mp3"),		_T("Laser3"));		 //レーザー(反射)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_936158.mp3"),		_T("Ripples"));		 //波紋.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_104974.mp3"),		_T("Break"));		 //隕石破壊.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_981051.mp3"),		_T("PlayerDeath"));
	p_sound->LoadFile(_T("Resources/Sounds/se/決定ボタンを押す23.mp3"),		_T("LevelUp"));
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_184924.mp3"),		_T("BestScore"));	 //最高スコア更新.

	//アクション登録.
	p_input->AddAction(_T("GameNext"),  KeyID::Space);  //キー操作.
	p_input->AddAction(_T("GamePause"), KeyID::P);      //キー操作.
#if defined INPUT_CHANGE_ARCADE
	p_input->AddAction(_T("GameNext"),  PadArcadeID::BtnUpper1); //アーケード操作.
	p_input->AddAction(_T("GamePause"), PadArcadeID::BtnUpper2); //アーケード操作.
	p_input->AddAction(_T("GameQuit"),  PadArcadeID::BtnStart);  //アーケード操作.
#else
	p_input->AddAction(_T("GameNext"),  PadXboxID::A);    //コントローラ操作.
	p_input->AddAction(_T("GamePause"), PadXboxID::X);    //コントローラ操作.
	p_input->AddAction(_T("GameQuit"),  PadXboxID::View); //コントローラ操作.
#endif

	//タイマー初期化.
	for(int i = 0; i < SCENE_COUNT; i++){
		tmScene[i] = Timer(TimerMode::CountUp, 0);
	}
	tmGameTime    = Timer(TimerMode::CountUp, 0);
	tmReflectMode = Timer(TimerMode::CountDown, REFLECT_MODE_TIME);

	//Init処理
	{
		//障害物.
		for (int i = 0; i < _countof(laserStr); i++) {
			laserStr[i]->Init();
		}
		laserNor1->Init();
		laserNor2->Init();
		laserNor3->Init();
		laserNor4->Init();

		bg->Init();
		menuMng->Init();
		tutorialStg->Init();
		endlessStg->Init();
		laserMng->Init();
		meteorMng->Init();
		ripples->Init();
		fireworksMng->Init();
		item->Init();
		player->Init();
		effectMng->Init();
		uiMng->Init();
	}

	//スコア読み込み.
	{
		File file;
		file.Open(FILE_DATA, _T("r"));        //ファイルを開く.
		gameData->bestScore = file.ReadInt(); //数字を読み込んで登録.

		uiMng->SetDisBestScore(gameData->bestScore); //ベストスコア表示更新.
	}

	Reset();
}

//リセット(何回でも行う)
void GameManager::Reset() {

	//データ.
	gameData->scoreBef      = 0;
	gameData->score         = 0;
	gameData->counter       = 0;
	gameData->speedRate     = 1.0;   //通常は100%
	gameData->spawnRate     = 1.0;   //最初は100%
	gameData->level         = 1;     //最初はLv1
	gameData->isReflectMode = false; //最初はLv1
	isTitleAnim             = false;
	isBestScoreSound        = false;
	isGameStart             = false;
	isBestScore             = false;
	for (int i = 0; i < 3; i++) {
		isItemCountDownSound[i] = false;
	}
	//タイマー.
	for (int i = 0; i < SCENE_COUNT; i++) {
		tmScene[i].Reset();
	}
	tmGameTime.Reset();
	tmReflectMode.Reset();

	//サウンド.
	p_sound->StopAll();
	p_sound->Play(_T("BGM_Menu"), true, 90); //メニューBGMを流す.

	{
		//レーザー系.
		ResetNorLaser();
		ResetStrLaser();

		menuMng->Reset();
		tutorialStg->Reset();
		laserMng->Reset();
		meteorMng->Reset();
		ripples->Reset();
		fireworksMng->Reset();
		item->Reset();
		player->Reset({ WINDOW_WID/2, WINDOW_HEI/2+250 }, true);
		effectMng->Reset();
		uiMng->Reset();
	}
}

//更新.
void GameManager::Update() {

	p_input->UpdateKey();    //キー入力更新.
	p_input->UpdatePad();    //コントローラ入力更新.
	p_input->UpdateAction(); //アクション更新.
	p_sound->Update();       //サウンド更新.

	//ポーズしてなければ.
	if (gameData->scene != SCENE_PAUSE) {
		bg->Update();        //背景.
		effectMng->Update(); //エフェクト.
	}
	//シーン別.
	switch (gameData->scene) 
	{
		case SCENE_TITLE: UpdateTitle(); break;
		case SCENE_MENU:  UpdateMenu();  break;
		case SCENE_GAME:  UpdateGame();  break;
		case SCENE_END:   UpdateEnd();   break;
		case SCENE_PAUSE: UpdatePause(); break;
	
		default: assert(FALSE); break;
	}

	//特定の操作でゲーム終了
	if (p_input->IsPushActionTime(_T("GameQuit")) >= FPS * 1) {
		App::GetInst().Quit(); //ボタン長押しで終了.
	}
	else if (p_input->IsPushKey(KeyID::Esc)) {
		App::GetInst().Quit(); //ESCAPEキーを押したら即終了.
	}
}

//描画.
void GameManager::Draw() {

	bg->Draw(); //背景.

	//シーン別.
	switch (gameData->scene) 
	{
		case SCENE_TITLE: DrawTitle(); break;
		case SCENE_MENU:  DrawMenu();  break;
		case SCENE_GAME:  DrawGame();  break;
		case SCENE_END:   DrawEnd();   break;
		case SCENE_PAUSE: DrawPause(); break;

		default: assert(FALSE); break;
	}

	effectMng->Draw(); //エフェクト.
}

//通常レーザーのリセット.
void GameManager::ResetNorLaser() {

	laserNor1->Reset(WINDOW_WID/2, 0, 3, MOVE_RIGHT);
	laserNor2->Reset(WINDOW_WID/2, 0, 3, MOVE_LEFT);
	laserNor3->Reset(WINDOW_WID/2, WINDOW_HEI, 3, MOVE_RIGHT);
	laserNor4->Reset(WINDOW_WID/2, WINDOW_HEI, 3, MOVE_LEFT);
}
//直線レーザーのリセット.
void GameManager::ResetStrLaser() {

	for (int i = 0; i < _countof(laserStr); i++) {
		laserStr[i]->Reset();
	}
}

//シーン別更新.
void GameManager::UpdateTitle()
{
	//シーンタイマー開始.
	if (!tmScene[SCENE_TITLE].GetIsMove()) {
		tmScene[SCENE_TITLE].Start();
	}

	//特定の操作でゲーム開始.
	if (p_input->IsPushActionTime(_T("GameNext")) == 1) {
		gameData->scene = SCENE_MENU; //メニューシーンへ.
	}
}
void GameManager::UpdateMenu() {
	menuMng->Update();
}
void GameManager::UpdateGame() {

	//シーンタイマー開始.
	if (!tmScene[SCENE_GAME].GetIsMove()) {
		tmScene[SCENE_GAME].Start();
	}

	//ゲーム開始前.
	if (!isGameStart) {
		//一定時間経ったら.
		if (tmScene[SCENE_GAME].GetPassTime() >= GAME_START_TIME) {

			tmGameTime.Start(); //ゲーム時間計測開始.
			isGameStart = true; //ゲーム開始.
		}
	}
	//ゲーム開始後.
	else{

		UpdateReflectMode(); //反射モード.

		//ステージ別.
		switch (gameData->stage) 
		{
			case STAGE_TUTORIAL: tutorialStg->Update(); break;
			case STAGE_ENDLESS:  endlessStg->Update();  break;

			default: assert(FALSE); break;
		}
		//ポーズ.
		if (p_input->IsPushActionTime(_T("GamePause")) == 1) {
			gameData->scene = SCENE_PAUSE;
			tmGameTime.Stop();    //一時停止.
			tmReflectMode.Stop(); //一時停止.
		}
	}

	player->Update(); //プレイヤー.
}
void GameManager::UpdateEnd() {

	//シーンタイマー開始.
	if (!tmScene[SCENE_END].GetIsMove()) {
		tmScene[SCENE_END].Start();
	}

	//チュートリアルの場合.
	if (gameData->stage == STAGE_TUTORIAL) {

		UpdateGame(); //ゲームシーンと同じ動作をする.

		//死亡後一定時間経過したら.
		if (tmScene[SCENE_END].GetPassTime() >= TUTORIAL_RESPAWN_TIME) {
			tmScene[SCENE_END].Reset();   //タイマーリセット.
			player->PlayerRevival();      //復活.
			gameData->scene = SCENE_GAME; //ゲームシーンへ戻る.
		}
	}
	//チュートリアル以外の場合.
	else {
		//特定の操作でタイトルへ.
		if (p_input->IsPushActionTime(_T("GameNext")) == 1)
		{
			gameData->scene = SCENE_TITLE;
			uiMng->SetDisBestScore(gameData->bestScore); //ベストスコア表示更新.
			Reset();
		}
	}
}
void GameManager::UpdatePause() {
	
	//ポーズ解除.
	if (p_input->IsPushActionTime(_T("GamePause")) == 1) {

		gameData->scene = SCENE_GAME;
		tmGameTime.Start(); //再開.
		//スローモード中だったなら.
		if (tmReflectMode.GetPassTime() < REFLECT_MODE_TIME) {
			tmReflectMode.Start(); //再開.
		}
	}
}

//反射モードの更新.
void GameManager::UpdateReflectMode() {

	//反射モード時間判定.
	if (gameData->slowBufCntr > 0) {
		gameData->speedRate = SLOW_MODE_SPEED; //速度倍率を遅くする.
		gameData->slowBufCntr--;               //カウントを減らす.
	}
	else {
		gameData->speedRate = 1.0; //速度倍率を戻す.
	}

	//反射モード中.
	if (tmReflectMode.GetIsMove()) {
		//3秒以下になったばかりの時.
		if (tmReflectMode.GetPassTime() <= 3) {
			if (!isItemCountDownSound[2]) {
				p_sound->Play(_T("CountDown"), false, 78); //再生.
				isItemCountDownSound[2] = true;
			}
		}
		//2秒以下になったばかりの時.
		if (tmReflectMode.GetPassTime() <= 2) {
			if (!isItemCountDownSound[1]) {
				p_sound->Play(_T("CountDown"), false, 78); //再生.
				isItemCountDownSound[1] = true;
			}
		}
		//1秒以下になったばかりの時.
		if (tmReflectMode.GetPassTime() <= 1) {
			if (!isItemCountDownSound[0]) {
				p_sound->Play(_T("CountDown"), false, 78); //再生.
				isItemCountDownSound[0] = true;
			}
		}
		//時間切れで解除.
		if (tmReflectMode.GetPassTime() <= 0) {
			ReflectModeEnd();
		}
	}
}

//シーン別描画.
void GameManager::DrawTitle() {

	//アニメーション切り替わりポイント.
	const float delay1 = 1;
	const float delay2 = 1.4f;
	const float delay3 = 1.6f;
	const float delay4 = 3;
	const float delay5 = 3;

	//画像の表示.
	{
		const int    logoY   = WINDOW_HEI/2 - 85;
		const DBL_XY imgSize = {0.7, 0.7};
	
		//切り替え前.
		if (tmScene[SCENE_TITLE].GetPassTime() < delay1) {
			//アニメーション値.
			double anim = CalcNumEaseInOut(tmScene[SCENE_TITLE].GetPassTime()/delay1);
			//ロゴ1枚目.
			SetDrawBlendModeKR(BlendModeID::Alpha, 255 * anim);
			imgLogo[0].DrawExtend({WINDOW_WID/2, logoY}, imgSize, Anchor::Mid, true, true);
		}
		//切り替え後.
		else {
			//アニメーション値.
			double anim1 = CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay1    )/1.8);
			double anim2 = CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay1-0.4)/1.8); //少し遅延あり.
			//ロゴ1枚目.
			SetDrawBlendModeKR(BlendModeID::Alpha, 255 * (1-anim2));
			imgLogo[0].DrawExtend({WINDOW_WID/2, logoY - anim1*100}, imgSize, Anchor::Mid, true, true);
			//ロゴ2枚目.
			SetDrawBlendModeKR(BlendModeID::Alpha, 255 * anim1);
			imgLogo[1].DrawExtend({WINDOW_WID/2, logoY - anim1*100}, imgSize, Anchor::Mid, true, true);
		}
		//描画モードリセット.
		ResetDrawBlendMode();
	}

#if defined SHOW_BEST_SCORE
	//best score.
	if (tmScene[SCENE_TITLE].GetPassTime() >= delay2) {

		const int drawY = WINDOW_HEI/2 + 130;

		//アニメーション値.
		double anim1 = CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay3)/1.5);
		double anim2 = CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay2)/1.5);
		//テキスト.
		TCHAR text[256];
		_stprintf(text, _T("BEST SCORE: %d"), gameData->bestScore); //ベストスコア.
		DrawStr str(text, {WINDOW_WID/2, drawY+1}, COLOR_BEST_SCORE);

		SetDrawBlendModeKR(BlendModeID::Alpha, 255*anim1);
		str.Draw(Anchor::Mid, gameData->font2); //スコア値.
		SetDrawBlendModeKR(BlendModeID::Alpha, 255*anim2);
		imgUI.DrawExtend({WINDOW_WID/2, drawY + (10+18*anim2)}, {0.45, 0.4}, Anchor::Mid, true, true);
		imgUI.DrawExtend({WINDOW_WID/2, drawY - (10+18*anim2)}, {0.45, 0.4}, Anchor::Mid, true, true);
		ResetDrawBlendMode();
	}
#endif
	//PUSH SPACE.
	if (tmScene[SCENE_TITLE].GetPassTime() >= delay4) {

		const int drawY = WINDOW_HEI/2+310;

		//アニメーション値.
		double anim = CalcNumWaveLoop(tmScene[SCENE_TITLE].GetPassTime()-delay4);
		//テキスト.
		DrawStr str(_T("Push SPACE or Ⓐ"), {WINDOW_WID/2-5, drawY}, 0xFFFFFF);
		
		SetDrawBlendModeKR(BlendModeID::Alpha, 255*anim);
		str.Draw(Anchor::Mid, gameData->font1); //テキスト.
		ResetDrawBlendMode();
	}
	//隕石破壊アニメーション.
	if (!isTitleAnim) {
		if (tmScene[SCENE_TITLE].GetPassTime() >= delay5) {

			EffectData data{};
			data.type  = Effect_BreakMeteor;
			data.pos   = { 584, 290 };

			double dig = -130; //角度.

			//エフェクトをいくつか出す.
			for (int i = 0; i < METEOR_BREAK_ANIM_CNT; i++) {

				double newDig = dig + (float)RandNum(-300, 300)/10; //少し角度をずらす.
				data.vec   = CalcVectorDeg(newDig);                 //ずらした角度を反映.
				data.speed = ((float)RandNum(20, 100)/10) * 1.4f;   //速度抽選.
				data.len   = ((float)RandNum(10, 150)/10) * 1.4f;   //長さ抽選.
				data.ang   =  (float)RandNum(0, 3599)/10;           //角度抽選.
				effectMng->SpawnEffect(&data);                      //エフェクト召喚.
			}
			//サウンド.
			p_sound->Play(_T("Break"), false, 65);

			isTitleAnim = true;
		}
	}
}
void GameManager::DrawMenu() {
	menuMng->Draw();
}
void GameManager::DrawGame() {

	player->Draw();     //プレイヤー.
	DrawReflectMode();  //反射モード演出.
	uiMng->Draw();      //UI.

	//ゲームが開始したら.
	if (isGameStart) {
		//ステージ別.
		switch (gameData->stage)
		{
			case STAGE_TUTORIAL: tutorialStg->Draw(); break;
			case STAGE_ENDLESS:  endlessStg->Draw();  break;

			default: assert(FALSE); break;
		}
	}
}
void GameManager::DrawEnd() {
	
	//ステージ別.
	switch (gameData->stage) 
	{
		case STAGE_TUTORIAL: tutorialStg->Draw(); break;
		case STAGE_ENDLESS:  endlessStg->Draw();  break;

		default: assert(FALSE); break;
	}
	//黒フィルター.
	{
		float anim = CalcNumEaseInOut(tmScene[SCENE_END].GetPassTime()); //アニメーション値.
		Box box = { {0, 0}, {WINDOW_WID, WINDOW_HEI}, 0x000000 };

		SetDrawBlendModeKR(BlendModeID::Alpha, 128*anim);
		DrawBoxKR(&box, Anchor::LU); //画面を暗くする(UI以外)
		ResetDrawBlendMode();
	}
	uiMng->Draw(); //UI.

	//チュートリアルの場合.
	if (gameData->stage == STAGE_TUTORIAL) {
		
		//アニメーション値.
		double anim = CalcNumEaseOut(tmScene[SCENE_END].GetPassTime());
		//テキスト.
		DrawStr str(_T("チュートリアルではその場で復活します..."), {WINDOW_WID/2, WINDOW_HEI/2}, 0x00FFFF);

		SetDrawBlendModeKR(BlendModeID::Alpha, 255 * anim);

		//GAME OVER
		imgGameOver.DrawExtend({WINDOW_WID/2, 370+30*anim}, {0.5, 0.5}, Anchor::Mid, true, true);
		//テキスト.
		str.Draw(Anchor::Mid, gameData->font2);

		ResetDrawBlendMode();
	}
	//チュートリアル以外の場合.
	else {
		//終了案内.
		{
			//アニメーション値.
			double anim = CalcNumEaseOut(tmScene[SCENE_END].GetPassTime());

			//スコア表示.
			TCHAR text[256];
			_stprintf(
				text, _T("%d + %d(%.3f秒) = %d点"),
				gameData->scoreBef, _int(tmGameTime.GetPassTime() * 10), tmGameTime.GetPassTime(), gameData->score
			);
			//テキストの設定.
			DrawStr str1(_T("Time Bonus"), {WINDOW_WID/2, WINDOW_HEI/2-20}, 0xFFFFFF);
			DrawStr str2(text,             {WINDOW_WID/2, WINDOW_HEI/2+20}, 0xFFFFFF);

			SetDrawBlendModeKR(BlendModeID::Alpha, 255*anim);
			imgGameOver.DrawExtend({WINDOW_WID/2, 370+30*anim}, {0.5, 0.5}, Anchor::Mid, true, true); //GAME OVER
			//画面中央に文字を表示.
			str1.Draw(Anchor::Mid, gameData->font1);
			str2.Draw(Anchor::Mid, gameData->font1);
			ResetDrawBlendMode();
		}

		const float delay1 = 1.2f;
		const float delay2 = 1.5f;

		//一定時間が経ったら.
		if (tmScene[SCENE_END].GetPassTime() > delay1) {
			//ベストスコア更新.
			if (isBestScore) {

				//アニメーション値.
				double anim = CalcNumEaseOut((tmScene[SCENE_END].GetPassTime()-delay1)*2);
				//描画.
				SetDrawBlendModeKR(BlendModeID::Alpha, 255*anim);
				imgNewRecord.DrawExtend({WINDOW_WID/2, WINDOW_HEI/2-330+anim*20}, {0.4, 0.4}, Anchor::Mid, true, true); //NEW RECORD
				ResetDrawBlendMode();
				//サウンド.
				if (!isBestScoreSound) {
					p_sound->Play(_T("BestScore"), false, 65);
					isBestScoreSound = true; //一度のみ.
				}
			}
		}
		//一定時間が経ったら.
		if (tmScene[SCENE_END].GetPassTime() > delay2) {
		
			//アニメーション値.
			double anim = CalcNumWaveLoop(tmScene[SCENE_END].GetPassTime()-delay2);
			//テキスト.
			DrawStr str(_T("Push SPACE or Ⓐ"), {WINDOW_WID/2-5, WINDOW_HEI/2+145}, 0xFFFFFF);
		
			SetDrawBlendModeKR(BlendModeID::Alpha, 255*anim);
			str.Draw(Anchor::Mid, gameData->font1); //テキスト.
			ResetDrawBlendMode();
		}
	}
}
void GameManager::DrawPause() {

	DrawGame(); //ゲームシーンと同じ.
}

//反射モード演出.
void GameManager::DrawReflectMode() {

	//カウントダウン中.
	if (tmReflectMode.GetIsMove() && tmReflectMode.GetPassTime() > 0)
	{
		//テキストの設定.
		TCHAR text[256];
		_stprintf(text, _T("%d"), (int)ceil(tmReflectMode.GetPassTime())); //TCHAR型に変数を代入.
		DrawStr str(text, {WINDOW_WID/2, WINDOW_HEI/2}, COLOR_ITEM);

		//画面中央に数字を表示.
		{
			double dec  = GetDecimal(tmReflectMode.GetPassTime()); //小数だけ取り出す.
			double anim = CalcNumEaseOut(dec);
			
			SetDrawBlendModeKR(BlendModeID::Alpha, _int_r(255 * dec)); //1秒ごとに薄くなる演出.
			//最初の1秒.
			if (tmReflectMode.GetPassTime() > REFLECT_MODE_TIME-1) {
				imgReflect.DrawExtend({WINDOW_WID/2, WINDOW_HEI/2}, {0.3+0.2*anim, 0.3+0.2*anim});
			}
			//最後の3秒.
			if (tmReflectMode.GetPassTime() <= 3) {
				str.Draw(Anchor::Mid, gameData->font4); //数字.
			}
			ResetDrawBlendMode();
		}
	}
}

//ゲーム終了(死亡)
void GameManager::GameOver() {

	//ステージ別.
	switch (gameData->stage)
	{
		case STAGE_TUTORIAL:
		{
			gameData->scene = SCENE_END; //ゲーム終了へ.
		}
		break;

		case STAGE_ENDLESS:
		{
			//まだ終わってないなら(念のため2重実行されることを防ぐ)
			if (gameData->scene != SCENE_END) {
				gameData->scene = SCENE_END; //ゲーム終了へ.
	
				tmGameTime.Stop(); //停止.
				tmReflectMode.Reset();
				gameData->speedRate = 1.0; //速度倍率を100%に戻す.

				//記録リセット.
				for (int i = 0; i < _countof(isItemCountDownSound); i++) {
					isItemCountDownSound[i] = false;
				}

				gameData->scoreBef = gameData->score;                   //時間加算前のスコアを記録.
				gameData->score += _int(tmGameTime.GetPassTime() * 10); //時間ボーナス加算.

				//最高スコア更新なら.
				if (gameData->score > gameData->bestScore) {

					File file;
					file.MakeDir(FILE_DATA_PATH);   //フォルダ作成.
					file.Open(FILE_DATA, _T("w"));  //ファイルを開く.
					file.WriteInt(gameData->score); //スコアを保存.

					gameData->bestScore = gameData->score; //スコア更新.
					isBestScore = true;
				}

				//BGM停止.
				p_sound->FadeOutPlay(_T("BGM_Endless"), 2);
				//ゲームオーバーBGM.
				p_sound->Play(_T("BGM_Over"), true, 68);
			}
			break;

			default: assert(FALSE); break;
		}
	}
}
//アイテムを使用した時.
void GameManager::ItemUsed() {

	gameData->isReflectMode = true; //反射モードにする.
	tmReflectMode.Start();          //反射モード計測開始.

	//記録リセット.
	for (int i = 0; i < _countof(isItemCountDownSound); i++) {
		isItemCountDownSound[i] = false;
	}

	//チュートリアルなら指示送信.
	if (gameData->stage == STAGE_TUTORIAL) {
		tutorialStg->SetTakeItem(true);       //指示を送る.
		tutorialStg->SetReflectFinish(false); //falseにする(指示取り消し)
	}
}
//反射モード終了.
void GameManager::ReflectModeEnd() {

	tmReflectMode.Reset();

	gameData->isReflectMode = false; //反射モード解除.
	gameData->speedRate     = 1.0;   //速度倍率を100%に戻す.
	gameData->slowBufCntr   = 0;     //カウンターを0に.
	player->SetMode(Player_Normal);  //通常状態に戻す.
			
	p_sound->Play(_T("PowerDown"), false, 78); //再生.
	
	//記録リセット.
	for (int i = 0; i < _countof(isItemCountDownSound); i++) {
		isItemCountDownSound[i] = false;
	}

	//チュートリアルなら指示送信.
	if (gameData->stage == STAGE_TUTORIAL) {
		tutorialStg->SetReflectFinish(true); //指示を送る.
	}
}