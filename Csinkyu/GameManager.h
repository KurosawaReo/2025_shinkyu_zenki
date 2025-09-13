/*
   - GameManager.h -
   �Q�[���S�̊Ǘ�.
*/
#pragma once

//�Q�[���}�l�[�W���[.
class GameManager 
{
private: //����.
	static GameManager inst; //���g�̃C���X�^���X.

private: //�f�[�^.
	GameData data{}; //�Q�[���f�[�^.

	//�V�[���ʂɌo�ߎ��Ԃ��L�^����.
	Timer tmScene[SCENE_COUNT] = {
		Timer(COUNT_UP, 0), //Title�V�[��.
		Timer(COUNT_UP, 0), //Ready�V�[��.
		Timer(COUNT_UP, 0), //Game�V�[��.
		Timer(COUNT_UP, 0), //End�V�[��.
		Timer(COUNT_UP, 0), //Pause�V�[��.
	};
	Timer tmSlowMode = Timer(COUNT_DOWN, SLOW_MODE_TIME); //�X���[�p������.

	DrawImg imgLogo[2]{};   //�^�C�g�����S�摜.
	DrawImg imgUI[4]{};     //UI�摜.
	DrawImg imgNewRecord{}; //new record.
	DrawImg imgGameOver{};  //gameover.
	DrawImg imgReflect{};   //reflect.

	bool isTitleAnim{};             //Title:     �j�ЃA�j���[�V�������o������.
	bool isBestScoreSound{};        //BestScore: ����炵����.
	bool isItemCountDownSound[3]{}; //Item:      �J�E���g�_�E���̉���炵����.

	InputMng* p_input{};
	SoundMng* p_sound{};

public:
	//���̂̎擾.
	static GameManager* GetPtr() {
		return &inst;
	}
	//get.
	float GetSlowModeTime() {
		return tmSlowMode.GetPassTime();
	}

	//���C������.
	void Init();
	void Reset();
	void Update();
	void Draw();

	//Reset.
	void ResetNorLaser();
	void ResetStrLaser();

	//Update.
	void UpdateTitle();
	void UpdateMenu();
	void UpdateTutorial();
	void UpdateReady();
	void UpdateGame();
	void UpdateEnd();
	void UpdatePause();

	void UpdateObjects();

	//Draw.
	void DrawTitle();
	void DrawMenu();
	void DrawTutorial();
	void DrawReady();
	void DrawGame();
	void DrawEnd();
	void DrawPause();

	void DrawUI();
	void DrawObjects();
	void DrawReflectMode();

	//���̑�.
	void GameEnd();
	void TakeItem();
};