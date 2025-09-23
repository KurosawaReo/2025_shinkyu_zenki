/*
   - Stage_Endless.h -

   ステージ: 耐久モード.
*/
#pragma once

//前方宣言.
class GameData;
class GameManager;
class LaserManager;
class MeteorManager;
class Ripples;
class ItemManager;
class FireworksManager;
class EffectManager;

//耐久モード.[継承不可]
class EndlessStage final
{
//▼実体関係.
public:
	//実体取得用.
	static EndlessStage& GetInst() {
		static EndlessStage inst; //自身のインスタンス.
		return inst;
	}
	//使用禁止.
	EndlessStage(const EndlessStage&) = delete;
	EndlessStage& operator=(const EndlessStage&) = delete;
private:
	//constructor(新規作成をできなくする)
	EndlessStage(){}

//▼データ.
private:
	GameData*         p_data{};
	GameManager*      p_gameMng{};
	LaserManager*     p_laserMng{};
	MeteorManager*    p_meteorMng{};
	Ripples*          p_ripples{};
	ItemManager*      p_itemMng{};
	FireworksManager* p_fireworksMng{};
	EffectManager*    p_effectMng{};
	SoundMng*         p_sound{};

public:
	void Init();
	void Reset();
	void Update();
	void Draw();

	void UpdateObjects();
	void DrawObjects();
};