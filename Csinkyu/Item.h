#pragma once
#include "Player.h"  // Player �N���X���g�p���邽��

class Item
{
private:
	DBL_XY pos{};    //���W.
	DBL_XY size{};   //�T�C�Y.
	BOOL   active{}; //�L����.

	int    itemGraph{};
	float  itemCounter{};

	GameData* p_gamedata{}; //�Q�[���f�[�^.
	Player*   p_player{};   //�v���C���[�f�[�^.

public:
	void Init(GameData*, Player*);
	void Update();
	void Draw();
	void ItemMove(); //�A�C�e��.
	void Reset();    // �A�C�e���̃��Z�b�g�i�Đ����p�j

	// �����蔻��֘A
	BOOL CheckHitPlayer(); // �v���C���[�Ƃ̓����蔻��
	void OnHitPlayer();    // ���������Ƃ��̏���

	// �֗��Ȋ֐����ǉ�
	BOOL IsActive() const { return active; }
};