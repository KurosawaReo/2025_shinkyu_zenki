/*
   - KR_Global.h - (DxLib)
   ver: 2025/10.09

   KR_Lib�S�̂Ŏg���ėp�@�\��ǉ����܂��B
*/
#include "KR_Global.h"

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	//constructor.
	MY_COLOR::MY_COLOR(UINT _colorCode) {
		*this = _colorCode; //�u=�v���Z�q���ŕϊ�.
	}
	MY_COLOR::MY_COLOR(ColorID id) {
		*this = id;         //�u=�v���Z�q���ŕϊ�.
	}

	//get.
	COLOR_U8 MY_COLOR::GetColorU8()   const { return { color.b, color.g, color.r, color.a }; }
	UINT     MY_COLOR::GetColorCode() const { return DxLib::GetColor(color.r, color.g, color.b); }

	//����p.
	void MY_COLOR::operator=(const RGBA& rgba) {
		color = rgba; //���̂܂�.
	}
	void MY_COLOR::operator=(UINT colorCode) {
		//�J���[�R�[�h��RGB�ɕ���.
		color.r =  colorCode / 0x010000;
		color.g = (colorCode / 0x000100) % 0x100;
		color.b =  colorCode % 0x100;
		color.a = 255;
	}
	void MY_COLOR::operator=(ColorID id) {

		switch (id) {
			case ColorID::Red:     color = { 255,   0,   0, 255 }; break;
			case ColorID::Orange:  color = { 255, 128,   0, 255 }; break;
			case ColorID::Yellow:  color = { 255, 255,   0, 255 }; break;
			case ColorID::Lime:    color = { 128, 255,   0, 255 }; break;
			case ColorID::Green:   color = {   0, 255,   0, 255 }; break;
			case ColorID::Cyan:    color = {   0, 255, 255, 255 }; break;
			case ColorID::Blue:    color = {   0,   0, 255, 255 }; break;
			case ColorID::Purple:  color = { 128,   0, 255, 255 }; break;
			case ColorID::Pink:    color = { 255,   0, 255, 255 }; break;
			case ColorID::Magenta: color = { 255,   0, 128, 255 }; break;
			case ColorID::White:   color = { 255, 255, 255, 255 }; break;
			case ColorID::Gray:    color = { 128, 128, 128, 255 }; break;
			case ColorID::Black:   color = {   0,   0,   0, 255 }; break;

			default: assert(FALSE); return;
		}
	}
}