/*
   - Meteo.h -
   �~���Ă���覐�.
*/
#pragma once

#define METEO_MAX_LINE (16) //�ő�16�p�`.

//覐�(�P��)
class Meteo
{
private:
	DBL_XY pos;					 //���S���W.
	DBL_XY vel;                  //���x.
	Line   line[METEO_MAX_LINE]; //覐΂��\�����鑽�p�`�̐�.
	BOOL   active;               //�L�����ǂ���.

	GameData* p_data;            //�Q�[���f�[�^.

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

	void Spawn(); //覐Ώo��. 
};