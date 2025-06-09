/*
   - myInputST.h - (original)
   ver.2025/06/09

   DxLib�Ŏg���p�̃I���W�i�����͊֐�.
*/
#pragma once

//����.
BOOL   IsPushKey       (int keyNum);
int    IsPushKeyTime   (int keyNum);
BOOL   IsPushMouse     (int mouseNum);
int    IsPushMouseTime (int mouseNum);
BOOL   IsPushPadBtn    (int btnNum);
int    IsPushPadBtnTime(int btnNum);

//�擾.
void   GetMousePos    (DBL_XY* pos, BOOL isValidX = TRUE, BOOL isValidY = TRUE);

//�ړ��n.
void   InputKey4Dir   (DBL_XY* pos, float speed);
void   InputPad4Dir   (DBL_XY* pos, float speed);
DBL_XY Move4Dir       (INT_XY  pow);

void   FixPosInArea   (DBL_XY* pos, INT_XY size, int left, int up, int right, int down);

//�X�V.
void   UpdateKeys();
void   UpdateMouse();
void   UpdatePadBtn();