#pragma once

//アイテムタイプ.
enum ItemType
{
	Item_Normal, //通常.
	Item_Super,  //強化版.
};
//アイテムデータ.
struct ItemData
{
	ItemType type{};   //タイプ.
	DBL_XY   pos{};    //座標.
	bool     active{}; //有効か.

	float    counter{};
	float    spawnCounter{};
};

//アイテム管理クラス.[継承不可]
class ItemManager final
{
//▼実体関係.
public:
	static ItemManager& GetInst() {
		static ItemManager inst; //自身のインスタンス.
		return inst;
	}

//▼変数.
private:
	ItemData items[ITEM_COUNT]{};
	int      itemMaxCnt{}; //出すアイテムの数.

	bool     isItemUseWait{}; //アイテム発動待ちかどうか.
	bool     isSpawnAble{};   //召喚可能かどうか.

//▼関数.
private:
	//constructor(新規作成をできなくする)
	ItemManager(){}

public:
	//set.
	void SetIsSpawnAble(bool _flag) { isSpawnAble = _flag; }
	//add.
	void AddItemCnt() { itemMaxCnt++; }

	void Init();
	void Reset();
	void Update();
	void Draw();

	void ItemSpawn(int idx); //アイテム召喚.
	void ItemErase(int idx); //アイテム消滅.
	void ItemUse  ();        //アイテム発動.

	void CheckHitPlayer(int idx); //プレイヤーとの当たり判定.

	//使用禁止.
	ItemManager(const ItemManager&) = delete;
	ItemManager& operator=(const ItemManager&) = delete;
};