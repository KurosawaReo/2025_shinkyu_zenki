#pragma once
#include "Player.h"  // Player クラスを使用するため

//アイテムタイプ.
enum ItemType
{
	Item_Normal, //通常.
	Item_Super,  //強化版.
};
class Item
{
private:
	ItemType type{};   //タイプ.

	DBL_XY   pos{};    //座標.
	DBL_XY   size{};   //サイズ.
	BOOL     active{}; //有効か.

	int      itemGraph{};
	float    itemCounter{};

	GameData*      p_gamedata{}; //ゲームデータ.
	Player*        p_player{};   //プレイヤーデータ.
	EffectManager* p_effectMng{};

public:
	void Init(GameData*, Player*, EffectManager*);
	void Reset();
	void Update();
	void Draw();

	void ItemMove();  //移動.
	void ItemSpawn(); //アイテム召喚.

	//当たり判定関連.
	BOOL CheckHitPlayer(); // プレイヤーとの当たり判定
	void OnHitPlayer();    // 当たったときの処理

	BOOL IsActive() const { return active; }
};