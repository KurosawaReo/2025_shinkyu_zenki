/*
   - BG1.cpp -
*/
#include "BG1.h"

#include "BGManager.h"
#include "GameManager.h"

// ▼*---=[ BG_Tile ]=---*▼ //

//初期化.
void BG_Tile::Init() {
	p_data = &GameData::GetInst();
}
//更新.
void BG_Tile::Update() {
	//0になったら停止.
	if (timer.GetPassTime() <= 0) {
		timer.Reset();
	}
}
//描画.
void BG_Tile::Draw(double slowTime) {

	const float counter = BGManager::GetInst().GetCounter();

	//通常モード.
	{
		//透明度計算.
		const double alpha  = 70 + 80 * sin(M_PI * timer.GetPassTime()/3);
		const double sinNum = (sin(M_PI * _dbl(pos.x - pos.y + counter*2)/(WINDOW_WID/4)) + 1) / 2;
		//透明度設定.
		SetDrawBlendModeKR(BlendModeID::Alpha, alpha * sinNum * (1-slowTime));
		//画像.
		DrawImgMng::Get("bg_normal")->DrawExtend(pos.ToDbl(), sizeRate, Anchor::Mid);
	}
	//反射モード.
	if (p_data->isReflectMode) {
		//透明度計算.
		const double alpha  = 70 + 80 * sin(M_PI * timer.GetPassTime()/3);
		const double sinNum = (sin(M_PI * _dbl(pos.x - pos.y + counter*2)/(WINDOW_WID/4)) + 1) / 2;
		//透明度設定.
		SetDrawBlendModeKR(BlendModeID::Alpha, alpha * sinNum * slowTime);
		//画像.
		DrawImgMng::Get("bg_reflect")->DrawExtend(pos.ToDbl(), sizeRate, Anchor::Mid);
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

// ▼*---=[ BG1 ]=---*▼ //

//初期化.
void BG1::Init() {

	p_data = &GameData::GetInst();

	DrawImgMng::LoadFile(_T("Resources/Images/bg_normal.png"),          "bg_normal");
	DrawImgMng::LoadFile(_T("Resources/Images/bg_reflect.png"),         "bg_reflect");
	DrawImgMng::LoadFile(_T("Resources/Images/reflect_mode_frame.png"), "reflect_mode_frame");

	{
		INT_XY imgSize  = DrawImgMng::Get("bg_normal")->GetSize(); //画像サイズ取得.
		DBL_XY sizeRate = { 0.1, 0.1 };                            //サイズ倍率.

		INT_XY size = { _int_r(imgSize.x * sizeRate.x), _int_r(imgSize.y * sizeRate.y) };

		//タイルのように貼り付ける.
		for (int x = 0; x < WINDOW_WID + size.x; x += size.x) {
			for (int y = -size.y; y < WINDOW_HEI; y += size.y) {

				BG_Tile tile; //タイルを作成.

				tile.pos.x = x; 
				tile.pos.y = y;
				tile.sizeRate = sizeRate;
				tile.Init();
 				tiles.push_back(tile); //配列に追加.
			}
		}
	}

	tmShine.Start(); //タイマー開始.
}
//更新.
void BG1::Update() {

	//一定間隔ごと.
	if (tmShine.IntervalTime()) {
		int idx = Calc::RandNum(0, (int)tiles.size()-1);
		tiles[idx].Shine(); //ランダムでタイルを発光させる.
	}
	//各タイル更新.
	for (auto& i : tiles) {
		i.Update();
	}
}
//描画.
void BG1::Draw() {

	//スローモード経過時間.
	float pass = GameManager::GetInst().GetReflectModeTime();
	//最初の0.5秒
	double time = 0.5-(pass -(REFLECT_MODE_TIME-0.5));
	time = Calc::AnimEaseOut(time); //値の曲線変動.

	//各タイル描画.
	for (auto& i : tiles) {
		i.Draw(time);
	}
	//スローモード中.
	if (p_data->speedRate) {
		//グラデーション枠.
		SetDrawBlendModeKR(BlendModeID::Alpha, 255*time);
		DrawImgMng::Get("reflect_mode_frame")->Draw({WINDOW_WID/2, WINDOW_HEI/2});
		ResetDrawBlendMode();
		//枠線.
		Box box = { {WINDOW_WID/2, WINDOW_HEI/2}, {WINDOW_WID * time, WINDOW_HEI * time}, COLOR_PLY_REFLECT };
		DrawBoxKR(box, Anchor::Mid, false, true);
	}
}

//ポーズする.
void BG1::StopAnim() {
	for (auto& i : tiles) {
		i.timer.Stop();
	}
}
//ポーズ解除.
void BG1::RestartAnim() {
	for (auto& i : tiles) {
		//稼働中だったならリスタート.
		if (i.timer.GetIsMove()) {
			i.timer.Start();
		}
	}
}