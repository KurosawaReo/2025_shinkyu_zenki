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

	// 感性関連.
	velocity = {0,0};

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
		imgRot += 1.5 * gameData->speedRate; //画像回転.

		UpdateAfterImage();
		UpdateDash();
		PlayerMove();
	}
}
//描画.
void Player::Draw()
{
#if defined _DEBUG //Releaseでは入れない.
	//デバッグ表示.
	if (isDebug) {
		DrawStr str(_T("[Debug] 無敵モード"), {WINDOW_WID/2, WINDOW_HEI/2+300}, COLOR_PLY_DEBUG);
		str.Draw(Anchor::Mid, gameData->fonts["size26"].GetFont());
	}
#endif

	//有効なら.
	if (active) {
		DrawAfterImage();

		const float size = 0.17f;

		//プレイヤー描画.
		if (mode == Player_Reflect ||
			mode == Player_SuperReflect
		){
			//ダッシュ演出.
			if (isDashing) {
				DrawImgMng::Get("player_light_ref")->DrawExtend(hit.pos, {0.05, 0.05}, Anchor::Mid, true, true);
			}
			//反射モードの画像.
			DrawImgMng::Get("player_ref")->DrawRota(hit.pos, size, imgRot, {0, 0}, true, true);
		}
		else {
			//ダッシュ演出.
			if (isDashing) {
				DrawImgMng::Get("player_light_nor")->DrawExtend(hit.pos, {0.05, 0.05}, Anchor::Mid, true, true);
			}
			//通常モードの画像.
			DrawImgMng::Get("player_nor")->DrawRota(hit.pos, size, imgRot, {0, 0}, true, true);
		}

		//チュートリアル用.
		if (gameData->stage == Stage_Tutorial) {
			DrawStr str(_T("プレイヤー"), hit.pos.Add(0, -35).ToInt(), 0xFFFFFF );
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
			isDashing = false; //ダッシュ終了.
		}
	}
	//ダッシュしてないなら.
	else
	{
		if (dashCooldown <= 0)
		{
			bool dashkey = inputMng->IsPushActionTime("PlayerDash") == 1;
			//ダッシュ開始.
			if (dashkey)
			{
				//ダッシュ音追加..
				if (auto i = soundMng->Get("PlayerDash")) {
					i->Play(false, 60); //再生.
				}
				dashTimer    = PLAYER_DASH_DURATION;
				dashCooldown = PLAYER_DASH_COOLDOWN;
				isDashing    = true;

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
	float speed = PLAYER_MOVE_SPEED * gameData->speedRate;

	//移動可能なら.
	if (isMoveAble) {
		//ダッシュ中は加速.
		if (isDashing)
		{
			//残り時間に応じて段々減速.
			speed *= 1.0f + _flt(PLAYER_DASH_SPEED * Calc::AnimEase(EaseType::OutQuad, dashTimer/PLAYER_DASH_DURATION));
		}

		DBL_XY input = inputMng->GetKey4Dir() + inputMng->GetPadStick();

		DBL_XY targetVel = input * speed;

		const float moveLerp = PLAYER_MOVE_LERP_SPEED;

		velocity.x += (targetVel.x - velocity.x) * moveLerp;
		velocity.y += (targetVel.y - velocity.y) * moveLerp;

		if (fabs(velocity.x) < 0.01f) velocity.x = 0;
		if (fabs(velocity.y) < 0.01f) velocity.y = 0;

		hit.pos += velocity * gameData->speedRate;

		//移動限界.
		Calc::FixPosInArea(&hit.pos, { PLAYER_SIZE * 2, PLAYER_SIZE * 2 }, {0, 0, WINDOW_WID-1, WINDOW_HEI-1});
	}
}

//死亡処理.
void Player::PlayerDeath() {

	//デバッグモード中は無敵.
	if (isDebug) { return; }

	//まだ生存してるなら.
	if (active) {

		//サウンド.
		if (auto i = soundMng->Get("PlayerDeath")) {
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
		//1フレーム目の情報登録.
		after[0].pos      = hit.pos;                                         //プレイヤー座標.
		after[0].ang      = Calc::FacingAng(after[0].pos, after[1].pos); //移動方向.
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

			float anim = (float)i/PLAYER_AFT_IMG_NUM; //アニメーション値.
			{
				DrawMode _(DrawModeID::None, DrawBlendModeID::Alpha, 255 * (1 - anim));
	
				MY_COLOR color;

				//ダッシュエフェクト.
				if (after[i].isDash) {
					//三角形データ.
					DBL_XY   pos1 = after[i].pos + Calc::AngToVector(after[i].ang)    * (30 * (1-anim));
					DBL_XY   pos2 = after[i].pos + Calc::AngToVector(after[i].ang+90) * (20 * (1-anim));
					DBL_XY   pos3 = after[i].pos + Calc::AngToVector(after[i].ang-90) * (20 * (1-anim));
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
					Circle cir = { after[i].pos, PLAYER_SIZE, color, 1.0f };
					DrawCircleKR(cir, Anchor::Mid, false, true);
				}
			}
		}
	}
}