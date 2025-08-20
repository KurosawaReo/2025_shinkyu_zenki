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

	DrawImgST imgLogo[2];   //�^�C�g�����S�摜.
	DrawImgST imgUI[4];     //UI�摜.
	DrawImgST imgNewRecord; //new record.
	DrawImgST imgGameOver;  //gameover.

	bool isTitleAnim{};             //Title:     �j�ЃA�j���[�V�������o������.
	bool isBestScoreSound{};        //BestScore: ����炵����.
	bool isItemCountDownSound[3]{}; //Item:      �J�E���g�_�E���̉���炵����.

	InputST* p_input{};
	SoundST* p_sound{};

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
	void UpdateReady();
	void UpdateGame();
	void UpdateEnd();
	void UpdatePause();

	void UpdateObjects();

	//Draw.
	void DrawTitle();
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