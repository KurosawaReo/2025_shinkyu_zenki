/*
   - Player.cpp -
   プレイヤー管理.
*/
#include "GameManager.h"
#include "Obstacle4main.h"

#include "Player.h"

//初期化(一回のみ行う)
void Player::Init(GameData* _data, EffectManager* _effectMng)
{
	p_data = _data;
	p_effectMng = _effectMng;

	isDebug = FALSE;  // デバッグフラグの初期化を追加
}
//リセット(何回でも行う)
void Player::Reset(DBL_XY _pos, BOOL _active)
{
	hit = { _pos, PLAYER_HIT_R, {} };
	active = _active;
	isReflect = false;
	afterCntr = 1;  // afterCntrの初期化を追加

	//座標配列のリセット.
	for (int i = 0; i < _countof(afterPos); i++) {
		afterPos[i] = _pos;
	}
	// 反射エフェクト初期化を追加
	reflectEffectIndex = 0;
	for (int i = 0; i < MAX_REFLECT_EFFECTS; i++) {
		reflectEffects[i].active = FALSE;
		reflectEffects[i].timer = 0;
		reflectEffects[i].alpha = 0.0f;
		reflectEffects[i].scale = 1.0f;
		reflectEffects[i].pos = _pos;
	}
}
//更新.
void Player::Update()
{
	InputST* input = InputST::GetPtr();

	//デバッグモード切り替え.
	if (input->IsPushKeyTime(KEY_M) == 1) {
		isDebug = !isDebug;
	}

	//テスト用：Eキーで反射エフェクトを生成
	if (input->IsPushKeyTime(KEY_E) == 1) {
		CreateReflectEffect(hit.pos);
	}

	//有効なら.
	if (active) {
		UpdateAfterImage();
		UpdateReflectEffects();
		PlayerMove();
	}
}
//描画.
void Player::Draw()
{
	//デバッグ表示.
	if (isDebug) {
		DrawString(0, 430, _T("[Debug] 無敵モード"), 0xFFFFFF);

		// エフェクトのデバッグ情報表示
		for (int i = 0; i < MAX_REFLECT_EFFECTS; i++) {
			if (reflectEffects[i].active) {
				TCHAR debugStr[128];
				_stprintf_s(debugStr, _T("Effect[%d]: timer=%d, alpha=%.1f, scale=%.1f"),
					i, reflectEffects[i].timer, reflectEffects[i].alpha, reflectEffects[i].scale);
				DrawString(0, 450 + i * 20, debugStr, 0xFFFFFF);
			}
		}
	}

	//有効なら.
	if (active) {
		DrawAfterImage();
		DrawReflectEffects();  // エフェクトを先に描画

		//四角形.
		Box box1 = { hit.pos, { PLAYER_SIZE,   PLAYER_SIZE   }, 0xFFFFFF };
		Box box2 = { hit.pos, { PLAYER_SIZE - 2, PLAYER_SIZE - 2 }, 0xFFFFFF };

		//反射モード中の色.
		if (IsReflectionMode())
		{
			box1.clr = box2.clr = COLOR_PLY_REFLECT;
		}
		//デバッグモード中.
		if (isDebug) {
			box1.clr = box2.clr = COLOR_PLY_DEBUG;
		}

		DrawBoxST(&box1, TRUE, FALSE);
		DrawBoxST(&box2, TRUE, FALSE);
	}
}

//残像更新.
void Player::UpdateAfterImage()
{
	afterCntr -= (p_data->isSlow) ? SLOW_MODE_SPEED : 1;

	//残像を残すタイミングになったら(基本は毎フレーム)
	if (afterCntr <= 0) {
		afterCntr = 1;

		//残像データを後ろにずらす.
		for (int i = PLAYER_AFT_IMG_NUM - 1; i > 0; i--)
		{
			afterPos[i] = afterPos[i - 1];
		}
		afterPos[0] = hit.pos; //プレイヤー座標を1フレーム目に記録.
	}
}

//残像描画.
void Player::DrawAfterImage()
{
	//残像処理.
	for (int i = 0; i < PLAYER_AFT_IMG_NUM; i++)
	{
		//透明度の計算.
		float alpha = (float)i/PLAYER_AFT_IMG_NUM;
		//透明度反映.
		SetDrawBlendModeST(MODE_ADD, 255*(1-alpha));

		Box box = { afterPos[i], {PLAYER_SIZE, PLAYER_SIZE}, {} };
		//反射カラー.
		if (IsReflectionMode())
		{
			box.clr = COLOR_PLY_AFT_REF;
		}
		//通常カラー.
		else
		{
			box.clr = COLOR_PLY_AFT_NOR;
		}

		DrawBoxST(&box, TRUE, FALSE);
	}

	//描画モードリセット.
	ResetDrawBlendMode();
}

//移動処理(斜め対応)
void Player::PlayerMove()
{
	InputST* input = InputST::GetPtr();

	//移動する.
	if (p_data->isSlow) {
		input->InputKey4Dir (&hit.pos, PLAYER_MOVE_SPEED * SLOW_MODE_SPEED);
		input->InputPadStick(&hit.pos, PLAYER_MOVE_SPEED * SLOW_MODE_SPEED);
	}
	else {
		input->InputKey4Dir (&hit.pos, PLAYER_MOVE_SPEED);
		input->InputPadStick(&hit.pos, PLAYER_MOVE_SPEED);
	}
	//移動限界.
	FixPosInArea(&hit.pos, { PLAYER_SIZE, PLAYER_SIZE }, 0, 0, WINDOW_WID, WINDOW_HEI);
}

// 反射エフェクト生成
void Player::CreateReflectEffect(DBL_XY pos)
{
	ReflectEffect* effect = &reflectEffects[reflectEffectIndex];

	effect->pos = pos;
	effect->scale = 1.0f;
	effect->alpha = 255.0f;
	effect->timer = 30;  // 30フレーム表示
	effect->active = TRUE;

	// 次のインデックスに移動（循環）
	reflectEffectIndex = (reflectEffectIndex + 1) % MAX_REFLECT_EFFECTS;
}

// 反射エフェクト更新
void Player::UpdateReflectEffects()
{
	for (int i = 0; i < MAX_REFLECT_EFFECTS; i++) {
		if (reflectEffects[i].active) {
			reflectEffects[i].timer--;
			reflectEffects[i].scale += 0.1f;      // 拡大速度を少し遅く
			reflectEffects[i].alpha -= 6.0f;     // フェードアウト速度を少し遅く

			// タイマーが0になったか透明度が0以下になったら非アクティブ
			if (reflectEffects[i].timer <= 0 || reflectEffects[i].alpha <= 0) {
				reflectEffects[i].active = FALSE;
			}
		}
	}
}

// 反射エフェクト描画
void Player::DrawReflectEffects()
{
	for (int i = 0; i < MAX_REFLECT_EFFECTS; i++) {
		if (reflectEffects[i].active) {
			ReflectEffect* effect = &reflectEffects[i];

			// 点滅効果の計算（2フレームごとに点滅）
			BOOL isFlashOn = ((effect->timer / 2) % 2) == 0;
			if (!isFlashOn) continue;  // 点滅のOFFフレームなら描画しない

			// エフェクトのサイズ計算
			int baseSize = (int)(PLAYER_SIZE * effect->scale);
			int alpha = (int)max(0, min(255, effect->alpha));

			// アルファが0以下なら描画しない
			if (alpha <= 0) continue;

			// 点滅による輝度変化（強めの点滅）
			float flashIntensity = (effect->timer % 4 < 2) ? 1.5f : 0.8f;
			alpha = (int)(alpha * flashIntensity);
			alpha = min(255, max(0, alpha));

			// ピンク色の設定（より明るく、点滅で変化）
			UINT color = GetColor(
				min(255, (int)(alpha * flashIntensity)),
				alpha * 80 / 255,
				min(255, alpha * 150 / 255)
			);

			// アルファブレンドモード設定（エフェクトごとに設定）
			SetDrawBlendModeST(MODE_ALPHA, alpha);

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
						DrawBoxST(&thickBox, TRUE, FALSE);
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
			DrawBoxST(&centerBox, TRUE, FALSE);

			// 描画モードリセット
			ResetDrawBlendMode();
		}
	}
}

//反射モードかどうか.
BOOL Player::IsReflectionMode() const
{
	return isReflect;
}
//反射モード設定.
void Player::SetReflectionMode(BOOL tf)
{
	isReflect = tf;
}

//死亡処理.
void Player::PlayerDeath() {

	//デバッグモード中は無敵.
	if (isDebug) { return; }

	//サウンド.
	SoundST* sound = SoundST::GetPtr();
	sound->Play(_T("PlayerDeath"), FALSE, 80);
	//エフェクト.
	EffectData data{};
	data.type = Effect_PlayerDeath;
	data.pos  = hit.pos;
	p_effectMng->SpawnEffect(&data);
	//GamaManagerの関数実行(includeだけすれば使える)
	GameManager::GetPtr()->GameEnd(); //ゲーム終了.
	
	active = FALSE;
}