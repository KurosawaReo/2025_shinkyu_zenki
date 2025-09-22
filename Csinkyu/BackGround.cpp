/*
   - BackGround.cpp -
*/
#include "GameManager.h"
#include "BackGround.h"

using namespace Calc; //�v�Z�@�\���g�p.

// ��*---=[ BG_Tile ]=---*�� //

//������.
void BG_Tile::Init() {
	p_data = GameData::GetPtr();
	p_bg   = BackGround::GetPtr();
}
//�X�V.
void BG_Tile::Update() {

	//0�ɂȂ������~.
	if (timer.GetPassTime() <= 0) {
		timer.Reset();
	}
}
//�`��.
void BG_Tile::Draw(double slowTime) {

	//�ʏ탂�[�h.
	{
		double alpha = 60 + 70 * sin(M_PI * timer.GetPassTime()/3);
		SetDrawBlendModeST(MODE_ALPHA, alpha * (1-slowTime) * (sin(M_PI * (double)(pos.x - pos.y + p_bg->GetCounter())/(WINDOW_WID/4))+1)/2);
		img[0]->DrawExtend(pos.ToDblXY(), sizeRate, ANC_MID);
	}
	//���˃��[�h.
	if (p_data->isReflectMode) {
		double alpha = 70 + 100 * sin(M_PI * timer.GetPassTime()/3);
		SetDrawBlendModeST(MODE_ALPHA, alpha * slowTime* (sin(M_PI * (double)(pos.x - pos.y + p_bg->GetCounter())/(WINDOW_WID/4))+1)/2);
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
				tile.Init();
 				tiles.push_back(tile); //�z��ɒǉ�.
			}
		}
	}

	tmShine.Start(); //�^�C�}�[�J�n.
}
//�X�V.
void BackGround::Update() {
	
	counter += p_data->speedRate;

	//�e�^�C���X�V.
	for (auto& i : tiles) {
		i.Update();
	}
}
//�`��.
void BackGround::Draw() {

	//�X���[���[�h�o�ߎ���.
	float pass = GameManager::GetPtr()->GetSlowModeTime();
	//�ŏ���0.5�b
	double time = 0.5-(pass -(REFLECT_MODE_TIME-0.5));
	time = CalcNumEaseOut(time); //�l�̋Ȑ��ϓ�.

	//���Ԋu����.
	if (tmShine.IntervalTime()) {
		int idx = RandNum(0, (int)tiles.size()-1);
		tiles[idx].Shine(); //�����_���Ń^�C���𔭌�������.
	}
	//�e�^�C���`��.
	for (auto& i : tiles) {
		i.Draw(time);
	}

	//�X���[���[�h��.
	if (p_data->speedRate) {
		//�g��.
		Box box = { {WINDOW_WID/2, WINDOW_HEI/2}, {WINDOW_WID * time, WINDOW_HEI * time}, COLOR_PLY_REFLECT };
		DrawBoxST(&box, ANC_MID, false, true);
	}
}