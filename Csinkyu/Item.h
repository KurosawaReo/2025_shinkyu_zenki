#pragma once

//前方宣言.
class Player;
class LaserManager;
class EffectManager;

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
public: //実体.
	static ItemManager* GetPtr() {
		static ItemManager inst; //自身のインスタンス.
		return &inst;
	}

private:
	ItemData items[ITEM_COUNT]{};
	int      itemMaxCnt{}; //出すアイテムの数.

	DrawImg  imgItem{}; //アイテム画像.

	bool     isItemUseWait{}; //アイテム発動待ちかどうか.
	bool     isSpawnAble{};   //召喚可能かどうか.

	GameData*      p_gamedata{};  //ゲームデータ.
	Player*        p_player{};    //プレイヤーデータ.
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

	void ItemSpawn(int idx); //アイテム召喚.
	void ItemErase(int idx); //アイテム消滅.
	void ItemUse  ();        //アイテム発動.

	void CheckHitPlayer(int idx); //プレイヤーとの当たり判定.
};