/*
   - GameManager.h -
   �Q�[���S�̊Ǘ�.
*/
#pragma once
#include "KR_Lib/KR_Scene.h"

//�O���錾.
class NormalLaser_1;
class NormalLaser_2;
class NormalLaser_3;
class NormalLaser_4;
class StraightLaser;

//�Q�[���f�[�^.[�p���s��]
class GameData final
{
public:
	//����.
	static GameData* GetPtr() {
		static GameData inst; //���g�̃C���X�^���X.
		return &inst;
	}

	Scene     scene;			//�V�[���̋L�^�p.
	StageType stage;			//�X�e�[�W���.

	int		  score;			//�X�R�A.
	int		  scoreBef;			//�X�R�A(���ԉ��Z�O)
	int		  bestScore;		//�x�X�g�X�R�A.
	int		  level;			//���x��.

	float	  speedRate;		//�Q�[���i�s���x�{��.
	float	  spawnRate;		//��Q���̏o�����Ԋ���.
	float	  counter;			//�o�ߎ��ԃJ�E���^�[(�X���[�̉e�����󂯂�)

	bool      isReflectMode;	//���˃��[�h���ǂ���.
	float     slowBufCntr;		//�X���[���s����.

	int		  font1;			//�t�H���g.
	int		  font2;			//�t�H���g.
	int		  font3;			//�t�H���g.
	int		  font4;			//�t�H���g.
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
	Timer tmScene[SCENE_COUNT]; //�V�[���ʂɌo�ߎ��Ԃ��L�^����.

	Timer tmGameTime{};     //�Q�[���v������.
	Timer tmReflectMode{};  //�X���[�p������.

	DrawImg imgLogo[2]{};   //�^�C�g�����S�摜.
	DrawImg imgUI{};        //UI�摜.
	DrawImg imgNewRecord{}; //new record.
	DrawImg imgGameOver{};  //gameover.
	DrawImg imgReflect{};   //reflect.

	bool isTitleAnim{};             //Title:     �j�ЃA�j���[�V�������o������.
	bool isBestScoreSound{};        //BestScore: ����炵����.
	bool isItemCountDownSound[3]{}; //Item:      �J�E���g�_�E���̉���炵����.

	bool isGameStart{};             //�Q�[���J�n�T�C��.
	bool isBestScore{};             //�x�X�g�X�R�A�X�V������.

	InputMng* p_input{};
	SoundMng* p_sound{};

public: //�I�u�W�F�N�g.
	NormalLaser_1* laserNor1;
	NormalLaser_2* laserNor2;
	NormalLaser_3* laserNor3;
	NormalLaser_4* laserNor4;
	StraightLaser* laserStr[2];

public:
	//destructor.
	~GameManager();
	//get.
	float GetReflectModeTime() {
		return tmReflectMode.GetPassTime();
	}
	float GetSceneTime(Scene scene) {
		return tmScene[scene].GetPassTime();
	}
	float GetGameTime() {
		return tmGameTime.GetPassTime();
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
	void UpdateGame();
	void UpdateEnd();
	void UpdatePause();

	void UpdateReflectMode();

	//Draw.
	void DrawTitle();
	void DrawMenu();
	void DrawGame();
	void DrawEnd();
	void DrawPause();

	void DrawReflectMode();

	//���̑�.
	void GameEnd();
	void ItemUsed();
	void ReflectModeEnd();
};