/*
   - Item.cpp -
   Item�Ǘ�.
*/
#include "Item.h"
#include "Player.h"

//������.
void Item::Init()
{
	active = TRUE;
}
//�X�V.
void Item::Update()
{
	
}
//�`��.
void Item::Draw()
{
	

	//�L���Ȃ�.
	if (active) {
		unsigned int Cr;
		Cr = GetColor(0, 255, 255); // ���F
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