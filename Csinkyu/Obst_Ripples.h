/*
   - Ripples.h -

   障害物: 波紋.
*/
#pragma once

//波紋データ.
struct RipplesData
{
	double x, y;       // エフェクト位置.
	int    baseSize;   // 基本サイズ
	bool   alreadyHit; 
	float  counter;    // 経過時間.
	float  duration;   // エフェクトの持続時間.
};

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
	list<RipplesData> ripples; //波紋配列.

	float     flashTimer{}; //出現タイマー.

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
	void SpawnRipples(double x, double y); // この行を追加

	void GenerateRandomPosition(double& x, double& y);
	bool CheckDistance(double x, double y);
	void SpawnObstaclegroup();

	int  GetEffectState   (list<RipplesData>::iterator it);
	void DrawWarningEffect(list<RipplesData>::iterator it);
	void DrawActiveEffect (list<RipplesData>::iterator it);
};