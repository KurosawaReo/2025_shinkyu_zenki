/*
   - Player.h -
   プレイヤー管理.
*/
#pragma once
#include "EffectManager.h"

class GameData; //前方宣言.

//ダッシュエフェクト.
struct ReflectEffect
{
	DBL_XY pos;           // エフェクト位置
	float  scale;         // スケール
	float  alpha;         // 透明度
	int    timer;         // 表示時間
	bool   active;        // 有効フラグ
};

//残像データ.
struct AfterEffect
{
	DBL_XY pos;
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
	PlayerMode  mode{};     //モード.
	
	Circle      hit{};      //プレイヤーの当たり判定円.
	bool        active{};   //有効か.
	bool        isDebug{};  //デバッグ用.

	float       afterCntr{};	 		     //残像用時間カウンター.
	AfterEffect after[PLAYER_AFT_IMG_NUM]{}; //残像位置の履歴.

	DrawImg     imgPlayer[2]{}; //プレイヤー画像.
	double      imgRot{};       //プレイヤーの画像角度.

	bool        isMoveAble{};   //移動可能かどうか.

	GameData*      p_data{};      //ゲームデータ.
	EffectManager* p_effectMng{}; //エフェクト管理.
	InputMng*      p_input{};     //入力機能.

	//エフェクト用(未使用)
	ReflectEffect reflectEffects[PLAYER_MAX_EFFECT]{}; // エフェクト配列
	int reflectEffectIndex{};                          // 次に使用するエフェクトのインデックス

public:
	//set.
	void       SetPos       (DBL_XY     _pos)    { hit.pos    = _pos;    }
	void       SetActive    (bool       _active) { active     = _active; }
	void       SetMode      (PlayerMode _mode)   { mode       = _mode;   } //モード設定.
	void       SetIsMoveAble(bool       _flag)   { isMoveAble = _flag;   }
	//get. 
	DBL_XY     GetPos()     const { return hit.pos; }
	bool       GetActive()  const { return active; }
	PlayerMode GetMode()    const { return mode; }
	Circle     GetHit()     const { return hit; }
	//計測.
	double     GetMoveDist() const { 
		return Calc::CalcDist(hit.pos, after[1].pos); //移動した距離.
	}

	//その他.
	void Init  ();
	void Reset (DBL_XY _pos, bool _active);
	void Update();
	void Draw  ();

	void PlayerMove();       //プレイヤー移動.
	void PlayerDeath();      //プレイヤー死亡.
	void PlayerRevival();    //プレイヤー復活.

	void UpdateAfterImage(); //残像更新.
	void DrawAfterImage();   //残像描画.

	//エフェクト用(未使用)
	void CreateReflectEffect(DBL_XY pos);
	void UpdateReflectEffects();
	void DrawReflectEffects();
};