
/*
   - Player.cpp -
   プレイヤー管理.
*/
#include "GameManager.h"
#include "Obstacle4main.h"

#include "Player.h"

//初期化(一回のみ行う)
void Player::Init(GameData* _data)
{
	p_data = _data;
}
//リセット(何回でも行う)
void Player::Reset(DBL_XY _pos, BOOL _active) 
{
	hit       = {_pos, PLAYER_HIT_R, {} };
	active    = _active;
	isReflect = false;
}
//更新.
void Player::Update()
{
	InputST* input = InputST::GetPtr();

	//デバッグモード切り替え.
	if (input->IsPushKeyTime(KEY_M) == 1) {
		isDebug = !isDebug;
	}

	//有効なら.
	if (active) {
		UpdateAfterImage();
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

	//有効なら.
	if (active) {
		DrawAfterImage();
		//四角形.
		Box box1 = { hit.pos, { PLAYER_SIZE,   PLAYER_SIZE   }, 0xFFFFFF };
		Box box2 = { hit.pos, { PLAYER_SIZE-2, PLAYER_SIZE-2 }, 0xFFFFFF };

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
		for (int i = PLAYER_AFT_IMG_NUM-1; i > 0; i--)
		{
			afterPos[i] = afterPos[i - 1];
		}
		afterPos[0] = hit.pos; //プレイヤー座標を1フレーム目に記録.
	}
}

//残像描画.
void Player::DrawAfterImage()
{
	//描画モード変更.
	SetDrawBlendModeST(MODE_ADD, 255);

	//残像処理.
	for (int i = PLAYER_AFT_IMG_NUM - 1; i >= 0; i -= 1)
	{
		int  alpha  = 105 - 105*i/PLAYER_AFT_IMG_NUM;
		int  alpha2 =  50 -  50*i/PLAYER_AFT_IMG_NUM;
		UINT color  = GetColor(alpha, alpha, alpha);

		if (IsReflectionMode())
		{
			color = GetColor(alpha2*255/50, alpha2/2, alpha2*255/50);
		}
		else
		{
			color = GetColor(alpha, alpha, alpha);
		}

		Box box3 = { afterPos[i], {PLAYER_SIZE, PLAYER_SIZE}, color };
		DrawBoxST(&box3, TRUE, FALSE);
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

	active = FALSE;
	//GamaManagerの関数実行(includeだけすれば使える)
	GameManager::GetPtr()->GameEnd(); //ゲーム終了.
}