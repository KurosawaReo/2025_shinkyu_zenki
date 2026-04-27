/*
   - BGManager.h -
*/
#pragma once
#include "BG1.h"
#include "BG2.h"

//”wŒiƒNƒ‰ƒX.
class BGManager final : public ManagerBase 
{
//¥ ===== •Ï” ===== ¥.
private:
	float counter{}; //Œo‰ßŠÔ.

	int   useBgNo{}; //‰½”Ô–Ú‚Ì”wŒi‚ğg‚¤‚©.
	BG1   bg1{};     //”wŒi1.
	BG2   bg2{};     //”wŒi2.

//¥ ===== ŠÖ” ===== ¥.
public:
	//ƒRƒ“ƒXƒgƒ‰ƒNƒ^.
	BGManager(int order) : ManagerBase(order) {}

	//set.
	void  SetBgNo(int _no) { useBgNo = _no; }
	//get.
	float GetCounter() const { return counter; }

	void  Init()   override;
	void  Reset()  override;
	void  Update() override;
	void  Draw()   override;

	//ƒ|[ƒY—p.
	void  Pause();
	void  PauseEnd();

	//g—p‹Ö~.
	BGManager(const BGManager*) = delete;
	BGManager* operator=(const BGManager*) = delete;
};