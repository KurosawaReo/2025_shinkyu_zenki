/*
   - Obstacle2.cpp -
   障害物管理.(小田島作)
*/
#include "Player.h"
#include "Obstacle2.h"

void Obstacle2::Init(Player* _player)
{
	LoadGraphST(&img, _T("image/enemy.png"));
	//img.handle;
	//img.size.x;
	//img.size.y;

	player = _player; //プレイヤーの実体アドレスをもらう.

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
	//extrn変数を使用してプレイヤーにアクセス.
	//extern Player player;

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

				//プレイヤーの方向へ向かう角度を計算.
				double px = player->GetPos().x + PLAYER_SIZE / 2.0;//プレイヤーの中心x.
				double py = player->GetPos().y + PLAYER_SIZE / 2.0;//プレイヤーの中心y.
				Ma[i] = atan2(py - My[i], px - Mx[i]); // プレイヤーへの角度を計算.
				//角度をセット.
				//Ma[i] = M_PI / 2;

				//追尾カウンタをセット.
				Mc[i] = 0;

				//ショットデータを使用中にセット.
				Mv[i] = 1;

				//一発だけ発射するためループを抜ける.

				break;
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

		//衝突判定
		bool isCollison = false;

		int x = Mx[i] < player->GetPos().x + PLAYER_SIZE;
		int x2 = Mx[i] + 16 > player->GetPos().x;
		int y = My[i] < player->GetPos().y + PLAYER_SIZE;
		int y2 = My[i] + 16 > player->GetPos().y;
		//プレイヤーとミサイルの距離が重ねっているか確認.
		if (x && x2 && y && y2)
		{
			isCollison = true;
		}

		if (isCollison)
		{
			Mv[i] = 0;
			continue;
		}

		//追尾カウンタが規定値に来ていなければ追尾処理.
		if (Mc[i] < 100)
		{

			//プレイヤーへの中心座標を計算.
			double px = player->GetPos().x + PLAYER_SIZE / 2.0;
			double py = player->GetPos().y + PLAYER_SIZE / 2.0;

			double targetAngle = atan2(py - My[i], px - Mx[i]);

			//プレイヤーへの角度を計算.
			double angleDiff = targetAngle - Ma[i];

			//現在の角度と目標角度の差を計算.
			while (angleDiff > M_PI)angleDiff -= 2 * M_PI;
			while (angleDiff < -M_PI)angleDiff += 2 * M_PI;

			//角度の変化量を制限してらかな追尾を実現.
			double turnSpeed = (M_PI / 180.0) * 5.0;//1フレームあたりの最大回転角度.

			//角度を更新.
			if (fabs(angleDiff) < 0.001)
			{
				// 角度差がほぼ0の場合は調整しない.
				// 何もしない.
			}
			else if (angleDiff > 0)
			{
				Ma[i] += fmin(turnSpeed, angleDiff);
			}
			else
			{
				Ma[i] += fmax(-turnSpeed, angleDiff);
			}
		}
		//追尾カウンタ加算.
		Mc[i]++;
		//移動する.
		double speed = 4.0; // ミサイルの速度
		Mx[i] += (int)(cos(Ma[i]) * speed);
		My[i] += (int)(sin(Ma[i]) * speed);

		//画面外にでたらミサイルデータを無効にする.
		if (Mx[i] < -100 || Mx[i]>740 || My[i] < -100 || My[i]>500)
		{
			Mv[i] = 0;
		}
	}
}

