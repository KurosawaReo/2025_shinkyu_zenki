/*
   - KR_ManagerBase.h - (DxLib)
   ver.2026/01/30

   管理クラスの根底。

   [注意]
   App::InitDx()内でInit()が自動で呼ばれるため
   main関数が動く前に、ManagerBaseを継承した全クラスの実体を生成する必要がある。
   シングルトンにするのがおすすめ。
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

	//前方宣言.
	class ManagerBase;

	//実体管理クラス.
	class ManagerInsts
	{
	//▼ ===== 実体 ===== ▼.
	public:
		static ManagerInsts& GetInst() {
			static ManagerInsts inst; //初呼び出し時に生成する.
			return inst;
		}

	//▼ ===== 変数 ===== ▼.
	private:
		vector<ManagerBase*> mngInsts; //インスタンス配列.

	//▼ ===== 関数 ===== ▼.
	private:
		//コンストラクタ.
		ManagerInsts(){}
		//管理クラスを探す.
		ManagerBase* GetByType(const std::type_info& type);

	public:
		//管理クラスを追加.
		void Push(ManagerBase* _inst);
		//管理クラスを取得.
		template<class T>
		T* Get() {
			return static_cast<T*>(GetByType(typeid(T)));
		}
		//管理クラスを全て取得.
		vector<ManagerBase*>& GetAll() { return mngInsts; }

		//使用禁止.
		ManagerInsts(const ManagerInsts&) = delete;
		ManagerInsts& operator=(const ManagerInsts&) = delete;
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

	//▼ ===== 関数 ===== ▼.
	public:
		//コンストラクタ.
		ManagerBase(int _order);
		//デストラクタ(これがあると安全?)
		virtual ~ManagerBase() = default;

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

		virtual void Init()   = 0;
		virtual void Reset()  = 0;
		virtual void Update() = 0;
		virtual void Draw()   = 0;
	};
}