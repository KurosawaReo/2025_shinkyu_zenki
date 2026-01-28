/*
   - Scene_Game.h -

   [Scene]
   ・Title 
   ・Menu
   ・Game <-
   ・End
*/
#pragma once
#include "SceneBase.h"

//タイトルシーン.
class GameScene : public State, public SceneBase
{
private:
public:
	void Init()   override;
	void Reset()  override;
	void Update() override;
	void Draw()   override;
};