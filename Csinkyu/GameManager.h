/*
   - GameManager.h -
   ゲーム全体管理.
*/
#pragma once
#include "Scene_Title.h"
#include "Scene_Menu.h"
#include "Scene_Game.h"
#include "Scene_End.h"
#include "Obst_NormalLaser.h"
#include "Obst_NormalLaserMain.h"
#include "Obst_StraightLaser.h"

//ゲームマネージャー.
class GameManager : public ManagerBase
{
//▼ ===== 実体 ===== ▼.
public:
	static GameManager& GetInst() {
		static GameManager inst; //自身のインスタンス.
		return inst;
	}

//▼ ===== 変数 ===== ▼.
private:
	/* シーン関係 */
	StateMachine scene{};			//シーン切り替え用.

	TitleScene titleScene{};
	GameScene  gameScene{};
	MenuScene  menuScene{};
	EndScene   endScene{};

	/* タイマー */
	Timer tmGameTime{};			    //ゲーム計測時間.
	Timer tmReflectMode{};			//スロー継続時間.
	
	/* その他 */
	bool isTitleAnim{};             //Title:     破片アニメーションを出したか.
	bool isBestScoreSound{};        //BestScore: 音を鳴らしたか.
	bool isItemCountDownSound[3]{}; //Item:      カウントダウンの音を鳴らしたか.

	bool isGameStart{};             //ゲーム開始サイン.
	bool isBestScore{};             //ベストスコア更新したか.

#if defined DEBUG_SHOW_FPS
	TimerMicro tmFps{};         //fps計測用タイマー.
#endif

public:
	//オブジェクト.
	NormalLaser_1* laserNor1{};
	NormalLaser_2* laserNor2{};
	NormalLaser_3* laserNor3{};
	NormalLaser_4* laserNor4{};
	StraightLaser* laserStr[2]{};

//▼ ===== 関数 ===== ▼.
private:
	//コンストラクタ.
	GameManager() : ManagerBase(ORDER_GAME_MNG) {}
	//デストラクタ.
	~GameManager();

public:
	//get.
	float GetReflectModeTime() {
		return tmReflectMode.GetPassTime();
	}
	float GetGameTime() {
		return tmGameTime.GetPassTime();
	}

	//メイン処理.
	void Init()   override;
	void Reset()  override;
	void Update() override;
	void Draw()   override;

	//Reset.
	void ResetNorLaser();
	void ResetStrLaser();

	//Update.
	//TODO
	void UpdateReflectMode();

	//Draw.
	//TODO
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