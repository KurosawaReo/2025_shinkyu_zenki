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
}FLASHEFFECT5;

class Obstacle5
{
private:
	Line  line{};
	float ang{};   //角度.
	float len{};   //長さ.
	float speed{}; //速さ.

	GameData* data{};
	Player* player{};
	FLASHEFFECT5 flashEffect[OBSTACLE5_FLASH_MAX]{}; // クラスのメンバ変数として追加

public:
	void Init(GameData*, Player*);  // ポインタのポインタから修正
	void Reset(double x, double y, float speed, int direction);
	void Update();
	void Draw();
	void Hitjudgment();
	void UpdateFlashGeneration();
	void DrawObstFlash();
	void StartFlashEffect(double x, double y);  // この行を追加
};