/*
   - KR_File.cpp - (C++)
   ver: 2025/11/29
*/
#include "KR_File.h"
#include <direct.h> //フォルダ作成のため導入.

//KrLib名前空間.
namespace KR
{
	//ファイルを開く.
	int File::Open(MY_STRING path, MY_STRING mode, bool isMakeDir) {

		//先にファイルを閉じる.
		Close();
		//フォルダ作成.
		if (isMakeDir) { MakeDir(path); }
		//ファイルを開く(fopen)
		fp = _tfopen(path.c_str(), mode.c_str());
		if (fp == nullptr) {
			return -1; //読み込みエラー.
		}
		return 0; //正常終了.
	}
	//ファイルを閉じる.
	void File::Close() {

		//既に開いているファイルがあるなら.
		if (fp != nullptr) {
			fclose(fp); //ファイルを閉じる.
			fp = nullptr;
		}
	}
	//フォルダを作成(なければ)
	int File::MakeDir(MY_STRING path) {
		//文字数ループ.
		for (int i = 0; i < path.size(); i++) {
			//「/」区切りでフォルダ作成.
			if (path[i] == '/') {
				int err = _tmkdir(path.substr(0, i).c_str());
				_return(-1, err < 0); //-1: _tmkdirエラー.
			}
		}
		return 0; //正常終了.
	}

	//読み込み(文字列)
	MY_STRING File::ReadString() {

		//既に開いているファイルがあるなら.
		if (fp != nullptr) {
			TCHAR str[256];        //文字列格納用.
			_fgetts(str, 256, fp); //ファイルから読み込み(fgets)
			return str;
		}
		else {
			return _T("null"); //読み込み失敗.
		}
	}
	//読み込み(数字)
	int File::ReadInt() {

		//既に開いているファイルがあるなら.
		if (fp != nullptr) {
			TCHAR str[256];        //文字列格納用.
			_fgetts(str, 256, fp); //ファイルから読み込み(fgets)
			return _ttoi(str);     //int型に変換(atoi)
		}
		else {
			return -1; //読み込み失敗.
		}
	}
	//書き込み(文字列)
	void File::WriteString(MY_STRING data) {

		//既に開いているファイルがあるなら.
		if (fp != nullptr) {
			_fputts(data.c_str(), fp); //ファイルに書き込み(fputs)
		}
	}
	//書き込み(数字)
	void File::WriteInt(int data) {

		//既に開いているファイルがあるなら.
		if (fp != nullptr) {
			TCHAR str[256];       //文字列格納用.
			_itot(data, str, 10); //10進数でchar型に変換(itoa)
			_fputts(str, fp);     //ファイルに書き込み(fputs)
		}
	}
}