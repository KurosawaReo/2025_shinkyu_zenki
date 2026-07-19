/*
   - BGBase.h -
   このクラスを継承して背景を作る。
*/
#pragma once

//背景基底クラス.
class BGBase
{
//▼ ===== 関数 ===== ▼.
public:
	virtual void Init()   = 0;
	virtual void Update() = 0;

	//描画用.
	virtual void DrawNor(double modeAlpha, double count) = 0; //描画(通常時)
	virtual void DrawRef(double modeAlpha, double count) = 0; //描画(反射モード)

	//ポーズ用.
	virtual void Pause()    = 0;
	virtual void PauseEnd() = 0;
};