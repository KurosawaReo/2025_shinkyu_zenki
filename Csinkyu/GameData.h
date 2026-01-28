/*
   - GameData.h -
*/
#pragma once

//ゲームデータ.[継承不可]
class GameData final
{
//▼ ===== 実体 ===== ▼.
public:
	static GameData& GetInst() {
		static GameData inst; //自身のインスタンス.
		return inst;
	}

//▼ ===== 変数 ===== ▼.
public:
	StageType  stage{};			//ステージ種類.
	bool       isPause{};       //ポーズ中かどうか.

	int		   score{};			//スコア.
	int		   scoreBef{};		//スコア(時間加算前)
	int		   bestScore{};		//ベストスコア.
	int		   level{};			//レベル.

	float	   speedRate{};		//ゲーム進行速度倍率.
	float	   spawnRate{};		//障害物の出現時間割合.
	float	   counter{};		//経過時間カウンター(スローの影響を受ける)

	bool       isReflectMode{};	//反射モードかどうか.
	float      slowBufCntr{};	//スロー続行時間.

	int		   font1{};			//フォント.
	int		   font2{};			//フォント.
	int		   font3{};			//フォント.
	int		   font4{};			//フォント.
	
//▼ ===== 関数 ===== ▼.
private:
	//コンストラクタ.
	GameData(){}

public:
	//使用禁止.
	GameData(const GameData&) = delete;
	GameData& operator=(const GameData&) = delete;
};