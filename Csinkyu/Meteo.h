/*
   - Meteo.h -
   �~���Ă���覐�.
*/
#pragma once
#include "Player.h"

//覐΂̏��.
enum MeteoState
{
	Meteo_Normal,
	Meteo_Destroy, //�j�󃂁[�h.
};

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
	MeteoState state{};		  //覐΂̏��.
	MeteoShape shape{};       //覐΂̌`�f�[�^.

	DBL_XY     pos{};	      //���S���W.
	float      ang{};	      //�p�x.
	DBL_XY     vel{};         //���x.
	bool       active{};      //�L�����ǂ���.

	float      destroyCntr{}; //�j��ʂ̓x��.

	GameData*  p_data;        //�Q�[���f�[�^.
	Calc*      p_calc;        //�v�Z�@�\.

public:
	//set.
	void SetActive(bool _active) { 
		active = _active; 
	}
	//get.
	DBL_XY     GetPos()    { return pos; }
	bool       GetActive() { return active; }
	MeteoState GetState()  { return state; }

	//���̑�.
	void Init(GameData*);
	void Reset();
	void Update();
	void Draw();

	void Spawn();				//覐Ώo��. 
	void Destroy();				//覐Δj��.
	bool IsHitMeteo(Circle*);	//覐΂̓����蔻��.

	void UpdateMeteoLine();		//覐΂��\��������̍X�V.
};