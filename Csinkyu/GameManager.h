/*
   - GameManager.h -
   �Q�[���S�̊Ǘ�.
*/
#pragma once

//�Q�[���}�l�[�W���[.
class GameManager 
{
private:
	GameData data{};     //�Q�[���f�[�^.

	Timer    tmGame;     //�Q�[������.
	Timer    tmSlowMode; //�X���[�p������.

public:

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
};