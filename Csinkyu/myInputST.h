/*
   - myInputST.h - (original)
   ver.2025/05/21

   DxLib�Ŏg���p�̃I���W�i�����͊֐�.
*/
#pragma once

//����.
BOOL IsPushMouse    (int num);
BOOL IsPushMouseTime(int num);
BOOL IsPushKey      (int num);
int  IsPushKeyTime  (int num);

//�擾.
void GetMousePos    (INT_XY* pos);

//�e���v��.
void InputKey4Dir   (DBL_XY* pos, int speed);
void LimMovePos     (DBL_XY* pos, INT_XY size, int lLim, int uLim, int rLim, int dLim);

//�X�V.
void UpdateKeys();
void UpdateMouse();