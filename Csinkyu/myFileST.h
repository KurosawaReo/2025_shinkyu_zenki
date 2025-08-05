/*
   - myFileST.h - (original)
   ver.2025/08/05

   DxLib: オリジナルファイル機能の追加.
*/
#pragma once

//ファイルクラス.
class FileST
{
private:
	FILE* fp; //ファイルポインタ.

public:
	//デストラクタ.
	~FileST() {
		Close(); //自動で閉じる.
	}

	int  Open   (MY_STRING fileName, MY_STRING mode); //ファイルを開く.
	int  MakeDir(MY_STRING folderName);			      //フォルダを作成(なければ)
	void Close  ();                                   //ファイルを閉じる.

	MY_STRING ReadString ();               //読み込み(文字列)
	int       ReadInt    ();               //読み込み(数字)
	void      WriteString(MY_STRING data); //書き込み(文字列)
	void      WriteInt   (int data);       //書き込み(数字)
};