/*
   - Obstacle.cpp -
   障害物管理.
*/
#include "Obstacle2.h"
#include "myDrawST.h"

#define MAX_M 100
#define PI 3.14159//円周率

int hsc;//エネミーの出る間隔.
int Mg; //エネミーの画像.
int Mx[MAX_M], My[MAX_M];//ミサイルのグラフィック.
int Mv[MAX_M]; //ミサイルデータの使用状態(1:使用中0:未使用)
double Ma[MAX_M];//ミサイルの角度.


void Obstacle::Init()
{
	Mg = LoadGraph(_T("image/enemy.png"));
}
void Obstacle::Update()
{
	enemyMove();
}
void Obstacle::Draw()
{
	//IMG img;
	//LoadGraphST(&img, _T()))
}

void Obstacle::enemyMove()
{
}