/*
   - GameManager.h -
   ゲーム全体管理.
*/
#pragma once
#include "KR_Lib/KR_Scene.h"

//ゲームデータ.[継承不可]
class GameData final
{
public:
	//実体.
	static GameData* GetPtr() {
		static GameData inst; //自身のインスタンス.
		return &inst;
	}

	Scene scene;      //シーンの記録用.
	int   stage;      //ステージ数.

	int   score;      //スコア.
	int   scoreBef;   //スコア(時間加算前)
	int   bestScore;  //ベストスコア.
	int   level;	  //レベル.

	float spawnRate;  //障害物の出現時間割合.
	float counter;    //経過時間カウンター(スローの影響を受ける)

	int   font1;      //フォント.
	int   font2;      //フォント.
	int   font3;      //フォント.
	int   font4;      //フォント.

	bool  isSlow;     //スローモードかどうか.
};

//ゲームマネージャー.[継承不可]
class GameManager final
{
public: //実体.
	static GameManager* GetPtr() {
		static GameManager inst; //自身のインスタンス.
		return &inst;
	}

private: //データ.
	//シーン別に経過時間を記録する.
	Timer tmScene[SCENE_COUNT] = {
		Timer(COUNT_UP, 0), //Titleシーン.
		Timer(COUNT_UP, 0), //Readyシーン.
		Timer(COUNT_UP, 0), //Gameシーン.
		Timer(COUNT_UP, 0), //Endシーン.
		Timer(COUNT_UP, 0), //Pauseシーン.
	};
	Timer tmSlowMode = Timer(COUNT_DOWN, SLOW_MODE_TIME); //スロー継続時間.

	DrawImg imgLogo[2]{};   //タイトルロゴ画像.
	DrawImg imgUI[4]{};     //UI画像.
	DrawImg imgNewRecord{}; //new record.
	DrawImg imgGameOver{};  //gameover.
	DrawImg imgReflect{};   //reflect.

	bool isTitleAnim{};             //Title:     破片アニメーションを出したか.
	bool isBestScoreSound{};        //BestScore: 音を鳴らしたか.
	bool isItemCountDownSound[3]{}; //Item:      カウントダウンの音を鳴らしたか.

	InputMng* p_input{};
	SoundMng* p_sound{};

public:
	//get.
	float GetSlowModeTime() {
		return tmSlowMode.GetPassTime();
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
	void UpdateTutorial();
	void UpdateReady();
	void UpdateGame();
	void UpdateEnd();
	void UpdatePause();

	void UpdateObjects();

	//Draw.
	void DrawTitle();
	void DrawMenu();
	void DrawTutorial();
	void DrawReady();
	void DrawGame();
	void DrawEnd();
	void DrawPause();

	void DrawUI();
	void DrawObjects();
	void DrawReflectMode();

	//その他.
	void GameEnd();
	void TakeItem();
};