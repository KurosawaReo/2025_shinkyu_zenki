/*
突然出現する障害物
*/
#pragma once

typedef struct tagFLASHEFFECT5
{
	double x, y;    // エフェクト位置.
	float Counter;  // 経過時間.
	float Duration; // エフェクトの持続時間.
	int BaseSize;   // 基本サイズ
	int ValidFlag;  // 有効フラグ
	bool AlreadyHit;
}FLASHEFFECT5;

class Obstacle5
{
private:
	FLASHEFFECT5 flashEffect[OBSTACLE5_FLASH_MAX]{}; // クラスのメンバ変数として追加

    int  flashTimer;   // インターバル時間から開始（カウントダウン）
	int  baseInterval; // 基本インターバル.
	bool isFirstCall;  // 初回呼び出しフラグ

	GameData* p_data{};
	Player*   p_player{};

public:
	void Init(GameData*, Player*);  // ポインタのポインタから修正
	void Reset(double x, double y, int direction);
	void Update();
	void Draw();
	void Hitjudgment();
	void UpdateFlashGeneration();
	void DrawObstFlash();
	void StartFlashEffect(double x, double y); // この行を追加

	void GenerateRandomPosition(double& x, double& y);
	bool CheckDistance(double x, double y);
	void SpawnObstaclegroup();
	int  GetEffectState(int index);
	void DrawWarningEffect(int index);
	void DrawActiveEffect(int index);
};