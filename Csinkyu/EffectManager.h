/*
   - EffectManager.h -
   �G�t�F�N�g���Ǘ�����N���X.
*/
#pragma once

//�G�t�F�N�g�^�C�v.
enum EffectType
{
	Effect_Score100,
	Effect_Score500,
};

//�G�t�F�N�g�f�[�^.
struct EFFECT
{
	EffectType type;

	DBL_XY     pos;     //���W.
	float      counter; //���Ԍv���p.
	BOOL       active;
};

//�G�t�F�N�g�Ǘ��N���X.
class EffectManager
{
private:
	EFFECT effect[EFFECT_MAX]{};

	GameData* p_data{};

public:
	void Init(GameData*);
	void Reset();
	void Update();
	void Draw();

	void SpawnEffect(EffectType type, DBL_XY pos); //�G�t�F�N�g�o��.
	void DeleteEffect(int idx);                    //�G�t�F�N�g����.
};
