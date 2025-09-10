/*
   - KR_File.h - (DxLib)
   ver: 2025/09/10

   �t�@�C������@�\��ǉ����܂��B
*/
#pragma once

//KR_Lib�Ɏg���p.
namespace KR_Lib
{
	//�t�@�C���N���X.
	class File
	{
	private:
		FILE* fp; //�t�@�C���|�C���^.

	public:
		//destructor.
		~File() {
			Close(); //�����ŕ���.
		}

		int  Open   (MY_STRING fileName, MY_STRING mode); //�t�@�C�����J��.
		int  MakeDir(MY_STRING folderName);			      //�t�H���_���쐬(�Ȃ����)
		void Close  ();                                   //�t�@�C�������.

		MY_STRING ReadString ();               //�ǂݍ���(������)
		int       ReadInt    ();               //�ǂݍ���(����)
		void      WriteString(MY_STRING data); //��������(������)
		void      WriteInt   (int data);       //��������(����)
	};
}