/*
   - KR_Scene.h - (DxLib)
   ver: 2025/11/18

   シーン管理機能を追加。
   ※ガチで設計をする時用。手軽にプログラムを組む時にはおすすめしない。
*/
#pragma once

//KR_Libに使う用.
namespace KR
{
	//シーンクラス(基本)[継承必須]
	class SceneBasic
	{
	protected:
		//constructor.
		SceneBasic(){}
	public:
		//基本処理.
		virtual void Update() = 0;
		virtual void Draw()   = 0;
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

	//▼データ.
	private:
		map<MY_STRING, SceneBasic*> sceneData; //シーンリスト.
		MY_STRING                   nowScene;  //現在のシーン名.

	public:
		void AddScene(SceneBasic* sceneClass, MY_STRING name); //シーンの追加.
		int  SetScene(MY_STRING name);                         //シーンの変更.

		void UpdateScene();
		void DrawScene();
	};
}