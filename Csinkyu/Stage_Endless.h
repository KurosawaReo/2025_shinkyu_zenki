/*
   - Stage_Endless.h -

   ステージ: 耐久モード.
*/
#pragma once

//エンドレスステージ.
class EndlessStage : public ManagerBase 
{
//▼実体関係.
public:
	static EndlessStage& GetInst() {
		static EndlessStage inst; //自身のインスタンス.
		return inst;
	}

//▼変数.
private:
	
//▼関数.
private:
	//コンストラクタ.
	EndlessStage() : ManagerBase(ORDER_ENDLESS_STAGE) {}

public:
	void Init()   override;
	void Reset()  override;
	void Update() override;
	void Draw()   override;

	void UpdateObjects();
	void DrawObjects();

	//使用禁止.
	EndlessStage(const EndlessStage&) = delete;
	EndlessStage& operator=(const EndlessStage&) = delete;
};