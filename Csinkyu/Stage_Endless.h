/*
   - Stage_Endless.h -

   �X�e�[�W: �ϋv���[�h.
*/
#pragma once

//�ϋv���[�h.[�p���s��]
class EndlessStage final
{
public: //����.
	static EndlessStage* GetPtr() {
		static EndlessStage inst; //���g�̃C���X�^���X.
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