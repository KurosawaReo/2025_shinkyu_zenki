/*
   - myInputST.h - (original)
   ver.2025/06/02

   DxLib�Ŏg���p�̃I���W�i�����͊֐�.
*/
#pragma once

//����.
BOOL IsPushMouse    (int num);
BOOL IsPushMouseTime(int num);
BOOL IsPushKey      (int num);
int  IsPushKeyTime  (int num);

//�擾.
void GetMousePos    (DBL_XY* pos);

//�ړ��n.
void InputKey4Dir   (DBL_XY* pos, float speed);
void FixPosInArea   (DBL_XY* pos, INT_XY size, int left, int up, int right, int down);

//�X�V.
void UpdateKeys();
void UpdateMouse();