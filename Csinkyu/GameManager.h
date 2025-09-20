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

	Scene     scene;	  //シーンの記録用.
	StageType stage;	  //ステージ種類.

	int		  score;      //スコア.
	int		  scoreBef;   //スコア(時間加算前)
	int		  bestScore;  //ベストスコア.
	int		  level;	  //レベル.

	float	  speedRate;  //ゲーム進行速度倍率.
	float	  spawnRate;  //障害物の出現時間割合.
	float	  counter;    //経過時間カウンター(スローの影響を受ける)

	int		  font1;      //フォント.
	int		  font2;      //フォント.
	int		  font3;      //フォント.
	int		  font4;      //フォント.
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
	Timer tmScene[SCENE_COUNT]; //シーン別に経過時間を記録する.

	Timer tmGameTime{};     //ゲーム計測時間.
	Timer tmSlowMode{};     //スロー継続時間.

	DrawImg imgLogo[2]{};   //タイトルロゴ画像.
	DrawImg imgUI{};        //UI画像.
	DrawImg imgNewRecord{}; //new record.
	DrawImg imgGameOver{};  //gameover.
	DrawImg imgReflect{};   //reflect.

	bool isTitleAnim{};             //Title:     破片アニメーションを出したか.
	bool isBestScoreSound{};        //BestScore: 音を鳴らしたか.
	bool isItemCountDownSound[3]{}; //Item:      カウントダウンの音を鳴らしたか.

	bool isGameStart{};             //ゲーム開始サイン.

	InputMng* p_input{};
	SoundMng* p_sound{};

public:
	//get.
	float GetSlowModeTime() {
		return tmSlowMode.GetPassTime();
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

	void UpdateObjects();
	void UpdateSlowMode();

	//Draw.
	void DrawTitle();
	void DrawMenu();
	void DrawGame();
	void DrawEnd();
	void DrawPause();

	void DrawObjects();
	void DrawReflectMode();

	//その他.
	void GameEnd();
	void ItemUsed();
};