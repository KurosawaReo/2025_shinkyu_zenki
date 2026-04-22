/*
   - GameData.h -
*/
#pragma once

//ゲームデータ[継承不可]
class GameData final : public Singleton<GameData>
{
	friend class Singleton<GameData>;

//▼ ===== 変数 ===== ▼.
public:
	StageType  stage{};			//ステージ種類.
	bool       isPause{};       //ポーズ中かどうか.

	int		   score{};			//スコア.5
	int		   scoreBef{};		//スコア(時間加算前)
	int		   bestScore{};		//ベストスコア.
	int		   level{};			//レベル.

	float	   speedRate{};		//ゲーム進行速度倍率.
	float	   spawnRate{};		//障害物の出現時間割合.
	float	   counter{};		//経過時間カウンター(スローの影響を受ける)

	bool       isReflectMode{};	//反射モードかどうか.
	float      slowBufCntr{};	//スロー続行時間.

	umap<string, Font> fonts;	//フォントデータ.
	
//▼ ===== 関数 ===== ▼.
private:
	//コンストラクタ.
	GameData(){}
};