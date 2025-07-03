/*
   - Player.h -
   プレイヤー管理.
*/
#pragma once

//プレイヤーを囲うシールド.
struct PlayerShield
{
	
};

class Player
{
private:
	Circle hit{};       //プレイヤーの当たり判定円.
	BOOL   active{};    //有効か.

	float  afterCntr;					 //残像用時間カウンター.
	DBL_XY afterPos[PLAYER_AFT_IMG_NUM]; //残像位置の履歴.
	float  reflectionCooldown{};         //反射のクールダウン時間.

	GameData* p_data{}; //ゲームデータ.

	BOOL   isDebug{};   //デバッグ用.

public:

	//set.
	void    SetActive(BOOL _active) { active = _active; }
	//get. 
	DBL_XY  GetPos()   { return hit.pos; }
	BOOL    GetActive(){ return active; }
	Circle* GetHit()   { return &hit; }

	//その他.
	void  Init  (GameData*);
	void  Reset (DBL_XY _pos, BOOL _active);
	void  Update();
	void  Draw  ();

	void  PlayerMove();          //プレイヤー移動.
	void  PlayerDeath();         //プレイヤー死亡.

	void  UpdateAfterImage();	 //残像更新.
	void  DrawAfterImage();      //残像描画.

	BOOL  IsReflectionMode() const;			//反射モードかどうかを返す.
	float GetReflectionCooldown() const;	//クールダウン時間を持つ.
	void  UseReflection();					//反射を使用.
};