/*
   - Stage_Tutorial.h -

   ステージ: チュートリアル.
*/
#pragma once

//チュートリアル.[継承不可]
class TutorialStage final
{
//▼実体関係.
public:
	static TutorialStage& GetInst() {
		static TutorialStage inst; //自身のインスタンス.
		return inst;
	}

//▼変数.
private:
	Font   font[2]{};
	
	int    stepNo{};          //現在のステップ番号.
	int    stepInNo{};        //現在のステップ内番号.

	double plyMoveSum{};      //プレイヤーの移動距離.

	bool   isPlayerDash{};    //プレイヤーがダッシュしたかどうか.
	bool   isTakeItem{};      //アイテムを取ったかどうか.
	bool   isReflectLaser{};  //レーザーを反射したかどうか.
	bool   isReflectFinish{}; //反射モードが終わったかどうか.
	bool   isBreakMeteor{};   //隕石を壊したかどうか.

	Timer  startTimer{};      //項目開始時に計測開始.
	Timer  endTimer{};        //項目終了時に計測開始.

//▼関数.
private:
	//constructor(新規作成をできなくする)
	TutorialStage(){}

public:
	//set.
	void SetPlayerDash   (bool _flag) { isPlayerDash    = _flag; }
	void SetTakeItem     (bool _flag) { isTakeItem      = _flag; }
	void SetReflectLaser (bool _flag) { isReflectLaser  = _flag; }
	void SetReflectFinish(bool _flag) { isReflectFinish = _flag; }
	void SetBreakMeteor  (bool _flag) { isBreakMeteor   = _flag; }
	//get
	int  GetStepNo() const { return stepNo; }

	void Init();
	void Reset();
	void Update();
	void Draw();

	void ResetSignFlag();
	void StepInEnd();

	void UpdateStep0();
	void UpdateStep1();
	void UpdateStep2();
	void UpdateStep3();
	void UpdateStep4();

	void DrawStep1();
	void DrawStep2();
	void DrawStep3();
	void DrawStep4();

	void DrawTopText1(MY_STRING text, double alpha);
	void DrawTopText2(MY_STRING text, double alpha);
	void DrawTopText3(MY_STRING text, double alpha);
	void DrawTopText4(MY_STRING text, double alpha);

	//使用禁止.
	TutorialStage(const TutorialStage&) = delete;
	TutorialStage& operator=(const TutorialStage&) = delete;
};