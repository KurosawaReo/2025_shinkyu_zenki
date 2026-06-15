/*
   - BG3.h -
*/
#pragma once

#include "DxLib.h"
#include <vector>

//背景3.
class BG3
{
private:

	//==============================
	// 六角形1枚分の情報
	//==============================
	struct HexData
	{
		float x;
		float z;

		//高さ(凹凸)
		float height;

		//発光するか
		bool isGlow;
	};

	//六角形リスト.
	std::vector<HexData> m_hexList;

	//光アニメ用.
	float m_glowAnim = 0.0f;

public:
	void Init();
	void Update();
	void Draw();

	//ポーズ用.
	void Pause();
	void PauseEnd();
};