/*
   - KR_ObjectMng.h - (DxLib)
   ver: 2025/12/30
*/
#pragma once
//KR_Globalが入ってなければここで導入.
#if !defined DEF_KR_DX_GLOBAL
  #include "KR_Global.h"
#endif

//KrLib名前空間.
namespace KR
{
	//管理対象クラス[多重継承想定]
	class ObjectMngTarget
	{
	//▼ ===== 関数 ===== ▼.
	protected:
		//constructor.
		ObjectMngTarget() {}

	public:
		virtual void Init()          = 0; //初期化.
		virtual void Update()        = 0; //更新.
		virtual void Draw()          = 0; //描画.
		virtual bool IsErase() const = 0; //消滅条件.
	};
	
	//管理クラス.
	//ObjectMngTargetを継承したクラスのみ指定可.
	template<typename T> requires std::derived_from<T, ObjectMngTarget>
	class ObjectMng
	{
	//▼ ===== 変数 ===== ▼.
	private:
		list<T> objects; //object配列.

	//▼ ===== 関数 ===== ▼.
	private:
		//object削除.
		void Erase() {
			//list全ループ.
			for (auto i = objects.begin(); i != objects.end(); ) {
				//消滅するなら.
				if (i->IsErase()) {
					i = objects.erase(i); //消去.
				}
				else {
					i++;
				}
			}
		}

	protected:
		//constructor.
		ObjectMng() {}

		//object追加.
		void Push(T obj) {
			obj.Init(); //初期化処理.
			objects.push_back(obj);
		}
		//object生成処理.
		virtual void Spawn() = 0;

	public:
		//get.
		int GetObjectCnt() const { return objects.size(); }
		
		//管理クラス更新.
		void UpdateMng() {
			//生成処理.
			Spawn();
			//activeなobjectのみ.
			for (T& i : objects) if (i.isActive) { i.Update(); }
			//消滅処理.
			Erase();
		}
		//管理クラス描画.
		void DrawMng() {
			//activeなobjectのみ.
			for (T& i : objects) if (i.isActive) { i.Draw(); }
		}
	};
}