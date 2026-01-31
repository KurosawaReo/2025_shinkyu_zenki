/*
   - KR_ManagerBase.cpp - (DxLib)
   ver.2026/01/31
*/
#include "KR_ManagerBase.h"

//[include] cppでのみ使うもの.
#include "KR_App.h"

//KrLib名前空間.
namespace KR
{
// ▼*--=<[ ManagerInsts ]>=--*▼ //

	//管理クラスを追加.
	void ManagerInsts::Push(ManagerBase* _inst) {
		//まだ入ってなければ.
		if (find(mngInsts.begin(), mngInsts.end(), _inst) == mngInsts.end()) {
			mngInsts.push_back(_inst);
		}
	}

	//管理クラスを探す.
	ManagerBase* ManagerInsts::GetMngClass(const std::type_info& type) {
		//保存された管理クラスを全ループ.
		for (auto* m : mngInsts) {
			if (typeid(*m) == type) { //一致すれば返す.
				return m;
			}
		}
		return nullptr;
	}

// ▼*--=<[ ManagerBase ]>=--*▼ //

	//コンストラクタ.
	ManagerBase::ManagerBase(int _order) :
		order(_order), mode(MngAutoExe::Active)
	{
		//派生クラスのコンストラクタが実行された時, 自身を登録する.
		ManagerInsts::GetInst().Push(this);
	}
}