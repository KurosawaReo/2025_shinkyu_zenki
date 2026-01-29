/*
   - KR_StateMachine.cpp - (DxLib)
   ver.2026/01/29
*/
#pragma once
#include "KR_StateMachine.h"

//TODO: SceneManager‚ðì‚Á‚ÄA‚»‚Ì’†‚ÉStateMachine‚ð“ü‚ê‚½‚¢(Unity‚Ý‚½‚¢‚Éstatic‚Å‚â‚è‚½‚¢)

//KrLib–¼‘O‹óŠÔ.
namespace KR
{
    //‰Šú‰».
    void StateMachine::InitState(IState* state) {
        current = state;                    //‰Šústate.
        if (current) { current->Enter(); }  //‰Šústate‚ÉEnter.
    }
    //state‘JˆÚ.
    void StateMachine::ChangeState(IState* newState) {
        if (current == newState) return;    //“¯‚¶state‚É‚Í‘JˆÚ‚µ‚È‚¢.
        if (current) { current->Exit(); }   //Œ³‚Ìstate‚©‚çExit.
        current = newState;                 //state‚ð•ÏX.
        if (current) { current->Enter(); }  //V‚½‚Èstate‚ÉEnter.
    }
    //XV.
    void StateMachine::Update() {
        if (current) { current->Update(); } //Œ»state‚ÌXV.
    }
    //•`‰æ.
    void StateMachine::Draw() {
        if (current) { current->Draw(); }   //Œ»state‚Ì•`‰æ.
    }
}