/*
   - Obstacle.cpp -
   ��Q���Ǘ�.
*/
#include"Obstacle.h"
#include "myDraw.h"

#define MAX_M 100
#define PI 3.14159//�~����

int hsc;//�G�l�~�[�̏o��Ԋu.
int Mg; //�G�l�~�[�̉摜.
int Mx[MAX_M], My[MAX_M];//�~�T�C���̃O���t�B�b�N.
int Mv[MAX_M]; //�~�T�C���f�[�^�̎g�p���(1:�g�p��0:���g�p)
double Ma[MAX_M];//�~�T�C���̊p�x.


void Obstacle::Init()
{
	Mg = LoadGraph(_T("image/enemy.png"));
}
void Obstacle::Update()
{
	eneyMove();
}
void Obstacle::Draw()
{

}

void eneyMove()
{
	IMG img;
	LoadGraphST(&img, _T()))
}
