/*
   - KR_ManagerBase.h - (DxLib)
   ver.2026/01/29

   管理クラスの根底。
*/
#pragma once

//KrLib名前空間.
namespace KR
{
	//KrLibの管理クラスのorder値.
	constexpr int ORDER_KR_INPUT_MNG = -1;
	constexpr int ORDER_KR_SOUND_MNG = -1;
	constexpr int ORDER_KR_SCENE_MNG = 0;

	//管理クラスの実行状態.
	enum class MngExeState
	{
		Active,		//Update & Draw
		UpdateOnly, //Updateのみ.
		DrawOnly,	//Drawのみ.
		Stop		//実行しない.
	};

	/*
	   管理クラスの根底[継承想定]
	   
	   Init, Update, Drawは自動でAppクラスから呼び出される.
	   (order値が小さいほど先に実行)
	*/
	class ManagerBase
	{
	//▼ ===== 変数 ===== ▼.
	private:
		MngExeState state; //実行状態.
		int order;         //処理優先度.

	public:
		inline static vector<ManagerBase*> mngInsts; //管理クラス配列(staticで保管)

	//▼ ===== 関数 ===== ▼.
	public:
		//コンストラクタ.
		ManagerBase(int _order);
		//set.
		void        SetExeState(MngExeState _state) { state = _state; }
		//get.
		int         GetOrder()    const { return order; }
		MngExeState GetExeState() const { return state; }

		//実行判定.
		bool CanUpdate() const {
			return state == MngExeState::Active || state == MngExeState::UpdateOnly;
		}
		bool CanDraw() const {
			return state == MngExeState::Active || state == MngExeState::DrawOnly;
		}

		//管理クラスを取得.
		template<class T>
		static T* GetMng() {
			//登録された管理クラスをループ.
			for (auto* m : mngInsts) {
				//castできるなら返す.
				if (auto* p = dynamic_cast<T*>(m)) { return p; }
			}
			return nullptr; //なければnull
		}
		//管理クラスを全て取得.
		static vector<ManagerBase*> GetAllMng() { return mngInsts; }

		virtual void Init()   = 0;
		virtual void Reset()  = 0;
		virtual void Update() = 0;
		virtual void Draw()   = 0;
	};
}