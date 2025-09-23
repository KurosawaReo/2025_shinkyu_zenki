/*
   - BackGround.h -
*/
#pragma once

//�O���錾.
class GameData; 
class BackGround;

//�w�i�^�C��.
class BG_Tile
{
	friend class BackGround; //�A�N�Z�X����.
private:
	INT_XY   pos{};
	DBL_XY   sizeRate{};
	DrawImg* img[2]{};

	Timer timer = Timer(COUNT_DOWN, 3); //�������鎞��.

	GameData*   p_data;
	BackGround* p_bg;

public:
	void Init();                //������.
	void Update();              //�X�V.
	void Draw(double slowTime); //�`��.

	void Shine(); //����.
};

//�w�i�N���X.[�p���s��]
class BackGround final
{
//�����̊֌W.
public:
	//���̎擾�p.
	static BackGround& GetInst() {
		static BackGround inst; //���g�̃C���X�^���X.
		return inst;
	}
	//�g�p�֎~.
	BackGround(const BackGround&) = delete;
	BackGround& operator=(const BackGround&) = delete;
private:
	//constructor(�V�K�쐬���ł��Ȃ�����)
	BackGround(){}

//���f�[�^.
private:
	vector<BG_Tile> tiles;      //�w�i�^�C���f�[�^.
	DrawImg         imgBG[2]{}; //�w�i�摜.

	TimerMicro tmShine = TimerMicro(COUNT_DOWN, 1000000/60); //����Ԋu.

	float counter{}; //���Ԍo�ߌv���p.

	GameData* p_data{}; //�Q�[���f�[�^.

public:
	//get.
	float GetCounter() const { return counter; }

	void Init();
	void Update();
	void Draw();
};