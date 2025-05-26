/*
   - myInputST.h - (original)
   ver.2025/05/21

   DxLibで使う用のオリジナル入力関数.
*/
#pragma once

//判定.
BOOL IsPushMouse    (int num);
BOOL IsPushMouseTime(int num);
BOOL IsPushKey      (int num);
int  IsPushKeyTime  (int num);

//取得.
void GetMousePos    (INT_XY* pos);

//テンプレ.
void InputKey4Dir   (DBL_XY* pos, int speed);
void LimMovePos     (DBL_XY* pos, INT_XY size, int lLim, int uLim, int rLim, int dLim);

//更新.
void UpdateKeys();
void UpdateMouse();