/*
   - GameManager.h -
   �Q�[���S�̊Ǘ�.
*/
#pragma once
#include "KR_Lib/KR_Scene.h"

//�Q�[���f�[�^.[�p���s��]
class GameData final
{
public:
	//����.
	static GameData* GetPtr() {
		static GameData inst; //���g�̃C���X�^���X.
		return &inst;
	}

	Scene scene;      //�V�[���̋L�^�p.
	int   stage;      //�X�e�[�W��.

	int   score;      //�X�R�A.
	int   scoreBef;   //�X�R�A(���ԉ��Z�O)
	int   bestScore;  //�x�X�g�X�R�A.
	int   level;	  //���x��.

	float spawnRate;  //��Q���̏o�����Ԋ���.
	float counter;    //�o�ߎ��ԃJ�E���^�[(�X���[�̉e�����󂯂�)

	int   font1;      //�t�H���g.
	int   font2;      //�t�H���g.
	int   font3;      //�t�H���g.
	int   font4;      //�t�H���g.

	bool  isSlow;     //�X���[���[�h���ǂ���.
};

//�Q�[���}�l�[�W���[.[�p���s��]
class GameManager final
{
public: //����.
	static GameManager* GetPtr() {
		static GameManager inst; //���g�̃C���X�^���X.
		return &inst;
	}

private: //�f�[�^.
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