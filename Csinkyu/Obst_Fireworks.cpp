/*
   - Obst_Fireworks.cpp -

   ��Q��: �ԉ�.
*/
#include "Player.h"
#include "GameManager.h"
#include "LaserManager.h"
#include "Obst_Fireworks.h"
//#include <cmath>    KR���C�u�����ɒ�`�������Ă邽�ߕs�v.
//#include <cstdlib>

// ������
void FireworksManager::Init() {

	p_data     = GameData::GetPtr();
	p_player   = Player::GetPtr();
	p_laserMng = LaserManager::GetPtr();

	// �ԉ΃f�[�^�̏�����
	for (int i = 0; i < FIREWORKS_CNT_MAX; i++) {
		fireworks[i].ValidFlag = 0;
		fireworks[i].x = 0.0f;
		fireworks[i].y = 0.0f;
		fireworks[i].targetX = 0.0f;
		fireworks[i].targetY = 0.0f;
		fireworks[i].vx = 0.0f;
		fireworks[i].vy = 0.0f;
		fireworks[i].Counter = 0.0f;
		fireworks[i].state = FIREWORKS_STATE_WARNING;
		fireworks[i].sparkCount = 0;
	}
}

// ���Z�b�g
void FireworksManager::Reset() {
	spawnTimer = 120; // �ŏ��͏����ҋ@

	// �����̉ԉ΂����ׂăN���A
	for (int i = 0; i < FIREWORKS_CNT_MAX; i++) {
		fireworks[i].ValidFlag = 0;
		fireworks[i].Counter = 0.0f;
		fireworks[i].state = FIREWORKS_STATE_WARNING;
	}
}

// �����_���ʒu����
void FireworksManager::GenerateRandomPosition(float& x, float& y) {
	int margin = 80;
	x = (float)(margin + (rand() % (WINDOW_WID - margin * 2)));
	y = (float)(margin + (rand() % (WINDOW_HEI - margin * 2 - FIREWORKS_LAUNCH_HEIGHT)));
}

// �����`�F�b�N(�߂�����ԉ΂��Ȃ����true)
bool FireworksManager::CheckDistance(float x, float y) {
	for (int i = 0; i < FIREWORKS_CNT_MAX; i++) {
		if (fireworks[i].ValidFlag == 1) {
			float dx = x - fireworks[i].targetX;
			float dy = y - fireworks[i].targetY;
			float distance = sqrt(dx * dx + dy * dy);
			if (distance < FIREWORKS_MIN_DISTANCE) {
				return false;
			}
		}
	}
	return true;
}

// �ԉΊJ�n
void FireworksManager::StartFireworks(float x, float y) {
	for (int i = 0; i < FIREWORKS_CNT_MAX; i++) {
		if (fireworks[i].ValidFlag == 0) {
			fireworks[i].targetX = x;
			fireworks[i].targetY = y;
			fireworks[i].x = x;
			fireworks[i].y = y;
			fireworks[i].vx = 0.0f;
			fireworks[i].vy = 0.0f;
//			fireworks[i].Duration = FIREWORKS_WARNING_DURATION + 120; // �\��+�������� //�ǋL:����Ȃ��C������
			fireworks[i].Counter = FIREWORKS_WARNING_DURATION;
			fireworks[i].state = FIREWORKS_STATE_WARNING;
			fireworks[i].sparkCount = FIREWORKS_SPARKS_COUNT + (rand() % 8);
			fireworks[i].ValidFlag = 1;
			break;
		}
	}
}

// �ԉΐ����X�V
void FireworksManager::UpdateFireworksGeneration() {
	spawnTimer -= (p_data->isSlow) ? SLOW_MODE_SPEED : 1;

	if (spawnTimer <= 0) {
		//1�`3�̉ԉ΂������_������.
		int spawnCount = 1 + (rand() % FIREWORKS_RND_MAX);

		for (int i = 0; i < spawnCount; i++) {
			float x, y;
			bool validPosition = false;
			int attempts = 0;

			while (!validPosition && attempts < 10) {
				GenerateRandomPosition(x, y);
				validPosition = CheckDistance(x, y);
				attempts++;
			}

			if (validPosition) {
				StartFireworks(x, y);
			}
		}
		//�o���J�E���^�[���Z�b�g.
		spawnTimer = FIREWORKS_SPAWN_SPAN * p_data->spawnRate;
	}
}

// �ʉԉ΍X�V
void FireworksManager::UpdateIndividualFireworks() {

	for (int i = 0; i < FIREWORKS_CNT_MAX; i++) {
		if (fireworks[i].ValidFlag == 0) continue;

		fireworks[i].Counter -= (p_data->isSlow) ? SLOW_MODE_SPEED : 1.0f;

		//�x���\��.
		if (fireworks[i].Counter > 0) {
			fireworks[i].state = FIREWORKS_STATE_WARNING;
		}
		//����.
		else {
			////�������[�h����Ȃ��Ȃ�ύX.
			//if (fireworks[i].state != FIREWORKS_STATE_EXPLODING) {
			//	fireworks[i].state = FIREWORKS_STATE_EXPLODING;
			//	ExplodeFireworks(i);
			//}
			fireworks[i].ValidFlag = 0; //�ԉΖ{�̏���.
			ExplodeFireworks(i);
		}
	}
}

// ��������
void FireworksManager::ExplodeFireworks(int index) {
	CreateFireworksSparks(fireworks[index].x, fireworks[index].y);

	// ������
	SoundMng* sound = SoundMng::GetPtr();
	sound->Play(_T("Explosion"), false, 70);
}

// �ԉ΂̉Ήԍ쐬�iLaserManager���g�p�j- �������ʕt��
void FireworksManager::CreateFireworksSparks(float x, float y) {
	int sparkCount = fireworks[0].sparkCount; // ����0�Ԃ̉ΉԐ����g�p

	for (int i = 0; i < sparkCount; i++) {
		float angle = _flt((2.0f * M_PI * i) / sparkCount);

		// �������x�������_���ɒ���
		float baseSpeed = 2.5f + (float)(rand() % 3); // 2.5~4.5�͈̔�
		float speedVariation = 0.8f + (float)(rand() % 4) / 10.0f; // 0.8~1.1�͈̔�
		float speed = baseSpeed * speedVariation;

		// �p�x�ɏ��������_������ǉ�
		float angleVariation = _flt((float)(rand() % 40 - 20) * M_PI / 180.0f); // �}20�x
		angle += angleVariation;

		DBL_XY pos = { x, y };
		DBL_XY vel = {
			cos(angle) * speed,
			sin(angle) * speed - 0.5f // ������Ƀo�C�A�X��������
		};

		// �������郌�[�U�[�Ƃ��Đ���
		p_laserMng->SpawnLaser(pos, vel, Laser_Falling);
	}
}

// �X�V
void FireworksManager::Update() {
	UpdateFireworksGeneration();
	UpdateIndividualFireworks();
}

// �`��
void FireworksManager::Draw() {
	for (int i = 0; i < FIREWORKS_CNT_MAX; i++) {
		if (fireworks[i].ValidFlag == 0) continue;

		DrawWarningEffect(i);

//		if (fireworks[i].state == FIREWORKS_STATE_WARNING) {
//			DrawWarningEffect(i);
//		}
		// �����G�t�F�N�g�͕`�悵�Ȃ��i�g��폜�̂��߁j
	}

	// �`�惂�[�h�����Z�b�g
	ResetDrawBlendMode();
}

// �\���G�t�F�N�g�`��
void FireworksManager::DrawWarningEffect(int index) {

	const float sepTime = 30; //��؂莞��.

	float elapsedTime = fireworks[index].Counter;

	// �_�ŃG�t�F�N�g
	int alphaValue;
	if (elapsedTime < sepTime) {
		double blinkPhase = fmod(elapsedTime, 20);
		double blinkAlpha = sin(blinkPhase * M_PI/20);
		alphaValue = (int)(255 - 150 * blinkAlpha);
	}
	else {
		alphaValue = 255;
	}

	// �����T�C�Y
	int warningSize;
	if (elapsedTime >= sepTime) {
		double pulseFactor = 1.0f + 0.3f * sin(elapsedTime * 4.0f * M_PI / 60.0f);
		warningSize = (int)(30 * pulseFactor);
	}
	else {
		warningSize = 30;
	}

	SetDrawBlendModeST(MODE_ALPHA, alphaValue);

	Circle cir;
	// �O���̉~�D�F
	cir = { {fireworks[index].targetX, fireworks[index].targetY}, (float)warningSize, GetColor(128, 128, 128) };
	DrawCircleST(&cir, false, true);
	// �����̉~�D�F
	cir = { {fireworks[index].targetX, fireworks[index].targetY}, (float)(warningSize / 2), GetColor(128, 128, 128) };
	DrawCircleST(&cir, false, true);
	// ���S�_�D�F
	cir = { {fireworks[index].targetX, fireworks[index].targetY}, 5, GetColor(128,128, 128) };
	DrawCircleST(&cir, false, true);
}