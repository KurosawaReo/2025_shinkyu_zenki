/*
   - Player.cpp -
   プレイヤー管理.
*/
#include "Player.h"

//依存関係.
#include "LaserManager.h"
#include "Obst_NormalLaserMain.h"
#include "Stage_Tutorial.h"
#include "GameManager.h"
#include "GameData.h"
//参照.
static GameData&      gameData      = GameData::GetInst();
static EffectManager& effectMng = EffectManager::GetInst();

//初期化(一回のみ行う)
void Player::Init()
{
	isDebug = false;

	//画像読み込み.
	DrawImgMng::LoadFile(_T("Resources/Images/player_normal.png"),   "player_nor");
	DrawImgMng::LoadFile(_T("Resources/Images/player_reflect.png"),  "player_ref");
	DrawImgMng::LoadFile(_T("Resources/Images/light_color_nor.png"), "player_light_nor");
	DrawImgMng::LoadFile(_T("Resources/Images/light_color_ref.png"), "player_light_ref");
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
	if (InputMng::IsPushKeyTime(KeyID::M) == 1) {
		isDebug = !isDebug;
	}
#endif

	//有効なら.
	if (active) {
		imgRot += 1.5 * gameData.speedRate; //画像回転.

		UpdateAfterImage();
		UpdateDash();
		PlayerMove();
		
		//反射モード中.
		if (gameData.isReflectMode) {
			//敵のレーザーが近くにあれば.
			if (LaserManager::GetInst().IsExistEnemyLaser(hit.pos, SLOW_MODE_DIS_LEN)) {
				gameData.slowBufCntr = SLOW_MODE_BUF_F;
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
		str.Draw(Anchor::Mid, gameData.font1);
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
		if (gameData.stage == STAGE_TUTORIAL) {
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
		dashCooldown -= 1 * gameData.speedRate;
	}

	//ダッシュ中なら.
	if (isDashing)
	{
		dashTimer -= 1 * gameData.speedRate;
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
			bool dashkey = InputMng::IsPushActionTime("PlayerDash") == 1;
			//ダッシュ開始.
			if (dashkey)
			{
				dashTimer    = PLAYER_DASH_DURATION;
				dashCooldown = PLAYER_DASH_COOLDOWN;
				isDashing    = true;

				//チュートリアルなら.
				if (gameData.stage == STAGE_TUTORIAL) {
					TutorialStage::GetInst().SetPlayerDash(true);
				}
			}
		}
	}
}

//移動処理(斜め対応)
void Player::PlayerMove()
{
	float speed = PLAYER_MOVE_SPEED * gameData.speedRate;

	//移動可能なら.
	if (isMoveAble) {
		//ダッシュ中は加速.
		if (isDashing)
		{
			//残り時間に応じて段々減速.
			speed *= 1.0f + _flt(PLAYER_DASH_SPEED * Calc::AnimEaseOut(dashTimer/PLAYER_DASH_DURATION));
		}
		//移動.
		hit.pos += InputMng::GetKey4Dir()  * speed;
		hit.pos += InputMng::GetPadStick() * speed;
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
		if (auto i = SoundMng::Get("PlayerDeath")) {
			i->Play(false, 80); //再生.
		}
		//エフェクト.
		EffectData data{};
		data.type = Effect_PlayerDeath;
		data.pos  = hit.pos;
		effectMng.SpawnEffect(&data);
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
	afterCntr -= gameData.speedRate;

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
					DBL_XY   pos1 = after[i].pos + Calc::VectorDeg(after[i].ang)    * (30 * (1-anim));
					DBL_XY   pos2 = after[i].pos + Calc::VectorDeg(after[i].ang+90) * (20 * (1-anim));
					DBL_XY   pos3 = after[i].pos + Calc::VectorDeg(after[i].ang-90) * (20 * (1-anim));
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
					DrawCircleKR(cir, false, true);
				}
			}
		}
	}
}