/*
   - Obstacle2.h -
   ��Q���Ǘ�.(���c����)
*/
#pragma once

#define MAX_M 100 //�~�T�C������ԍő勗��.
//#define PI 3.14159//�~����

class Obstacle2
{
private:
	int    hsc;                    //�G�l�~�[�̏o��Ԋu.
	int    Mg;                     //�G�l�~�[�̉摜.
	double Mx[MAX_M], My[MAX_M];   //�~�T�C���̃O���t�B�b�N.
	double Mv[MAX_M];              //�~�T�C���f�[�^�̎g�p���(1:�g�p��,0:���g�p)
	double Ma[MAX_M];              //�~�T�C���̊p�x.
	int    Mc[MAX_M];              //�~�T�C���̒ǔ��J�E���^

	IMG img;
	Player* player;

public:
	void Init(Player*);
	void Update();
	void Draw();
	void enemyMove();
};