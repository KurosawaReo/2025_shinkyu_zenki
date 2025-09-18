/*
   - Stage_Tutorial.h -

   �X�e�[�W: �`���[�g���A��.
*/
#pragma once

//�`���[�g���A��.[�p���s��]
class TutorialStage final
{
public: //����.
	static TutorialStage* GetPtr() {
		static TutorialStage inst; //���g�̃C���X�^���X.
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