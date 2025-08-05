/*
   - BackGround.h -
*/
#pragma once

//�w�i�^�C��.
class BG_Tile
{
private:
	INT_XY pos;

public:
	//set.
	void SetPos(int _x, int _y) {
		pos = {_x, _y};
	}
	//�`��.
	void Draw();
};

//�w�i�N���X.
class BackGround
{
private:
	vector<BG_Tile> tiles;    //�w�i�^�C���f�[�^.
	DrawImgST       imgBG[2]; //�w�i�摜.

	GameData* p_data{}; //�Q�[���f�[�^.

public:
	void Init(GameData*);
	void Update();
	void Draw();
};