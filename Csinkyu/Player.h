/*
   - Player.h -
   プレイヤー管理.
*/
#pragma once
#include "EffectManager.h"

class GameData; //前方宣言.

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

//プレイヤー.[継承不可]
class Player final
{
//▼実体関係.
public:
	//実体取得用.
	static Player& GetInst() {
		static Player inst; //自身のインスタンス.
		return inst;
	}
	//使用禁止.
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
private:
	//constructor(新規作成をできなくする)
	Player(){}

//▼データ.
private:
	PlayerMode     mode{};     //モード.
	
	Circle         hit{};      //プレイヤーの当たり判定円.
	bool           active{};   //有効か.
	bool           isDebug{};  //デバッグ用.

	//残像.
	float          afterCntr{};	 		        //残像用時間カウンター.
	AfterEffect    after[PLAYER_AFT_IMG_NUM]{}; //残像位置の履歴.

	//ダッシュ.
	bool           isDashing;        // ダッシュ中かどうか.
	float          dashTimer;        // ダッシュの残り時間.
	float          dashCooldown;     // ダッシュのクールダウン.

	DrawImg        imgPlayer[2]{};      //プレイヤー画像.
	DrawImg        imgPlayerLight[2]{}; //プレイヤーの光る画像.
	double         imgRot{};            //プレイヤーの画像角度.

	bool           isMoveAble{};     //移動可能かどうか.

	GameData*      p_data{};      //ゲームデータ.
	EffectManager* p_effectMng{}; //エフェクト管理.
	InputMng*      p_input{};     //入力機能.

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
	//計測.
	double     GetMoveDist() const { 
		return Calc::CalcDist(hit.pos, after[1].pos); //移動した距離.
	}

	//その他.
	void Init  ();
	void Reset (DBL_XY _pos, bool _active);
	void Update();
	void Draw  ();

	void UpdateDash();       //ダッシュ更新.

	void PlayerMove();       //プレイヤー移動.
	void PlayerDeath();      //プレイヤー死亡.
	void PlayerRevival();    //プレイヤー復活.

	void UpdateAfterImage(); //残像更新.
	void DrawAfterImage();   //残像描画.
};