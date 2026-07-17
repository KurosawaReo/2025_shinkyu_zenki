/*
   - Player.cpp -
   プレイヤー管理.
*/
#include "Player.h"

//依存関係.
#include "LaserManager.h"
#include "Obst_NormalLaser.h"
#include "Stage_Tutorial.h"
#include "GameManager.h"
#include "GameData.h"

#include "KrLib_Dx/KR_ManagerInsts.h"
#include "KrLib_Dx/KR_TimerMng.h"
//参照.
static GameData*      gameData;
static GameManager*   gameMng;
static EffectManager* effectMng;
static TutorialStage* tutorialStg;
//参照(KRライブラリ)
static SoundMng*      soundMng;
static InputMng*      inputMng;

// ▼*--=<[ Player ]>=--*▼ //

//初期化(一回のみ行う)
void Player::Init()
{
	//参照取得.
	gameData    = ManagerInsts::Get<GameData>();
	gameMng     = ManagerInsts::Get<GameManager>();
	effectMng   = ManagerInsts::Get<EffectManager>();
	tutorialStg = ManagerInsts::Get<TutorialStage>();
	soundMng    = ManagerInsts::Get<SoundMng>();
	inputMng    = ManagerInsts::Get<InputMng>();

	isDebug = false;
}

//リセット(何回でも行う)
void Player::Reset()
{
	//自動実行設定.
	SetAutoExeMode(MngAutoExe::Stop);

	hit        = { { WINDOW_WID / 2, WINDOW_HEI / 2 + 200 }, PLAYER_SIZE, {}, {} };
	mode       = Player_Normal;
	afterCntr  = 1;
	isMoveAble = true;
	active     = true;

	//初期速度.
	velocity = {0,0};
	//最後の移動方向(上方向にしておく)
	lastInputVec = {0, -1};

	// ダッシュ関連の初期化.
	isDashing    = false;
	dashTimer    = 0;
	dashCooldown = 0;

	//ダッシュ関係.
	dashEndEffectTimer = 0;
	isDashEndEffect = false;

	//残像配列のリセット.
	for (int i = 0; i < _countof(after); i++) {
		after[i].pos      = hit.pos; //初期位置と同じ.
		after[i].isActive = false;
	}
}

//更新.
void Player::Update()
{
#if defined _DEBUG //Releaseでは入れない.
	//無敵モード.
	if (inputMng->IsPushKeyTime(KeyID::M) == 1) {
		isDebug = !isDebug;
	}
#endif

	//有効なら.
	if (active) {

		//画像回転.
		imgRot += (1.0 + velocity.Dist()*0.5) * gameData->speedRate;

		UpdateAfterImage();
		UpdateDash();
		PlayerMove();
	}
}

//描画.
void Player::Draw()
{
#if defined _DEBUG //Releaseでは入れない.
	//無敵モード表示.
	if (isDebug) {
		DrawStr str(_T("[Debug] 無敵モード"), {WINDOW_WID/2, WINDOW_HEI/2+300}, COLOR_PLY_DEBUG);
		str.Draw(Anchor::Mid, gameData->fonts["size26"].GetFont());
	}
#endif

	//有効なら.
	if (active) {
		DrawAfterImage();

		const float size  = 0.17f;
		const float size2 = 0.05f;

		//プレイヤー描画.
		if (mode == Player_ItemReflect ||
			mode == Player_ItemReflectSuper
		){
			//ダッシュ演出.
			if (isDashing) {
				DrawImgMng::Get(_T("player_light_ref"))->DrawExtend(hit.pos, { size2, size2 }, Anchor::Mid, true, true);
			}
			//反射モードの画像.
			DrawImgMng::Get(_T("player_ref"))->DrawRota(hit.pos, size, imgRot, {0, 0}, true, true);
		}
		else {
			//ダッシュ演出.
			if (isDashing) {
				DrawImgMng::Get(_T("player_light_nor"))->DrawExtend(hit.pos, { size2, size2 }, Anchor::Mid, true, true);
			}
			//通常モードの画像.
			DrawImgMng::Get(_T("player_nor"))->DrawRota(hit.pos, size, imgRot, {0, 0}, true, true);
		}

		//チュートリアル用.
		if (gameData->stage == Stage_Tutorial) {
			DrawStr str(_T("プレイヤー"), hit.pos.ToInt() + INT_XY(0, -35), 0xFFFFFF );
			str.Draw();
		}
	}
}

//ダッシュ処理.
void Player::UpdateDash()
{
	//ダッシュクールダウン減少.
	if (dashCooldown > 0){
		dashCooldown -= 1 * gameData->speedRate;
	}

	//ダッシュ中なら.
	if (isDashing)
	{
		dashTimer -= 1 * gameData->speedRate;
		//ダッシュ時間切れ.
		if (dashTimer <= 0)
		{
			/*if (mode == Player_DashReflect)
			{
				mode = Player_Normal;
			}*/
			isDashing = false; //ダッシュ終了.
		}
	}
	//ダッシュしてないなら.
	else
	{
		if (dashCooldown <= 0)
		{
			bool dashkey = inputMng->IsPushActionTime(_T("PlayerDash")) == 1;
			//ダッシュ開始.
			if (dashkey)
			{
				//ダッシュ音再生.
				if (auto i = soundMng->Get(_T("PlayerDash"))) {
					i->Play(false, 60); //再生.
				}
				dashTimer    = PLAYER_DASH_DURATION;
				dashCooldown = PLAYER_DASH_COOLDOWN;
				isDashing    = true;

				//ダッシュ反射開始.
				if (mode == Player_Normal)
				{
					mode = Player_DashReflect;
				}
				//ダッシュ反射終了(遅延実行)
				ManagerInsts::Get<TimerMng>()->ReservExe(
					PLAYER_DASH_REFLECT_TIME, [&]() {
						//戻す.
						if (mode == Player_DashReflect)
						{
							mode = Player_Normal;
						}
					}
				);

				//チュートリアルなら.
				if (gameData->stage == Stage_Tutorial) {
					tutorialStg->SetPlayerDash(true);
				}

			}
		}
	}
}

//移動処理(斜め対応)
void Player::PlayerMove()
{
	float speed = PLAYER_MOVE_SPEED;

	//移動可能なら.
	if (isMoveAble) {

		//目標速度.
		DBL_XY targetVel{};
		//入力操作.
		DBL_XY input = inputMng->GetKey4Dir() + inputMng->GetPadStick();
		//入力があれば更新.
		if (input.x != 0 || input.y != 0) {
			lastInputVec = input;
		}

		//ダッシュ中なら.
		if (isDashing) {
			//段々減速.
			const double rate = Calc::AnimEase(EaseType::OutQuad, dashTimer / PLAYER_DASH_DURATION);
			//速度変化.
			speed *= _flt(1.0 + PLAYER_DASH_SPEED * rate);
			//目標速度変更.
			targetVel = lastInputVec * speed;
		}
		else {
			//目標速度変更.
		    targetVel = input * speed;
		}

		//Lerp速度.
		const double moveLerp = PLAYER_MOVE_LERP_SPEED;
		//Lerpで目標速度に近づける.
		velocity.x += (targetVel.x - velocity.x) * moveLerp;
		velocity.y += (targetVel.y - velocity.y) * moveLerp;
		//誤差は無視.
		if (fabs(velocity.x) < 0.01f) velocity.x = 0;
		if (fabs(velocity.y) < 0.01f) velocity.y = 0;

		//移動.
		hit.pos += velocity * gameData->speedRate;
		//移動限界.
		Calc::FixPosInArea(&hit.pos, { PLAYER_SIZE * 2, PLAYER_SIZE * 2 }, {0, 0, WINDOW_WID-1, WINDOW_HEI-1});
	}
}

//死亡処理.
void Player::PlayerDeath() {

	//デバッグモード中は無敵.
	if (isDebug) { return; }
	//死亡済なら中断.
	if (!active) { return; }

	//サウンド.
	if (auto i = soundMng->Get(_T("PlayerDeath"))) {
		i->Play(false, 80); //再生.
	}
	//エフェクト.
	EffectData data{};
	data.type = Effect_PlayerDeath;
	data.pos  = hit.pos;
	effectMng->SpawnEffect(&data);

	gameMng->GameOver(); //ゲーム終了.
	
	isDashing    = false;
	dashTimer    = 0;
    dashCooldown = 0;
	active       = false;
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
	afterCntr -= gameData->speedRate;

	//残像を残すタイミングになったら(基本は毎フレーム)
	if (afterCntr <= 0) {
		afterCntr = 1;

		//残像データを後ろにずらす.
		for (int i = PLAYER_AFT_IMG_NUM - 1; i > 0; i--)
		{
			after[i] = after[i-1];
		}

		//一旦無効にする.
		after[0].isActive = false;

		//ある程度移動したら.
		if (fabs(hit.pos.x - after[1].pos.x) >= 0.5 ||
			fabs(hit.pos.y - after[1].pos.y) >= 0.5
		){
			//1フレーム目の情報登録.
			after[0].pos      = hit.pos;                                     //プレイヤー座標.
			after[0].ang      = Calc::FacingAng(after[0].pos, after[1].pos); //移動方向.
			after[0].isDash   = isDashing;                                   //ダッシュ中ならダッシュエフェクトに.
			after[0].isActive = true;                                        //残像を出す.
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

			float anim = (float)i/PLAYER_AFT_IMG_NUM; //アニメーション値.

			//描画.
			DrawMode::Exe(
				DrawModeID::None, DrawBlendModeID::Alpha, _int(255 * (1 - anim)),
				[&]() {

					MY_COLOR color;

					//ダッシュエフェクト.
					if (after[i].isDash) {
						//三角形データ.
						DBL_XY   pos1 = after[i].pos + Calc::AngToVector(after[i].ang) * (30 * (1 - anim));
						DBL_XY   pos2 = after[i].pos + Calc::AngToVector(after[i].ang + 90) * (20 * (1 - anim));
						DBL_XY   pos3 = after[i].pos + Calc::AngToVector(after[i].ang - 90) * (20 * (1 - anim));
						GradLine line;
						//反射カラー.
						if (mode == Player_ItemReflect ||
							mode == Player_ItemReflectSuper
							) {
							line.AddPoint(pos2, { 255,   0, 255, _int_r(255 * (1 - anim)) });
							line.AddPoint(pos1, { 100,   0, 100, _int_r(255 * (1 - anim)) });
							line.AddPoint(pos3, { 255,   0, 255, _int_r(255 * (1 - anim)) });
						}
						//通常カラー.
						else
						{
							line.AddPoint(pos2, { 255, 255, 255, _int_r(255 * (1 - anim)) });
							line.AddPoint(pos1, { 100, 100, 100, _int_r(255 * (1 - anim)) });
							line.AddPoint(pos3, { 255, 255, 255, _int_r(255 * (1 - anim)) });
						}
						line.Draw();
					}
					//通常エフェクト.
					else {
						//反射カラー.
						if (mode == Player_ItemReflect ||
							mode == Player_ItemReflectSuper
							) {
							color = COLOR_PLY_AFT_REF;
						}
						//通常カラー.
						else
						{
							color = COLOR_PLY_AFT_NOR;
						}
						//円描画.
						Circle cir = { after[i].pos, PLAYER_SIZE, color, 1.0f };
						DrawCircleKR(cir, Anchor::Mid, false, true);
					}
				}
			);
		}
	}
}