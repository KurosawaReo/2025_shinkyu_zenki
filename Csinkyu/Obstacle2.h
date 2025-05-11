/*
   - Obstacle2.h -
   障害物管理.(小田島作)
*/
#pragma once

#define MAX_M 100 //ミサイルが飛ぶ最大距離.
//#define PI 3.14159//円周率

class Obstacle2
{
private:
	int    hsc;                    //エネミーの出る間隔.
	int    Mg;                     //エネミーの画像.
	double Mx[MAX_M], My[MAX_M];   //ミサイルのグラフィック.
	double Mv[MAX_M];              //ミサイルデータの使用状態(1:使用中,0:未使用)
	double Ma[MAX_M];              //ミサイルの角度.
	int    Mc[MAX_M];              //ミサイルの追尾カウンタ

	IMG img;
	Player* player;

public:
	void Init(Player*);
	void Update();
	void Draw();
	void enemyMove();
};