/*
   - myFileST.cpp - (original)
   ver.2025/08/02

   DxLib: オリジナルファイル機能の追加.
*/
#include "myFileST.h"

//ファイルを開く.
int FileST::Open(MY_STRING fileName, MY_STRING mode) {

	//先にファイルを閉じる.
	Close();
	//ファイルを開く(fopen)
	fp = _tfopen(fileName.c_str(), mode.c_str());
	if (fp == nullptr) {
		return -1; //読み込みエラー.
	}
	return 0; //正常終了.
}
//ファイルを閉じる.
void FileST::Close() {

	//既に開いているファイルがあるなら.
	if (fp != nullptr) {
		fclose(fp); //ファイルを閉じる.
		fp = nullptr;
	}
}

//読み込み(文字列)
MY_STRING FileST::ReadString() {

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
int FileST::ReadInt() {

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
void FileST::WriteString(MY_STRING data) {

	//既に開いているファイルがあるなら.
	if (fp != nullptr) {
		_fputts(data.c_str(), fp); //ファイルに書き込み(fputs)
	}
}
//書き込み(数字)
void FileST::WriteInt(int data) {

	//既に開いているファイルがあるなら.
	if (fp != nullptr) {
		TCHAR str[256];       //文字列格納用.
		_itot(data, str, 10); //10進数でchar型に変換(itoa)
		_fputts(str, fp);     //ファイルに書き込み(fputs)
	}
}