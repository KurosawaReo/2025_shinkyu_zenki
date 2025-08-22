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
	Effect_PlayerDeath,  //プレイヤー死亡.
	Effect_ReflectLaser, //レーザー反射.
	Effect_BreakMeteo,   //隕石破壊.
	Effect_Level1,		 //レベル1演出.
	Effect_Level2,		 //レベル2演出.
	Effect_Level3,		 //レベル3演出.
	Effect_Level4,		 //レベル4演出.
	Effect_Level5,		 //レベル5演出.
};
//エフェクトデータ.
struct EffectData
{
	EffectType type{};

	DBL_XY     pos{};     //座標.
	DBL_XY     vec{};     //方向.
	float      speed{};   //速さ.
	float      ang{};     //角度.
	float      len{};     //長さ.
};
//エフェクト.
struct Effect : public EffectData
{
	float      counter{}; //時間計測用.
	bool       active{};
};

//エフェクト管理クラス.
class EffectManager
{
private:
	Effect effect[EFFECT_MAX]{};

	GameData* p_data{};

public:
	void Init(GameData*);
	void Reset();
	void Update();
	void Draw();

	void SpawnEffect(EffectData* data); //エフェクト出現.
	void DeleteEffect(int idx);         //エフェクト消去.
};
