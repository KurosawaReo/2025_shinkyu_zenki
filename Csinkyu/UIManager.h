/*
   - UIManager.h -
   UI�Ǘ�.
*/
#pragma once

//�O���錾.
class GameManager;
class TutorialStage;

//UI�Ǘ�.[�p���s��]
class UIManager final
{
//�����̊֌W.
public:
	//���̎擾�p.
	static UIManager& GetInst() {
		static UIManager inst; //���g�̃C���X�^���X.
		return inst;
	}
	//�g�p�֎~.
	UIManager(const UIManager&) = delete;
	UIManager& operator=(const UIManager&) = delete;
private:
	//constructor(�V�K�쐬���ł��Ȃ�����)
	UIManager(){}

//���f�[�^.
private:
	DrawImg imgUI[4]{}; //UI�摜.

	int  disBestScore{}; //�\���x�X�g�X�R�A.
	int  disScore{};     //�\���X�R�A.

	bool isShowScore{}; //�X�R�A��\�����邩�ǂ���.

	GameManager*   p_gameMng{};
	GameData*      p_gameData{};
	TutorialStage* p_tutorialStg{};

public:
	//sign.
	void SignIsShowScore() { isShowScore = true; }
	//set.
	void SetDisBestScore(int _score) { disBestScore = _score; }

	void Init();
	void Reset();
	void Update();
	void Draw();
};