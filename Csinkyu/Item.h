#pragma once

//�O���錾.
class Player;
class LaserManager;
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
	ItemData items[ITEM_COUNT]{};
	int      itemMaxCnt{}; //�o���A�C�e���̐�.

	DrawImg  imgItem{}; //�A�C�e���摜.

	bool     isItemUseWait{}; //�A�C�e�������҂����ǂ���.
	bool     isSpawnAble{};   //�����\���ǂ���.

	GameData*      p_gamedata{};  //�Q�[���f�[�^.
	Player*        p_player{};    //�v���C���[�f�[�^.
	LaserManager*  p_laserMng{};
	EffectManager* p_effectMng{};

public:
	//set.
	void SetIsSpawnAble(bool _flag) { isSpawnAble = _flag; }
	//add.
	void AddItemCnt() { itemMaxCnt++; }

	void Init();
	void Reset();
	void Update();
	void Draw();

	void ItemSpawn(int idx); //�A�C�e������.
	void ItemErase(int idx); //�A�C�e������.
	void ItemUse  ();        //�A�C�e������.

	void CheckHitPlayer(int idx); //�v���C���[�Ƃ̓����蔻��.
};