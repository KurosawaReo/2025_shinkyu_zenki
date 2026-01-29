/*
   - KR_Scene.cpp - (DxLib)
   ver.2026/01/29
*/
#include "KR_Scene.h"

//KrLib名前空間.
namespace KR
{
// ▼*--=<[ SceneMng ]>=--*▼ //

	SceneMng SceneMng::inst; //実体生成.

	/*
	   InputMngやSoundMngは自動実行を止める必要はないが
	   SceneMngは自動実行を止めれるよう、専用の関数を用意.
	*/
	void SceneMng::SetExeState(MngExeState _state) {
		inst.SetExeState(_state);
	}

	//シーン追加.
	void SceneMng::AddScene(IScene* sceneClass, string saveName) {
		sceneClass->Init();                 //初期化.
		inst.scenes[saveName] = sceneClass; //クラスを登録.
	}
	//シーン変更.
	ResultInt SceneMng::SetScene(string saveName) {
		//登録されてたら.
		if (inst.scenes.count(saveName) > 0) {
			inst.sceneChanger.ChangeState(inst.scenes[saveName]); //シーン変更.
			return { 0, _T("SceneMng::SetScene"), _T("正常終了") };
		}
		return { -1, _T("SceneMng::SetScene"), _T("未登録のシーン") };
	}

	//基本処理(自動実行)
	void SceneMng::Reset() {
		//全シーンをリセット.
		for (auto& i : scenes) {
			i.second->Reset();
		}
	}
	void SceneMng::Update() {
		sceneChanger.GetCurrent()->Update(); //現シーンの更新.
	}
	void SceneMng::Draw() {
		sceneChanger.GetCurrent()->Draw();   //現シーンの描画.
	}
}