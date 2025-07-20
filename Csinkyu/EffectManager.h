/*
   - EffectManager.h -
   エフェクトを管理するクラス.
*/
#pragma once

//エフェクトタイプ.
enum EffectType
{
	Effect_Score100,
	Effect_Score500,
};

//エフェクトデータ.
struct EFFECT
{
	EffectType type;

	DBL_XY     pos;     //座標.
	float      counter; //時間計測用.
	BOOL       active;
};

//エフェクト管理クラス.
class EffectManager
{
private:
	EFFECT effect[EFFECT_MAX]{};

	GameData* p_data{};

public:
	void Init(GameData*);
	void Reset();
	void Update();
	void Draw();

	void SpawnEffect(EffectType type, DBL_XY pos); //エフェクト出現.
	void DeleteEffect(int idx);                    //エフェクト消去.
};
