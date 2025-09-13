/*
   - BackGround.cpp -
*/
#include "GameManager.h"
#include "BackGround.h"

using namespace Calc; //計算機能を使用.

// ▼*---=[ BG_Tile ]=---*▼ //

//初期化.
void BG_Tile::Init(GameData* _data) {
	p_data = _data;
}
//更新.
void BG_Tile::Update() {

	//0になったら停止.
	if (timer.GetPassTime() <= 0) {
		timer.Reset();
	}
}
//描画.
void BG_Tile::Draw(bool isSlow, double slowTime) {

	//通常モード.
	{
		double alpha = 50 + 70 * sin(M_PI * timer.GetPassTime()/3);
		SetDrawBlendModeST(MODE_ALPHA, alpha * (1-slowTime) * (sin(M_PI * (double)(pos.x - pos.y + p_data->counter)/(WINDOW_WID/4))+1)/2);
		img[0]->DrawExtend(pos.ToDblXY(), sizeRate, ANC_MID);
	}
	//反射モード.
	if (isSlow) {
		double alpha = 70 + 100 * sin(M_PI * timer.GetPassTime()/3);
		SetDrawBlendModeST(MODE_ALPHA, alpha * slowTime* (sin(M_PI * (double)(pos.x - pos.y + p_data->counter)/(WINDOW_WID/4))+1)/2);
		img[1]->DrawExtend(pos.ToDblXY(), sizeRate, ANC_MID);
	}
	ResetDrawBlendMode(); //描画モードリセット.
}
//発光.
void BG_Tile::Shine() {
	//発光してないなら.
	if(!timer.GetIsMove()){
		timer.Start(); //開始.
	}
}

// ▼*---=[ BackGround ]=---*▼ //

//初期化.
void BackGround::Init() {

	p_data = GameData::GetPtr();

	imgBG[0].LoadFile(_T("Resources/Images/bg_normal.png"));
	imgBG[1].LoadFile(_T("Resources/Images/bg_reflect.png"));

	{
		INT_XY imgSize  = imgBG[0].GetSize(); //画像サイズ取得.
		DBL_XY sizeRate = { 0.1, 0.1 };       //サイズ倍率.

		INT_XY size = { _int_r(imgSize.x * sizeRate.x), _int_r(imgSize.y * sizeRate.y) };

		//タイルのように貼り付ける.
		for (int x = 0; x < WINDOW_WID + size.x; x += size.x) {
			for (int y = -size.y; y < WINDOW_HEI; y += size.y) {

				BG_Tile tile; //タイルを作成.

				tile.pos.x = x; 
				tile.pos.y = y;
				tile.sizeRate = sizeRate;
				tile.img[0] = &imgBG[0];
				tile.img[1] = &imgBG[1];
				tile.Init(p_data);
 				tiles.push_back(tile); //配列に追加.
			}
		}
	}

	tmShine.Start(); //タイマー開始.
}
//更新.
void BackGround::Update() {
	
	for (auto& i : tiles) {
		i.Update();
	}
}
//描画.
void BackGround::Draw() {

	//スローモード経過時間.
	float pass = GameManager::GetPtr()->GetSlowModeTime();
	//最初の0.5秒
	double time = 0.5-(pass -(SLOW_MODE_TIME-0.5));
	time = CalcNumEaseOut(time); //値の曲線変動.

	//いくつかのパターンを用意.(デザイン案)
#if false
	//背景デザイン.
	for (int x = 0; x < WINDOW_WID; x += 5) {

		int clr = _int45(20 * fabs(sin((double)(x+p_data->counter)/200))); //色の変化.
		Line line = { {(double)x, 0},{(double)x, WINDOW_HEI}, GetColor(0, clr, clr) };
		DrawLineST(&line, false, 5);
	}

#elif false
	//背景画像.
	{
		INT_XY imgSize = imgBG[0].GetImage()->size; //画像サイズ取得.
		DBL_XY sizeRate = {0.1, 0.1};               //サイズ倍率.

		INT_XY size = {_int45(imgSize.x * sizeRate.x), _int45(imgSize.y * sizeRate.y)};
		
		//タイルのように貼り付ける.
		for (int x = 0; x < WINDOW_WID+size.x; x += size.x) {
			for (int y = -size.y; y < WINDOW_HEI; y += size.y) {
				
				//座標を少しずつずらす.
				INT_XY newPos = {
					_int45(x - fmod(p_data->counter, size.x)), //sizeで割った余り.
					_int45(y + fmod(p_data->counter, size.y))
				};
				//通常モード.
				{
					double alpha = (1-time) * (sin(M_PI*(double)(newPos.x-newPos.y)/(WINDOW_WID/4))+1)/2;
					SetDrawBlendModeST(MODE_ALPHA, 100*alpha);
					imgBG[0].DrawExtendGraphST(newPos, sizeRate, ANC_MID);
				}
				//反射モード.
				if (p_data->isSlow) {
					double alpha = time * (sin(M_PI*(double)(newPos.x-newPos.y)/(WINDOW_WID/4))+1)/2;
					SetDrawBlendModeST(MODE_ALPHA, 100*alpha);
					imgBG[1].DrawExtendGraphST(newPos, sizeRate, ANC_MID);
				}
			}
		}

		ResetDrawBlendMode(); //描画モードリセット.
	}
#else
	//一定間隔ごと.
	if (tmShine.IntervalTime()) {
		int idx = RandNum(0, (int)tiles.size()-1);
		tiles[idx].Shine(); //ランダムでタイルを発光させる.
	}
	//描画.
	for (auto& i : tiles) {
		i.Draw(p_data->isSlow, time);
	}
#endif

	//スローモード中.
	if (p_data->isSlow) {
		//枠線.
		Box box = { {WINDOW_WID/2, WINDOW_HEI/2}, {WINDOW_WID * time, WINDOW_HEI * time}, COLOR_PLY_REFLECT };
		DrawBoxST(&box, ANC_MID, false, true);
	}
}