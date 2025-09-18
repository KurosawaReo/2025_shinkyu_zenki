/*
   - Stage_Tutorial.h -

   ステージ: チュートリアル.
*/
#pragma once

//チュートリアル.[継承不可]
class TutorialStage final
{
public: //実体.
	static TutorialStage* GetPtr() {
		static TutorialStage inst; //自身のインスタンス.
		return &inst;
	}

private:
	int stepNo{}; //現在のステップ番号.

	GameData*      p_data{};
	GameManager*   p_gameMng{};
	EffectManager* p_effectMng{};
	InputMng*      p_input{};
	SoundMng*      p_sound{};

public:
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
};