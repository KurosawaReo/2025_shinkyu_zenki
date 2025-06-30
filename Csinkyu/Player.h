/*
   - Player.h -
   プレイヤー管理.
*/
#pragma once


class Player
{
private:
	Circle hit{};       //プレイヤーの当たり判定円.
	int    graph{};     //画像データ.
	BOOL   active{};    //有効か.
	DBL_XY afterImagePos[AFTIMAGENUM];//残像位置の履歴.
	
	float  reflectionCooldown{}; //反射のクールダウン時間.

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
	void Init  (GameData*);
	void Reset (DBL_XY _pos, BOOL _active);
	void Update();
	void Draw  ();

	void PlayerMove();          //プレイヤー移動.
	void PlayerDeath();         //プレイヤー死亡.
	void PlayerFaterimage();        //プレイヤー残像.
	BOOL IsReflectionMode();    //反射モードかどうかを返す.
	void UseReflection();         //反射を使用.
	float GetReflectionCooldown();//クールダウン時間を持つ.
};