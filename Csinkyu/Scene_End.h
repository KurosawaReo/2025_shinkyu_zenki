/*
   - Scene_End.h -
   
   [Scene]
   ・Title 
   ・Menu
   ・Game
   ・End <-
*/
#pragma once
#include "SceneBase.h"

//終了シーン.
class EndScene : public SceneBase
{
private:
public:
	void Init()   override;
	void Reset()  override;
	void Update() override;
	void Draw()   override;
};