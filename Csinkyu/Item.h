#pragma once
#include "Player.h"  // Player クラスを使用するため

class Item
{
private:
	DBL_XY pos;  //座標.
	INT_XY size; //サイズ.
	UINT   clr;  //色.
	BOOL   active; //有効か.

	float Ix, Iy;
	double itemX, itemY;
	int itemFlag;
	int itemW, itemH, itemGraph;
	int itemCounter;
public:
	void Init();
	void Update();
	void Draw();
	void ItemMove(); //アイテム.
	void Reset();    // アイテムのリセット（再生成用）

	// 当たり判定関連
	BOOL CheckHitPlayer(Player* player);  // プレイヤーとの当たり判定
	void OnHitPlayer();                   // 当たったときの処理

	// 便利な関数も追加
	BOOL IsActive() const { return active && itemFlag; }
	double GetX() const { return itemX; }
	double GetY() const { return itemY; }
};