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
		//1フレーム目の情報登録.
		after[0].pos      = hit.pos;                                         //プレイヤー座標.
		after[0].ang      = Calc::CalcFacingAng(after[0].pos, after[1].pos); //移動方向.
		after[0].isDash   = isDashing;                                       //ダッシュ中ならダッシュエフェクトに.
		after[0].isActive = false;                                           //一旦無効にする.
		//位置が変わったら(移動したら)
		if (after[0].pos.x != after[1].pos.x || after[0].pos.y != after[1].pos.y) {
			after[0].isActive = true; //有効に.
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
			//アニメーション値.
			float anim = (float)i/PLAYER_AFT_IMG_NUM;
			//透明度反映.
			SetDrawBlendModeKR(BlendModeID::Add, 255*(1-anim));

			MY_COLOR color;

			//ダッシュエフェクト.
			if (after[i].isDash) {
				//三角形データ.
				DBL_XY   pos1 = after[i].pos + Calc::CalcVectorDeg(after[i].ang)    * (30 * (1-anim));
				DBL_XY   pos2 = after[i].pos + Calc::CalcVectorDeg(after[i].ang+90) * (20 * (1-anim));
				DBL_XY   pos3 = after[i].pos + Calc::CalcVectorDeg(after[i].ang-90) * (20 * (1-anim));
				GradLine line;
				//反射カラー.
				if (mode == Player_Reflect ||
					mode == Player_SuperReflect
				){
					line.AddPoint(pos2, {255,   0, 255, _int_r(255*(1-anim))});
					line.AddPoint(pos1, {100,   0, 100, _int_r(255*(1-anim))});
					line.AddPoint(pos3, {255,   0, 255, _int_r(255*(1-anim))});
				}
				//通常カラー.
				else
				{
					line.AddPoint(pos2, {255, 255, 255, _int_r(255*(1-anim))});
					line.AddPoint(pos1, {100, 100, 100, _int_r(255*(1-anim))});
					line.AddPoint(pos3, {255, 255, 255, _int_r(255*(1-anim))});
				}
				line.Draw();
			}
			//通常エフェクト.
			else {
				//反射カラー.
				if (mode == Player_Reflect ||
					mode == Player_SuperReflect
				){
					color = COLOR_PLY_AFT_REF;
				}
				//通常カラー.
				else
				{
					color = COLOR_PLY_AFT_NOR;
				}
				//円描画.
				Circle cir = { after[i].pos, PLAYER_SIZE, color };
				DrawCircleKR(&cir, false, true);
			}
		}
	}

	//描画モードリセット.
	KR_Lib::ResetDrawBlendMode();
}