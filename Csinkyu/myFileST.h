/*
   - myFileST.h - (original)
   ver.2025/07/26

   DxLib: �I���W�i���t�@�C���@�\�̒ǉ�.
*/
#pragma once

//�t�@�C���N���X.
class FileST
{
private:
	FILE* fp; //�t�@�C���|�C���^.

public:
	//�f�X�g���N�^.
	~FileST() {
		Close(); //�����ŕ���.
	}

	int  Open(my_string fileName, my_string mode); //�t�@�C�����J��.
	void Close();                                  //�t�@�C�������.
	
	my_string ReadString ();               //�ǂݍ���(������)
	int       ReadInt    ();               //�ǂݍ���(����)
	void      WriteString(my_string data); //��������(������)
	void      WriteInt   (int data);       //��������(����)
};