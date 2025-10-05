/*
   - Player.cpp -
   プレイヤー管理.
*/
#include "GameManager.h"
#include "LaserManager.h"
#include "Obst_NormalLaserMain.h"
#include "Stage_Tutorial.h"

#include "Player.h"

using namespace Calc; //計算機能を使用.

//初期化(一回のみ行う)
void Player::Init()
{
	p_data      = &GameData::GetInst();
	p_effectMng = &EffectManager::GetInst();
	p_input     = &InputMng::GetInst();

	isDebug = false;

	//画像読み込み.
	imgPlayer[0].     LoadFile(_T("Resources/Images/player_normal.png"));
	imgPlayer[1].     LoadFile(_T("Resources/Images/player_reflect.png"));
	imgPlayerLight[0].LoadFile(_T("Resources/Images/light_color_2.png"));
	imgPlayerLight[1].LoadFile(_T("Resources/Images/light_color_3.png"));
}
//リセット(何回でも行う)
void Player::Reset(DBL_XY _pos, bool _active)
{
	hit        = { _pos, PLAYER_SIZE, {} };
	active     = _active;
	mode       = Player_Normal;
	afterCntr  = 1;
	isMoveAble = true;

	// ダッシュ関連の初期化.
	isDashing    = false;
	dashTimer    = 0;
	dashCooldown = 0;

	//残像配列のリセット.
	for (int i = 0; i < _countof(after); i++) {
		after[i].pos      = _pos;
		after[i].isActive = false;
	}
	//反射エフェクトリセット.
	dashEffectIndex = 0;
	for (int i = 0; i < PLAYER_DASH_EFFECT_MAX; i++) {
		dashEffects[i].active = false;
		dashEffects[i].timer = 0;
		dashEffects[i].alpha = 0.0f;
		dashEffects[i].scale = 1.0f;
		dashEffects[i].pos = _pos;
	}
}
//更新.
void Player::Update()
{
#if defined _DEBUG //Releaseでは入れない.
	//無敵モード.
	if (p_input->IsPushKeyTime(KeyID::M) == 1) {
		isDebug = !isDebug;
	}
#endif

	//有効なら.
	if (active) {
		imgRot += 1.5 * p_data->speedRate; //画像回転.

		UpdateAfterImage();
		UpdateDash();
		PlayerMove();
		
		//反射モード中.
		if (p_data->isReflectMode) {
			//敵のレーザーが近くにあれば.
			if (LaserManager::GetInst().IsExistEnemyLaser(hit.pos, SLOW_MODE_DIS_LEN)) {
				p_data->slowBufCntr = SLOW_MODE_BUF_F;
			}
		}
	}
}
//描画.
void Player::Draw()
{
#if defined _DEBUG //Releaseでは入れない.
	//デバッグ表示.
	if (isDebug) {
		DrawStr str(_T("[Debug] 無敵モード"), {WINDOW_WID/2, WINDOW_HEI/2+300}, COLOR_PLY_DEBUG);
		str.Draw(Anchor::Mid, p_data->font1);
	}
	// エフェクトのデバッグ情報表示
	for (int i = 0; i < PLAYER_DASH_EFFECT_MAX; i++) {
		if (dashEffects[i].active) {
			TCHAR debugStr[128];
			_stprintf_s(debugStr, _T("Effect[%d]: timer=%d, alpha=%.1f, scale=%.1f"),
				i, dashEffects[i].timer, dashEffects[i].alpha, dashEffects[i].scale);
			DrawString(0, 450 + i * 20, debugStr, 0xFFFFFF);
		}
	}
	// ダッシュのデバッグ表示
	if (isDashing || dashCooldown > 0) {
		TCHAR dashStr[128];
		_stprintf_s(dashStr, _T("Dash: timer=%f, cooldown=%f"), dashTimer, dashCooldown);
		DrawString(0, 430, dashStr, isDashing ? 0x00FF00 : 0xFFFF00);
	}
#endif

	//有効なら.
	if (active) {
		DrawAfterImage();

		const float size = 0.17;

		//プレイヤー描画.
		if (mode == Player_Reflect ||
			mode == Player_SuperReflect
		){
			//ダッシュ演出.
			if (isDashing) {
				imgPlayerLight[0].DrawExtend(hit.pos, {0.05, 0.05}, Anchor::Mid, true, true);
			}
			//反射モードの画像.
			imgPlayer[1].DrawRota(hit.pos, size, imgRot, {0, 0}, Anchor::Mid, true, true);
		}
		else {
			//ダッシュ演出.
			if (isDashing) {
				imgPlayerLight[1].DrawExtend(hit.pos, {0.05, 0.05}, Anchor::Mid, true, true);
			}
			//通常モードの画像.
			imgPlayer[0].DrawRota(hit.pos, size, imgRot, {0, 0}, Anchor::Mid, true, true);
		}

		//チュートリアル用.
		if (p_data->stage == STAGE_TUTORIAL) {
			DrawStr str(_T("プレイヤー"), hit.pos.Add(0, -35).ToIntXY(), 0xFFFFFF );
			str.Draw();
		}
	}
}

//ダッシュ処理.
void Player::UpdateDash()
{
	//ダッシュクールダウン減少.
	if (dashCooldown > 0){
		dashCooldown -= 1 * p_data->speedRate;
	}

	//ダッシュ中なら.
	if (isDashing)
	{
		dashTimer -= 1 * p_data->speedRate;
		//ダッシュ時間切れ.
		if (dashTimer <= 0)
		{
			isDashing = false; //ダッシュ終了.
		}
	}
	//ダッシュしてないなら.
	else
	{
		if (dashCooldown <= 0)
		{
			bool dashkey = p_input->IsPushActionTime(_T("PlayerDash")) == 1;
			//ダッシュ開始.
			if (dashkey)
			{
				dashTimer    = PLAYER_DASH_DURATION;
				dashCooldown = PLAYER_DASH_COOLDOWN;
				isDashing    = true;

				//チュートリアルなら.
				if (p_data->stage == STAGE_TUTORIAL) {
					TutorialStage::GetInst().SetPlayerDash(true);
				}
			}
		}
	}
}

//移動処理(斜め対応)
void Player::PlayerMove()
{
	float speed = PLAYER_MOVE_SPEED * p_data->speedRate;

	//移動可能なら.
	if (isMoveAble) {
		//ダッシュ中は加速.
		if (isDashing)
		{
			//残り時間に応じて段々減速.
			speed *= 1.0 + PLAYER_DASH_SPEED * Calc::CalcNumEaseOut(dashTimer/PLAYER_DASH_DURATION);
		}
		//移動.
		p_input->MoveKey4Dir(&hit.pos, speed);
		p_input->MovePadStick(&hit.pos, speed);
		//移動限界.
		FixPosInArea(&hit.pos, { PLAYER_SIZE * 2, PLAYER_SIZE * 2 }, 0, 0, WINDOW_WID - 1, WINDOW_HEI - 1);
	}
}

//死亡処理.
void Player::PlayerDeath() {

	//デバッグモード中は無敵.
	if (isDebug) { return; }

	//まだ生存してるなら.
	if (active) {

		//サウンド.
		InstSoundMng.Play(_T("PlayerDeath"), false, 80);
		//エフェクト.
		EffectData data{};
		data.type = Effect_PlayerDeath;
		data.pos  = hit.pos;
		p_effectMng->SpawnEffect(&data);
		//GamaManagerの関数実行(includeだけすれば使える)
		GameManager::GetInst().GameOver(); //ゲーム終了.
	
		isDashing    = false;
		dashTimer    = 0;
        dashCooldown = 0;
		active       = false;
	}
}

//プレイヤー復活.
void Player::PlayerRevival()
{
	hit.pos = {WINDOW_WID/2, WINDOW_HEI/2};
	active  = true;

	//残像配列のリセット.
	for (int i = 0; i < _countof(after); i++) {
		after[i].pos = hit.pos;
		after[i].isActive = false;
	}
}

//残像更新.
void Player::UpdateAfterImage()
{
	afterCntr -= p_data->speedRate;

	//残像を残すタイミングになったら(基本は毎フレーム)
	if (afterCntr <= 0) {
		afterCntr = 1;

		//残像データを後ろにずらす.
		for (int i = PLAYER_AFT_IMG_NUM - 1; i > 0; i--)
		{
			after[i] = after[i-1];
		}
		after[0].pos      = hit.pos; //プレイヤー座標を1フレーム目に記録.
		after[0].isActive = false;   //一旦無効にする.

		//ダッシュ中.
		if (isDashing) {
			//エフェクト.
			EffectData data;
			data.type = Effect_PlayerDash;
			data.pos  = hit.pos;
			data.ang  = Calc::CalcFacingAng(after[0].pos, after[1].pos); //移動方向の逆向き.
			p_effectMng->SpawnEffect(&data);
		}
		else {
			//位置が変わったら(移動したら)
			if (after[0].pos.x != after[1].pos.x || after[0].pos.y != after[1].pos.y) {
				after[0].isActive = true; //有効に.
			}
		}
	}
}

//残像描画.
void Player::DrawAfterImage()
{
	//残像処理.
	for (int i = 0; i < PLAYER_AFT_IMG_NUM; i++)
	{
		if (!after[i].isActive) { continue; }

		if (hit.pos.x != after[i].pos.x || hit.pos.y != after[i].pos.y) {
			//透明度の計算.
			float alpha = (float)i/PLAYER_AFT_IMG_NUM;
			//透明度反映.
			SetDrawBlendModeKR(BlendModeID::Add, 255*(1-alpha));

			Circle cir = { after[i].pos, PLAYER_SIZE, {} };
			//反射カラー.
			if (mode == Player_Reflect ||
				mode == Player_SuperReflect
			){
				cir.color = COLOR_PLY_AFT_REF;
			}
			//通常カラー.
			else
			{
				cir.color = COLOR_PLY_AFT_NOR;
			}

			DrawCircleKR(&cir, false, true);
		}
	}

	//描画モードリセット.
	ResetDrawBlendMode();
}

/*
//ダッシュエフェクト生成.
void Player::CreateDashEffect(DBL_XY pos)
{
	DashEffect* effect = &dashEffects[dashEffectIndex];

	effect->pos = pos;
	effect->scale = 1.0f;
	effect->alpha = 255.0f;
	effect->timer = 30;  // 30フレーム表示
	effect->active = true;

	// 次のインデックスに移動（循環）
	dashEffectIndex = (dashEffectIndex + 1) % PLAYER_DASH_EFFECT_MAX;
}

//ダッシュエフェクト更新.
void Player::UpdateDashEffects()
{
	for (int i = 0; i < PLAYER_DASH_EFFECT_MAX; i++) {
		if (dashEffects[i].active) {
			dashEffects[i].timer--;
			dashEffects[i].scale += 0.1f; // 拡大速度を少し遅く
			dashEffects[i].alpha -= 6.0f; // フェードアウト速度を少し遅く

			//タイマーが0 or 透明度が0以下になったら.
			if (dashEffects[i].timer <= 0 || dashEffects[i].alpha <= 0) {
				dashEffects[i].active = false; //非アクティブに.
			}
		}
	}
}

//ダッシュエフェクト描画.
void Player::DrawDashEffects()
{
	for (int i = 0; i < PLAYER_DASH_EFFECT_MAX; i++) {
		if (dashEffects[i].active) {

			DashEffect* effect = &dashEffects[i];

			// 点滅効果の計算（2フレームごとに点滅）
			bool isFlashOn = ((effect->timer / 2) % 2) == 0;
			if (!isFlashOn) continue;  // 点滅のOFFフレームなら描画しない

			// エフェクトのサイズ計算
			int baseSize = (int)(PLAYER_SIZE * effect->scale);
			int alpha = (int)max(0, min(255, effect->alpha));

			// アルファが0以下なら描画しない
			if (alpha <= 0) continue;

			// 点滅による輝度変化（強めの点滅）
			float flashIntensity = (effect->timer % 4 < 2) ? 1.5f : 0.8f;
			alpha = (int)(alpha * flashIntensity);
			alpha = Calc::ClampNum(alpha, 0, 255); //0～255の範囲に収める.

			// アルファブレンドモード設定（エフェクトごとに設定）
			SetDrawBlendModeKR(BlendModeID::Alpha, alpha);

			// 四角い波紋を描画
			for (int wave = 0; wave < 3; wave++) {
				int waveSize = baseSize + wave * 8; // 各波紋のサイズ
				int waveAlpha = alpha - wave * 50;  // 外側ほど薄く

				if (waveAlpha > 0) {
					// より明るいピンク色（点滅効果付き）
					UINT waveColor = GetColor(
						min(255, (int)(waveAlpha * 2 * flashIntensity)),
						waveAlpha * 80 / 255,
						min(255, (int)(waveAlpha * 150 / 255))
					);

					// 四角い枠線で波紋を描画（太い線）
					Box waveBox = {
						effect->pos,
						{ (double)waveSize, (double)waveSize },
						waveColor
					};

					// 枠線を太くするため複数回描画
					for (int thickness = 0; thickness < 2; thickness++) {
						Box thickBox = {
							{ effect->pos.x - thickness, effect->pos.y - thickness },
							{ (double)(waveSize + thickness * 2), (double)(waveSize + thickness * 2) },
							waveColor
						};
						DrawBoxKR(&thickBox, Anchor::Mid, false, true);
					}
				}
			}

			// 中央の四角い光点（点滅で色と大きさが変化）
			int centerSize = (int)(12 * flashIntensity);
			UINT centerColor = GetColor(
				min(255, (int)(255 * flashIntensity)),
				min(255, (int)(150 * flashIntensity)),
				min(255, (int)(255 * flashIntensity))
			);

			Box centerBox = {
				effect->pos,
				{ (double)centerSize, (double)centerSize },
				centerColor
			};
			DrawBoxKR(&centerBox, Anchor::Mid, false, true);

			// 描画モードリセット
			ResetDrawBlendMode();
		}
	}
}
*/