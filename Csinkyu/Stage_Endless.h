/*
   - Stage_Endless.h -

   �X�e�[�W: �ϋv���[�h.
*/
#pragma once

//�O���錾.
class GameData;
class GameManager;
class LaserManager;
class MeteorManager;
class Ripples;
class ItemManager;
class FireworksManager;
class EffectManager;

//�ϋv���[�h.[�p���s��]
class EndlessStage final
{
//�����̊֌W.
public:
	//���̎擾�p.
	static EndlessStage& GetInst() {
		static EndlessStage inst; //���g�̃C���X�^���X.
		return inst;
	}
	//�g�p�֎~.
	EndlessStage(const EndlessStage&) = delete;
	EndlessStage& operator=(const EndlessStage&) = delete;
private:
	//constructor(�V�K�쐬���ł��Ȃ�����)
	EndlessStage(){}

//���f�[�^.
private:
	GameData*         p_data{};
	GameManager*      p_gameMng{};
	LaserManager*     p_laserMng{};
	MeteorManager*    p_meteorMng{};
	Ripples*          p_ripples{};
	ItemManager*      p_itemMng{};
	FireworksManager* p_fireworksMng{};
	EffectManager*    p_effectMng{};
	SoundMng*         p_sound{};

public:
	void Init();
	void Reset();
	void Update();
	void Draw();

	void UpdateObjects();
	void DrawObjects();
};