/*
   - Obstacle4.h -

   ���[�U�[�̌p����N���X.
   �C��(�s��)�����E�ňႤ�����ɂ��邽�߁Aoverride���g�p.
*/
#pragma once
#include "Obstacle4main.h"

//#define MAX_L 100 //�~�T�C������ԍő勗��.
//#define PI 3.14159//�~����.
//#define LINE_MAXNUM 3000//�`�悷����̍ő吔.

//�p����N���X(�q1)
class Obstacle4_1 : public Obstacle4main
{
public:
	void Move() override;
};

//�p����N���X(�q2)
class Obstacle4_2 : public Obstacle4main
{
public:
	void Move() override;
};

//�p����N���X(�q3)
class Obstacle4_3 : public Obstacle4main
{
public:
	void Move() override;
};

//�p����N���X(�q4)
class Obstacle4_4 : public Obstacle4main
{
public:
	void Move() override;
};