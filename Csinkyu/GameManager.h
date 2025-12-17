/*
   - GameManager.h -
   ゲーム全体管理.
*/
#pragma once

//前方宣言.
class NormalLaser_1;
class NormalLaser_2;
class NormalLaser_3;
class NormalLaser_4;
class StraightLaser;

//ゲームデータ.[継承不可]
class GameData final
{
//▼実体関係.
public:
	static GameData& GetInst() {
		static GameData inst; //自身のインスタンス.
		return inst;
	}

//▼データ.
public:
	Scene      scene{};			//現在のシーン.
	StageType  stage{};			//ステージ種類.
	bool       isPause{};       //ポーズ中かどうか.

	int		   score{};			//スコア.
	int		   scoreBef{};		//スコア(時間加算前)
	int		   bestScore{};		//ベストスコア.
	int		   level{};			//レベル.

	float	   speedRate{};		//ゲーム進行速度倍率.
	float	   spawnRate{};		//障害物の出現時間割合.
	float	   counter{};		//経過時間カウンター(スローの影響を受ける)

	bool       isReflectMode{};	//反射モードかどうか.
	float      slowBufCntr{};	//スロー続行時間.

	int		   font1{};			//フォント.
	int		   font2{};			//フォント.
	int		   font3{};			//フォント.
	int		   font4{};			//フォント.
	
private:
	//constructor(新規作成をできなくする)
	GameData(){}

public:
	//使用禁止.
	GameData(const GameData&) = delete;
	GameData& operator=(const GameData&) = delete;
};

//ゲームマネージャー.[継承不可]
class GameManager final
{
//▼実体関係.
public:
	static GameManager& GetInst() {
		static GameManager inst; //自身のインスタンス.
		return inst;
	}

//▼データ.
private:
	Timer tmScene[SCENE_COUNT]; //シーン別に経過時間を記録する.

	Timer      tmGameTime{};    //ゲーム計測時間.
	Timer      tmReflectMode{}; //スロー継続時間.

#if defined DEBUG_SHOW_FPS
	TimerMicro tmFps{};         //fps計測用タイマー.
#endif

	bool isTitleAnim{};             //Title:     破片アニメーションを出したか.
	bool isBestScoreSound{};        //BestScore: 音を鳴らしたか.
	bool isItemCountDownSound[3]{}; //Item:      カウントダウンの音を鳴らしたか.

	bool isGameStart{};             //ゲーム開始サイン.
	bool isBestScore{};             //ベストスコア更新したか.

public: //オブジェクト.
	NormalLaser_1* laserNor1{};
	NormalLaser_2* laserNor2{};
	NormalLaser_3* laserNor3{};
	NormalLaser_4* laserNor4{};
	StraightLaser* laserStr[2]{};

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

	//その他.
	void GamePause();
	void GamePauseEnd();
	void GameOver();
	void ItemUsed();
	void ReflectModeEnd();

	//使用禁止.
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
};