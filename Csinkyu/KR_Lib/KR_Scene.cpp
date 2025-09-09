/*
   - KR_Scene.cpp - (DxLib)
   ver: 2025/09/07

   �V�[���Ǘ��@�\��ǉ����܂��B
   ���K�`�Ő݌v�����鎞�p�B��y�Ƀv���O������g�ގ��ɂ͂������߂��܂���B
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.h�ɓ����ĂȂ���΂����œ���.
  #include "KR_Calc.h"
  #include "KR_Input.h"
  #include "KR_Scene.h"
  #include "KR_Sound.h"
  using namespace KR_Lib;
#endif
#include "KR_Scene.h"

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
// ��*---=[ SceneBasic ]=---*�� //

	//constructor.
	SceneBasic::SceneBasic() {
		//���̎擾.
		p_calc  = Calc::GetPtr();
		p_input = InputMng::GetPtr();
		p_scene = SceneMng::GetPtr();
		p_sound = SoundMng::GetPtr();
	}

// ��*---=[ SceneMng ]=---*�� //

	//�V�[���̒ǉ�.
	void SceneMng::AddScene(SceneBasic* sceneClass, MY_STRING name) {
		sceneData[name] = sceneClass; //�N���X�̃|�C���^��o�^.
	}
	//�V�[���̕ύX.
	int SceneMng::SetScene(MY_STRING name) {
		//�o�^���Ă���ΕύX.
		if (sceneData.count(name) > 0) {
			nowScene = name;
			return 0; //����I��.
		}
		return -1; //-1: �V�[�����o�^.
	}
	//��{����.
	void SceneMng::UpdateScene() {
		sceneData[nowScene]->Update();
	}
	void SceneMng::DrawScene() {
		sceneData[nowScene]->Draw();
	}
}