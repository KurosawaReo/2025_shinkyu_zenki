/*
   - KR_ManagerBase.cpp - (DxLib)
   ver.2026/01/29
*/
#include "KR_ManagerBase.h"

//[include] cppでのみ使うもの.
#include "KR_App.h"

//KrLib名前空間.
namespace KR
{
	//コンストラクタ.
	ManagerBase::ManagerBase(int _order) :
		order(_order), state(MngExeState::Active)
	{
		//派生クラスのコンストラクタが実行された時, 自身を登録する.
		mngInsts.push_back(this);
	}
}