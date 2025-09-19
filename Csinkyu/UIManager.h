/*
   - UIManager.h -
   UI�Ǘ�.
*/
#pragma once

//�O���錾.
class GameManager;
//class TutorialStage;

//UI�Ǘ�.[�p���s��]
class UIManager final
{
public: //����.
	static UIManager* GetPtr() {
		static UIManager inst; //���g�̃C���X�^���X.
		return &inst;
	}

private: //�f�[�^.
	DrawImg imgUI[4]{}; //UI�摜.

	GameManager*   p_gameMng{};
	GameData*      p_gameData{};
	TutorialStage* p_tutorialStg{};

public:
	void Init();
	void Reset();
	void Update();
	void Draw();
};