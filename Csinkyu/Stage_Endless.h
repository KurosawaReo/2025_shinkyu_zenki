/*
   - Stage_Endless.h -

   ステージ: 耐久モード.
*/
#pragma once

//耐久モード.[継承不可]
class EndlessStage final
{
public: //実体.
	static EndlessStage* GetPtr() {
		static EndlessStage inst; //自身のインスタンス.
		return &inst;
	}

private:
	GameData*      p_data{};
	EffectManager* p_effectMng{};
	SoundMng*      p_sound{};

public:
	void Init();
	void Reset();
	void Update();
	void Draw();
};