/*
   - KR_StateMachine.h - (DxLib)
   ver.2026/01/29

   ステート遷移機能。
*/
#pragma once

//KrLib名前空間.
namespace KR
{
    /*
       状態クラス[継承想定]
       AIの行動、シーン、stepなど、様々な切り替えに使える.
    */
    class IState
    {
    public:
        virtual void Enter()  = 0; //状態に入った瞬間.
        virtual void Exit()   = 0; //状態を抜けた瞬間.
        virtual void Update() = 0; //更新.
        virtual void Draw()   = 0; //描画.
    };

    //状態管理クラス.
    class StateMachine
    {
    //▼ ===== 変数 ===== ▼.
    private:
        IState* current = nullptr; //現在のstate.

    //▼ ===== 関数 ===== ▼.
    public:
        //get.
        IState* GetCurrent() const { return current; }

        void InitState  (IState* state);    //初期化.
        void ChangeState(IState* newState); //state遷移.
        void Update();                      //更新.
        void Draw();                        //描画.
    };
}
