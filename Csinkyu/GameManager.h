/*
   - GameManager.h -
   �Q�[���S�̊Ǘ�.
*/
#pragma once

//�Q�[���}�l�[�W���[.
class GameManager 
{
private:
	GameData data{}; //�Q�[���f�[�^.

	Timer tmGame     = Timer(0, CountUp);                //�Q�[������.
	Timer tmSlowMode = Timer(SLOW_MODE_TIME, CountDown); //�X���[�p������.

public:
	static GameManager* pSelf; //���g�̃|�C���^.

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