/*
   - Player.cpp -
   プレイヤー管理.
*/
#include "GameManager.h"
#include "Player.h"
#include "Obstacle4main.h"

//初期化(一回のみ行う)
void Player::Init(GameData* _data)
{
	p_data = _data;
}
//リセット(何回でも行う)
void Player::Reset(DBL_XY _pos, BOOL _active) 
{
	hit    = {_pos, PLAYER_HIT_R, 0x000000};
	active = _active;
}
//更新.
void Player::Update()
{
	InputST* input = InputST::GetPtr();

	//デバッグモード切り替え.
	if (input->IsPushKeyTime(KEY_M) == 1) {
		isDebug = !isDebug;
	}

	//反射モードの状態をコンソールに出力（デバッグ用）
	if (input->IsPushKey(KEY_V)) {
//		printf("Vキー押下中, クールダウン: %.1f\n", reflectionCooldown);
	}

	if (reflectionCooldown > 0)
	{
		reflectionCooldown -= (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
	}
	//有効なら.
	if (active) {
		PlayerMove();
	}
}
//描画.
void Player::Draw()
{
	//デバッグ表示.
	if (isDebug) {
		DrawString(0, 430, _T("[Debug] 無敵モード"), 0xFFFFFF);
	}

	// 反射モード表示.
	if (IsReflectionMode())
	{
		DrawString(0, 430, _T("反射モード ON"), 0x00FF00);
	}

	// クールダウン表示.
	if (reflectionCooldown > 0) {
		DrawString(0, 470, _T("反射クールダウン中..."), 0xFF0000);
	}

	//有効なら.
	if (active) {
		//四角形.
		Box box1 = { hit.pos, { PLAYER_SIZE,   PLAYER_SIZE   }, 0xFFFFFF };
		Box box2 = { hit.pos, { PLAYER_SIZE-2, PLAYER_SIZE-2 }, 0xA0A0A0 };

		//反射モード中は青色に変更.
		if (IsReflectionMode())
		{
			box1.clr = box2.clr = GetColor(255, 155, 255);//青色.
		}

		//デバッグモード中.
		if (isDebug) {
			box1.clr = box2.clr = GetColor(255, 150, 150); //赤色.
		}

		DrawBoxST(&box1, TRUE, FALSE);
		DrawBoxST(&box2, TRUE, FALSE);
	}
}

//移動処理(斜め対応)
void Player::PlayerMove()
{
	InputST* input = InputST::GetPtr();

	//移動する.
	if (p_data->isSlow) {
		input->InputKey4Dir(&hit.pos, PLAYER_MOVE_SPEED * SLOW_MODE_SPEED);
		input->InputPad4Dir(&hit.pos, PLAYER_MOVE_SPEED * SLOW_MODE_SPEED); //コントローラ移動(仮)
	}
	else {
		input->InputKey4Dir(&hit.pos, PLAYER_MOVE_SPEED);
		input->InputPad4Dir(&hit.pos, PLAYER_MOVE_SPEED); //コントローラ移動(仮)
	}
	//移動限界.
	FixPosInArea(&hit.pos, { PLAYER_SIZE, PLAYER_SIZE }, 0, 0, WINDOW_WID, WINDOW_HEI);
}

BOOL Player::IsReflectionMode()
{
	InputST* input = InputST::GetPtr(); //input情報を取得.

	int vKeyPressed = input->IsPushKey(KEY_V); //Vキーを押していれば.
	int cooldownOK = (reflectionCooldown <= 0);

	// デバッグ出力.
	//DrawFormatString(0, 300, 0xFF0000, _T("反射モード確認: Vキー=%d"), vKeyPressed);
	//DrawFormatString(0, 320, 0xFF0000, _T("クールダウン=%.1f"), reflectionCooldown);
	//DrawFormatString(0, 340, 0xFF0000, _T("結果=%d"), (vKeyPressed & cooldownOK));

	return vKeyPressed && cooldownOK;
}

void Player::UseReflection()
{
	reflectionCooldown = PLAYER_REF_COOLDOWN; //クールダウン開始.
}
float Player::GetReflectionCooldown()
{
	return reflectionCooldown; //クールダウン時間を返す.
}


//死亡処理.
void Player::PlayerDeath() {

	//デバッグモード中は無敵.
	if (isDebug) { return; }

	active = FALSE;
	//GamaManagerの関数実行(includeだけすれば使える)
	GameManager::GetPtr()->GameEnd(); //ゲーム終了.
}
