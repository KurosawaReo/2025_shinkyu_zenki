/*
   - KR_ManagerBase.h - (DxLib)
   ver.2026/01/28

   管理クラスの根底。
*/
#pragma once

//KrLib名前空間.
namespace KR
{
	//管理クラスの実行状態.
	enum class ManagerState 
	{
		Active,		//Update & Draw
		UpdateOnly, //Updateのみ.
		DrawOnly,	//Drawのみ.
		Stop		//実行しない.
	};

	/*
	   管理クラスの元[継承想定]
	   
	   Init, Update, Drawは自動でAppクラスから呼び出される.
	   (order値が小さいほど先に実行)
	*/
	class ManagerBase
	{
	//▼ ===== 変数 ===== ▼.
	private:
		ManagerState state; //実行状態.
		int order;          //処理優先度.

	//▼ ===== 関数 ===== ▼.
	public:
		//コンストラクタ.
		ManagerBase(int _order);
		//set.
		void         SetState(ManagerState _state) { state = _state; }
		//get.
		int          GetOrder() const { return order; }
		ManagerState GetState() const { return state; }

		//実行判定.
		bool CanUpdate() const {
			return state == ManagerState::Active || state == ManagerState::UpdateOnly;
		}
		bool CanDraw() const {
			return state == ManagerState::Active || state == ManagerState::DrawOnly;
		}

		virtual void Init()   = 0;
		virtual void Reset()  = 0;
		virtual void Update() = 0;
		virtual void Draw()   = 0;
	};
}