/*
   - Ripples.h -

   障害物: 波紋.
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

//波紋管理.[継承不可]
class Ripples final
{
//▼実体関係.
public:
	//実体取得用.
	static Ripples& GetInst() {
		static Ripples inst; //自身のインスタンス.
		return inst;
	}
	//使用禁止.
	Ripples(const Ripples&) = delete;
	Ripples& operator=(const Ripples&) = delete;
private:
	//constructor(新規作成をできなくする)
	Ripples(){}

//▼データ.
private:
	FLASHEFFECT5 flashEffect[RIPPLES_FLASH_MAX]{}; // クラスのメンバ変数として追加

	float flashTimer{}; //出現タイマー.

	GameData* p_data{};
	Player*   p_player{};

public:
	void Init();
	void Reset();
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