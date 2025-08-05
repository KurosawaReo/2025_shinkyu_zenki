/*
   - BackGround.h -
*/
#pragma once

//背景タイル.
class BG_Tile
{
private:
	INT_XY pos;

public:
	//set.
	void SetPos(int _x, int _y) {
		pos = {_x, _y};
	}
	//描画.
	void Draw();
};

//背景クラス.
class BackGround
{
private:
	vector<BG_Tile> tiles;    //背景タイルデータ.
	DrawImgST       imgBG[2]; //背景画像.

	GameData* p_data{}; //ゲームデータ.

public:
	void Init(GameData*);
	void Update();
	void Draw();
};