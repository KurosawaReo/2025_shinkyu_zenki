/*
   - myInputST.h - (original)
   ver.2025/05/15

   DxLibで使う用のオリジナル入力関数.
*/
#pragma once

BOOL IsPushMouse  (int num);
BOOL IsPushKey    (int num);
int  IsPushKeyTime(int num);

void InputMove4Dir(DBL_XY* pos, int speed);
void MoveLimPos   (DBL_XY* pos, INT_XY size, int lLim, int uLim, int rLim, int dLim);

void UpdateKeys();