/*
   - Stage_Tutorial.h -

   �X�e�[�W: �`���[�g���A��.
*/
#pragma once

//�O���錾.
class GameData;
class GameManager;
class LaserManager;
class MeteorManager;
class Ripples;
class ItemManager;
class Player;
class FireworksManager;
class EffectManager;

//�`���[�g���A��.[�p���s��]
class TutorialStage final
{
public: //����.
	static TutorialStage* GetPtr() {
		static TutorialStage inst; //���g�̃C���X�^���X.
		return &inst;
	}

private: //�f�[�^.

	Font   font[2]{};
	
	int    stepNo{};     //���݂̃X�e�b�v�ԍ�.
	int    stepInNo{};   //���݂̃X�e�b�v���ԍ�.

	double plyMoveSum{}; //�v���C���[�̈ړ�����.

	Timer  startTimer{}; //���ڊJ�n���Ɍv���J�n.
	Timer  endTimer{};   //���ڏI�����Ɍv���J�n.

	GameData*         p_data{};
	GameManager*      p_gameMng{};
	LaserManager*     p_laserMng{};
	MeteorManager*    p_meteorMng{};
	Ripples*          p_ripples{};
	ItemManager*      p_itemMng{};
	Player*           p_player{};
	FireworksManager* p_fireworksMng{};
	EffectManager*    p_effectMng{};
	InputMng*         p_input{};
	SoundMng*         p_sound{};

public:
	//get.
	int GetStepNo() const { return stepNo; }

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

	void DrawTopText1(MY_STRING text, double alpha);
	void DrawTopText2(MY_STRING text, double alpha);
	void DrawTopText3(MY_STRING text, double alpha);
};