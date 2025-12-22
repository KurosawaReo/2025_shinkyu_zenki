/*
   - GameManager.h -
   ゲーム全体管理.
*/
#pragma once

//前方宣言.
class GameData;
class BGManager;
class MenuManager;
class TutorialStage;
class EndlessStage;
class LaserManager;
class MeteorManager;
class Ripples;
class FireworksManager;
class ItemManager;
class Player;
class EffectManager;
class UIManager;

class NormalLaser_1;
class NormalLaser_2;
class NormalLaser_3;
class NormalLaser_4;
class StraightLaser;

//ゲームマネージャー.[継承不可]
class GameManager final
{
//▼実体関係.
public:
	static GameManager& GetInst() {
		static GameManager inst; //自身のインスタンス.
		return inst;
	}

//▼変数.
private:
	Timer tmScene[SCENE_COUNT]; //シーン別に経過時間を記録する.

	Timer tmGameTime{};         //ゲーム計測時間.
	Timer tmReflectMode{};      //スロー継続時間.

#if defined DEBUG_SHOW_FPS
	TimerMicro tmFps{};         //fps計測用タイマー.
#endif

	bool isTitleAnim{};             //Title:     破片アニメーションを出したか.
	bool isBestScoreSound{};        //BestScore: 音を鳴らしたか.
	bool isItemCountDownSound[3]{}; //Item:      カウントダウンの音を鳴らしたか.

	bool isGameStart{};             //ゲーム開始サイン.
	bool isBestScore{};             //ベストスコア更新したか.

	//参照.
	GameData         *gameData{};
	BGManager        *bg{};
	MenuManager      *menuMng{};
	TutorialStage    *tutorialStg{};
	EndlessStage     *endlessStg{};
	LaserManager     *laserMng{};
	MeteorManager    *meteorMng{};
	Ripples          *ripples{};
	FireworksManager *fireworksMng{};
	ItemManager      *item{};
	Player           *player{};
	EffectManager    *effectMng{};
	UIManager        *uiMng{};

//▼オブジェクト.
public:
	NormalLaser_1* laserNor1{};
	NormalLaser_2* laserNor2{};
	NormalLaser_3* laserNor3{};
	NormalLaser_4* laserNor4{};
	StraightLaser* laserStr[2]{};

//▼関数.
private:
	//constructor(新規作成をできなくする)
	GameManager(){}
	//destructor.
	~GameManager();

public:
	//get.
	float GetReflectModeTime() {
		return tmReflectMode.GetPassTime();
	}
	float GetSceneTime(Scene scene) {
		return tmScene[scene].GetPassTime();
	}
	float GetGameTime() {
		return tmGameTime.GetPassTime();
	}

	//メイン処理.
	void Init();
	void Reset();
	void Update();
	void Draw();

	//Reset.
	void ResetNorLaser();
	void ResetStrLaser();

	//Update.
	void UpdateTitle();
	void UpdateMenu();
	void UpdateGame();
	void UpdateEnd();

	void UpdateReflectMode();

	//Draw.
	void DrawTitle();
	void DrawMenu();
	void DrawGame();
	void DrawEnd();

	void DrawReflectMode();

	//ポーズ画面.
	void GamePause();
	void GamePauseEnd();
	void DrawPause();

	//その他.
	void GameOver();
	void ItemUsed();
	void ReflectModeEnd();

	//使用禁止.
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
};