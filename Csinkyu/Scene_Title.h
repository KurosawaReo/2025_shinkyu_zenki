/*
   - Scene_Title.h -

   [Scene]
   ・Title <-
   ・Menu
   ・Game
   ・End
*/
#pragma once
#include "SceneBase.h"

//タイトルシーン.
class TitleScene : public State, public SceneBase
{
private:
public:
	void Init()   override;
	void Reset()  override;
	void Update() override;
	void Draw()   override;
};