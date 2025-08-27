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
#define _if_check(n)              assert(n); if(n)                     //if���̑O�ɓ�������assert������.
#define _return(num, cond)        if (cond) { return num; }            //�����ɍ����Ȃ�return����.(cond = ����)
#define _is_in_range(num, n1, n2) ((n1 <= num) && (num <= n2))         //�͈͓��ɐ��l�����邩�ǂ���.
#define _debug_log(var)           printfDx(_T("%s: %d\n"), #var, var); //�ϐ����ƒl��\������.
//����}�N��(��{KR_Lib�Ŏg���p)
#define _type_num_only(T)		  typename = typename enable_if<is_arithmetic<T>::value>::type //int, float, double, char�^�̂�OK�Ƃ���.

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

		//���Z�q[+,-,*,/] [XY<T>�EXY<T>]
		XY<T> operator+(const XY<T>& value) {    //+�̉E���������ɓ���A�Ԃ�l�������ɓ���.
			return { x + value.x, y + value.y }; //x��y�����Z���ĕԂ�.
		}
		XY<T> operator-(const XY<T>& value) {
			return { x - value.x, y - value.y };
		}
		XY<T> operator*(const XY<T>& value) {
			return { x * value.x, y * value.y };
		}
		XY<T> operator/(const XY<T>& value) {
			return { x / value.x, y / value.y };
		}
		//���Z�q[+=,-=,*=,/=] [XY<T>�EXY<T>]
		XY<T>& operator+=(const XY<T>& xy) {
			x += xy.x;
			y += xy.y;
			return *this; //���g�̎���.
		}
		XY<T>& operator-=(const XY<T>& xy) {
			x -= xy.x;
			y -= xy.y;
			return *this;
		}
		XY<T>& operator*=(const XY<T>& xy) {
			x *= xy.x;
			y *= xy.y;
			return *this;
		}
		XY<T>& operator/=(const XY<T>& xy) {
			x /= xy.x;
			y /= xy.y;
			return *this;
		}

		//���Z�q [+,-,*,/] [XY<T>�E���l]
		//�E�������l�łȂ���Ζ����ɂ���.
		template<typename T2, _type_num_only(T2)>
		XY<T> operator+(T2 num) {
			return { x + static_cast<T>(num), y + static_cast<T>(num) }; //cast���x��y�����Z���ĕԂ�.
		}
		template<typename T2, _type_num_only(T2)>
		XY<T> operator-(T2 num) {
			return { x - static_cast<T>(num), y - static_cast<T>(num) };
		}
		template<typename T2, _type_num_only(T2)>
		XY<T> operator*(T2 num) {
			return { x * static_cast<T>(num), y * static_cast<T>(num) };
		}
		template<typename T2, _type_num_only(T2)>
		XY<T> operator/(T2 num) {
			return { x / static_cast<T>(num), y / static_cast<T>(num) };
		}
		//���Z�q[+=,-=,*=,/=] [XY<T>�E���l]
		//�E�������l�łȂ���Ζ����ɂ���.
		template<typename T2, _type_num_only(T2)>
		XY<T>& operator+=(T2 num) {
			x += num;
			y += num;
			return *this; //���g�̎���.
		}
		template<typename T2, _type_num_only(T2)>
		XY<T>& operator-=(T2 num) {
			x -= num;
			y -= num;
			return *this;
		}
		template<typename T2, _type_num_only(T2)>
		XY<T>& operator*=(T2 num) {
			x *= num;
			y *= num;
			return *this;
		}
		template<typename T2, _type_num_only(T2)>
		XY<T>& operator/=(T2 num) {
			x /= num;
			y /= num;
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