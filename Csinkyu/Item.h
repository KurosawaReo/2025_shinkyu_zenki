#pragma once
#include "Player.h"  // Player �N���X���g�p���邽��

//�A�C�e���^�C�v.
enum ItemType
{
	Item_Normal, //�ʏ�.
	Item_Super,  //������.
};
class Item
{
private:
	ItemType type{};   //�^�C�v.

	DBL_XY   pos{};    //���W.
	DBL_XY   size{};   //�T�C�Y.
	BOOL     active{}; //�L����.

	int      itemGraph{};
	float    itemCounter{};

	GameData*      p_gamedata{}; //�Q�[���f�[�^.
	Player*        p_player{};   //�v���C���[�f�[�^.
	EffectManager* p_effectMng{};

public:
	void Init(GameData*, Player*, EffectManager*);
	void Reset();
	void Update();
	void Draw();

	void ItemMove();  //�ړ�.
	void ItemSpawn(); //�A�C�e������.

	//�����蔻��֘A.
	BOOL CheckHitPlayer(); // �v���C���[�Ƃ̓����蔻��
	void OnHitPlayer();    // ���������Ƃ��̏���

	BOOL IsActive() const { return active; }
};