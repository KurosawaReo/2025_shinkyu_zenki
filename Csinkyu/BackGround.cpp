/*
   - BackGround.cpp -
*/
#include "GameManager.h"
#include "BackGround.h"

using namespace Calc; //�v�Z�@�\���g�p.

// ��*---=[ BG_Tile ]=---*�� //

//������.
void BG_Tile::Init(GameData* _data) {
	p_data = _data;
}
//�X�V.
void BG_Tile::Update() {

	//0�ɂȂ������~.
	if (timer.GetPassTime() <= 0) {
		timer.Reset();
	}
}
//�`��.
void BG_Tile::Draw(bool isSlow, double slowTime) {

	//�ʏ탂�[�h.
	{
		double alpha = 50 + 70 * sin(M_PI * timer.GetPassTime()/3);
		SetDrawBlendModeST(MODE_ALPHA, alpha * (1-slowTime) * (sin(M_PI * (double)(pos.x - pos.y + p_data->counter)/(WINDOW_WID/4))+1)/2);
		img[0]->DrawExtend(pos.ToDblXY(), sizeRate, ANC_MID);
	}
	//���˃��[�h.
	if (isSlow) {
		double alpha = 70 + 100 * sin(M_PI * timer.GetPassTime()/3);
		SetDrawBlendModeST(MODE_ALPHA, alpha * slowTime* (sin(M_PI * (double)(pos.x - pos.y + p_data->counter)/(WINDOW_WID/4))+1)/2);
		img[1]->DrawExtend(pos.ToDblXY(), sizeRate, ANC_MID);
	}
	ResetDrawBlendMode(); //�`�惂�[�h���Z�b�g.
}
//����.
void BG_Tile::Shine() {
	//�������ĂȂ��Ȃ�.
	if(!timer.GetIsMove()){
		timer.Start(); //�J�n.
	}
}

// ��*---=[ BackGround ]=---*�� //

//������.
void BackGround::Init() {

	p_data = GameData::GetPtr();

	imgBG[0].LoadFile(_T("Resources/Images/bg_normal.png"));
	imgBG[1].LoadFile(_T("Resources/Images/bg_reflect.png"));

	{
		INT_XY imgSize  = imgBG[0].GetSize(); //�摜�T�C�Y�擾.
		DBL_XY sizeRate = { 0.1, 0.1 };       //�T�C�Y�{��.

		INT_XY size = { _int_r(imgSize.x * sizeRate.x), _int_r(imgSize.y * sizeRate.y) };

		//�^�C���̂悤�ɓ\��t����.
		for (int x = 0; x < WINDOW_WID + size.x; x += size.x) {
			for (int y = -size.y; y < WINDOW_HEI; y += size.y) {

				BG_Tile tile; //�^�C�����쐬.

				tile.pos.x = x; 
				tile.pos.y = y;
				tile.sizeRate = sizeRate;
				tile.img[0] = &imgBG[0];
				tile.img[1] = &imgBG[1];
				tile.Init(p_data);
 				tiles.push_back(tile); //�z��ɒǉ�.
			}
		}
	}

	tmShine.Start(); //�^�C�}�[�J�n.
}
//�X�V.
void BackGround::Update() {
	
	for (auto& i : tiles) {
		i.Update();
	}
}
//�`��.
void BackGround::Draw() {

	//�X���[���[�h�o�ߎ���.
	float pass = GameManager::GetPtr()->GetSlowModeTime();
	//�ŏ���0.5�b
	double time = 0.5-(pass -(SLOW_MODE_TIME-0.5));
	time = CalcNumEaseOut(time); //�l�̋Ȑ��ϓ�.

	//�������̃p�^�[����p��.(�f�U�C����)
#if false
	//�w�i�f�U�C��.
	for (int x = 0; x < WINDOW_WID; x += 5) {

		int clr = _int45(20 * fabs(sin((double)(x+p_data->counter)/200))); //�F�̕ω�.
		Line line = { {(double)x, 0},{(double)x, WINDOW_HEI}, GetColor(0, clr, clr) };
		DrawLineST(&line, false, 5);
	}

#elif false
	//�w�i�摜.
	{
		INT_XY imgSize = imgBG[0].GetImage()->size; //�摜�T�C�Y�擾.
		DBL_XY sizeRate = {0.1, 0.1};               //�T�C�Y�{��.

		INT_XY size = {_int45(imgSize.x * sizeRate.x), _int45(imgSize.y * sizeRate.y)};
		
		//�^�C���̂悤�ɓ\��t����.
		for (int x = 0; x < WINDOW_WID+size.x; x += size.x) {
			for (int y = -size.y; y < WINDOW_HEI; y += size.y) {
				
				//���W�����������炷.
				INT_XY newPos = {
					_int45(x - fmod(p_data->counter, size.x)), //size�Ŋ������]��.
					_int45(y + fmod(p_data->counter, size.y))
				};
				//�ʏ탂�[�h.
				{
					double alpha = (1-time) * (sin(M_PI*(double)(newPos.x-newPos.y)/(WINDOW_WID/4))+1)/2;
					SetDrawBlendModeST(MODE_ALPHA, 100*alpha);
					imgBG[0].DrawExtendGraphST(newPos, sizeRate, ANC_MID);
				}
				//���˃��[�h.
				if (p_data->isSlow) {
					double alpha = time * (sin(M_PI*(double)(newPos.x-newPos.y)/(WINDOW_WID/4))+1)/2;
					SetDrawBlendModeST(MODE_ALPHA, 100*alpha);
					imgBG[1].DrawExtendGraphST(newPos, sizeRate, ANC_MID);
				}
			}
		}

		ResetDrawBlendMode(); //�`�惂�[�h���Z�b�g.
	}
#else
	//���Ԋu����.
	if (tmShine.IntervalTime()) {
		int idx = RandNum(0, (int)tiles.size()-1);
		tiles[idx].Shine(); //�����_���Ń^�C���𔭌�������.
	}
	//�`��.
	for (auto& i : tiles) {
		i.Draw(p_data->isSlow, time);
	}
#endif

	//�X���[���[�h��.
	if (p_data->isSlow) {
		//�g��.
		Box box = { {WINDOW_WID/2, WINDOW_HEI/2}, {WINDOW_WID * time, WINDOW_HEI * time}, COLOR_PLY_REFLECT };
		DrawBoxST(&box, ANC_MID, false, true);
	}
}