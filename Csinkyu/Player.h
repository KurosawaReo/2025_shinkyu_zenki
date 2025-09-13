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
	bool   active;        // 有効フラグ
};

//プレイヤーモード.
enum PlayerMode
{
	Player_Normal,
	Player_Reflect,     //反射モード.
	Player_SuperReflect //反射モード強化版.
};

class Player
{
private:
	PlayerMode mode{}; //モード.
	
	Circle hit{};      //プレイヤーの当たり判定円.
	bool   active{};   //有効か.
	bool   isDebug{};  //デバッグ用.

	float  afterCntr{};					   //残像用時間カウンター.
	DBL_XY afterPos[PLAYER_AFT_IMG_NUM]{}; //残像位置の履歴.

	DrawImg imgPlayer[2]{}; //プレイヤー画像.
	double  imgRot{};       //プレイヤーの画像角度.

	GameData*      p_data{};      //ゲームデータ.
	EffectManager* p_effectMng{}; //エフェクト管理.
	InputMng*      p_input{};     //入力機能.

public:

	//???
	static const int MAX_REFLECT_EFFECTS = 5;  // 最大エフェクト数
	ReflectEffect reflectEffects[MAX_REFLECT_EFFECTS]{};  // エフェクト配列
	int reflectEffectIndex{};  // 次に使用するエフェクトのインデックス

	//set.
	void       SetActive(bool _active)     { active = _active; }
	void       SetMode  (PlayerMode _mode) { mode   = _mode;   } //モード設定.
	//get. 
	DBL_XY     GetPos()   { return hit.pos; }
	bool       GetActive(){ return active; }
	PlayerMode GetMode()  { return mode; }
	Circle*    GetHit()   { return &hit; }


	//その他.
	void Init  (GameData*, EffectManager*);
	void Reset (DBL_XY _pos, bool _active);
	void Update();
	void Draw  ();

	void PlayerMove();       //プレイヤー移動.
	void PlayerDeath();      //プレイヤー死亡.

	void UpdateAfterImage(); //残像更新.
	void DrawAfterImage();   //残像描画.

	void CreateReflectEffect(DBL_XY pos);
	void UpdateReflectEffects();
	void DrawReflectEffects();
};