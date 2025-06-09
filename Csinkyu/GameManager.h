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
	//GameManager(); //private�ɂ��邱�ƂŃR���X�g���N�^���g�p�֎~����.

private: //�f�[�^.
	GameData data{}; //�Q�[���f�[�^.

	Timer tmGame     = Timer(0, CountUp);                //�Q�[������.
	Timer tmSlowMode = Timer(SLOW_MODE_TIME, CountDown); //�X���[�p������.

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

	//Update.
	void UpdateTitle();
	void UpdateGame();
	void UpdateEnd();

	//Draw.
	void DrawTitle();
	void DrawGame();
	void DrawEnd();
	void DrawObjests();

	//���̑�.
	void GameEnd();
};