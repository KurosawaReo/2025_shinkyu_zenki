/*
   - KR_Memory.cpp - (C++)
   ver.2025/11/18
*/
#if !defined DEF_KR_CPP_GLOBAL
  #include "KR_Global.h" //stdafx.hに入ってなければここで導入.
#endif
#include "KR_Memory.h"

//KR_Libに使う用.
namespace KR
{
// ▼*--=<[ MemoryLeak ]>=--*▼ //

    MemoryLeak MemoryLeak::inst; //実体生成.

// ▼*--=<[ TypePtr ]>=--*▼ //

    //メモリ確保.
    template<typename T>
    bool TypePtr<T>::New() {
        //未確保なら.
        if (!pointer) {
            //確保を試みる.
            try {
                pointer = new T();
                return true;  //確保成功.
            }
            //tryの処理中、例外(bad_alloc)を受け取ったら.
            catch (const std::bad_alloc&) {
                return false; //確保失敗.
            }
        }
    }
    //メモリ解放.
    template<typename T>
    void TypePtr<T>::Delete() {
        //確保済みなら.
        if (pointer) {
            delete pointer; pointer = nullptr; //解放してnullに.
        }
    }
}