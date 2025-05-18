/*
   - Obstacle4.cpp -
   障害物管理.(小田島作)
*/
#include "DxLib.h"
#include <math.h>
#include "Player.h"
#include "Obstacle4.h"

// 外部定義があれば追加
#define PLAYER_SIZE 32
#define WINDOW_WID 640
#define WINDOW_HEI 480

void Obstacle4::Init(Player* _player)
{
	player = _player;

	Hx = 320;
	Hy = 30;

	Hm = 3;
	Hsc = 30;

	for (int i = 0; i < MAX_L; i++)
		Ld[i].ValidFlag = 0;

	for (int i = 0; i < LINE_MAXNUM; i++)
		Line[i].ValidFlag = 0;
}

void Obstacle4::Update()
{
	if (player->GetActive()) {
		enemy4Move();
	}
}

void Obstacle4::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	for (int i = 0; i < LINE_MAXNUM; i++)
	{
		if (Line[i].ValidFlag == 0) continue;

		DrawLine(Line[i].x1, Line[i].y1,
			Line[i].x2, Line[i].y2,
			GetColor(0, 255 - Line[i].Counter * 4, 0));

		Line[i].Counter++;
		if (Line[i].Counter == 64) Line[i].ValidFlag = 0;
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	DrawBox(Hx - 8, Hy - 8, Hx + 8, Hy + 8, GetColor(255, 255, 0), TRUE);
}

void Obstacle4::enemy4Move()
{
	for (int i = 0; i < MAX_L; i++)
	{
		int xb, yb;

		if (Ld[i].ValidFlag == 0) continue;

		DBL_XY playerPos = player->GetPos();
		double Px = playerPos.x;
		double Py = playerPos.y;

		double halfSize = PLAYER_SIZE / 2.0;

		if ((Ld[i].x > Px - halfSize && Ld[i].x < Px + halfSize) &&
			(Ld[i].y > Py - halfSize && Ld[i].y < Py + halfSize))
		{
			Ld[i].ValidFlag = 0;
			continue;
		}

		if (Ld[i].Counter < 200)
		{
			double targetAngle = atan2(Py - Ld[i].y, Px - Ld[i].x);
			double currentAngle = atan2(Ld[i].sy, Ld[i].sx);
			double angleDiff = targetAngle - currentAngle;

			while (angleDiff > PI) angleDiff -= 2 * PI;
			while (angleDiff < -PI) angleDiff += 2 * PI;

			const double maxTurn = PI / 180 * 15;
			if (angleDiff > maxTurn) angleDiff = maxTurn;
			if (angleDiff < -maxTurn) angleDiff = -maxTurn;

			double newAngle = currentAngle + angleDiff;
			Ld[i].sx += (int)(cos(newAngle) * 30);
			Ld[i].sy += (int)(sin(newAngle) * 30);
		}

		Ld[i].Counter++;

		xb = Ld[i].x;
		yb = Ld[i].y;

		Ld[i].x = (Ld[i].x * 100 + Ld[i].sx) / 100;
		Ld[i].y = (Ld[i].y * 100 + Ld[i].sy) / 100;

		for (int j = 0; j < LINE_MAXNUM; j++)
		{
			if (Line[j].ValidFlag == 0)
			{
				Line[j].x1 = xb;
				Line[j].y1 = yb;
				Line[j].x2 = Ld[i].x;
				Line[j].y2 = Ld[i].y;
				Line[j].Counter = 0;
				Line[j].ValidFlag = 1;
				break;
			}
		}

		if (Ld[i].x < -100 || Ld[i].x > WINDOW_WID + 100 ||
			Ld[i].y < -100 || Ld[i].y > WINDOW_HEI + 100)
		{
			Ld[i].ValidFlag = 0;
		}
	}

	// 砲台の移動とレーザー発射
	{
		Hx += Hm;

		if (Hx > WINDOW_WID - 16 || Hx < 0) Hm *= -1;

		Hsc--;

		if (Hsc == 0)
		{
			for (int i = 0; i < MAX_L; i++)
			{
				if (Ld[i].ValidFlag == 0)
				{
					// プレイヤー座標取得
					DBL_XY playerPos = player->GetPos();
					double Px = playerPos.x;
					double Py = playerPos.y;

					// 発射位置
					double startX = Hx + 16;
					double startY = Hy + 16;

					// プレイヤー方向へ初期角度計算
					double angle = atan2(Py - startY, Px - startX);

					Ld[i].x = startX;
					Ld[i].y = startY;
					Ld[i].sx = (int)(cos(angle) * 30);
					Ld[i].sy = (int)(sin(angle) * 30);
					Ld[i].Counter = 0;
					Ld[i].LogNum = 0;
					Ld[i].ValidFlag = 1;
					break;
				}
			}
			Hsc = 30;
		}
	}
}
