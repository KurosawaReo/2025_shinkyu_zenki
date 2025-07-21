/*
   - myCalcST.h - (original)
   ver.2025/07/21

   DxLib: �I���W�i���v�Z�@�\�̒ǉ�.
*/
#pragma once

//�p�x�ϊ��p.
#define _rad(x) (x)*(M_PI/180)
#define _dig(x) (x)*(180/M_PI)

//�����蔻��.
BOOL   IsHitCircle	 (const Circle* cir1, const Circle* cir2);
BOOL   IsHitBox		 (const Box*    box1, const Box*    box2,  BOOL isCenter);
BOOL   IsHitLine	 (const Line*   line, const Circle* cir);

//�ړ����E.
void   FixPosInArea  (DBL_XY* pos, INT_XY size, int left, int up, int right, int down);
BOOL   IsOutInArea   (DBL_XY  pos, INT_XY size, int left, int up, int right, int down, BOOL isCompOut);

//�v�Z.
double CalcDis		 (INT_XY pos1,  INT_XY pos2);
double CalcDis		 (DBL_XY pos1,  DBL_XY pos2);
DBL_XY CalcMidPos	 (DBL_XY pos1,  DBL_XY pos2);
DBL_XY CalcArcPos	 (DBL_XY stPos, double ang, double len);
double CalcFacingAng (DBL_XY stPos, DBL_XY targetPos);
DBL_XY CalcDigToPos	 (double dig);
DBL_XY CalcRadToPos	 (double rad);

//�l�̋Ȑ��ϓ�(�A�j���[�V�����p)
float  CalcNumEaseIn   (float time);
float  CalcNumEaseOut  (float time);
float  CalcNumEaseInOut(float time);
float  CalcNumWaveLoop  (float time);

//�l�̑���.
int    RndNum		 (int st, int ed, BOOL isDxRnd = FALSE);
double GetDecimal	 (double num);