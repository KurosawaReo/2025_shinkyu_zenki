/*
   - Obst_NormalLaserMain.h -

   ��Q��: ���[�U�[���ˑ�(�p����)
*/
#pragma once

//�O���錾.
class Player;
class LaserManager;
class MeteorManager;

struct FlashEffect
{
	double x, y;    // �G�t�F�N�g�ʒu.
	float Counter;  // �o�ߎ���.
	float Duration; // �G�t�F�N�g�̎�������.
	int BaseSize;   // ��{�T�C�Y
	int ValidFlag;  // �L���t���O

	double angle;
};

//�p�����ƂȂ�N���X(�e)
class NormalLaserMain
{
protected:
	float   Hx{}, Hy{};  //�C��̈ʒu.
	float   Hm{};        //�C��̈ړ�����.
	float   Hsc{};       //�C��̃V���b�g�Ԋu�J�E���^.
	float   HscTm{};     //�C�䂪�V���b�g���鎞��.
	MoveDir moveDir{};   //���݂̈ړ�����.

	FlashEffect flashEffect[LASER_NOR_FLASH_MAX]{};	// �N���X�̃����o�ϐ��Ƃ��Ēǉ�

	GameData*      p_data{};
	Player*        p_player{};
	LaserManager*  p_laserMng{};
	MeteorManager* p_meteorMng{};

public:
	//��{����.
	void Init  ();
	void Reset (float _Hx, float _Hy, float _Hm, MoveDir);
	void Update();
	void Draw  ();
	//�X�V�n.
	void UpdateObstFlash();
	//�`��n.
	void DrawObstFlash();
	void DrawPreLaserDots();
	//�ړ��n.
	void enemy4Move();
	virtual void Move() = 0; //�C��ɂ���ē������Ⴄ��override�𗘗p���A"����"������ς���.

	//�o�钼�O�̓_��.
	void CreateFlashEffect(double x, double y);
};
