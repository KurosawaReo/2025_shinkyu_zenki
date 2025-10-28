/*
   - KR_Scene.h - (DxLib)
   ver: 2025/10/02

   �V�[���Ǘ��@�\��ǉ����܂��B(���K�`�Ő݌v���鎞�p�̂��ߏ����ʓ|)
*/
#pragma once

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	//�V�[���N���X(��{)[�p���K�{]
	class SceneBasic
	{
	protected:
		//constructor.
		SceneBasic(){}
	public:
		//��{����.
		virtual void Update() = 0;
		virtual void Draw()   = 0;
	};

	//�V�[���Ǘ��N���X[�p���s��]
	class SceneMng final
	{
	//�����̊֌W.
	public:
		//���̎擾�p.
		static SceneMng& GetInst() {
			static SceneMng inst; //���g�̃C���X�^���X.
			return inst;
		}
		//�g�p�֎~.
		SceneMng(const SceneMng&) = delete;
		SceneMng& operator=(const SceneMng&) = delete;
	private: 
		//constructor(�V�K�쐬���ł��Ȃ�����)
		SceneMng(){}

	//���f�[�^.
	private:
		map<MY_STRING, SceneBasic*> sceneData; //�V�[�����X�g.
		MY_STRING                   nowScene;  //���݂̃V�[����.

	public:
		void AddScene(SceneBasic* sceneClass, MY_STRING name); //�V�[���̒ǉ�.
		int  SetScene(MY_STRING name);                         //�V�[���̕ύX.

		void UpdateScene();
		void DrawScene();
	};
}