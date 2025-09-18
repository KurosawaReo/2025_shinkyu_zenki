/*
   - TutorialManager.h -
   �`���[�g���A���V�[��.
*/
#pragma once

//�`���[�g���A��.[�p���s��]
class TutorialManager final
{
public: //����.
	static TutorialManager* GetPtr() {
		static TutorialManager inst; //���g�̃C���X�^���X.
		return &inst;
	}

private:
	int stepNo{}; //���݂̃X�e�b�v�ԍ�.

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