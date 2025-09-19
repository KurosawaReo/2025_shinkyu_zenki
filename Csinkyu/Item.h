#pragma once

//�O���錾.
class Player;
class EffectManager;

//�A�C�e���^�C�v.
enum ItemType
{
	Item_Normal, //�ʏ�.
	Item_Super,  //������.
};
//�A�C�e���f�[�^.
struct ItemData
{
	ItemType type{};   //�^�C�v.
	DBL_XY   pos{};    //���W.
	bool     active{}; //�L����.

	float    counter{};
	float    spawnCounter{};
};

//�A�C�e���Ǘ��N���X.[�p���s��]
class ItemManager final
{
public: //����.
	static ItemManager* GetPtr() {
		static ItemManager inst; //���g�̃C���X�^���X.
		return &inst;
	}

private:
	ItemData data[2];
	int      itemCnt{}; //�o���A�C�e���̐�.

	GameData*      p_gamedata{};  //�Q�[���f�[�^.
	Player*        p_player{};    //�v���C���[�f�[�^.
	EffectManager* p_effectMng{};

public:
	//add.
	void AddItemCnt() { itemCnt++; }

	void Init();
	void Reset();
	void Update();
	void Draw();

	void ItemSpawn(int idx); //�A�C�e������.
	void ItemErase(int idx); //�A�C�e������.

	//�����蔻��֘A.
	void CheckHitPlayer(int idx); // �v���C���[�Ƃ̓����蔻��
	void OnHitPlayer   (int idx); // ���������Ƃ��̏���

//	bool IsActive() const { return active; }
};