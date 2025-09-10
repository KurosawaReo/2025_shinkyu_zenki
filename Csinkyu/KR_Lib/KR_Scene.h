/*
   - KR_Scene.h - (DxLib)
   ver: 2025/09/10

   �V�[���Ǘ��@�\��ǉ����܂��B(���K�`�Ő݌v���鎞�p�̂��ߏ����ʓ|)
*/
#pragma once

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	//�O���錾.
	class InputMng;
	class SceneMng;
	class SoundMng;

	//�V�[���N���X(��{)[�p���K�{]
	class SceneBasic
	{
	protected:
		InputMng* p_input;
		SceneMng* p_scene;
		SoundMng* p_sound;

		//constructor.
		SceneBasic();
	public:
		//��{����.
		virtual void Update() = 0;
		virtual void Draw()   = 0;
	};

	//�V�[���Ǘ��N���X[�p���s��]
	class SceneMng final
	{
	private: //�f�[�^.
		map<MY_STRING, SceneBasic*> sceneData; //�V�[�����X�g.
		MY_STRING                   nowScene;  //���݂̃V�[����.

	public:
		//���̂̎擾.
		static SceneMng* GetPtr() {
			static SceneMng inst; //���g�̃C���X�^���X.
			return &inst;
		}
		
		void AddScene(SceneBasic* sceneClass, MY_STRING name); //�V�[���̒ǉ�.
		int  SetScene(MY_STRING name);                         //�V�[���̕ύX.

		void UpdateScene();
		void DrawScene();
	};
}