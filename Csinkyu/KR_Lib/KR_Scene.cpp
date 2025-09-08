/*
   - KR_Scene.cpp - (DxLib)
   ver: 2025/09/07

   シーン管理機能を追加します。
   ※ガチで設計をする時用。手軽にプログラムを組む時にはおすすめしません。
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.hに入ってなければここで導入.
  #include "KR_Calc.h"
  #include "KR_Input.h"
  #include "KR_Scene.h"
  #include "KR_Sound.h"
  using namespace KR_Lib;
#endif
#include "KR_Scene.h"

//KR_Libに使う用.
namespace KR_Lib
{
// ▼*---=[ SceneBasic ]=---*▼ //

	//constructor.
	SceneBasic::SceneBasic() {
		//実体取得.
		p_calc  = Calc::GetPtr();
		p_input = InputMng::GetPtr();
		p_scene = SceneMng::GetPtr();
		p_sound = SoundMng::GetPtr();
	}

// ▼*---=[ SceneMng ]=---*▼ //

	//シーンの追加.
	void SceneMng::AddScene(SceneBasic* sceneClass, MY_STRING name) {
		sceneData[name] = sceneClass; //クラスのポインタを登録.
	}
	//シーンの変更.
	int SceneMng::SetScene(MY_STRING name) {
		//登録していれば変更.
		if (sceneData.count(name) > 0) {
			nowScene = name;
			return 0; //正常終了.
		}
		return -1; //-1: シーン未登録.
	}
	//基本処理.
	void SceneMng::UpdateScene() {
		sceneData[nowScene]->Update();
	}
	void SceneMng::DrawScene() {
		sceneData[nowScene]->Draw();
	}
}