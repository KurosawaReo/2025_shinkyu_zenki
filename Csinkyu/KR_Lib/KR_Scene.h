/*
   - KR_Scene.h - (DxLib)
   ver: 2025/09/23

   シーン管理機能を追加します。(※ガチで設計する時用のため少し面倒)
*/
#pragma once

//実体取得マクロ.
#define SceneMngInst KR_Lib::SceneMng::GetInst()

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
	public:
		//実体取得用.
		static SceneMng& GetInst() {
			static SceneMng inst; //自身のインスタンス.
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