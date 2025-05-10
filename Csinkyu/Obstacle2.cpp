/*
   - Obstacle2.cpp -
   障害物管理.(小田島作)
*/
#include "Player.h"
#include "Obstacle2.h"

void Obstacle2::Init()
{
	LoadGraphST(&img, _T("image/enemy.png"));
	//img.handle;
	//img.size.x;
	//img.size.y;

	for (int i = 0; i < MAX_M; i++)
	{
		Mv[i] = 0;
	}
	//発射カウント値をリセット.
	hsc = 30;
}
void Obstacle2::Update()
{
	enemyMove();
}
void Obstacle2::Draw()
{
	for (int i = 0; i < MAX_M; i++)
	{
		//ミサイルデータが有効でない場合は次に移る.
		if (Mv[i] == 0) continue;

		double size = 0.1; //仮.
		DrawRotaGraph(Mx[i], My[i], size, Ma[i], img.handle, TRUE);
	}
}

//敵の移動.
void Obstacle2::enemyMove()
{
	//ショットカウンタを減らす.
	hsc--;
	//カウンタが0になったらミサイル発射.
	if (hsc == 0)
	{
		//使われてないミサイルデータを探す.
		for (int i = 0; i < MAX_M; i++)
		{
			//使われてないデータを見つけたら.
			if (Mv[i] == 0) {
		
				//ミサイルの位置を設定.
				Mx[i] = 320 + 16; //砲台のX座標.
				My[i] = 30 + 16;  //砲台のy座標.

				//角度をセット.
				Ma[i] = M_PI / 2;

				//追尾カウンタをセット.
				Mc[i] = 0;

				//ショットデータを使用中にセット.
				Mv[i] = 1;
			}
		}
		//発射カウンタ値をセット.
		hsc = 30;
	}

	//ミサイルの移動処理.
	for (int i = 0; i < MAX_M; i++)
	{
		//ミサイルデータが無効だったらスキップ.
		if (Mv[i] == 0) continue;

		int px  = (Mx[i] > player.GetX() && Mx[i] < player.GetX() + 16);
		int px2 = (player.GetX() > Mx[i] && player.GetX() < Mx[i] + 16);
		int py  = (My[i] > player.GetY() && My[i] < player.GetY() + 16);
		int py2 = (player.GetY() > My[i] && player.GetY() < My[i] + 16);

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

			//自分の進んでる方向.
			bx = cos(Ma[i]);
			by = sin(Ma[i]);
			//本来進むべき方向.
			ax = (player.GetX() + 16) - Mx[i];
			ay = (player.GetY() + 16) - My[i];

			//外積を利用し向きを標準側に向ける.
			Ma[i] += (ax * by - ay * bx < 0.0) ? + (M_PI/180) * 8 : -(M_PI/180) * 8;
		}
		//追尾カウンタ加算.
		Mc[i]++;
		//移動する.
		Mx[i] += (int)(cos(Ma[i]) * 6.0);
		My[i] += (int)(sin(Ma[i]) * 6.0);

		//画面外にでたらミサイルデータを無効にする.
		if (Mx[i] < -100 || Mx[i]>740 || My[i] < -100 || My[i]>500) Mv[i] = 0;
	}
}

/*
//小田島作の元のプログラム

void Obstacle2::enemyMove()
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
			Ma[i] = M_PI / 2;

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

		int px  = (Mx[i] > player.GetX() && Mx[i] < player.GetX() + 16);
		int px2 = (player.GetX() > Mx[i] && player.GetX() < Mx[i] + 16);
		int py  = (My[i] > player.GetY() && My[i] < player.GetY() + 16);
		int py2 = (player.GetY() > My[i] && player.GetY() < My[i] + 16);

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
			ax = (player.GetX() + 16) - Mx[i];
			ay = (player.GetY() + 16) - My[i];

			//外積を利用し向きを標準側に向ける.
			Ma[i] += (ax * by - ay * bx < 0.0) ? + (M_PI/180) * 8 : -(M_PI/180) * 8;

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
*/