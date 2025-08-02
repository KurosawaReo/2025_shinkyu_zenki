/*
   - myFileST.cpp - (original)
   ver.2025/08/02

   DxLib: �I���W�i���t�@�C���@�\�̒ǉ�.
*/
#include "myFileST.h"

//�t�@�C�����J��.
int FileST::Open(MY_STRING fileName, MY_STRING mode) {

	//��Ƀt�@�C�������.
	Close();
	//�t�@�C�����J��(fopen)
	fp = _tfopen(fileName.c_str(), mode.c_str());
	if (fp == nullptr) {
		return -1; //�ǂݍ��݃G���[.
	}
	return 0; //����I��.
}
//�t�@�C�������.
void FileST::Close() {

	//���ɊJ���Ă���t�@�C��������Ȃ�.
	if (fp != nullptr) {
		fclose(fp); //�t�@�C�������.
		fp = nullptr;
	}
}

//�ǂݍ���(������)
MY_STRING FileST::ReadString() {

	//���ɊJ���Ă���t�@�C��������Ȃ�.
	if (fp != nullptr) {
		TCHAR str[256];        //������i�[�p.
		_fgetts(str, 256, fp); //�t�@�C������ǂݍ���(fgets)
		return str;
	}
	else {
		return _T("null"); //�ǂݍ��ݎ��s.
	}
}
//�ǂݍ���(����)
int FileST::ReadInt() {

	//���ɊJ���Ă���t�@�C��������Ȃ�.
	if (fp != nullptr) {
		TCHAR str[256];        //������i�[�p.
		_fgetts(str, 256, fp); //�t�@�C������ǂݍ���(fgets)
		return _ttoi(str);     //int�^�ɕϊ�(atoi)
	}
	else {
		return -1; //�ǂݍ��ݎ��s.
	}
}
//��������(������)
void FileST::WriteString(MY_STRING data) {

	//���ɊJ���Ă���t�@�C��������Ȃ�.
	if (fp != nullptr) {
		_fputts(data.c_str(), fp); //�t�@�C���ɏ�������(fputs)
	}
}
//��������(����)
void FileST::WriteInt(int data) {

	//���ɊJ���Ă���t�@�C��������Ȃ�.
	if (fp != nullptr) {
		TCHAR str[256];       //������i�[�p.
		_itot(data, str, 10); //10�i����char�^�ɕϊ�(itoa)
		_fputts(str, fp);     //�t�@�C���ɏ�������(fputs)
	}
}