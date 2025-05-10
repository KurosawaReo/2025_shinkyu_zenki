/*
   - myInputST.h - (original)

   DxLibで使う用のオリジナル入力関数.
*/
#pragma once

BOOL IsPushMouse  (int num);
BOOL IsPushKey    (int num);
int  IsPushKeyTime(int num);

void UpdateKeys();