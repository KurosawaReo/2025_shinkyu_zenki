/*
   - KR_Global.h - (DxLib)
   ver: 2025/08/24

   KR_Lib�S�̂Ŏg���ėp�@�\��ǉ����܂�.
*/
#pragma once

//���̃w�b�_����`����Ă��邩���ʂ���p.
#define DEF_KR_GLOBAL

//C����p.
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
//C++�p.
#include <vector>
#include <map>
#include <string>
#include <cassert> //assert.h �����b�v��������.
#include <cmath>   //math.h   �����b�v��������.
#include <cstdlib> //stdlib.h �����b�v��������.
#include <ctime>   //time.h   �����b�v��������.
using namespace std;
//DxLib.
#include "DxLib.h"

//�^�ϊ��}�N��.
#define _int(n)   static_cast<int>   (n)        //int�^�ϊ��}�N��.
#define _int_r(n) static_cast<int>   (round(n)) //int�^�ϊ��}�N��(�l�̌ܓ�)
#define _flt(n)   static_cast<float> (n)        //float�^�ϊ��}�N��.
#define _dbl(n)   static_cast<double>(n)        //double�^�ϊ��}�N��.
//�֗��}�N��.
#define _if_check(n)              assert(n); if(n)                    //if���̑O�ɓ�������assert������.
#define _return(num, cond)        if (cond) { return num; }           //�����ɍ����Ȃ�return����.(cond = ����)
#define _is_in_range(num, n1, n2) (n1 <= num && num <= n2)            //�͈͓��ɐ��l�����邩�ǂ���.
#define _debug_log(var)           printfDx(_T("%s:%d\n"), #var, var); //�ϐ����ƒl��\������.

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
//�����R�[�h�Ő؂�ւ�.
#if defined UNICODE
	using MY_STRING = wstring; //wchar_t�^.
#else
	using MY_STRING = string;  //char�^.
#endif

	//x��y�̋Ïk.
	template<typename T> //�^��<>�œ��͂��Ďg��.
	struct XY
	{
		T x{}, y{};

		//constructor.
		XY(){}
		XY(T _x, T _y) : x(_x), y(_y) {}

		//INT_XY�^�ɕϊ�.
		XY<int> ToIntXY() const {
			return {_int_r(x), _int_r(y)};
		}
		//DBL_XY�^�ɕϊ�.
		XY<double> ToDblXY() const {
			return {_dbl(x), _dbl(y)};
		}

		//���Z�q�Ōv�Z�ł���悤��.
		XY<T> operator+(const XY<T>& xy) {  //+�̉E���������ɓ���A�Ԃ�l�������ɓ���.
			return { x + xy.x, y + xy.y };  //x��y�����Z���ĕԂ�.
		}
		XY<T> operator-(const XY<T>& xy) {
			return { x - xy.x, y - xy.y };
		}
		XY<T> operator*(const XY<T>& xy) {
			return { x * xy.x, y * xy.y };
		}
		XY<T> operator/(const XY<T>& xy) {
			return { x / xy.x, y / xy.y };
		}

		XY<T>& operator+=(const XY<T>& xy) {
			x += xy.x;
			y += xy.y;
			return *this; //���g�̎���.
		}
		XY<T> operator-=(const XY<T>& xy) {
			x -= xy.x;
			y -= xy.y;
			return *this;
		}
		XY<T> operator*=(const XY<T>& xy) {
			x *= xy.x;
			y *= xy.y;
			return *this;
		}
		XY<T> operator/=(const XY<T>& xy) {
			x /= xy.x;
			y /= xy.y;
			return *this;
		}
		XY<T> operator*=(int n) {
			x *= n;
			y *= n;
			return *this;
		}
		XY<T> operator*=(double n) {
			x *= n;
			y *= n;
			return *this;
		}
		XY<T> operator/=(int n) {
			x /= n;
			y /= n;
			return *this;
		}
		XY<T> operator/=(double n) {
			x /= n;
			y /= n;
			return *this;
		}
	};
	using INT_XY = XY<int>;    //int�^.
	using DBL_XY = XY<double>; //double�^.

	//�~�f�[�^.
	struct Circle
	{
		DBL_XY pos;   //���W.
		float  r;     //���a.
		UINT   color; //�F.
	};
	//�l�p�`�f�[�^.
	struct Box
	{
		DBL_XY pos;   //���W.
		DBL_XY size;  //�T�C�Y.
		UINT   color; //�F.
	};
	//�O�p�`�f�[�^.
	struct Triangle
	{
		DBL_XY pos[3]; //3�_�̍��W.
		UINT   color;  //�F.
	};
	//���f�[�^.
	struct Line
	{
		DBL_XY stPos; //�n�_���W.
		DBL_XY edPos; //�I�_���W.
		UINT   color; //�F.
	};
}