/*
   - KR_Scene.h - (DxLib)
   ver: 2025/11/29

   シーン管理機能を追加。

   シーンごとにSceneBasicを継承してクラスを作る。
   (※しっかり設計を作る時用)
*/
#pragma once
//KR_Globalが入ってなければここで導入.
#if !defined DEF_KR_DXLIB_GLOBAL
  #include "KR_Global.h"
#endif

//実体取得用.
#define InstSceneMng KR::SceneMng::GetInst()

//KrLib名前空間.
namespace KR
{
	//シーンクラス(基本)[継承必須]
	class SceneBasic
	{
	public:
		//基本処理.
		virtual void Update()       = 0;
		virtual void Draw()   const = 0;
	};

	//シーン管理クラス[継承不可]
	class SceneMng final
	{
	//▼実体関係.
	private:
		static SceneMng inst; //実体を入れる用.
	public:	
		//実体を取得.
		static SceneMng& GetInst() {
			return inst;
		}
		//使用禁止.
		SceneMng(const SceneMng&) = delete;
		SceneMng& operator=(const SceneMng&) = delete;
	private: 
		//constructor(新規作成をできなくする)
		SceneMng(){}

	//▼変数.
	private:
		map<MY_STRING, SceneBasic*> scenes;   //シーンリスト.
		MY_STRING                   nowScene; //現在のシーン名.

	//▼関数.
	public:
		void UpdateScene();
		void DrawScene();

		void AddScene(SceneBasic* sceneClass, MY_STRING name); //シーンの追加.
		int  SetScene(MY_STRING name);                         //シーンの変更.
	};
}