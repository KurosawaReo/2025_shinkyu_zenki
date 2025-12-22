/*
   - BGManager.h -
*/
#pragma once
#include "BG1.h"
#include "BG2.h"

//”wŒiƒNƒ‰ƒX.[Œp³•s‰Â]
class BGManager final
{
//¥À‘ÌŠÖŒW.
public:
	static BGManager& GetInst() {
		static BGManager inst; //©g‚ÌƒCƒ“ƒXƒ^ƒ“ƒX.
		return inst;
	}

//¥•Ï”.
private:
	float counter{}; //Œo‰ßŠÔ.

	int   useBgNo{}; //‰½”Ô–Ú‚Ì”wŒi‚ğg‚¤‚©.
	BG1   bg1{};     //”wŒi1.
	BG2   bg2{};     //”wŒi2.

//¥ŠÖ”.
private:
	//constructor(V‹Kì¬‚ğ‚Å‚«‚È‚­‚·‚é)
	BGManager(){}

public:
	//set.
	void  SetBgNo(int _no) { useBgNo = _no; }
	//get.
	float GetCounter() const { return counter; }

	void  Init();
	void  Update();
	void  Draw();

	//ƒ|[ƒY—p.
	void  PauseAnim();
	void  RestartAnim();

	//g—p‹Ö~.
	BGManager(const BGManager&) = delete;
	BGManager& operator=(const BGManager&) = delete;
};