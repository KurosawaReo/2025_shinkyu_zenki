/*
   - Obst_NormalLaser.h -

   ��Q��: ���[�U�[���ˑ�(�p����)
   �̂ɂ���ĈႤ���������邽�߁Aoverride���g�p.
*/
#pragma once
#include "Obst_NormalLaserMain.h"

//#define MAX_L 100 //�~�T�C������ԍő勗��.
//#define PI 3.14159//�~����.
//#define LINE_MAXNUM 3000//�`�悷����̍ő吔.

//�p����N���X(�q1)
class NormalLaser_1 : public NormalLaserMain
{
public:
	void Move() override;
};

//�p����N���X(�q2)
class NormalLaser_2 : public NormalLaserMain
{
public:
	void Move() override;
};

//�p����N���X(�q3)
class NormalLaser_3 : public NormalLaserMain
{
public:
	void Move() override;
};

//�p����N���X(�q4)
class NormalLaser_4 : public NormalLaserMain
{
public:
	void Move() override;
};