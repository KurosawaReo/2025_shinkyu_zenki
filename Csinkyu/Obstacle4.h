/*
   - Obstacle4.h -

   ���[�U�[�̌p����N���X.
   �C��(�s��)�����E�ňႤ�����ɂ��邽�߁Aoverride���g�p.
*/
#pragma once
#include "Player.h"
#include "Obstacle4main.h"

//#define MAX_L 100 //�~�T�C������ԍő勗��.
//#define PI 3.14159//�~����.
//#define LINE_MAXNUM 3000//�`�悷����̍ő吔.

//�p����N���X(�q1)
class Obstacle4_1 : public Obstacle4main
{
public:
	void Init(GameData*, Player*);
	void Reset(float _Hx, float _Hy, float _Hm) override;
	void Move() override;
};

//�p����N���X(�q2)
class Obstacle4_2 : public Obstacle4main
{
public:
	void Init(GameData*, Player*);
	void Reset(float _Hx, float _Hy, float _Hm) override;
	void Move() override;
};