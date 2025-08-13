/*
   - BackGround.h -
*/
#pragma once

//�w�i�^�C��.
class BG_Tile
{
	friend class BackGround; //�A�N�Z�X����.
private:
	INT_XY    pos{};
	DBL_XY    sizeRate{};
	DrawImgST img[2]{};

	Timer timer = Timer(COUNT_DOWN, 3); //�������鎞��.

	GameData* p_data{};

public:
	void Init(GameData*);                    //������.
	void Update();                           //�X�V.
	void Draw(bool isSlow, double slowTime); //�`��.

	void Shine(); //����.
};

//�w�i�N���X.
class BackGround
{
private:
	vector<BG_Tile> tiles;    //�w�i�^�C���f�[�^.
	DrawImgST       imgBG[2]; //�w�i�摜.

	TimerMicro tmShine = TimerMicro(COUNT_DOWN, 1000000/60); //����Ԋu.

	GameData* p_data{}; //�Q�[���f�[�^.

public:
	void Init(GameData*);
	void Update();
	void Draw();
};