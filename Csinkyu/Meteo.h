/*
   - Meteo.h -
   �~���Ă���覐�.
*/
#pragma once

/*
//覐΂��\�������.
struct MeteoLine : public Line
{
	BOOL active; //�L�����ǂ���.
};
*/

//覐΂̌`�f�[�^.
struct ShapeData
{
	int  lineCnt{};						//覐΂����p�`�ɂ��邩.
	int  lineDis[METEO_LINE_CNT_MAX]{};	//覐΂̒��S����̒��_�̋���.
	Line line   [METEO_LINE_CNT_MAX]{};	//覐΂��\�����鑽�p�`�̐�. 
};

//覐�(�P��)
class Meteo
{
private:
	DBL_XY    pos{};	//���S���W.
	float     ang{};	//�p�x.
	DBL_XY    vel{};    //���x.
	BOOL      active{}; //�L�����ǂ���.

	ShapeData shape{};  //覐΂̌`�f�[�^.

	GameData* p_data;   //�Q�[���f�[�^.

public:
	//set.
	void SetActive(BOOL _active) { 
		active = _active; 
	}
	//get.
	DBL_XY GetPos()    { return pos; }
	BOOL   GetActive() { return active; }

	//���̑�.
	void Init(GameData*);
	void Reset();
	void Update();
	void Draw();

	void Spawn();           //覐Ώo��. 
	void UpdateMeteoLine(); //覐΂��\��������̍X�V.
};