/*
   - KR_File.cpp - (kurosawa original)
   ver: 2025/08/23

   DxLib用のファイル操作機能.
*/
#if !defined DEF_KR_GLOBAL
  #include "KR_Global.h" //stdafx.hに入ってなければここで導入.
  using namespace KR_Lib;
#endif
#include "KR_File.h"
#include <direct.h> //フォルダ作成のため導入.

//KR_Libに使う用.
namespace KR_Lib
{
	//ファイルを開く.
	int File::Open(MY_STRING fileName, MY_STRING mode) {

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
	void File::Close() {

		//既に開いているファイルがあるなら.
		if (fp != nullptr) {
			fclose(fp); //ファイルを閉じる.
			fp = nullptr;
		}
	}
	//フォルダを作成(なければ)
	int File::MakeDir(MY_STRING folderName) {
		return _tmkdir(folderName.c_str()); //_mkdirマクロのTCHAR版.
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