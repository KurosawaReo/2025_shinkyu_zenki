/*
   - KR_ManagerBase.cpp - (DxLib)
   ver.2026/01/28
*/
#include "KR_ManagerBase.h"

//[include] cppでのみ使うもの.
#include "KR_App.h"

//KrLib名前空間.
namespace KR
{
	//コンストラクタ.
	ManagerBase::ManagerBase(int _order) :
		order(_order), state(ManagerState::Active)
	{
		App::AddManager(this); //自身を登録.
	}
}