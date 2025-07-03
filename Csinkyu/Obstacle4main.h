/*
   - Obstacle4main.h -

   ���[�U�[�̌p�����N���X.
*/
#pragma once
#include "LaserManager.h" //���[�U�[�Ǘ��̃w�b�_�[�t�@�C��.

typedef struct tagFLASHEFFECT
{
	double x, y;    // �G�t�F�N�g�ʒu.
	float Counter;  // �o�ߎ���.
	float Duration; // �G�t�F�N�g�̎�������.
	int BaseSize;   // ��{�T�C�Y
	int ValidFlag; // �L���t���O

	double angle;
}FLASHEFFECT;

//�p�����ƂȂ�N���X(�e)
class Obstacle4main
{
protected:
	float Hx{}, Hy{};  //�C��̈ʒu.
	float Hm{};        //�C��̈ړ�����.
	float Hsc{};       //�C��̃V���b�g�Ԋu�J�E���^.
	float HscTm{};     //�C�䂪�V���b�g���鎞��.
	MoveDir moveDir{}; // ���݂̈ړ�����.

//	IMG         img{};
	DBL_XY      pPos{};// �v���C���[�̌��݈ʒu���擾
	FLASHEFFECT flashEffect[OBSTACLE4_FLASH_MAX]{};	// �N���X�̃����o�ϐ��Ƃ��Ēǉ�

	GameData*     p_data{};
	Player*       p_player{};
	MeteoManager* p_meteoMng{};
	LaserManager* p_laserMng{};

public:
	//��{����.
	        void Init  (GameData*, Player*, MeteoManager*, LaserManager*);
			void Reset (float _Hx, float _Hy, float _Hm, MoveDir);
	        void Update();
	        void Draw  ();
	//�`��n.
			void DrawObstFlash();
	//�ړ��n.
	        void enemy4Move();
	virtual void Move() = 0;

	//�o�钼�O�̓_��.
	void CreateFlashEffect(double x, double y);
};
