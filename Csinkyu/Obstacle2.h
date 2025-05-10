/*
   - Obstacle.h -
   障害物管理.
*/
#pragma once

#define MAX_M 100 //ミサイルが飛ぶ最大距離.
//#define PI 3.14159//円周率

class Obstacle2
{
private:
	int    hsc;                    //エネミーの出る間隔.
	int    Mg;                     //エネミーの画像.
	int    Mx[MAX_M], My[MAX_M];   //ミサイルのグラフィック.
	int    Mv[MAX_M];              //ミサイルデータの使用状態(1:使用中0:未使用)
	double Ma[MAX_M];              //ミサイルの角度.
	int    Mc[MAX_M];              //ミサイルの追尾カウンタ

	IMG img;
	Player player;

public:
	void Init();
	void Update();
	void Draw();
	void enemyMove();
};