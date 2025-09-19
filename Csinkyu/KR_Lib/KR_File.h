/*
   - KR_File.h - (DxLib)
   ver: 2025/09/10

   ファイル操作機能を追加します。
*/
#pragma once

//KR_Libに使う用.
namespace KR_Lib
{
	//ファイルクラス.
	class File
	{
	private:
		FILE* fp; //ファイルポインタ.

	public:
		//destructor.
		~File() {
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
}