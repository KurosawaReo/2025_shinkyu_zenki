/*
   - MenuManager.h -
   ���j���[�V�[��.
*/
#pragma once

//���j���[.[�p���s��]
class MenuManager final
{
public: //����.
	static MenuManager* GetPtr() {
		static MenuManager inst; //���g�̃C���X�^���X.
		return &inst;
	}

private:
	GameData* p_data{};    //GameData�̃|�C���^.
	SoundMng* p_sound{};   //�T�E���h�Ǘ�.

	DrawImg imgMenu [3]{}; //���j���[�p�摜.
	Font    fontMenu[2]{}; //���j���[�p�t�H���g.

	int   selectedIndex = 0;  // �I�𒆂̃C���f�b�N�X
	float counter = 0;        // �o�ߎ��ԃJ�E���^�[.

public:
	void Init();
	void Reset();
	void Update();
	void Draw();
};