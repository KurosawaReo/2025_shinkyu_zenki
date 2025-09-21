/*
   - Stage_Tutorial.h -

   ステージ: チュートリアル.
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

//チュートリアル.[継承不可]
class TutorialStage final
{
public: //実体.
	static TutorialStage* GetPtr() {
		static TutorialStage inst; //自身のインスタンス.
		return &inst;
	}

private: //データ.
	int stepNo{}; //現在のステップ番号.

	Font font[2]{};

	GameData*         p_data{};
	GameManager*      p_gameMng{};
	LaserManager*     p_laserMng{};
	MeteorManager*    p_meteorMng{};
	Ripples*          p_ripples{};
	ItemManager*      p_itemMng{};
	FireworksManager* p_fireworksMng{};
	EffectManager*    p_effectMng{};
	InputMng*         p_input{};
	SoundMng*         p_sound{};

public:
	//get.
	int GetStepNo() const { return stepNo; }

	void Init();
	void Reset();
	void Update();
	void Draw();

	void UpdateStep0();
	void UpdateStep1();
	void UpdateStep2();
	void UpdateStep3();
	void UpdateStep4();

	void DrawStep1();
	void DrawStep2();
	void DrawStep3();
	void DrawStep4();

	void DrawTopText (MY_STRING text);
	void DrawTopText2(MY_STRING text);
};