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

void Obstacle5::GenerateRandomPosition(double& x, double& y)  // �Q�Ɠn���ɏC��
{
	//��ʃT�C�Y
	int screnWidth = WINDOW_WID;
	int screnHeight = WINDOW_HEI;
	int margin = 100;//��ʒ[����̃}�[�W���傫��.
	x = margin + (rand() % (screnWidth - margin * 2));
	y = margin + (rand() % (screnHeight - margin * 2));
}
bool Obstacle5::CheckDistance(double x, double y)
{
	for (int i = 0; i < OBSTACLE5_FLASH_MAX; i++)
	{
		if (flashEffect[i].ValidFlag == 1)
		{
			double dx = x - flashEffect[i].x;
			double dy = y - flashEffect[i].y;
			double distance = sqrt(dx * dx + dy * dy);  // dy * dy �ɏC��
			if (distance < OBSTACLE5_MIN_DISTANCE)
			{
				return false;
			}
		}
	}
	return true;
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
			flashEffect[i].Duration = OBSTACLE5_WARNING_DURATION + OBSTACLE5_ACTIVE_DURATION;;  // �K�؂Ȏ������Ԃɒ���
			flashEffect[i].BaseSize = 20;     // �K�؂Ȋ�{�T�C�Y�ɒ���
			flashEffect[i].ValidFlag = 1;
			break;
		}
	}
}
void Obstacle5::SpawnObstaclegroup()
{
	//�����o���������_���Ɍ���.
	int spawnCount = 1 + (rand() % OBSTACLE5_MAX_SIMULTANEOUS);
	for (int i = 0; i < spawnCount; i++)
	{
		double x{}, y{};
		bool validPosition = false;
		int attempts = 0;

		while (!validPosition && attempts < 10)
		{
			GenerateRandomPosition(x, y);
			validPosition = CheckDistance(x, y);
			attempts++;
		}
		if (validPosition)
		{
			StartFlashEffect(x, y);
		}
	}
}
int Obstacle5::GetEffectState(int index)
{
	if (flashEffect[index].Counter < OBSTACLE5_WARNING_DURATION)  // ��r���Z�q�ɏC��
	{
		return OBSTACLE5_STATE_WARNING;
	}
	else
	{
		return OBSTACLE5_STATE_ACTIVE;
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
		SpawnObstaclegroup();  // �����_���ʒu�ɕ�����������悤�ɕύX
		flashTimer = 0;
	}
}
//�X�V.
void Obstacle5::Update()
{
	UpdateFlashGeneration();
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

		// �G�t�F�N�g�̏�Ԃ��m�F
		int effectState = GetEffectState(i);

		// �\����Ԃ̏ꍇ�͓����蔻����X�L�b�v
		if (effectState == OBSTACLE5_STATE_WARNING)
		{
			continue;
		}

		// �G�t�F�N�g�̃T�C�Y�����Ԃɉ����Ċg��i�`��Ɠ����v�Z�j
		float sizeMultiplier = OBSTACLE5_FLASH_SIZE_INIT + (
			flashEffect[i].Counter * OBSTACLE5_FLASH_SIZE_SPREAD / flashEffect[i].Duration
			);
		int effectSize = (int)(flashEffect[i].BaseSize * sizeMultiplier);

		// �v���C���[�̈ʒu���擾
		DBL_XY playerPos = player->GetPos();

		// �v���C���[�ƃG�t�F�N�g�~�̋������v�Z
		double dx = playerPos.x - flashEffect[i].x;
		double dy = playerPos.y - flashEffect[i].y;
		double distance = sqrt(dx * dx + dy * dy);

		// �v���C���[�̓����蔻�蔼�a�i�K�؂Ȓl�ɒ������Ă��������j
		float playerRadius = 10.0f; // �܂��� player->GetHitSize() �ȂǁA���ۂ̃��\�b�h������Ύg�p

		// �~���m�̓����蔻��
		if (distance < (effectSize * 0.8f + playerRadius))
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
		int effetState = GetEffectState(i);
		if (effetState == OBSTACLE5_STATE_WARNING)
		{
			// �\����Ԃ̕`��i�Ԃ��_�ŃG�t�F�N�g�j
			DrawWarningEffect(i);
		}
		else
		{
			// �A�N�e�B�u��Ԃ̕`��i���̃t���b�V���G�t�F�N�g�j
			DrawActiveEffect(i);
		}
		// �J�E���^�̍X�V���C��
		flashEffect[i].Counter += (data->isSlow) ? (float)SLOW_MODE_SPEED : 1.0f;

		//�G�t�F�N�g���Ԃ��I�������疳����.
		if (flashEffect[i].Counter >= flashEffect[i].Duration)
		{
			flashEffect[i].ValidFlag = 0;
		}
	}
	//�ʏ�̕`�惂�[�h�ɖ߂�
	ResetDrawBlendMode();
}
void Obstacle5::DrawWarningEffect(int index)
{
	float blinkRate = 8.0f;
	float blinkPhase = fmod(flashEffect[index].Counter * blinkRate, 60.0f);
	float blinkAlpha = (sin(blinkPhase * 3.14f / 30.0f) + 1.0f) * 0.5f;
	// ��������
	float pulseRate = 4.0f;
	float pulseFactor = 1.0f + 0.4f * sin(flashEffect[index].Counter * pulseRate * 3.14159f / 60.0f);
	int warningSize = (int)(flashEffect[index].BaseSize * pulseFactor);

	int alphaValue = (int)(255 * blinkAlpha * 0.8f);

	// �\���G�t�F�N�g��`��i�ԐF�j
	SetDrawBlendModeST(MODE_ADD, alphaValue);
	DrawCircle((int)(flashEffect[index].x), (int)(flashEffect[index].y), warningSize, GetColor(255, 100, 100), FALSE);
	DrawCircle((int)(flashEffect[index].x), (int)(flashEffect[index].y), warningSize / 2, GetColor(255, 150, 150), FALSE);

	// �O�������O
	DrawCircle((int)(flashEffect[index].x), (int)(flashEffect[index].y), warningSize + 5, GetColor(255, 50, 50), FALSE);
}
void Obstacle5::DrawActiveEffect(int index)
{
	// �A�N�e�B�u��Ԃł̐i�s�x
	float activeProgress = (flashEffect[index].Counter - OBSTACLE5_WARNING_DURATION) / OBSTACLE5_ACTIVE_DURATION;

	// �����x�����Ԃɉ����Čv�Z
	float alpha = 1.0f - (activeProgress * OBSTACLE5_FLASH_ALPHA_TM);
	int alphaValue = (int)(255 * max(alpha, 0.0f));

	// �G�t�F�N�g�̃T�C�Y�����Ԃɉ����Ċg��
	float sizeMultiplier = OBSTACLE5_FLASH_SIZE_INIT + (activeProgress * OBSTACLE5_FLASH_SIZE_SPREAD);
	int effectSize = (int)(flashEffect[index].BaseSize * sizeMultiplier);
	int innerSize = effectSize / 2;

	// �A�N�e�B�u�G�t�F�N�g���~�`�ŕ`��i�V�A���F�Ō���j
	SetDrawBlendModeST(MODE_ADD, alphaValue);
	DrawCircle((int)(flashEffect[index].x), (int)(flashEffect[index].y), effectSize, GetColor(0, 255, 255), FALSE);
	DrawCircle((int)(flashEffect[index].x), (int)(flashEffect[index].y), innerSize, GetColor(0, 255, 200), FALSE);
}