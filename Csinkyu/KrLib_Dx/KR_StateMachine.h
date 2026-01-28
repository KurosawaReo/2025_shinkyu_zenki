/*
   - KR_StateMachine.h - (DxLib)
   ver.2026/01/28

   ステート遷移機能。
*/
#pragma once

//KrLib名前空間.
namespace KR
{
    //状態クラス[継承想定]
    class State
    {
    public:
        virtual void Enter()  = 0; //状態に入った瞬間.
        virtual void Exit()   = 0; //状態を抜けた瞬間.
        virtual void Update() = 0; //更新.
        virtual void Draw()   = 0; //描画.
    };

    //状態管理クラス.
    //シーン切り替え、stepの切り替えなど様々な用途に使える.
    class StateMachine
    {
    //▼ ===== 変数 ===== ▼.
    private:
        State* current = nullptr; //現在のstate.

    //▼ ===== 関数 ===== ▼.
    public:
        //get.
        State* GetCurrent() const { return current; }

        //初期化.
        void Init(State* initState) {
            current = initState;               //初期state.
            if (current) { current->Enter(); } //初期stateにEnter.
        }
        //state遷移.
        void ChangeState(State* newState) {
            if (current == newState) return;   //同じstateには遷移しない.
            if (current) { current->Exit(); }  //元のstateからExit.
            current = newState;                //stateを変更.
            if (current) { current->Enter(); } //新たなstateにEnter.
        }
        //現stateの更新.
        void Update() {
            if (current) { current->Update(); }
        }
        //現stateの描画.
        void Draw() {
            if (current) { current->Draw(); }
        }
    };
}
