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
class UIManager;

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
	
	int    stepNo{};          //���݂̃X�e�b�v�ԍ�.
	int    stepInNo{};        //���݂̃X�e�b�v���ԍ�.

	double plyMoveSum{};      //�v���C���[�̈ړ�����.

	bool   isTakeItem{};      //�A�C�e������������ǂ���.
	bool   isReflectLaser{};  //���[�U�[�𔽎˂������ǂ���.
	bool   isReflectFinish{}; //���˃��[�h���I��������ǂ���.
	bool   isBreakMeteor{};   //覐΂��󂵂����ǂ���.

	Timer  startTimer{};      //���ڊJ�n���Ɍv���J�n.
	Timer  endTimer{};        //���ڏI�����Ɍv���J�n.

	GameData*         p_data{};
	GameManager*      p_gameMng{};
	LaserManager*     p_laserMng{};
	MeteorManager*    p_meteorMng{};
	Ripples*          p_ripples{};
	ItemManager*      p_itemMng{};
	Player*           p_player{};
	FireworksManager* p_fireworksMng{};
	EffectManager*    p_effectMng{};
	UIManager*        p_uiMng{};
	InputMng*         p_input{};
	SoundMng*         p_sound{};

public:
	//set.
	void SetTakeItem     (bool _flag) { isTakeItem      = _flag; }
	void SetReflectLaser (bool _flag) { isReflectLaser  = _flag; }
	void SetReflectFinish(bool _flag) { isReflectFinish = _flag; }
	void SetBreakMeteor  (bool _flag) { isBreakMeteor   = _flag; }
	//get
	int GetStepNo() const { return stepNo; }

	void Init();
	void Reset();
	void Update();
	void Draw();

	void ResetSignFlag();
	void StepInEnd();

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