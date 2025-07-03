#include "GameManager.h"
#include "Player.h"

#include "Obstacle5.h"

//������(���̂ݍs��)
//���Z�b�g(����ł��s��)
void Obstacle5::Init(GameData* data, Player* player)
{
	//���̂̃A�h���X�����炤.
	this->data = data;
	this->player = player;

	// �t���b�V���G�t�F�N�g�̏�����
	for (int i = 0; i < OBSTACLE5_FLASH_MAX; i++) {
		flashEffect[i].ValidFlag = 0;
		flashEffect[i].Counter = 0.0f;
		flashEffect[i].Duration = 0.0f;
		flashEffect[i].x = 0.0;
		flashEffect[i].y = 0.0;
		flashEffect[i].BaseSize = 0;
	}
}
void Obstacle5::Reset(double x, double y, float speed, int direction)
{
	line.stPos.x = x;
	line.stPos.y = y;
	this->speed = speed;
	// direction �͕K�v�ɉ����Ďg�p

	// ���Z�b�g���Ƀt���b�V���G�t�F�N�g���J�n
	StartFlashEffect(x, y);
}

// �t���b�V���G�t�F�N�g���J�n����֐���ǉ�
void Obstacle5::StartFlashEffect(double x, double y)
{
	// �󂢂Ă���X���b�g��T��
	for (int i = 0; i < OBSTACLE5_FLASH_MAX; i++) {
		if (flashEffect[i].ValidFlag == 0) {
			flashEffect[i].x = x;
			flashEffect[i].y = y;
			flashEffect[i].Counter = 0.0f;
			flashEffect[i].Duration = 60.0f;  // �K�؂Ȏ������Ԃɒ���
			flashEffect[i].BaseSize = 20;     // �K�؂Ȋ�{�T�C�Y�ɒ���
			flashEffect[i].ValidFlag = 1;
			break;
		}
	}
}

// ����I�ɃG�t�F�N�g�𐶐�����֐���ǉ�
void Obstacle5::UpdateFlashGeneration()
{
	static int flashTimer = 0;
	static int flashInterval = 120; // 2�b�Ԋu�i60FPS�z��j

	flashTimer++;
	if (flashTimer >= flashInterval) {
		// �V�����t���b�V���G�t�F�N�g�𐶐�
		StartFlashEffect(line.stPos.x, line.stPos.y);
		flashTimer = 0;
	}
}
//�X�V.
void Obstacle5::Update()
{
	Hitjudgment();
}


//�`��.
void Obstacle5::Draw()
{
	DrawObstFlash();
}
void Obstacle5::Hitjudgment()
{

	// �t���b�V���G�t�F�N�g�ƃv���C���[�̓����蔻��
	for (int i = 0; i < OBSTACLE5_FLASH_MAX; i++)
	{
		if (flashEffect[i].ValidFlag == 0)
		{
			continue; // �����ȃG�t�F�N�g���X�L�b�v
		}

		// �G�t�F�N�g�̃T�C�Y�����Ԃɉ����Ċg��i�`��Ɠ����v�Z�j
		float sizeMultiplier = OBSTACLE5_FLASH_SIZE_INIT + (
			flashEffect[i].Counter * OBSTACLE5_FLASH_SIZE_SPREAD / flashEffect[i].Duration
			);
		int effectSize = _int(flashEffect[i].BaseSize * sizeMultiplier);

		// �v���C���[�̈ʒu���擾
		DBL_XY playerPos = player->GetPos();

		// �v���C���[�ƃG�t�F�N�g�~�̋������v�Z
		double dx = playerPos.x - flashEffect[i].x;
		double dy = playerPos.y - flashEffect[i].y;
		double distance = sqrt(dx * dx + dy * dy);

		// �v���C���[�̓����蔻�蔼�a�i�K�؂Ȓl�ɒ������Ă��������j
		float playerRadius = 10.0f; // �܂��� player->GetHitSize() �ȂǁA���ۂ̃��\�b�h������Ύg�p

		// �~���m�̓����蔻��
		if (distance < (effectSize + playerRadius))
		{
			player->PlayerDeath();
			return; // ��x���񂾂珈���I��
		}
	}

}
void Obstacle5::DrawObstFlash()
{
	for (int i = 0; i < OBSTACLE5_FLASH_MAX; i++)
	{
		if (flashEffect[i].ValidFlag == 0)
		{
			continue;//�����ȃG�t�F�N�g���X�L�b�v.
		}
		//�G�t�F�N�g�̓����x�����Ԃɉ����Čv�Z.
		float alpha = 1.0f - (
			flashEffect[i].Counter * OBSTACLE5_FLASH_ALPHA_TM / flashEffect[i].Duration
			);
		int alphaValue = (int)(255 * alpha);
		alphaValue = max(alphaValue, 0); //������0.
		//�G�t�F�N�g�̃T�C�Y�����Ԃɉ����Ċg��.
		float sizeMultiplier = OBSTACLE5_FLASH_SIZE_INIT + (
			flashEffect[i].Counter * OBSTACLE5_FLASH_SIZE_SPREAD / flashEffect[i].Duration
			);
		int effectSize = (int)(flashEffect[i].BaseSize * sizeMultiplier);
		int innerSize = effectSize / 2;

		//���˃G�t�F�N�g���~�`�ŕ`��(��������)
		SetDrawBlendModeST(MODE_ADD, alphaValue);
		DrawCircle((int)(flashEffect[i].x), (int)(flashEffect[i].y), effectSize, GetColor(0, 255, 255), FALSE);
		DrawCircle((int)(flashEffect[i].x), (int)(flashEffect[i].y), innerSize, GetColor(0, 255, 200), FALSE); // �����ɂ�薾�邢�~��`��

		//�G�t�F�N�g�̃J�E���^���X�V
		flashEffect[i].Counter += (data->isSlow) ? (float)SLOW_MODE_SPEED : 1.0f;

		//�G�t�F�N�g���Ԃ��I�������疳�������ĐV�����G�t�F�N�g���J�n
		if (flashEffect[i].Counter >= flashEffect[i].Duration)
		{
			// ���݂̈ʒu��ۑ�
			double currentX = flashEffect[i].x;
			double currentY = flashEffect[i].y;

			// ���݂̃G�t�F�N�g�𖳌���
			flashEffect[i].ValidFlag = 0;

			// �V�����G�t�F�N�g���J�n�i�A���\�����邽�߁j
			StartFlashEffect(currentX, currentY);
		}
	}
	//�ʏ�̕`�惂�[�h�ɖ߂�
	ResetDrawBlendMode();
}