/*
   - KR_ObjectMng.h - (DxLib)
   ver: 2025/11/29
*/
#pragma once
//KR_Globalが入ってなければここで導入.
#if !defined DEF_KR_DXLIB_GLOBAL
  #include "KR_Global.h"
#endif
#include "KR_Object.h"

//KrLib名前空間.
namespace KR
{
	//オブジェクト(管理クラス)
	//requiresで、ObjectShapeを継承したクラスのみ指定可能にしている.
	template<typename T> requires std::derived_from<T, ObjectShape>
	class ObjectMng
	{
	//▼変数.
	private:
		list<T> objects;

	//▼関数.
	protected:
		//constructor.
		ObjectMng() {}

	private:
		//オブジェクト削除.
		void Remove() {
			//list全ループ.
			for (auto i = objects.begin(); i != objects.end(); ) {
				//消滅するなら.
				if (IsErase(*i)) {
					i = objects.erase(i); //消去.
				}
				else {
					i++;
				}
			}
		}

	public:
		//get.
		int GetObjectCnt() const { return objects.size(); }

		//更新.
		void UpdateLoop() {
			//activeなobjectのみ実行.
			for (T& i : objects) if (i.isActive) { Update(i); }
			//消滅処理.
			Remove();
		}
		virtual void Update(T& object) {}

		//描画.
		void DrawLoop() {
			//activeなobjectのみ実行.
			for (const T& i : objects) if (i.isActive) { Draw(i); }
		}
		virtual void Draw(const T& object) const {}

		//オブジェクト追加.
		void Add(const T& object) {
			objects.push_back(object);
		}

		//消滅判定(必須)
		virtual bool IsErase(const T& object) const = 0;
	};
}