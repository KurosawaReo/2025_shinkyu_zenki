/*
   - GameManager.cpp -
   ゲーム全体管理.
*/
/*--------------------------------------------------------/
   [TODO]
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

   前期発表会後: 変更内容
   ・UIレイアウトの変更。"BEST SCORE","SCORE","TIME"の3つだけにした。
   ・アイテムの終了が分かりやすくなるよう、数字を3秒だけ表示して音を足した。
   ・ポーズ機能仮追加。(Pキー)
   ・図形や線のアンチエイリアス導入, より滑らかな描画が可能に。
   ・レーザーで短すぎる線を描画しないように。(処理軽減に繋がる)
   ・隕石の破片の飛び散り方を調整
   ・反射レーザーが隕石に当たっても反射するように
/--------------------------------------------------------*/

#include "MeteoManager.h"
#include "LaserManager.h"
#include "EffectManager.h"

#include "Obstacle4.h"
#include "Obstacle4main.h"
#include "Obstacle5.h"
#include "MapGimmickLaser.h"

#include "Item.h"
#include "Player.h"

#include "GameManager.h"

//管理クラスの実体.
MeteoManager  meteoMng;
LaserManager  laserMng;
EffectManager effectMng;
//障害物の実体.
Obstacle4_1 obstacle4_1;
Obstacle4_2 obstacle4_2;
Obstacle4_3 obstacle4_3;
Obstacle4_4 obstacle4_4;
Obstacle5   obstacle5;
MapGimmickLaser mgl[2];
//アイテムの実体.
Item item;
//プレイヤーの実体.
Player player;

//初期化(一回のみ行う)
void GameManager::Init() {

	srand((unsigned)time(NULL)); //乱数初期化.
	
	p_input = InputST::GetPtr();
	p_sound = SoundST::GetPtr();
	
	//タイトル.
	data.scene = SCENE_TITLE;
	//フォント作成.
	data.font1 = CreateFontToHandle(NULL, 26, 1);
	data.font2 = CreateFontToHandle(NULL, 30, 1, DX_FONTTYPE_ANTIALIASING);
	data.font3 = CreateFontToHandle(NULL, 40, 1, DX_FONTTYPE_ANTIALIASING);
	//画像読み込み.
	imgLogo[0].LoadGraphST(_T("Resources/Images/REFLINEロゴ_一部.png"));
	imgLogo[1].LoadGraphST(_T("Resources/Images/REFLINEロゴ.png"));
	imgUI.     LoadGraphST(_T("Resources/Images/testUI.png"));
	//サウンド読み込み.
	p_sound->LoadFile(_T("Resources/Sounds/bgm/Scarlet Radiance.mp3"),		_T("BGM1"));
	p_sound->LoadFile(_T("Resources/Sounds/bgm/audiostock_1603723.mp3"),	_T("BGM2"));		//未使用(BGM候補)
	p_sound->LoadFile(_T("Resources/Sounds/bgm/GB_Shooting_2025.0725.mp3"),	_T("BGM3"));
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_461339.mp3"),		_T("TakeItem"));	//アイテム取る.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_1116927_cut.mp3"),	_T("CountDown"));	//カウントダウン.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_63721.mp3"),		_T("PowerDown"));	//アイテム解除.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_1296254.mp3"),		_T("Laser1"));		//レーザー(発射)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_1296256.mp3"),		_T("Laser2"));		//レーザー(強発射)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_218404.mp3"),		_T("Laser3"));		//レーザー(反射)
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_936158.mp3"),		_T("Ripples"));		//波紋.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_104974.mp3"),		_T("Break"));		//隕石破壊.
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_981051.mp3"),		_T("PlayerDeath"));
	p_sound->LoadFile(_T("Resources/Sounds/se/決定ボタンを押す23.mp3"),		_T("LevelUp"));
	p_sound->LoadFile(_T("Resources/Sounds/se/audiostock_184924.mp3"),		_T("BestScore"));	//最高スコア更新.
	//Init処理
	{
		//管理class.
		laserMng.Init(&data, &player, &meteoMng, &effectMng);
		meteoMng.Init(&data, &player, &effectMng);
		effectMng.Init(&data);
		//障害物class.
		mgl[0].Init(&data, &player, &laserMng, &meteoMng);
		mgl[1].Init(&data, &player, &laserMng, &meteoMng);
		obstacle4_1.Init(&data, &player, &meteoMng, &laserMng);
		obstacle4_2.Init(&data, &player, &meteoMng, &laserMng);
		obstacle4_3.Init(&data, &player, &meteoMng, &laserMng);
		obstacle4_4.Init(&data, &player, &meteoMng, &laserMng);
		obstacle5.Init(&data, &player);
		//アイテムclass.
		item.Init(&data, &player, &effectMng);
		//プレイヤーclass.
		player.Init(&data, &effectMng);
	}

	//スコア読み込み.
	{
		FileST file;
		int ret = file.Open(FILE_DATA_PATH, _T("r")); //ファイルを開く.
		data.bestScore = file.ReadInt();    //数字を読み込んで登録.
	}

	Reset();
}

//リセット(何回でも行う)
void GameManager::Reset() {

	if (data.bestScore < data.score) {
		data.bestScore = data.score; //ハイスコア記録.
	}

	//リセット.
	data.scoreBef = 0;
	data.score = 0;
	data.isSlow = FALSE;
	data.counter = 0;
	data.spawnRate = 1.0; //最初は100%
	data.level = 1;       //最初はLv1
	isFinTitleAnim = FALSE;
	isFinScoreAnim = FALSE;
	//サウンド.
	p_sound->Stop(_T("BGM1"));
	p_sound->Play(_T("BGM1"), TRUE, 68);
	//タイマー.
	tmScene[SCENE_TITLE].Start();
	tmScene[SCENE_READY].Reset();
	tmScene[SCENE_GAME].Reset();
	tmScene[SCENE_END].Reset();

	{
		//管理class.
		laserMng.Reset();
		meteoMng.Reset();
		effectMng.Reset();
		//障害物class.
		mgl[0].Reset();
		mgl[1].Reset();
		ResetNorLaser();
		obstacle5.Reset();
		//アイテムclass.
		item.Reset();
		//プレイヤーclass.
		player.Reset({ WINDOW_WID/2, WINDOW_HEI/2+185 }, TRUE);
	}
}

//更新.
void GameManager::Update() {

	p_input->UpdateKey(); //キー入力更新.
	p_input->UpdatePad(); //コントローラ入力更新.
	p_sound->Update();    //サウンド更新.

	//シーン別.
	switch (data.scene) 
	{
		case SCENE_TITLE: UpdateTitle(); break;
		case SCENE_READY: UpdateReady(); break;
		case SCENE_GAME:  UpdateGame();  break;
		case SCENE_END:   UpdateEnd();   break;
		case SCENE_PAUSE: UpdatePause(); break;
	
		default: assert(FALSE); break;
	}
}

//描画.
void GameManager::Draw() {

	DrawBG();

	//シーン別.
	switch (data.scene) 
	{
		case SCENE_TITLE: DrawTitle(); break;
		case SCENE_READY: DrawReady(); break;
		case SCENE_GAME:  DrawGame();  break;
		case SCENE_END:   DrawEnd();   break;
		case SCENE_PAUSE: DrawPause(); break;

		default: assert(FALSE); break;
	}
}

//通常レーザーのリセット.
void GameManager::ResetNorLaser() {

	obstacle4_1.Reset(WINDOW_WID/2, 0, 3, MOVE_RIGHT);
	obstacle4_2.Reset(WINDOW_WID/2, 0, 3, MOVE_LEFT);
	obstacle4_3.Reset(WINDOW_WID/2, WINDOW_HEI, 3, MOVE_RIGHT);
	obstacle4_4.Reset(WINDOW_WID/2, WINDOW_HEI, 3, MOVE_LEFT);
}

//シーン別更新.
void GameManager::UpdateTitle() 
{
	player.Update();    //プレイヤー.
	effectMng.Update(); //エフェクト.

	//特定の操作でゲーム開始.
	if (p_input->IsPushKeyTime(KEY_SPACE) == 1 || p_input->IsPushPadBtnTime(PAD_BTN_X) == 1)
	{
		tmScene[SCENE_READY].Start(); //タイマー開始.
		data.scene = SCENE_READY;     //準備シーンへ.
	}
}
void GameManager::UpdateReady() {

	player.Update();    //プレイヤー.
	effectMng.Update(); //エフェクト.
	
	//一定時間経ったら.
	if (tmScene[SCENE_READY].GetPassTime() >= GAME_START_TIME) {

		tmScene[SCENE_GAME].Start(); //ゲーム開始.
		data.scene = SCENE_GAME;     //ゲームシーンへ.
//		data.level = 1;              //Lv1にする.

		//サウンド.
		SoundST* sound = SoundST::GetPtr();
		sound->Play(_T("LevelUp"), FALSE, 100);
		//エフェクト.
		EffectData data{};
		data.type = Effect_Level1;
		data.pos = { WINDOW_WID/2, WINDOW_HEI/2 };
		effectMng.SpawnEffect(&data);
	}
}
void GameManager::UpdateGame() {

	//カウンター増加.
	data.counter += ((data.isSlow) ? SLOW_MODE_SPEED : 1);
	//出現間隔.
	data.spawnRate = 1.0f/(1 + (data.counter/8000)); //100%から少しずつ減少.
	//レベル管理.
	switch (data.level) 
	{
		case 1:
			if (data.spawnRate <= 0.85) { //85%以下.
				data.level = 2; //Lv2へ.

				//サウンド.
				SoundST* sound = SoundST::GetPtr();
				sound->Play(_T("LevelUp"), FALSE, 100);
				//エフェクト.
				EffectData data{};
				data.type = Effect_Level2;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);
			}
			break;
		case 2:
			if (data.spawnRate <= 0.65) { //65%以下.
				data.level = 3; //Lv3へ.

				//サウンド.
				SoundST* sound = SoundST::GetPtr();
				sound->Play(_T("LevelUp"), FALSE, 100);
				//エフェクト.
				EffectData data{};
				data.type = Effect_Level3;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);
			}
			break;
		case 3:
			if (data.spawnRate <= 0.5) { //50%以下.
				data.level = 4; //Lv4へ.
				ResetNorLaser();

				//サウンド.
				SoundST* sound = SoundST::GetPtr();
				sound->Play(_T("LevelUp"), FALSE, 100);
				//エフェクト.
				EffectData data{};
				data.type = Effect_Level4;
				data.pos  = {WINDOW_WID/2, WINDOW_HEI/2};
				effectMng.SpawnEffect(&data);
			}
			break;
		case 4:
		case 5:
			//最終レベル.
			break;

		default: assert(FALSE); break;
	}

	//スローモード.
	if (tmSlowMode.GetIsMove()) {
		//3秒以下になったばかりの時.
		if (tmSlowMode.GetPassTime() <= 3){
			if (!isItemCount[2]) {
				p_sound->Play(_T("CountDown"), FALSE, 78); //再生.
				isItemCount[2] = TRUE;
			}
		}
		//2秒以下になったばかりの時.
		if (tmSlowMode.GetPassTime() <= 2) {
			if (!isItemCount[1]) {
				p_sound->Play(_T("CountDown"), FALSE, 78); //再生.
				isItemCount[1] = TRUE;
			}
		}
		//1秒以下になったばかりの時.
		if (tmSlowMode.GetPassTime() <= 1) {
			if (!isItemCount[0]) {
				p_sound->Play(_T("CountDown"), FALSE, 78); //再生.
				isItemCount[0] = TRUE;
			}
		}
		//時間切れで解除.
		if (tmSlowMode.GetPassTime() <= 0) {
			
			player.SetReflectionMode(FALSE); //反射モード終了.
			p_sound->Play(_T("PowerDown"), FALSE, 78); //再生.
			
			//リセット.
			tmSlowMode.Reset();
			data.isSlow = FALSE;
			for (int i = 0; i < _countof(isItemCount); i++) {
				isItemCount[i] = FALSE;
			}
		}
	}

	UpdateObjects();    //オブジェクト.
	player.Update();    //プレイヤー.
	effectMng.Update(); //エフェクト.
	
	//ポーズする.
	if(p_input->IsPushKeyTime(KEY_P) == 1){
		data.scene = SCENE_PAUSE;
		tmScene[SCENE_GAME].Stop(); //一時停止.
		tmSlowMode.Stop();          //一時停止.
	}
}
void GameManager::UpdateEnd() {

	effectMng.Update(); //エフェクト.

	//特定の操作でタイトルへ.
	if (p_input->IsPushKeyTime(KEY_SPACE) == 1 || p_input->IsPushPadBtnTime(PAD_BTN_A) == 1)
	{
		data.scene = SCENE_TITLE; //ゲームシーンへ.
		Reset();
	}
}
void GameManager::UpdatePause() {

	//ポーズ解除.
	if (p_input->IsPushKeyTime(KEY_P) == 1) {

		data.scene = SCENE_GAME;
		tmScene[SCENE_GAME].Start(); //再開.
		//スローモード中だったなら.
		if (tmSlowMode.GetPassTime() < SLOW_MODE_TIME) {
			tmSlowMode.Start(); //再開.
		}
	}
}

//オブジェクトの更新.
void GameManager::UpdateObjects() {

	//Lv1以上.
	laserMng.Update();
	meteoMng.Update();
	obstacle4_1.Update();
	obstacle4_2.Update();
	item.Update();
	//Lv2以上.
	if (data.level >= 2) {
		mgl[0].Update();
		mgl[1].Update();
	}
	//Lv3以上.
	if (data.level >= 3) {
		obstacle5.Update();
	}
	//Lv4以上.
	if (data.level >= 4) {
		obstacle4_3.Update();
		obstacle4_4.Update();
	}
}

//シーン別描画.
void GameManager::DrawTitle() {
	
	player.Draw();    //プレイヤー. 
	effectMng.Draw(); //エフェクト管理.

	//アニメーション切り替わりポイント.
	const float delay1 = 1;
	const float delay2 = 1.6f;
	const float delay3 = 3;
	const float delay4 = 3;

	const int logoY = WINDOW_HEI/2 - 70;

	//画像の表示.
	{	
		//切り替え前.
		if (tmScene[SCENE_TITLE].GetPassTime() < delay1) {
			//アニメーション値.
			double anim = CalcNumEaseInOut(tmScene[SCENE_TITLE].GetPassTime()/delay1);
			//ロゴ1枚目.
			SetDrawBlendModeST(MODE_ADD, 255 * anim);
			imgLogo[0].DrawExtendGraphST(0, {WINDOW_WID/2, logoY}, {0.5, 0.5}, TRUE);
		}
		//切り替え後.
		else {
			//アニメーション値.
			double anim = CalcNumEaseInOut((tmScene[SCENE_TITLE].GetPassTime()-delay1)/1.8);
			//ロゴ1枚目.
			SetDrawBlendModeST(MODE_ADD, 255 * anim);
			imgLogo[1].DrawExtendGraphST(0, {WINDOW_WID/2, _int(logoY - anim*100)}, {0.5, 0.5}, TRUE);
			//ロゴ2枚目.
			SetDrawBlendModeST(MODE_ADD, 255 * (1-anim));
			imgLogo[0].DrawExtendGraphST(0, {WINDOW_WID/2, _int(logoY - anim*100)}, {0.5, 0.5}, TRUE);
		}
		//描画モードリセット.
		ResetDrawBlendMode();
	}

	//best score.
	if (tmScene[SCENE_TITLE].GetPassTime() > delay2) {

		//アニメーション値.
		double anim = CalcNumEaseInOut(tmScene[SCENE_TITLE].GetPassTime()-delay2);
		//テキスト.
		TCHAR text[256];
		_stprintf(text, _T("BEST SCORE: %d"), data.bestScore); //ベストスコア.
		DrawStrST str(text, {WINDOW_WID/2, WINDOW_HEI/2+85}, COLOR_BEST_SCORE);

		SetDrawBlendModeST(MODE_ADD, 255*anim);
		str.DrawStringST(TRUE, data.font2);
		ResetDrawBlendMode();
	}
	//PUSH SPACE.
	if (tmScene[SCENE_TITLE].GetPassTime() > delay3) {
		//アニメーション値.
		double anim = CalcNumWaveLoop(tmScene[SCENE_TITLE].GetPassTime()-delay3);
		//テキスト.
		DrawStrST str(_T("Push SPACE or  X"), {WINDOW_WID/2-5, WINDOW_HEI/2+285}, 0xFFFFFF);
		Circle cir = { {WINDOW_WID/2+93, WINDOW_HEI/2+285-1}, 18, 0xFFFFFF };
		
		SetDrawBlendModeST(MODE_ADD, 255*anim);
		str.DrawStringST(TRUE, data.font1); //テキスト.
		DrawCircleST(&cir, FALSE, FALSE);   //Xボタンの円.
		ResetDrawBlendMode();
	}
	//隕石破壊.
	if (tmScene[SCENE_TITLE].GetPassTime() > delay4) {
		//まだ出してなければ.
		if (!isFinTitleAnim) {
			isFinTitleAnim = TRUE; //一度きり.

			double dig = -130; //角度.

			//エフェクトをいくつか出す.
			for (int i = 0; i < 8; i++) {

				double newDig = dig + (float)RandNum(-300, 300)/10; //少し角度をずらす.

				EffectData data{}; 
				data.type  = Effect_BreakMeteo;
				data.pos   = { 600, 338 };
				data.vec   = CalcDigToPos(newDig);                //ずらした角度を反映.
				data.speed = ((float)RandNum( 60,  100)/10)*1.4f; //速度抽選.
				data.len   = ((float)RandNum( 30,  150)/10)*1.4f; //長さ抽選.
				data.ang   =  (float)RandNum(  0, 3599)/10;       //角度抽選.
				//エフェクト召喚.
				effectMng.SpawnEffect(&data);
			}
			//サウンド.
			p_sound->Play(_T("Break"), FALSE, 65);
		}
	}
}
void GameManager::DrawReady() {
	
	player.Draw();    //プレイヤー.
	effectMng.Draw(); //エフェクト管理.
	DrawUI();
}
void GameManager::DrawGame() {

	DrawObjects();     //オブジェクト.
	player.Draw();     //プレイヤー.
	effectMng.Draw();  //エフェクト.
	DrawUI();
	DrawReflectMode(); //反射モード演出.
}
void GameManager::DrawEnd() {
	
	DrawObjects();
	effectMng.Draw(); //エフェクト.
	{
		float anim = min(tmScene[SCENE_END].GetPassTime(), 1); //アニメーション値.
		Box box = { {0, 0}, {WINDOW_WID, WINDOW_HEI}, 0x000000 };

		SetDrawBlendModeST(MODE_ALPHA, 128*anim);
		DrawBoxST(&box, FALSE); //画面を暗くする(UI以外)
		ResetDrawBlendMode();
	}
	DrawUI();

	//終了案内.
	{
		//アニメーション値.
		double anim = CalcNumEaseOut(tmScene[SCENE_END].GetPassTime());

		//スコア表示.
		TCHAR text[256];
		_stprintf(
			text, _T("%d + %d(%.3f秒) = %d点"),
			data.scoreBef, (int)(tmScene[SCENE_GAME].GetPassTime() * 10), tmScene[SCENE_GAME].GetPassTime(), data.score
		);
		//テキストの設定.
		DrawStrST str1(_T("- GAME OVER -"), {WINDOW_WID/2, _int(370+30*anim)}, 0xA0A0A0);
		DrawStrST str2(_T("Time Bonus"),    {WINDOW_WID/2, WINDOW_HEI/2-20},   0xFFFFFF);
		DrawStrST str3(text,                {WINDOW_WID/2, WINDOW_HEI/2+20},   0xFFFFFF);
		//画面中央に文字を表示.
		SetDrawBlendModeST(MODE_ADD, 255*anim);
		str1.DrawStringST(TRUE, data.font3);
		str2.DrawStringST(TRUE, data.font1);
		str3.DrawStringST(TRUE, data.font1);
		ResetDrawBlendMode();
	}

	const float delay1 = 1.2f;
	const float delay2 = 1.5f;

	//一定時間が経ったら.
	if (tmScene[SCENE_END].GetPassTime() > delay1) {
		//ベストスコア更新.
		if (data.score > data.bestScore) {

			//アニメーション値.
			double anim = CalcNumEaseOut((tmScene[SCENE_END].GetPassTime()-delay1)*2);
			//テキスト.
			DrawStrST str = { _T("NEW RECORD!"), {WINDOW_WID/2, _int(WINDOW_HEI/2-350+anim*20)}, 0xEFFFA0 };
			//描画.
			SetDrawBlendModeST(MODE_ADD, 255*anim);
			str.DrawStringST(TRUE, data.font2);
			ResetDrawBlendMode();
			//サウンド.
			if (!isFinScoreAnim) {
				isFinScoreAnim = TRUE; //一度のみ.
				p_sound->Play(_T("BestScore"), FALSE, 65);
			}
		}
	}
	//一定時間が経ったら.
	if (tmScene[SCENE_END].GetPassTime() > delay2) {
		
		//アニメーション値.
		double anim = CalcNumWaveLoop(tmScene[SCENE_END].GetPassTime()-delay2);
		//テキスト.
		DrawStrST str(_T("Push SPACE or  A"), {WINDOW_WID/2-5, WINDOW_HEI/2+145}, 0xFFFFFF);
		Circle cir = { {WINDOW_WID/2+93, WINDOW_HEI/2+145}, 18, 0xFFFFFF };
		
		SetDrawBlendModeST(MODE_ADD, 255*anim);
		str.DrawStringST(TRUE, data.font1); //テキスト.
		DrawCircleST(&cir, FALSE, FALSE);   //Aボタンの円.
		ResetDrawBlendMode();
	}
}
void GameManager::DrawPause() {

	DrawObjects();     //オブジェクト.
	player.Draw();     //プレイヤー.
	effectMng.Draw();  //エフェクト.
	DrawUI();
	DrawReflectMode(); //反射モード演出.
}

//背景の描画.
void GameManager::DrawBG() {

	//背景デザイン.
	for (int x = 0; x < WINDOW_WID; x += 5) {

		int clr = _int(20 * fabs(sin((double)x/200))); //色の変化.
		Line line = { {(double)x, 0},{(double)x, WINDOW_HEI}, GetColor(0, clr, clr) };
		DrawLineST(&line, FALSE, 5);
	}
	//背景(スローモード).
	if (data.isSlow) {
		//最初の0.5秒
		double time = 0.5-(tmSlowMode.GetPassTime()-(SLOW_MODE_TIME-0.5));
		time = CalcNumEaseOut(time); //値の曲線変動.
		//背景色.
		{
			Box box = { {0, 0}, {WINDOW_WID, WINDOW_HEI}, 0x303030 };
			SetDrawBlendModeST(MODE_ADD, 100*time);
			DrawBoxST(&box, FALSE);
			ResetDrawBlendMode();
		}
		//枠線.
		{
			Box box = { {WINDOW_WID/2, WINDOW_HEI/2}, {WINDOW_WID * time, WINDOW_HEI * time}, COLOR_PLY_REFLECT };
			DrawBoxST(&box, TRUE, FALSE, TRUE);
		}
	}
}
//UIの描画.
void GameManager::DrawUI() {

#if false
	//レベル(debug)
	DrawFormatStringToHandle(
		10, WINDOW_HEI-75, 0xFFFFFF, data.font2, _T("Level: %d"), data.level
	);
	//出現間隔割合(debug)
	DrawFormatStringToHandle(
		10, WINDOW_HEI-40, 0xFFFFFF, data.font2, _T("Spawn: %.2f%%"), data.spawnRate*100
	);
#endif

	//ハイスコア表示.
	{
		//アニメーション値.
		double alpha1   = CalcNumEaseInOut( tmScene[SCENE_READY].GetPassTime()-0.1);
		double alpha2   = CalcNumEaseInOut( tmScene[SCENE_READY].GetPassTime()-0.2);
		double alpha3   = CalcNumEaseInOut( tmScene[SCENE_READY].GetPassTime()-0.3);
		double alpha4   = CalcNumEaseInOut((tmScene[SCENE_READY].GetPassTime()-1.0)*2);
		double animSin1 = sin(M_PI* tmScene[SCENE_READY].GetPassTime()-0.1);
		double animSin2 = sin(M_PI*(tmScene[SCENE_READY].GetPassTime()-0.2));
		double animSin3 = sin(M_PI*(tmScene[SCENE_READY].GetPassTime()-0.3));

#if true
		//test.
		imgUI.DrawExtendGraphST(0, {WINDOW_WID/2,      70}, {0.6, 0.3}, TRUE, TRUE);
		imgUI.DrawExtendGraphST(0, {WINDOW_WID/2-380, 150}, {0.6, 0.3}, TRUE, TRUE);
		imgUI.DrawExtendGraphST(0, {WINDOW_WID/2,     150}, {0.6, 0.3}, TRUE, TRUE);
		imgUI.DrawExtendGraphST(0, {WINDOW_WID/2+380, 150}, {0.6, 0.3}, TRUE, TRUE);
#endif

		//テキスト設定.
		TCHAR text[256];
		_stprintf(text, _T("LEVEL:%d"),        data.level);
		DrawStrST str1(text, {WINDOW_WID/2,      70}, 0xFFFFFF);
		_stprintf(text, _T("BEST SCORE:%05d"), data.bestScore);
		DrawStrST str2(text, {WINDOW_WID/2-380, 150}, COLOR_BEST_SCORE);
		_stprintf(text, _T("SCORE:%05d"),      data.score);
		DrawStrST str3(text, {WINDOW_WID/2,     150}, COLOR_SCORE);
		_stprintf(text, _T("TIME:%.3f"),       tmScene[SCENE_GAME].GetPassTime());
		DrawStrST str4(text, {WINDOW_WID/2+380, 150}, COLOR_TIME);
		//テキスト(main)
		SetDrawBlendModeST(MODE_ALPHA, 255 * alpha4);
		str1.DrawStringST(TRUE, data.font3);
		SetDrawBlendModeST(MODE_ALPHA, 255 * alpha1);
		str2.DrawStringST(TRUE, data.font3);
		SetDrawBlendModeST(MODE_ALPHA, 255 * alpha2);
		str3.DrawStringST(TRUE, data.font3);
		SetDrawBlendModeST(MODE_ALPHA, 255 * alpha3);
		str4.DrawStringST(TRUE, data.font3);
		//テキスト(光沢用)
		str2.SetColor(0xFFFFFF);
		str3.SetColor(0xFFFFFF);
		str4.SetColor(0xFFFFFF);
		SetDrawBlendModeST(MODE_ALPHA, 100 * animSin1);
		str2.DrawStringST(TRUE, data.font3);
		SetDrawBlendModeST(MODE_ALPHA, 100 * animSin2);
		str3.DrawStringST(TRUE, data.font3);
		SetDrawBlendModeST(MODE_ALPHA, 100 * animSin3);
		str4.DrawStringST(TRUE, data.font3);
		//描画モードリセット.
		ResetDrawBlendMode();
	}
}
//オブジェクトの描画.
void GameManager::DrawObjects() {

	//Lv1以上.
	laserMng.Draw();
	meteoMng.Draw();
	obstacle4_1.Draw();
	obstacle4_2.Draw();
	item.Draw();
	//Lv2以上.
	if (data.level >= 2) {
		mgl[0].Draw();
		mgl[1].Draw();
	}
	//Lv3以上.
	if (data.level >= 3) {
		obstacle5.Draw();
	}
	//Lv4以上.
	if (data.level >= 4) {
		obstacle4_3.Draw();
		obstacle4_4.Draw();
	}
}
//反射モード演出.
void GameManager::DrawReflectMode() {

	//カウントダウン中.
	if (tmSlowMode.GetIsMove() && tmSlowMode.GetPassTime() > 0)
	{
		//テキストの設定.
		TCHAR text[256];
		_stprintf(text, _T("%d"), (int)ceil(tmSlowMode.GetPassTime())); //TCHAR型に変数を代入.
		DrawStrST str1(_T("REFLECT"), {WINDOW_WID/2, WINDOW_HEI/2}, COLOR_ITEM);
		DrawStrST str2(text,          {WINDOW_WID/2, WINDOW_HEI/2}, COLOR_ITEM);

		//画面中央に数字を表示.
		{
			double dec = GetDecimal(tmSlowMode.GetPassTime()); //小数だけ取り出す.
			SetDrawBlendModeST(MODE_ADD, _int(255 * dec));     //1秒ごとに薄くなる演出.
			//最初の1秒.
			if (tmSlowMode.GetPassTime() > SLOW_MODE_TIME-1) {
				str1.DrawStringST(TRUE, data.font3); //反射モード.
			}
			//最後の3秒.
			if (tmSlowMode.GetPassTime() <= 3) {
				str2.DrawStringST(TRUE, data.font3); //数字.
			}
			ResetDrawBlendMode();
		}
	}
}

//ゲーム終了.
void GameManager::GameEnd() {
	
	data.scene = SCENE_END; //ゲーム終了へ.
	
	tmScene[SCENE_GAME].Stop(); //停止.
	tmScene[SCENE_END].Start(); //開始.
	data.isSlow = FALSE;
	tmSlowMode.Reset();

	for (int i = 0; i < _countof(isItemCount); i++) {
		isItemCount[i] = FALSE;
	}

	data.scoreBef = data.score;                                  //時間加算前のスコアを記録.
	data.score += (int)(tmScene[SCENE_GAME].GetPassTime() * 10); //時間ボーナス加算.

	//最高スコア更新なら保存.
	if (data.score > data.bestScore) {

		FileST file;
		file.Open(FILE_DATA_PATH, _T("w")); //ファイルを開く.
		file.WriteInt(data.score);          //スコアを保存.
	}

	//サウンド.
	p_sound->FadeOutPlay(_T("BGM1"), 2);
}
//アイテムを取った時.
void GameManager::TakeItem() {

	data.isSlow = TRUE;             //スローモードにする.
	data.score += SCORE_TAKE_ITEM;  //スコア加算.
	tmSlowMode.Start();             //スローモード計測開始.
	player.SetReflectionMode(TRUE); //反射モード開始.
}