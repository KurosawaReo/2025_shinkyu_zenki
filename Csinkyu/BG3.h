/*
   - BG3.h -
*/
#pragma once
#include "BGBase.h"

//背景3.
class BG3 : public BGBase
{
//▼ ===== 変数 ===== ▼.
private:
	//疑似3Dオブジェクト.
	struct WarpPoint
	{
		double x;
		double y;
		double z;

		// 前フレーム位置
		double oldZ;
	};

	static constexpr int POINT_NUM = 220;

	WarpPoint point[POINT_NUM];

	double angle; //回転角.
	double pulse; //明滅.


//▼ ===== 関数 ===== ▼.
public:
	void Init()   override;
	void Update() override;

	//描画用.
	void DrawNor   (double modeAlpha, double count) override;	//描画(通常時)
	void DrawRef   (double modeAlpha, double count) override;	//描画(反射モード)
	void DrawCommon(double modeAlpha, MY_COLOR mainColor);		//描画(共通)

	//ポーズ用.
	void Pause()    override;
	void PauseEnd() override;
};