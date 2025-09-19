/*
   - Ripples.cpp -

   ��Q��: �g��.
*/
#include "GameManager.h"
#include "Player.h"

#include "Obst_Ripples.h"

//������(���̂ݍs��)
//���Z�b�g(����ł��s��)
void Ripples::Init()
{
	//���̂̃A�h���X�����炤.
	p_data   = GameData::GetPtr();
	p_player = Player::GetPtr();

	// �t���b�V���G�t�F�N�g�̏�����
	for (int i = 0; i < RIPPLES_FLASH_MAX; i++) {
		flashEffect[i].ValidFlag = 0;
		flashEffect[i].Counter = 0.0f;
		flashEffect[i].Duration = 0.0f;
		flashEffect[i].x = 0.0;
		flashEffect[i].y = 0.0;
		flashEffect[i].BaseSize = 0;
	}
}
void Ripples::Reset()
{
	flashTimer = 80; //�ŏ��͏��������ҋ@.

	// ���Z�b�g���Ɋ����̃t���b�V���G�t�F�N�g�����ׂăN���A
	for (int i = 0; i < RIPPLES_FLASH_MAX; i++) {
		flashEffect[i].ValidFlag = 0;
		flashEffect[i].Counter = 0.0f;
		flashEffect[i].Duration = 0.0f;
		flashEffect[i].x = 0.0;
		flashEffect[i].y = 0.0;
		flashEffect[i].BaseSize = 0;
	}
}

void Ripples::GenerateRandomPosition(double& x, double& y)  // �Q�Ɠn���ɏC��
{
	//��ʃT�C�Y
	int screnWidth = WINDOW_WID;
	int screnHeight = WINDOW_HEI;
	int margin = 100;//��ʒ[����̃}�[�W���傫��.
	x = margin + (rand() % (screnWidth - margin * 2));
	y = margin + (rand() % (screnHeight - margin * 2));
}
bool Ripples::CheckDistance(double x, double y)
{
	for (int i = 0; i < RIPPLES_FLASH_MAX; i++)
	{
		if (flashEffect[i].ValidFlag == 1)
		{
			double dx = x - flashEffect[i].x;
			double dy = y - flashEffect[i].y;
			double distance = sqrt(dx * dx + dy * dy);  // dy * dy �ɏC��
			if (distance < RIPPLES_MIN_DISTANCE)
			{
				return false;
			}
		}
	}
	return true;
}
// �t���b�V���G�t�F�N�g���J�n����֐���ǉ�
void Ripples::StartFlashEffect(double x, double y)
{
	// �󂢂Ă���X���b�g��T��
	for (int i = 0; i < RIPPLES_FLASH_MAX; i++) {
		if (flashEffect[i].ValidFlag == 0) {
			flashEffect[i].x = x;
			flashEffect[i].y = y;
			flashEffect[i].Duration = RIPPLES_WARNING_DURATION + RIPPLES_ACTIVE_DURATION;
			flashEffect[i].Counter = flashEffect[i].Duration;  // �������Ԃ���J�n�i�J�E���g�_�E���j
			flashEffect[i].BaseSize = 20;     // �K�؂Ȋ�{�T�C�Y�ɒ���
			flashEffect[i].ValidFlag = 1;
			break;
		}
	}
}
void Ripples::SpawnObstaclegroup()
{
	//�����o���������_���Ɍ���.
	int spawnCount = 1 + (rand() % RIPPLES_MAX_SIMULTANEOUS);
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
int Ripples::GetEffectState(int index)
{
	if (flashEffect[index].Counter > RIPPLES_ACTIVE_DURATION)  // �c�莞�Ԃ��A�N�e�B�u���Ԃ��傫����Όx�����
	{
		return RIPPLES_STATE_WARNING;
	}
	else
	{
		return RIPPLES_STATE_ACTIVE;
	}
}

// ����I�ɃG�t�F�N�g�𐶐�����֐���ǉ�
void Ripples::UpdateFlashGeneration()
{
	//�^�C�}�[����.
	flashTimer -= ((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
	//0�ȉ��ɂȂ�������s.
	if (flashTimer <= 0) {
		// �V�����t���b�V���G�t�F�N�g�𐶐�
		SpawnObstaclegroup();  // �����_���ʒu�ɕ�����������悤�ɕύX

		// GameData��spawnRate���g�p���ăC���^�[�o���𒲐�
		flashTimer = RIPPLES_SPAWN_SPAN * p_data->spawnRate;
	}

	//�S�t���b�V��.
	for (int i = 0; i < RIPPLES_FLASH_MAX; i++)
	{
		if (flashEffect[i].ValidFlag == 0)
		{
			continue;//�����ȃG�t�F�N�g���X�L�b�v.
		}

		//�J�E���g�_�E��.
		flashEffect[i].Counter -= (p_data->isSlow) ? (float)SLOW_MODE_SPEED : 1.0f;
		//�G�t�F�N�g���Ԃ��I�������疳����.
		if (flashEffect[i].Counter <= 0)  // 0�ȉ��ɂȂ�����I��
		{
			flashEffect[i].ValidFlag = 0;
			flashEffect[i].AlreadyHit = false; //�����蔻��̃��Z�b�g.
		}
	}
}
//�X�V.
void Ripples::Update()
{
	UpdateFlashGeneration();
	Hitjudgment();
}

//�`��.
void Ripples::Draw()
{
	DrawObstFlash();
}
//�����蔻��.
void Ripples::Hitjudgment()
{
	bool isPlaySound = false; //��x�̂݃T�E���h�𗬂��p.

	for (int i = 0; i < RIPPLES_FLASH_MAX; i++) {
		if (flashEffect[i].ValidFlag == 0 || flashEffect[i].Counter <= 0) {
			continue;
		}

		int effectState = GetEffectState(i);
		if (effectState == RIPPLES_STATE_WARNING) {
			continue;
		}

		// �o�ߎ��Ԃ̌v�Z
		float elapsedTime = flashEffect[i].Duration - flashEffect[i].Counter;
		float activeElapsedTime = elapsedTime - RIPPLES_WARNING_DURATION;
		float activeProgress = activeElapsedTime / RIPPLES_ACTIVE_DURATION;

		// �A�N�e�B�u��ԂɂȂ������ゾ������
		if (effectState == RIPPLES_STATE_ACTIVE && !flashEffect[i].AlreadyHit) {

			float sizeMultiplier = RIPPLES_FLASH_SIZE_INIT + (activeProgress * RIPPLES_FLASH_SIZE_SPREAD);
			int effectSize = (int)(flashEffect[i].BaseSize * sizeMultiplier);

			DBL_XY playerPos = p_player->GetPos();
			double dx = playerPos.x - flashEffect[i].x;
			double dy = playerPos.y - flashEffect[i].y;
			double distance = sqrt(dx * dx + dy * dy);
			float playerRadius = 10.0f;

			if (distance < (effectSize * 0.8f + playerRadius)) {
				p_player->PlayerDeath();
			}

			//�T�E���h.
			if (!isPlaySound) {
				SoundMng* sound = SoundMng::GetPtr();
				sound->Play(_T("Ripples"), false, 73);
				isPlaySound = true; //�����Đ����Ȃ�.
			}

			// ��x������s������t���O�𗧂ĂāA�Ȍ�͖�����
			flashEffect[i].AlreadyHit = true;
		}
	}
}

void Ripples::DrawObstFlash()
{
	for (int i = 0; i < RIPPLES_FLASH_MAX; i++)
	{
		if (flashEffect[i].ValidFlag == 0)
		{
			continue;//�����ȃG�t�F�N�g���X�L�b�v.
		}
		int effetState = GetEffectState(i);
		if (effetState == RIPPLES_STATE_WARNING)
		{
			// �\����Ԃ̕`��i�Ԃ��_�ŃG�t�F�N�g�j
			DrawWarningEffect(i);
		}
		else
		{
			// �A�N�e�B�u��Ԃ̕`��i���̃t���b�V���G�t�F�N�g�j
			DrawActiveEffect(i);
		}
	}
	//�ʏ�̕`�惂�[�h�ɖ߂�
	ResetDrawBlendMode();
}

void Ripples::DrawWarningEffect(int index)
{
	//�c�莞�Ԃ���o�ߎ��Ԃ��v�Z.
	float elapsedTime = flashEffect[index].Duration - flashEffect[index].Counter;

	//1: �����x�̌v�Z(�_��)
	int alphaValue;
	//�U���O�ɂȂ�܂œ_��.
	if (elapsedTime < 90) {
		double blinkPhase = fmod(elapsedTime, RIPPLES_FLASH_BLINK_TM);
		double blinkAlpha = sin(blinkPhase * M_PI/RIPPLES_FLASH_BLINK_TM); //0.0�`1.0������������ۂ�.
		alphaValue = (int)(255 - 200*blinkAlpha);
	}
	else {
		alphaValue = 255; //�ő�l.
	}

	//2: �T�C�Y�̌v�Z.
	int warningSize;
	//�U���O�ɂȂ����疬���J�n.
	if (elapsedTime >= 90) {
		const float pulseRate = 4.0f;
		double pulseFactor = 1.0f + 0.4f * sin(elapsedTime * pulseRate * M_PI/60.0f);
		warningSize = (int)(flashEffect[index].BaseSize * pulseFactor);
	}
	else {
		warningSize = flashEffect[index].BaseSize; //�Œ�T�C�Y.
	}

	// �\���G�t�F�N�g��`��.
	SetDrawBlendModeST(MODE_ALPHA, alphaValue);

	Circle cir;
	cir = { {flashEffect[index].x, flashEffect[index].y}, (float)warningSize,   GetColor(150, 150, 150) };
	DrawCircleST(&cir, false, true);
	cir = { {flashEffect[index].x, flashEffect[index].y}, (float)warningSize/2, GetColor(200, 200, 200) };
	DrawCircleST(&cir, false, true);
	cir = { {flashEffect[index].x, flashEffect[index].y}, (float)warningSize+5, GetColor(120, 120, 120) }; // �O�������O
	DrawCircleST(&cir, false, true);

	//�ʏ�̕`�惂�[�h�ɖ߂�
	ResetDrawBlendMode();
}

void Ripples::DrawActiveEffect(int index)
{
	// �c�莞�Ԃ���o�ߎ��Ԃ��v�Z
	float elapsedTime = flashEffect[index].Duration - flashEffect[index].Counter;
	float activeElapsedTime = elapsedTime - RIPPLES_WARNING_DURATION;

	// �A�N�e�B�u��Ԃł̐i�s�x
	float activeProgress = activeElapsedTime / RIPPLES_ACTIVE_DURATION;

	// �����x�����Ԃɉ����Čv�Z
	float alpha = 1.0f - (activeProgress * RIPPLES_FLASH_ALPHA_TM);
	int alphaValue = (int)(255 * max(alpha, 0.0f));

	// �G�t�F�N�g�̃T�C�Y�����Ԃɉ����Ċg��
	float sizeMultiplier = RIPPLES_FLASH_SIZE_INIT + (activeProgress * RIPPLES_FLASH_SIZE_SPREAD);
	int effectSize = (int)(flashEffect[index].BaseSize * sizeMultiplier);
	int innerSize = effectSize / 2;

	// �A�N�e�B�u�G�t�F�N�g���~�`�ŕ`��i�V�A���F�Ō���j
	SetDrawBlendModeST(MODE_ADD, alphaValue);

	Circle cir;
	cir = {{flashEffect[index].x, flashEffect[index].y}, (float)effectSize, GetColor(0, 255, 255)};
	DrawCircleST(&cir, false, true);
	cir = {{flashEffect[index].x, flashEffect[index].y}, (float)innerSize,  GetColor(0, 255, 200)};
	DrawCircleST(&cir, false, true);

	//�ʏ�̕`�惂�[�h�ɖ߂�
	ResetDrawBlendMode();
}