/*
   - Player.h -
   プレイヤー管理.
*/
#pragma once
#include "EffectManager.h"

//ダッシュエフェクト.
struct ReflectEffect
{
	DBL_XY pos;           // エフェクト位置
	float  scale;         // スケール
	float  alpha;         // 透明度
	int    timer;         // 表示時間
	BOOL   active;        // 有効フラグ
};

class Player
{
private:
	Circle hit{};       //プレイヤーの当たり判定円.
	BOOL   isReflect{}; //反射モードかどうか.
	BOOL   active{};    //有効か.

	float  afterCntr{};					   //残像用時間カウンター.
	DBL_XY afterPos[PLAYER_AFT_IMG_NUM]{}; //残像位置の履歴.

	GameData*      p_data{};      //ゲームデータ.
	EffectManager* p_effectMng{}; //エフェクト管理.

	BOOL   isDebug{};   //デバッグ用.

public:

	//set.
	void    SetActive(BOOL _active) { active = _active; }
	//get. 
	DBL_XY  GetPos()   { return hit.pos; }
	BOOL    GetActive(){ return active; }
	Circle* GetHit()   { return &hit; }
	static const int MAX_REFLECT_EFFECTS = 5;  // 最大エフェクト数
	ReflectEffect reflectEffects[MAX_REFLECT_EFFECTS]{};  // エフェクト配列
	int reflectEffectIndex{};  // 次に使用するエフェクトのインデックス

	//その他.
	void  Init  (GameData*, EffectManager*);
	void  Reset (DBL_XY _pos, BOOL _active);
	void  Update();
	void  Draw  ();

	void  PlayerMove();          //プレイヤー移動.
	void  PlayerDeath();         //プレイヤー死亡.

	void  UpdateAfterImage();	 //残像更新.
	void  DrawAfterImage();      //残像描画.

	BOOL  IsReflectionMode() const; //反射モードかどうかを返す.
	void  SetReflectionMode(BOOL);	//反射モード設定.

	void CreateReflectEffect(DBL_XY pos);
	void UpdateReflectEffects();
	void DrawReflectEffects();
};