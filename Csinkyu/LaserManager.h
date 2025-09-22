/*
   - LaserManager.h -
   ���XObstacle4main�Ƃ��Ă܂Ƃ߂��Ă����[�U�[.
*/
#pragma once

//�O���錾.
class GameData;
class Player;
class MeteorManager;
class EffectManager;

//���[�U�[�^�C�v.
enum LaserType
{
	Laser_Normal,       //�ʏ탌�[�U�[.
	Laser_Straight,     //�������[�U�[.
	Laser_Reflect,      //���˃��[�U�[.
	Laser_SuperReflect, //���˃��[�U�[������.
	Laser_Falling,      //�������[�U�[(�ԉΗp)
};

//���[�U�[�{�̃f�[�^.
struct LaserData
{
	LaserType type;      //���[�U�[�^�C�v.

	double    x,  y;     //���݂̍��W.
	double    bx, by;    //�O��`�悵�����ɂ������W.
	double    vx, vy;    //�i�s�����x�N�g��.

	DBL_XY    goalPos;   //�ڕW�n�_�̍��W.
	bool      isGoGoal;  //�ڕW�n�_�Ɍ������Đi�ނ�.

	int       LogNum;    //�L�^�����O�Ղ̐�.
	float     Counter;   //�ǔ������߂Ă���ʉ߂�������.

	int       ValidFlag; //���̃f�[�^���g�p�����t���O.
};

//���[�U�[���`���O�����C���f�[�^.
struct LaserLineData
{
	LaserType type;         //���[�U�[�^�C�v.

	double x1, y1, x2, y2;  //�`�����C���̍��W.
	float  Counter;         //�`�����C���̐F����p�l.

	int    ValidFlag;       //���̃f�[�^���g�p�����t���O
};

//���[�U�[�Ǘ��p.
class LaserManager final
{
public: //����.
	static LaserManager* GetPtr() {
		static LaserManager inst; //���g�̃C���X�^���X.
		return &inst;
	}

private:
	LaserData     laser[LASER_CNT_MAX]{};      //�z�[�~���O���[�U�[�̃f�[�^.
	LaserLineData line [LASER_LINE_CNT_MAX]{}; //���C���`��p�f�[�^.

	DBL_XY plyPos{}; //�v���C���[���W�ۊǗp.

	GameData*      p_data{};
	Player*        p_player{};
	MeteorManager* p_meteorMng{};
	EffectManager* p_effectMng{};

public:
	void Init();
	void Reset();
	void Update();
	void Draw();

	void UpdateLaser();                                             //�e���[�U�[�̍X�V.
	void UpdateLaserLine();                                         //�e���[�U�[�`����̍X�V.
	
	bool SpawnLaser       (DBL_XY pos, DBL_XY vel, LaserType type); //����.
	void DeleteLaser      (int idx);                                //����.
	void ReflectLaser     (int idx);               	                //����.

	bool IsExistEnemyLaser(DBL_XY pos, float len);                  //�G�̃��[�U�[��1�ł����݂��邩�ǂ���.

	void LaserRefTracking (int idx);                                //���[�U�[(reflected)��覐Βǔ�.
	void LaserReflectRange(Circle* cir);						    //���[�U�[�̈ꊇ����.
};