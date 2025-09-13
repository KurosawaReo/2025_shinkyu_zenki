/*
   - EffectManager.h -
   �G�t�F�N�g���Ǘ�����N���X.
*/
#pragma once

class GameData; //�O���錾.

//�G�t�F�N�g�^�C�v.
enum EffectType
{
	Effect_Score100,
	Effect_Score500,
	Effect_PlayerDeath,  //�v���C���[���S.
	Effect_ReflectLaser, //���[�U�[����.
	Effect_BreakMeteo,   //覐Δj��.
	Effect_Level1,		 //���x��1���o.
	Effect_Level2,		 //���x��2���o.
	Effect_Level3,		 //���x��3���o.
	Effect_Level4,		 //���x��4���o.
	Effect_Level5,		 //���x��5���o.
};
//�G�t�F�N�g�f�[�^.
struct EffectData
{
	EffectType type{};

	DBL_XY     pos{};     //���W.
	DBL_XY     vec{};     //����.
	float      speed{};   //����.
	float      ang{};     //�p�x.
	float      len{};     //����.
};
//�G�t�F�N�g.
struct Effect : public EffectData
{
	float      counter{}; //���Ԍv���p.
	bool       active{};
};

//�G�t�F�N�g�Ǘ��N���X.[�p���s��]
class EffectManager final
{
public: //����.
	static EffectManager* GetPtr() {
		static EffectManager inst; //���g�̃C���X�^���X.
		return &inst;
	}

private:
	Effect effect[EFFECT_MAX]{};

	DrawImg imgScore[2]{}; //�X�R�A�摜.

	GameData* p_data{};

public:
	void Init();
	void Reset();
	void Update();
	void Draw();

	void SpawnEffect(EffectData* data); //�G�t�F�N�g�o��.
	void DeleteEffect(int idx);         //�G�t�F�N�g����.
};
