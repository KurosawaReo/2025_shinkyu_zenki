/*
   - KR_Scene.h - (DxLib)
   ver: 2025/09/10

   シーン管理機能を追加します。(※ガチで設計する時用のため少し面倒)
*/
#pragma once

//KR_Libに使う用.
namespace KR_Lib
{
	//前方宣言.
	class InputMng;
	class SceneMng;
	class SoundMng;

	//シーンクラス(基本)[継承必須]
	class SceneBasic
	{
	protected:
		InputMng* p_input;
		SceneMng* p_scene;
		SoundMng* p_sound;

		//constructor.
		SceneBasic();
	public:
		//基本処理.
		virtual void Update() = 0;
		virtual void Draw()   = 0;
	};

	//シーン管理クラス[継承不可]
	class SceneMng final
	{
	private: //データ.
		map<MY_STRING, SceneBasic*> sceneData; //シーンリスト.
		MY_STRING                   nowScene;  //現在のシーン名.

	public:
		//実体の取得.
		static SceneMng* GetPtr() {
			static SceneMng inst; //自身のインスタンス.
			return &inst;
		}
		
		void AddScene(SceneBasic* sceneClass, MY_STRING name); //シーンの追加.
		int  SetScene(MY_STRING name);                         //シーンの変更.

		void UpdateScene();
		void DrawScene();
	};
}