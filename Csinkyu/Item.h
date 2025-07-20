#pragma once
#include "Player.h"  // Player クラスを使用するため

class Item
{
private:
	DBL_XY pos{};    //座標.
	DBL_XY size{};   //サイズ.
	BOOL   active{}; //有効か.

	int    itemGraph{};
	float  itemCounter{};

	GameData*      p_gamedata{}; //ゲームデータ.
	Player*        p_player{};   //プレイヤーデータ.
	EffectManager* p_effectMng{};

public:
	void Init(GameData*, Player*, EffectManager*);
	void Update();
	void Draw();
	void ItemMove(); //アイテム.
	void Reset();    // アイテムのリセット（再生成用）

	// 当たり判定関連
	BOOL CheckHitPlayer(); // プレイヤーとの当たり判定
	void OnHitPlayer();    // 当たったときの処理

	// 便利な関数も追加
	BOOL IsActive() const { return active; }
};