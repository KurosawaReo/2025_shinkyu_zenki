/*
   - KR_Scene.h - (DxLib)
   ver: 2025/12/08

   シーン管理機能を追加。

   シーンごとにSceneBasicを継承してクラスを作る。
   (※しっかり設計を作る時用)
*/
#pragma once
//KR_Globalが入ってなければここで導入.
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
		map<MY_STRING, SceneBasic*> scenes;   //シーンリスト.
		MY_STRING                   nowScene; //現在のシーン名.

	//▼ ===== 関数 ===== ▼.
	private:
		//constructor(新規作成をできなくする)
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