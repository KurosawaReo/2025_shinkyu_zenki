/*
   - Meteo.h -
   �~���Ă���覐�.
*/
#pragma once
#include "Player.h"

//覐΂̌`�f�[�^.
struct MeteoShape
{
	int   lineCnt{};					 //覐΂����p�`�ɂ��邩.
	float lineDis[METEO_LINE_CNT_MAX]{}; //覐΂̒��S����̒��_�̋���.
	Line  line   [METEO_LINE_CNT_MAX]{}; //覐΂��\�������. 
};

//覐�(�P��)
class Meteo
{
private:
	DBL_XY     pos{};	 //���S���W.
	float      ang{};	 //�p�x.
	DBL_XY     vel{};    //���x.
	BOOL       active{}; //�L�����ǂ���.

	MeteoShape shape{};  //覐΂̌`�f�[�^.

	GameData*  p_data;   //�Q�[���f�[�^.
	Player*    p_player; //�v���C���[�f�[�^.

public:
	//set.
	void SetActive(BOOL _active) { 
		active = _active; 
	}
	//get.
	DBL_XY GetPos()    { return pos; }
	BOOL   GetActive() { return active; }

	//���̑�.
	void Init(GameData*, Player*);
	void Reset();
	void Update();
	void Draw();

	void Spawn();				//覐Ώo��. 
	void Destroy();				//覐Δj��.
	BOOL IsHitMeteo(Circle*);	//覐΂̓����蔻��.

	void UpdateMeteoLine();		//覐΂��\��������̍X�V.
};