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
	Effect_PlayerDeath,		//�v���C���[���S.
	Effect_ReflectLaser,	//���[�U�[����.
	Effect_BreakMeteo,		//覐Δj��.

	Effect_Endless_Level1,	//�ϋv���[�h: Level1���o.
	Effect_Endless_Level2,	//�ϋv���[�h: Level2���o.
	Effect_Endless_Level3,	//�ϋv���[�h: Level3���o.
	Effect_Endless_Level4,	//�ϋv���[�h: Level4���o.
	Effect_Endless_Level5,	//�ϋv���[�h: Level5���o.
	Effect_Tutorial_Step1,	//�`���[�g���A��: step1���o.
	Effect_Tutorial_Step2,	//�`���[�g���A��: step2���o.
	Effect_Tutorial_Step3,	//�`���[�g���A��: step3���o.
	Effect_Tutorial_Step4,	//�`���[�g���A��: step4���o.
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
//�����̊֌W.
public:
	//���̎擾�p.
	static EffectManager& GetInst() {
		static EffectManager inst; //���g�̃C���X�^���X.
		return inst;
	}
	//�g�p�֎~.
	EffectManager(const EffectManager&) = delete;
	EffectManager& operator=(const EffectManager&) = delete;
private:
	//constructor(�V�K�쐬���ł��Ȃ�����)
	EffectManager(){}

//���f�[�^.
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
