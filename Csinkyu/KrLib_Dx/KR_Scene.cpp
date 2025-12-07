/*
   - KR_Scene.cpp - (DxLib)
   ver: 2025/12/05
*/
#include "KR_Scene.h"

//KrLib名前空間.
namespace KR
{
// ▼*--=<[ SceneBasic ]>=--*▼ //

// ▼*--=<[ SceneMng ]>=--*▼ //

	SceneMng SceneMng::inst; //実体生成.

	//シーンの追加.
	void SceneMng::AddScene(SceneBasic* sceneClass, MY_STRING name) {
		inst.scenes[name] = sceneClass; //クラスのポインタを登録.
	}
	//シーンの変更.
	ResultInt SceneMng::SetScene(MY_STRING name) {
		//登録していれば変更.
		if (inst.scenes.count(name) > 0) {
			inst.nowScene = name;
			return {0, _T("SceneMng::SetScene"), _T("正常終了")};
		}
		return {-1, _T("SceneMng::SetScene"), _T("シーン未登録")};
	}
	//基本処理.
	void SceneMng::UpdateScene() {
		inst.scenes[inst.nowScene]->Update();
	}
	void SceneMng::DrawScene() {
		inst.scenes[inst.nowScene]->Draw();
	}
}