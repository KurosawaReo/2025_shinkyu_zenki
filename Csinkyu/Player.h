/*
   - Player.h -
   プレイヤー管理.
*/
#pragma once
#include "EffectManager.h"
#include "Global.h"

//エフェクトデータ.
struct AfterEffect
{
	DBL_XY pos;
	double ang;
	bool   isDash;   //ダッシュエフェクトにするか.
	bool   isActive;
};

//プレイヤーモード.
enum PlayerMode
{
	Player_Normal,           //通常モード.
	Player_ItemReflect,      //アイテム反射モード.
	Player_ItemReflectSuper, //アイテム反射モード強化版.
	Player_DashReflect,      //反射ダッシュ.
};

//プレイヤー.
class Player final : public ManagerBase
{
//▼ ===== 変数 ===== ▼.
private:
	PlayerMode mode{};			//モード.
	
	Circle     hit{};			//プレイヤーの当たり判定円.
	bool       active{};		//有効か.
	bool       isDebug{};		//デバッグ用.

	DBL_XY	   velocity{};		//移動速度.
	DBL_XY	   lastInputVec{};	//最後の入力方向.

	float      dashEndEffectTimer{};	//エフェクト残り時間.

	bool       isDashing{};			//ダッシュ中かどうか.
	bool       isDashReflect{};		//ダッシュ反射演出を出すか.
	bool       isDashEndEffect{};	//エフェクト発動フラグ.

	//残像.
	float          afterCntr{};	 		        //残像用時間カウンター.
	AfterEffect    after[PLAYER_AFT_IMG_NUM]{}; //残像位置の履歴.

	//ダッシュ.
	float          dashTimer{};        // ダッシュの残り時間.
	float          dashCooldown{};     // ダッシュのクールダウン.

	double         imgRot{};            //プレイヤーの画像角度.


//▼ ===== 関数 ===== ▼.
public:
	//コンストラクタ.
	Player(int order) : ManagerBase(order) {}

	//set.
	void       SetPos          (DBL_XY     _pos)    { hit.pos       = _pos;    }
	void       SetActive       (bool       _active) { active        = _active; }
	void       SetMode         (PlayerMode _mode)   { mode          = _mode;   } //モード設定.
	void       SetIsDashReflect(bool       _flag)   { isDashReflect = _flag;   }
	//get. 
	DBL_XY     GetPos()      const { return hit.pos; }
	bool       GetActive()   const { return active; }
	PlayerMode GetMode()     const { return mode; }
	Circle     GetHit()      const { return hit; }
	
	//移動したか.
	bool IsMoved() const { 
		return Calc::Dist(hit.pos, after[1].pos) > 0; //移動距離が0より大きければ.
	}

	bool GetIsDashing() const { return isDashing; }

	void Init  () override;
	void Reset () override;
	void Update() override;
	void Draw  () override;

	void UpdateDash();       //ダッシュ更新.

	void PlayerMove();       //プレイヤー移動.
	void PlayerDeath();      //プレイヤー死亡.
	void PlayerRevival();    //プレイヤー復活.

	void UpdateAfterImage(); //残像更新.
	void DrawAfterImage();   //残像描画.

	//void OnDashEnd();        //ダッシュ終了時エフェクト関数.


	//使用禁止.
	Player(const Player*) = delete;
	Player* operator=(const Player*) = delete;
};