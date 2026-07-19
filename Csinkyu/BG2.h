/*
   - BG2.h -
*/
#pragma once
#include "BGBase.h"

//”wŒi2.
class BG2 : public BGBase
{
//¥ ===== •Ï” ===== ¥.
private:

//¥ ===== ŠÖ” ===== ¥.
public:
	void Init()   override;
	void Update() override;

	//•`‰æ—p.
	void DrawNor(double modeAlpha, double count) override; //•`‰æ(’Êí)
	void DrawRef(double modeAlpha, double count) override; //•`‰æ(”½Ëƒ‚[ƒh)

	//ƒ|[ƒY—p.
	void Pause()    override;
	void PauseEnd() override;
};