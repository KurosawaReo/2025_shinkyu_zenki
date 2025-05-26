/*
   - Item.cpp -
   Item管理.
*/
#include "Item.h"
#include "Player.h"

//初期化.
void Item::Init()
{
	active = TRUE;
}
//更新.
void Item::Update()
{
	
}
//描画.
void Item::Draw()
{
	

	//有効なら.
	if (active) {
		unsigned int Cr;
		Cr = GetColor(0, 255, 255); // 白色
		int x  = ITEM_SIZE / 2;
		int y  = ITEM_SIZE / 2;
		int tx = ITEM_SIZE / 2;
		int ty = ITEM_SIZE / 2;
		DrawBox(x, y, tx, ty, Cr, TRUE);

		
	}
}


void Item::ItemMove()
{
	
}