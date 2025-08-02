/*
   - myFileST.h - (original)
   ver.2025/08/02

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

	int  Open(MY_STRING fileName, MY_STRING mode); //�t�@�C�����J��.
	void Close();                                  //�t�@�C�������.
	
	MY_STRING ReadString ();               //�ǂݍ���(������)
	int       ReadInt    ();               //�ǂݍ���(����)
	void      WriteString(MY_STRING data); //��������(������)
	void      WriteInt   (int data);       //��������(����)
};