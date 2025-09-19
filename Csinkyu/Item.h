#pragma once

//前方宣言.
class Player;
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
	ItemData data[2];
	int      itemCnt{}; //出すアイテムの数.

	GameData*      p_gamedata{};  //ゲームデータ.
	Player*        p_player{};    //プレイヤーデータ.
	EffectManager* p_effectMng{};

public:
	//add.
	void AddItemCnt() { itemCnt++; }

	void Init();
	void Reset();
	void Update();
	void Draw();

	void ItemSpawn(int idx); //アイテム召喚.
	void ItemErase(int idx); //アイテム消滅.

	//当たり判定関連.
	void CheckHitPlayer(int idx); // プレイヤーとの当たり判定
	void OnHitPlayer   (int idx); // 当たったときの処理

//	bool IsActive() const { return active; }
};