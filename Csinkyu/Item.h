#pragma once
#include "Player.h"  // Player �N���X���g�p���邽��

class Item
{
private:
	DBL_XY pos;  //���W.
	INT_XY size; //�T�C�Y.
	UINT   clr;  //�F.
	BOOL   active; //�L����.

	float Ix, Iy;
	double itemX, itemY;
	int itemFlag;
	int itemW, itemH, itemGraph;
	int itemCounter;
public:
	void Init();
	void Update();
	void Draw();
	void ItemMove(); //�A�C�e��.
	void Reset();    // �A�C�e���̃��Z�b�g�i�Đ����p�j

	// �����蔻��֘A
	BOOL CheckHitPlayer(Player* player);  // �v���C���[�Ƃ̓����蔻��
	void OnHitPlayer();                   // ���������Ƃ��̏���

	// �֗��Ȋ֐����ǉ�
	BOOL IsActive() const { return active && itemFlag; }
	double GetX() const { return itemX; }
	double GetY() const { return itemY; }
};