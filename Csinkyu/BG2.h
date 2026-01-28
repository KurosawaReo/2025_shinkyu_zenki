/*
   - BG2.h -
*/
#pragma once

//背景2.
class BG2
{
//▼ ===== 変数 ===== ▼.
private:
	double angle{};      // 回転用
	double pulse{};      // 明滅用
	bool   isPaused{};   // ポーズ状態

//▼ ===== 関数 ===== ▼.
public:
	void Init();
	void Update();
	void Draw();

	//ポーズ用.
	void PauseAnim();
	void RestartAnim();
};