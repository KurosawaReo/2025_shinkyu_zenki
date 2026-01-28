/*
   - SceneBase.h -
*/
#pragma once

//KrLib名前空間.
namespace KR
{
	//シーンクラスの元[継承想定]
	class SceneBase
	{
	protected:
		Timer tmScene; //シーンごとに経過時間を計測.

	public:
		//コンストラクタ.
		SceneBase() : tmScene(Timer(TimerMode::CountUp, 0)) {}

		virtual void Init()   = 0;
		virtual void Reset()  = 0;
		virtual void Update() = 0;
		virtual void Draw()   = 0;
	};
}