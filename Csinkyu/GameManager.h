/*
   - GameManager.h -
   ゲーム全体管理.
*/
#pragma once
#include "KR_Lib/KR_Scene.h"

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
	//実体取得用.
	static GameData& GetInst() {
		static GameData inst; //自身のインスタンス.
		return inst;
	}
	//使用禁止.
	GameData(const GameData&) = delete;
	GameData& operator=(const GameData&) = delete;
private:
	//constructor(新規作成をできなくする)
	GameData(){}

//▼データ.
public:
	Scene     scene;			//シーンの記録用.
	StageType stage;			//ステージ種類.

	int		  score;			//スコア.
	int		  scoreBef;			//スコア(時間加算前)
	int		  bestScore;		//ベストスコア.
	int		  level;			//レベル.

	float	  speedRate;		//ゲーム進行速度倍率.
	float	  spawnRate;		//障害物の出現時間割合.
	float	  counter;			//経過時間カウンター(スローの影響を受ける)

	bool      isReflectMode;	//反射モードかどうか.
	float     slowBufCntr;		//スロー続行時間.

	int		  font1;			//フォント.
	int		  font2;			//フォント.
	int		  font3;			//フォント.
	int		  font4;			//フォント.
};

//ゲームマネージャー.[継承不可]
class GameManager final
{
//▼実体関係.
public:
	//実体取得用.
	static GameManager& GetInst() {
		static GameManager inst; //自身のインスタンス.
		return inst;
	}
	//使用禁止.
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
private:
	//constructor(新規作成をできなくする)
	GameManager(){}

//▼データ.
private:
	Timer tmScene[SCENE_COUNT]; //シーン別に経過時間を記録する.

	Timer tmGameTime{};     //ゲーム計測時間.
	Timer tmReflectMode{};  //スロー継続時間.

	DrawImg imgLogo[2]{};   //タイトルロゴ画像.
	DrawImg imgUI{};        //UI画像.
	DrawImg imgNewRecord{}; //new record.
	DrawImg imgGameOver{};  //gameover.
	DrawImg imgReflect{};   //reflect.

	bool isTitleAnim{};             //Title:     破片アニメーションを出したか.
	bool isBestScoreSound{};        //BestScore: 音を鳴らしたか.
	bool isItemCountDownSound[3]{}; //Item:      カウントダウンの音を鳴らしたか.

	bool isGameStart{};             //ゲーム開始サイン.
	bool isBestScore{};             //ベストスコア更新したか.

	InputMng* p_input{};
	SoundMng* p_sound{};

public: //オブジェクト.
	NormalLaser_1* laserNor1;
	NormalLaser_2* laserNor2;
	NormalLaser_3* laserNor3;
	NormalLaser_4* laserNor4;
	StraightLaser* laserStr[2];

public:
	//destructor.
	~GameManager();
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
	void UpdatePause();

	void UpdateReflectMode();

	//Draw.
	void DrawTitle();
	void DrawMenu();
	void DrawGame();
	void DrawEnd();
	void DrawPause();

	void DrawReflectMode();

	//その他.
	void GameOver();
	void ItemUsed();
	void ReflectModeEnd();
};