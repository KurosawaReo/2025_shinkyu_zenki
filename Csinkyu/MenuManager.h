/*
   - MenuManager.h -
   ���j���[�V�[��.
*/
#pragma once

//���j���[[�p���s��]
class MenuManager final
{
private:
	GameData* p_data{};     // GameData�̃|�C���^
	int selectedIndex = 0;  // �I�𒆂̃C���f�b�N�X
public:
	void Init();
	void Reset();
	void Update();
	void Draw();
};