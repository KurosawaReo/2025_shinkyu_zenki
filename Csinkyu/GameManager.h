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
	TitleScene titleScene{};
	GameScene  gameScene{};
	MenuScene  menuScene{};
	EndScene   endScene{};

#if defined DEBUG_SHOW_FPS
	TimerMicro tmFps{};				//fps計測用タイマー.
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
	GameScene* GetGameScene() { return &gameScene; }

	//メイン処理.
	void Init()   override;
	void Reset()  override;
	void Update() override;
	void Draw()   override;

	//Reset.
	void ResetNorLaser();
	void ResetStrLaser();

	//ポーズ画面.
	void GamePause();
	void GamePauseEnd();
	void DrawPause();

	//その他.
	void GameOver();
	void ItemUsed();

	//使用禁止.
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
};