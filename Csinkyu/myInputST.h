/*
   - myInputST.h - (original)
   ver.2025/06/02

   DxLibで使う用のオリジナル入力関数.
*/
#pragma once

//判定.
BOOL IsPushMouse    (int num);
BOOL IsPushMouseTime(int num);
BOOL IsPushKey      (int num);
int  IsPushKeyTime  (int num);

//取得.
void GetMousePos    (DBL_XY* pos);

//移動系.
void InputKey4Dir   (DBL_XY* pos, float speed);
void FixPosInArea   (DBL_XY* pos, INT_XY size, int left, int up, int right, int down);

//更新.
void UpdateKeys();
void UpdateMouse();