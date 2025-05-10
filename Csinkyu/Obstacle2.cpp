/*
   - Obstacle.cpp -
   障害物管理.
*/
#include"Obstacle2.h"
#include "myDraw.h"
#include"Player.h"


#define MAX_M 100
#define PI 3.14159//円周率

int hsc;                    //エネミーの出る間隔.
int Mg;                     //エネミーの画像.
int Mx[MAX_M], My[MAX_M];   //ミサイルのグラフィック.
int Mv[MAX_M];              //ミサイルデータの使用状態(1:使用中0:未使用)
double Ma[MAX_M];           //ミサイルの角度.
int Mc[MAX_M];              //ミサイルの追尾カウンタ

IMG img;
void eneyMove();
Player player;

void Obstacle2::Init()
{

	Mg = LoadGraphST(&img, _T("image/enemy.png"));
	img.handle;
	img.size.x;
	img.size.y;

	for (int i = 0; i < MAX_M; i++)
	{
		Mv[i] = 0;
	}
	//発射カウント値をリセット.
	hsc = 30;
}
void Obstacle2::Update()
{
	eneyMove();
}
void Obstacle2::Draw()
{
	for (int i = 0; i < MAX_M; i++)
	{
		//ミサイルデータが有効でない場合は次に移る.
		if (Mv[i] == 0)continue;
		DrawRotaGraph(Mx[i], My[i], 1.0, Ma[i], Mg, TRUE);
	}

	DrawGraph(0, 0, img.handle, TRUE);
}

void eneyMove()
{
	//ショットカウンタを減らす.
	hsc--;
	//カウンタが0になったらミサイル発射.
	if (hsc == 0)
	{
		//使われてないミサイルデータを探す.
		int i;
		for (i = 0; i < MAX_M; i++)
		{
			if (Mv[i] == 0)break;
		}
		//もし使われてないミサイルデータがあったらショットを出す.
		if (i != MAX_M)
		{
			//ミサイルの位置を設定.
			Mx[i] = 320 + 16;//砲台のX座標.
			My[i] = 30 + 16;//砲台のy座標.

			//角度をセット.
			Ma[i] = PI / 2;

			//追尾カウンタをセット.
			Mc[i] = 0;

			//ショットデータを使用中にセット.
			Mv[i] = 1;

		}
		//発射カウンタ値をセット.
		hsc = 30;
	}
	//ミサイルの移動処理.
	for (int i = 0; i < MAX_M; i++)
	{
		//ミサイルデータが無効だったらスキップ.
		if (Mv[i] == 0)continue;

		int px = (Mx[i] > PlayerX && Mx[i] < PlayerX + 16);
		int px2 = (PlayerX > Mx[i] && PlayerX < Mx[i] + 16);
		int py = (My[i] > PlayerY && My[i] < PlayerY + 16);
		int py2 = (PlayerY > My[i] && PlayerY < My[i] + 16);

		//playerに当ったらミサイルデータを無効にする.
		if ((px || px2) && (py || py2))
		{
			Mv[i] = 0;
			continue;
		}
		//追尾カウンタが規定値に来ていなければ追尾処理.
		if (Mc[i] < 100)
		{
			double ax, ay, bx, by;

			//bx,by自分の進んでる方向ax,ay本来進むべき方向.
			bx = cos(Ma[i]);
			by = sin(Ma[i]);
			ax = (PlayerX + 16) - Mx[i];
			ay = (PlayerY + 16) - My[i];

			//外積を利用し向きを標準側に向ける.
			Ma[i] += (ax * by - ay * bx < 0.0) ? +PI / 180 * 8 : -PI / 180 * 8;

		}
		//追尾カウンタ加算.
		Mc[i]++;
		//移動する.
		Mx[i] += (int)(cos(Ma[i]) * 6.0);
		My[i] += (int)(sin(Ma[i]) * 6.0);

		//画面外にでたらミサイルデータを無効にする.
		if (Mx[i] < -100 || Mx[i]>740 || My[i] < -100 || My[i]>500)Mv[i] = 0;


	}
}

