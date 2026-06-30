#pragma once
#include "Global.h"

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

//アイテム管理クラス.
class ItemManager final : public ManagerBase
{
//▼ ===== 変数 ===== ▼.
private:
	ItemData items[ITEM_COUNT]{};
	int      itemMaxCnt{}; //出すアイテムの数.

	bool     isItemUseWait{}; //アイテム発動待ちかどうか.

//▼ ===== 関数 ===== ▼.
public:
	//コンストラクタ.
	ItemManager(int order) : ManagerBase(order) {}

	//set.
	void SetItemMaxCnt(int count) { itemMaxCnt = count; }

	void Init()   override;
	void Reset()  override;
	void Update() override;
	void Draw()   override;

	void ItemSpawn(int idx); //アイテム召喚.
	void ItemErase(int idx); //アイテム消滅.
	void ItemUse  ();        //アイテム発動.

	void CheckHitPlayer(int idx); //プレイヤーとの当たり判定.

	//使用禁止.
	ItemManager(const ItemManager&) = delete;
	ItemManager& operator=(const ItemManager&) = delete;
};