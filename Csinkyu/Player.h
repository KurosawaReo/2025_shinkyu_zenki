/*
   - Player.h -
   プレイヤー管理.
*/
#pragma once
#include "EffectManager.h"

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
	Player_Normal,
	Player_Reflect,     //反射モード.
	Player_SuperReflect //反射モード強化版.
};

//プレイヤー.
class Player : public ManagerBase
{
//▼ ===== 実体 ===== ▼.
public:
	static Player& GetInst() {
		static Player inst; //自身のインスタンス.
		return inst;
	}

//▼ ===== 変数 ===== ▼.
private:
	PlayerMode     mode{};     //モード.
	
	Circle         hit{};      //プレイヤーの当たり判定円.
	bool           active{};   //有効か.
	bool           isDebug{};  //デバッグ用.

	//残像.
	float          afterCntr{};	 		        //残像用時間カウンター.
	AfterEffect    after[PLAYER_AFT_IMG_NUM]{}; //残像位置の履歴.

	//ダッシュ.
	bool           isDashing{};        // ダッシュ中かどうか.
	float          dashTimer{};        // ダッシュの残り時間.
	float          dashCooldown{};     // ダッシュのクールダウン.

	double         imgRot{};            //プレイヤーの画像角度.

	bool           isMoveAble{};     //移動可能かどうか.

//▼ ===== 関数 ===== ▼.
private:
	//コンストラクタ.
	Player() : ManagerBase(ORDER_PLAYER_MNG) {}

public:
	//set.
	void       SetPos       (DBL_XY     _pos)    { hit.pos    = _pos;    }
	void       SetActive    (bool       _active) { active     = _active; }
	void       SetMode      (PlayerMode _mode)   { mode       = _mode;   } //モード設定.
	void       SetIsMoveAble(bool       _flag)   { isMoveAble = _flag;   }
	//get. 
	DBL_XY     GetPos()      const { return hit.pos; }
	bool       GetActive()   const { return active; }
	PlayerMode GetMode()     const { return mode; }
	Circle     GetHit()      const { return hit; }
	
	//移動したか.
	double     IsMoved() const { 
		return Calc::Dist(hit.pos, after[1].pos) > 0; //移動距離が0より大きければ.
	}

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

	//使用禁止.
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
};