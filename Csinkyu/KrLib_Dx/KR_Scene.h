/*
   - KR_Scene.h - (DxLib)
   ver.2026/01/28

   シーン管理機能。(試作品)
   シーンごとにSceneBasicを継承してクラスを作る。
*/
#pragma once
//[include] KR_Global.
#if !defined DEF_KR_DX_GLOBAL
  #include "KR_Global.h"
#endif

//KrLib名前空間.
namespace KR
{
	//シーンクラス(基本)[継承想定]
	class SceneBasic
	{
	public:
		//基本処理.
		virtual void Update()       = 0;
		virtual void Draw()   const = 0;
	};

	//シーン管理クラス[staticクラス]
	class SceneMng final
	{
	//▼ ===== 実体 ===== ▼.
	private:
		static SceneMng inst; //実体を入れる用.

	//▼ ===== 変数 ===== ▼.
	private:
		umap<MY_STRING, SceneBasic*> scenes;   //シーンリスト.
		MY_STRING                    nowScene; //現在のシーン名.

	//▼ ===== 関数 ===== ▼.
	private:
		//コンストラクタ(新規作成をできなくする)
		SceneMng() {}

	public:
		static void		 UpdateScene();
		static void		 DrawScene();

		static void      AddScene(SceneBasic* sceneClass, MY_STRING name); //シーンの追加.
		static ResultInt SetScene(MY_STRING name);                         //シーンの変更.

		//使用禁止.
		SceneMng(const SceneMng&) = delete;
		SceneMng& operator=(const SceneMng&) = delete;
	};
}