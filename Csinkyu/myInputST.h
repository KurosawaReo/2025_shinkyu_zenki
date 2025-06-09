/*
   - myInputST.h - (original)
   ver.2025/06/09

   DxLibで使う用のオリジナル入力関数.
*/
#pragma once

//判定.
BOOL   IsPushKey       (int keyNum);
int    IsPushKeyTime   (int keyNum);
BOOL   IsPushMouse     (int mouseNum);
int    IsPushMouseTime (int mouseNum);
BOOL   IsPushPadBtn    (int btnNum);
int    IsPushPadBtnTime(int btnNum);

//取得.
void   GetMousePos    (DBL_XY* pos, BOOL isValidX = TRUE, BOOL isValidY = TRUE);

//移動系.
void   InputKey4Dir   (DBL_XY* pos, float speed);
void   InputPad4Dir   (DBL_XY* pos, float speed);
DBL_XY Move4Dir       (INT_XY  pow);

void   FixPosInArea   (DBL_XY* pos, INT_XY size, int left, int up, int right, int down);

//更新.
void   UpdateKeys();
void   UpdateMouse();
void   UpdatePadBtn();