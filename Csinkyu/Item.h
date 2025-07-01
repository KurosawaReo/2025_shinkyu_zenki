#pragma once
#include "Player.h"  // Player �N���X���g�p���邽��

class Item
{
private:
	DBL_XY pos{};    //���W.
	INT_XY size{};   //�T�C�Y.
	UINT   clr[2]{}; //�F.
	BOOL   active{}; //�L����.

	float  Ix{}, Iy{};
	double itemX{}, itemY{};
	double itemW{}, itemH{};
	int    itemFlag{};
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
	BOOL IsActive() const { return active && itemFlag; }
	double GetX() const { return itemX; }
	double GetY() const { return itemY; }
};