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
	Effect_PlayerDeath,		//プレイヤー死亡.
	Effect_Reflect,			//反射.
	Effect_ReflectSpark,	//反射火花.
	Effect_MeteorCrash,		//隕石破壊.
	Effect_MeteorFragment,	//隕石破片.

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
struct Effect : public EffectData //TODO: この継承の使い方は不適切.
{
	float      counter{}; //時間計測用.
};

//エフェクト管理クラス.
class EffectManager final : public ManagerBase
{
//▼ ===== 変数 ===== ▼.
private:
	list<Effect> effect; //エフェクト配列.

//▼ ===== 関数 ===== ▼.
public:
	//コンストラクタ.
	EffectManager(int order) : ManagerBase(order) {}

	void Init()	  override;
	void Reset()  override;
	void Update() override;
	void Draw()	  override;

	void SpawnEffect (const EffectData* data); //エフェクト出現.

	//使用禁止.
	EffectManager(const EffectManager*) = delete;
	EffectManager* operator=(const EffectManager*) = delete;
};
