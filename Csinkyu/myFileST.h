/*
   - myFileST.h - (original)
   ver.2025/07/26

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

	int  Open(my_string fileName, my_string mode); //ファイルを開く.
	void Close();                                  //ファイルを閉じる.
	
	my_string ReadString ();               //読み込み(文字列)
	int       ReadInt    ();               //読み込み(数字)
	void      WriteString(my_string data); //書き込み(文字列)
	void      WriteInt   (int data);       //書き込み(数字)
};