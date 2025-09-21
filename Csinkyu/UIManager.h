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

	int disBestScore{}; //�\���x�X�g�X�R�A.
	int disScore{};     //�\���X�R�A.

	GameManager*   p_gameMng{};
	GameData*      p_gameData{};
	TutorialStage* p_tutorialStg{};

public:
	//set.
	void SetDisBestScore(int _score) { disBestScore = _score; }

	void Init();
	void Reset();
	void Update();
	void Draw();
};