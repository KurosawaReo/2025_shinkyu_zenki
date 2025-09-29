/*
   - EffectManager.h -
   エフェクトを管理するクラス.
*/
#pragma once

class GameData; //前方宣言.

//エフェクトタイプ.
enum EffectType
{
	Effect_Score100,
	Effect_Score500,
	Effect_PlayerDeath,		//プレイヤー死亡.
	Effect_ReflectLaser,	//レーザー反射.
	Effect_BreakMeteo,		//隕石破壊.

	Effect_Endless_Level1,	//耐久モード: Level1演出.
	Effect_Endless_Level2,	//耐久モード: Level2演出.
	Effect_Endless_Level3,	//耐久モード: Level3演出.
	Effect_Endless_Level4,	//耐久モード: Level4演出.
	Effect_Endless_Level5,	//耐久モード: Level5演出.
	Effect_Tutorial_Step1,	//チュートリアル: step1演出.
	Effect_Tutorial_Step2,	//チュートリアル: step2演出.
	Effect_Tutorial_Step3,	//チュートリアル: step3演出.
	Effect_Tutorial_Step4,	//チュートリアル: step4演出.
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

//エフェクト管理クラス.[継承不可]
class EffectManager final
{
//▼実体関係.
public:
	//実体取得用.
	static EffectManager& GetInst() {
		static EffectManager inst; //自身のインスタンス.
		return inst;
	}
	//使用禁止.
	EffectManager(const EffectManager&) = delete;
	EffectManager& operator=(const EffectManager&) = delete;
private:
	//constructor(新規作成をできなくする)
	EffectManager(){}

//▼データ.
private:
	Effect effect[EFFECT_MAX]{};

	DrawImg imgScore[2]{}; //スコア画像.

	GameData* p_data{};

public:
	void Init();
	void Reset();
	void Update();
	void Draw();

	void SpawnEffect(EffectData* data); //エフェクト出現.
	void DeleteEffect(int idx);         //エフェクト消去.
};
