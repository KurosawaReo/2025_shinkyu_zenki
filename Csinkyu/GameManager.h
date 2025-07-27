/*
   - GameManager.h -
   �Q�[���S�̊Ǘ�.
*/
#pragma once

//�Q�[���}�l�[�W���[.
class GameManager 
{
private: //����.
	static GameManager self; //���g�̎���.

private: //�f�[�^.
	GameData data{}; //�Q�[���f�[�^.

	//�V�[���ʂɌo�ߎ��Ԃ��L�^����.
	Timer tmScene[SCENE_COUNT] = {
		Timer(CountUp, 0), //Title�V�[��.
		Timer(CountUp, 0), //Ready�V�[��.
		Timer(CountUp, 0), //Game�V�[��.
		Timer(CountUp, 0), //End�V�[��.
		Timer(CountUp, 0), //Pause�V�[��.
	};
	Timer tmSlowMode = Timer(CountDown, SLOW_MODE_TIME); //�X���[�p������.

	DrawImgST imgLogo[2]; //�^�C�g�����S�摜.
	DrawImgST imgUI;      //UI�摜.

	BOOL isFinTitleAnim{}; //�^�C�g���A�j���[�V�����p.
	BOOL isFinScoreAnim{}; //�ō��X�R�A�A�j���[�V�����p.
	BOOL isItemCount[3]{}; //�A�C�e���J�E���g�_�E���̉���炵����.

	InputST* p_input{};
	SoundST* p_sound{};

public:
	//���̂̎擾.
	static GameManager* GetPtr() {
		return &self;
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

	void DrawBG();
	void DrawUI();
	void DrawObjects();
	void DrawReflectMode();

	//���̑�.
	void GameEnd();
	void TakeItem();
};