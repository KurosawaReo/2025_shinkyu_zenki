#include "Player.h"

int PlayerX = 320, PlayerY = 400, PlayerGraph = -1; // �������ɏ����l��ݒ�
int i = 0; // i�ɂ������l��ݒ�

//������.
void InitPlayer() {

	PlayerGraph = LoadGraph(_T("image/Player.png"));
	if (PlayerGraph == -1){
		return; //�G���[.
	}

	//�����ʒu�̐ݒ�
	PlayerX = 320; // ��ʒ�����X���W
	PlayerY = 400; // ��ʉ�����Y���W
}

//�X�V.
void UpdatePlayer() {

}

//�`��.
void DrawPlayer() {
	DrawExtendGraph(270, 430, 270 + 50, 430 + 50, PlayerGraph, TRUE);
}